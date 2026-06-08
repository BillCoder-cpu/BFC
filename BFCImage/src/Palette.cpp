//*/
/*
					Palette.cpp : 
	
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
/*
	Palette.cpp : Generation of an optimized palette.
		
		
		
		Todo:
		
		  now generates for 256 colors.
		optimize if fewer colors are requested!
*/
#include <BFC/BFCImage.h>
#include <stdlib.h>


namespace CBfcImage
{

PaletteCounter::PaletteCounter (const Palette *p_palette)
	: Palette (p_palette)
{
}

void PaletteCounter::IncrementSample(const UINT uColor)
{
	Color c;
	c.CopyRGB((BYTEPTR)&uColor);
	const UINT	uIndex = ColorToIndex(c);
	m_Occurance[uIndex] += 1;
}

bool PaletteCounter::GetPrimaryColor(Color &c) const
{
	UINT	uPrimaryIndex=0, uPrimaryCount=0;
	for (UINT u=0;u<GetNumberOfColors();u++)
	{
		if (uPrimaryCount < m_Occurance[u])
		{
			uPrimaryCount = m_Occurance[u];
			uPrimaryIndex = u;
		}
	}
	if (uPrimaryCount == 0)
		return false;
	c = GetColor(uPrimaryIndex);
	return true;
}



///--------------------------------------------------------------------------------
		
Palette::Palette()
	: m_uColorCount(0)
{
}

Palette::Palette(const Palette *p_paldup)
	: m_uColorCount(0)
{
	if (p_paldup)
	{
		m_uColorCount = p_paldup->m_uColorCount;
		for (int i=0;i<m_uColorCount;i++)
			m_uColors[i] = p_paldup->m_uColors[i];
	}
}

Palette *Palette::Dup() const
{
	return new Palette (this);
}

UINT Palette :: ColorToIndex (const Color &c) const
{
	UINT	uIndex=0, uCloseness=0xffffffff;
	for (UINT u=0;u<m_uColorCount;u++)
	{
		UINT	uClose = c.Closeness(GetColor(u));
		if (uCloseness > uClose)
		{
			uIndex = u;
			if (uClose == 0)		/// found exact match, no need to look further
				break;
			uCloseness = uClose;
		}
	}
	return uIndex;
}

Color	Palette :: GetColor (const UINT uIndex) const
{
	Color c;
	c.CopyRGB ((BYTEPTR)&m_uColors[uIndex]);
	return c;
}

void Palette :: GetColor (const UINT uIndex, Color &c) const
{
	c.CopyRGB ((BYTEPTR)&m_uColors[uIndex]);
}

bool Palette::Generate(const Bitmap *pBmp,const UINT uPalsize, const CBfc::Rect2dU *pRect)
{
	m_uColorCount = uPalsize;
	return GeneratePalette (pBmp, m_uColors, m_uColorCount, pRect);
}

unsigned long	*Occurance;

/// qsort comparison function 
int fPalsort ( const void *arg1, const void *arg2 )
{
	return Occurance[*((unsigned short*)arg2)] - Occurance[*((unsigned short*)arg1)];
}

bool GeneratePalette (const Bitmap *pBmp,UINT *palFill,const UINT uPalsize, const CBfc::Rect2dU *pRect)
{
	const UINT			SPECIFIC = 256;		// change to 192 to cover all areas of color, even if not represented in the image.
	
	if ((Occurance = new unsigned long[32768])) 
	{
		memset (Occurance, 0, 32768*sizeof(long));
	
		BitmapPipe		pipe(pBmp,pRect);
		 /// ask for our colors in 15 bit
		pipe.SetColorSpace (ColorSpace(ColorSpace::COLORSPACE_RGB16)); 
		PixelBuffer	pbuf;
		while (pipe.Iterate(pbuf))
		{
			Color c;
			while (pbuf.Iterate(c))
					Occurance[c.GetAs16BitRGB()] += 1;
		}
		/// Occurance is now filled with counts of matches with every color to 16 bits
// 
// 	Find about the top 192 most common colors, and have palette values for them.
// 
		unsigned short		Selection[256];
		unsigned long		iLowbar = 0xffffffff;
		unsigned short		index, i;
		for (index = 0; index < SPECIFIC; index++) 
		{
			Selection[index]=index;
			if (Occurance[index] < iLowbar)
				iLowbar = Occurance[index];
		}
		for (; index < 32768; index++) 
		{
			if (Occurance[index] > iLowbar)
			{
				unsigned long	ilb=0xffffffff;
				for (i = 0; i < SPECIFIC; i++) 
				{
					if (Occurance[Selection[i]] == iLowbar)
					{		/// replace a low match
						Selection[i] = index;
						break;
					}
						/// record new low
					if (Occurance[Selection[i]] < ilb)
						ilb = Occurance[Selection[i]];
				}
					/// keep looking for new low
				for (;i < SPECIFIC; i++)
					if (Occurance[Selection[i]] < ilb)
						ilb = Occurance[Selection[i]];
				iLowbar = ilb;		/// New low
			}
		}
		
		// Sort it so that the most common color are at the 'top'
 		qsort (Selection,SPECIFIC,sizeof(unsigned short),fPalsort);
/*
		unsigned long		iHighest = 0, highColor=0;
		for (i=0;i<200;i++)
			if (Occurance[Selection[i]] > iHighest)
			{
				iHighest = Occurance[Selection[i]];
				highColor = i;
			}
*/	

if (SPECIFIC == 192)
{
// 	Then, with the other 64 colors, make sure all color 'slots' are represented well.
		UINT	r,g,b;
		for (r=0;r<4;r++) for (g=0;g<4;g++) for (b=0;b<4;b++)
		{
			i = (r<<4) + (g<<2) + b;
			Selection[SPECIFIC + i] = (r << 13) + (g<<8) | (b << 3);
		}
}

/*					Older code ------------>
		// Now we have a palette of the 256 most common colors (Represented by shorts - 16 bit)
		if (uPalsize == 256) {
			// Go in, and make sure that we have represented all of the types of colors.
			int	iSaveSpace = 0;		// Will go 0-63.
			for (iRed = 0; iRed < 32; iRed += 8)
				for (iGreen = 0; iGreen < 32; iGreen += 8)
					for (iBlue = 0; iBlue < 32; iBlue += 8) {
						iIndex = (iRed << 10) | (iGreen << 5) | iBlue;
	// If something similar to this index is not already in the top of the table, add it.
#define	pxlMASK 0x6318
						for (i = 64; i < 256; i++) {
							if ( (Selection[i] & pxlMASK) == iIndex )
								break;
						}
						if (i == 256) {		// Not found, add it in
							Selection[iSaveSpace] = iIndex;
						}
						iSaveSpace++;  // goes up to 64
					}
		}
*/
		delete Occurance;

		// Fill in the RGB integer based colormap from the sequence of shorts
		unsigned char *ucp = (unsigned char *)&palFill[0];
		for (i=0; i < uPalsize; i++) 
		{
			*ucp++ = (Selection[i] >> 7) & 0xf8;
			*ucp++ = (Selection[i] >> 2) & 0xf8;
			*ucp++ = (Selection[i] & 0x1f) << 3;
			*ucp++ = 0;
		}
		return TRUE;
	}
	return FALSE;
}

}



