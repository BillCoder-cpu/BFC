//*/
/*
					CBfcImage_Pixels.cpp : 
	
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
#include <BFC/BFCImage.h>

namespace CBfcImage
{

PixelBuffer::PixelBuffer()
	: m_offset (0)
{
	Set (NULL, 0);
}

PixelBuffer::PixelBuffer(Pixels *p_pixels, const UINT count)
	: m_offset (0)
{
	Set (p_pixels, count);
}

bool PixelBuffer::Iterate (Color &c)
{
	if (m_offset < m_count)
	{
		c =  m_Pixels[m_offset++];
		return true;
	}
	m_offset = 0;
	return false;
}

void PixelBuffer::Set (Pixels *p_pixels, const UINT count)
{
	if (p_pixels)
		m_Pixels = *p_pixels;
	m_count = count;
}

Pixels::Pixels()
	: m_ptr(NULL)
{
}

/**
 * 
 * @param ptr 
 * @param colorSpace 
 * @return 
 */
Pixels::Pixels(BYTE *ptr, const ColorSpace &colorSpace)
	: m_ptr (ptr)
	, m_colorSpace(colorSpace)
{
	m_BytesPerPixel = (m_colorSpace.GetBitsPerPixel()+7)/8;
}

/**
 * Fill data here 
 * @param SourceData 
 * @param AlphaData 
 * @param uPixelCount 
 */
void Pixels::MixPixels (Pixels *SourceData, unsigned char *AlphaData, UINT uPixelCount)
{
	while (uPixelCount--)
	{
		const unsigned char	ucMix = *AlphaData++;
		if (ucMix)
			Stav (Pixels::MixPixel (Color(Color::WHITE), **SourceData, ucMix));
		else
			++(*this);
		++(*SourceData);
	}
}

/**
 * 
 * @param c1 
 * @param c2 
 * @param cAlpha 
 * @return 
 */
Color Pixels::MixPixel (const Color &c1, const Color &c2, const unsigned char &ucAlpha)
{
	Color cRet(c2);
	
	return cRet;
}

/**
 * 
 * @param u_pixelCount 
 * @return 
 */
UINT Pixels::BytesRequiredToStore (const UINT u_pixelCount) const
{
	return m_colorSpace.BytesRequiredToStore(u_pixelCount);
}

void Pixels:: operator = (const Pixels &eq)
{
	m_ptr = eq.m_ptr;
	m_colorSpace = eq.m_colorSpace;
	m_BytesPerPixel = eq.m_BytesPerPixel;
}

/**
 * 
 * @return 
 */
Color	OVERRIDE Pixels::operator *() const
{
	Color	c;
	switch (m_colorSpace.GetColorSpace())
	{
		case ColorSpace::COLORSPACE_RGBA:
			c.CopyRGBA(m_ptr);
			break;
		case ColorSpace::COLORSPACE_RGB:
			c.CopyRGB(m_ptr);
			break;
		case ColorSpace::COLORSPACE_RGB16:
			{
				const unsigned short	*p_us = (unsigned short *)m_ptr;
				c.Set16bitRGB (*p_us);
			}
			break;
		case ColorSpace::COLORSPACE_BGRA:
			c.SetRGBA(m_ptr[2],m_ptr[1],m_ptr[0],m_ptr[3]);
			break;
		case ColorSpace::COLORSPACE_BGR:
			c.SetRGB(m_ptr[2],m_ptr[0],m_ptr[1]);
			break;
	}
	return c;
}

OVERRIDE Color	Pixels::operator[](const UINT offset) const
{
	Color	c;
	const UINT off = offset * m_BytesPerPixel;
	BYTEPTR		poff = m_ptr + off;
	switch (m_colorSpace.GetColorSpace())
	{
		case ColorSpace::COLORSPACE_RGBA:
			c.SetRGBA(*poff,poff[1],poff[2],poff[3]);
			break;
		case ColorSpace::COLORSPACE_RGB:
			c.SetRGB(*poff,poff[1],poff[2]);
			break;
		case ColorSpace::COLORSPACE_RGB16:
			{
				unsigned short	*p_us = (unsigned short *)(poff);
				c.Set16bitRGB (*p_us);
			}
			break;
		case ColorSpace::COLORSPACE_BGRA:
			c.SetRGBA(poff[2],poff[1],poff[0],poff[3]);
			break;
		case ColorSpace::COLORSPACE_BGR:
			c.SetRGB(poff[2],poff[0],poff[1]);
			break;
	}
	return c;
}

