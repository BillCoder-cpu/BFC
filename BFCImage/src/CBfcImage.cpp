//*/
/*
					CBfcImage.cpp : 
	
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

Image_Basic::Image_Basic ()
	: m_uSelectionLayer(1)
{
}

Image_Basic::Image_Basic (const CBfc_Stream &stream)
	: Image_Store (stream)
		, m_uSelectionLayer(1)
{
}

Image_Basic::~Image_Basic()
{
}

OVERRIDE bool Image_Basic::NextSelection()
{
	const UINT	uNext = NextLayer(m_uSelectionLayer);
	if (uNext)
	{
		m_uSelectionLayer = uNext;
		return true;
	}
	return false;
}

OVERRIDE bool Image_Basic::PreviousSelection()
{
	const UINT uPrev = PreviousLayer(m_uSelectionLayer);
	if (uPrev)
	{
		m_uSelectionLayer = uPrev;
		return true;
	}
	return false;
}

/**
 * 		Destroys the current contents and puts in an Empty Image of the given size
 * @param size 
 * @return 
 */
bool Image_Basic :: CreateEmptyBuffer (const CBfc::Size2dU &size)
{
	Empty();			
    
	Image_Buffer	*p_buffer = new Image_Buffer(GetInfoPtr_Native());
	if (p_buffer)
	{
		CBfc::Rect2dU	r;
		r.Set(size);
		SetBitmap(p_buffer->AllocateRectangle(r,0));
		return AddBuffer (p_buffer);
	}
	return false;
}

/**
 * 
 * @param seg 
 */
void Image_Basic::SetSegmentToEntireImage(Image_Segment &seg)
{
//  fill me in!
	Image_Store::SetSegmentToEntireImage(seg);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

Image::Image ()
	: m_p_Script (NULL)
{
}

Image::Image (const CBfc_Stream &stream)
	: Image_Basic (stream)
	, m_p_Script (NULL)
{
}

Image::~Image()
{
}

void Image_Basic::SetNativeColorspace (const ColorSpace &cspace)
{
	GetInfoPtr_Native()->GetColorSpace() = cspace;
}

Image_Info  *Image_Basic :: GetInfoPtr_Native()   	// Returns the info before any inherant transform is applied.
{
	return &m_InfoNative;
}

//CBfcImage_Info	*CBfcImage :: GetInfoPtrForPlane_Transformed ()
//{
//}

Image_Info  *Image :: GetInfoPtr_Transformed()  // Returns the info after any inherant transform is applied.
{
    TransformInfo (m_InfoNative, m_InfoTransformed);
	return &m_InfoTransformed;
}


Image_Info  *Image :: TransformInfo (const Image_Info &InfoNative, Image_Info &InfoTransformed)
{
#pragma message ("Unfinished Code!!!")
    InfoTransformed = InfoNative ;

    // utilize m_transform.

    return (&InfoTransformed);
//  m_InfoNative
}

//
//  GetBuffer is more advanced than a standard buffer.  It need not be of the full image
//     The buffer is not filled with data
//  PARAMETERS:
//     The resolution desired (full image size)
//     The size of the buffer (# pixels wide and # of lines that the buffer encompasses)
//
//
//
Image_Buffer *Image :: GetBuffer(const Image_Segment *p_segment)
{
	// Determine if the buffer exists in memory - if so, give it
	// Determine at what size to read the source.
	// Determine what resolution to read the source

	Image_Segment seg, *pSeg;
	if (p_segment)
	{
		ReverseTransformSegment(*p_segment, seg);
	} else
	{
		SetSegmentToEntireImage(seg);
	}
	pSeg=&seg;
//	return ConstructBuffer(pSeg, m_effects);
	return ConstructBuffer(pSeg, *m_p_Script);
}

/**
 * 
 * @param SegNative 
 * @param SegReverseTransformed 
 * @return 
 */
bool Image::ReverseTransformSegment(const Image_Segment &SegNative, Image_Segment &SegReverseTransformed)
{
	throw 101;		// unsuported
	return false;
}

void Image::SetSegmentToEntireImage(Image_Segment &seg)
{
	Image_Basic::SetSegmentToEntireImage(seg);
//  fill me in!
}

bool Image :: Save (const Image_Segment * p_segment)
{
	return Image_Store::Save (GetBuffer(p_segment));
}


bool Image::Effect (const Image_Segment *p_segment, Image_Effect *pEffect)
{
	Image_Buffer *buffer = GetBuffer(p_segment);
	return pEffect->ApplyToBuffer(*buffer);
}


}


