//*/
/*
					CBfcImage_Format_DJVU.h : 
	
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

namespace CBfcImage
{

BFC_IMAGE_CLASS Image_Format_DJVU : public Image_Format
{
public:
	Image_Format_DJVU (const CBfc_Stream *p_Stream);
	virtual ~Image_Format_DJVU();

    virtual bool LoadHeader (Image_Info &info);
    virtual bool LoadRectangle (const CBfc_2dRect &rect2d_Load, Bitmap &bfc_bitmap);
	virtual bool Save (/*const*/ Bitmap &bfc_bitmap);

// These methods Get/Set the information for the current layer only.
	virtual BinaryData	*GetUserDatafield() ;
	virtual bool SetUserDatafield(BinaryData	*);
	virtual bool GetTag (const CBfc::STRING &tag, CBfc::STRING &data);
	virtual bool SetTag (const CBfc::STRING &tag, const CBfc::STRING &data);

protected:
//    UINT    ObtainOffset(UINT u_x, UINT u_y);
private:
	void			handle(int wait);
	void			dopage(int pageno);
private:
	void			*m_p_ddjvu_context;
	void			*m_p_ddjvu_document;

	Bitmap			m_bitstore;		// Load up the whole image always.
private:
	CBfc::DynamicLink		*m_p_dynalink;
};

}

