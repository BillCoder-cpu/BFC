//*/
/*
					CBfcVector_Shape2d_Bezier.cpp : 
	
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

namespace CBfcVector {

Shape2d_Bezier::Shape2d_Bezier(const Shape2d_Bezier *p_duper)
	: Shape2d(p_duper)
{
	if (p_duper)
		*this = *p_duper;
}

Shape2d_Bezier::~Shape2d_Bezier()
{
}

void *Shape2d_Bezier::Dup_const() const
{
	Shape2d_Bezier *p_ShapeDup = new Shape2d_Bezier (this);
	return (void *)p_ShapeDup;
}


void Shape2d_Bezier :: operator = (const Shape2d_Bezier &Other_2dBezier)
{
	Shape2d::Equals (Other_2dBezier);

//	m_Width.Set (rectangle.GetSize().GetX(), CBfc_Distance::EBFC_DISTANCEUNIT_UNIT);
//	m_Height.Set (rectangle.GetSize().GetY(), CBfc_Distance::EBFC_DISTANCEUNIT_UNIT);
}


Shape2d_Rect *Shape2d_Bezier::Calculate_EncompassingRetangle ()
{
	return NULL; // new Shape2d_Rect(*this);
}


bool Shape2d_Bezier::Intersects (Shape2d &Shape2d)
{
	const Shape2d_Rect	rect=*Calculate_EncompassingRetangle();
	return Shape2d.IntersectsRectangle (rect);
}

bool Shape2d_Bezier::IntersectsRectangle (const Shape2d_Rect &Rect2d)
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


BFC_RVAL Shape2d_Bezier::RenderToAlphaBitmap (const CBfc_2dRect sourceRect, CBfcImage::Bitmap_Alpha &destAlphaBitmap)
{
	// Needs Work
	return false;
}


// Returns a positive integer if the point is over the Shape
unsigned long Shape2d_Bezier::GetAlphaAt (const Point2d &pt)
{
	// Needs Work
	return false;
}

/*

// Calculate the next bezier point.

Point drawBezier(Point A, Point B, Point C, double t) {
	Point P;

	P.x = pow((1 - t), 2) * A.x + 2 * t * (1 -t) * B.x + pow(t, 2) * C.x;
	P.y = pow((1 - t), 2) * A.y + 2 * t * (1 -t) * B.y + pow(t, 2) * C.y;

	return P;
}

	abc[NUMPOINTS].setxy((float)x,(float)(SCREEN_HEIGHT - y));
	NUMPOINTS++;
		
	// Draw the red  dot.

	drawDot(x, SCREEN_HEIGHT - y);

	// If 3 points are drawn do the curve.

	if(NUMPOINTS == 3) {
		glColor3f(1.0,1.0,1.0);
		// Draw two legs of the triangle

		drawLine(abc[0], abc[1]);
		drawLine(abc[1], abc[2]);
		Point POld = abc[0];
		// Draw each segment of the curve.  Make t increment in
        //         smaller amounts for a more detailed curve. 
		for(double t = 0.0;t <= 1.0; t += 0.1) {
			Point P = drawBezier(abc[0], abc[1], abc[2], t);
			drawLine(POld, P);
			POld = P;
		}
		glColor3f(1.0,0.0,0.0);
		NUMPOINTS = 0;
	}
*/

}
