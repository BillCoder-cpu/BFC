//*/
/*
					CBfcImage_Format_BMP.cpp : 
	
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

#ifdef MICROSOFT_WINDOWS

namespace CBfcImage
{

typedef struct tagRGBQUAD {
		BYTE    rgbBlue;
		BYTE    rgbGreen;
		BYTE    rgbRed;
		BYTE    rgbReserved;
} RGBQUAD;

typedef struct tagBITMAPINFOHEADER{
		DWORD      biSize;
		long       biWidth;
		long       biHeight;
		WORD       biPlanes;
		WORD       biBitCount;
		DWORD      biCompression;
		DWORD      biSizeImage;
		long       biXPelsPerMeter;
		long       biYPelsPerMeter;
		DWORD      biClrUsed;
		DWORD      biClrImportant;
} BITMAPINFOHEADER, *LPBITMAPINFOHEADER, *PBITMAPINFOHEADER;

typedef struct tagBITMAPINFO {
	BITMAPINFOHEADER    bmiHeader;
	RGBQUAD             bmiColors[1];
} BITMAPINFO, *LPBITMAPINFO, *PBITMAPINFO;

typedef struct tagBITMAPFILEHEADER {
		WORD    bfType;
		DWORD   bfSize;
		WORD    bfReserved1;
		WORD    bfReserved2;
		DWORD   bfOffBits;
} BITMAPFILEHEADER, *LPBITMAPFILEHEADER, *PBITMAPFILEHEADER;



bool Image_Format_BMP :: LoadHeader (Image_Info &info)     // virtual
{
	#define DIB_HEADER_MARKER   ((WORD) ('M' << 8) | 'B')

	BITMAPFILEHEADER    bmfhdr;
	BITMAPINFOHEADER    bmihdr;
	BITMAPINFO          *p_bmi;

	if (Stream::Open ())
	{
			 // Read bitmap file header.
		if ( Stream::Read (&bmfhdr, sizeof(bmfhdr)) )
			// Keep going only if the header type identifies this as a DIB file.
		if (bmfhdr.bfType == DIB_HEADER_MARKER) 
		{
			UINT     ncolors;
										// Read bitmap info header.
			Stream::Read (&bmihdr, sizeof(bmihdr));
										// Compute number of entries in
										// color table.
			if (bmihdr.biBitCount == 24) 
				ncolors = 0;            // No color table in 24-bit DIB files.
			else if (!(ncolors = (UINT) bmihdr.biClrUsed))
				ncolors = 1 << bmihdr.biBitCount;
										// Compute bitmap data size.
			const DWORD   image_size = bmfhdr.bfSize - bmfhdr.bfOffBits;
										// Get memory for complete bitmap,
										// including info, color table, and
										// bitmap data. 
			m_BitsOffset = bmfhdr.bfOffBits;
			if ( (p_bmi = (BITMAPINFO*) malloc(sizeof(BITMAPINFOHEADER) + ncolors * sizeof(RGBQUAD)) ) != NULL)
			{
										// Load memory with info header
										// and color table.
				memcpy(p_bmi, &bmihdr, sizeof(bmihdr));
				Stream::Read (p_bmi->bmiColors, sizeof(RGBQUAD) * ncolors);

										//Set bitmap data size.
				p_bmi->bmiHeader.biSizeImage = image_size;

										// Get ptr to bits memory.
				m_u_effectiveBits = CBfcImage::Bitmap::CalculateEffectiveBits (bmihdr.biBitCount);
				
				m_p_bits = (BYTE *) &p_bmi->bmiColors[ncolors];
				m_u_pitch = ((bmihdr.biWidth * m_u_effectiveBits)/8 + 3) & ~3; // 4 byte aligned
				delete p_bmi;
				return true;
			}
		}
	}
	return false;
}

//
//
//
bool Image_Format_BMP :: Save (/*const*/ CBfcImage::Bitmap &bfc_bitmap)
{
	bool    b_rVal = true;
	BITMAPINFOHEADER    bmihdr;
	BITMAPFILEHEADER    bmfhdr;

	CBfc::Size2dU	size2d;
	bfc_bitmap.GetSize( size2d );

	UINT     u_x=0, u_y=0;
	UINT     u_x2 = (UINT)size2d.GetX();
	UINT	 u_y2 = (UINT)size2d.GetY();
	UINT     u_pitch = ObtainOffset (0, 1);


	ColorSpace colorSpace;
	Resolution resolutionX, resolutionY;

	bfc_bitmap.GetColorSpace (colorSpace);
	bfc_bitmap.GetResolution (resolutionX, resolutionY);

	bmihdr.biSize = sizeof (bmihdr);
	bmihdr.biWidth = (long)u_x2;
	bmihdr.biHeight = 0-(long)u_y2;	// Negative indicates top-down
	bmihdr.biPlanes = 1;
	bmihdr.biBitCount = (WORD)colorSpace.GetBitsPerPixel();
	bmihdr.biCompression = 0;
	bmihdr.biSizeImage = u_pitch * u_y2;
	bmihdr.biXPelsPerMeter = resolutionX.GetDotsPerMeter();
	bmihdr.biYPelsPerMeter = resolutionY.GetDotsPerMeter();
	bmihdr.biClrUsed = 0;
	bmihdr.biClrImportant = 0;


	bmfhdr.bfType = DIB_HEADER_MARKER;
	bmfhdr.bfReserved1 = bmfhdr.bfReserved2 = 0;
	bmfhdr.bfOffBits = sizeof(bmfhdr) + sizeof(bmihdr) + (bmihdr.biClrUsed * 4);
	bmfhdr.bfSize = bmfhdr.bfOffBits + bmihdr.biSizeImage;
	if ( !Stream::Write (&bmfhdr, sizeof(bmfhdr)) )
		return false;

	if ( !Stream::Write (&bmihdr, sizeof(bmihdr)) )
		return false;

			// Position file to data bits and load them into memory.
	if ( bfc_bitmap.IsCompressed() )
	{
/*
		BYTE *pad = new BYTE[u_pitch];
		while (y < y2)
		{
			const UINT    offset = ObtainOffset (x, y);
			m_p_Stream->Seek (bmfhdr.bfOffBits + offset, 0);

			if (!m_p_Stream->Read (pad, u_pitch))
			{
				b_rVal = false;
				break;
			}
			bfc_bitmap.SetBits (pad, x, y, u_w, 1, u_pitch);
			y++;
		}
		delete [] pad;
*/
	} else
	{
		while (u_y < u_y2 && b_rVal)
		{
//            const UINT    offset = ObtainOffset (u_x, u_y);
//            m_p_Stream->Seek (bmfhdr.bfOffBits + offset, 0);

			BYTE *pSrc = bfc_bitmap.ReferenceBitPtr(u_x,u_y,u_pitch);
			if (pSrc)
			{
				b_rVal = Stream::Write (pSrc, u_pitch);
				bfc_bitmap.DeReferenceBitPtr (pSrc);
			}
			u_y++;
		}
	}
	return b_rVal;
}

