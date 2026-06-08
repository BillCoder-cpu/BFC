//*/
/*
					CBfcGUI_Brush.cpp : 
	
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

#include <BFC/BFCGUI.h>

namespace CBfcGUI
{

//--------------------------------------------------

Brush::~Brush()
{
}

Brush::Brush(const EBFCGui_BrushType brushType)
	: m_brushType (brushType)
{
}
//--------------------------------------------------

// Todo: apply alpha of brush before rendering
bool Brush::DoBrush (CBfcImage::Bitmap &bitmap, CBfcVector::Shape2d &ShapeDraw, const CBfcVector::Shape2d &ShapeOutline)
{
	// CBfcImage_Bitmap &bitmap
//	BFC_RVAL br = shapeDraw.RenderToAlphaBitmap 
//					(CBfc_2dRect sourceRect, CBfcImage_Bitmap_Alpha &destAlphaBitmap);
	bool b_rVal;

	CBfcVector::Shape2d_Rect rectangle;

	ShapeDraw.GetEncompassingRetangle (rectangle);
	b_rVal = BrushVirtualInternal (bitmap, rectangle);

// Also, Clip to specified shape
	return b_rVal;
}

// Alpha automatically applied by base brush class
//bool BrushVirtualInternal (CBfcImage_Bitmap &bitmap, const CBfcVector_2dShape &shapeDraw);
	
//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************


Brush_Solid::Brush_Solid(const CBfcImage::Color &color)
	: m_color(color)
{
	m_brushType = (Brush::EBFCGUI_SOLID_COLOR);
}

Brush_Solid::~Brush_Solid()
{
}

bool Brush_Solid::BrushVirtualInternal (CBfcImage::Bitmap &bitmap, const CBfcVector::Shape2d_Rect &shapeDraw)
{
	return true;
}

//*******************************************************************************************

Brush_Effect::~Brush_Effect()
{
}

bool Brush_Effect::BrushVirtualInternal (CBfcImage::Bitmap &bitmap, const CBfcVector::Shape2d_Rect &shapeDraw)
{
	// Needs Work!
	return false;
}


//*******************************************************************************************
Brush_Image::~Brush_Image()
{
}

bool Brush_Image::BrushVirtualInternal (CBfcImage::Bitmap &bitmap, const CBfcVector::Shape2d_Rect &shapeDraw)
{
	// Needs Work!
	return false;
}


}


//*******************************************************************************************


