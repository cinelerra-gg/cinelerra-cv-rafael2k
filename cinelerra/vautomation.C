#include "clip.h"
#include "colors.h"
#include "edl.h"
#include "edlsession.h"
#include "floatauto.h"
#include "floatautos.h"
#include "intauto.h"
#include "intautos.h"
#include "maskautos.h"
#include "overlayframe.inc"
#include "transportque.inc"
#include "vautomation.h"


VAutomation::VAutomation(EDL *edl, Track *track)
 : Automation(edl, track)
{
}



VAutomation::~VAutomation()
{
}


int VAutomation::create_objects()
{
	Automation::create_objects();

	autos[AUTOMATION_FADE] = new FloatAutos(edl, track, 100);
	autos[AUTOMATION_FADE]->create_objects();

	autos[AUTOMATION_MODE] = new IntAutos(edl, track, TRANSFER_NORMAL);
	autos[AUTOMATION_MODE]->create_objects();

	autos[AUTOMATION_MASK] = new MaskAutos(edl, track);
	autos[AUTOMATION_MASK]->create_objects();

	autos[AUTOMATION_CAMERA_X] = new FloatAutos(edl, track, 0.0);
	autos[AUTOMATION_CAMERA_X]->create_objects();

	autos[AUTOMATION_CAMERA_Y] = new FloatAutos(edl, track, 0.0);
	autos[AUTOMATION_CAMERA_Y]->create_objects();

	autos[AUTOMATION_PROJECTOR_X] = new FloatAutos(edl, track, 0.0);
	autos[AUTOMATION_PROJECTOR_X]->create_objects();

	autos[AUTOMATION_PROJECTOR_Y] = new FloatAutos(edl, track, 0.0);
	autos[AUTOMATION_PROJECTOR_Y]->create_objects();

	autos[AUTOMATION_CAMERA_Z] = new FloatAutos(edl, track, 1.0);
	autos[AUTOMATION_CAMERA_Z]->create_objects();

	autos[AUTOMATION_PROJECTOR_Z] = new FloatAutos(edl, track, 1.0);
	autos[AUTOMATION_PROJECTOR_Z]->create_objects();

// 	autos[AUTOMATION_NUDGE] = new FloatAutos(edl, track, 0.0);
// 	autos[AUTOMATION_NUDGE]->create_objects();

	for(int i = 0; i < AUTOMATION_TOTAL; i++)
		if (autos[i]) 
		{
			autos[i]->autoidx = i;
			autos[i]->autogrouptype = autogrouptype(i, autos[i]->track);
		}

	return 0;
}

int VAutomation::direct_copy_possible(int64_t start, int direction)
{
	int64_t end = (direction == PLAY_FORWARD) ? (start + 1) : (start - 1);

	if(!Automation::direct_copy_possible(start, direction))
		return 0;

// Automation is constant
	double constant;
	if(((FloatAutos*)autos[AUTOMATION_FADE])->automation_is_constant(
		start, 1, direction, constant))
	{
		if(!EQUIV(constant, 100))
			return 0;
	}
	else
// Automation varies
		return 0;

// Track must not be muted
	if(autos[AUTOMATION_MUTE]->automation_is_constant(start, end))
	{
		if(autos[AUTOMATION_MUTE]->get_automation_constant(start, end) > 0)
			return 0;
	}
	else
		return 0;

// Projector must be centered.
	FloatAuto *previous = 0, *next = 0;
	float z = ((FloatAutos*)autos[AUTOMATION_PROJECTOR_Z])->get_value(
		start, direction, previous, next);
	if(!EQUIV(z, 1)) return 0;

	previous = 0;
	next = 0;
	float x = ((FloatAutos*)autos[AUTOMATION_PROJECTOR_X])->get_value(start,
				direction,
				previous, 
				next);
	if(!EQUIV(x, 0)) return 0;
	previous = 0;
	next = 0;
	float y = ((FloatAutos*)autos[AUTOMATION_PROJECTOR_Y])->get_value(start,
				direction,
				previous, 
				next);
	if(!EQUIV(y, 0)) return 0;




// Camera must be centered
	previous = 0;
	next = 0;
	z = ((FloatAutos*)autos[AUTOMATION_CAMERA_Z])->get_value(
		start, 
		direction, 
		previous, 
		next);
	if(!EQUIV(z, 1)) return 0;



	previous = 0;
	next = 0;
	x = ((FloatAutos*)autos[AUTOMATION_CAMERA_X])->get_value(start,
				direction,
				previous, 
				next);
	if(!EQUIV(x, 0)) return 0;

	previous = 0;
	next = 0;
	y = ((FloatAutos*)autos[AUTOMATION_CAMERA_Y])->get_value(start,
				direction,
				previous, 
				next);

	if(!EQUIV(y, 0)) return 0;

// No mask must exist
	if(((MaskAutos*)autos[AUTOMATION_MASK])->mask_exists(start, direction))
		return 0;

	return 1;
}

void VAutomation::get_projector(float *x, 
	float *y, 
	float *z, 
	int64_t position,
	int direction)
{
	FloatAuto *before, *after;
	before = 0;
	after = 0;
	*x = ((FloatAutos*)autos[AUTOMATION_PROJECTOR_X])->get_value(position,
		direction,
		before,
		after);
	before = 0;
	after = 0;
	*y = ((FloatAutos*)autos[AUTOMATION_PROJECTOR_Y])->get_value(position,
		direction,
		before,
		after);
	before = 0;
	after = 0;
	*z = ((FloatAutos*)autos[AUTOMATION_PROJECTOR_Z])->get_value(position,
		direction,
		before,
		after);
}


void VAutomation::get_camera(float *x, 
	float *y, 
	float *z, 
	int64_t position,
	int direction)
{
	FloatAuto *before, *after;
	before = 0;
	after = 0;
	*x = ((FloatAutos*)autos[AUTOMATION_CAMERA_X])->get_value(position,
		direction,
		before,
		after);
	before = 0;
	after = 0;
	*y = ((FloatAutos*)autos[AUTOMATION_CAMERA_Y])->get_value(position,
		direction,
		before,
		after);
	before = 0;
	after = 0;
	*z = ((FloatAutos*)autos[AUTOMATION_CAMERA_Z])->get_value(position,
		direction,
		before,
		after);
}

