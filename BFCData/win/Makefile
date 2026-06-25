#
#ThisistheWindowsMakefileforBFCData
#
#SPDX-License-Identifier:LGPL-3.0-or-later
#Copyright(C)2011-2026WilliamP.Foster
#Thisprogramisfreesoftware:youcanredistributeitand/ormodify
#itunderthetermsoftheGNULesserGeneralPublicLicenseaspublishedby
#theFreeSoftwareFoundation,eitherversion3oftheLicense,or
#(atyouroption)anylaterversion.
#
#Thisprogramisdistributedinthehopethatitwillbeuseful,but
#WITHOUTANYWARRANTY;withouteventheimpliedwarrantyof
#MERCHANTABILITYorFITNESSFORAPARTICULARPURPOSE.SeetheGNU
#LesserGeneralPublicLicenseformoredetails.
#
#YoushouldhavereceivedacopyoftheGNULesserGeneralPublicLicense
#alongwiththisprogram.Ifnot,see<https://www.gnu.org/licenses/>.
#
# Generated via Programmer, a programmer's utility.
#
DebugDir=Debug
ReleaseDir=Release

ALL_H = CBfcData_Archive.h CBfcData_Archive_Field.h CBfcData_Archive_Record.h CBfcData_Archive_Table.h  \
		CBfcData_FileFolder.h CBfcData_Object.h  

ALL_CPP = ../src\CBfcData_Archive.cpp ../src\CBfcData_Archive_Field.cpp ../src\CBfcData_Archive_Record.cpp  

ALL_OBJ = ../src\CBfcData_Archive.o ../src\CBfcData_Archive_Field.o ../src\CBfcData_Archive_Record.o  

ALL_DEBUG_OBJ = $(DebugDir)\CBfcData_Archive.o $(DebugDir)\CBfcData_Archive_Field.o $(DebugDir)\CBfcData_Archive_Record.o  

ALL_RELEASE_OBJ = $(ReleaseDir)\CBfcData_Archive.o $(ReleaseDir)\CBfcData_Archive_Field.o $(ReleaseDir)\CBfcData_Archive_Record.o  

LIBINSTALL=\Libraries
#SRCBASE=\Sources

VER=1
srcdir=../src
LIBOUT = .
includes=../../include
DEFS = -D WIN32 -D STATICLIB
#BFCDIR=$(SRCBASE)\C++\Engines\BFC
#CSDIR=$(SRCBASE)\cs
#VCINC="C:\Program Files\Microsoft Visual Studio 10.0\VC\include"

CCPP = cl /std:c++17
CPPDEBUG = -D _DEBUG /Zi
CPPFLAGS = -I$(srcdir) -I$(includes) /std:c++17 $(DEFS)

LINKER = lib
#LINKEROPTIONS = -r

build: create debug

all : create check_headers debug release

rebuild: clean all

backup:
	programmer -b .

create:
	if NOT EXIST Debug (mkdir Debug)
	if NOT EXIST Release (mkdir Release)
	programmer -mpw $(srcdir)

clean :
	del Debug\*.o
	del Release\*.o
	del $(LIBOUT)\BFCData_d.lib
	del $(LIBOUT)\BFCData.lib

head:
	programmer -h ../header src/*.cpp
	programmer -h ../header src/*.h
	
debug : $(LIBOUT)/BFCData_d.lib

$(LIBOUT)/BFCData_d.lib :$(ALL_DEBUG_OBJ)
	$(LINKER) $(LINKEROPTIONS) /OUT:$(LIBOUT)/BFCData_d.lib $(ALL_DEBUG_OBJ)

release : $(LIBOUT)/BFCData.lib

$(LIBOUT)/BFCData.lib : $(ALL_RELEASE_OBJ)
	$(LINKER) $(LINKEROPTIONS) /OUT:$(LIBOUT)/BFCData.lib $(ALL_RELEASE_OBJ)

install: installd release
	copy $(LIBOUT)\BFCData.lib $(LIBINSTALL)

installd: debug
	copy $(LIBOUT)\BFCData_d.lib $(LIBINSTALL)

uninstall:
	del -f $(LIBINSTALL)\BFCData.lib
	del -f $(LIBINSTALL)\BFCData_d.lib


check_headers : $(ALL_H)
	$(CCPP) -E $(CPPFLAGS) ../include/BFCData.h > junk

convert:
	   skipper -i $(includes);$(VCINC) $(DEFS) -s $(BFCDIR)\BFCData\src -d $(CSDIR)\Engines\ElData\src "*.cpp"

$(DebugDir)\CBfcData_Archive.o : ..\src\CBfcData_Archive.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\CBfcData_Archive.o ..\src\CBfcData_Archive.cpp

$(ReleaseDir)\CBfcData_Archive.o : ..\src\CBfcData_Archive.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\CBfcData_Archive.o ..\src\CBfcData_Archive.cpp

$(DebugDir)\CBfcData_Archive_Field.o : ..\src\CBfcData_Archive_Field.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\CBfcData_Archive_Field.o ..\src\CBfcData_Archive_Field.cpp

$(ReleaseDir)\CBfcData_Archive_Field.o : ..\src\CBfcData_Archive_Field.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\CBfcData_Archive_Field.o ..\src\CBfcData_Archive_Field.cpp

$(DebugDir)\CBfcData_Archive_Record.o : ..\src\CBfcData_Archive_Record.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\CBfcData_Archive_Record.o ..\src\CBfcData_Archive_Record.cpp

$(ReleaseDir)\CBfcData_Archive_Record.o : ..\src\CBfcData_Archive_Record.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\CBfcData_Archive_Record.o ..\src\CBfcData_Archive_Record.cpp
