plugin_LTLIBRARIES = reverb.la
reverb_la_LDFLAGS = -avoid-version -module -shared 
reverb_la_LIBADD = 
reverb_la_SOURCES = reverb.C reverbwindow.C 
AM_CXXFLAGS = $(LARGEFILE_CFLAGS)

INCLUDES = -I$(top_srcdir)/guicast -I$(top_srcdir)/cinelerra -I$(top_srcdir)/quicktime
LIBTOOL = $(SHELL) $(top_builddir)/libtool $(LTCXX_FLAGS)

noinst_HEADERS = picon_png.h reverb.h reverb.inc reverbwindow.h reverbwindow.inc
EXTRA_DIST = picon.png
