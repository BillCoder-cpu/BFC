//*/
/*
					CBfcImage_Bitmap.h : 
	
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

BFC_IMAGE_CLASS Bitmap_Alpha;


BFC_IMAGE_CLASS Thing2d : public CBfcImage_Object
{
public:
	Thing2d();
	
	void	SetPosition (const CBfc::Position2dU &pos) {
		m_rectSize.SetPosition (pos);
	}
	void SetLayer(const UINT uLayer) {
		m_Layer = uLayer;
	}
	UINT	GetLayer() const {
		return m_Layer;
	}
	void	GetRect(CBfc::Rect2dU &rectU) const {
		rectU = m_rectSize;
	}
	void	GetPosition (CBfc::Position2dU &pos) const {
		pos = m_rectSize.TopLeft();
	}
	void GetSize (CBfc::Size2dU &size2d) const {
		size2d = m_rectSize.GetSize();
	}
	
	void Name(const CBfc::STRING &name) {
		m_Name = name;
	}
	CBfc::STRING &GetName() {
		return m_Name;
	}
	void operator = (const Thing2d &src);
public:
	virtual Bitmap_Alpha		*GetAlpha()=0;
protected:
	CBfc::STRING			m_Name;
	UINT					m_Layer;
	CBfc::Rect2dU			m_rectSize;
};		// BFC_IMAGE_CLASS Thing2d;

/// A simple, 2dimensional bitmap
/// use a bunch of these with compressed allocations
BFC_IMAGE_CLASS Bitmap : public Thing2d
{
public:
	virtual ~Bitmap ();
	Bitmap ();
	Bitmap(const CBfc::Size2dU &size, const ColorSpace &colorSpace, Color *p_BackgroundColor=NULL);
//	Bitmap *Dup();
	
	static UINT CalculateEffectiveBits (const UINT u_bitsPerPixel);
	
	virtual bool 	crop(const CBfc::Rect2dU &chunk);
	
	bool Release ();
	bool Allocate (const ColorSpace &colorSpace, const CBfc::Size2dU &size);
	bool Enlarge(const CBfc::Rect2dU &rect);

	Color operator [] (const CBfc::Position2dU &pos) const;
	void operator = (const Bitmap &bmp);
	
	inline bool  IsCompressed(void) const { return false; }

	BYTE *ReferenceBitPtr (const CBfc::Position2dU &pos, const UINT u_getPixelCount=0) const;
	BYTE *ReferenceBitPtr (const UINT u_x, const UINT u_y, const UINT u_getPixelCount=0) const;
	bool DeReferenceBitPtr (BYTE *p) const;

	bool SetBits (const BYTE *srcBits, const UINT u_x, const UINT u_y, const UINT u_w, const UINT u_h, const UINT u_pitch);
	bool SetScanlines (BYTE *pixelData, const UINT u_x, const UINT u_y, const UINT ww, const ColorSpace &cspace, const UINT u_nLines);

	bool GetRectangle(BYTE *destPixels, const CBfc::Size2dU &destSize, const CBfc::Position2dU &sourceOrigin, const ColorSpace &destCSpace) const;
	bool GetScanline (BYTE *pixelData, const UINT u_x, const UINT u_y, const UINT ww, const ColorSpace &cspace) const;
	
	bool GetZoomedRectangle(BYTE *destPixels, const CBfc::Size2dU &destSize, const CBfc::Position2dU &sourceOrigin, const double zoom, const ColorSpace &destCSpace) const;
	bool GetZoomedScanlines (BYTE *destPixels, const CBfc::Position2dU &source_pos, const CBfc::Size2dU &dest_size, const double zoom, const ColorSpace &cspace) const;
	bool GetZoomedScanline (BYTE *destPixels, const CBfc::Position2dU &source_pos, const UINT dest_ww, const double zoom, const ColorSpace &cspace) const;

	void 			GetColorSpace (ColorSpace &colorSpace) const {
					colorSpace = m_colorSpace;
				}
	ColorSpace 		GetColorSpace () const {
					return m_colorSpace;
				}
	void 			GetResolution (Resolution &resolutionX, Resolution &resolutionY) const {
					resolutionX = m_resolutionX;
					resolutionY = m_resolutionY;
				}
	
	Bitmap *		PickupSelection (Bitmap_Alpha *pAlpha, Color *pBackgroundColor=NULL) const;
	
	void 			GeneratePalette(UINT minColors=256);
	void			ReGeneratePalette(UINT minColors=256);
	Palette	*	GetPalette() const {
						return m_p_palette;
					}
	void				SetPalette(const Palette *p_palette);
	void				SetAlpha(Bitmap_Alpha*);
	void				DupAlpha(Bitmap_Alpha*);
	
	
	bool			FillRectangle (const Color &col, const CBfc::Rect2dU &r);

public:
	virtual Bitmap_Alpha		*GetAlpha();
protected:
	ColorSpace				m_colorSpace;
	Resolution				m_resolutionX, m_resolutionY;
   	Image_2dArrayPixel		*m_p_pixelArray2d;
	Palette				*m_p_palette;
private:
	Bitmap_Alpha			*m_p_Alpha;
};


BFC_IMAGE_CLASS Bitmap_Alpha : public Bitmap
{
public:
	virtual ~Bitmap_Alpha () {}
	Bitmap_Alpha ();
	Bitmap_Alpha (const CBfc::Size2dU &size);
	Bitmap_Alpha (const Bitmap_Alpha *pDupAlpha);
	
	Bitmap_Alpha	*Dup() const;

	void operator = (const Bitmap_Alpha &bmpAlpha);
	void operator |= (const Bitmap_Alpha &bmpAlpha);
	UINT operator [] (const CBfc::Position2dU &pos) const;
	
	unsigned char AdjacentOn (const CBfc::Position2dU &pos) const;
	unsigned char AdjacentOff (const CBfc::Position2dU &pos) const;
	unsigned char Edge (const CBfc::Position2dU &pos) const;
//	unsigned char AdjacentEdge(const CBfc::Position2d &pos) const;
	void Set(const CBfc::Position2dU &pos, unsigned char value);
	bool Shrink ();
protected:
	bool IsBlankLine(const UINT line) const;
	bool RangeOfZeros(const UINT line, int &l, int &r);
private:
	unsigned char AnAdjacentIs (const CBfc::Position2dU &pos, const bool b_aboveThreshold, const unsigned char ucThreshold) const;

};

typedef Bitmap Bitmap_Uncompressed;

}





