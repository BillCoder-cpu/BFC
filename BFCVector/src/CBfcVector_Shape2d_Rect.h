//*/
/*
					CBfcVector_Shape2d_Rect.h : 
	
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

BFC_VECTOR_CLASS Shape2d_Rect : public Shape2d, public CBfc::Rect2d
{
public:
	Shape2d_Rect (const Shape2d_Rect *p_duper);
	Shape2d_Rect ()
	{
		m_shapeType = (Shape2d::SHAPE_2D_POLYGON);
	}
	Shape2d_Rect (const CBfc_2dRect &rectangle)
	{
		m_shapeType = (Shape2d::SHAPE_2D_POLYGON);
		*this = rectangle;
	}
	virtual ~Shape2d_Rect ();

public:	
	void operator = (const Shape2d_Rect &);

	virtual void *Dup_const() const;
	virtual bool Intersects (Shape2d &Shape2d);
	virtual bool IntersectsRectangle (const Shape2d_Rect &Rect2d);

	virtual BFC_RVAL RenderToAlphaBitmap (const CBfc_2dRect sourceRect, CBfcImage::Bitmap_Alpha &destAlphaBitmap);
			// Returns a positive integer if the point is over the Shape
	virtual unsigned long GetAlphaAt (const CBfc::Point2d &pt);
protected:
	virtual Shape2d_Rect *Calculate_EncompassingRetangle ();
private:
	Distance	m_Width, m_Height;
};

}

