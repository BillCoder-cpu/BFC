#
#FreeBSDMakefile
#
#ThisistheWindowsMakefile(Base)forBFCOS
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

ALL_CPP = ..\src\CBfcOS_Application.cpp ..\src\CBfcOS_Application_Fox.cpp ..\src\CBfcOS_Application_WxWidgets.cpp ..\src\CBfcOS_FileDialog.cpp  \
		..\src\CBfcOS_FileOperation.cpp ..\src\CBfcOS_FileSelector.cpp ..\src\CBfcOS_Registry.cpp ..\src\CBfcOS_Static.cpp  

ALL_OBJ = ..\src\CBfcOS_Application.o ..\src\CBfcOS_Application_Fox.o ..\src\CBfcOS_Application_WxWidgets.o ..\src\CBfcOS_FileDialog.o  \
		..\src\CBfcOS_FileOperation.o ..\src\CBfcOS_FileSelector.o ..\src\CBfcOS_Registry.o ..\src\CBfcOS_Static.o  

ALL_DEBUG_OBJ = $(DebugDir)\CBfcOS_Application.o $(DebugDir)\CBfcOS_Application_Fox.o $(DebugDir)\CBfcOS_Application_WxWidgets.o $(DebugDir)\CBfcOS_FileDialog.o  \
		$(DebugDir)\CBfcOS_FileOperation.o $(DebugDir)\CBfcOS_FileSelector.o $(DebugDir)\CBfcOS_Registry.o $(DebugDir)\CBfcOS_Static.o  

ALL_RELEASE_OBJ = $(ReleaseDir)\CBfcOS_Application.o $(ReleaseDir)\CBfcOS_Application_Fox.o $(ReleaseDir)\CBfcOS_Application_WxWidgets.o $(ReleaseDir)\CBfcOS_FileDialog.o  \
		$(ReleaseDir)\CBfcOS_FileOperation.o $(ReleaseDir)\CBfcOS_FileSelector.o $(ReleaseDir)\CBfcOS_Registry.o $(ReleaseDir)\CBfcOS_Static.o  

SHELL=C:/Windows/System32/cmd.exe
VER=1
LIBINSTALL = \Libraries
LIBOUT=.
FOXDIR=\Sources\C++\Third-Party\fox-current
srcdir=..\src
includes=-I$(srcdir) -I..\..\include  -I$(FOXDIR)/include
DEFS = -D WIN32 -D BFC_STATICLIB
LIBS = $(LIBOUT)/BFC.so

CCPP = cl
CPPDEBUG = -D _DEBUG /Zi
#INTELOPTIONS=-march=pentium3 -msse -mfpmath=sse
CPPFLAGS = $(INTELOPTIONS) $(CDEBUG) $(includes) $(DEFS)

LINKER = lib
#LINKEROPTIONS = -r


build : create debug

all : create check_headers debug release

# CXXLINK = $(LIBTOOL) --mode=link $(CXXLD) $(AM_CXXFLAGS) $(CXXFLAGS) $(LDFLAGS) -o $@

backup:
	programmer -b .

create:
	if NOT EXIST Debug (mkdir Debug)
	if NOT EXIST Release (mkdir Release)
	programmer -mpw $(srcdir)

debug : $(LIBOUT)/BFCOS_d.lib

$(LIBOUT)/BFCOS_d.lib: $(ALL_DEBUG_OBJ)
	$(LINKER) $(LINKEROPTIONS) /OUT:$(LIBOUT)\BFCOS_d.lib $(ALL_DEBUG_OBJ)

release : $(LIBOUT)/BFCOS.lib

$(LIBOUT)/BFCOS.lib : $(ALL_RELEASE_OBJ)
	$(LINKER) $(LINKEROPTIONS) /OUT:$(LIBOUT)\BFCOS.lib $(ALL_RELEASE_OBJ)

install : installd release
	copy $(LIBOUT)\BFCOS.lib $(LIBINSTALL)

installd: debug
	copy $(LIBOUT)\BFCOS_d.lib $(LIBINSTALL)

uninstall:
	del -f $(LIBINSTALL)\BFCOS.lib
	del -f $(LIBINSTALL)\BFCOS_d.lib

clean:
	programmer -c
	del $(LIBOUT)\BFCOS.lib
	del $(LIBOUT)\BFCOS_d.lib


check_headers : $(ALL_H)
	$(CCPP) -E $(CPPFLAGS) ../include/BFCOS.h > junk





$(DebugDir)\CBfcOS_Application.o : ..\src\CBfcOS_Application.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\CBfcOS_Application.o ..\src\CBfcOS_Application.cpp

$(ReleaseDir)\CBfcOS_Application.o : ..\src\CBfcOS_Application.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\CBfcOS_Application.o ..\src\CBfcOS_Application.cpp

$(DebugDir)\CBfcOS_Application_Fox.o : ..\src\CBfcOS_Application_Fox.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\CBfcOS_Application_Fox.o ..\src\CBfcOS_Application_Fox.cpp

$(ReleaseDir)\CBfcOS_Application_Fox.o : ..\src\CBfcOS_Application_Fox.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\CBfcOS_Application_Fox.o ..\src\CBfcOS_Application_Fox.cpp

$(DebugDir)\CBfcOS_Application_WxWidgets.o : ..\src\CBfcOS_Application_WxWidgets.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\CBfcOS_Application_WxWidgets.o ..\src\CBfcOS_Application_WxWidgets.cpp

$(ReleaseDir)\CBfcOS_Application_WxWidgets.o : ..\src\CBfcOS_Application_WxWidgets.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\CBfcOS_Application_WxWidgets.o ..\src\CBfcOS_Application_WxWidgets.cpp

$(DebugDir)\CBfcOS_FileDialog.o : ..\src\CBfcOS_FileDialog.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\CBfcOS_FileDialog.o ..\src\CBfcOS_FileDialog.cpp

$(ReleaseDir)\CBfcOS_FileDialog.o : ..\src\CBfcOS_FileDialog.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\CBfcOS_FileDialog.o ..\src\CBfcOS_FileDialog.cpp

$(DebugDir)\CBfcOS_FileOperation.o : ..\src\CBfcOS_FileOperation.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\CBfcOS_FileOperation.o ..\src\CBfcOS_FileOperation.cpp

$(ReleaseDir)\CBfcOS_FileOperation.o : ..\src\CBfcOS_FileOperation.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\CBfcOS_FileOperation.o ..\src\CBfcOS_FileOperation.cpp

$(DebugDir)\CBfcOS_FileSelector.o : ..\src\CBfcOS_FileSelector.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\CBfcOS_FileSelector.o ..\src\CBfcOS_FileSelector.cpp

$(ReleaseDir)\CBfcOS_FileSelector.o : ..\src\CBfcOS_FileSelector.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\CBfcOS_FileSelector.o ..\src\CBfcOS_FileSelector.cpp

$(DebugDir)\CBfcOS_Registry.o : ..\src\CBfcOS_Registry.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\CBfcOS_Registry.o ..\src\CBfcOS_Registry.cpp

$(ReleaseDir)\CBfcOS_Registry.o : ..\src\CBfcOS_Registry.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\CBfcOS_Registry.o ..\src\CBfcOS_Registry.cpp

$(DebugDir)\CBfcOS_Static.o : ..\src\CBfcOS_Static.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\CBfcOS_Static.o ..\src\CBfcOS_Static.cpp

$(ReleaseDir)\CBfcOS_Static.o : ..\src\CBfcOS_Static.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\CBfcOS_Static.o ..\src\CBfcOS_Static.cpp
