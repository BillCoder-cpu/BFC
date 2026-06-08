//*/
/*
					CBfcImage_Histogram.cpp : 
	
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

using namespace CBfc;

namespace CBfcImage
{

Histogram::Histogram (const Bitmap *pBmp)
: m_pBmp(pBmp)
, m_b_beenRun(false)
{
}

void Histogram::ZeroMap()
{
	for (UINT x=0; x < 256; x++)
		m_Map[x] = 0;
}

// Find the midpoint, or average of the curve	
unsigned char Histogram::Average()
{
	UINT64	total=0, divisor=0;

	Run_Histogram();
	for (UINT x=0; x < 256; x++)
	{
		total += (UINT64)x * m_Map[x];
		divisor += m_Map[x];
	}
	if (divisor==0)
		return 0;
	return (unsigned char)(total / divisor);
}


HSL_Histogram::HSL_Histogram(const Bitmap *pBmp)
	: Histogram (pBmp)
{
}

void HSL_Histogram::ZeroMaps()
{
	for (UINT x=0; x < 256; x++)
	{
		m_HueMap[x] = 0;
		m_SaturationMap[x] = 0;
	}
	ZeroMap();
}

void HSL_Histogram::Run_Histogram (const Rect2dU *p_Rect)
{
	if (!m_b_beenRun)
	{
		CBfc::Rect2dU	rect;
		
		Position2dU	pos(0,0);
		if (p_Rect)
		{
			pos = p_Rect->TopLeft();
			rect.Set(*p_Rect);
		} else
		{
			Size2dU size;
			
			m_pBmp->GetSize (size);
			rect.SetSize(size);
		}
		
		ZeroMaps();
		ColorSpace	colorSpace;
		m_pBmp->GetColorSpace(colorSpace);
		do
		{
			UINT	ww = rect.Width();
			BYTE	*pData = m_pBmp->ReferenceBitPtr (pos,ww);
			Pixels	px(pData, colorSpace);
			for (UINT xx=0; xx<ww; xx++, ++px)
			{
				UINT	H,S,L;
				Color	c = *px;
				c.SplitHSL (H, S, L);
				m_Map[L] += 1;
				m_SaturationMap[S] += 1;
				m_HueMap[H] += 1;
			}
			m_pBmp->DeReferenceBitPtr (pData);
		} while (pos.IterateY(rect));
		
		m_b_beenRun = true;
	}
}


Brightness_Histogram::Brightness_Histogram(const Bitmap *pBmp)
: Histogram (pBmp)
{
}

void Brightness_Histogram::Run_Histogram (const Rect2dU *p_Rect)
{
	if (!m_b_beenRun)
	{
		CBfc::Size2dU	size;
		m_pBmp->GetSize (size);
		
		UINT	xx,yy,ww,hh;
		size.Get(ww,hh);
		
		ZeroMap();
		ColorSpace	colorSpace;
		m_pBmp->GetColorSpace(colorSpace);
		for (yy=0; yy<hh; yy++)
		{
			BYTE	*pData = m_pBmp->ReferenceBitPtr (0,yy,ww);
			Pixels	px(pData, colorSpace);
			for (xx=0; xx<ww; xx++, ++px)
			{
				Color c = *px;
				m_Map[c.GetBrightness()] += 1;
			}
			m_pBmp->DeReferenceBitPtr (pData);
		}
		m_b_beenRun = true;
	}
}


}


