//*/
/*
					BitmapPipe.cpp : 
	
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

BitmapPipe::BitmapPipe(const Bitmap *pBmp,  const Rect2dU *pRect)
	: m_pBmp(pBmp)
	, m_y_offset(0)
	, m_buffer(NULL)
{
	if (pRect)
	{
		m_Rect.Set(*pRect);
	} else
	{
		Size2dU size;
		m_pBmp->GetSize(size);
		m_Rect.Set (size);
	}
	ReallocateBuffer();
}

BitmapPipe::~BitmapPipe()
{
	BFC_RELEASE(m_buffer);
}

Size2dU BitmapPipe::GetSize() const
{
	return m_Rect.GetSize ();
}

void BitmapPipe::ReallocateBuffer()
{
	UINT width = m_OutputColorspace.BytesRequiredToStore(m_Rect.Width());
	BFC_RELEASE(m_buffer);
	m_buffer = new BYTE[width+16];
}

void BitmapPipe::SetColorSpace (const ColorSpace &cspace)
{
	m_OutputColorspace = cspace;
	ReallocateBuffer();
}

bool	BitmapPipe::Iterate(PixelBuffer &pxlbuf)
{
	if (m_y_offset < m_Rect.Height())
	{
		const	Position2dU	tl(m_Rect.TopLeft());
		const	UINT			w = m_Rect.Width();
		if (m_pBmp->GetScanline (m_buffer, tl.GetX(), tl.GetY()+m_y_offset, w, m_OutputColorspace))
		{
			Pixels	pxls(m_buffer, m_OutputColorspace);
			pxlbuf.Set (&pxls, w);
			m_y_offset++;
			return true;
		}
		return false;
	}
	m_y_offset = 0;
	return false;
}


PixelBuffer *BitmapPipe::Iterate()
{
	if (m_y_offset < m_Rect.Height())
	{
		const	Position2dU	tl(m_Rect.TopLeft());
		const	UINT			w = m_Rect.Width();
		if (m_pBmp->GetScanline (m_buffer, tl.GetX(), tl.GetY()+m_y_offset,w, m_OutputColorspace))
		{
			PixelBuffer *pBuf = new PixelBuffer();
			Pixels	pxls(m_buffer, m_OutputColorspace);
			pBuf->Set (&pxls, w);
			m_y_offset++;
			return pBuf;
		}
	}
	m_y_offset = 0;
	return NULL;
}

}

