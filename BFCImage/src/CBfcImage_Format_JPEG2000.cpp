//*/
/*
					CBfcImage_Format_JPEG2000.cpp : 
	
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
#include "FoxImage.h"
#include "BFC/BFCOS.h"

namespace CBfcImage
{

bool Image_Format_JPEG2000 :: LoadHeader (Image_Info &info)     // virtual
{
    #define DIB_HEADER_MARKER   ((WORD) ('M' << 8) | 'B')
	bool b_rVal = false;

	// Utilize fox here !
	FXFileStream	store;

	Filename fc;
	((StreamSource_File*)m_p_source)->GetFilename(fc);
	STRING8	s8(fc);
	
	FXString file (s8.GetPtr8());
	if(store.open(file,FXStreamLoad))
	{  
//  FXJPGImage(FXApp *a,const void *pix=NULL,FXuint opts=0,FXint w=1,FXint h=1);
		FXJPGImage		*pImg = new FXJPGImage((FXApp *)m_p_app->GetLayerAppPointer());	
		try
		{
			pImg->load (store);
			b_rVal = true;
		} catch (FXResourceException fxe)
		{
			STRING	sMsg(fxe.what());
		}
		
		store.close();
		if (b_rVal)
		{
			const UINT	ww=pImg->getWidth();
			const UINT	hh=pImg->getHeight();
	
			GetPage(0)->GetLayer(0)->SetImageSize(Size2dU(ww,hh));
					
			Rect2dU	rect2d_Load(0,0,ww,hh);
		//	info.GetResolution().
			info.GetColorSpace().SetColorSpace(ColorSpace::COLORSPACE_RGBA);
		
// 			m_bitstore.Allocate(info.GetColorSpace(), rect2d_Load.GetSize());
// 			b_rVal = FoxLoadRectangle((void*)pImg, rect2d_Load, m_bitstore);
		}		
		delete pImg;
	}
	return b_rVal;
}


OVERRIDE Image_Format_Page *Image_Format_JPEG2000::GetPage(const UINT uPage)
{
	return &m_Page;
}

OVERRIDE Image_Format_Layer *Image_Format_Page_JPEG2000::GetLayer(const UINT uLayer)
{
	return &m_Layer;
}

/////////////////////////////////////////////////////////
// Assumes bfc_bitmap is of the correct known data type
//
bool Image_Format_Layer_JPEG2000 :: LoadRectangle (const Rect2dU &rect2d_Load, Bitmap &bfc_bitmap)     // virtual
{
	bfc_bitmap = m_bitstore;
	return true;
}

bool Image_Format_Layer_JPEG2000 :: SaveBitmap (/*const*/ Bitmap &bfc_bitmap)
{
	return false;
}

}


