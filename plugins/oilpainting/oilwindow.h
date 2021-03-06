#ifndef BLURWINDOW_H
#define BLURWINDOW_H

#include "bcbase.h"

class OilThread;
class OilWindow;

#include "filexml.h"
#include "mutex.h"
#include "oil.h"

class OilThread : public Thread
{
public:
	OilThread(OilMain *client);
	~OilThread();

	void run();

	Mutex gui_started; // prevent loading data until the GUI is started
	OilMain *client;
	OilWindow *window;
};

class OilRadius;
class OilIntensity;

class OilWindow : public BC_Window
{
public:
	OilWindow(OilMain *client);
	~OilWindow();
	
	int create_objects();
	int close_event();
	
	OilMain *client;
	OilRadius *radius;
	OilIntensity *use_intensity;
};

class OilRadius : public BC_IPot
{
public:
	OilRadius(OilMain *client, int x, int y);
	~OilRadius();
	int handle_event();

	OilMain *client;
};

class OilIntensity : public BC_CheckBox
{
public:
	OilIntensity(OilMain *client, int x, int y);
	~OilIntensity();
	int handle_event();

	OilMain *client;
};


#endif
