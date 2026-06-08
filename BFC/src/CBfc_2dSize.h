//*/
/*
					CBfc_2dSize.h : 
	
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

#ifndef _CBFC_AREA_H__
#define _CBFC_AREA_H__

/*
  CBfc_Area.h   CBfc_Area

  Needs Measure Units support!!!!!!!!!!
  - DISTANCE - SEE VECTORE_SHAPE.H
*/

#include "BFCDefs.h"
#include "CBfc_Value.h"

namespace CBfc {

BFC_CLASS Size2d;
BFC_CLASS Rect2d;
BFC_CLASS Rect2dU;

#define CBfc_2dSize CBfc::Size2d

BFC_CLASS Size2dU : public CBfc_Object
{
	public:
		Size2dU (void);
		Size2dU (const UINT dimensionX, const UINT dimensionY);
		Size2dU (const Size2d &size);
		Size2dU (const Size2dU &size);

		void    Get (UINT &u_x, UINT &u_y) const;

		const UINT GetX() const {
			return m_dimensionX;
		}
		const UINT GetY() const {
			return m_dimensionY;
		}
		UINT Product() const;
		bool Product(UINT &result) const;
		bool	Encapsulates(const Size2dU &siz) const;
		void OR(const Rect2dU &rect);
	
		static Size2dU Minimum (const Size2dU &size1, const Size2dU &size2);
		static Size2dU Maximum(const Size2dU &size1, const Size2dU &size2);
		static Size2dU IMaximum(const Size2dU &size1, const Size2dU &size2);
		static Size2dU IMinimum (const Size2dU &size1, const Size2dU &size2);

		void	Zero() {m_dimensionX = m_dimensionY = 0;}
		bool    Set (const UINT dimensionX, const UINT dimensionY);
		bool    Set (const Size2dU &size2d);
		void	SetX (const UINT dimensionX);
		void	SetY (const UINT dimensionY);

		UINT GetIndex (const Size2dU &offset) const;

		bool Iterate(const Size2dU &size);
		bool Iterate(const Size2dU &size,const Size2dU &increment);
		bool Iterate(const Rect2dU &rect);
		bool IterateX(const Size2dU &size);
		bool IterateX(const Rect2dU &rect);
		bool IterateY(const Size2dU &size);
		bool IterateY(const Rect2dU &rect);

		void	IncrementX ();
		void	IncrementY ();
		void	DecrementX ();
		void	DecrementY ();

		Size2dU operator*(const Size2dU &mulSize2d) const;
		Size2dU operator*(const double d_mul) const;
		Size2dU operator/(const Size2dU &divSize2d) const;
		Size2dU operator/(const double d_div) const;
		Size2dU operator+(const Size2dU &addSize2d) const;
		Size2dU operator-(const Size2dU &subSize2d) const;
		Size2dU operator % (const Size2dU &subSize2d) const;

		bool operator    == (const Size2dU &eqeqSize2d) const;
		void operator    *= (const Size2dU &mulSize2d);
		void operator    *= (const double d_mul);
		void operator    += (const Size2dU &addSize2d);
		void operator    -= (const Size2dU &subSize2d);

		bool operator    < (const Size2dU &lessthanSize2d) const;
		bool operator    > (const Size2dU &greaterthanSize2d) const;
		bool operator    <= (const Size2dU &lessthanSize2d) const;
		bool operator    >= (const Size2dU &greaterthanSize2d) const;
	private:
		UINT			m_dimensionX, m_dimensionY;
};

BFC_CLASS Size2d : public CBfc_Object
{
public:
	Size2d (void);
//    CBfc_Area (const CBfc_Value dimensionX, const CBfc_Value dimensionY);
	Size2d (const Value &dimensionX, const Value &dimensionY);
	Size2d (const Size2d &size);
	Size2d (const Size2dU &size);

	void    Get (Value &dimensionX, Value &dimensionY) const;
	void    Get (UINT &u_x, UINT &u_y) const;

	const CBfc_Value  &GetX() const {
		return m_dimensionX;
	}
	const CBfc_Value  &GetY() const {
		return m_dimensionY;
	}

	bool Product(UINT &result) const;
	bool Product(double &result) const;
	bool Product(CBfc_Value &result) const;
	
	bool	Encapsulates(const Size2d &siz) const;
	double DistanceTo (const Size2d & siz) const;
	
	static Size2d Minimum (const Size2d &size1, const Size2d &size2);
	static Size2d Maximum(const Size2d &size1, const Size2d &size2);

	void	Zero();
	bool    Set (const CBfc_Value &dimensionX, const CBfc_Value &dimensionY);
	bool    Set (const Size2d &size2d);
	void	SetX (const CBfc_Value &dimensionX);
	void	SetY (const CBfc_Value &dimensionY);

	UINT GetIndex (const Size2d &offset) const;
			
	bool Iterate(const Size2d &size);
	bool Iterate(const Rect2d &rect);
	bool Iterate(const Size2d &size,const Size2d &increment);
	bool IterateX(const Size2d &size);
	bool IterateX(const Rect2d &rect);
	bool IterateY(const Size2d &size);
	bool IterateY(const Rect2d &rect);

	void	IncrementX ();
	void	IncrementY ();
	void	DecrementX ();
	void	DecrementY ();

	Size2d operator*(const Size2d &mulSize2d) const;
	Size2d operator*(const double d_mul) const;
	Size2d operator/(const Size2d &divSize2d) const;
	Size2d operator/(const double d_div) const;
	Size2d operator+(const Size2d &addSize2d) const;
	Size2d operator-(const Size2d &subSize2d) const;
	Size2d operator % (const Size2d &subSize2d) const;

	bool operator    == (const Size2d &eqeqSize2d) const;
	void operator    *= (const Size2d &mulSize2d);
	void operator    *= (const double d_mul);
	void operator    += (const Size2d &addSize2d);
	void operator    -= (const Size2d &subSize2d);

	bool operator    < (const Size2d &lessthanSize2d) const;
	bool operator    > (const Size2d &greaterthanSize2d) const;
	bool operator    <= (const Size2d &lessthanSize2d) const;
	bool operator    >= (const Size2d &greaterthanSize2d) const;

private:
	CBfc_Value		m_dimensionX, m_dimensionY;
//	CBfc_Distance	m_dimensionX, m_dimensionY;
};

BFC_CLASS Size2dF : public CBfc_Object
{
	public:
		Size2dF (void);
		Size2dF (const float dimensionX, const float dimensionY);
		Size2dF (const Size2d &size);
		Size2dF (const Size2dF &size);
		Size2dF (const Size2dU &size);

		void    Get (float &u_x, float &u_y) const;

		const float GetX() const {
			return m_dimensionX;
		}
		const float GetY() const {
			return m_dimensionY;
		}
		float Product() const;
		bool Product(float &result) const;
		bool	Encapsulates(const Size2dF &siz) const;
		void OR(const Rect2d &rect);
	
		static Size2dF Minimum (const Size2dF &size1, const Size2dF &size2);
		static Size2dF Maximum(const Size2dF &size1, const Size2dF &size2);
		static Size2dF IMaximum(const Size2dF &size1, const Size2dF &size2);
		static Size2dF IMinimum (const Size2dF &size1, const Size2dF &size2);

		void	Zero() {m_dimensionX = m_dimensionY = 0;}
		bool    Set (const float dimensionX, const float dimensionY);
		bool    Set (const Size2dF &size2d);
		void	SetX (const float dimensionX);
		void	SetY (const float dimensionY);

		UINT GetIndex (const Size2dF &offset) const;

		void	IncrementX ();
		void	IncrementY ();
		void	DecrementX ();
		void	DecrementY ();

		Size2dF operator*(const Size2dF &mulSize2d) const;
		Size2dF operator*(const double d_mul) const;
		Size2dF operator/(const Size2dF &divSize2d) const;
		Size2dF operator/(const double d_div) const;
		Size2dF operator+(const Size2dF &addSize2d) const;
		Size2dF operator-(const Size2dF &subSize2d) const;

		bool operator    == (const Size2dF &eqeqSize2d) const;
		void operator    *= (const Size2dF &mulSize2d);
		void operator    *= (const double d_mul);
		void operator    += (const Size2dF &addSize2d);
		void operator    -= (const Size2dF &subSize2d);

		bool operator    < (const Size2dF &lessthanSize2d) const;
		bool operator    > (const Size2dF &greaterthanSize2d) const;
		bool operator    <= (const Size2dF &lessthanSize2d) const;
		bool operator    >= (const Size2dF &greaterthanSize2d) const;
	private:
		float			m_dimensionX, m_dimensionY;
};

typedef Size2d Area2d;
typedef Size2d Position2d;
typedef Size2d Point2d;
typedef Size2d ValuePair;

typedef Size2dU Area2dU;
typedef Size2dU Position2dU;
typedef Size2dU Point2dU;
typedef Size2dU ValuePairU;

typedef Size2dF Position2dF;

}

#endif // ifndef _CBFC_AREA_H__






