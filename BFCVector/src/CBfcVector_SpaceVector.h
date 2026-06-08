//*/
/*
					CBfcVector_SpaceVector.h : 
	
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

// see CBfc_PointSpaceTime
// typedef CBfc_3dPosition CBfc_SpaceVector;
namespace CBfcVector
{

// needs work!
//
BFC_VECTOR_CLASS SpaceVector
{
public:
	SpaceVector(void);
	SpaceVector (const CBfc_Value &X, const CBfc_Value &Y,const CBfc_Value &Z,const CBfc_Value &dx,const CBfc_Value &dy,const CBfc_Value &dz);
	void Set (const SpaceVector &vector);
	void Set (const CBfc::Position3d &position, const CBfc::Direction3d &direction);
	void Set (const CBfc_Value &X, const CBfc_Value &Y,const CBfc_Value &Z,const CBfc_Value &dx,const CBfc_Value &dy,const CBfc_Value &dz);
	void Get (CBfc::Position3d &position, CBfc::Direction3d &direction) const;
protected:
private:
	CBfc::Position3d	m_position;
	CBfc::Direction3d	m_direction;
//	CBfc_Value			m_length;
};

}
