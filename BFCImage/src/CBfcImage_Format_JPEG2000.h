//*/
/*
					CBfcImage_Format_JPEG2000.h : 
	
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

#if MSCVER > 1000
# pragma once
#endif

namespace CBfcOS
{
class Application;
}

namespace CBfcImage
{


BFC_IMAGE_CLASS	Image_Format_JPEG2000;


BFC_IMAGE_CLASS Image_Format_Layer_JPEG2000 : public Image_Format_Layer
{
	public:
		Image_Format_Layer_JPEG2000(Image_Format *pMotherFormat)
	: Image_Format_Layer(pMotherFormat)
		{}
	public:
		virtual bool LoadRectangle (const CBfc::Rect2dU &rect2d_Load, Bitmap &bfc_bitmap);
		virtual bool SaveBitmap (/*const*/ Bitmap &bfc_bitmap);
	private:
		Bitmap		m_bitstore;		// Load up the whole image always.
		
		Image_Format_JPEG2000 *GetFormat() {
			return (Image_Format_JPEG2000*)m_p_Format;
		}
};

BFC_IMAGE_CLASS Image_Format_Page_JPEG2000 : public Image_Format_Page
{
	public:
		Image_Format_Page_JPEG2000(Image_Format *pMotherFormat)
		: Image_Format_Page(pMotherFormat)
			, m_Layer(pMotherFormat)
		{}
	public:
		virtual Image_Format_Layer *GetLayer(const UINT uLayer);
	private:
		Image_Format_JPEG2000 *GetFormat() {
			return (Image_Format_JPEG2000*)m_p_Format;
		}
		Image_Format_Layer_JPEG2000		m_Layer;		// single layer
};

BFC_IMAGE_CLASS Image_Format_JPEG2000 : public Image_Format
{
public:
    inline Image_Format_JPEG2000 (CBfcOS::Application *p_app, const CBfc_Stream *p_Stream)
        : Image_Format (p_Stream)
		    , m_Page(this)
		, m_p_app(p_app)
    {
    }

    virtual Image_Format_Page	*GetPage(const UINT uPage);
    virtual bool LoadHeader (Image_Info &info);
protected:
//    UINT    ObtainOffset(UINT u_x, UINT u_y);
private:
	Image_Format_Page_JPEG2000		m_Page;		// single page
	CBfcOS::Application			*m_p_app;
};

}

