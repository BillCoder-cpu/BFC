#
#FreeBSDMakefile
#
#ThisisthegccMakefileforBFC
#
#Copyright(C)2004byWilliamP.Foster,allrightsreserved
#
#
# Generated via Programmer, a programmer's utility.
#
DebugDir=Debug
ReleaseDir=Release

ALL_H = CBfcData_Archive.h CBfcData_Archive_Field.h CBfcData_Archive_Record.h CBfcData_Archive_Table.h  \
		CBfcData_FileFolder.h CBfcData_Object.h  

ALL_CPP = src/CBfcData_Archive.cpp src/CBfcData_Archive_Field.cpp src/CBfcData_Archive_Record.cpp  

ALL_OBJ = src/CBfcData_Archive.o src/CBfcData_Archive_Field.o src/CBfcData_Archive_Record.o  

ALL_DEBUG_OBJ = $(DebugDir)/CBfcData_Archive.o $(DebugDir)/CBfcData_Archive_Field.o $(DebugDir)/CBfcData_Archive_Record.o  

ALL_RELEASE_OBJ = $(ReleaseDir)/CBfcData_Archive.o $(ReleaseDir)/CBfcData_Archive_Field.o $(ReleaseDir)/CBfcData_Archive_Record.o  

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

build: create debug

all : create check_headers debug release

rebuild: clean all

backup:
	programmer -b .

create:
	mkdir -p Debug
	mkdir -p Release
	programmer -mp $(srcdir)

clean :
	rm -f Debug/*.o
	rm -f Release/*.o
	rm -f $(LIBOUT)/BFCData_d.so.$(VER)
	rm -f $(LIBOUT)/BFCData.so.$(VER)

debug : $(ALL_DEBUG_OBJ)
	g++ -shared -o $(LIBOUT)/BFCData_d.so.$(VER) $(ALL_DEBUG_OBJ)
	$(LINKER) $(LINKEROPTIONS) -o $(LIBOUT)/BFCData_d.lib $(ALL_DEBUG_OBJ)

release : $(ALL_RELEASE_OBJ)
	g++ -shared -o $(LIBOUT)/BFCData.so.$(VER) $(ALL_RELEASE_OBJ)
	$(LINKER) $(LINKEROPTIONS) -o $(LIBOUT)/BFCData.lib $(ALL_RELEASE_OBJ)

check_headers : $(ALL_H)
	$(CCPP) -E $(CPPFLAGS) ../include/BFCData.h > junk

install: installd release
	rm -f $(LIBINSTALL)/BFCData.so
	cp $(LIBOUT)/BFCData.so.$(VER) $(LIBINSTALL)/BFCData.so.$(VER)
	link $(LIBINSTALL)/BFCData.so.$(VER) $(LIBINSTALL)/BFCData.so

installd: debug
	rm -f $(LIBINSTALL)/BFCData_d.so
	cp $(LIBOUT)/BFCData_d.so.$(VER) $(LIBINSTALL)/BFCData_d.so.$(VER)
	link $(LIBINSTALL)/BFCData_d.so.$(VER) $(LIBINSTALL)/BFCData_d.so

uninstall:
	rm -f $(LIBINSTALL)/BFCData_d.so
	rm -f $(LIBINSTALL)/BFCData_d.so.$(VER)
	rm -f $(LIBINSTALL)/BFCData.so
	rm -f $(LIBINSTALL)/BFCData.so.$(VER)


$(DebugDir)/CBfcData_Archive.o : src/CBfcData_Archive.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o $(DebugDir)/CBfcData_Archive.o src/CBfcData_Archive.cpp

$(ReleaseDir)/CBfcData_Archive.o : src/CBfcData_Archive.cpp 
		$(CCPP) -c $(CPPFLAGS) -o $(ReleaseDir)/CBfcData_Archive.o src/CBfcData_Archive.cpp

$(DebugDir)/CBfcData_Archive_Field.o : src/CBfcData_Archive_Field.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o $(DebugDir)/CBfcData_Archive_Field.o src/CBfcData_Archive_Field.cpp

$(ReleaseDir)/CBfcData_Archive_Field.o : src/CBfcData_Archive_Field.cpp 
		$(CCPP) -c $(CPPFLAGS) -o $(ReleaseDir)/CBfcData_Archive_Field.o src/CBfcData_Archive_Field.cpp

$(DebugDir)/CBfcData_Archive_Record.o : src/CBfcData_Archive_Record.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o $(DebugDir)/CBfcData_Archive_Record.o src/CBfcData_Archive_Record.cpp

$(ReleaseDir)/CBfcData_Archive_Record.o : src/CBfcData_Archive_Record.cpp 
		$(CCPP) -c $(CPPFLAGS) -o $(ReleaseDir)/CBfcData_Archive_Record.o src/CBfcData_Archive_Record.cpp
