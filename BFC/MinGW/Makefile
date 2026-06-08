#
#WINDOWSMakefile
#
#ThisistheMinGWMakefileforBFC
#
#Copyright(C)2012byWilliamP.Foster,allrightsreserved
#
#
# Generated via Programmer, a programmer's utility.
#

ALL_H = Array2d.h BFCDefs.h BFCDefs_KeyDefs.h BFCTypes.h  \
		BFCUnDefs.h Bfc_DebugStatic.h bfc_unix.h bfc_windows.h  \
		CBfc_2dRect.h CBfc_2dShape.h CBfc_2dSize.h CBfc_Angle.h  \
		CBfc_Array.h CBfc_CompressionAlgorythm.h CBfc_Distance.h CBfc_DynamicLink.h  \
		CBfc_Exception.h CBfc_File.h CBfc_Filename.h CBfc_LinkedList.h  \
		CBfc_Map2d.h CBfc_Matrix.h CBfc_Object.h CBfc_PointSpace3d.h  \
		CBfc_PointSpaceTime.h CBfc_PointTime.h CBfc_Range2d.h CBfc_ReferencedAllocation.h  \
		CBfc_ReferencedObject.h CBfc_ReferencedPointer.h CBfc_ReferencedValue.h CBfc_Registry.h  \
		CBfc_Stream.h CBfc_StreamSource.h CBfc_String.h CBfc_Tree.h  \
		CBfc_Value.h character.h speedfloat.h  

ALL_CPP = ../src\Bfc_DebugStatic.cpp ../src\CBfc_2dRect.cpp ../src\CBfc_2dSize.cpp ../src\CBfc_Angle.cpp  \
		../src\CBfc_Array.cpp ../src\CBfc_CompressionAlgorythm.cpp ../src\CBfc_Distance.cpp ../src\CBfc_DynamicLink.cpp  \
		../src\CBfc_Exception.cpp ../src\CBfc_File.cpp ../src\CBfc_Filename.cpp ../src\CBfc_LinkedList.cpp  \
		../src\CBfc_MatrixDoubles.cpp ../src\CBfc_PointSpace3d.cpp ../src\CBfc_PointSpaceTime.cpp ../src\CBfc_PointTime.cpp  \
		../src\CBfc_Range2d.cpp ../src\CBfc_ReferencedAllocation.cpp ../src\CBfc_ReferencedObject.cpp ../src\CBfc_ReferencedPointer.cpp  \
		../src\CBfc_Registry.cpp ../src\CBfc_Stream.cpp ../src\CBfc_StreamSource.cpp ../src\CBfc_String.cpp  \
		../src\CBfc_String8.cpp ../src\CBfc_Value.cpp ../src\character.cpp ../src\Rect2dU.cpp  \
		../src\Size2dU.cpp  

ALL_OBJ = ../src\Bfc_DebugStatic.o ../src\CBfc_2dRect.o ../src\CBfc_2dSize.o ../src\CBfc_Angle.o  \
		../src\CBfc_Array.o ../src\CBfc_CompressionAlgorythm.o ../src\CBfc_Distance.o ../src\CBfc_DynamicLink.o  \
		../src\CBfc_Exception.o ../src\CBfc_File.o ../src\CBfc_Filename.o ../src\CBfc_LinkedList.o  \
		../src\CBfc_MatrixDoubles.o ../src\CBfc_PointSpace3d.o ../src\CBfc_PointSpaceTime.o ../src\CBfc_PointTime.o  \
		../src\CBfc_Range2d.o ../src\CBfc_ReferencedAllocation.o ../src\CBfc_ReferencedObject.o ../src\CBfc_ReferencedPointer.o  \
		../src\CBfc_Registry.o ../src\CBfc_Stream.o ../src\CBfc_StreamSource.o ../src\CBfc_String.o  \
		../src\CBfc_String8.o ../src\CBfc_Value.o ../src\character.o ../src\Rect2dU.o  \
		../src\Size2dU.o  

