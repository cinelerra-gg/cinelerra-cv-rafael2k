#ifndef TRANSPORTQUE_INC
#define TRANSPORTQUE_INC

// Directions
#define PLAY_FORWARD 0
#define PLAY_REVERSE 1

// Commands
// Perform change but don't render anything
#define COMMAND_NONE              0
// Stop playback but keep existing change_type flag
#define STOP              	 	  7

#define SINGLE_FRAME_FWD     	  1
#define NORMAL_FWD           	  2
#define FAST_FWD             	  3
#define SINGLE_FRAME_REWIND  	  4
#define NORMAL_REWIND     	 	  5
#define FAST_REWIND       	 	  6
#define PAUSE             	 	  8
#define SLOW_FWD             	  9
#define SLOW_REWIND          	  10
#define REWIND               	  11
#define GOTO_END             	  12
#define CURRENT_FRAME             13

// Level of change.  Changes have to be inclusive of all the lesser changes.
// Delete cache
#define CHANGE_ALL            0xffffffff
// Delete render engines
#define CHANGE_EDL                  0x11
// Search EDL and synchronize parameters.
#define CHANGE_PARAMS                0x1
#define CHANGE_NONE                  0x0

class TransportCommand;
class TransportQue;

#endif
