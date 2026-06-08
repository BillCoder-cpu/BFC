//*/
/*
					CBfc_PointSpace3d.h : 
	
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

namespace CBfc {

BFC_CLASS Position3d : public CBfc_Object
{
public:
	virtual ~Position3d ();
	Position3d (void);
    Position3d (const CBfc_Value &positionX, const CBfc_Value &positionY, const CBfc_Value &positionZ);

    void    Get (CBfc_Value &positionX, CBfc_Value &positionY, CBfc_Value &positionZ) const;
    void    Get (UINT &u_x, UINT &u_y, UINT &u_z) const;

    const CBfc_Value  &GetX() const {
        return m_positionX;
    }
    const CBfc_Value  &GetY() const {
        return m_positionY;
    }
    const CBfc_Value  &GetZ() const {
        return m_positionZ;
    }

//    static CBfc_3dPosition CBfc_3dPosition::Minimum (const CBfc_3dPosition size1, const CBfc_3dPosition size2);

    bool    Set (const CBfc_Value &positionX, const CBfc_Value &positionY, const CBfc_Value &positionZ);
    bool    Set (const Position3d &position3d);

//    CBfc_2dSize operator*(const Position3d &mulSize2d) const;
//    CBfc_2dSize operator+(const CBfc_2dSize &addSize2d) const;
//    CBfc_2dSize operator-(const CBfc_2dSize &subSize2d) const;

    bool operator    == (const Position3d &eqeqSize3d) const;
//    void operator    *= (const CBfc_2dSize &mulSize2d);
//    void operator    += (const CBfc_2dSize &addSize2d);
//    void operator    -= (const CBfc_2dSize &subSize2d);

//    bool operator    < (const CBfc_2dSize &lessthanSize2d) const;
//    bool operator    > (const CBfc_2dSize &greaterthanSize2d) const;

private:
    class CBfc_Value    m_positionX, m_positionY, m_positionZ;
};


typedef Position3d Volume3d;
typedef Position3d ValueTriplet;
typedef Position3d PointSpace;
typedef Position3d PointSpace3d;
typedef Position3d Direction3d;
//typedef Position3d SpaceVector;

}



