#
#FreeBSDMakefile
#
#ThisistheMakefileforBFCGUI
#
#Copyright(C)2004-2008byWilliamP.Foster,allrightsreserved
#
#
#
# Generated via Programmer, a programmer's utility.
#
DebugDir=Debug
ReleaseDir=Release

ALL_H = CBfcGUI.h CBfcGUI_Brush.h CBfcGUI_CursesWindow.h CBfcGUI_DialogWindow.h  \
		CBfcGUI_EditInterface.h CBfcGUI_FoxLayer.h CBfcGUI_GLWindow.h CBfcGUI_ListControl.h  \
		CBfcGUI_MenuWindow.h CBfcGUI_Message.h CBfcGUI_MessageBox.h CBfcGUI_Object.h  \
		CBfcGUI_QuickGUILayer.h CBfcGUI_Resource.h CBfcGUI_ResourceEntity.h CBfcGUI_ResourceStore.h  \
		CBfcGUI_ScriptResource.h CBfcGUI_TerminalWindow.h CBfcGUI_Toolbar.h CBfcGUI_TreeControl.h  \
		CBfcGUI_Window.h CBfcGUI_WxLayer.h CFoxBFCWindow.h CQuickGUIBFCWindow.h  \
		CWxBFCWindow.h ImageWindow.h ProgressControl.h  

ALL_CPP = src/CBfcGUI.cpp src/CBfcGUI_Brush.cpp src/CBfcGUI_CursesWindow.cpp src/CBfcGUI_DialogWindow.cpp  \
		src/CBfcGUI_EditInterface.cpp src/CBfcGUI_FoxLayer.cpp src/CBfcGUI_ListControl.cpp src/CBfcGUI_MenuWindow.cpp  \
		src/CBfcGUI_MessageBox.cpp src/CBfcGUI_QuickGUILayer.cpp src/CBfcGUI_Resource.cpp src/CBfcGUI_ResourceEntity.cpp  \
		src/CBfcGUI_ResourceStore.cpp src/CBfcGUI_ScriptResource.cpp src/CBfcGUI_TerminalWindow.cpp src/CBfcGUI_Toolbar.cpp  \
		src/CBfcGUI_Window.cpp src/CBfcGUI_WxLayer.cpp src/CFoxBFCWindow.cpp src/CQuickGUIBFCWindow.cpp  \
		src/CWxBFCWindow.cpp src/ImageWindow.cpp src/ProgressControl.cpp src/ResourceWindow.cpp  

ALL_OBJ = src/CBfcGUI.o src/CBfcGUI_Brush.o src/CBfcGUI_CursesWindow.o src/CBfcGUI_DialogWindow.o  \
		src/CBfcGUI_EditInterface.o src/CBfcGUI_FoxLayer.o src/CBfcGUI_ListControl.o src/CBfcGUI_MenuWindow.o  \
		src/CBfcGUI_MessageBox.o src/CBfcGUI_QuickGUILayer.o src/CBfcGUI_Resource.o src/CBfcGUI_ResourceEntity.o  \
		src/CBfcGUI_ResourceStore.o src/CBfcGUI_ScriptResource.o src/CBfcGUI_TerminalWindow.o src/CBfcGUI_Toolbar.o  \
		src/CBfcGUI_Window.o src/CBfcGUI_WxLayer.o src/CFoxBFCWindow.o src/CQuickGUIBFCWindow.o  \
		src/CWxBFCWindow.o src/ImageWindow.o src/ProgressControl.o src/ResourceWindow.o  

ALL_DEBUG_OBJ = $(DebugDir)/CBfcGUI.o $(DebugDir)/CBfcGUI_Brush.o $(DebugDir)/CBfcGUI_CursesWindow.o $(DebugDir)/CBfcGUI_DialogWindow.o  \
		$(DebugDir)/CBfcGUI_EditInterface.o $(DebugDir)/CBfcGUI_FoxLayer.o $(DebugDir)/CBfcGUI_ListControl.o $(DebugDir)/CBfcGUI_MenuWindow.o  \
		$(DebugDir)/CBfcGUI_MessageBox.o $(DebugDir)/CBfcGUI_QuickGUILayer.o $(DebugDir)/CBfcGUI_Resource.o $(DebugDir)/CBfcGUI_ResourceEntity.o  \
		$(DebugDir)/CBfcGUI_ResourceStore.o $(DebugDir)/CBfcGUI_ScriptResource.o $(DebugDir)/CBfcGUI_TerminalWindow.o $(DebugDir)/CBfcGUI_Toolbar.o  \
		$(DebugDir)/CBfcGUI_Window.o $(DebugDir)/CBfcGUI_WxLayer.o $(DebugDir)/CFoxBFCWindow.o $(DebugDir)/CQuickGUIBFCWindow.o  \
		$(DebugDir)/CWxBFCWindow.o $(DebugDir)/ImageWindow.o $(DebugDir)/ProgressControl.o $(DebugDir)/ResourceWindow.o  

