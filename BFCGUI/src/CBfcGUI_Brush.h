//*/
/*
					CBfcGUI_Brush.h : 
	
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

namespace CBfcGUI
{

BFC_GUI_CLASS Brush
{
public:
	virtual ~Brush();

	typedef enum BFC_API tagEBFC_BrushType {
		EBFCGUI_SOLID_COLOR,
		EBFCGUI_IMAGE2D,
//		EBFCGUI_GRADIENT,		// handled by effect
		EBFCGUI_EFFECT,
    } EBFCGui_BrushType;

	Brush(const EBFCGui_BrushType brushType=EBFCGUI_SOLID_COLOR);

public:
	EBFCGui_BrushType GetBrushType () const {
										return m_brushType; }

	// Apply Brush to an outline (folow the shape)
	bool DoBrush (CBfcImage::Bitmap &bitmap, CBfcVector::Shape2d &ShapeDraw, const CBfcVector::Shape2d &ShapeClip);

	// Apply the Brush just once to a particular area - overwrites data.
	virtual bool BrushVirtualInternal (CBfcImage::Bitmap &bitmap, const CBfcVector::Shape2d_Rect &RectDraw)= 0;

protected:
	EBFCGui_BrushType	m_brushType;

private:
	BFCGUI_ALPHA_VALUE	m_Opacity;
	CBfc_2dSize				m_size2d;		// Size of this brush (only need to set for line drawing, etc.)
	CBfcImage::Bitmap	*m_p_Alpha;
};


BFC_GUI_CLASS Brush_Solid : public Brush
{
public:
	virtual ~Brush_Solid();
	Brush_Solid (const CBfcImage::Color &color);
	virtual bool BrushVirtualInternal (CBfcImage::Bitmap &bitmap, const CBfcVector::Shape2d_Rect &shapeDraw);
private:
	CBfcImage::Color		m_color;
};



BFC_GUI_CLASS Brush_Effect : public Brush
{
public:
	virtual ~Brush_Effect();
	virtual bool BrushVirtualInternal (CBfcImage::Bitmap &bitmap, const CBfcVector::Shape2d_Rect &shapeDraw);
private:
};

BFC_GUI_CLASS Brush_Image : public Brush
{
public:
	virtual ~Brush_Image();
	virtual bool BrushVirtualInternal (CBfcImage::Bitmap &bitmap, const CBfcVector::Shape2d_Rect &shapeDraw);
private:
	CBfcImage::Image	*m_p_Image2d;
	CBfc_2dRect				m_rectImage2d;			// Portion of image to utilize
};

}



