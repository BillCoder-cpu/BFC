#
#WINDOWSMakefile
#
#ThisistheWindowsMakefileforBFCGUI
#
#Copyright(C)2004-2008byWilliamP.Foster,allrightsreserved
#
#
#
# Generated via Programmer, a programmer's utility.
#

ALL_H = CBfcGUI.h CBfcGUI_Brush.h CBfcGUI_CursesWindow.h CBfcGUI_DialogWindow.h  \
		CBfcGUI_EditInterface.h CBfcGUI_FoxLayer.h CBfcGUI_GLWindow.h CBfcGUI_ListControl.h  \
		CBfcGUI_MenuWindow.h CBfcGUI_Message.h CBfcGUI_MessageBox.h CBfcGUI_Object.h  \
		CBfcGUI_QuickGUILayer.h CBfcGUI_Resource.h CBfcGUI_ResourceEntity.h CBfcGUI_ResourceStore.h  \
		CBfcGUI_ScriptResource.h CBfcGUI_TerminalWindow.h CBfcGUI_Toolbar.h CBfcGUI_TreeControl.h  \
		CBfcGUI_Window.h CBfcGUI_WxLayer.h CFoxBFCWindow.h CQuickGUIBFCWindow.h  \
		CWxBFCWindow.h ImageWindow.h ProgressControl.h  

ALL_CPP = ..\src\CBfcGUI.cpp ..\src\CBfcGUI_Brush.cpp ..\src\CBfcGUI_CursesWindow.cpp ..\src\CBfcGUI_DialogWindow.cpp  \
		..\src\CBfcGUI_EditInterface.cpp ..\src\CBfcGUI_FoxLayer.cpp ..\src\CBfcGUI_ListControl.cpp ..\src\CBfcGUI_MenuWindow.cpp  \
		..\src\CBfcGUI_MessageBox.cpp ..\src\CBfcGUI_QuickGUILayer.cpp ..\src\CBfcGUI_Resource.cpp ..\src\CBfcGUI_ResourceEntity.cpp  \
		..\src\CBfcGUI_ResourceStore.cpp ..\src\CBfcGUI_ScriptResource.cpp ..\src\CBfcGUI_TerminalWindow.cpp ..\src\CBfcGUI_Toolbar.cpp  \
		..\src\CBfcGUI_Window.cpp ..\src\CBfcGUI_WxLayer.cpp ..\src\CFoxBFCWindow.cpp ..\src\CQuickGUIBFCWindow.cpp  \
		..\src\CWxBFCWindow.cpp ..\src\ImageWindow.cpp ..\src\ProgressControl.cpp ..\src\ResourceWindow.cpp  

ALL_OBJ = ..\src\CBfcGUI.o ..\src\CBfcGUI_Brush.o ..\src\CBfcGUI_CursesWindow.o ..\src\CBfcGUI_DialogWindow.o  \
		..\src\CBfcGUI_EditInterface.o ..\src\CBfcGUI_FoxLayer.o ..\src\CBfcGUI_ListControl.o ..\src\CBfcGUI_MenuWindow.o  \
		..\src\CBfcGUI_MessageBox.o ..\src\CBfcGUI_QuickGUILayer.o ..\src\CBfcGUI_Resource.o ..\src\CBfcGUI_ResourceEntity.o  \
		..\src\CBfcGUI_ResourceStore.o ..\src\CBfcGUI_ScriptResource.o ..\src\CBfcGUI_TerminalWindow.o ..\src\CBfcGUI_Toolbar.o  \
		..\src\CBfcGUI_Window.o ..\src\CBfcGUI_WxLayer.o ..\src\CFoxBFCWindow.o ..\src\CQuickGUIBFCWindow.o  \
		..\src\CWxBFCWindow.o ..\src\ImageWindow.o ..\src\ProgressControl.o ..\src\ResourceWindow.o  

ALL_DEBUG_OBJ = Debug\CBfcGUI.o Debug\CBfcGUI_Brush.o Debug\CBfcGUI_CursesWindow.o Debug\CBfcGUI_DialogWindow.o  \
		Debug\CBfcGUI_EditInterface.o Debug\CBfcGUI_FoxLayer.o Debug\CBfcGUI_ListControl.o Debug\CBfcGUI_MenuWindow.o  \
		Debug\CBfcGUI_MessageBox.o Debug\CBfcGUI_QuickGUILayer.o Debug\CBfcGUI_Resource.o Debug\CBfcGUI_ResourceEntity.o  \
		Debug\CBfcGUI_ResourceStore.o Debug\CBfcGUI_ScriptResource.o Debug\CBfcGUI_TerminalWindow.o Debug\CBfcGUI_Toolbar.o  \
		Debug\CBfcGUI_Window.o Debug\CBfcGUI_WxLayer.o Debug\CFoxBFCWindow.o Debug\CQuickGUIBFCWindow.o  \
		Debug\CWxBFCWindow.o Debug\ImageWindow.o Debug\ProgressControl.o Debug\ResourceWindow.o  

