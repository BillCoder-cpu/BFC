//*/
/*
					CBfcImage_2dArrayPixel.cpp : 
	
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

using namespace CBfc;

Image_2dArrayPixel::Image_2dArrayPixel(const ColorSpace &colorSpace)
	: m_p_allocation(NULL)
	, m_colorSpace(colorSpace)
{
    m_u_effectiveBitsPerPixel = Bitmap::CalculateEffectiveBits (colorSpace.GetBitsPerPixel());
}

Image_2dArrayPixel::Image_2dArrayPixel(const CBfc::Size2dU &size2d, const ColorSpace &colorSpace, CBfc_ReferencedAllocation *p_DupAllocation)
	: m_p_allocation(p_DupAllocation)
	, m_colorSpace(colorSpace)
{
	m_u_effectiveBitsPerPixel = Bitmap::CalculateEffectiveBits (colorSpace.GetBitsPerPixel());
	SetSize (size2d);
	if (!p_DupAllocation)
		Allocate();
}

Image_2dArrayPixel::~Image_2dArrayPixel()
{
	BFC_RELEASE (m_p_allocation);
}

Image_2dArrayPixel *Image_2dArrayPixel::Dup() const
{
	return new Image_2dArrayPixel(m_size,m_colorSpace,m_p_allocation);
}

void Image_2dArrayPixel::SetSize(const Size2dU &size2d)
{
	m_size.Set(size2d);
	m_u_pitchBytes = BytesRequiredToStore(m_size.GetX());
}


void Image_2dArrayPixel::Allocate()
{
	BFC_RELEASE(m_p_allocation);
	m_p_allocation = new CBfc_ReferencedAllocation();
	m_p_allocation->EnsureBytesAllocated(m_u_pitchBytes * m_size.GetY());
}

UINT Image_2dArrayPixel::BytesRequiredToStore (const UINT u_pixelCount) const
{
    const UINT u_byteCount = ((u_pixelCount*m_u_effectiveBitsPerPixel)+7)/8;
    return u_byteCount;
}

BYTE *Image_2dArrayPixel::GetPtr (const Position2dU &pos, const UINT u_membersNeeded) const
{
    BYTE    *ptr;
    __uint64    n_offset = ((pos.GetX() * m_u_effectiveBitsPerPixel)/8) + (pos.GetY() * m_u_pitchBytes);
    m_p_allocation->ReferenceBytes (n_offset, BytesRequiredToStore(u_membersNeeded), ptr);
    return ptr;
}

BYTE *Image_2dArrayPixel::GetPtr (const UINT u_x, const UINT u_y, const UINT u_membersNeeded) const
{
    BYTE    *ptr;
    __uint64    n_offset = ((u_x * m_u_effectiveBitsPerPixel)/8) + (u_y * m_u_pitchBytes);
    m_p_allocation->ReferenceBytes (n_offset, BytesRequiredToStore(u_membersNeeded), ptr);
    return ptr;
}

bool Image_2dArrayPixel::ReleasePtr (BYTE *p)
{
    return m_p_allocation->DeReferenceBytes(p);
}

bool Image_2dArrayPixel::Enlarge(const Size2dU &size)
{
	const UINT	uWidth = size.GetX();
	const UINT	uPitch = BytesRequiredToStore(uWidth);
	const UINT	TotalBytes = uPitch * (UINT)size.GetY();
	
	CBfc_ReferencedAllocation *alloc = new CBfc_ReferencedAllocation();
	alloc->EnsureBytesAllocated(TotalBytes);
	
	Position2dU	posIterate(0,0);
	__uint64    n_offset = 0;
	BYTE   *d;
	alloc->ReferenceBytes (0, TotalBytes, d);
	do {
		BYTE *s = GetPtr (posIterate, m_size.GetX());
		memcpy (d+n_offset, s, m_u_pitchBytes);
		n_offset += uPitch;
		ReleasePtr(s);
	} while (posIterate.IterateY(size));
	alloc->DeReferenceBytes(d);
				
	BFC_RELEASE(m_p_allocation);
	m_p_allocation = alloc;
	SetSize(size);
	return true;
}

bool Image_2dArrayPixel::crop(const CBfc::Rect2dU &chunk)
{
#if 0
	UINT	cx,cy,cw,ch;
	chunk.Get(cx,cy,cw,ch);
	BFC_TRACE (_TXT(" ~Cropping (%d,%d,%d,%d)\n"), cx,cy,cw,ch);
#endif
	const UINT	uWidth = chunk.Width();
	const UINT	uPitch = BytesRequiredToStore(uWidth);
	const UINT	TotalBytes = uPitch * (UINT)chunk.Height();
	
	CBfc_ReferencedAllocation *alloc = new CBfc_ReferencedAllocation();
	alloc->EnsureBytesAllocated(TotalBytes);
	
	Position2dU	posGet(chunk.TopLeft());
	Position2dU	posIterate(0,0);
	__uint64    n_offset = 0;
	BYTE   *d;
	alloc->ReferenceBytes (0, TotalBytes, d);
	do {
		BYTE *s = GetPtr (posGet+posIterate, uWidth);
		memcpy (d+n_offset, s, uPitch);
		n_offset += uPitch;
		ReleasePtr(s);
	} while (posIterate.IterateY(chunk.GetSize()));
	alloc->DeReferenceBytes(d);
				
	BFC_RELEASE(m_p_allocation);
	m_p_allocation = alloc;
	SetSize(chunk.GetSize());
	return true;
}


}


