//*/
/*
					CBfcVector_Shape2d.h : 
	
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
// begun in 2000
// These types belong in a different class
//
//		SHAPE_ALPHA_FUNCTION,	// 8 bit opaciy function
//		SHAPE_ALPHA_BITMAP,		// 8 bit OPACITY CHANNEL
//		SHAPE_BITMAP,	

namespace CBfcVector
{

BFC_VECTOR_CLASS Shape2d_Rect;

BFC_VECTOR_CLASS Shape2d : public CBfc_ReferencedObject
{
public:
	typedef 
		enum BFC_API tagEShapeType2d 
	{
		SHAPE_UNINITIALIZED,
		SHAPE_2D_LINE,				// INCLUDES POINT
		SHAPE_2D_POLYGON,			// INCLUDES TRIANGLE,RECTANGLE,ETC.
		SHAPE_2D_BEZIER,
		SHAPE_2D_TEXT,
		SHAPE_2D_OVAL,
		SHAPE_2D_CURVE,
	} 
		EShapeType2d;

	Shape2d(const Shape2d *p_duper=NULL);
	virtual ~Shape2d();

public:
	EShapeType2d	GetShapeType (void) const {
		return m_shapeType;
	}
	CBfc::Position2d &GetPosition () {	
		return m_2dPosition;
	}
	CBfc::Position2d  GetPositionConst() const {
		return m_2dPosition;
	}

	virtual void *Dup() { return Dup_const(); }
	virtual void *Dup_const()const=0;
	//	Union ();		// Add two shapes together

	// Keep the limiting shape stored here if types do not easily integrate.
	bool LimitTo (const Shape2d &shapeLimit);	// Limit to another shape

	bool GetEncompassingRetangle (Shape2d_Rect &rectangle);
	bool EncompassingRectanglesIntersect (Shape2d &Shape2d);

	virtual bool Intersects (Shape2d &Shape2d)=0;
	virtual bool IntersectsRectangle (Shape2d_Rect &Rect2d);
	virtual bool IntersectsRectangle (const Shape2d_Rect &Rect2d);

	// Draw our shape as a mask into 8 bit alpha.
	virtual BFC_RVAL RenderToAlphaBitmap (const CBfc_2dRect sourceRect, CBfcImage::Bitmap_Alpha &destAlphaBitmap);
	// Returns a positive integer if the point is over the Shape
	virtual unsigned long GetAlphaAt (const CBfc::Point2d &pt);

protected:
	void operator = (const Shape2d &other_2dShape);  // Do NOT Make this public!!!!!!
	virtual void Equals(const Shape2d &other_2dShape);

	virtual Shape2d_Rect *Calculate_EncompassingRetangle (void)=0;
	void   SetDirty();					// must set this whenever shape changes

	EShapeType2d			m_shapeType;
private:
	CBfc::Position2d			m_2dPosition;

	Shape2d_Rect			*m_p_EncompassingRetangle;	// If NULL, needs recalculation!
	Shape2d				*m_p_Limiting2dShape;

	CBfcImage::Bitmap_Alpha		*m_p_AlphaBitmap;		// Usable if non-null.

	friend BFC_VECTOR_CLASS       Shape2d_Rect;
};

typedef Shape2d *Shape2d_PTR;

BFC_VECTOR_CLASS Shape2d_Ellipsoid : public Shape2d 
{
public:
	Shape2d_Ellipsoid ()
	{
		m_shapeType = (Shape2d::SHAPE_2D_OVAL);
	}

	void SetRadii (const Distance XR, const Distance &YR, const Distance &ZR) {
		m_XRadius = XR;		m_YRadius = YR;		m_ZRadius = ZR;
	}
	void GetRadii (Distance &XR, Distance &YR, Distance &ZR) const {
		XR = m_XRadius;		YR = m_YRadius;		ZR = m_ZRadius;
	}
protected:
	Distance	m_XRadius;
	Distance	m_YRadius;
	Distance	m_ZRadius;
};

BFC_VECTOR_CLASS Shape2d_Sphere : public Shape2d_Ellipsoid 
{
public:
	void SetRadius (const Distance Radius) { m_XRadius = m_YRadius = m_ZRadius = Radius; }
	inline Distance GetRadius (void) const { return m_XRadius; }
private:
};



/*
// Data structures for various drawing integers
typedef struct {
	int	iSize;
} DRAW_2D_CURVE;

typedef struct {
	int	iSize;
} DRAW_2D_BEZIER;

typedef struct {
	VIEW_COORDS_2D	co2Center;
} DRAW_2D_OVAL;

typedef struct {
	CBfc_Array<VIEW_COORDS_2D>	co2Points;
} DRAW_2D_POLYGON;

typedef struct {
	CBfc_String	sString;
	CBfc_String	Fontname;
	float		fPoints;		// Size of the text (in 72/inch)
} DRAW_2D_TEXT;

typedef struct {
	VIEW_COORDS_2D	co2From, co2To;
} DRAW_2D_LINE;

typedef struct {
	VIEW_COORDS_2D	co2At;
} DRAW_2D_BITMAP;

typedef struct {
} DRAW_3D_CUBE;

typedef struct {
	CBfc_Array<VIEW_COORDS_3D>	co3Points;
} DRAW_3D_VERTICES;

union DRAW_DESCRIPTION {
	DRAW_2D_CURVE		CurveDesc;
	DRAW_2D_BEZIER		BezierDesc;
	DRAW_2D_OVAL		OvalDesc;
//	DRAW_2D_POLYGON		PolygonDesc;
//	DRAW_2D_TEXT		TextDesc;
	DRAW_2D_LINE		LineDesc;
	DRAW_2D_BITMAP		BitmapDesc;
	DRAW_3D_CUBE		CubeDesc;
//	DRAW_3D_SPHERE		SphereDesc;
//	DRAW_3D_VERTICES	VertDesc;
} ;

class GRADIENT_2D {
	CBfc_Color		ColorFrom, ColorTo;		
	VIEW_COORDS_2D	co2Center;
	Angle			Direction;	// Angle of 0 indicates Circular
};

// CTexture describes the color, fill pattern, etc.
class CTexture {
	CBfc_Color		Color;
	GRADIENT_2D		*ColorGradient;
	GRADIENT_2D		*OpacityGradient;
	char			cOpacity;
};
*/

/*

*/



} // namespace






