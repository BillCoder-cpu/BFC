#
#WindowsMakefile
#
#ThisistheMinGWgccMakefileforBFCData
#
#Copyright(C)2004,2012byWilliamP.Foster,allrightsreserved
#
#
# Generated via Programmer, a programmer's utility.
#

ALL_H = CBfcData_Archive.h CBfcData_Archive_Field.h CBfcData_Archive_Record.h CBfcData_Archive_Table.h  \
		CBfcData_FileFolder.h CBfcData_Object.h  

ALL_CPP = ../src\CBfcData_Archive.cpp ../src\CBfcData_Archive_Field.cpp ../src\CBfcData_Archive_Record.cpp  

ALL_OBJ = ../src\CBfcData_Archive.o ../src\CBfcData_Archive_Field.o ../src\CBfcData_Archive_Record.o  

ALL_DEBUG_OBJ = Debug\CBfcData_Archive.o Debug\CBfcData_Archive_Field.o Debug\CBfcData_Archive_Record.o  

ALL_RELEASE_OBJ = Release\CBfcData_Archive.o Release\CBfcData_Archive_Field.o Release\CBfcData_Archive_Record.o  

VER=1
srcdir=../src
includes=../../include

LIBOUT=.\lib
LIBINSTALL=\Users\Bill\Libraries
DEFS = -DWIN32 -DMINGW -DSTATICLIB
# -DBFC_DLL 

CCPP = gcc
INTELOPTIONS=-march=pentium3 -msse -mfpmath=sse
CPPFLAGS = $(INTELOPTIONS) -I$(srcdir) -I$(includes) $(DEFS)
CPPDEBUG = -g -D_DEBUG 

LINKER = ar
LINKEROPTIONS = rcs

DEBUG_NAME=BFCData_mingw_d.a
RELEASE_NAME=BFCData_mingw.a

# For Making DLL's:
DLL_LINKER = g++ -shared
DLL_LINKEROPTIONS = -o

DLL_DEBUG_NAME=BFCData_mingw_d.dll
DLL_RELEASE_NAME=BFCData_mingw.dll

DEBUG_DLLS=$(LIBINSTALL)\BFC_mingw_d.dll
RELEASE_DLLS=$(LIBINSTALL)\BFC_mingw.dll


build: create debug

all : create debug release

rebuild: clean all

backup:
	header -b .

create:
	programmer -mpg $(srcdir)

clean :
	programmer -c
	del $(LIBOUT)\$(DEBUG_NAME)
	del $(LIBOUT)\$(RELEASE_NAME)

debug : $(LIBOUT)/$(DEBUG_NAME) $(LIBOUT)/$(DLL_DEBUG_NAME)

$(LIBOUT)/$(DEBUG_NAME) : $(ALL_DEBUG_OBJ)
	$(LINKER) $(LINKEROPTIONS) $(LIBOUT)/$(DEBUG_NAME) $(ALL_DEBUG_OBJ)

$(LIBOUT)/$(DLL_DEBUG_NAME) : $(ALL_DEBUG_OBJ) $(DEBUG_DLLS)
	$(DLL_LINKER) $(DLL_LINKEROPTIONS) $(LIBOUT)/$(DLL_DEBUG_NAME) $(ALL_DEBUG_OBJ) $(DEBUG_DLLS)
	
release : $(LIBOUT)/$(RELEASE_NAME) $(LIBOUT)/$(DLL_RELEASE_NAME)

$(LIBOUT)/$(RELEASE_NAME) : $(ALL_RELEASE_OBJ) $(RELEASE_DLLS)
	$(LINKER) $(LINKEROPTIONS) $(LIBOUT)/$(RELEASE_NAME) $(ALL_RELEASE_OBJ)

$(LIBOUT)/$(DLL_RELEASE_NAME) : $(ALL_RELEASE_OBJ) $(RELEASE_DLLS)
	$(DLL_LINKER) $(DLL_LINKEROPTIONS) $(LIBOUT)/$(DLL_RELEASE_NAME) $(ALL_RELEASE_OBJ) $(RELEASE_DLLS)

install: installd release
	copy $(LIBOUT)\$(RELEASE_NAME) $(LIBINSTALL)\$(RELEASE_NAME)
	copy $(LIBOUT)\$(DLL_RELEASE_NAME) $(LIBINSTALL)\$(DLL_RELEASE_NAME)

installd: debug
	copy $(LIBOUT)\$(DEBUG_NAME) $(LIBINSTALL)\$(DEBUG_NAME)
	copy $(LIBOUT)\$(DLL_DEBUG_NAME) $(LIBINSTALL)\$(DLL_DEBUG_NAME)

uninstall:
	del $(LIBINSTALL)/$(DEBUG_NAME)
	del $(LIBINSTALL)/$(RELEASE_NAME)


Debug\CBfcData_Archive.o : ../src\CBfcData_Archive.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfcData_Archive.o ../src\CBfcData_Archive.cpp

Release\CBfcData_Archive.o : ../src\CBfcData_Archive.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfcData_Archive.o ../src\CBfcData_Archive.cpp

Debug\CBfcData_Archive_Field.o : ../src\CBfcData_Archive_Field.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfcData_Archive_Field.o ../src\CBfcData_Archive_Field.cpp

Release\CBfcData_Archive_Field.o : ../src\CBfcData_Archive_Field.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfcData_Archive_Field.o ../src\CBfcData_Archive_Field.cpp

Debug\CBfcData_Archive_Record.o : ../src\CBfcData_Archive_Record.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfcData_Archive_Record.o ../src\CBfcData_Archive_Record.cpp

Release\CBfcData_Archive_Record.o : ../src\CBfcData_Archive_Record.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfcData_Archive_Record.o ../src\CBfcData_Archive_Record.cpp
