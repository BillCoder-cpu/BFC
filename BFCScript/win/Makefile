#
#WindowsMakefile
#
#ThisistheWindowsMakefileforBFCScript
#
#Copyright(C)2005-2020byWilliamP.Foster,allrightsreserved
#
#
# Generated via Programmer, a programmer's utility.
#
DebugDir=Debug
ReleaseDir=Release

ALL_H = CBfcScript.h CBfcScript_Phrase.h CBfcScript_Text.h CBfcScript_XML.h  \
		CPlusPlus_FunctionDefinition.h Equation.h Script_C.h Script_CPlusPlus.h  \
		Script_Program.h  

ALL_CPP = ..\src\CBfcScript.cpp ..\src\CBfcScript_Phrase.cpp ..\src\CBfcScript_Text.cpp ..\src\CBfcScript_XML.cpp  \
		..\src\CPlusPlus_FunctionDefinition.cpp ..\src\Equation.cpp ..\src\Script_C.cpp ..\src\Script_CPlusPlus.cpp  \
		..\src\Script_Program.cpp  

ALL_OBJ = ..\src\CBfcScript.o ..\src\CBfcScript_Phrase.o ..\src\CBfcScript_Text.o ..\src\CBfcScript_XML.o  \
		..\src\CPlusPlus_FunctionDefinition.o ..\src\Equation.o ..\src\Script_C.o ..\src\Script_CPlusPlus.o  \
		..\src\Script_Program.o  

ALL_DEBUG_OBJ = $(DebugDir)\CBfcScript.o $(DebugDir)\CBfcScript_Phrase.o $(DebugDir)\CBfcScript_Text.o $(DebugDir)\CBfcScript_XML.o  \
		$(DebugDir)\CPlusPlus_FunctionDefinition.o $(DebugDir)\Equation.o $(DebugDir)\Script_C.o $(DebugDir)\Script_CPlusPlus.o  \
		$(DebugDir)\Script_Program.o  

ALL_RELEASE_OBJ = $(ReleaseDir)\CBfcScript.o $(ReleaseDir)\CBfcScript_Phrase.o $(ReleaseDir)\CBfcScript_Text.o $(ReleaseDir)\CBfcScript_XML.o  \
		$(ReleaseDir)\CPlusPlus_FunctionDefinition.o $(ReleaseDir)\Equation.o $(ReleaseDir)\Script_C.o $(ReleaseDir)\Script_CPlusPlus.o  \
		$(ReleaseDir)\Script_Program.o  

SHELL=C:/Windows/System32/cmd.exe
VER=1
srcdir=..\src
LIBOUT=.
LIBINSTALL = \Libraries
includes=../../include
DEFS = -D WIN32 -D BFC_STATICLIB
SRCDIR=\Sources
BFCINC=$(SRCDIR)\C++\Engines\BFC\include
BFCDIR=$(SRCDIR)\C++\Engines\BFC
VCINC="C:\Program Files\Microsoft Visual Studio 10.0\VC\include"
CSDIR=$(SRCDIR)\cs

CCPP = cl
CPPDEBUG = -D _DEBUG /Zi
CPPFLAGS = -I$(srcdir) -I$(includes) $(DEFS)

LINKER = lib
#LINKEROPTIONS = -r

# ifeq ($(CC),gcc)
#   libs=$(libs_for_gcc)
# else
#   libs=$(normal_libs)
# endif

#Debug/%.o $(srcdir)/%.cpp:
#	$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) $< /Fo$@

#Release/%.o $(srcdir)/%.cpp:
#	$(CCPP) -c $(CPPFLAGS) $< /Fo$@

all : create debug release

create:
	if NOT EXIST Debug (mkdir Debug)
	if NOT EXIST Release (mkdir Release)
	programmer -mpw $(srcdir)

backup:
	programmer -b .

clean :
	programmer -c
	del $(LIBOUT)\BFCScript_d.lib
	del $(LIBOUT)\BFCScript.lib

gen_cs:
	skipper -i "$(includes);$(srcdir)" -d cs -s $(srcdir) *.cpp

convert:
	skipper -i $(BFCINC);$(VCINC) $(DEFS) -s $(BFCDIR)\BFCScript\src -d $(CSDIR)\Engines\ElScript\ElScript\src "*.cpp"

