//*/
/*
					CBfc_2dRect.cpp : 
	
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

namespace CBfc
{
/*
void Rect2d :: operator *= (const Rect2d &mulRect2d)
{
    Position2d position;    CBfc_2dArea size;
    mulRect2d.Get (position, size);
    m_position *= position;
    m_size *= size;
}
*/


void Rect2d ::  operator = (const Rect2d &rect2d)
{
    rect2d.Get (m_position, m_size);
}

bool Rect2d ::  operator == (const Rect2d &rect2d) const
{
   Position2d	position;       Area2d size;
   rect2d.Get (position, size);
   return (m_position == position && m_size == size);
}

bool Rect2d ::  Encapsulates (const Rect2d rect2d) const
{
    Position2d position;       Area2d size;

    rect2d.Get (position, size);
    Position2d lowerLeft(position);
    lowerLeft += size;
    Position2d my_lowerLeft(m_position);
    my_lowerLeft += m_size;
    if (position < m_position || lowerLeft > my_lowerLeft)
        return false;
    return true;
}


Rect2d :: Rect2d (const Rect2d &rect2d)
{
    Set (rect2d);
}

Rect2d :: Rect2d (const Value &left, const Value &top, const Value &width, const Value &height)
{
    Set (left, top, width, height);
}

Rect2d :: Rect2d (const Position2d &position, const Area2d &size)
{
    Set (position, size);
}

void Rect2d :: Set (const Value &left, const Value &top, const Value &width, const Value &height)
{
	m_position.Set (left, top);
	m_size.Set (width, height);
}

void Rect2d :: Set (const Position2d &position, const Area2d &size)
{
	m_position = position;
	m_size = size;
}

void Rect2d :: Set (const Area2d &size)
{
	m_position.Zero();
	m_size = size;
}

void Rect2d :: SetPosition (const Position2d &position)
{
	m_position = position;
}

void Rect2d :: SetSize (const Area2d &size)
{
    m_size = size;
}

void Rect2d :: Set (const Rect2d &rect2d)
{
    *this = rect2d;
}

void Rect2d :: Get (Position2d &position, Area2d &size) const
{
	position = m_position;
    size = m_size;
}

void Rect2d :: Get (UINT &u_x, UINT &u_y, UINT &u_w, UINT &u_h) const
{
    m_position.Get (u_x, u_y);
    m_size.Get (u_w, u_h);
}

Size2d Rect2d :: GetSize(void) const
{
    return m_size;
}

Position2d Rect2d :: TopLeft(void) const
{
    return m_position;
}

Position2d Rect2d :: BottomRight() const
{
	return m_position + m_size;
}

Value Rect2d :: Width(void) const
{
	return m_size.GetX();
}

Value Rect2d :: Height(void) const
{
	return m_size.GetY();
}


}



