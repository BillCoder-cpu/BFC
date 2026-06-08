//*/
/*
					CBfc_Range2d.cpp : 
	
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
/*
Position2dU Range2d::StartIteration(Position2d &pos)
{
	Position2dU pos(m_rect.TopLeft());
	switch(m_rangeType)
	{
		case EBFC_RANGE_COLUMNS:
			pos.SetY(0);
			break;
		case EBFC_RANGE_ROWS:
			pos.SetX(0);
			break;
	}
	return pos;
}

bool Range2d::GetNext(Position2d &pos)
{
	pos = (m_curpos);

	switch(m_rangeType)
	{
		case EBFC_RANGE_NONE:
			return false;
		case EBFC_RANGE_RANGE:
		case EBFC_RANGE_COLUMNS:
			if (m_curpos.GetX() > m_rect.BottomRight().GetX())
				return false;
			m_curpos += Position2d(0,1);
			if (m_curpos.GetY() > m_rect.BottomRight().GetY())
			{
				if (m_rangeType==EBFC_RANGE_COLUMNS)
					m_curpos.SetY(0);
				else
					m_curpos.SetY(m_rect.TopLeft().GetY());
				m_curpos += Position2d(1,0);
			}
			break;
		case EBFC_RANGE_ROWS:
			if (m_curpos.GetY() > m_rect.BottomRight().GetY())
				return false;
			m_curpos += Position2d(1,0);
			if (m_curpos.GetX() > m_rect.BottomRight().GetX())
			{
				m_curpos.SetX(0);
				m_curpos += Position2d(0,1);
			}
			break;
	}
	return true;
}
*/

bool Range2dU::StartIteration(Position2dU &pos) const
{
	pos.Set (m_rect.TopLeft());
	switch(m_rangeType)
	{
		case EBFC_RANGE_COLUMNS:
			pos.SetY(0);
			break;
		case EBFC_RANGE_ROWS:
			pos.SetX(0);
			break;
	}
	return true;
}

bool Range2dU::GetNext(Position2dU &pos) const
{
	switch(m_rangeType)
	{
		case EBFC_RANGE_NONE:
			return false;
		case EBFC_RANGE_RANGE:
		case EBFC_RANGE_COLUMNS:
			pos += Position2dU(0,1);
			if (pos.GetY() >= m_rect.BottomRight().GetY())
			{
				if (m_rangeType==EBFC_RANGE_COLUMNS)
					pos.SetY(0);
				else
					pos.SetY(m_rect.TopLeft().GetY());
				pos += Position2dU(1,0);
				if (pos.GetX() >= m_rect.BottomRight().GetX())
					return false;
			}
			break;
		case EBFC_RANGE_ROWS:
			pos += Position2dU(1,0);
			if (pos.GetX() >= m_rect.BottomRight().GetX())
			{
				pos.SetX(0);
				pos += Position2dU(0,1);
				if (pos.GetY() >= m_rect.BottomRight().GetY())
					return false;
			}
			break;
	}
	return true;
}


}