ALL_RELEASE_OBJ = Release\CBfcGUI.o Release\CBfcGUI_Brush.o Release\CBfcGUI_CursesWindow.o Release\CBfcGUI_DialogWindow.o  \
		Release\CBfcGUI_EditInterface.o Release\CBfcGUI_FoxLayer.o Release\CBfcGUI_ListControl.o Release\CBfcGUI_MenuWindow.o  \
		Release\CBfcGUI_MessageBox.o Release\CBfcGUI_QuickGUILayer.o Release\CBfcGUI_Resource.o Release\CBfcGUI_ResourceEntity.o  \
		Release\CBfcGUI_ResourceStore.o Release\CBfcGUI_ScriptResource.o Release\CBfcGUI_TerminalWindow.o Release\CBfcGUI_Toolbar.o  \
		Release\CBfcGUI_Window.o Release\CBfcGUI_WxLayer.o Release\CFoxBFCWindow.o Release\CQuickGUIBFCWindow.o  \
		Release\CWxBFCWindow.o Release\ImageWindow.o Release\ProgressControl.o Release\ResourceWindow.o  

SHELL=C:/Windows/System32/cmd.exe
VER=1
srcdir=..\src
LIBINSTALL = \Users\Bill\Libraries
LIBOUT=.

SRCDIR=\Users\Bill\Sources
BFCINC=$(SRCDIR)\C++\Engines\BFC\include
BFCDIR=$(SRCDIR)\C++\Engines\BFC
CSDIR=$(SRCDIR)\cs

# FOXDIR=\Users\Bill\Third-Party\fox-current
QUICKGUIDIR=../../../../../Exile/QuickGUI/QuickGUI/include
includes=-I$(srcdir) -I..\..\include -I$(QUICKGUIDIR)
# -I$(FOXDIR)\include
DEFS = -D WIN32 -D STATICLIB
LIBS = $(LIBOUT)\BFCGUI.lib

CCPP = gcc
CPPDEBUG = -g -O0 -D_DEBUG 
#INTELOPTIONS=-march=pentium3 -msse -mfpmath=sse
CPPFLAGS = $(INTELOPTIONS) $(includes) $(DEFS)

LINKER = ar
LINKEROPTIONS = rcs
DLL_LINKER = g++ -shared
DLL_LINKEROPTIONS = -o

DEBUG_NAME=BFCGUI_mingw_d.a
RELEASE_NAME=BFCGUI_mingw.a

DEBUG_NAME_DLL=BFCGUI_mingw_d.dll
RELEASE_NAME_DLL=BFCGUI_mingw.dll

all: create debug release

backup:
	programmer -b .

create:
	if NOT EXIST Debug (mkdir Debug)
	if NOT EXIST Release (mkdir Release)
	programmer -mpg $(srcdir)

clean: uninstall
	programmer -c

debug : $(LIBOUT)/$(DEBUG_NAME) $(LIBOUT)/$(DEBUG_NAME_DLL)

$(LIBOUT)/$(DEBUG_NAME) : $(ALL_DEBUG_OBJ)
	$(LINKER) $(LINKEROPTIONS) $(LIBOUT)/$(DEBUG_NAME) $(ALL_DEBUG_OBJ)

$(LIBOUT)/$(DEBUG_NAME_DLL) : $(ALL_DEBUG_OBJ)
	$(DLL_LINKER) $(DLL_LINKEROPTIONS) $(LIBOUT)/$(DEBUG_NAME_DLL) $(ALL_DEBUG_OBJ)
	
release : $(LIBOUT)/$(RELEASE_NAME) $(LIBOUT)/$(RELEASE_NAME_DLL)

$(LIBOUT)/$(RELEASE_NAME) : $(ALL_RELEASE_OBJ)
	$(LINKER) $(LINKEROPTIONS) $(LIBOUT)/$(RELEASE_NAME) $(ALL_RELEASE_OBJ)

$(LIBOUT)/$(RELEASE_NAME_DLL) : $(ALL_RELEASE_OBJ)
	$(DLL_LINKER) $(DLL_LINKEROPTIONS) $(LIBOUT)/$(RELEASE_NAME_DLL) $(ALL_RELEASE_OBJ)

