#include "filexml.h"
#include "keyframe.h"

#include <stdio.h>
#include <string.h>



KeyFrame::KeyFrame()
 : Auto()
{
	data[0] = 0;
}

KeyFrame::KeyFrame(EDL *edl, KeyFrames *autos)
 : Auto(edl, (Autos*)autos)
{
	data[0] = 0;
}
KeyFrame::~KeyFrame()
{
}

void KeyFrame::load(FileXML *file)
{
//printf("KeyFrame::load 1\n");
// Shouldn't be necessary
//	position = file->tag.get_property("POSITION", position);
//printf("KeyFrame::load 1\n");

	file->read_text_until("/KEYFRAME", data, MESSAGESIZE);
//printf("KeyFrame::load 2 data=\n%s\nend of data\n", data);
}

void KeyFrame::copy(int64_t start, int64_t end, FileXML *file, int default_auto)
{
//printf("KeyFrame::copy 1 %d\n%s\n", position - start, data);
	file->tag.set_title("KEYFRAME");
	if(default_auto)
		file->tag.set_property("POSITION", 0);
	else
		file->tag.set_property("POSITION", position - start);
// default_auto converts a default auto to a normal auto
	if(is_default && !default_auto)
		file->tag.set_property("DEFAULT", 1);
	file->append_tag();
// Can't put newlines in because these would be reimported and resaved along
// with new newlines.
//	file->append_newline();

	file->append_text(data);
//	file->append_newline();

	file->tag.set_title("/KEYFRAME");
	file->append_tag();
	file->append_newline();
}


void KeyFrame::copy_from(Auto *that)
{
	copy_from((KeyFrame*)that);
}

void KeyFrame::copy_from(KeyFrame *that)
{
	Auto::copy_from(that);
	KeyFrame *keyframe = (KeyFrame*)that;
	strcpy(data, keyframe->data);
	position = keyframe->position;
}


int KeyFrame::identical(KeyFrame *src)
{
	return !strcasecmp(src->data, data);
}


int KeyFrame::operator==(Auto &that)
{
	return identical((KeyFrame*)&that);
}

int KeyFrame::operator==(KeyFrame &that)
{
	return identical(&that);
}


void KeyFrame::dump()
{
	printf("     position: %lld\n", position);
	printf("     data: %s\n", data);
}
