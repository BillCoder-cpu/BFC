//*/
/*
					CBfc_2dSize.cpp : 
	
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
#include <math.h>

namespace CBfc {

Size2d :: Size2d (void)
{
// 	Set (CBfc_Value(), CBfc_Value());
}

Size2d :: Size2d (const CBfc_Value &dimensionX, const CBfc_Value &dimensionY)
{
	Set (dimensionX, dimensionY);
}

Size2d :: Size2d (const Size2d &size)
{
	Set (size);
}

Size2d :: Size2d (const Size2dU &size)
{
	Set (size.GetX(),size.GetY());
}

/**
 * For a given (X,Y) offset within a square of size 'size', return the index from zero of the matrix
 * @param offset -
 * @return
 */
UINT Size2d::GetIndex (const Size2d &offset) const
{
	return offset.GetX() + offset.GetY() * GetX();
}

bool Size2d :: Iterate(const Size2d &size)
{
	if (IterateX(size))
		return true;
	return IterateY(size);
}

bool Size2d :: Iterate(const Size2d &size,const Size2d &increment)
{
	m_dimensionX += increment.GetX();
	if ((GetX() < size.GetX()))
		return true;
	SetX(0);
	m_dimensionY += increment.GetY();
	if (!(GetY() < size.GetY()))
	{
		SetY(0);
		return false;
	}
	return true;
}

bool Size2d :: Iterate(const Rect2d &rect)
{
	if (IterateX(rect))
		return true;
	return IterateY(rect);
}

bool Size2d :: IterateX(const Size2d &size)
{
	IncrementX();
	if (!(GetX() < size.GetX()))
	{
		SetX(0);
		return false;
	}
	return true;
}

bool Size2d :: IterateX(const Rect2d &rect)
{
	IncrementX();
	if (!(GetX() < rect.BottomRight().GetX()))
	{
		SetX(rect.TopLeft().GetX());
		return false;
	}
	return true;
}

bool Size2d :: IterateY(const Size2d &size)
{
	IncrementY();
	if (!(GetY() < size.GetY()))
	{
		SetY(0);
		return false;
	}
	return true;
}

bool Size2d :: IterateY(const Rect2d &rect)
{
	IncrementY();
	if (!(GetY() < rect.BottomRight().GetY()))
	{
		SetY(rect.TopLeft().GetY());
		return false;
	}
	return true;
}


Size2d Size2d :: Minimum (const Size2d &size1, const Size2d &size2)
{
    Size2d sizeMin;

    sizeMin.Set ( size1.GetX() < size2.GetX() ? size1.GetX() : size2.GetX(),
                     size1.GetY() < size2.GetY() ? size1.GetY() : size2.GetY() );
    return sizeMin;
}

Size2d Size2d :: Maximum (const Size2d &size1, const Size2d &size2)
{
    Size2d sizeMax;

    sizeMax.Set ( size1.GetX() > size2.GetX() ? size1.GetX() : size2.GetX(),
                     size1.GetY() > size2.GetY() ? size1.GetY() : size2.GetY() );
    return sizeMax;
}

void Size2d :: Get (CBfc_Value &dimensionX, CBfc_Value &dimensionY) const
{
    dimensionX = (m_dimensionX);    dimensionY = (m_dimensionY);
}

void Size2d :: Get (UINT &u_x, UINT &u_y) const
{
    u_x = (UINT)m_dimensionX.GetValue_UINT();  u_y = (UINT)m_dimensionY.GetValue_UINT();
}


bool Size2d :: operator  == (const Size2d &eqeqSize2d) const
{
    CBfc_Value dimensionX, dimensionY;

   eqeqSize2d.Get (dimensionX, dimensionY);
   return (dimensionX == m_dimensionX && dimensionY == m_dimensionY);
}

Size2d Size2d :: operator*(const double d_mul) const
{
    Size2d result;

    result.Set ((double)m_dimensionX * d_mul, (double)m_dimensionY * d_mul);
    return result;
}

Size2d Size2d :: operator*(const Size2d &mulSize2d) const
{
    CBfc_Value  dimensionX, dimensionY;
    Size2d result;

    mulSize2d.Get (dimensionX, dimensionY);
    result.Set (m_dimensionX * dimensionX, m_dimensionY * dimensionY);
    return result;
}

Size2d Size2d :: operator/(const double d_div) const
{
    Size2d result;

    result.Set ((double)m_dimensionX / d_div, (double)m_dimensionY / d_div);
    return result;
}

Size2d Size2d :: operator/(const Size2d &divSize2d) const
{
	CBfc_Value  dimensionX, dimensionY;
	Size2d result;

	divSize2d.Get (dimensionX, dimensionY);
	result.Set (m_dimensionX / dimensionX, m_dimensionY / dimensionY);
	return result;
}


