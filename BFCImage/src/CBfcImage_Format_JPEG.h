//*/
/*
					CBfcImage_Format_JPEG.h : 
	
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

BFC_IMAGE_CLASS	Image_Format_JPEG;

BFC_IMAGE_CLASS Image_Format_Layer_JPEG : public Image_Format_Layer
{
	public:
		Image_Format_Layer_JPEG(Image_Format *pMotherFormat)
			: Image_Format_Layer(pMotherFormat)
		{}
	public:
		virtual bool LoadRectangle (const CBfc::Rect2dU &rect2d_Load, Bitmap &bfc_bitmap);
		virtual bool SaveBitmap (/*const*/ Bitmap &bfc_bitmap);
	private:
		Image_Format_JPEG *GetFormat() {
			return (Image_Format_JPEG*)m_p_Format;
		}
};

BFC_IMAGE_CLASS Image_Format_Page_JPEG : public Image_Format_Page
{
	public:
		Image_Format_Page_JPEG(Image_Format *pMotherFormat)
			: Image_Format_Page(pMotherFormat)
				, m_Layer(pMotherFormat)
		{}
	public:
		virtual Image_Format_Layer *GetLayer(const UINT uLayer);
	private:
		Image_Format_JPEG *GetFormat() {
			return (Image_Format_JPEG*)m_p_Format;
		}
 		Image_Format_Layer_JPEG		m_Layer;		// single layer
};

BFC_IMAGE_CLASS Image_Format_JPEG : public Image_Format
{
	public:
		Image_Format_JPEG (const CBfc_Stream *p_Stream);
		virtual ~Image_Format_JPEG();
		
		friend BFC_IMAGE_CLASS       Image_Format_Layer_JPEG;
		friend BFC_IMAGE_CLASS       Image_Format_Page_JPEG;
	public:
		virtual Image_Format_Page	*GetPage(const UINT uPage);
		virtual bool LoadHeader (Image_Info &info);
		void SetQuality (int i_quality);
	public:
		void	* m_p_error_mgr;		// struct my_error_mgr 	m_jerr;
		void	* m_p_info;
		int	m_i_quality;
	private:
		Image_Format_Page_JPEG		m_Page;		// single page
};
}

