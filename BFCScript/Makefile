#
#PosixMakefile
#
#ThisisthegccMakefileforBFCScript
#
#Copyright(C)2005byWilliamP.Foster,allrightsreserved
#
#
# Generated via Programmer, a programmer's utility.
#
DebugDir=Debug
ReleaseDir=Release

ALL_H = CBfcScript.h CBfcScript_Phrase.h CBfcScript_Text.h CBfcScript_XML.h  \
		CPlusPlus_FunctionDefinition.h Equation.h Script_C.h Script_CPlusPlus.h  \
		Script_Program.h  

ALL_CPP = src/CBfcScript.cpp src/CBfcScript_Phrase.cpp src/CBfcScript_Text.cpp src/CBfcScript_XML.cpp  \
		src/CPlusPlus_FunctionDefinition.cpp src/Equation.cpp src/Script_C.cpp src/Script_CPlusPlus.cpp  \
		src/Script_Program.cpp  

ALL_OBJ = src/CBfcScript.o src/CBfcScript_Phrase.o src/CBfcScript_Text.o src/CBfcScript_XML.o  \
		src/CPlusPlus_FunctionDefinition.o src/Equation.o src/Script_C.o src/Script_CPlusPlus.o  \
		src/Script_Program.o  

ALL_DEBUG_OBJ = $(DebugDir)/CBfcScript.o $(DebugDir)/CBfcScript_Phrase.o $(DebugDir)/CBfcScript_Text.o $(DebugDir)/CBfcScript_XML.o  \
		$(DebugDir)/CPlusPlus_FunctionDefinition.o $(DebugDir)/Equation.o $(DebugDir)/Script_C.o $(DebugDir)/Script_CPlusPlus.o  \
		$(DebugDir)/Script_Program.o  

ALL_RELEASE_OBJ = $(ReleaseDir)/CBfcScript.o $(ReleaseDir)/CBfcScript_Phrase.o $(ReleaseDir)/CBfcScript_Text.o $(ReleaseDir)/CBfcScript_XML.o  \
		$(ReleaseDir)/CPlusPlus_FunctionDefinition.o $(ReleaseDir)/Equation.o $(ReleaseDir)/Script_C.o $(ReleaseDir)/Script_CPlusPlus.o  \
		$(ReleaseDir)/Script_Program.o  

VER=1
srcdir=src
LIBINSTALL=/lib
LIBOUT = $(HOME)/Libraries/Unix
includes=../include
WINDEFS = -D _WIN32
LINUXDEFS = -D UNIX
ifeq ($(OS),Windows_NT)
	DEFS=$(WINDEFS)
else
	DEFS=$(LINUXDEFS)
endif

CCPP = gcc
CPPDEBUG = -g -D _DEBUG
CPPFLAGS = -I$(srcdir) -I$(includes) -fPIC $(DEFS)

LINKER = ld
LINKEROPTIONS = -r

# ifeq ($(CC),gcc)
#   libs=$(libs_for_gcc)
# else
#   libs=$(normal_libs)
# endif

Debug/%.o $(srcdir)/%.cpp:
	$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) $< -o $@

Release/%.o $(srcdir)/%.cpp:
	$(CCPP) -c $(CPPFLAGS) $< -o $@

all : create check_headers debug release

create:
	mkdir -p Debug
	mkdir -p Release
	programmer -mp $(srcdir)

backup:
	programmer -b .

