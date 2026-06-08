//*/
/*
					CBfcVector_Shape2d_Bezier.h : 
	
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
namespace CBfcVector
{

BFC_VECTOR_CLASS Shape2d_BezierSegment
{
	// Point [1] is the ceneter point - actually on the bezier curve,
	// Points [0] and [2] are the control points - moved around with a mouse usually.
	CBfc::Point2d	m_Points[3];
};

BFC_VECTOR_CLASS Shape2d_Bezier : public Shape2d
{
public:
	Shape2d_Bezier (const Shape2d_Bezier *p_duper);
	Shape2d_Bezier ()
	{
		m_shapeType = (Shape2d::SHAPE_2D_BEZIER);
	}
	Shape2d_Bezier (const Shape2d_Bezier &bezier)
	{
		m_shapeType = (Shape2d::SHAPE_2D_BEZIER);
		*this = bezier;
	}
	virtual ~Shape2d_Bezier ();

public:	
	void operator = (const Shape2d_Bezier &);

	virtual void *Dup_const() const;
	virtual bool Intersects (Shape2d &Shape2d);
	virtual bool IntersectsRectangle (const Shape2d_Rect &Rect2d);

	virtual BFC_RVAL RenderToAlphaBitmap (const CBfc::Rect2d sourceRect, CBfcImage::Bitmap_Alpha &destAlphaBitmap);
			// Returns a positive integer if the point is over the Shape
	virtual unsigned long GetAlphaAt (const CBfc::Point2d &pt);
protected:
	virtual Shape2d_Rect *Calculate_EncompassingRetangle ();
private:
	Array<Shape2d_BezierSegment>		m_Segments;
};

}

