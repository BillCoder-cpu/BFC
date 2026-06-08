//*/
/*
					CBfcVector_SpaceVector.cpp : 
	
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

namespace CBfcVector
{
	using namespace CBfc;

SpaceVector::SpaceVector(void)
{
}

SpaceVector::SpaceVector (const CBfc_Value &X, const CBfc_Value &Y,const CBfc_Value &Z,const CBfc_Value &dx,const CBfc_Value &dy,const CBfc_Value &dz)
{
	Set (X, Y,Z, dx, dy, dz);
}

void SpaceVector::Set (const SpaceVector &vector)
{
	Position3d position;
	Direction3d direction;
	vector.Get (position, direction);
	Set(position, direction);
}

void SpaceVector::Set (const Position3d &position, const Direction3d &direction)
{
	m_position.Set(position);
	m_direction.Set(direction);
}

void SpaceVector::Set (const CBfc_Value &X, const CBfc_Value &Y,const CBfc_Value &Z,const CBfc_Value &dx,const CBfc_Value &dy,const CBfc_Value &dz)
{
	Set (Position3d(X,Y,Z), Direction3d(dx,dy,dz));
}

void SpaceVector::Get (Position3d &position, Direction3d &direction) const
{
	position.Set (m_position);
	direction.Set (m_direction);
}

}