install: installd release
	copy $(LIBOUT)\$(RELEASE_NAME) $(LIBINSTALL)\$(RELEASE_NAME)
	copy $(LIBOUT)\$(RELEASE_NAME_DLL) $(LIBINSTALL)\$(RELEASE_NAME_DLL)

installd: debug
	copy $(LIBOUT)\$(DEBUG_NAME) $(LIBINSTALL)\$(DEBUG_NAME)
	copy $(LIBOUT)\$(DEBUG_NAME_DLL) $(LIBINSTALL)\$(DEBUG_NAME_DLL)

uninstall:
	del $(LIBINSTALL)\$(DEBUG_NAME)
	del $(LIBINSTALL)\$(RELEASE_NAME)




Debug\CBfcGUI.o : ..\src\CBfcGUI.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfcGUI.o ..\src\CBfcGUI.cpp

Release\CBfcGUI.o : ..\src\CBfcGUI.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfcGUI.o ..\src\CBfcGUI.cpp

Debug\CBfcGUI_Brush.o : ..\src\CBfcGUI_Brush.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfcGUI_Brush.o ..\src\CBfcGUI_Brush.cpp

Release\CBfcGUI_Brush.o : ..\src\CBfcGUI_Brush.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfcGUI_Brush.o ..\src\CBfcGUI_Brush.cpp

Debug\CBfcGUI_CursesWindow.o : ..\src\CBfcGUI_CursesWindow.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfcGUI_CursesWindow.o ..\src\CBfcGUI_CursesWindow.cpp

Release\CBfcGUI_CursesWindow.o : ..\src\CBfcGUI_CursesWindow.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfcGUI_CursesWindow.o ..\src\CBfcGUI_CursesWindow.cpp

Debug\CBfcGUI_DialogWindow.o : ..\src\CBfcGUI_DialogWindow.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfcGUI_DialogWindow.o ..\src\CBfcGUI_DialogWindow.cpp

Release\CBfcGUI_DialogWindow.o : ..\src\CBfcGUI_DialogWindow.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfcGUI_DialogWindow.o ..\src\CBfcGUI_DialogWindow.cpp

Debug\CBfcGUI_EditInterface.o : ..\src\CBfcGUI_EditInterface.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfcGUI_EditInterface.o ..\src\CBfcGUI_EditInterface.cpp

Release\CBfcGUI_EditInterface.o : ..\src\CBfcGUI_EditInterface.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfcGUI_EditInterface.o ..\src\CBfcGUI_EditInterface.cpp

Debug\CBfcGUI_FoxLayer.o : ..\src\CBfcGUI_FoxLayer.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfcGUI_FoxLayer.o ..\src\CBfcGUI_FoxLayer.cpp

Release\CBfcGUI_FoxLayer.o : ..\src\CBfcGUI_FoxLayer.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfcGUI_FoxLayer.o ..\src\CBfcGUI_FoxLayer.cpp

Debug\CBfcGUI_ListControl.o : ..\src\CBfcGUI_ListControl.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfcGUI_ListControl.o ..\src\CBfcGUI_ListControl.cpp

Release\CBfcGUI_ListControl.o : ..\src\CBfcGUI_ListControl.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfcGUI_ListControl.o ..\src\CBfcGUI_ListControl.cpp

Debug\CBfcGUI_MenuWindow.o : ..\src\CBfcGUI_MenuWindow.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfcGUI_MenuWindow.o ..\src\CBfcGUI_MenuWindow.cpp

Release\CBfcGUI_MenuWindow.o : ..\src\CBfcGUI_MenuWindow.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfcGUI_MenuWindow.o ..\src\CBfcGUI_MenuWindow.cpp

Debug\CBfcGUI_MessageBox.o : ..\src\CBfcGUI_MessageBox.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfcGUI_MessageBox.o ..\src\CBfcGUI_MessageBox.cpp

Release\CBfcGUI_MessageBox.o : ..\src\CBfcGUI_MessageBox.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfcGUI_MessageBox.o ..\src\CBfcGUI_MessageBox.cpp

Debug\CBfcGUI_QuickGUILayer.o : ..\src\CBfcGUI_QuickGUILayer.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfcGUI_QuickGUILayer.o ..\src\CBfcGUI_QuickGUILayer.cpp

Release\CBfcGUI_QuickGUILayer.o : ..\src\CBfcGUI_QuickGUILayer.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfcGUI_QuickGUILayer.o ..\src\CBfcGUI_QuickGUILayer.cpp

Debug\CBfcGUI_Resource.o : ..\src\CBfcGUI_Resource.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfcGUI_Resource.o ..\src\CBfcGUI_Resource.cpp

