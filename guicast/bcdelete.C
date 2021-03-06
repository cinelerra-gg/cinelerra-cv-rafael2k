#include "bcdelete.h"
#include "bcsignals.h"
#include "filesystem.h"
#include "language.h"





BC_DeleteFile::BC_DeleteFile(BC_FileBox *filebox, int x, int y)
 : BC_Window(filebox->get_delete_title(), 
 	x, 
	y, 
	320, 
	480, 
	0, 
	0, 
	0, 
	0, 
	1)
{
	this->filebox = filebox;
	data = 0;
}

BC_DeleteFile::~BC_DeleteFile()
{
	delete data;
}

void BC_DeleteFile::create_objects()
{
	int x = 10, y = 10;
	data = new ArrayList<BC_ListBoxItem*>;
	int i = 1;
	char *path;
	FileSystem fs;

	while((path = filebox->get_path(i)))
	{
		data->append(new BC_ListBoxItem(path));
		i++;
	}
		
	BC_Title *title;
	add_subwindow(title = new BC_Title(x, y, _("Really delete the following files?")));
	y += title->get_h() + 5;
	BC_DeleteList *list;
	add_subwindow(list = new BC_DeleteList(filebox, 
		x, 
		y, 
		get_w() - x * 2, 
		get_h() - y - BC_OKButton::calculate_h() - 20,
		data));
	y += list->get_h() + 5;
	add_subwindow(new BC_OKButton(this));
	add_subwindow(new BC_CancelButton(this));
	show_window();
}





BC_DeleteList::BC_DeleteList(BC_FileBox *filebox, 
	int x, 
	int y, 
	int w, 
	int h,
	ArrayList<BC_ListBoxItem*> *data)
 : BC_ListBox(x, 
 	y, 
	w, 
	h, 
	LISTBOX_TEXT,
	data)
{
	this->filebox = filebox;
}










BC_DeleteThread::BC_DeleteThread(BC_FileBox *filebox)
 : BC_DialogThread()
{
	this->filebox = filebox;
}

void BC_DeleteThread::handle_done_event(int result)
{
	if(!result)
	{
		filebox->lock_window("BC_DeleteThread::handle_done_event");
		filebox->delete_files();
		filebox->unlock_window();
	}
}

BC_Window* BC_DeleteThread::new_gui()
{
	int x = filebox->get_abs_cursor_x(1);
	int y = filebox->get_abs_cursor_y(1);
	BC_DeleteFile *result = new BC_DeleteFile(filebox, x, y);
	result->create_objects();
	return result;
}








