#
#WINDOWSMakefile
#
#ThisistheMinGWMakefileforBFCScript
#
#Copyright(C)2004through2008,2012byWilliamP.Foster,allrightsreserved
#
#
# Generated via Programmer, a programmer's utility.
#

ALL_H = CBfcScript.h CBfcScript_Phrase.h CBfcScript_Text.h CBfcScript_XML.h  \
		CPlusPlus_FunctionDefinition.h Equation.h Script_C.h Script_CPlusPlus.h  \
		Script_Program.h  

ALL_CPP = ../src\CBfcScript.cpp ../src\CBfcScript_Phrase.cpp ../src\CBfcScript_Text.cpp ../src\CBfcScript_XML.cpp  \
		../src\CPlusPlus_FunctionDefinition.cpp ../src\Equation.cpp ../src\Script_C.cpp ../src\Script_CPlusPlus.cpp  \
		../src\Script_Program.cpp  

ALL_OBJ = ../src\CBfcScript.o ../src\CBfcScript_Phrase.o ../src\CBfcScript_Text.o ../src\CBfcScript_XML.o  \
		../src\CPlusPlus_FunctionDefinition.o ../src\Equation.o ../src\Script_C.o ../src\Script_CPlusPlus.o  \
		../src\Script_Program.o  

ALL_DEBUG_OBJ = Debug\CBfcScript.o Debug\CBfcScript_Phrase.o Debug\CBfcScript_Text.o Debug\CBfcScript_XML.o  \
		Debug\CPlusPlus_FunctionDefinition.o Debug\Equation.o Debug\Script_C.o Debug\Script_CPlusPlus.o  \
		Debug\Script_Program.o  

ALL_RELEASE_OBJ = Release\CBfcScript.o Release\CBfcScript_Phrase.o Release\CBfcScript_Text.o Release\CBfcScript_XML.o  \
		Release\CPlusPlus_FunctionDefinition.o Release\Equation.o Release\Script_C.o Release\Script_CPlusPlus.o  \
		Release\Script_Program.o  

SHELL=C:\Windows\System32\CMD.exe

VER=1
srcdir=../src
includes=../../include

LIBOUT=.\lib
LIBINSTALL=\Users\Bill\Libraries

DEFS = -DWIN32 -DMINGW -DBFC_STATICLIB
#  -DBFC_DLL

CCPP = gcc
INTELOPTIONS=-march=pentium3 -msse -mfpmath=sse
CPPFLAGS = $(INTELOPTIONS) -I$(srcdir) -I$(includes) $(DEFS)
CPPDEBUG = -g -D_DEBUG 

LINKER = ar
LINKEROPTIONS = rcs

DLL_LINKER = g++ -shared
DLL_LINKEROPTIONS = -o
#LINKEROPTIONS = --export-dynamic

DEBUG_DLLS=$(LIBINSTALL)\BFC_mingw_d.dll $(LIBINSTALL)\BFCData_mingw_d.dll
RELEASE_DLLS=$(LIBINSTALL)\BFC_mingw.dll $(LIBINSTALL)\BFCData_mingw.dll

DEBUG_NAME=BFCScript_mingw_d.a
RELEASE_NAME=BFCScript_mingw.a

DEBUG_NAME_DLL=BFCScript_mingw_d.dll
RELEASE_NAME_DLL=BFCScript_mingw.dll

build: create debug

all : create debug release

backup:
	programmer -b .

rebuild: clean all

clean :
	programmer -c
	del $(LIBOUT)\$(DEBUG_NAME)
	del $(LIBOUT)\$(RELEASE_NAME)
	del $(LIBOUT)\$(DEBUG_NAME_DLL)
	del $(LIBOUT)\$(RELEASE_NAME_DLL)