ALL_RELEASE_OBJ = $(ReleaseDir)/CBfcGUI.o $(ReleaseDir)/CBfcGUI_Brush.o $(ReleaseDir)/CBfcGUI_CursesWindow.o $(ReleaseDir)/CBfcGUI_DialogWindow.o  \
		$(ReleaseDir)/CBfcGUI_EditInterface.o $(ReleaseDir)/CBfcGUI_FoxLayer.o $(ReleaseDir)/CBfcGUI_ListControl.o $(ReleaseDir)/CBfcGUI_MenuWindow.o  \
		$(ReleaseDir)/CBfcGUI_MessageBox.o $(ReleaseDir)/CBfcGUI_QuickGUILayer.o $(ReleaseDir)/CBfcGUI_Resource.o $(ReleaseDir)/CBfcGUI_ResourceEntity.o  \
		$(ReleaseDir)/CBfcGUI_ResourceStore.o $(ReleaseDir)/CBfcGUI_ScriptResource.o $(ReleaseDir)/CBfcGUI_TerminalWindow.o $(ReleaseDir)/CBfcGUI_Toolbar.o  \
		$(ReleaseDir)/CBfcGUI_Window.o $(ReleaseDir)/CBfcGUI_WxLayer.o $(ReleaseDir)/CFoxBFCWindow.o $(ReleaseDir)/CQuickGUIBFCWindow.o  \
		$(ReleaseDir)/CWxBFCWindow.o $(ReleaseDir)/ImageWindow.o $(ReleaseDir)/ProgressControl.o $(ReleaseDir)/ResourceWindow.o  

VER=1
srcdir=src
LIBINSTALL=/lib

LIBOUT = $(HOME)/Libraries/Unix
FOXDIR=/usr/include/fox-1.6
# QUICKGUIDIR=../../../../../Exile/QuickGUI/QuickGUI/include
includes=-I$(srcdir) -I../include -I$(FOXDIR)

WINDEFS = -D _WIN32
LINUXDEFS = -D UNIX
ifeq ($(OS),Windows_NT)
	DEFS=$(WINDEFS)
else
	DEFS=$(LINUXDEFS)
endif

LIBS = $(LIBOUT)/BFCGUI.so

CCPP = g++
CPPDEBUG = -g -D _DEBUG
INTELOPTIONS=-march=pentium3 -msse -mfpmath=sse
CPPFLAGS = $(includes) -fPIC $(DEFS) -fpermissive

LINKER = ld
LINKEROPTIONS = -r

all: create debug release

backup:
	programmer -b .

create:
	mkdir -p Debug
	mkdir -p Release
	programmer -mp $(srcdir)

