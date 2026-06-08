//*/
/*
					CBfcImage_Chunker.cpp : 
	
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
/*

	Okay,   I want to be able to run image processing on my images
	what do i use - chunker, buffer, what?
	
	I need to locate the background of the images - like the sky
			also , distant areas wish to darken - so areas next to background in lightness
			
	Need cmyk, rgb, etc. to mesh flawlessly - use CMYK? or use LAB? or us my own?

*/
namespace CBfcImage
{

	using namespace CBfc;
	
//
// b_EdgeChunksLarger not yet implemented
//
Image_Chunker :: Image_Chunker (const Image_Buffer *p_imageBuffer, const bool b_EdgeChunksLarger)
{
    Set (p_imageBuffer);
    m_b_EdgeChunksLarger = b_EdgeChunksLarger;
}

bool Image_Chunker :: Set (const Image_Buffer *p_imageBuffer)
{
    if (p_imageBuffer)
    {
        m_ImageSize.Set(100, 100);
        return true;
    }
    return false;
}

//
//
bool Image_Chunker :: StartIteratingChunks ()
{
	m_ChunkXY.Set (0,0);
	return true;
}

//
//
//
unsigned Image_Chunker::IterateNextChunk (Rect2dU &NextRect)
{
    // If Going
    Size2dU ChunkSize(m_ChunkSize);

    Position2dU ChunkPositon2d = m_ChunkXY * m_ChunkSize;
    Position2dU LowerRight = ChunkPositon2d + ChunkSize;
    
    if (LowerRight > m_ImageSize)
    {
        ChunkSize.Set ( Size2dU::Minimum (ChunkSize, m_ImageSize - ChunkPositon2d) );
    }
    NextRect.Set (ChunkPositon2d, ChunkSize);
    return 1;
}


}



















