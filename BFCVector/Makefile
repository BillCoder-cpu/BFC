#
#WINDOWSMakefile
#
#ThisisthevisualstudioMakefileforBFCVector
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
#
# Generated via Programmer, a programmer's utility.
#
DebugDir=Debug
ReleaseDir=Release

ALL_H = CBfcVector_2dPlane.h CBfcVector_2dTransform.h CBfcVector_3dTransform.h CBfcVector_Coordinates.h  \
		CBfcVector_Shape2d.h CBfcVector_Shape2d_Bezier.h CBfcVector_Shape2d_Rect.h CBfcVector_Shape3d.h  \
		CBfcVector_SpaceVector.h  

ALL_CPP = src\CBfcVector_Shape2d.cpp src\CBfcVector_Shape2d_Bezier.cpp src\CBfcVector_Shape2d_Rect.cpp src\CBfcVector_Shape3d.cpp  \
		src\CBfcVector_SpaceVector.cpp  

ALL_OBJ = src\CBfcVector_Shape2d.o src\CBfcVector_Shape2d_Bezier.o src\CBfcVector_Shape2d_Rect.o src\CBfcVector_Shape3d.o  \
		src\CBfcVector_SpaceVector.o  

ALL_DEBUG_OBJ = $(DebugDir)\CBfcVector_Shape2d.o $(DebugDir)\CBfcVector_Shape2d_Bezier.o $(DebugDir)\CBfcVector_Shape2d_Rect.o $(DebugDir)\CBfcVector_Shape3d.o  \
		$(DebugDir)\CBfcVector_SpaceVector.o  

ALL_RELEASE_OBJ = $(ReleaseDir)\CBfcVector_Shape2d.o $(ReleaseDir)\CBfcVector_Shape2d_Bezier.o $(ReleaseDir)\CBfcVector_Shape2d_Rect.o $(ReleaseDir)\CBfcVector_Shape3d.o  \
		$(ReleaseDir)\CBfcVector_SpaceVector.o  

SRCBASE=\Sources
LIBINSTALL=\Libraries

SHELL=C:/Windows/System32/cmd.exe
VCINC="C:\Program Files\Microsoft Visual Studio 10.0\VC\include"
BFCINC=$(SRCBASE)\C++\Engines\BFC\include
BFCDIR=$(SRCBASE)\C++\Engines\BFC
CSDIR=$(SRCBASE)\cs

VER=1
srcdir=src
LIBOUT = .
includes=..\include
DEFS = -D WIN32 -D BFC_STATICLIB

CCPP = cl /std:c++17
CPPDEBUG = -D _DEBUG /Zi
CPPFLAGS = $(INTELOPTIONS) -I$(srcdir) -I$(includes) $(DEFS)

LINKER = lib
#LINKEROPTIONS = -r

build: create debug

all : create check_headers debug release

backup:
	programmer -b .

create:
	if NOT EXIST Debug (mkdir Debug)
	if NOT EXIST Release (mkdir Release)
	programmer -mpw $(srcdir)

convert :
	skipper -i $(BFCINC);$(VCINC) $(DEFS) -s $(BFCDIR)\BFCVector\src -d $(CSDIR)\Engines\ElVector\src "*.cpp"

clean :
	programmer -c
	del $(LIBOUT)\BFCVector_d.lib
	del $(LIBOUT)\BFCVector.lib

debug : $(ALL_DEBUG_OBJ)
	$(LINKER) $(LINKEROPTIONS) /OUT:$(LIBOUT)\BFCVector_d.lib $(ALL_DEBUG_OBJ)

release : $(ALL_RELEASE_OBJ)
	$(LINKER) $(LINKEROPTIONS) /OUT:$(LIBOUT)\BFCVector.lib $(ALL_RELEASE_OBJ)

install: installd release
	copy $(LIBOUT)\BFCVector.lib $(LIBINSTALL)

installd: debug
	copy $(LIBOUT)\BFCVector_d.lib $(LIBINSTALL)

uninstall:
	del $(LIBINSTALL)\BFCVector.lib
	del $(LIBINSTALL)\BFCVector_d.lib

check_headers : $(ALL_H)
	$(CCPP) -E $(CPPFLAGS) ../include/BFCVector.h > junk




$(DebugDir)\CBfcVector_Shape2d.o : src\CBfcVector_Shape2d.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\CBfcVector_Shape2d.o src\CBfcVector_Shape2d.cpp

$(ReleaseDir)\CBfcVector_Shape2d.o : src\CBfcVector_Shape2d.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\CBfcVector_Shape2d.o src\CBfcVector_Shape2d.cpp

$(DebugDir)\CBfcVector_Shape2d_Bezier.o : src\CBfcVector_Shape2d_Bezier.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\CBfcVector_Shape2d_Bezier.o src\CBfcVector_Shape2d_Bezier.cpp

$(ReleaseDir)\CBfcVector_Shape2d_Bezier.o : src\CBfcVector_Shape2d_Bezier.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\CBfcVector_Shape2d_Bezier.o src\CBfcVector_Shape2d_Bezier.cpp

$(DebugDir)\CBfcVector_Shape2d_Rect.o : src\CBfcVector_Shape2d_Rect.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\CBfcVector_Shape2d_Rect.o src\CBfcVector_Shape2d_Rect.cpp

$(ReleaseDir)\CBfcVector_Shape2d_Rect.o : src\CBfcVector_Shape2d_Rect.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\CBfcVector_Shape2d_Rect.o src\CBfcVector_Shape2d_Rect.cpp

$(DebugDir)\CBfcVector_Shape3d.o : src\CBfcVector_Shape3d.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\CBfcVector_Shape3d.o src\CBfcVector_Shape3d.cpp

$(ReleaseDir)\CBfcVector_Shape3d.o : src\CBfcVector_Shape3d.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\CBfcVector_Shape3d.o src\CBfcVector_Shape3d.cpp

$(DebugDir)\CBfcVector_SpaceVector.o : src\CBfcVector_SpaceVector.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\CBfcVector_SpaceVector.o src\CBfcVector_SpaceVector.cpp

$(ReleaseDir)\CBfcVector_SpaceVector.o : src\CBfcVector_SpaceVector.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\CBfcVector_SpaceVector.o src\CBfcVector_SpaceVector.cpp