ALL_DEBUG_OBJ = Debug\Bfc_DebugStatic.o Debug\CBfc_2dRect.o Debug\CBfc_2dSize.o Debug\CBfc_Angle.o  \
		Debug\CBfc_Array.o Debug\CBfc_CompressionAlgorythm.o Debug\CBfc_Distance.o Debug\CBfc_DynamicLink.o  \
		Debug\CBfc_Exception.o Debug\CBfc_File.o Debug\CBfc_Filename.o Debug\CBfc_LinkedList.o  \
		Debug\CBfc_MatrixDoubles.o Debug\CBfc_PointSpace3d.o Debug\CBfc_PointSpaceTime.o Debug\CBfc_PointTime.o  \
		Debug\CBfc_Range2d.o Debug\CBfc_ReferencedAllocation.o Debug\CBfc_ReferencedObject.o Debug\CBfc_ReferencedPointer.o  \
		Debug\CBfc_Registry.o Debug\CBfc_Stream.o Debug\CBfc_StreamSource.o Debug\CBfc_String.o  \
		Debug\CBfc_String8.o Debug\CBfc_Value.o Debug\character.o Debug\Rect2dU.o  \
		Debug\Size2dU.o  

ALL_RELEASE_OBJ = Release\Bfc_DebugStatic.o Release\CBfc_2dRect.o Release\CBfc_2dSize.o Release\CBfc_Angle.o  \
		Release\CBfc_Array.o Release\CBfc_CompressionAlgorythm.o Release\CBfc_Distance.o Release\CBfc_DynamicLink.o  \
		Release\CBfc_Exception.o Release\CBfc_File.o Release\CBfc_Filename.o Release\CBfc_LinkedList.o  \
		Release\CBfc_MatrixDoubles.o Release\CBfc_PointSpace3d.o Release\CBfc_PointSpaceTime.o Release\CBfc_PointTime.o  \
		Release\CBfc_Range2d.o Release\CBfc_ReferencedAllocation.o Release\CBfc_ReferencedObject.o Release\CBfc_ReferencedPointer.o  \
		Release\CBfc_Registry.o Release\CBfc_Stream.o Release\CBfc_StreamSource.o Release\CBfc_String.o  \
		Release\CBfc_String8.o Release\CBfc_Value.o Release\character.o Release\Rect2dU.o  \
		Release\Size2dU.o  

SHELL=C:\Windows\System32\CMD.exe
VER=1
srcdir=../src
includes=../../include

LIBOUT=.
LIBINSTALL=\Users\Bill\Libraries

DEFS = -DWIN32 -DMINGW -DBFC_STATICLIB
# -DBFC_DLL

CCPP = gcc
INTELOPTIONS=-march=pentium3 -msse -mfpmath=sse
CPPFLAGS = $(INTELOPTIONS) -I$(srcdir) -I$(includes) $(DEFS)
CPPDEBUG = -g -O0 -D_DEBUG 

LINKER = ar
LINKEROPTIONS = rcs

DLL_LINKER = g++ -shared
DLL_LINKEROPTIONS = -o
#LINKEROPTIONS = --export-dynamic

DEBUG_NAME=BFC_mingw_d.a
RELEASE_NAME=BFC_mingw.a

DEBUG_NAME_DLL=BFC_mingw_d.dll
RELEASE_NAME_DLL=BFC_mingw.dll

build: create debug

all : create debug release

backup:
	programmer -b .

rebuild: clean all

clean :
	programmer -c
	del $(LIBOUT)\$(DEBUG_NAME)
	del $(LIBOUT)\$(RELEASE_NAME)

