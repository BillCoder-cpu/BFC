#
#FreeBSDMakefile
#
#ThisisthegccMakefileforBFCOS
#
#
#
#LIBINSTALL=/usr/local/lib
#
# Generated via Programmer, a programmer's utility.
#
DebugDir=Debug
ReleaseDir=Release

ALL_H = CBfcOS_Application.h CBfcOS_Application_Fox.h CBfcOS_Application_WxWidgets.h CBfcOS_FileDialog.h  \
		CBfcOS_FileOperation.h CBfcOS_FileSelector.h CBfcOS_Object.h CBfcOS_Registry.h  \
		CBfcOS_Static.h  

ALL_CPP = src/CBfcOS_Application.cpp src/CBfcOS_Application_Fox.cpp src/CBfcOS_Application_WxWidgets.cpp src/CBfcOS_FileDialog.cpp  \
		src/CBfcOS_FileOperation.cpp src/CBfcOS_FileSelector.cpp src/CBfcOS_Registry.cpp src/CBfcOS_Static.cpp  

ALL_OBJ = src/CBfcOS_Application.o src/CBfcOS_Application_Fox.o src/CBfcOS_Application_WxWidgets.o src/CBfcOS_FileDialog.o  \
		src/CBfcOS_FileOperation.o src/CBfcOS_FileSelector.o src/CBfcOS_Registry.o src/CBfcOS_Static.o  

ALL_DEBUG_OBJ = $(DebugDir)/CBfcOS_Application.o $(DebugDir)/CBfcOS_Application_Fox.o $(DebugDir)/CBfcOS_Application_WxWidgets.o $(DebugDir)/CBfcOS_FileDialog.o  \
		$(DebugDir)/CBfcOS_FileOperation.o $(DebugDir)/CBfcOS_FileSelector.o $(DebugDir)/CBfcOS_Registry.o $(DebugDir)/CBfcOS_Static.o  

ALL_RELEASE_OBJ = $(ReleaseDir)/CBfcOS_Application.o $(ReleaseDir)/CBfcOS_Application_Fox.o $(ReleaseDir)/CBfcOS_Application_WxWidgets.o $(ReleaseDir)/CBfcOS_FileDialog.o  \
		$(ReleaseDir)/CBfcOS_FileOperation.o $(ReleaseDir)/CBfcOS_FileSelector.o $(ReleaseDir)/CBfcOS_Registry.o $(ReleaseDir)/CBfcOS_Static.o  

VER=1
LIBINSTALL=/lib
LIBOUT = $(HOME)/Libraries/Unix
FOXDIR=/usr/include/fox-1.6
srcdir=src
includes=-I$(srcdir) -I../include  -I$(FOXDIR)
WINDEFS = -D _WIN32
LINUXDEFS = -D UNIX
ifeq ($(OS),Windows_NT)
	DEFS=$(WINDEFS)
else
	DEFS=$(LINUXDEFS)
endif
LIBS = $(LIBOUT)/BFC.so

CCPP = gcc
CPPDEBUG = -g -D _DEBUG
INTELOPTIONS=-march=pentium3 -msse -mfpmath=sse
CPPFLAGS = $(CDEBUG) $(includes) -fPIC $(DEFS)

LINKER = ld
LINKEROPTIONS = -r


build : create debug

all : create check_headers debug release

# CXXLINK = $(LIBTOOL) --mode=link $(CXXLD) $(AM_CXXFLAGS) $(CXXFLAGS) $(LDFLAGS) -o $@

backup:
	programmer -b .

create:
	mkdir -p Debug
	mkdir -p Release
	programmer -mp $(srcdir)

debug : $(ALL_DEBUG_OBJ)
	$(CCPP) -shared -o $(LIBOUT)/BFCOS_d.so.$(VER) $(ALL_DEBUG_OBJ)
	$(LINKER) $(LINKEROPTIONS) -o $(LIBOUT)/BFCOS_d.lib $(ALL_DEBUG_OBJ)
# 	$(CXXLINK) -rpath $(libdir) $(libFOX_1_4_la_LDFLAGS) $(libFOX_1_4_la_OBJECTS) $(libFOX_1_4_la_LIBADD) $(LIBS)

release : $(ALL_RELEASE_OBJ)
	$(CCPP) -shared -o $(LIBOUT)/BFCOS.so.$(VER) $(ALL_RELEASE_OBJ)
	$(LINKER) $(LINKEROPTIONS) -o $(LIBOUT)/BFCOS.lib $(ALL_RELEASE_OBJ)

install : installd release
	cp $(LIBOUT)/BFCOS.so.$(VER) $(LIBINSTALL)
	rm -f $(LIBINSTALL)/BFCOS.so
	link $(LIBINSTALL)/BFCOS.so.$(VER) $(LIBINSTALL)/BFCOS.so

