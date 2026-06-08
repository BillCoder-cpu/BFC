//*/
/*
					CBfcImage_Format.cpp : 
	
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
//
// C++ Implementation: CBfcImage_Format
//
// Description: 
//
//
// Author: Bill Foster <wpf_software@hotmail.com>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "BFC/BFCImage.h"
#include "FoxImage.h"

namespace CBfcImage
{


bool Image_Format::LoadHeader (Image_Info &info) 
{
	return false;
}

///
/// This needs to be much improved - should iterate all existing pages and layers and save them all out.\
/// current status == brain-dead.
bool Image_Format::SaveBuffer (Image_Buffer*p_buffer)
{
	return GetPage(0)->GetLayer(0)->SaveBitmap(*(p_buffer->GetBitmap()));
}

void	Image_Format_Layer::SetImageSize(const CBfc::Size2dU &size)
{
	m_ImageSize = size;
	m_b_ImageSizeSet = true;
}

bool	Image_Format_Layer::GetImageSize(CBfc::Size2dU &size) const
{
	size = m_ImageSize;
	return (m_b_ImageSizeSet);
}

void	Image_Format_Layer::SetLayerNumber (const UINT uLayer)
{
	m_LayerNumber = uLayer;
}

UINT	Image_Format_Layer::GetLayerNumber() const
{
	return m_LayerNumber;
}

bool Image_Format_Layer::LoadRectangle (const CBfc::Rect2dU &rect2d_Load, Bitmap &bfc_bitmap)
{
	return false;
}

#if 0
bool Image_Format::FoxLoadHeader (void *fxImg)
{
// 	FXImage	*pImg = (FXImage*)fxImg;
	return false;
}

/**
 * 
 * @param fxImg 
 * @param rect2d_Load 
 * @param bmp 
 * @return 
 */
bool Image_Format::FoxLoadRectangle (void *fxImg, const CBfc::Rect2dU &rect2d_Load, Bitmap &bmp)
{
    bool    b_rVal = true;
    UINT    x, y, x2, y2;

    rect2d_Load.Get (x,y,x2,y2);
	
	FXImage	*pImg = (FXImage*)fxImg;
	FXColor	*pData = pImg->getData();
	if (pData)
	{
		UINT	nPixels = (x2-x) * (y2-y);
		BYTE	*bp = bmp.ReferenceBitPtr(0,0,nPixels);			// transfer the loaded data into a bfc bitmap
		memcpy (bp, pData, nPixels*4);
		bmp.DeReferenceBitPtr(bp);
		return true;
	}

	return false;
}
#endif


}