clean :
	rm -f Debug/*.o
	rm -f Release/*.o
	rm -f $(LIBOUT)/BFCScript_d.so.$(VER)
	rm -f $(LIBOUT)/BFCScript.so.$(VER)

gen_cs:
	skipper -i "$(includes);$(srcdir)" -d cs -s $(srcdir) *.cpp

head:
	header -h ../header $(srcdir)/*.cpp
	header -h ../header $(srcdir)/*.h

debug : $(ALL_DEBUG_OBJ)
	g++ -shared -Wl,-soname,BFCScript_d.so.$(VER) -o $(LIBOUT)/BFCScript_d.so.$(VER) $(ALL_DEBUG_OBJ)
	$(LINKER) $(LINKEROPTIONS) -o $(LIBOUT)/BFCScript_d.lib $(ALL_DEBUG_OBJ)

release : $(ALL_RELEASE_OBJ)
	g++ -shared -Wl,-soname,BFCScript.so.$(VER) -o $(LIBOUT)/BFCScript.so.$(VER) $(ALL_RELEASE_OBJ)
	$(LINKER) $(LINKEROPTIONS) -o $(LIBOUT)/BFCScript.lib $(ALL_RELEASE_OBJ)

install: installd release
	cp $(LIBOUT)/BFCScript.so.$(VER) $(LIBINSTALL)
	rm -f $(LIBINSTALL)/BFCScript.so
	link $(LIBINSTALL)/BFCScript.so.$(VER) $(LIBINSTALL)/BFCScript.so

installd: debug
	cp $(LIBOUT)/BFCScript_d.so.$(VER) $(LIBINSTALL)
	rm -f $(LIBINSTALL)/BFCScript_d.so
	link $(LIBINSTALL)/BFCScript_d.so.$(VER) $(LIBINSTALL)/BFCScript_d.so

uninstall:
	rm -f $(LIBINSTALL)/BFCScript.so
	rm -f $(LIBINSTALL)/BFCScript.so.$(VER)
	rm -f $(LIBINSTALL)/BFCScript_d.so
	rm -f $(LIBINSTALL)/BFCScript_d.so.$(VER)

# check_headers : $(ALL_H)
#	$(CCPP) -E $(CPPFLAGS) $(includes)/BFCScript.h > junk




$(DebugDir)/CBfcScript.o : src/CBfcScript.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o $(DebugDir)/CBfcScript.o src/CBfcScript.cpp

$(ReleaseDir)/CBfcScript.o : src/CBfcScript.cpp 
		$(CCPP) -c $(CPPFLAGS) -o $(ReleaseDir)/CBfcScript.o src/CBfcScript.cpp

$(DebugDir)/CBfcScript_Phrase.o : src/CBfcScript_Phrase.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o $(DebugDir)/CBfcScript_Phrase.o src/CBfcScript_Phrase.cpp

$(ReleaseDir)/CBfcScript_Phrase.o : src/CBfcScript_Phrase.cpp 
		$(CCPP) -c $(CPPFLAGS) -o $(ReleaseDir)/CBfcScript_Phrase.o src/CBfcScript_Phrase.cpp

$(DebugDir)/CBfcScript_Text.o : src/CBfcScript_Text.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o $(DebugDir)/CBfcScript_Text.o src/CBfcScript_Text.cpp

$(ReleaseDir)/CBfcScript_Text.o : src/CBfcScript_Text.cpp 
		$(CCPP) -c $(CPPFLAGS) -o $(ReleaseDir)/CBfcScript_Text.o src/CBfcScript_Text.cpp

$(DebugDir)/CBfcScript_XML.o : src/CBfcScript_XML.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o $(DebugDir)/CBfcScript_XML.o src/CBfcScript_XML.cpp

$(ReleaseDir)/CBfcScript_XML.o : src/CBfcScript_XML.cpp 
		$(CCPP) -c $(CPPFLAGS) -o $(ReleaseDir)/CBfcScript_XML.o src/CBfcScript_XML.cpp

$(DebugDir)/CPlusPlus_FunctionDefinition.o : src/CPlusPlus_FunctionDefinition.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o $(DebugDir)/CPlusPlus_FunctionDefinition.o src/CPlusPlus_FunctionDefinition.cpp

$(ReleaseDir)/CPlusPlus_FunctionDefinition.o : src/CPlusPlus_FunctionDefinition.cpp 
		$(CCPP) -c $(CPPFLAGS) -o $(ReleaseDir)/CPlusPlus_FunctionDefinition.o src/CPlusPlus_FunctionDefinition.cpp

$(DebugDir)/Equation.o : src/Equation.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o $(DebugDir)/Equation.o src/Equation.cpp

$(ReleaseDir)/Equation.o : src/Equation.cpp 
		$(CCPP) -c $(CPPFLAGS) -o $(ReleaseDir)/Equation.o src/Equation.cpp

$(DebugDir)/Script_C.o : src/Script_C.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o $(DebugDir)/Script_C.o src/Script_C.cpp

$(ReleaseDir)/Script_C.o : src/Script_C.cpp 
		$(CCPP) -c $(CPPFLAGS) -o $(ReleaseDir)/Script_C.o src/Script_C.cpp

$(DebugDir)/Script_CPlusPlus.o : src/Script_CPlusPlus.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o $(DebugDir)/Script_CPlusPlus.o src/Script_CPlusPlus.cpp

$(ReleaseDir)/Script_CPlusPlus.o : src/Script_CPlusPlus.cpp 
		$(CCPP) -c $(CPPFLAGS) -o $(ReleaseDir)/Script_CPlusPlus.o src/Script_CPlusPlus.cpp

$(DebugDir)/Script_Program.o : src/Script_Program.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o $(DebugDir)/Script_Program.o src/Script_Program.cpp

$(ReleaseDir)/Script_Program.o : src/Script_Program.cpp 
		$(CCPP) -c $(CPPFLAGS) -o $(ReleaseDir)/Script_Program.o src/Script_Program.cpp
