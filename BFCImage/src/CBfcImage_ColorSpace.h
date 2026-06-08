//*/
/*
					CBfcImage_ColorSpace.h : 
	
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

namespace CBfcImage
{

BFC_IMAGE_CLASS ColorSpace : public CBfcImage_Object
{
public:
	typedef enum BFC_API tagEBFC_ColorFamily {
    	COLORFAMILY_RGB,
    	COLORFAMILY_FSL,			// Bill's home-made frequency spectrum and lightness.
    	COLORFAMILY_CMYK,
    	COLORFAMILY_GRAY,
    	COLORFAMILY_HSL,
    	COLORFAMILY_LAB,
    	COLORFAMILY_MONOCHROME,
    	COLORFAMILY_PANTONE,
    	COLORFAMILY_OPACITY,
    	COLORFAMILY_UNKNOWN,
    } EBFC_ColorFamily;

    typedef enum BFC_API tagEBFC_ColorSpace {
    	COLORSPACE_RGB,
	COLORSPACE_RGBA,			// 32 bit
    	COLORSPACE_RGB16,		// 15 bit
    	COLORSPACE_FSL,			// Bill's home-made frequency spectrum and lightness.
    	COLORSPACE_CMYK,
    	COLORSPACE_GRAY,
    	COLORSPACE_HSL,
    	COLORSPACE_LAB,
    	COLORSPACE_MONOCHROME,
    	COLORSPACE_INDEXED,
    	COLORSPACE_PANTONE,
    	COLORSPACE_OPACITY,
    	COLORSPACE_UNKNOWN,
	
	COLORSPACE_BGRA,
	COLORSPACE_BGR,
    } EBFC_ColorSpace;

    ColorSpace ();
	ColorSpace (const EBFC_ColorSpace eSpace);

	void SetColorSpace (const EBFC_ColorSpace eSpace);
	EBFC_ColorSpace GetColorSpace () const;
    uchar GetBitsPerPixel (void) const {
        return m_uc_bitsPerPixel;
    }
	UINT BytesRequiredToStore (const UINT u_pixelCount) const;

    void operator = (const ColorSpace &colorSpace);
	bool operator == (const ColorSpace &colorSpace) const;
protected:
	void		CalculateBitsPerPixel();
private:
    unsigned char		m_uc_bitsPerPixel;
	EBFC_ColorSpace		m_e_colorSpace;
};


}



