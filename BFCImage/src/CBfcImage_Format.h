//*/
/*
					CBfcImage_Format.h : 
	
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

// Base class for all simple 2d image file format interfaces

/*
#define SUPPORTS_TILES			1
#define SUPPORTS_LINE_BY_LINE		2
#define SUPPORTS_PYRAMID		4	// true if multiple resolutions present
#define SUPPORTS_MEMORY_READ		8	// Can we pass a memory pointer to read from?
*/

namespace CBfcImage
{

#define BinaryData CBfc_ReferencedAllocation

BFC_IMAGE_CLASS	Image_Format;
BFC_IMAGE_CLASS	Image_Buffer;
	
BFC_IMAGE_CLASS Image_Format_Layer
{
	public:
		Image_Format_Layer(Image_Format *pMotherFormat)
			: m_p_Format(pMotherFormat)
			, m_b_ImageSizeSet(false)
			, m_LayerNumber(0)
				{}
		Image_Format *GetFormat() const {
					return m_p_Format; }

		virtual bool SaveLayer () { return false; }
		virtual bool LoadRectangle (const CBfc::Rect2dU &rect2d_Load, Bitmap &bfc_bitmap) = 0;
		virtual bool SaveBitmap (/*const*/ Bitmap &bfc_bitmap) { return false; }
		void	SetImageSize(const CBfc::Size2dU &size);
		bool	GetImageSize(CBfc::Size2dU &size) const;
		void	SetLayerNumber (const UINT uLayer);
		UINT	GetLayerNumber () const;

// These methods Get/Set the information for the current layer only.
		virtual BinaryData	*GetUserDatafield() { return NULL; }
		virtual bool SetUserDatafield(BinaryData	*) { return false; }
		virtual bool GetTag (const CBfc::STRING &tag, CBfc::STRING &data) { return false; }
		virtual bool SetTag (const CBfc::STRING &tag, const CBfc::STRING &data) { return false; }

	protected:
		UINT			m_LayerNumber;
		CBfc::Size2dU	m_ImageSize;
		bool			m_b_ImageSizeSet;
	protected:
	// 	bool	FoxLoadHeader (void *fxImg);
	// 	bool	FoxLoadRectangle (void *fxImg, const CBfc::Rect2dU &rect2d_Load, Bitmap &bfc_bitmap);
	protected:
		Image_Format	*m_p_Format;
};

BFC_IMAGE_CLASS Image_Format_Page 
{
	public:
		Image_Format_Page(Image_Format *pMotherFormat)
			: m_p_Format(pMotherFormat)
				{}
	public:
		virtual bool SavePage () { return false; }
		virtual Image_Format_Layer *GetLayer(const UINT uLayer)=0;
	protected:
		Image_Format	*m_p_Format;
};

BFC_IMAGE_CLASS Image_Format : public CBfc::Stream
{
public:
    inline Image_Format (const CBfc::Stream *p_Stream=NULL)
                {
				if (p_Stream) 
					AttachStream(*p_Stream);
                }
    virtual ~Image_Format ()
                {
                }

	virtual bool LoadHeader (Image_Info &info);
	bool SaveBuffer (Image_Buffer*p_buffer);

	virtual Image_Format_Page	*GetPage(const UINT uPage)=0;
protected:
	UINT		m_flags_features;		//	What does this one support
//    int		m_tileWidth, m_tileHeight;
};


}

#include "CBfcImage_Format_BMP.h"
#include "CBfcImage_Format_JPEG.h"
#include "CBfcImage_Format_JPEG2000.h"
#include "CBfcImage_Format_DJVU.h"
#include "CBfcImage_Format_TIFF.h"