clean:
	rm -f Debug/*.o
	rm -f Release/*.o
	rm -f $(LIBOUT)/BFCGUI_d.so.1
	rm -f $(LIBOUT)/BFCGUI_d.so.1

BFCGUI : $(ALL_OBJ)
	g++ -shared -o $(LIBOUT)/BFCGUI.so.1 $(ALL_OBJ)

debug: $(ALL_DEBUG_OBJ)
	g++ -shared -o $(LIBOUT)/BFCGUI_d.so.$(VER) $(ALL_DEBUG_OBJ)
	$(LINKER) $(LINKEROPTIONS) -o $(LIBOUT)/BFCGUI_d.lib $(ALL_DEBUG_OBJ)

release: $(ALL_RELEASE_OBJ)
	g++ -shared -o $(LIBOUT)/BFCGUI.so.$(VER) $(ALL_RELEASE_OBJ)
	$(LINKER) $(LINKEROPTIONS) -o $(LIBOUT)/BFCGUI.lib $(ALL_RELEASE_OBJ)

install: installd release
	cp $(LIBOUT)/BFCGUI.so.$(VER) $(LIBINSTALL)
	rm -f $(LIBINSTALL)/BFCGUI.so
	link $(LIBINSTALL)/BFCGUI.so.$(VER) $(LIBINSTALL)/BFCGUI.so

installd: debug
	cp $(LIBOUT)/BFCGUI_d.so.$(VER) $(LIBINSTALL)
	rm -f $(LIBINSTALL)/BFCGUI_d.so
	link $(LIBINSTALL)/BFCGUI_d.so.$(VER) $(LIBINSTALL)/BFCGUI_d.so

uninstall:
	rm -f $(LIBINSTALL)/BFCGUI_d.so
	rm -f $(LIBINSTALL)/BFCGUI_d.so.$(VER)
	rm -f $(LIBINSTALL)/BFCGUI.so
	rm -f $(LIBINSTALL)/BFCGUI.so.$(VER)




$(DebugDir)/CBfcGUI.o : src/CBfcGUI.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o $(DebugDir)/CBfcGUI.o src/CBfcGUI.cpp

$(ReleaseDir)/CBfcGUI.o : src/CBfcGUI.cpp 
		$(CCPP) -c $(CPPFLAGS) -o $(ReleaseDir)/CBfcGUI.o src/CBfcGUI.cpp

$(DebugDir)/CBfcGUI_Brush.o : src/CBfcGUI_Brush.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o $(DebugDir)/CBfcGUI_Brush.o src/CBfcGUI_Brush.cpp

$(ReleaseDir)/CBfcGUI_Brush.o : src/CBfcGUI_Brush.cpp 
		$(CCPP) -c $(CPPFLAGS) -o $(ReleaseDir)/CBfcGUI_Brush.o src/CBfcGUI_Brush.cpp

$(DebugDir)/CBfcGUI_CursesWindow.o : src/CBfcGUI_CursesWindow.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o $(DebugDir)/CBfcGUI_CursesWindow.o src/CBfcGUI_CursesWindow.cpp

$(ReleaseDir)/CBfcGUI_CursesWindow.o : src/CBfcGUI_CursesWindow.cpp 
		$(CCPP) -c $(CPPFLAGS) -o $(ReleaseDir)/CBfcGUI_CursesWindow.o src/CBfcGUI_CursesWindow.cpp

$(DebugDir)/CBfcGUI_DialogWindow.o : src/CBfcGUI_DialogWindow.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o $(DebugDir)/CBfcGUI_DialogWindow.o src/CBfcGUI_DialogWindow.cpp

$(ReleaseDir)/CBfcGUI_DialogWindow.o : src/CBfcGUI_DialogWindow.cpp 
		$(CCPP) -c $(CPPFLAGS) -o $(ReleaseDir)/CBfcGUI_DialogWindow.o src/CBfcGUI_DialogWindow.cpp

$(DebugDir)/CBfcGUI_EditInterface.o : src/CBfcGUI_EditInterface.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o $(DebugDir)/CBfcGUI_EditInterface.o src/CBfcGUI_EditInterface.cpp

$(ReleaseDir)/CBfcGUI_EditInterface.o : src/CBfcGUI_EditInterface.cpp 
		$(CCPP) -c $(CPPFLAGS) -o $(ReleaseDir)/CBfcGUI_EditInterface.o src/CBfcGUI_EditInterface.cpp

$(DebugDir)/CBfcGUI_FoxLayer.o : src/CBfcGUI_FoxLayer.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o $(DebugDir)/CBfcGUI_FoxLayer.o src/CBfcGUI_FoxLayer.cpp

$(ReleaseDir)/CBfcGUI_FoxLayer.o : src/CBfcGUI_FoxLayer.cpp 
		$(CCPP) -c $(CPPFLAGS) -o $(ReleaseDir)/CBfcGUI_FoxLayer.o src/CBfcGUI_FoxLayer.cpp

$(DebugDir)/CBfcGUI_ListControl.o : src/CBfcGUI_ListControl.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o $(DebugDir)/CBfcGUI_ListControl.o src/CBfcGUI_ListControl.cpp

$(ReleaseDir)/CBfcGUI_ListControl.o : src/CBfcGUI_ListControl.cpp 
		$(CCPP) -c $(CPPFLAGS) -o $(ReleaseDir)/CBfcGUI_ListControl.o src/CBfcGUI_ListControl.cpp

$(DebugDir)/CBfcGUI_MenuWindow.o : src/CBfcGUI_MenuWindow.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o $(DebugDir)/CBfcGUI_MenuWindow.o src/CBfcGUI_MenuWindow.cpp

$(ReleaseDir)/CBfcGUI_MenuWindow.o : src/CBfcGUI_MenuWindow.cpp 
		$(CCPP) -c $(CPPFLAGS) -o $(ReleaseDir)/CBfcGUI_MenuWindow.o src/CBfcGUI_MenuWindow.cpp

$(DebugDir)/CBfcGUI_MessageBox.o : src/CBfcGUI_MessageBox.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o $(DebugDir)/CBfcGUI_MessageBox.o src/CBfcGUI_MessageBox.cpp

$(ReleaseDir)/CBfcGUI_MessageBox.o : src/CBfcGUI_MessageBox.cpp 
		$(CCPP) -c $(CPPFLAGS) -o $(ReleaseDir)/CBfcGUI_MessageBox.o src/CBfcGUI_MessageBox.cpp

$(DebugDir)/CBfcGUI_QuickGUILayer.o : src/CBfcGUI_QuickGUILayer.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o $(DebugDir)/CBfcGUI_QuickGUILayer.o src/CBfcGUI_QuickGUILayer.cpp

$(ReleaseDir)/CBfcGUI_QuickGUILayer.o : src/CBfcGUI_QuickGUILayer.cpp 
		$(CCPP) -c $(CPPFLAGS) -o $(ReleaseDir)/CBfcGUI_QuickGUILayer.o src/CBfcGUI_QuickGUILayer.cpp

$(DebugDir)/CBfcGUI_Resource.o : src/CBfcGUI_Resource.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o $(DebugDir)/CBfcGUI_Resource.o src/CBfcGUI_Resource.cpp

$(ReleaseDir)/CBfcGUI_Resource.o : src/CBfcGUI_Resource.cpp 
		$(CCPP) -c $(CPPFLAGS) -o $(ReleaseDir)/CBfcGUI_Resource.o src/CBfcGUI_Resource.cpp

$(DebugDir)/CBfcGUI_ResourceEntity.o : src/CBfcGUI_ResourceEntity.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o $(DebugDir)/CBfcGUI_ResourceEntity.o src/CBfcGUI_ResourceEntity.cpp

$(ReleaseDir)/CBfcGUI_ResourceEntity.o : src/CBfcGUI_ResourceEntity.cpp 
		$(CCPP) -c $(CPPFLAGS) -o $(ReleaseDir)/CBfcGUI_ResourceEntity.o src/CBfcGUI_ResourceEntity.cpp

$(DebugDir)/CBfcGUI_ResourceStore.o : src/CBfcGUI_ResourceStore.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o $(DebugDir)/CBfcGUI_ResourceStore.o src/CBfcGUI_ResourceStore.cpp

$(ReleaseDir)/CBfcGUI_ResourceStore.o : src/CBfcGUI_ResourceStore.cpp 
		$(CCPP) -c $(CPPFLAGS) -o $(ReleaseDir)/CBfcGUI_ResourceStore.o src/CBfcGUI_ResourceStore.cpp

$(DebugDir)/CBfcGUI_ScriptResource.o : src/CBfcGUI_ScriptResource.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o $(DebugDir)/CBfcGUI_ScriptResource.o src/CBfcGUI_ScriptResource.cpp

$(ReleaseDir)/CBfcGUI_ScriptResource.o : src/CBfcGUI_ScriptResource.cpp 
		$(CCPP) -c $(CPPFLAGS) -o $(ReleaseDir)/CBfcGUI_ScriptResource.o src/CBfcGUI_ScriptResource.cpp

$(DebugDir)/CBfcGUI_TerminalWindow.o : src/CBfcGUI_TerminalWindow.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o $(DebugDir)/CBfcGUI_TerminalWindow.o src/CBfcGUI_TerminalWindow.cpp

$(ReleaseDir)/CBfcGUI_TerminalWindow.o : src/CBfcGUI_TerminalWindow.cpp 
		$(CCPP) -c $(CPPFLAGS) -o $(ReleaseDir)/CBfcGUI_TerminalWindow.o src/CBfcGUI_TerminalWindow.cpp

$(DebugDir)/CBfcGUI_Toolbar.o : src/CBfcGUI_Toolbar.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o $(DebugDir)/CBfcGUI_Toolbar.o src/CBfcGUI_Toolbar.cpp

$(ReleaseDir)/CBfcGUI_Toolbar.o : src/CBfcGUI_Toolbar.cpp 
		$(CCPP) -c $(CPPFLAGS) -o $(ReleaseDir)/CBfcGUI_Toolbar.o src/CBfcGUI_Toolbar.cpp

$(DebugDir)/CBfcGUI_Window.o : src/CBfcGUI_Window.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o $(DebugDir)/CBfcGUI_Window.o src/CBfcGUI_Window.cpp

$(ReleaseDir)/CBfcGUI_Window.o : src/CBfcGUI_Window.cpp 
		$(CCPP) -c $(CPPFLAGS) -o $(ReleaseDir)/CBfcGUI_Window.o src/CBfcGUI_Window.cpp

$(DebugDir)/CBfcGUI_WxLayer.o : src/CBfcGUI_WxLayer.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o $(DebugDir)/CBfcGUI_WxLayer.o src/CBfcGUI_WxLayer.cpp

$(ReleaseDir)/CBfcGUI_WxLayer.o : src/CBfcGUI_WxLayer.cpp 
		$(CCPP) -c $(CPPFLAGS) -o $(ReleaseDir)/CBfcGUI_WxLayer.o src/CBfcGUI_WxLayer.cpp

$(DebugDir)/CFoxBFCWindow.o : src/CFoxBFCWindow.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o $(DebugDir)/CFoxBFCWindow.o src/CFoxBFCWindow.cpp

$(ReleaseDir)/CFoxBFCWindow.o : src/CFoxBFCWindow.cpp 
		$(CCPP) -c $(CPPFLAGS) -o $(ReleaseDir)/CFoxBFCWindow.o src/CFoxBFCWindow.cpp

$(DebugDir)/CQuickGUIBFCWindow.o : src/CQuickGUIBFCWindow.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o $(DebugDir)/CQuickGUIBFCWindow.o src/CQuickGUIBFCWindow.cpp

$(ReleaseDir)/CQuickGUIBFCWindow.o : src/CQuickGUIBFCWindow.cpp 
		$(CCPP) -c $(CPPFLAGS) -o $(ReleaseDir)/CQuickGUIBFCWindow.o src/CQuickGUIBFCWindow.cpp

$(DebugDir)/CWxBFCWindow.o : src/CWxBFCWindow.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o $(DebugDir)/CWxBFCWindow.o src/CWxBFCWindow.cpp

$(ReleaseDir)/CWxBFCWindow.o : src/CWxBFCWindow.cpp 
		$(CCPP) -c $(CPPFLAGS) -o $(ReleaseDir)/CWxBFCWindow.o src/CWxBFCWindow.cpp

$(DebugDir)/ImageWindow.o : src/ImageWindow.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o $(DebugDir)/ImageWindow.o src/ImageWindow.cpp

$(ReleaseDir)/ImageWindow.o : src/ImageWindow.cpp 
		$(CCPP) -c $(CPPFLAGS) -o $(ReleaseDir)/ImageWindow.o src/ImageWindow.cpp

$(DebugDir)/ProgressControl.o : src/ProgressControl.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o $(DebugDir)/ProgressControl.o src/ProgressControl.cpp

$(ReleaseDir)/ProgressControl.o : src/ProgressControl.cpp 
		$(CCPP) -c $(CPPFLAGS) -o $(ReleaseDir)/ProgressControl.o src/ProgressControl.cpp

$(DebugDir)/ResourceWindow.o : src/ResourceWindow.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o $(DebugDir)/ResourceWindow.o src/ResourceWindow.cpp

$(ReleaseDir)/ResourceWindow.o : src/ResourceWindow.cpp 
		$(CCPP) -c $(CPPFLAGS) -o $(ReleaseDir)/ResourceWindow.o src/ResourceWindow.cpp
