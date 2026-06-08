//*/
/*
					CBfcImage_Buffer.cpp : 
	
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

Image_Buffer :: Image_Buffer (Image_Info *p_imageInfo)
{
	if (p_imageInfo)
        m_imageInfo = *p_imageInfo;
}

Image_Buffer::~Image_Buffer()
{
// 	BFC_RELEASE (m_p_imageBitmap);
}

// Construct another buffer from this one.   If the full buffer is required,
// increment the reference count and contine
// This assumes
// Return NULL if unable
Image_Buffer *Image_Buffer :: ConstructBuffer (Image_Segment * p_segment)
{
	// Look at the current segment portion, and determine
#pragma message ("Not Yet Working!")
//    Rect2dU	rectSeg ((this->GetSegment(), p_segment));
	if (this->GetSegment() == *p_segment)
	    	return this;		// ups the reference count.
	Image_Buffer	*p_buffer = new Image_Buffer ();
    	return p_buffer;
}

Bitmap	*Image_Buffer :: GetBitmap(const UINT uLayer)
{
	const UINT	uIndexExisting = LookupBitmap(uLayer==ALL_LAYERS?0:uLayer);
	if (uIndexExisting != -1)
		return *(m_bitmap_pointers.GetAt(uIndexExisting));
	return NULL;
}

/// returns 0 if no more layers
UINT Image_Buffer::EmptyLayer(const UINT uLayer)
{
	const UINT	uIndexExisting = LookupBitmap(uLayer);
	if (uIndexExisting != -1)
		m_bitmap_pointers.RemoveAt(uIndexExisting);
	return m_bitmap_pointers.GetCount();
}

void Image_Buffer::SetBitmap (Bitmap *pBmp, const Image_Segment * p_segment)
{
	if (p_segment)
		m_segment = *p_segment;
	else
		throw;
	EmptyLayer(pBmp->GetLayer());
	m_bitmap_pointers.Add(&pBmp);
}

UINT	Image_Buffer::LookupBitmap(const UINT uLayer) const
{
	Bitmap **pp_bitmap;
	ULONG	uIndex = m_bitmap_pointers.StartIteration();
	while ((pp_bitmap = m_bitmap_pointers.GetNext(uIndex)))
	{
		if ((*pp_bitmap)->GetLayer()==uLayer)
			return uIndex-1;
	}
	return (-1);
}


// Internally sets up a bitmap for this buffer with the given segment info, so the when
// asked for it will be available.
bool Image_Buffer :: LoadBuffer (Image_Format_Layer *pLayerLoader, const Image_Segment * p_segment)
{
	CBfc::Rect2dU	rect;

//    if (TranslateSegment_To_PixelRectangle ( m_p_parentImage->GetInfoPtrForPlane(), &m_segment, rect))
	if (TranslateSegment_To_PixelRectangle (p_segment, rect))
	{
// 		m_segment = *p_segment;		Happens in SetBitmap
		CBfc::Size2dU	size;
				
		pLayerLoader->GetImageSize(size);
		rect.Set(size);

		Bitmap	*pBmp = AllocateRectangle (rect, pLayerLoader->GetLayerNumber());
		if (pBmp)
		{
			bool b = pLayerLoader->LoadRectangle (rect, *pBmp);
			if (b)
				SetBitmap (pBmp, p_segment);
			else
				delete pBmp;
			return b;
		}
	}
	return false;
}

Bitmap * Image_Buffer :: AllocateRectangle (const CBfc::Rect2dU &rect, const UINT uLayer)
{
	Bitmap *pBmp = new Bitmap();
	if (!pBmp->Allocate (m_imageInfo.GetColorSpace(), rect.GetSize()))
	{
		delete (pBmp);
		return NULL;
	}
	pBmp->SetPosition (rect.TopLeft());
	pBmp->SetLayer (uLayer);
	return pBmp;
}


bool Image_Buffer :: TranslateSegment_To_PixelRectangle (const Image_Segment * p_segment, CBfc::Rect2dU &rectangle) const
{
	return true;
}

}

