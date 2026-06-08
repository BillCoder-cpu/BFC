//*/
/*
					Bitmap_Alpha.cpp : 
	
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
/***********************************************************************************************/
/***********************************************************************************************/
/***********************************************************************************************/

#include <BFC/BFCImage.h>

namespace CBfcImage
{

	using namespace CBfc;

Bitmap_Alpha :: Bitmap_Alpha ()
{
	m_colorSpace = ColorSpace (ColorSpace::COLORSPACE_GRAY);
}

Bitmap_Alpha :: Bitmap_Alpha (const CBfc::Size2dU &size)
	: Bitmap(size, ColorSpace (ColorSpace::COLORSPACE_GRAY))
{
}

Bitmap_Alpha :: Bitmap_Alpha (const Bitmap_Alpha *pDupAlpha)
{
	*this = *pDupAlpha;
}

Bitmap_Alpha *Bitmap_Alpha::Dup() const
{
	return  new Bitmap_Alpha(this);
}

void Bitmap_Alpha::operator = (const Bitmap_Alpha &bmpAlpha)
{
	*((Bitmap*)this) = *((Bitmap*)&bmpAlpha);
}

void Bitmap_Alpha::operator |= (const Bitmap_Alpha &bmpAlpha)
{
	const Rect2dU	r = m_rectSize + bmpAlpha.m_rectSize;
	Enlarge (r);
	const Point2dU	offset = bmpAlpha.m_rectSize.TopLeft() - r.TopLeft();
		Point2dU	pos(0,0);

	Size2dU	srcSize;
	bmpAlpha.GetSize(srcSize);

	do {
/// 		or the data together.
		UINT	srcW = srcSize.GetX();
		BYTE	*pSrc = bmpAlpha.ReferenceBitPtr (pos, srcW);
		BYTE	*pDst = ReferenceBitPtr (pos+offset, srcW);
		while (srcW--)
			*pDst++ |= *pSrc++;
	} while (pos.IterateY(srcSize));
}

UINT Bitmap_Alpha :: operator [] (const Position2dU &pos) const
{
	unsigned char *p = (unsigned char *)m_p_pixelArray2d->GetPtr (pos, 1);
	return  (UINT)(*p);
}

unsigned char Bitmap_Alpha :: Edge (const CBfc::Position2dU &pos) const
{
	if ((*this)[pos] > 0x10)
		return AdjacentOff(pos);
	return 0;
}

unsigned char Bitmap_Alpha::AdjacentOn (const Position2dU &pos) const
{
	return AnAdjacentIs (pos, 1, 1);
}

unsigned char Bitmap_Alpha::AdjacentOff (const Position2dU &pos) const
{
	return AnAdjacentIs (pos, 0, 1); //0x10);
}

unsigned char Bitmap_Alpha::AnAdjacentIs (const Position2dU &pos, const bool b_aboveThreshold, const unsigned char ucThreshold) const
{
	int	xoff = -1, yoff=-1;
	UINT	look_width=3, look_height=3;
	if (pos.GetX()==0)
	{
		look_width=2;
		xoff++;
	}
	if (pos.GetX() == m_rectSize.Width()-1)
		look_width--;
	
	if (pos.GetY() == 0)
	{
		look_height=2;
		yoff++;
	}
	if (pos.GetY() == m_rectSize.Height()-1)
		look_height--;

	Position2dU testPos(pos + Size2dU(xoff,yoff));		
	while (look_height--)
	{
		unsigned char *p = (unsigned char *)m_p_pixelArray2d->GetPtr (testPos, look_width);
		UINT	x;
		if (b_aboveThreshold)
		{
			for (x=0;x<look_width;x++)
				if (p[x] > ucThreshold) return p[x];
		} else
		{
			for (x=0;x<look_width;x++)
				if (*p++ < ucThreshold) return 1;
		}
		testPos.IncrementY();
	}	
	return 0;
}


void Bitmap_Alpha::Set(const CBfc::Position2dU &pos, unsigned char value)
{
	unsigned char *p = (unsigned char *)m_p_pixelArray2d->GetPtr (pos, 1);
	*p = value;
}


bool Bitmap_Alpha :: IsBlankLine(const UINT line) const
{
	UINT	w = m_rectSize.Width();
	BYTE	*pSrc = ReferenceBitPtr (0, line, w);
	while (w--)
		if (*pSrc++)
			return false;
	return true;
}

/**
 * 
 * @param line 
 * @param l 
 * @param r 
 * @return true if the line is blank
 */
bool Bitmap_Alpha :: RangeOfZeros(const UINT line, int &l, int &r)
{
	bool bBlank = true;
	
	l = r = -1;
	const UINT	w = m_rectSize.Width();
	
	BYTE    *pDst, *pSav;
	pDst = pSav = ReferenceBitPtr (0, line, w);
	UINT x;
	for (x=0;x<w;x++)
	{
		if (*pDst++)
		{
			l = x;
			bBlank = false;
			break;
		}
	}
	if (!bBlank) 
	{
		x = w-1;
		pDst = pSav + x;
		for (;x>l;x--)
		{
			if (*pDst--)
			{
				r = x;
				break;
			}
		}
		if (r==-1)
			r = l;
	}
	DeReferenceBitPtr (pSav);
	return bBlank;
}
/**
 * 
 *  New Position of Bitmap is set -  receives the offset from zero of the shrunken item.
 * @return - true if size is changed.
 */
bool Bitmap_Alpha :: Shrink ()
{
	const Size2dU	size(m_rectSize.GetSize());
	const UINT		height = size.GetY();
			
	UINT	line = 0;
	UINT	top, bottom;
	UINT	left = size.GetX(), right=0;
	int	l, r;
	
	for (line=0; line < height; line++)		// 	find the top
		if (!IsBlankLine(line))
			break;
	top = line;
	
	for (line=height-1; line > top; line--)	// 	find the bottom
		if (!IsBlankLine(line))
			break;
	bottom = line;
	
	for (line=top; line <= bottom; line++)
	{
		if (!RangeOfZeros (line, l, r))
		{
			if (l < left) left = l;
			if (r > right) right = r;
		}
	}
	
	const Rect2dU chunk(left, top, right-left+1, bottom-top+1);
	crop (chunk);
	return false;
}

}