head:
	programmer -h ../header src/*.cpp
	programmer -h ../header src/*.h

create:
	programmer -mpg $(srcdir)

debug : $(LIBOUT)/$(DEBUG_NAME) $(LIBOUT)/$(DEBUG_NAME_DLL)

$(LIBOUT)/$(DEBUG_NAME) : $(ALL_DEBUG_OBJ) $(DEBUG_DLLS)
	$(LINKER) $(LINKEROPTIONS) $(LIBOUT)/$(DEBUG_NAME) $(ALL_DEBUG_OBJ)

$(LIBOUT)/$(DEBUG_NAME_DLL) : $(ALL_DEBUG_OBJ) $(DEBUG_DLLS)
	$(DLL_LINKER) $(DLL_LINKEROPTIONS) $(LIBOUT)/$(DEBUG_NAME_DLL) $(ALL_DEBUG_OBJ) $(DEBUG_DLLS)
	
release : $(LIBOUT)/$(RELEASE_NAME) $(LIBOUT)/$(RELEASE_NAME_DLL)

$(LIBOUT)/$(RELEASE_NAME) : $(ALL_RELEASE_OBJ) $(RELEASE_DLLS)
	$(LINKER) $(LINKEROPTIONS) $(LIBOUT)/$(RELEASE_NAME) $(ALL_RELEASE_OBJ)

$(LIBOUT)/$(RELEASE_NAME_DLL) : $(ALL_RELEASE_OBJ) $(RELEASE_DLLS)
	$(DLL_LINKER) $(DLL_LINKEROPTIONS) $(LIBOUT)/$(RELEASE_NAME_DLL) $(ALL_RELEASE_OBJ) $(RELEASE_DLLS)
	
install: installd release
	copy $(LIBOUT)\$(RELEASE_NAME) $(LIBINSTALL)\$(RELEASE_NAME)
	copy $(LIBOUT)\$(RELEASE_NAME_DLL) $(LIBINSTALL)\$(RELEASE_NAME_DLL)

installd: debug
	copy $(LIBOUT)\$(DEBUG_NAME) $(LIBINSTALL)\$(DEBUG_NAME)
	copy $(LIBOUT)\$(DEBUG_NAME_DLL) $(LIBINSTALL)\$(DEBUG_NAME_DLL)

uninstall:
	del $(LIBINSTALL)/$(DEBUG_NAME)
	del $(LIBINSTALL)/$(RELEASE_NAME)






Debug\CBfcScript.o : ../src\CBfcScript.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfcScript.o ../src\CBfcScript.cpp

Release\CBfcScript.o : ../src\CBfcScript.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfcScript.o ../src\CBfcScript.cpp

Debug\CBfcScript_Phrase.o : ../src\CBfcScript_Phrase.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfcScript_Phrase.o ../src\CBfcScript_Phrase.cpp

Release\CBfcScript_Phrase.o : ../src\CBfcScript_Phrase.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfcScript_Phrase.o ../src\CBfcScript_Phrase.cpp

Debug\CBfcScript_Text.o : ../src\CBfcScript_Text.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfcScript_Text.o ../src\CBfcScript_Text.cpp

Release\CBfcScript_Text.o : ../src\CBfcScript_Text.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfcScript_Text.o ../src\CBfcScript_Text.cpp

Debug\CBfcScript_XML.o : ../src\CBfcScript_XML.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfcScript_XML.o ../src\CBfcScript_XML.cpp

Release\CBfcScript_XML.o : ../src\CBfcScript_XML.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfcScript_XML.o ../src\CBfcScript_XML.cpp

Debug\CPlusPlus_FunctionDefinition.o : ../src\CPlusPlus_FunctionDefinition.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CPlusPlus_FunctionDefinition.o ../src\CPlusPlus_FunctionDefinition.cpp

Release\CPlusPlus_FunctionDefinition.o : ../src\CPlusPlus_FunctionDefinition.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CPlusPlus_FunctionDefinition.o ../src\CPlusPlus_FunctionDefinition.cpp

Debug\Equation.o : ../src\Equation.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\Equation.o ../src\Equation.cpp

Release\Equation.o : ../src\Equation.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\Equation.o ../src\Equation.cpp

Debug\Script_C.o : ../src\Script_C.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\Script_C.o ../src\Script_C.cpp

Release\Script_C.o : ../src\Script_C.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\Script_C.o ../src\Script_C.cpp

Debug\Script_CPlusPlus.o : ../src\Script_CPlusPlus.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\Script_CPlusPlus.o ../src\Script_CPlusPlus.cpp

Release\Script_CPlusPlus.o : ../src\Script_CPlusPlus.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\Script_CPlusPlus.o ../src\Script_CPlusPlus.cpp

Debug\Script_Program.o : ../src\Script_Program.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\Script_Program.o ../src\Script_Program.cpp

Release\Script_Program.o : ../src\Script_Program.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\Script_Program.o ../src\Script_Program.cpp
