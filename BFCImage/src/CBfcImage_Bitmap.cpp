//*/
/*
					CBfcImage_Bitmap.cpp : 
	
		This source file is part of the BFC Engine.
		
	Author: William P. Foster (bill@software0imagination.com)

// SPDX-License-Identifier: LGPL-3.0-or-later
// Copyright (C) 2026 William P. Foster
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

//*/

#include "BFC/BFCImage.h"

namespace CBfcImage
{

using namespace CBfc;

Thing2d::Thing2d()
	: m_Layer(0)
	{
	}

void Thing2d::operator = (const Thing2d &src)
{
	m_Name = src.m_Name;
	m_Layer = src.m_Layer;
	m_rectSize = src.m_rectSize;
}

/**
 * 
 * @return 
 */
Bitmap::Bitmap ()
	: m_p_pixelArray2d(NULL)
	, m_p_palette(NULL)
	, m_p_Alpha(NULL)
{
}

Bitmap::Bitmap(const Size2dU &size, const ColorSpace &colorSpace, Color *p_BackgroundColor)
	: m_p_pixelArray2d(NULL)
	, m_p_palette(NULL)
	, m_p_Alpha(NULL)
{
	bool bOK = Allocate (colorSpace, size);
//	if (p_BackgroundColor)
// 		Fill (p_BackgroundColor);
}

/**
 * 
 * @return 
 */
Bitmap::~Bitmap ()
{
	Release ();
}


//CBfcImage_Bitmap *CBfcImage_Bitmap::Dup()
//{
//}

/**
 * 
 * @return 
 */
bool Bitmap::Release ()
{
    BFC_RELEASE (m_p_pixelArray2d);
    BFC_RELEASE (m_p_palette);
    BFC_RELEASE (m_p_Alpha);
    return true;
}


/**
 * 
 * @param colorSpace 
 * @param rect_Size 
 * @return 
 */
bool Bitmap::Allocate (const ColorSpace &colorSpace, const Size2dU &size)
{
    if (Release ())
    {
        m_rectSize.SetSize (size);
        m_colorSpace = colorSpace;
        m_p_pixelArray2d = new Image_2dArrayPixel(size,colorSpace);
        return true;
    }
    return false;
}

bool Bitmap::Enlarge(const Rect2dU &rect)
{
	m_p_pixelArray2d->Enlarge(rect.GetSize());
	m_rectSize = rect;
	return false;
}


Color Bitmap :: operator [] (const Position2dU &pos) const
{
	BYTEPTR p = m_p_pixelArray2d->GetPtr (pos, 1);
	Pixels pxls(p, GetColorSpace());
	return *pxls;
}

void Bitmap :: operator = (const Bitmap &bmp)
{
	Release();
	
	*((Thing2d*)this) = *((Thing2d*)&bmp);
	m_colorSpace = bmp.m_colorSpace;
	m_resolutionX = bmp.m_resolutionX;
	m_resolutionY = bmp.m_resolutionY;
	m_p_pixelArray2d = bmp.m_p_pixelArray2d->Dup();
	m_p_palette = bmp.m_p_palette->Dup();
}

/**
 * 
 * @param u_bitsPerPixel 
 * @return 
 */
UINT Bitmap::CalculateEffectiveBits (const UINT u_bitsPerPixel)
{
    if (u_bitsPerPixel > 8)
    {
        if (u_bitsPerPixel < 16)
		return 16;
    }
    return u_bitsPerPixel;
}

/**
 * 		Sets the bits inside our allocated bitmap;
 * @param srcBits 
 * @param u_x 
 * @param u_y 
 * @param u_w 
 * @param u_h 
 * @param u_pitch 
 * @return 
 */
bool Bitmap:: SetBits (const BYTE *srcBits, const UINT u_x, const UINT u_y, const UINT u_w, const UINT u_h, const UINT u_pitch)
{
	UINT		u_ty, u_bottom = u_y + u_h;
    const UINT	ubytesPerLine = m_p_pixelArray2d->BytesRequiredToStore (u_w);
    const BYTE	*pSrc = srcBits;

    for (u_ty = u_y; u_ty < u_bottom; u_ty++, pSrc += u_pitch)
    {
        BYTE    *pDst = ReferenceBitPtr (u_x, u_ty, u_w);
        memcpy (pDst, pSrc, ubytesPerLine);
        DeReferenceBitPtr (pDst);
    }
    return true;
}

bool Bitmap::GetRectangle(BYTE *destPixels, const Size2dU &Size, const Position2dU &Origin, const ColorSpace &destCSpace) const
{
	const UINT bytecount = destCSpace.BytesRequiredToStore(Size.GetX());
	for (UINT l=Size.GetY();l>0;l--)
	{
		if (!GetScanline(destPixels, Origin.GetX(),Origin.GetY()+l, Size.GetX(), destCSpace))
			return false;
		destPixels += bytecount;
	}
	return true;
}

/**
 *  Convert a line from our bitmap into the requested colorspace.
 * @param pixelData 
 * @param u_x 
 * @param u_y 
 * @param ww 
 * @param cspace 
 * @return 
 */
bool Bitmap::GetScanline (BYTE *pixelData, const UINT u_x, const UINT u_y, const UINT ww, const ColorSpace &cspace) const
{
	BYTE *datasource = ReferenceBitPtr (u_x, u_y,ww);
	if (!datasource)
		return false;
	if (cspace==GetColorSpace())		// Optimization for equal colorspaces.
	{
		const UINT copybytes = cspace.BytesRequiredToStore(ww);
		memcpy (pixelData, datasource, copybytes);
	} else
	{
		Pixels	pelSrc(datasource, GetColorSpace());
		Pixels	pelDst((BYTE*)pixelData, cspace);
		
		pelDst.StavLine(pelSrc,ww);
	}	
	DeReferenceBitPtr (datasource);
	return true;
}

/**
 * 
 * @param destPixels 
 * @param destSize 
 * @param sourceOrigin 
 * @param zoom 
 * @param destCSpace 
 * @return 
 */
bool Bitmap::GetZoomedRectangle(BYTE *destPixels, const Size2dU &destSize, const Position2dU &sourceOrigin, const double zoom, const ColorSpace &destCSpace) const
{
	return false;
}

/**
 * 
 * @param destPixels 
 * @param source_pos 
 * @param dest_ww 
 * @param zoom 
 * @param cspace 
 * @return 
 */
bool Bitmap::GetZoomedScanlines (BYTE *destPixels, const Position2dU &source_pos, const Size2dU &dest_size, const double zoom, const ColorSpace &cspace) const
{
	const UINT bytecount = cspace.BytesRequiredToStore(dest_size.GetX());
	for (UINT l=0;l<dest_size.GetY();l++)
	{
		const Position2dU	pos(source_pos + Position2dU(0,(UINT)(l/zoom)));
		
		if (!GetZoomedScanline(destPixels, pos, dest_size.GetX(), zoom, cspace))
			return false;
		destPixels += bytecount;
	}
	return true;
}

bool Bitmap::GetZoomedScanline (BYTE *destPixels, const Position2dU &source_pos, const UINT dest_ww, const double zoom, const ColorSpace &cspace) const
{
	UINT	source_ww = (UINT)(dest_ww / zoom)+1;
	
	Size2dU	bmpSize;
	GetSize(bmpSize);
	if (source_pos.GetY() >= bmpSize.GetY() || source_pos.GetX() >= bmpSize.GetX())
	{			/// make sure we are in range
		Pixels	pelDst((BYTE*)destPixels, cspace);
		pelDst.Fill(Color(Color::WHITE), dest_ww);
		return true;
	}
		
	bmpSize -= source_pos;
	const UINT	max_source_ww = bmpSize.GetX();

	UINT	fill_ww = dest_ww;
	if (source_ww > max_source_ww)
	{
		source_ww = max_source_ww;
		fill_ww = (UINT)(source_ww * zoom);
	}
	
	BYTE *datasource = ReferenceBitPtr (source_pos,source_ww);
	if (!datasource)
		return false;

// 	wprintf (_TXT("  Bmp ref at %d %d of %d pels to %d wide.\n"), source_pos.GetX(),source_pos.GetY(), source_ww, fill_ww);
	
	Pixels	pelSrc(datasource, GetColorSpace());
	Pixels	pelDst(destPixels, cspace);
	pelDst.StavZoomedLine(pelSrc,fill_ww,zoom);
	if (fill_ww < dest_ww)
		pelDst.Fill(Color(Color::WHITE), dest_ww-fill_ww);
	DeReferenceBitPtr (datasource);
	return true;
}

/**
 * 
 * @param pixelData 
 * @param u_x 
 * @param u_y 
 * @param ww 
 * @param cspace 
 * @return 
 */
bool Bitmap::SetScanlines (BYTE *pixelData, const UINT u_x, const UINT u_y, const UINT ww, const ColorSpace &cspace, const UINT u_nLines)
{
	UINT	uLine;
	const UINT copybytes = cspace.BytesRequiredToStore(ww);

	for (uLine=0; uLine< u_nLines; uLine++, pixelData += copybytes)
	{
		BYTE *datadest = ReferenceBitPtr (u_x,u_y+uLine,ww);
		if (!datadest)
			return false;
		
		Pixels	pelSrc((BYTE*)pixelData, cspace);
		Pixels	pelDst(datadest, GetColorSpace());
	
		pelDst.StavLine(pelSrc,ww);
		
		DeReferenceBitPtr (datadest);
	}
	return true;
}

/**
 * 
 * @param pos 
 * @param u_getPixelCount 
 * @return 
 */
BYTE *Bitmap::ReferenceBitPtr (const Position2dU &pos, const UINT u_getPixelCount) const
{
	if (m_p_pixelArray2d == NULL)
		return NULL;
	UINT u_usePixelCount = u_getPixelCount;
	if (u_getPixelCount == 0)
	{
		CBfc::Size2dU	size;
		GetSize(size);
		u_usePixelCount = size.Product() - pos.GetX() - (pos.GetY() * size.GetX());
	}
    return  m_p_pixelArray2d->GetPtr (pos, u_usePixelCount);
}

/**
 * 
 * @param u_x 
 * @param u_y 
 * @param u_getPixelCount 
 * @return 
 */
BYTE *Bitmap::ReferenceBitPtr (const UINT u_x, const UINT u_y, const UINT u_getPixelCount) const
{
	return ReferenceBitPtr (Position2dU(u_x, u_y), u_getPixelCount);
}

/**
 * 
 * @param p 
 * @return 
 */
bool Bitmap::DeReferenceBitPtr (BYTE *p) const
{
//     return m_p_pixelArray2d->ReleasePtr (p);
	return true;
}

/**
 *   Given an alpha channel, Get a new bitmap from the existing consisting of the region
 * @param pAlpha 
 * @return 
 */
Bitmap *Bitmap::PickupSelection (Bitmap_Alpha *pAlpha,  Color *pBackgroundColor) const
{
	Size2dU	size1, size2;
	
	Position2dU	posAlpha;
	pAlpha->GetPosition (posAlpha);	
	pAlpha->GetSize(size1);
	GetSize (size2);
	Size2dU size = Size2dU::Minimum(size1, size2);
//   	BFC_TRACE (_TXT("Pickup size (%d,%d).\n"), size.GetX(), size.GetY());

	Bitmap *p_bmp = new Bitmap(size, GetColorSpace(), pBackgroundColor ? pBackgroundColor : &Color (Color::WHITE));
	p_bmp->DupAlpha (pAlpha);
	const UINT	uWidth = size.GetX();	//  Should use Image_Chunker or BitmapPipe
	Position2dU	pos(0,0);
	do 
	{
// 		BFC_TRACE (_TXT("  pickup at (%d,%d).\n"), (int)pos.GetX(), (int)pos.GetY());
		BYTE 		*palpha =  pAlpha->ReferenceBitPtr(pos, uWidth);
		
		BYTE 		*psource =  ReferenceBitPtr(pos + posAlpha, uWidth);
		Pixels		SourceData(psource, GetColorSpace());
		
		BYTE 		*pdest =  p_bmp->ReferenceBitPtr(pos, uWidth);
		Pixels		DestData (pdest, p_bmp->GetColorSpace());
		
		DestData.MixPixels (&SourceData, (unsigned char *)palpha, uWidth);
		
		p_bmp->DeReferenceBitPtr (pdest);
		DeReferenceBitPtr (psource);
		pAlpha->DeReferenceBitPtr (palpha);
		
	} while (pos.IterateY(size));
	return p_bmp;
}


OVERRIDE bool Bitmap :: crop(const CBfc::Rect2dU &chunk)
{
	m_p_pixelArray2d->crop (chunk);
	
	Position2dU pos;
	GetPosition(pos);
	const Position2dU posNew(pos + chunk.TopLeft());
	m_rectSize.Set (posNew, chunk.GetSize());

//	BFC_TRACE (_TXT("Crop to %d,%d,%d,%d\n"), posNew.GetX(), posNew.GetY(), chunk.GetSize().GetX(), chunk.GetSize().GetY());
	return true;
}

void Bitmap::GeneratePalette(UINT minColors)
{
	if (!m_p_palette)
		ReGeneratePalette(minColors);
}

void Bitmap::ReGeneratePalette(UINT minColors)
{
	BFC_RELEASE (m_p_palette);
	m_p_palette = new Palette();
	m_p_palette->Generate (this, minColors);
}

void	Bitmap::SetPalette(const Palette *p_palette)
{
	BFC_RELEASE(m_p_palette);
	m_p_palette = new Palette(p_palette);
}

void	Bitmap::SetAlpha(Bitmap_Alpha*pAlpha)
{
	BFC_RELEASE(m_p_Alpha);
	m_p_Alpha = pAlpha;
	m_p_Alpha->SetLayer(GetLayer());
}

void	Bitmap::DupAlpha(Bitmap_Alpha*pAlpha)
{
	SetAlpha(pAlpha->Dup());
}

OVERRIDE Bitmap_Alpha	*Bitmap::GetAlpha()
{
	return m_p_Alpha;
}

/// /////////////////////////////////////////////
/// Drawing functions start here, may want to split into seperate class.
///
bool	Bitmap::FillRectangle (const Color &col, const Rect2dU &r)
{
		
	Position2dU	pos(r.TopLeft());
	const UINT w = r.Width();
	do {
		BYTEPTR p = m_p_pixelArray2d->GetPtr (pos, w);
		Pixels pxls(p, GetColorSpace());
		pxls.Fill (col, w);
	} while (pos.IterateY(r));
	return true;
}

}



