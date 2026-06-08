//*/
/*
					CBfcImage.h : 
	
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

#ifndef __H_bfcimg
#define __H_bfcimg

/*
	CBfcImage.h

    One library per supported file format
*/

namespace CBfcImage
{

	
BFC_IMAGE_CLASS Image_
{
private:
    Image_Buffer	m_ImageBuffer;
    Image_Info   	m_InfoTransformed; // The header of the original data.
};


//
// Use Image for 
// while transforming, the complete image may need to be assessed while partially processed (i.e. after a few effects)
// we cannot have the full thing in memory at once, so all pieces will have to be loaded in a chunker
BFC_IMAGE_CLASS Image_Basic : public Image_Store
{
	public:
		Image_Basic ();
		Image_Basic (const CBfc::Stream &stream);
		virtual ~Image_Basic();

		virtual bool	NextSelection();
		virtual bool	PreviousSelection();
		
		void SetNativeColorspace	(const ColorSpace &cspace);
		Image_Info  	*GetInfoPtr_Native();	// Returns info after any inherant transform is applied.

		bool			CreateEmptyBuffer(const CBfc::Size2dU &size);
		UINT			m_uSelectionLayer;
	protected:
		virtual void 	SetSegmentToEntireImage(Image_Segment &seg);

	private:
};

		
		// Includes editing functions		
BFC_IMAGE_CLASS Image : public Image_Basic
{
public:
   Image ();
   Image (const CBfc::Stream &stream);
   virtual ~Image();

	virtual Image_Buffer   *GetBuffer(const Image_Segment *p_segment);

	Image_Info  *	GetInfoPtr_Transformed();	// Returns info after any inherant transform is applied.
	Image_Info  *	GetInfoPtrForPlane_Transformed ();

	bool		Save (const Image_Segment * p_segment);
	bool 		Effect (const Image_Segment *p_segment, Image_Effect *pEffect);
protected:
	bool	ReverseTransformSegment(const Image_Segment &SegNative, Image_Segment &SegReverseTransformed);
	virtual void 	SetSegmentToEntireImage(Image_Segment &seg);
   // Apply tranforms to the info
	Image_Info  *	TransformInfo (const Image_Info &InfoNative, Image_Info &InfoTransformed);
private:
	Image_Info				m_InfoTransformed;	 // The header of the original data.
	Image_Transform			m_transform;		// change color space, rotation, mirror, etc.
//	Image_EffectsArray		m_effects;			// apply filter, 
	ScriptImage				*m_p_Script;		// what has been applied to this image, undo, etc.
private:
};


}

#endif //define __H_bfcimg

