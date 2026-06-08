//*/
/*
					BitmapPipe.h : 
	
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

BFC_IMAGE_CLASS BitmapPipe
{
public:
	BitmapPipe(const Bitmap *pBmp, const CBfc::Rect2dU *pRect=NULL);
	virtual ~BitmapPipe();
	
		void 		SetColorSpace (const ColorSpace &cspace);
	CBfc::Size2dU	GetSize() const;
	
		bool		Iterate(PixelBuffer &pxlbuf);
	PixelBuffer *	Iterate();
	
protected:
	ColorSpace		m_OutputColorspace;
private:
	void ReallocateBuffer();
	
	CBfc::Rect2dU	m_Rect;
	UINT			m_y_offset;
	BYTE	 		*m_buffer;
	const Bitmap	*m_pBmp;
};

}