installd: debug
	cp $(LIBOUT)/BFCOS_d.so.$(VER) $(LIBINSTALL)
	rm -f $(LIBINSTALL)/BFCOS_d.so
	link $(LIBINSTALL)/BFCOS_d.so.$(VER) $(LIBINSTALL)/BFCOS_d.so

uninstall:
	rm -f $(LIBINSTALL)/BFCOS.so
	rm -f $(LIBINSTALL)/BFCOS.so.$(VER)
	rm -f $(LIBINSTALL)/BFCOS_d.so
	rm -f $(LIBINSTALL)/BFCOS_d.so.$(VER)

clean:
	rm -f Debug/*.*
	rm -f Release/*.*
	rm -f $(LIBOUT)/BFCOS.so.$(VER)
	rm -f $(LIBOUT)/BFCOS_d.so.$(VER)

check_headers : $(ALL_H)
	$(CCPP) -E $(CPPFLAGS) ../include/BFCOS.h > junk





$(DebugDir)/CBfcOS_Application.o : src/CBfcOS_Application.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o $(DebugDir)/CBfcOS_Application.o src/CBfcOS_Application.cpp

$(ReleaseDir)/CBfcOS_Application.o : src/CBfcOS_Application.cpp 
		$(CCPP) -c $(CPPFLAGS) -o $(ReleaseDir)/CBfcOS_Application.o src/CBfcOS_Application.cpp

$(DebugDir)/CBfcOS_Application_Fox.o : src/CBfcOS_Application_Fox.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o $(DebugDir)/CBfcOS_Application_Fox.o src/CBfcOS_Application_Fox.cpp

$(ReleaseDir)/CBfcOS_Application_Fox.o : src/CBfcOS_Application_Fox.cpp 
		$(CCPP) -c $(CPPFLAGS) -o $(ReleaseDir)/CBfcOS_Application_Fox.o src/CBfcOS_Application_Fox.cpp

$(DebugDir)/CBfcOS_Application_WxWidgets.o : src/CBfcOS_Application_WxWidgets.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o $(DebugDir)/CBfcOS_Application_WxWidgets.o src/CBfcOS_Application_WxWidgets.cpp

$(ReleaseDir)/CBfcOS_Application_WxWidgets.o : src/CBfcOS_Application_WxWidgets.cpp 
		$(CCPP) -c $(CPPFLAGS) -o $(ReleaseDir)/CBfcOS_Application_WxWidgets.o src/CBfcOS_Application_WxWidgets.cpp

$(DebugDir)/CBfcOS_FileDialog.o : src/CBfcOS_FileDialog.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o $(DebugDir)/CBfcOS_FileDialog.o src/CBfcOS_FileDialog.cpp

$(ReleaseDir)/CBfcOS_FileDialog.o : src/CBfcOS_FileDialog.cpp 
		$(CCPP) -c $(CPPFLAGS) -o $(ReleaseDir)/CBfcOS_FileDialog.o src/CBfcOS_FileDialog.cpp

$(DebugDir)/CBfcOS_FileOperation.o : src/CBfcOS_FileOperation.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o $(DebugDir)/CBfcOS_FileOperation.o src/CBfcOS_FileOperation.cpp

$(ReleaseDir)/CBfcOS_FileOperation.o : src/CBfcOS_FileOperation.cpp 
		$(CCPP) -c $(CPPFLAGS) -o $(ReleaseDir)/CBfcOS_FileOperation.o src/CBfcOS_FileOperation.cpp

$(DebugDir)/CBfcOS_FileSelector.o : src/CBfcOS_FileSelector.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o $(DebugDir)/CBfcOS_FileSelector.o src/CBfcOS_FileSelector.cpp

$(ReleaseDir)/CBfcOS_FileSelector.o : src/CBfcOS_FileSelector.cpp 
		$(CCPP) -c $(CPPFLAGS) -o $(ReleaseDir)/CBfcOS_FileSelector.o src/CBfcOS_FileSelector.cpp

$(DebugDir)/CBfcOS_Registry.o : src/CBfcOS_Registry.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o $(DebugDir)/CBfcOS_Registry.o src/CBfcOS_Registry.cpp

$(ReleaseDir)/CBfcOS_Registry.o : src/CBfcOS_Registry.cpp 
		$(CCPP) -c $(CPPFLAGS) -o $(ReleaseDir)/CBfcOS_Registry.o src/CBfcOS_Registry.cpp

$(DebugDir)/CBfcOS_Static.o : src/CBfcOS_Static.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o $(DebugDir)/CBfcOS_Static.o src/CBfcOS_Static.cpp

$(ReleaseDir)/CBfcOS_Static.o : src/CBfcOS_Static.cpp 
		$(CCPP) -c $(CPPFLAGS) -o $(ReleaseDir)/CBfcOS_Static.o src/CBfcOS_Static.cpp
