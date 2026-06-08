//*/
/*
					CBfcVector_Shape2d.cpp : 
	
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

Shape2d::Shape2d (const Shape2d *p_duper)
	: CBfc_ReferencedObject(p_duper)
	,	m_p_Limiting2dShape (NULL)
	,	m_p_EncompassingRetangle (NULL)
{
	SetDirty();
}


Shape2d::~Shape2d()
{
	BFC_RELEASE(m_p_Limiting2dShape);
	BFC_RELEASE (m_p_EncompassingRetangle);
	BFC_RELEASE (m_p_AlphaBitmap);
}


void Shape2d::SetDirty()
{
	BFC_RELEASE (m_p_EncompassingRetangle);
	BFC_RELEASE (m_p_AlphaBitmap);
}


bool Shape2d::EncompassingRectanglesIntersect (Shape2d &Shape2d)
{
	Shape2d_Rect	rect_this, rect_other;

	if (GetEncompassingRetangle (rect_this) && Shape2d.GetEncompassingRetangle (rect_other))
		return rect_this.IntersectsRectangle (rect_other);
	return false;
}


bool Shape2d::GetEncompassingRetangle (Shape2d_Rect &rectangle)
{
	if (!m_p_EncompassingRetangle)
	{
		m_p_EncompassingRetangle = Calculate_EncompassingRetangle ();
	}
	if (m_p_EncompassingRetangle)
	{
		rectangle = *m_p_EncompassingRetangle;
		return true;
	}
	return false;
}


bool Shape2d::IntersectsRectangle (Shape2d_Rect &Rect2d)
{
	return (EncompassingRectanglesIntersect(Rect2d));
}

bool Shape2d::IntersectsRectangle (const Shape2d_Rect &Rect2d)
{
	Shape2d_Rect	rect = Rect2d;
	return IntersectsRectangle (Rect2d);		// Should jump into derived class
}


bool Shape2d::LimitTo (const Shape2d &shapeLimit)			// Limit to another shape
{
	// First, test to see if simple clipping can be accomplished.
	BFC_RELEASE (m_p_Limiting2dShape); // Very Chincy for now!!!!
	if (!m_p_Limiting2dShape)
		m_p_Limiting2dShape = (Shape2d*)shapeLimit.Dup_const();
	return true;
}


unsigned long Shape2d::GetAlphaAt (const Point2d &pt)
{
	return 255;
}


void Shape2d::operator = (const Shape2d &other_2dShape)  // Do NOT Make this public!!!!!!
{
	Equals(other_2dShape);
}

void Shape2d::Equals(const Shape2d &other_2dShape)
{
	BFC_RELEASE(m_p_Limiting2dShape);

	m_shapeType = other_2dShape.m_shapeType;
	const Position2d &pos = other_2dShape.GetPositionConst();
	m_2dPosition = pos;
	if (other_2dShape.m_p_Limiting2dShape)
		m_p_Limiting2dShape = (Shape2d*)other_2dShape.m_p_Limiting2dShape->Dup_const();
//	SetDirty();		// try not to do this here.
}

BFC_RVAL Shape2d::RenderToAlphaBitmap (const CBfc_2dRect sourceRect, CBfcImage::Bitmap_Alpha &destAlphaBitmap)
{
	// Needs Work
	return false;
}