/////////////////////////////////////////////////////////
// Assumes bfc_bitmap is of the correct known data type
//
bool Image_Format_BMP :: LoadRectangle (const CBfc_2dRect &rect2d_Load, CBfcImage::Bitmap &bfc_bitmap)     // virtual
{
	bool    b_rVal = true;
	UINT    x, y, x2, y2;

	rect2d_Load.Get (x,y,x2,y2);
	UINT     u_w = (UINT)x2-x;
	UINT     u_pitch = ObtainOffset (u_w, 0);
								// Position file to data bits and
								// load them into memory.
	if ( bfc_bitmap.IsCompressed() )
	{
		BYTE *pad = new BYTE[u_pitch];
		while (y < y2)
		{
			const UINT    offset = ObtainOffset (x, y);
			Stream::Seek (m_BitsOffset + offset, 0);

			if (!Stream::Read (pad, u_pitch))
			{
				b_rVal = false;
				break;
			}
			bfc_bitmap.SetBits (pad, x, y, u_w, 1, u_pitch);
			y++;
		}
		delete [] pad;
	} else
	{
		while (y < y2 && b_rVal)
		{
			const UINT    offset = ObtainOffset (x, y);
			Stream::Seek (m_BitsOffset + offset, 0);

			BYTE *pDst = bfc_bitmap.ReferenceBitPtr(x,y,u_pitch);
			if (pDst)
			{
				b_rVal = Stream::Read (pDst, u_pitch);
				bfc_bitmap.DeReferenceBitPtr (pDst);
			}
			y++;
		}
	}
	return b_rVal;
}

UINT Image_Format_BMP :: ObtainOffset(UINT u_x, UINT u_y)
{
	return (u_y * m_u_pitch) + (u_x * m_u_effectiveBits)/8;
}

}

#endif             // #ifdef MICROSOFT_WINDOWS





