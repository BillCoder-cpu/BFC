#
# FreeBSD Makefile
#
#  This is the Makefile for the BFC Skeletal samples
#
#
#

srcdir=.
FOXDIR=../../../../../Develop_Posix/Fox/fox-current
includes=-I$(srcdir) -I../include -I$(FOXDIR)
DEFS = -D UNIX

CCPP = c++
CDEBUG = -g -D _DEBUG
CPPFLAGS = $(CDEBUG) $(includes) -fPIC $(DEFS)

LINKER = ld
LINKEROPTIONS = --export-dynamic

.cc.o:
	$(CCPP) -c $(CPPFLAGS) $<

all: CBfc_Skeletal_GUI_AppWindow

CBfc_Skeletal_GUI_AppWindow.o : CBfc_Skeletal_GUI_AppWindow.cc
	$(CCPP) -c $(CPPFLAGS) -I/home/bill/Develop_Posix CBfc_Skeletal_GUI_AppWindow.cc


SHELL = /bin/sh
CXXLD=c++
LDFLAGS=
AM_CXXFLAGS=
CXXFLAGS =  -DHAVE_XSHM -DHAVE_ZLIB_H=1 -DHAVE_BZ2LIB_H=1 -Wall -W
LIBTOOL = $(SHELL) $(FOXDIR)/libtool
CXXLINK = $(LIBTOOL) --mode=link $(CXXLD) $(AM_CXXFLAGS) $(CXXFLAGS) $(LDFLAGS) -o $@

LIBS =  -lz -lbz2 -lm
LDADD = $(FOXDIR)/src/libFOX-1.1.la -lm

CBfc_Skeletal_GUI_AppWindow: CBfc_Skeletal_GUI_AppWindow.o $(FOXDIR)/src/libFOX-1.1.la
	@rm -f CBfc_Skeletal_GUI_AppWindow
	g++ CBfc_Skeletal_GUI_AppWindow.o  $(LDADD) $(LIBS) -lc
#	$(CXXLINK) $(LDFLAGS) CFoxBFCWindow.o $(LDADD) $(LIBS)








