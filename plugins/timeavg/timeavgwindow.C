#include "bcdisplayinfo.h"
#include "language.h"
#include "timeavgwindow.h"

PLUGIN_THREAD_OBJECT(TimeAvgMain, TimeAvgThread, TimeAvgWindow)


#define MAX_FRAMES 1024


TimeAvgWindow::TimeAvgWindow(TimeAvgMain *client, int x, int y)
 : BC_Window(client->gui_string, 
 	x, 
	y, 
	210, 
	210, 
	200, 
	210, 
	0, 
	0,
	1)
{ 
	this->client = client; 
}

TimeAvgWindow::~TimeAvgWindow()
{
}

int TimeAvgWindow::create_objects()
{
	int x = 10, y = 10;
	add_tool(new BC_Title(x, y, _("Frames to average")));
	y += 20;
	add_tool(total_frames = new TimeAvgSlider(client, x, y));
	y += 30;
	add_tool(accum = new TimeAvgAccum(client, this, x, y));
	y += 30;
	add_tool(avg = new TimeAvgAvg(client, this, x, y));
	y += 30;
	add_tool(inclusive_or = new TimeAvgOr(client, this, x, y));
	y += 30;
	add_tool(paranoid = new TimeAvgParanoid(client, x, y));
	y += 30;
	add_tool(no_subtract = new TimeAvgNoSubtract(client, x, y));
	show_window();
	flush();
	return 0;
}

WINDOW_CLOSE_EVENT(TimeAvgWindow)

TimeAvgSlider::TimeAvgSlider(TimeAvgMain *client, int x, int y)
 : BC_ISlider(x, 
 	y, 
	0,
	190, 
	200, 
	1, 
	MAX_FRAMES, 
	client->config.frames)
{
	this->client = client;
}
TimeAvgSlider::~TimeAvgSlider()
{
}
int TimeAvgSlider::handle_event()
{
	int result = get_value();
	if(result < 1) result = 1;
	client->config.frames = result;
	client->send_configure_change();
	return 1;
}













TimeAvgAccum::TimeAvgAccum(TimeAvgMain *client, TimeAvgWindow *gui, int x, int y)
 : BC_Radial(x, 
 	y, 
	client->config.mode == TimeAvgConfig::ACCUMULATE,
	_("Accumulate"))
{
	this->client = client;
	this->gui = gui;
}
int TimeAvgAccum::handle_event()
{
	int result = get_value();
	client->config.mode = TimeAvgConfig::ACCUMULATE;
	gui->avg->update(0);
	gui->inclusive_or->update(0);
	client->send_configure_change();
	return 1;
}





TimeAvgAvg::TimeAvgAvg(TimeAvgMain *client, TimeAvgWindow *gui, int x, int y)
 : BC_Radial(x, 
 	y, 
	client->config.mode == TimeAvgConfig::AVERAGE,
	_("Average"))
{
	this->client = client;
	this->gui = gui;
}
int TimeAvgAvg::handle_event()
{
	int result = get_value();
	client->config.mode = TimeAvgConfig::AVERAGE;
	gui->accum->update(0);
	gui->inclusive_or->update(0);
	client->send_configure_change();
	return 1;
}



TimeAvgOr::TimeAvgOr(TimeAvgMain *client, TimeAvgWindow *gui, int x, int y)
 : BC_Radial(x, 
 	y, 
	client->config.mode == TimeAvgConfig::OR,
	_("Inclusive Or"))
{
	this->client = client;
	this->gui = gui;
}
int TimeAvgOr::handle_event()
{
	int result = get_value();
	client->config.mode = TimeAvgConfig::OR;
	gui->accum->update(0);
	gui->avg->update(0);
	client->send_configure_change();
	return 1;
}



TimeAvgParanoid::TimeAvgParanoid(TimeAvgMain *client, int x, int y)
 : BC_CheckBox(x, 
 	y, 
	client->config.paranoid,
	_("Reprocess frame again"))
{
	this->client = client;
}
int TimeAvgParanoid::handle_event()
{
	int result = get_value();
	client->config.paranoid = result;
	client->send_configure_change();
	return 1;
}





TimeAvgNoSubtract::TimeAvgNoSubtract(TimeAvgMain *client, int x, int y)
 : BC_CheckBox(x, 
 	y, 
	client->config.nosubtract,
	_("Disable subtraction"))
{
	this->client = client;
}
int TimeAvgNoSubtract::handle_event()
{
	int result = get_value();
	client->config.nosubtract = result;
	client->send_configure_change();
	return 1;
}








