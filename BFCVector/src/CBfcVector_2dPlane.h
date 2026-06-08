//*/
/*
					CBfcVector_2dPlane.h : 
	
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

/* Holds the definition of a 2D or 3D representation */
class VIEW_COORDS_2D // - could use CBfc_2dPosition
{
	double x,y;
};

class VIEW_COORDS_3D // - could use CBfc_3dPosition
{
	double x,y,z;
};

class Plane2d
{
	CBfc::Position3d	m_pointOrigin;
	SpaceVector	m_vectorPositiveXAxis;
	SpaceVector	m_vectorPositiveYAxis;
};

}


