//*/
/*
					CBfcRIP_scene.h : 
	
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

class CBfcRIP_Scene
{
private:
	CBfc_Array<CBfcRIP_LightSource>	m_LightSourceList;
	CBfc_Array<Draw>				m_DrawList;
};

class CBfcVector_Surface
{
	CBfcVector_2dShape	*m_p_outline;	// 
	CBfcVector_2dPlane	m_plane;
};

class CBfcRIP_LightSource
{
	CBfc_Value	Intensity;		// Lumens / CandlePower
};

///////////////////////////////////////
// Describes the objects dimensions in refernce to an orgin
// 
class	CBfc_Object3D
{
	CBfc_Array<CBfcVector_Surface>	surfaces;
};

class DrawShape 
{
private:
	bool				m_b_3D;			// boolean
	CBfcVector_2dShape	*m_shape2d;
	CBfcVector_3dShape	*m_shape3d;
};

/* Holds the Info decribing a simple rendering */
class Draw 
{
	int						iSize;
	DrawShape				Shape;
//	CTexture				Texture;
//	union DRAW_DESCRIPTION	Desc;
};


// target Context
class CBfcRIP_Target
{
public:
	virtual ~CBfcRIP_Target();

	virtual	StartPage ();
	virtual	RenderSingleDraw ();
	virtual EndPage ();
protected:
private:
};

class CBfcRIP_TargetBitmap : public CBfcRIP_Target
{
public:
	CBfcRIP_TargetBitmap (CBfcImage_Bitmap *p_targetBmp);
private:
	CBfcImage_Bitmap	*m_p_TargetBitmap;
};


/* A SCOPE is the same thing as a viewpoint */
class CBfcRIP_Viewpoint 
{
	bool	b3D;
	double	Zoom;
private:
	CBfcVector_Surface	m_ProjectionWindow;
	CBfcVector_2dPlane	m_HitherPlane, m_YonPlane;
};

class CBfcRIP_RenderingIntent 
{
public:
	CBfcRIP_RenderingIntent();
	virtual ~CBfcRIP_RenderingIntent();

	bool Render (CBfcRIP_Viewpoint *p_Viewpoint, CBfcRIP_Target *p_Target);
protected:
	bool DetermineVisiblity (const Draw &drawObject/*, Clip */);
private:
	CBfcRIP_Scene		*m_p_Scene;
};


