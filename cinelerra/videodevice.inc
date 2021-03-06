#ifndef VIDEODEVICE_INC
#define VIDEODEVICE_INC

class VideoDevice;

// Flags for mainwindow->preferences->vconfig_in->driver
#define VIDEO4LINUX          0
#define VIDEO4LINUX2         1
#define VIDEO4LINUX2JPEG     2
#define SCREENCAPTURE        3
#define CAPTURE_LML          4
#define CAPTURE_FIREWIRE     5
#define CAPTURE_BUZ          6
#define CAPTURE_IEC61883     7
#define CAPTURE_DVB          8

#define VIDEO4LINUX_TITLE      "Video4Linux"
#define VIDEO4LINUX2_TITLE     "Video4Linux2"
#define VIDEO4LINUX2JPEG_TITLE "Video4Linux2 JPEG"
#define SCREENCAPTURE_TITLE    "Screencapture"
#define CAPTURE_LML_TITLE      "LML 33"
#define CAPTURE_BUZ_TITLE      "Buz"
#ifdef HAVE_FIREWIRE
#define CAPTURE_FIREWIRE_TITLE "DV 1394"
#define CAPTURE_IEC61883_TITLE "IEC 61883"
#endif
#define CAPTURE_DVB_TITLE      "DVB"

#define PLAYBACK_X11 	  10
#define PLAYBACK_X11_XV   14
#define PLAYBACK_X11_GL   17
#define PLAYBACK_BUZ 	  11
#define PLAYBACK_LML 	  12
#define PLAYBACK_FIREWIRE 13
#define PLAYBACK_DV1394   15
#define PLAYBACK_IEC61883   16
// This is passed to File::get_best_colormodel by FileThread so FileThread can
// do the colorspace conversion using the shortest path.
#define PLAYBACK_ASYNCHRONOUS 18

#define PLAYBACK_X11_TITLE  	"X11"
#define PLAYBACK_X11_XV_TITLE   "X11-XV"
#define PLAYBACK_X11_GL_TITLE   "X11-OpenGL"
#define PLAYBACK_BUZ_TITLE  	"Buz"
#define PLAYBACK_LML_TITLE  	"LML 33"
#ifdef HAVE_FIREWIRE
#define PLAYBACK_FIREWIRE_TITLE "RAW 1394"
#define PLAYBACK_DV1394_TITLE   "DV 1394"
#define PLAYBACK_IEC61883_TITLE "IEC 61883"
#endif

// Output formats required for direct frame copy
// RGB is for either RGB or RGBA as defined in the VFrame
#define OUTPUT_RGB  0
#define OUTPUT_MJPA 1
#define OUTPUT_DV   2

#endif
