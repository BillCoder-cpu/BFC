//*/
/*
					CBfc_Range2d.h : 
	
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

BFC_CLASS Range2d
{
public:
	typedef enum BFC_API tagEBFC_DistanceUnits {
		EBFC_RANGE_NONE,					//	
		EBFC_RANGE_RANGE,
		EBFC_RANGE_COLUMNS,
		EBFC_RANGE_ROWS,
    } EBFC_RangeType;

	Range2d()
	{
		Empty();
	}
	Range2d(UINT x,UINT y,UINT w,UINT h)
	{
		Set(x,y,w,h);
	}
	void Empty()
	{
		m_rangeType=EBFC_RANGE_NONE;
	}
	bool IsEmpty()
	{
		return (m_rangeType==EBFC_RANGE_NONE);
	}
	void Set(UINT x,UINT y,UINT w,UINT h)
	{
		m_rangeType=EBFC_RANGE_RANGE;
		m_rect.Set(x,y,w,h);
	}
	void Get(Rect2d &rect) const
	{
		rect = m_rect;
	}
/*
	bool 	StartIteration(Position2d &pos) const;
	bool	GetNext(Position2d &pos) const;
*/
	Rect2d			m_rect;
	EBFC_RangeType	m_rangeType;
};

BFC_CLASS Range2dU
{
	public:
		typedef enum BFC_API tagEBFC_DistanceUnits {
			EBFC_RANGE_NONE,					//	
			EBFC_RANGE_RANGE,
			EBFC_RANGE_COLUMNS,
			EBFC_RANGE_ROWS,
		} EBFC_RangeType;

		Range2dU()
		{
			Empty();
		}
		Range2dU(const UINT x,const UINT y,const UINT w,const UINT h)
		{
			Set(x,y,w,h);
		}
		Range2dU (const Rect2dU &r)
		{
			m_rangeType=EBFC_RANGE_RANGE;
			m_rect.Set(r);
		}
		
		void Empty()
		{
			m_rangeType=EBFC_RANGE_NONE;
		}
		bool IsEmpty()
		{
			return (m_rangeType==EBFC_RANGE_NONE);
		}
		
		void Set(UINT x,UINT y,UINT w,UINT h)
		{
			m_rangeType=EBFC_RANGE_RANGE;
			m_rect.Set(x,y,w,h);
		}
		void SetAbsolute(int xtop, int ytop, int xbot, int ybot)
		{
			m_rangeType=EBFC_RANGE_RANGE;
			m_rect.Set(xtop,ytop,xbot-xtop,ybot-ytop);
		}
		
		void Get(Rect2dU &rect) const
		{
			rect = m_rect;
		}

		bool		StartIteration(Position2dU &pos) const;
		bool		GetNext(Position2dU &pos) const;

		Rect2dU			m_rect;
		EBFC_RangeType	m_rangeType;
};

}
