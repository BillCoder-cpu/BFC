#
#WINDOWSMakefile
#
#ThisistheWindowsMakefileforBFCImage
#
#Copyright(C)2004-2011byWilliamP.Foster,allrightsreserved
#
#
# Generated via Programmer, a programmer's utility.
#
DebugDir=Debug
ReleaseDir=Release

ALL_H = BitmapPipe.h CBfcImage.h CBfcImage_2dArrayPixel.h CBfcImage_Bitmap.h  \
		CBfcImage_Buffer.h CBfcImage_Chunker.h CBfcImage_Color.h CBfcImage_ColorSpace.h  \
		CBfcImage_Effect.h CBfcImage_Format.h CBfcImage_Format_BMP.h CBfcImage_Format_DJVU.h  \
		CBfcImage_Format_JPEG.h CBfcImage_Format_JPEG2000.h CBfcImage_Format_TIFF.h CBfcImage_Histogram.h  \
		CBfcImage_Image_Store.h CBfcImage_Info.h CBfcImage_Object.h CBfcImage_Pixels.h  \
		CBfcImage_Resolution.h CBfcImage_ScriptImage.h CBfcImage_Segment.h CBfcImage_Transform.h  \
		ddjvuapi.h FoxImage.h Palette.h  

ALL_CPP = ..\src\BitmapPipe.cpp ..\src\Bitmap_Alpha.cpp ..\src\CBfcImage.cpp ..\src\CBfcImage_2dArrayPixel.cpp  \
		..\src\CBfcImage_Bitmap.cpp ..\src\CBfcImage_Buffer.cpp ..\src\CBfcImage_Chunker.cpp ..\src\CBfcImage_Color.cpp  \
		..\src\CBfcImage_ColorSpace.cpp ..\src\CBfcImage_Format.cpp ..\src\CBfcImage_Format_BMP.cpp ..\src\CBfcImage_Format_DJVU.cpp  \
		..\src\CBfcImage_Format_JPEG.cpp ..\src\CBfcImage_Format_JPEG2000.cpp ..\src\CBfcImage_Histogram.cpp ..\src\CBfcImage_Image_Store.cpp  \
		..\src\CBfcImage_Pixels.cpp ..\src\CBfcImage_Resolution.cpp ..\src\CBfcImage_ScriptImage.cpp ..\src\CBfcImage_Segment.cpp  \
		..\src\CImgPipe.cpp ..\src\Palette.cpp  

ALL_OBJ = ..\src\BitmapPipe.o ..\src\Bitmap_Alpha.o ..\src\CBfcImage.o ..\src\CBfcImage_2dArrayPixel.o  \
		..\src\CBfcImage_Bitmap.o ..\src\CBfcImage_Buffer.o ..\src\CBfcImage_Chunker.o ..\src\CBfcImage_Color.o  \
		..\src\CBfcImage_ColorSpace.o ..\src\CBfcImage_Format.o ..\src\CBfcImage_Format_BMP.o ..\src\CBfcImage_Format_DJVU.o  \
		..\src\CBfcImage_Format_JPEG.o ..\src\CBfcImage_Format_JPEG2000.o ..\src\CBfcImage_Histogram.o ..\src\CBfcImage_Image_Store.o  \
		..\src\CBfcImage_Pixels.o ..\src\CBfcImage_Resolution.o ..\src\CBfcImage_ScriptImage.o ..\src\CBfcImage_Segment.o  \
		..\src\CImgPipe.o ..\src\Palette.o  

ALL_DEBUG_OBJ = $(DebugDir)\BitmapPipe.o $(DebugDir)\Bitmap_Alpha.o $(DebugDir)\CBfcImage.o $(DebugDir)\CBfcImage_2dArrayPixel.o  \
		$(DebugDir)\CBfcImage_Bitmap.o $(DebugDir)\CBfcImage_Buffer.o $(DebugDir)\CBfcImage_Chunker.o $(DebugDir)\CBfcImage_Color.o  \
		$(DebugDir)\CBfcImage_ColorSpace.o $(DebugDir)\CBfcImage_Format.o $(DebugDir)\CBfcImage_Format_BMP.o $(DebugDir)\CBfcImage_Format_DJVU.o  \
		$(DebugDir)\CBfcImage_Format_JPEG.o $(DebugDir)\CBfcImage_Format_JPEG2000.o $(DebugDir)\CBfcImage_Histogram.o $(DebugDir)\CBfcImage_Image_Store.o  \
		$(DebugDir)\CBfcImage_Pixels.o $(DebugDir)\CBfcImage_Resolution.o $(DebugDir)\CBfcImage_ScriptImage.o $(DebugDir)\CBfcImage_Segment.o  \
		$(DebugDir)\CImgPipe.o $(DebugDir)\Palette.o  

