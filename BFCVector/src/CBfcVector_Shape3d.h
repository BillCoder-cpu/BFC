//*/
/*
					CBfcVector_Shape3d.h : 
	
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

BFC_VECTOR_CLASS Shape3d
{
public:
	typedef enum BFC_API tagEBfcVector_3dShapeType {
		SHAPE3D_UNINITIALIZED,
		SHAPE3D_3D_CUBE,
		SHAPE3D_3D_SPHERE,
		SHAPE3D_3D_VERTICES,
		SHAPE3D_3D_SHAPED_EDGES,	// CAN HAVE VARIOUS BEZIER, LINE, FACES.
//		SHAPE_3D_CURVE,
		SHAPE3D_3D_ALPHA_FUNCTION,
//		SHAPE_3D_ALPHA_BITMAP,
	} EBfcVector_3dShapeType;

	Shape3d ();
	virtual ~Shape3d();

public:
	EBfcVector_3dShapeType GetShapeType (void) const;

	BFC_RVAL RenderToBitmap (CBfcImage::Bitmap &destBitmap);
protected:
	EBfcVector_3dShapeType		m_shapeType;

};

BFC_VECTOR_CLASS Shape3d_Box : public Shape3d 
{
public:
	Shape3d_Box ()
	{
		m_shapeType = (Shape3d::SHAPE3D_3D_CUBE);
	}
private:
	Distance	Width, Height, Depth;
};

}