head:
	header -h ../header $(srcdir)/*.cpp
	header -h ../header $(srcdir)/*.h

debug : $(LIBOUT)/BFCScript_d.lib

$(LIBOUT)/BFCScript_d.lib: $(ALL_DEBUG_OBJ)
	$(LINKER) $(LINKEROPTIONS) /OUT:$(LIBOUT)/BFCScript_d.lib $(ALL_DEBUG_OBJ)

release : $(LIBOUT)/BFCScript.lib

$(LIBOUT)/BFCScript.lib : $(ALL_RELEASE_OBJ)
	$(LINKER) $(LINKEROPTIONS) /OUT:$(LIBOUT)/BFCScript.lib $(ALL_RELEASE_OBJ)

install: installd release
	copy $(LIBOUT)\BFCScript.lib $(LIBINSTALL)

installd: debug
	copy $(LIBOUT)\BFCScript_d.lib $(LIBINSTALL)

uninstall:
	DEL -f $(LIBINSTALL)\BFCScript.lib
	del -f $(LIBINSTALL)\BFCScript_d.lib

# check_headers : $(ALL_H)
#	$(CCPP) -E $(CPPFLAGS) $(includes)/BFCScript.h > junk




$(DebugDir)\CBfcScript.o : ..\src\CBfcScript.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\CBfcScript.o ..\src\CBfcScript.cpp

$(ReleaseDir)\CBfcScript.o : ..\src\CBfcScript.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\CBfcScript.o ..\src\CBfcScript.cpp

$(DebugDir)\CBfcScript_Phrase.o : ..\src\CBfcScript_Phrase.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\CBfcScript_Phrase.o ..\src\CBfcScript_Phrase.cpp

$(ReleaseDir)\CBfcScript_Phrase.o : ..\src\CBfcScript_Phrase.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\CBfcScript_Phrase.o ..\src\CBfcScript_Phrase.cpp

$(DebugDir)\CBfcScript_Text.o : ..\src\CBfcScript_Text.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\CBfcScript_Text.o ..\src\CBfcScript_Text.cpp

$(ReleaseDir)\CBfcScript_Text.o : ..\src\CBfcScript_Text.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\CBfcScript_Text.o ..\src\CBfcScript_Text.cpp

$(DebugDir)\CBfcScript_XML.o : ..\src\CBfcScript_XML.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\CBfcScript_XML.o ..\src\CBfcScript_XML.cpp

$(ReleaseDir)\CBfcScript_XML.o : ..\src\CBfcScript_XML.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\CBfcScript_XML.o ..\src\CBfcScript_XML.cpp

$(DebugDir)\CPlusPlus_FunctionDefinition.o : ..\src\CPlusPlus_FunctionDefinition.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\CPlusPlus_FunctionDefinition.o ..\src\CPlusPlus_FunctionDefinition.cpp

$(ReleaseDir)\CPlusPlus_FunctionDefinition.o : ..\src\CPlusPlus_FunctionDefinition.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\CPlusPlus_FunctionDefinition.o ..\src\CPlusPlus_FunctionDefinition.cpp

$(DebugDir)\Equation.o : ..\src\Equation.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\Equation.o ..\src\Equation.cpp

$(ReleaseDir)\Equation.o : ..\src\Equation.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\Equation.o ..\src\Equation.cpp

$(DebugDir)\Script_C.o : ..\src\Script_C.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\Script_C.o ..\src\Script_C.cpp

$(ReleaseDir)\Script_C.o : ..\src\Script_C.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\Script_C.o ..\src\Script_C.cpp

$(DebugDir)\Script_CPlusPlus.o : ..\src\Script_CPlusPlus.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\Script_CPlusPlus.o ..\src\Script_CPlusPlus.cpp

$(ReleaseDir)\Script_CPlusPlus.o : ..\src\Script_CPlusPlus.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\Script_CPlusPlus.o ..\src\Script_CPlusPlus.cpp

$(DebugDir)\Script_Program.o : ..\src\Script_Program.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\Script_Program.o ..\src\Script_Program.cpp

$(ReleaseDir)\Script_Program.o : ..\src\Script_Program.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\Script_Program.o ..\src\Script_Program.cpp