ALL_RELEASE_OBJ = $(ReleaseDir)\BitmapPipe.o $(ReleaseDir)\Bitmap_Alpha.o $(ReleaseDir)\CBfcImage.o $(ReleaseDir)\CBfcImage_2dArrayPixel.o  \
		$(ReleaseDir)\CBfcImage_Bitmap.o $(ReleaseDir)\CBfcImage_Buffer.o $(ReleaseDir)\CBfcImage_Chunker.o $(ReleaseDir)\CBfcImage_Color.o  \
		$(ReleaseDir)\CBfcImage_ColorSpace.o $(ReleaseDir)\CBfcImage_Format.o $(ReleaseDir)\CBfcImage_Format_BMP.o $(ReleaseDir)\CBfcImage_Format_DJVU.o  \
		$(ReleaseDir)\CBfcImage_Format_JPEG.o $(ReleaseDir)\CBfcImage_Format_JPEG2000.o $(ReleaseDir)\CBfcImage_Histogram.o $(ReleaseDir)\CBfcImage_Image_Store.o  \
		$(ReleaseDir)\CBfcImage_Pixels.o $(ReleaseDir)\CBfcImage_Resolution.o $(ReleaseDir)\CBfcImage_ScriptImage.o $(ReleaseDir)\CBfcImage_Segment.o  \
		$(ReleaseDir)\CImgPipe.o $(ReleaseDir)\Palette.o  

SRCBASE=\Sources
LIBINSTALL = \Libraries

SHELL=C:/Windows/System32/cmd.exe
VCINC="C:\Program Files\Microsoft Visual Studio 10.0\VC\include"
BFCINC=$(SRCBASE)\C++\Engines\BFC\include
BFCDIR=$(SRCBASE)\C++\Engines\BFC
CSDIR=$(SRCBASE)\cs

VER=1
srcdir=..\src
LIBOUT=.
FOXDIR=$(SRCBASE)\C++\Third-Party\fox-current
DJVU_DIR="C:\Program Files\DjVuZone\DjVuLibre\include"
includes=-I$(srcdir) -I../../include -I$(FOXDIR)/include -I$(DJVU_DIR)\libdjvu -I$(DL)\jpeg-6b
DEFS = -D WIN32 -D BFC_STATICLIB

CCPP = cl /std:c++17
CPPDEBUG = -D _DEBUG /Zi
#INTELOPTIONS=-march=pentium3 -msse -mfpmath=sse
CPPFLAGS = $(INTELOPTIONS) -I$(srcdir) $(includes) $(DEFS)

LINKER = lib
#LINKEROPTIONS = -r

build : create debug

all: check_headers create debug release

rebuild: clean all

backup:
	programmer -b .

create:
	if NOT EXIST Debug (mkdir Debug)
	if NOT EXIST Release (mkdir Release)
	programmer -mpw $(srcdir)

clean :
	programmer -c
	del $(LIBOUT)\BFCImage_d.lib
	del $(LIBOUT)\BFCImage.lib

head:
	programmer -h ..\..\header $(srcdir)\*.cpp
	programmer -h ..\..\header $(srcdir)\*.h

debug : $(LIBOUT)/BFCImage_d.lib

$(LIBOUT)/BFCImage_d.lib : $(ALL_DEBUG_OBJ)
	$(LINKER) $(LINKEROPTIONS) /OUT:$(LIBOUT)/BFCImage_d.lib $(ALL_DEBUG_OBJ)

release : $(LIBOUT)/BFCImage.lib

$(LIBOUT)/BFCImage.lib : $(ALL_RELEASE_OBJ)
	$(LINKER) $(LINKEROPTIONS) /OUT:$(LIBOUT)/BFCImage.lib $(ALL_RELEASE_OBJ)

install: installd release
	copy $(LIBOUT)\BFCImage.lib $(LIBINSTALL)

installd: debug
	copy $(LIBOUT)\BFCImage_d.lib $(LIBINSTALL)

uninstall:
	DEL -f $(LIBINSTALL)\BFCImage_d.lib
	DEL -f $(LIBINSTALL)\BFCImage.lib

