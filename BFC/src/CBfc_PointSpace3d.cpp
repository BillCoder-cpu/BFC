//*/
/*
					CBfc_PointSpace3d.cpp : 
	
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

#include <BFC/BFC.h>

namespace CBfc {

Position3d::~Position3d ()
{
}

Position3d ::Position3d (void)
{
}

Position3d ::Position3d (const CBfc_Value &positionX, const CBfc_Value &positionY, const CBfc_Value &positionZ)
{
	Set (positionX, positionY, positionZ);
}

void Position3d ::Get (CBfc_Value &positionX, CBfc_Value &positionY, CBfc_Value &positionZ) const
{
	positionX = m_positionX;
	positionY = m_positionY;
	positionZ = m_positionZ;
}

void Position3d ::Get (UINT &u_x, UINT &u_y, UINT &u_z) const
{
	u_x = m_positionX.GetValue_UINT ();
	u_y = m_positionY.GetValue_UINT ();
	u_z = m_positionZ.GetValue_UINT ();
}

bool    Position3d ::Set (const CBfc_Value &positionX, const CBfc_Value &positionY, const CBfc_Value &positionZ)
{
	m_positionX = positionX;
	m_positionY = positionY;
	m_positionZ = positionZ;
	return true;
}

bool    Position3d ::Set (const Position3d &position3d)
{
	CBfc_Value	X,Y,Z;
	position3d.Get (X,Y,Z);
	return Set (X,Y,Z);
}

bool Position3d :: operator == (const Position3d &eqeqSize3d) const
{
	CBfc_Value	X,Y,Z;
	eqeqSize3d.Get (X,Y,Z);
	return m_positionX==X && m_positionY==Y && m_positionZ==Z;
}

}

