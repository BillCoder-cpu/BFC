//*/
/*
					CBfcImage_Format_BMP.h : 
	
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

#ifdef MICROSOFT_WINDOWS

namespace CBfcImage
{

BFC_IMAGE_CLASS Image_Format_BMP : public Image_Format
{
public:
	inline Image_Format_BMP (CBfc_Stream *p_Stream)
		: Image_Format (p_Stream)
	{
	}

	bool LoadHeader (Image_Info &info);
	bool LoadRectangle (const CBfc_2dRect &rect2d_Load, CBfcImage::Bitmap &bfc_bitmap);
	bool Save (/*const*/ CBfcImage::Bitmap &bfc_bitmap);

protected:
	UINT    ObtainOffset(UINT u_x, UINT u_y);

private:
//    BITMAPFILEHEADER    m_bmfhdr;
//    BITMAPINFOHEADER    m_bmihdr;
//    BITMAPINFO          *m_bmi;
	unsigned long		m_BitsOffset;

	BYTE                *m_p_bits;
	UINT                m_u_pitch;
	UINT                m_u_effectiveBits;      // is 16 for 15 bits
};

}

#endif             // #ifdef MICROSOFT_WINDOWS