check_headers : $(ALL_H)
	$(CCPP) -E $(CPPFLAGS) ../include/BFCImage.h > junk

convert : 
	skipper -i $(BFCINC);$(VCINC) $(DEFS) -s $(BFCDIR)\BFCImage\src -d $(CSDIR)\Engines\ElImage\src "*.cpp"




$(DebugDir)\BitmapPipe.o : ..\src\BitmapPipe.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\BitmapPipe.o ..\src\BitmapPipe.cpp

$(ReleaseDir)\BitmapPipe.o : ..\src\BitmapPipe.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\BitmapPipe.o ..\src\BitmapPipe.cpp

$(DebugDir)\Bitmap_Alpha.o : ..\src\Bitmap_Alpha.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\Bitmap_Alpha.o ..\src\Bitmap_Alpha.cpp

$(ReleaseDir)\Bitmap_Alpha.o : ..\src\Bitmap_Alpha.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\Bitmap_Alpha.o ..\src\Bitmap_Alpha.cpp

$(DebugDir)\CBfcImage.o : ..\src\CBfcImage.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\CBfcImage.o ..\src\CBfcImage.cpp

$(ReleaseDir)\CBfcImage.o : ..\src\CBfcImage.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\CBfcImage.o ..\src\CBfcImage.cpp

$(DebugDir)\CBfcImage_2dArrayPixel.o : ..\src\CBfcImage_2dArrayPixel.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\CBfcImage_2dArrayPixel.o ..\src\CBfcImage_2dArrayPixel.cpp

$(ReleaseDir)\CBfcImage_2dArrayPixel.o : ..\src\CBfcImage_2dArrayPixel.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\CBfcImage_2dArrayPixel.o ..\src\CBfcImage_2dArrayPixel.cpp

$(DebugDir)\CBfcImage_Bitmap.o : ..\src\CBfcImage_Bitmap.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\CBfcImage_Bitmap.o ..\src\CBfcImage_Bitmap.cpp

$(ReleaseDir)\CBfcImage_Bitmap.o : ..\src\CBfcImage_Bitmap.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\CBfcImage_Bitmap.o ..\src\CBfcImage_Bitmap.cpp

$(DebugDir)\CBfcImage_Buffer.o : ..\src\CBfcImage_Buffer.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\CBfcImage_Buffer.o ..\src\CBfcImage_Buffer.cpp

$(ReleaseDir)\CBfcImage_Buffer.o : ..\src\CBfcImage_Buffer.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\CBfcImage_Buffer.o ..\src\CBfcImage_Buffer.cpp

$(DebugDir)\CBfcImage_Chunker.o : ..\src\CBfcImage_Chunker.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\CBfcImage_Chunker.o ..\src\CBfcImage_Chunker.cpp

$(ReleaseDir)\CBfcImage_Chunker.o : ..\src\CBfcImage_Chunker.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\CBfcImage_Chunker.o ..\src\CBfcImage_Chunker.cpp

$(DebugDir)\CBfcImage_Color.o : ..\src\CBfcImage_Color.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\CBfcImage_Color.o ..\src\CBfcImage_Color.cpp

$(ReleaseDir)\CBfcImage_Color.o : ..\src\CBfcImage_Color.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\CBfcImage_Color.o ..\src\CBfcImage_Color.cpp

$(DebugDir)\CBfcImage_ColorSpace.o : ..\src\CBfcImage_ColorSpace.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\CBfcImage_ColorSpace.o ..\src\CBfcImage_ColorSpace.cpp

$(ReleaseDir)\CBfcImage_ColorSpace.o : ..\src\CBfcImage_ColorSpace.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\CBfcImage_ColorSpace.o ..\src\CBfcImage_ColorSpace.cpp

$(DebugDir)\CBfcImage_Format.o : ..\src\CBfcImage_Format.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\CBfcImage_Format.o ..\src\CBfcImage_Format.cpp

$(ReleaseDir)\CBfcImage_Format.o : ..\src\CBfcImage_Format.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\CBfcImage_Format.o ..\src\CBfcImage_Format.cpp

$(DebugDir)\CBfcImage_Format_BMP.o : ..\src\CBfcImage_Format_BMP.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\CBfcImage_Format_BMP.o ..\src\CBfcImage_Format_BMP.cpp

$(ReleaseDir)\CBfcImage_Format_BMP.o : ..\src\CBfcImage_Format_BMP.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\CBfcImage_Format_BMP.o ..\src\CBfcImage_Format_BMP.cpp

