//*/
/*
					CBfcVector_Shape2d_Rect.cpp : 
	
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

#include <BFC/BFCVector.h>

using namespace CBfcVector;

Shape2d_Rect::Shape2d_Rect(const Shape2d_Rect *p_duper)
	: Shape2d(p_duper)
{
	if (p_duper)
		*this = *p_duper;
}

Shape2d_Rect::~Shape2d_Rect()
{
}

void *Shape2d_Rect::Dup_const() const
{
	Shape2d_Rect *p_ShapeDup = new Shape2d_Rect (this);
	return (void *)p_ShapeDup;
}


void Shape2d_Rect :: operator = (const Shape2d_Rect &Other_2dRect)
{
	Shape2d::Equals (Other_2dRect);
	m_Width.Set (Other_2dRect.GetSize().GetX(), Distance::EBFC_DISTANCEUNIT_UNIT);
	m_Height.Set (Other_2dRect.GetSize().GetY(), Distance::EBFC_DISTANCEUNIT_UNIT);
}


Shape2d_Rect *Shape2d_Rect::Calculate_EncompassingRetangle ()
{
	return new Shape2d_Rect(*this);
}


bool Shape2d_Rect::Intersects (Shape2d &Shape2d)
{
	const Shape2d_Rect	rect=*this;
	return Shape2d.IntersectsRectangle (rect);
}

bool Shape2d_Rect::IntersectsRectangle (const Shape2d_Rect &Rect2d)
{
	// NO- conversion should not be necessary.
	// The < and > operators should take care of this
	//
	//    Iron out the mechanics of my 'MeasureLength' equivalent by filling in this
	//   function to do the raw calculation of intersecting rectangles.
	// Steps:
	//

	// Needs Work
	return false;
}


BFC_RVAL Shape2d_Rect::RenderToAlphaBitmap (const CBfc_2dRect sourceRect, CBfcImage::Bitmap_Alpha &destAlphaBitmap)
{
	// Needs Work
	return false;
}


// Returns a positive integer if the point is over the Shape
unsigned long Shape2d_Rect::GetAlphaAt (const Point2d &pt)
{
	// Needs Work
	return false;
}


