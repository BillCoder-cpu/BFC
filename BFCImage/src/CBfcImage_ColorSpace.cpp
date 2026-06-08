//*/
/*
					CBfcImage_ColorSpace.cpp : 
	
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

ColorSpace :: ColorSpace ()
{
// Uninitialized state.
	m_uc_bitsPerPixel = 0;
	m_e_colorSpace = COLORSPACE_UNKNOWN;
}

ColorSpace :: ColorSpace (const EBFC_ColorSpace eSpace)
{
	SetColorSpace(eSpace);
}

void ColorSpace :: SetColorSpace (const EBFC_ColorSpace eSpace)
{
	m_e_colorSpace = eSpace;
	CalculateBitsPerPixel();
}

ColorSpace::EBFC_ColorSpace ColorSpace :: GetColorSpace () const
{
	return m_e_colorSpace;
}

void ColorSpace :: operator = (const ColorSpace &colorSpace)
{
    m_uc_bitsPerPixel = colorSpace.m_uc_bitsPerPixel;
	m_e_colorSpace = colorSpace.m_e_colorSpace;
}

bool ColorSpace :: operator == (const ColorSpace &colorSpace) const
{
	return m_e_colorSpace==colorSpace.GetColorSpace();
}

void ColorSpace :: CalculateBitsPerPixel()
{
	switch (m_e_colorSpace)
	{
		case COLORSPACE_CMYK:
		case COLORSPACE_RGBA:
		case COLORSPACE_BGRA:
			m_uc_bitsPerPixel = 32;
			break;
		case COLORSPACE_RGB:
		case COLORSPACE_FSL:			// Bill's home-made frequency spectrum and lightness.
		case COLORSPACE_HSL:
		case COLORSPACE_LAB:
		case COLORSPACE_BGR:
			m_uc_bitsPerPixel = 24;
			break;
		case COLORSPACE_RGB16:
			m_uc_bitsPerPixel = 16;
			break;
		case COLORSPACE_GRAY:
		case COLORSPACE_INDEXED:
			m_uc_bitsPerPixel = 8;
			break;
		case COLORSPACE_MONOCHROME:
			m_uc_bitsPerPixel = 1;
			break;
		case COLORSPACE_PANTONE:
		case COLORSPACE_OPACITY:
			m_uc_bitsPerPixel = 0;
			break;
		case COLORSPACE_UNKNOWN:
			m_uc_bitsPerPixel = 0;
			break;
	}
}

UINT ColorSpace::BytesRequiredToStore (const UINT u_pixelCount) const
{
    return ((u_pixelCount*GetBitsPerPixel())+7)/8;
}

}



