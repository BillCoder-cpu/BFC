//*/
/*
					Rect2dU.cpp : 
	
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
	Rect2dU :: Rect2dU (const Rect2dU &rect2d)
	{
		Set (rect2d);
	}

	Rect2dU :: Rect2dU (const UINT left, const UINT top, const UINT width, const UINT height)
	{
		Set (left, top, width, height);
	}

	Rect2dU :: Rect2dU (const Position2dU &position, const Area2dU &size)
	{
		Set (position, size);
	}

	void Rect2dU :: Set (const UINT left, const UINT top, const UINT width, const UINT height)
	{
		m_position.Set (left, top);
		m_size.Set (width, height);
	}

	void Rect2dU :: Set (const Position2dU &position, const Area2dU &size)
	{
		m_position = position;
		m_size = size;
	}
	
	void Rect2dU :: Set (const Area2dU &size)
	{
		m_position.Zero();
		m_size = size;
	}

	void Rect2dU :: SetPosition (const Position2dU &position)
	{
		m_position = position;
	}

	void Rect2dU :: SetSize (const Area2dU &size)
	{
		m_size = size;
	}

	void Rect2dU :: Set (const Rect2dU &rect2d)
	{
		*this = rect2d;
	}

	void Rect2dU :: Get (Position2dU &position, Area2dU &size) const
	{
		position = m_position;
		size = m_size;
	}

	void Rect2dU :: Get (UINT &u_x, UINT &u_y, UINT &u_w, UINT &u_h) const
	{
		m_position.Get (u_x, u_y);
		m_size.Get (u_w, u_h);
	}

	void Rect2dU :: GetAbsolute (UINT &xul, UINT &yul, UINT &xlr, UINT &ylr) const
	{
		m_position.Get (xul, yul);
		m_size.Get (xlr, ylr);
		xlr += xul-1;
		ylr += yul-1;
	}

	Size2dU Rect2dU :: GetSize(void) const
	{
		return m_size;
	}

	Position2dU Rect2dU :: TopLeft(void) const
	{
		return m_position;
	}

	Position2dU Rect2dU :: BottomRight() const
	{
		return m_position + m_size;
	}

	UINT Rect2dU :: Width(void) const
	{
		return m_size.GetX();
	}

	UINT Rect2dU :: Height(void) const
	{
		return m_size.GetY();
	}

	void Rect2dU ::operator = (const Rect2dU &rect2d)
	{
		rect2d.Get (m_position, m_size);
	}

	bool Rect2dU ::operator == (const Rect2dU &rect2d) const
	{
		Position2dU	position;       Area2dU size;
		rect2d.Get (position, size);
		return (m_position == position && m_size == size);
	}
	
	Rect2dU Rect2dU ::operator*(const double dmul) const
	{
		return Rect2dU(m_position*dmul, m_size*dmul);
	}

	/// make an encompassing rectangle
	Rect2dU Rect2dU ::operator+(const Rect2dU &AddRect) const
	{
//		Rect2dU n = new Rect2dU(r);
//		n.OR(AddRect);
//		return n;
		return Rect2dU( Point2dU::Minimum (m_position, AddRect.TopLeft()), 
				Point2dU::Maximum (BottomRight(), AddRect.BottomRight()) - m_position);
	}


	// Expand this rectangle to include (encapsulate) rect
	void Rect2dU::OR(const Rect2dU &rect)
	{
		if (Width() == 0 || Height() == 0)
			Set(rect);
		else
		{
			Position2dU br(BottomRight());
			if (rect.TopLeft().GetX() < TopLeft().GetX())
			{
				m_position.SetX(rect.TopLeft().GetX());
				SetWidth(br.GetX()-m_position.GetX());
			}
			if (rect.TopLeft().GetY() < TopLeft().GetY())
			{
				m_position.SetY(rect.TopLeft().GetY());
				SetHeight(br.GetY() - m_position.GetY());
			}
			if (rect.BottomRight().GetX() > br.GetX())
				m_size.SetX(rect.BottomRight().GetX() - TopLeft().GetX());
			if (rect.BottomRight().GetY() > br.GetY())
				m_size.SetY(rect.BottomRight().GetY() - TopLeft().GetY());
		}
	}

	void Rect2dU ::  SetWidth(UINT w)
	{
		m_size.SetX(w);
	}

	void Rect2dU ::  SetHeight(UINT h)
	{
		m_size.SetY(h);
	}

	bool Rect2dU ::  Encapsulates (const Rect2dU rect2d) const
	{
		Position2dU position;       Area2dU size;

		rect2d.Get (position, size);
		Position2dU lowerLeft(position);
		lowerLeft += size;
		
		Position2dU my_lowerLeft(m_position);
		my_lowerLeft += m_size;
		if (position < m_position || lowerLeft > my_lowerLeft)
			return false;
		return true;
	}

	bool Rect2dU :: Encapsulates (const Point2dU point2d) const
	{
		if (point2d < m_position || point2d >= m_position+m_size)
			return false;
		return true;
	}
	
}