head:
	programmer -h ../header src/*.cpp
	programmer -h ../header src/*.h

create:
	programmer -mpg $(srcdir)

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
	del $(LIBINSTALL)/$(DEBUG_NAME)
	del $(LIBINSTALL)/$(RELEASE_NAME)




Debug\Bfc_DebugStatic.o : ../src\Bfc_DebugStatic.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\Bfc_DebugStatic.o ../src\Bfc_DebugStatic.cpp

Release\Bfc_DebugStatic.o : ../src\Bfc_DebugStatic.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\Bfc_DebugStatic.o ../src\Bfc_DebugStatic.cpp

Debug\CBfc_2dRect.o : ../src\CBfc_2dRect.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfc_2dRect.o ../src\CBfc_2dRect.cpp

Release\CBfc_2dRect.o : ../src\CBfc_2dRect.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfc_2dRect.o ../src\CBfc_2dRect.cpp

Debug\CBfc_2dSize.o : ../src\CBfc_2dSize.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfc_2dSize.o ../src\CBfc_2dSize.cpp

Release\CBfc_2dSize.o : ../src\CBfc_2dSize.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfc_2dSize.o ../src\CBfc_2dSize.cpp

Debug\CBfc_Angle.o : ../src\CBfc_Angle.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfc_Angle.o ../src\CBfc_Angle.cpp

Release\CBfc_Angle.o : ../src\CBfc_Angle.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfc_Angle.o ../src\CBfc_Angle.cpp

Debug\CBfc_Array.o : ../src\CBfc_Array.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfc_Array.o ../src\CBfc_Array.cpp

Release\CBfc_Array.o : ../src\CBfc_Array.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfc_Array.o ../src\CBfc_Array.cpp

Debug\CBfc_CompressionAlgorythm.o : ../src\CBfc_CompressionAlgorythm.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfc_CompressionAlgorythm.o ../src\CBfc_CompressionAlgorythm.cpp

Release\CBfc_CompressionAlgorythm.o : ../src\CBfc_CompressionAlgorythm.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfc_CompressionAlgorythm.o ../src\CBfc_CompressionAlgorythm.cpp

Debug\CBfc_Distance.o : ../src\CBfc_Distance.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfc_Distance.o ../src\CBfc_Distance.cpp

Release\CBfc_Distance.o : ../src\CBfc_Distance.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfc_Distance.o ../src\CBfc_Distance.cpp

Debug\CBfc_DynamicLink.o : ../src\CBfc_DynamicLink.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfc_DynamicLink.o ../src\CBfc_DynamicLink.cpp

Release\CBfc_DynamicLink.o : ../src\CBfc_DynamicLink.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfc_DynamicLink.o ../src\CBfc_DynamicLink.cpp

Debug\CBfc_Exception.o : ../src\CBfc_Exception.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfc_Exception.o ../src\CBfc_Exception.cpp

Release\CBfc_Exception.o : ../src\CBfc_Exception.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfc_Exception.o ../src\CBfc_Exception.cpp

Debug\CBfc_File.o : ../src\CBfc_File.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfc_File.o ../src\CBfc_File.cpp

Release\CBfc_File.o : ../src\CBfc_File.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfc_File.o ../src\CBfc_File.cpp

Debug\CBfc_Filename.o : ../src\CBfc_Filename.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfc_Filename.o ../src\CBfc_Filename.cpp

Release\CBfc_Filename.o : ../src\CBfc_Filename.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfc_Filename.o ../src\CBfc_Filename.cpp

Debug\CBfc_LinkedList.o : ../src\CBfc_LinkedList.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfc_LinkedList.o ../src\CBfc_LinkedList.cpp

Release\CBfc_LinkedList.o : ../src\CBfc_LinkedList.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfc_LinkedList.o ../src\CBfc_LinkedList.cpp

Debug\CBfc_MatrixDoubles.o : ../src\CBfc_MatrixDoubles.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfc_MatrixDoubles.o ../src\CBfc_MatrixDoubles.cpp

Release\CBfc_MatrixDoubles.o : ../src\CBfc_MatrixDoubles.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfc_MatrixDoubles.o ../src\CBfc_MatrixDoubles.cpp

Debug\CBfc_PointSpace3d.o : ../src\CBfc_PointSpace3d.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfc_PointSpace3d.o ../src\CBfc_PointSpace3d.cpp

Release\CBfc_PointSpace3d.o : ../src\CBfc_PointSpace3d.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfc_PointSpace3d.o ../src\CBfc_PointSpace3d.cpp

Debug\CBfc_PointSpaceTime.o : ../src\CBfc_PointSpaceTime.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfc_PointSpaceTime.o ../src\CBfc_PointSpaceTime.cpp

Release\CBfc_PointSpaceTime.o : ../src\CBfc_PointSpaceTime.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfc_PointSpaceTime.o ../src\CBfc_PointSpaceTime.cpp

Debug\CBfc_PointTime.o : ../src\CBfc_PointTime.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfc_PointTime.o ../src\CBfc_PointTime.cpp

Release\CBfc_PointTime.o : ../src\CBfc_PointTime.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfc_PointTime.o ../src\CBfc_PointTime.cpp

Debug\CBfc_Range2d.o : ../src\CBfc_Range2d.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfc_Range2d.o ../src\CBfc_Range2d.cpp

Release\CBfc_Range2d.o : ../src\CBfc_Range2d.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfc_Range2d.o ../src\CBfc_Range2d.cpp

Debug\CBfc_ReferencedAllocation.o : ../src\CBfc_ReferencedAllocation.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfc_ReferencedAllocation.o ../src\CBfc_ReferencedAllocation.cpp

Release\CBfc_ReferencedAllocation.o : ../src\CBfc_ReferencedAllocation.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfc_ReferencedAllocation.o ../src\CBfc_ReferencedAllocation.cpp

Debug\CBfc_ReferencedObject.o : ../src\CBfc_ReferencedObject.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfc_ReferencedObject.o ../src\CBfc_ReferencedObject.cpp

Release\CBfc_ReferencedObject.o : ../src\CBfc_ReferencedObject.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfc_ReferencedObject.o ../src\CBfc_ReferencedObject.cpp

Debug\CBfc_ReferencedPointer.o : ../src\CBfc_ReferencedPointer.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfc_ReferencedPointer.o ../src\CBfc_ReferencedPointer.cpp

Release\CBfc_ReferencedPointer.o : ../src\CBfc_ReferencedPointer.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfc_ReferencedPointer.o ../src\CBfc_ReferencedPointer.cpp

Debug\CBfc_Registry.o : ../src\CBfc_Registry.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfc_Registry.o ../src\CBfc_Registry.cpp

Release\CBfc_Registry.o : ../src\CBfc_Registry.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfc_Registry.o ../src\CBfc_Registry.cpp

Debug\CBfc_Stream.o : ../src\CBfc_Stream.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfc_Stream.o ../src\CBfc_Stream.cpp

Release\CBfc_Stream.o : ../src\CBfc_Stream.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfc_Stream.o ../src\CBfc_Stream.cpp

Debug\CBfc_StreamSource.o : ../src\CBfc_StreamSource.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfc_StreamSource.o ../src\CBfc_StreamSource.cpp

Release\CBfc_StreamSource.o : ../src\CBfc_StreamSource.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfc_StreamSource.o ../src\CBfc_StreamSource.cpp

Debug\CBfc_String.o : ../src\CBfc_String.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfc_String.o ../src\CBfc_String.cpp

Release\CBfc_String.o : ../src\CBfc_String.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfc_String.o ../src\CBfc_String.cpp

Debug\CBfc_String8.o : ../src\CBfc_String8.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfc_String8.o ../src\CBfc_String8.cpp

Release\CBfc_String8.o : ../src\CBfc_String8.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfc_String8.o ../src\CBfc_String8.cpp

Debug\CBfc_Value.o : ../src\CBfc_Value.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\CBfc_Value.o ../src\CBfc_Value.cpp

Release\CBfc_Value.o : ../src\CBfc_Value.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\CBfc_Value.o ../src\CBfc_Value.cpp

Debug\character.o : ../src\character.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\character.o ../src\character.cpp

Release\character.o : ../src\character.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\character.o ../src\character.cpp

Debug\Rect2dU.o : ../src\Rect2dU.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\Rect2dU.o ../src\Rect2dU.cpp

Release\Rect2dU.o : ../src\Rect2dU.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\Rect2dU.o ../src\Rect2dU.cpp

Debug\Size2dU.o : ../src\Size2dU.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) -o Debug\Size2dU.o ../src\Size2dU.cpp

Release\Size2dU.o : ../src\Size2dU.cpp 
		$(CCPP) -c $(CPPFLAGS) -o Release\Size2dU.o ../src\Size2dU.cpp