$(DebugDir)\CBfcImage_Format_DJVU.o : ..\src\CBfcImage_Format_DJVU.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\CBfcImage_Format_DJVU.o ..\src\CBfcImage_Format_DJVU.cpp

$(ReleaseDir)\CBfcImage_Format_DJVU.o : ..\src\CBfcImage_Format_DJVU.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\CBfcImage_Format_DJVU.o ..\src\CBfcImage_Format_DJVU.cpp

$(DebugDir)\CBfcImage_Format_JPEG.o : ..\src\CBfcImage_Format_JPEG.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\CBfcImage_Format_JPEG.o ..\src\CBfcImage_Format_JPEG.cpp

$(ReleaseDir)\CBfcImage_Format_JPEG.o : ..\src\CBfcImage_Format_JPEG.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\CBfcImage_Format_JPEG.o ..\src\CBfcImage_Format_JPEG.cpp

$(DebugDir)\CBfcImage_Format_JPEG2000.o : ..\src\CBfcImage_Format_JPEG2000.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\CBfcImage_Format_JPEG2000.o ..\src\CBfcImage_Format_JPEG2000.cpp

$(ReleaseDir)\CBfcImage_Format_JPEG2000.o : ..\src\CBfcImage_Format_JPEG2000.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\CBfcImage_Format_JPEG2000.o ..\src\CBfcImage_Format_JPEG2000.cpp

$(DebugDir)\CBfcImage_Histogram.o : ..\src\CBfcImage_Histogram.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\CBfcImage_Histogram.o ..\src\CBfcImage_Histogram.cpp

$(ReleaseDir)\CBfcImage_Histogram.o : ..\src\CBfcImage_Histogram.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\CBfcImage_Histogram.o ..\src\CBfcImage_Histogram.cpp

$(DebugDir)\CBfcImage_Image_Store.o : ..\src\CBfcImage_Image_Store.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\CBfcImage_Image_Store.o ..\src\CBfcImage_Image_Store.cpp

$(ReleaseDir)\CBfcImage_Image_Store.o : ..\src\CBfcImage_Image_Store.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\CBfcImage_Image_Store.o ..\src\CBfcImage_Image_Store.cpp

$(DebugDir)\CBfcImage_Pixels.o : ..\src\CBfcImage_Pixels.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\CBfcImage_Pixels.o ..\src\CBfcImage_Pixels.cpp

$(ReleaseDir)\CBfcImage_Pixels.o : ..\src\CBfcImage_Pixels.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\CBfcImage_Pixels.o ..\src\CBfcImage_Pixels.cpp

$(DebugDir)\CBfcImage_Resolution.o : ..\src\CBfcImage_Resolution.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\CBfcImage_Resolution.o ..\src\CBfcImage_Resolution.cpp

$(ReleaseDir)\CBfcImage_Resolution.o : ..\src\CBfcImage_Resolution.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\CBfcImage_Resolution.o ..\src\CBfcImage_Resolution.cpp

$(DebugDir)\CBfcImage_ScriptImage.o : ..\src\CBfcImage_ScriptImage.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\CBfcImage_ScriptImage.o ..\src\CBfcImage_ScriptImage.cpp

$(ReleaseDir)\CBfcImage_ScriptImage.o : ..\src\CBfcImage_ScriptImage.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\CBfcImage_ScriptImage.o ..\src\CBfcImage_ScriptImage.cpp

$(DebugDir)\CBfcImage_Segment.o : ..\src\CBfcImage_Segment.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\CBfcImage_Segment.o ..\src\CBfcImage_Segment.cpp

$(ReleaseDir)\CBfcImage_Segment.o : ..\src\CBfcImage_Segment.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\CBfcImage_Segment.o ..\src\CBfcImage_Segment.cpp

$(DebugDir)\CImgPipe.o : ..\src\CImgPipe.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\CImgPipe.o ..\src\CImgPipe.cpp

$(ReleaseDir)\CImgPipe.o : ..\src\CImgPipe.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\CImgPipe.o ..\src\CImgPipe.cpp

$(DebugDir)\Palette.o : ..\src\Palette.cpp 
		$(CCPP) -c $(CPPFLAGS) $(CPPDEBUG) /Fo$(DebugDir)\Palette.o ..\src\Palette.cpp

$(ReleaseDir)\Palette.o : ..\src\Palette.cpp 
		$(CCPP) -c $(CPPFLAGS) /Fo$(ReleaseDir)\Palette.o ..\src\Palette.cpp
