//*/
/*
					CBfcImage_Pixels.h : 
	
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
// Use this class to move data across different Color-spaces
BFC_IMAGE_CLASS	Pixels : public CBfcImage_Object
{
public:
	Pixels();
	Pixels(BYTE *ptr, const ColorSpace &colorSpace);
	
	BYTE	*GetPtr() const {
		return	m_ptr;
	}
	virtual void		Stav (const Color &color);
	void StavLine(Pixels &pelSrc, UINT ww);
	void StavZoomedLine(Pixels &pelSrc, UINT dest_ww, const double zoom);
	void Fill(const Color &color, UINT ww);

	void MixPixels (Pixels *SourceData, unsigned char *AlphaData, UINT uPixelCount);
	static Color MixPixel (const Color &c1, const Color &c2, const unsigned char &ucAlpha);

		void		operator = (const Pixels &eq);
	virtual Color	operator *() const;
	virtual Color	operator[](const UINT offset) const;
	virtual void	operator ++();
	virtual void	operator +=(const int i_inc);
	virtual void	operator --();
protected:
	UINT			BytesRequiredToStore (const UINT u_pixelCount) const;
private:
	BYTE			*m_ptr;
	ColorSpace		m_colorSpace;
	UINT			m_BytesPerPixel;
};


BFC_IMAGE_CLASS	PixelBuffer : public CBfcImage_Object
{
public:
	PixelBuffer();
	PixelBuffer (Pixels *p_pixels, const UINT count);
	
	void Set (Pixels *p_pixels, const UINT count);
	bool Iterate (Color &c);
	UINT	GetCount() const {
		return	m_count;
	}
	BYTE	*GetPtr() const {
		return m_Pixels.GetPtr();
	}
protected:
	UINT			m_count, m_offset;
	Pixels		m_Pixels;
};


BFC_IMAGE_CLASS Pixels_RGBA : public Pixels
{
public:
	Pixels_RGBA(BYTE *ptr);
	virtual Color	operator *();
	virtual Color	operator[](const UINT offset) const;
	virtual void	Stav (const Color &color);
};

BFC_IMAGE_CLASS Pixels_RGB : public Pixels
{
public:
	Pixels_RGB(BYTE *ptr);
	virtual Color	operator *();
	virtual Color	operator[](const UINT offset) const;
	virtual void	Stav (const Color &color);
};

BFC_IMAGE_CLASS Pixels_RGB16 : public Pixels
{
public:
	Pixels_RGB16(BYTE *ptr);
	virtual Color	operator *();
	virtual Color	operator[](const UINT offset) const;
	virtual void	Stav (const Color &color);
};


}

