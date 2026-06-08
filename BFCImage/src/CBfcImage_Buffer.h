//*/
/*
					CBfcImage_Buffer.h : 
	
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

#define	ALL_LAYERS		(-1)

//
// Use Image_Buffer for tiled image buffers
//  transforms and effects are outside of this scope.
BFC_IMAGE_CLASS Image_Buffer : public CBfcImage_Object
{
public:
	Image_Buffer (Image_Info *p_imageInfo=NULL);
	virtual ~Image_Buffer();
//    bool     	Read();              // Fill in the buffer
//    bool     	Read(BCPoint &pt);   // Fill in the buffer from a particular location in the image.
//    void		SetStep(int lines, int columns=-1);  // set the amount to skip at each consecutive Read()

	inline Image_Segment	&GetSegment () {
    	                            return m_segment; }

		UINT			LookupBitmap(const UINT uLayer) const;

		bool			LoadBuffer (Image_Format_Layer *pLayerLoader, const Image_Segment * p_segment);
		Image_Buffer *	ConstructBuffer (Image_Segment * p_segment);
	
		Bitmap	*	GetBitmap(const UINT uLayer = (UINT)ALL_LAYERS);
		void			SetBitmap (Bitmap *pBmp, const Image_Segment * p_segment=NULL);
		
		UINT			EmptyLayer(const UINT uLayer);			/// returns 0 if no more layers
		Bitmap	*	AllocateRectangle (const CBfc::Rect2dU &rect, const UINT uLayer);
protected:
	bool				TranslateSegment_To_PixelRectangle (const Image_Segment * p_segment, CBfc::Rect2dU &rectangle) const;
private:
	Image_Info   		m_imageInfo;		// Reperesents this buffer - nontransformed.
	Image_Segment		m_segment;			// The position of this tile in the image
	CBfc::Array<Bitmap*>	m_bitmap_pointers;
};	//  Image_Buffer


}  // CBfcImage

