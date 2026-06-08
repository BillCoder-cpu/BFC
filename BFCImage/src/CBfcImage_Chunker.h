//*/
/*
					CBfcImage_Chunker.h : 
	
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
// CBfcImageChunker

namespace CBfcImage
{

BFC_IMAGE_CLASS Image_Chunker
{
public:
    Image_Chunker (const Image_Buffer *, const bool b_EdgeChunksLarger = false);

    bool Set (const Image_Buffer *p_imageBuffer);
    // Returns Number of chunks in the image (x,y)
    CBfc_2dSize SetChunkSize (CBfc::Size2dU region);
    bool StartIteratingChunks();
    unsigned IterateNextChunk (CBfc::Rect2dU &NextRect);
     // Call the internal
private:
    CBfc::Size2dU     m_ImageSize;
    CBfc::Size2dU     m_ChunkSize;
private:
    bool			m_b_EdgeChunksLarger;
    CBfc::Position2dU	m_ChunkXY;
};


typedef Image_Chunker Image_Squarer;

}
