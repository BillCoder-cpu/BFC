//*/
/*
					CBfcVector_Coordinates.h : 
	
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

// Given the current viewport, locate coordniates on the screen
BFC_VECTOR_CLASS  CoordinateSystem
{
public:
	void	SetViewpoint (const SpaceVector &viewpoint);
	void	SetViewSize (const CBfc::Size2d &size);		// example: 1024x768
protected:
	SpaceVector		m_viewPoint;
	CBfc::Size2d	m_viewSize;
};

BFC_VECTOR_CLASS  CoordinateSystem2d : public CoordinateSystem
{
public:
	void GetScreenCoordinates (const CBfc::Position2d &pos2d, CBfc::Point2d &point) const;
};

BFC_VECTOR_CLASS  CoordinateSystem3d : public CoordinateSystem
{
public:
	void GetScreenCoordinates (const CBfc::Position3d &pos3d, CBfc::Point2d &point) const;
};


}