Size2d Size2d :: operator+(const Size2d &addSize2d) const
{
    CBfc_Value  dimensionX, dimensionY;
    Size2d result;

    addSize2d.Get (dimensionX, dimensionY);
    result.Set (m_dimensionX + dimensionX, m_dimensionY + dimensionY);
    return result;
}
Size2d Size2d :: operator-(const Size2d &subSize2d) const
{
    CBfc_Value  dimensionX, dimensionY;
    Size2d result;

    subSize2d.Get (dimensionX, dimensionY);
    result.Set (m_dimensionX - dimensionX, m_dimensionY - dimensionY);
    return result;
}
Size2d Size2d :: operator%(const Size2d &subSize2d) const
{
    CBfc_Value  dimensionX, dimensionY;
    Size2d result;

    subSize2d.Get (dimensionX, dimensionY);
    result.Set ((UINT)m_dimensionX % (UINT)dimensionX, (UINT)m_dimensionY % (UINT)dimensionY);
    return result;
}

void Size2d :: operator    *= (const double d_mul)
{
    m_dimensionX *= d_mul;
    m_dimensionY *= d_mul;
}

void Size2d :: operator    *= (const Size2d &mulSize2d)
{
    CBfc_Value dimensionX, dimensionY;

    mulSize2d.Get (dimensionX, dimensionY);
    m_dimensionX *= dimensionX;
    m_dimensionY *= dimensionY;
}

void Size2d :: operator += (const Size2d &addSize2d)
{
    CBfc_Value dimensionX, dimensionY;

    addSize2d.Get (dimensionX, dimensionY);
    m_dimensionX += dimensionX;
    m_dimensionY += dimensionY;
}

void Size2d :: operator -= (const Size2d &subSize2d)
{
    CBfc_Value dimensionX, dimensionY;

    subSize2d.Get (dimensionX, dimensionY);
    m_dimensionX -= dimensionX;
    m_dimensionY -= dimensionY;
}

bool Size2d :: operator < (const Size2d &lessthanSize2d) const
{
    CBfc_Value dimensionX, dimensionY;

    lessthanSize2d.Get (dimensionX, dimensionY);
	return (m_dimensionX < dimensionX || m_dimensionY < dimensionY);
//     return (dimensionX < m_dimensionX  || dimensionY < m_dimensionY );
}

bool Size2d :: operator > (const Size2d &greaterthanSize2d) const
{
    CBfc_Value dimensionX, dimensionY;

    greaterthanSize2d.Get (dimensionX, dimensionY);
    return (m_dimensionX > dimensionX || m_dimensionY > dimensionY);
}

bool Size2d :: operator <= (const Size2d &lessthanSize2d) const
{
	CBfc_Value dimensionX, dimensionY;

	lessthanSize2d.Get (dimensionX, dimensionY);
	return (m_dimensionX <= dimensionX || m_dimensionY <= dimensionY);
//     return (dimensionX < m_dimensionX  || dimensionY < m_dimensionY );
}

bool Size2d :: operator >= (const Size2d &greaterthanSize2d) const
{
	CBfc_Value dimensionX, dimensionY;

	greaterthanSize2d.Get (dimensionX, dimensionY);
	return (m_dimensionX >= dimensionX || m_dimensionY >= dimensionY);
}

void	Size2d :: Zero()
{
	const UINT zero=0;
	m_dimensionX.SetValue(zero);
	m_dimensionY.SetValue(zero);
}

bool Size2d :: Set (const Size2d &size2d)
{
    CBfc_Value dimensionX, dimensionY;

    size2d.Get (dimensionX, dimensionY);
    return Set (dimensionX, dimensionY);
}

bool Size2d :: Set (const CBfc_Value &dimensionX, const CBfc_Value &dimensionY)
{
    m_dimensionX = (dimensionX);
    m_dimensionY = (dimensionY);
    return true;
}

void Size2d ::	SetX (const CBfc_Value &dimensionX)
{
    m_dimensionX = (dimensionX);
}

void Size2d ::	SetY (const CBfc_Value &dimensionY)
{
    m_dimensionY = (dimensionY);
}

void Size2d :: IncrementX ()
{
	m_dimensionX += 1;
}

void Size2d :: IncrementY ()
{
	m_dimensionY += 1;
}

void Size2d :: DecrementX ()
{
	m_dimensionX -= 1;
}

void Size2d :: DecrementY ()
{
	m_dimensionY -= 1;
}

bool Size2d :: Product(UINT &result) const
{
	result = m_dimensionX.GetValue_UINT() * m_dimensionY.GetValue_UINT();
	return (result != 0);
}

bool Size2d :: Product(double &result) const
{
	result = m_dimensionX.GetValue_double() * m_dimensionY.GetValue_double();
	return (result != 0.0);
}

bool Size2d :: Product(CBfc_Value &result) const
{
#pragma message ("Fill me in!!!")
	// fillin
	return false;
}

bool	Size2d::Encapsulates(const Size2d &siz) const
{
	if (siz >= *this)
		return false;
	Size2d zero(0,0);
	if (siz < zero)
		return false;
	return true;
}

	double Size2d::DistanceTo (const Size2d & siz) const
	{
		double dx = siz.GetX().GetValue_double() - GetX().GetValue_double();
		double dy = siz.GetY().GetValue_double() - GetY().GetValue_double();
		return sqrt ((dx * dx) + (dy * dy));
	}

}