/**
 *   Store and advance given a color.
 * @param color 
 * @return 
 */
void Pixels::Stav (const Color &color)
{
	UINT	r,g,b,a;
	switch (m_colorSpace.GetColorSpace())
	{
		case ColorSpace::COLORSPACE_RGBA:
			color.SplitRGBA (r,g,b,a);
			m_ptr[0] = r;
			m_ptr[1] = g;
			m_ptr[2] = b;
			m_ptr[3] = a;
			break;
		case ColorSpace::COLORSPACE_BGRA:
			color.SplitRGBA (r,g,b,a);
			m_ptr[2] = r;
			m_ptr[1] = g;
			m_ptr[0] = b;
			m_ptr[3] = a;
			break;
		case ColorSpace::COLORSPACE_RGB:
			color.SplitRGB (r,g,b);
			m_ptr[0] = r;
			m_ptr[1] = g;
			m_ptr[2] = b;
			break;
		case ColorSpace::COLORSPACE_BGR:
			color.SplitRGB (r,g,b);
			m_ptr[2] = r;
			m_ptr[0] = g;
			m_ptr[1] = b;
			break;
		case ColorSpace::COLORSPACE_RGB16:
			*((unsigned short*)m_ptr) = color.GetAs16BitRGB();
			break;
	}
	++(*this);
}

void Pixels::StavZoomedLine(Pixels &pelSrc, UINT dest_ww, const double zoom)
{
	if (zoom == 1.0)
	{
		StavLine (pelSrc, dest_ww);
		return;
	}
	register float	dx=0;
	const float		inv_zoom = 1/zoom;
	if (zoom > 1)
	{
		Color c;
		UINT	showx = 0;
		UINT	source_ww = dest_ww/zoom;
		while (source_ww--)
		{
			c = *pelSrc;
			++pelSrc;
			dx += zoom;
			while (showx < (UINT)dx)
			{
				Stav(c);
				showx++;
			}
		}
		return;
	}
#if 1
	while (dest_ww--)
	{
		Stav(pelSrc[(UINT)dx]);
		dx += inv_zoom;
	}
#else
	while (dest_ww--)
	{
		Stav(*pelSrc);
		dx += inv_zoom;
		const int	i_dx = (int)dx;
		if (i_dx)
		{
			pelSrc += i_dx;
			dx -= i_dx;
		}
	}
#endif
}

void Pixels::StavLine(Pixels &pelSrc, UINT ww)
{
	if (m_colorSpace==pelSrc.m_colorSpace)
	{
		UINT	u_bytecount=BytesRequiredToStore(ww);
		memcpy (m_ptr, pelSrc.m_ptr, u_bytecount);
		m_ptr += u_bytecount;
		pelSrc.m_ptr += u_bytecount;
	} else
	{
// 		wprintf (_TXT("Staving %d pels, scpace %d frm scpace %d\n"),ww,m_colorSpace.GetColorSpace(), pelSrc.m_colorSpace.GetColorSpace());
		while (ww--)
		{
			Stav(*pelSrc);
			++pelSrc;
		}
	}
}

void Pixels::Fill(const Color &color, UINT ww)
{
	while (ww--)
		Stav(color);
}

void	OVERRIDE		Pixels::operator +=(const int i_inc)
{
	m_ptr += i_inc * m_BytesPerPixel;
}

void	OVERRIDE 	Pixels::operator ++()
{
	m_ptr += m_BytesPerPixel;
}

void	OVERRIDE 	Pixels::operator --()
{
	m_ptr -=m_BytesPerPixel;
}


}