Release\CBfcGUI_Resource.o : ..\src\CBfcGUI_Resource.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfcGUI_Resource.o ..\src\CBfcGUI_Resource.cpp

Debug\CBfcGUI_ResourceEntity.o : ..\src\CBfcGUI_ResourceEntity.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfcGUI_ResourceEntity.o ..\src\CBfcGUI_ResourceEntity.cpp

Release\CBfcGUI_ResourceEntity.o : ..\src\CBfcGUI_ResourceEntity.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfcGUI_ResourceEntity.o ..\src\CBfcGUI_ResourceEntity.cpp

Debug\CBfcGUI_ResourceStore.o : ..\src\CBfcGUI_ResourceStore.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfcGUI_ResourceStore.o ..\src\CBfcGUI_ResourceStore.cpp

Release\CBfcGUI_ResourceStore.o : ..\src\CBfcGUI_ResourceStore.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfcGUI_ResourceStore.o ..\src\CBfcGUI_ResourceStore.cpp

Debug\CBfcGUI_ScriptResource.o : ..\src\CBfcGUI_ScriptResource.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfcGUI_ScriptResource.o ..\src\CBfcGUI_ScriptResource.cpp

Release\CBfcGUI_ScriptResource.o : ..\src\CBfcGUI_ScriptResource.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfcGUI_ScriptResource.o ..\src\CBfcGUI_ScriptResource.cpp

Debug\CBfcGUI_TerminalWindow.o : ..\src\CBfcGUI_TerminalWindow.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfcGUI_TerminalWindow.o ..\src\CBfcGUI_TerminalWindow.cpp

Release\CBfcGUI_TerminalWindow.o : ..\src\CBfcGUI_TerminalWindow.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfcGUI_TerminalWindow.o ..\src\CBfcGUI_TerminalWindow.cpp

Debug\CBfcGUI_Toolbar.o : ..\src\CBfcGUI_Toolbar.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfcGUI_Toolbar.o ..\src\CBfcGUI_Toolbar.cpp

Release\CBfcGUI_Toolbar.o : ..\src\CBfcGUI_Toolbar.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfcGUI_Toolbar.o ..\src\CBfcGUI_Toolbar.cpp

Debug\CBfcGUI_Window.o : ..\src\CBfcGUI_Window.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfcGUI_Window.o ..\src\CBfcGUI_Window.cpp

Release\CBfcGUI_Window.o : ..\src\CBfcGUI_Window.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfcGUI_Window.o ..\src\CBfcGUI_Window.cpp

Debug\CBfcGUI_WxLayer.o : ..\src\CBfcGUI_WxLayer.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfcGUI_WxLayer.o ..\src\CBfcGUI_WxLayer.cpp

Release\CBfcGUI_WxLayer.o : ..\src\CBfcGUI_WxLayer.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfcGUI_WxLayer.o ..\src\CBfcGUI_WxLayer.cpp

Debug\CFoxBFCWindow.o : ..\src\CFoxBFCWindow.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CFoxBFCWindow.o ..\src\CFoxBFCWindow.cpp

Release\CFoxBFCWindow.o : ..\src\CFoxBFCWindow.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CFoxBFCWindow.o ..\src\CFoxBFCWindow.cpp

Debug\CQuickGUIBFCWindow.o : ..\src\CQuickGUIBFCWindow.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CQuickGUIBFCWindow.o ..\src\CQuickGUIBFCWindow.cpp

Release\CQuickGUIBFCWindow.o : ..\src\CQuickGUIBFCWindow.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CQuickGUIBFCWindow.o ..\src\CQuickGUIBFCWindow.cpp

Debug\CWxBFCWindow.o : ..\src\CWxBFCWindow.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CWxBFCWindow.o ..\src\CWxBFCWindow.cpp

Release\CWxBFCWindow.o : ..\src\CWxBFCWindow.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CWxBFCWindow.o ..\src\CWxBFCWindow.cpp

Debug\ImageWindow.o : ..\src\ImageWindow.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\ImageWindow.o ..\src\ImageWindow.cpp

Release\ImageWindow.o : ..\src\ImageWindow.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\ImageWindow.o ..\src\ImageWindow.cpp

Debug\ProgressControl.o : ..\src\ProgressControl.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\ProgressControl.o ..\src\ProgressControl.cpp

Release\ProgressControl.o : ..\src\ProgressControl.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\ProgressControl.o ..\src\ProgressControl.cpp

Debug\ResourceWindow.o : ..\src\ResourceWindow.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\ResourceWindow.o ..\src\ResourceWindow.cpp

Release\ResourceWindow.o : ..\src\ResourceWindow.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\ResourceWindow.o ..\src\ResourceWindow.cpp
