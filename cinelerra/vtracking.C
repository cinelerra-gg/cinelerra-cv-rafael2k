#include "asset.h"
#include "assets.h"
#include "edl.h"
#include "edlsession.h"
#include "localsession.h"
#include "mainclock.h"
#include "meterpanel.h"
#include "mwindow.h"
#include "renderengine.h"
#include "mainclock.h"
#include "vplayback.h"
#include "vrender.h"
#include "vtimebar.h"
#include "vtracking.h"
#include "vwindow.h"
#include "vwindowgui.h"


VTracking::VTracking(MWindow *mwindow, VWindow *vwindow)
 : Tracking(mwindow)
{
	this->vwindow = vwindow;
}

VTracking::~VTracking()
{
}

PlaybackEngine* VTracking::get_playback_engine()
{
	return vwindow->playback_engine;
}

void VTracking::update_tracker(double position)
{
	Asset *asset = vwindow->get_edl()->assets->first;
//printf("VTracking::update_tracker %ld\n", position);
	vwindow->gui->lock_window("VTracking::update_tracker");
	vwindow->get_edl()->local_session->set_selectionstart(position);
	vwindow->get_edl()->local_session->set_selectionend(position);
	vwindow->gui->slider->update(position);

	vwindow->gui->clock->update(position + 
		asset->tcstart / (asset->video_data ?
							asset->frame_rate :
							asset->sample_rate));

// This is going to boost the latency but we need to update the timebar
	vwindow->gui->timebar->draw_range();
	vwindow->gui->timebar->flash();

	vwindow->gui->unlock_window();

	update_meters((int64_t)(position * mwindow->edl->session->sample_rate));
}

void VTracking::update_meters(int64_t position)
{
	double output_levels[MAXCHANNELS];

	int do_audio = get_playback_engine()->get_output_levels(output_levels, 
		position);
	if(do_audio)
	{
		vwindow->gui->lock_window("VTracking::update_meters");
		vwindow->gui->meters->update(output_levels);
		vwindow->gui->unlock_window();
	}
}

void VTracking::stop_meters()
{
	vwindow->gui->lock_window("VTracking::stop_meters");
	vwindow->gui->meters->stop_meters();
	vwindow->gui->unlock_window();
}

void VTracking::draw()
{
}
