//*/
/*
					Size2dU.cpp : 
	
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
	Size2dU :: Size2dU (void)
	{
		Set (0,0);
	}
	Size2dU :: Size2dU (const UINT dimensionX, const UINT dimensionY)
	{
		Set (dimensionX, dimensionY);
	}
	Size2dU :: Size2dU (const Size2dU &size)
	{
		Set (size);
	}
	Size2dU :: Size2dU (const Size2d &size)
	{
		Set (size.GetX(),size.GetY());
	}
/**
	 * For a given (X,Y) offset within a square of size 'size', return the index from zero of the matrix
	 * @param offset - 
	 * @return 
 */
	UINT Size2dU::GetIndex (const Size2dU &offset) const
	{
		return offset.GetX() + offset.GetY() * GetX();
	}
	bool Size2dU :: Iterate (const Size2dU &size)
	{
		if (IterateX(size))
			return true;
		return IterateY(size);
	}
	bool Size2dU :: Iterate (const Rect2dU &rect)
	{
		if (IterateX(rect))
			return true;
		return IterateY(rect);
	}
	
	bool Size2dU :: Iterate (const Size2dU &size,const Size2dU &increment)
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
	bool Size2dU :: IterateX (const Size2dU &size)
	{
		IncrementX();
		if (!(GetX() < size.GetX()))
		{
			SetX(0);
			return false;
		}
		return true;
	}
	bool Size2dU :: IterateX (const Rect2dU &rect)
	{
		IncrementX();
		if (!(GetX() < rect.BottomRight().GetX()))
		{
			SetX(rect.TopLeft().GetX());
			return false;
		}
		return true;
	}
	bool Size2dU :: IterateY (const Size2dU &size)
	{
		IncrementY();
		if (!(GetY() < size.GetY()))
		{
			SetY(0);
			return false;
		}
		return true;
	}
	bool Size2dU :: IterateY (const Rect2dU &rect)
	{
		IncrementY();
		if (!(GetY() < rect.BottomRight().GetY()))
		{
			SetY(rect.TopLeft().GetY());
			return false;
		}
		return true;
	}
	void Size2dU :: Get (UINT &u_x, UINT &u_y) const
	{
		u_x = m_dimensionX;  u_y = m_dimensionY;
	}
	bool Size2dU :: operator == (const Size2dU &eqeqSize2d) const
	{
		return (eqeqSize2d.GetX() == m_dimensionX && eqeqSize2d.GetY() == m_dimensionY);
	}
	Size2dU Size2dU :: operator * (const double d_mul) const
	{
		Size2dU result;

		result.Set ((UINT)(m_dimensionX * d_mul), (UINT)(m_dimensionY * d_mul));
		return result;
	}
	Size2dU Size2dU :: operator * (const Size2dU &mulSize2d) const
	{
		UINT  dimensionX, dimensionY;
		Size2dU result;

		mulSize2d.Get (dimensionX, dimensionY);
		result.Set (m_dimensionX * dimensionX, m_dimensionY * dimensionY);
		return result;
	}
	Size2dU Size2dU :: operator / (const double d_div) const
	{
		Size2dU result;

		result.Set ((UINT)(m_dimensionX / d_div), (UINT)(m_dimensionY / d_div));
		return result;
	}
	Size2dU Size2dU :: operator / (const Size2dU &divSize2d) const
	{
		UINT  dimensionX, dimensionY;
		Size2dU result;

		divSize2d.Get (dimensionX, dimensionY);
		result.Set (m_dimensionX / dimensionX, m_dimensionY / dimensionY);
		return result;
	}
	Size2dU Size2dU :: operator + (const Size2dU &addSize2d) const
	{
		UINT  dimensionX, dimensionY;
		Size2dU result;

		addSize2d.Get (dimensionX, dimensionY);
		result.Set (m_dimensionX + dimensionX, m_dimensionY + dimensionY);
		return result;
	}
	Size2dU Size2dU :: operator - (const Size2dU &subSize2d) const
	{
		UINT  dimensionX, dimensionY;
		Size2dU result;

		subSize2d.Get (dimensionX, dimensionY);
		result.Set (m_dimensionX - dimensionX, m_dimensionY - dimensionY);
		return result;
	}
	Size2dU Size2dU :: operator % (const Size2dU &subSize2d) const
	{
		UINT  dimensionX, dimensionY;
		Size2dU result;

		subSize2d.Get (dimensionX, dimensionY);
		result.Set (m_dimensionX % dimensionX, m_dimensionY % dimensionY);
		return result;
	}
	void Size2dU :: operator *= (const double d_mul)
	{
		m_dimensionX *= d_mul;
		m_dimensionY *= d_mul;
	}
	void Size2dU :: operator *= (const Size2dU &mulSize2d)
	{
		UINT dimensionX, dimensionY;

		mulSize2d.Get (dimensionX, dimensionY);
		m_dimensionX *= dimensionX;
		m_dimensionY *= dimensionY;
	}
	void Size2dU :: operator += (const Size2dU &addSize2d)
	{
		UINT dimensionX, dimensionY;

		addSize2d.Get (dimensionX, dimensionY);
		m_dimensionX += dimensionX;
		m_dimensionY += dimensionY;
	}
	void Size2dU :: operator -= (const Size2dU &subSize2d)
	{
		UINT dimensionX, dimensionY;

		subSize2d.Get (dimensionX, dimensionY);
		m_dimensionX -= dimensionX;
		m_dimensionY -= dimensionY;
	}
	bool Size2dU :: operator < (const Size2dU &lessthanSize2d) const
	{
		UINT dimensionX, dimensionY;

		lessthanSize2d.Get (dimensionX, dimensionY);
		return (m_dimensionX < dimensionX || m_dimensionY < dimensionY);
	}
	bool Size2dU :: operator > (const Size2dU &greaterthanSize2d) const
	{
		UINT dimensionX, dimensionY;

		greaterthanSize2d.Get (dimensionX, dimensionY);
		return (m_dimensionX > dimensionX || m_dimensionY > dimensionY);
	}
	bool Size2dU :: operator <= (const Size2dU &lessthanSize2d) const
	{
		return (m_dimensionX <= lessthanSize2d.GetX() || m_dimensionY <= lessthanSize2d.GetY());
	}
	bool Size2dU :: operator >= (const Size2dU &greaterthanSize2d) const
	{
		return (m_dimensionX >= greaterthanSize2d.GetX() || m_dimensionY >= greaterthanSize2d.GetY());
	}
	bool Size2dU :: Set (const Size2dU &size2d)
	{
		return Set (size2d.GetX(), size2d.GetY());
	}
	bool Size2dU :: Set (const UINT dimensionX, const UINT dimensionY) 
	{
		m_dimensionX = (dimensionX);
		m_dimensionY = (dimensionY);
		return true;
	}
	void Size2dU :: SetX (const UINT dimensionX)
	{
		m_dimensionX = (dimensionX);
	}
	void Size2dU :: SetY (const UINT dimensionY)
	{
		m_dimensionY = (dimensionY);
	}
	void Size2dU :: IncrementX ()
	{
		m_dimensionX += 1;
	}
	void Size2dU :: IncrementY ()
	{
		m_dimensionY += 1;
	}
	void Size2dU :: DecrementX ()
	{
		m_dimensionX -= 1;
	}
	void Size2dU :: DecrementY ()
	{
		m_dimensionY -= 1;
	}
	UINT Size2dU :: Product() const
	{
		return m_dimensionX * m_dimensionY;
	}
	bool Size2dU :: Product(UINT &result) const
	{
		result = m_dimensionX * m_dimensionY;
		return (result != 0);
	}
	bool	Size2dU :: Encapsulates(const Size2dU &siz) const
	{
		if (siz >= *this)
			return false;
		Size2dU zero(0,0);
		if (siz < zero)
			return false;
		return true;
	}
	Size2dU Size2dU :: Minimum (const Size2dU &size1, const Size2dU &size2)
	{
		Size2dU sizeMin;

		sizeMin.Set ( size1.GetX() < size2.GetX() ? size1.GetX() : size2.GetX(),
				  size1.GetY() < size2.GetY() ? size1.GetY() : size2.GetY() );
		return sizeMin;
	}
	Size2dU Size2dU :: Maximum (const Size2dU &size1, const Size2dU &size2)
	{
		Size2dU sizeMax;

		sizeMax.Set ( size1.GetX() > size2.GetX() ? size1.GetX() : size2.GetX(),
				  size1.GetY() > size2.GetY() ? size1.GetY() : size2.GetY() );
		return sizeMax;
	}
	Size2dU Size2dU :: IMinimum (const Size2dU &size1, const Size2dU &size2)
	{
		Size2dU sizeMin;

		sizeMin.Set ( (int)size1.GetX() < (int)size2.GetX() ? size1.GetX() : size2.GetX(),
				   (int)size1.GetY() < (int)size2.GetY() ? size1.GetY() : size2.GetY() );
		return sizeMin;
	}
	Size2dU Size2dU :: IMaximum (const Size2dU &size1, const Size2dU &size2)
	{
		Size2dU sizeMax;

		sizeMax.Set ( (int)size1.GetX() > (int)size2.GetX() ? size1.GetX() : size2.GetX(),
				   (int)size1.GetY() > (int)size2.GetY() ? size1.GetY() : size2.GetY() );
		return sizeMax;
	}


	Size2dF :: Size2dF (void) {
		Set (0,0);
	}
	Size2dF :: Size2dF (const float dimensionX, const float dimensionY)
	{
		Set (dimensionX, dimensionY);
	}
	Size2dF :: Size2dF (const Size2dF &size)
	{
		Set (size);
	}
	Size2dF :: Size2dF (const Size2d &size)
	{
		Set (size.GetX().GetValue_double(),size.GetY().GetValue_double());
	}
/**
	 * For a given (X,Y) offset within a square of size 'size', return the index from zero of the matrix
	 * @param offset - 
	 * @return 
 */
	UINT Size2dF::GetIndex (const Size2dF &offset) const
	{
		return offset.GetX() + offset.GetY() * GetX();
	}
	void Size2dF :: Get (float &u_x, float &u_y) const
	{
		u_x = m_dimensionX;  u_y = m_dimensionY;
	}
	bool Size2dF :: operator == (const Size2dF &eqeqSize2d) const
	{
		return (eqeqSize2d.GetX() == m_dimensionX && eqeqSize2d.GetY() == m_dimensionY);
	}
	Size2dF Size2dF :: operator * (const double d_mul) const
	{
		Size2dF result;

		result.Set ((m_dimensionX * d_mul), (m_dimensionY * d_mul));
		return result;
	}
	Size2dF Size2dF :: operator * (const Size2dF &mulSize2d) const
	{
		Size2dF result;
		result.Set (m_dimensionX * mulSize2d.m_dimensionX, m_dimensionY * mulSize2d.m_dimensionY);
		return result;
	}
	Size2dF Size2dF :: operator / (const double d_div) const
	{
		Size2dF result;

		result.Set ((m_dimensionX / d_div), (m_dimensionY / d_div));
		return result;
	}
	Size2dF Size2dF :: operator / (const Size2dF &divSize2d) const
	{
		Size2dF result;
		result.Set (m_dimensionX / divSize2d.m_dimensionX, m_dimensionY / divSize2d.m_dimensionY);
		return result;
	}
	Size2dF Size2dF :: operator + (const Size2dF &addSize2d) const
	{
		Size2dF result;
		result.Set (m_dimensionX + addSize2d.m_dimensionX, m_dimensionY + addSize2d.m_dimensionY);
		return result;
	}
	Size2dF Size2dF :: operator - (const Size2dF &subSize2d) const
	{
		Size2dF result;
		result.Set (m_dimensionX - subSize2d.m_dimensionX, m_dimensionY - subSize2d.m_dimensionY);
		return result;
	}
	void Size2dF :: operator *= (const double d_mul)
	{
		m_dimensionX *= d_mul;
		m_dimensionY *= d_mul;
	}
	void Size2dF :: operator *= (const Size2dF &mulSize2d)
	{
		m_dimensionX *= mulSize2d.m_dimensionX;
		m_dimensionY *= mulSize2d.m_dimensionY;
	}
	void Size2dF :: operator += (const Size2dF &addSize2d)
	{
		m_dimensionX += addSize2d.m_dimensionX;
		m_dimensionY += addSize2d.m_dimensionY;
	}
	void Size2dF :: operator -= (const Size2dF &subSize2d)
	{
		m_dimensionX -= subSize2d.m_dimensionX;
		m_dimensionY -= subSize2d.m_dimensionY;
	}
	bool Size2dF :: operator < (const Size2dF &lessthanSize2d) const
	{
		float dimensionX, dimensionY;

		lessthanSize2d.Get (dimensionX, dimensionY);
		return (m_dimensionX < dimensionX || m_dimensionY < dimensionY);
	}
	bool Size2dF :: operator > (const Size2dF &greaterthanSize2d) const
	{
		float dimensionX, dimensionY;

		greaterthanSize2d.Get (dimensionX, dimensionY);
		return (m_dimensionX > dimensionX || m_dimensionY > dimensionY);
	}
	bool Size2dF :: operator <= (const Size2dF &lessthanSize2d) const
	{
		return (m_dimensionX <= lessthanSize2d.GetX() || m_dimensionY <= lessthanSize2d.GetY());
	}
	bool Size2dF :: operator >= (const Size2dF &greaterthanSize2d) const
	{
		return (m_dimensionX >= greaterthanSize2d.GetX() || m_dimensionY >= greaterthanSize2d.GetY());
	}
	bool Size2dF :: Set (const Size2dF &size2d)
	{
		return Set (size2d.GetX(), size2d.GetY());
	}
	bool Size2dF :: Set (const float dimensionX, const float dimensionY) 
	{
		m_dimensionX = (dimensionX);
		m_dimensionY = (dimensionY);
		return true;
	}
	void Size2dF :: SetX (const float dimensionX)
	{
		m_dimensionX = (dimensionX);
	}
	void Size2dF :: SetY (const float dimensionY)
	{
		m_dimensionY = (dimensionY);
	}
	void Size2dF :: IncrementX ()
	{
		m_dimensionX += 1;
	}
	void Size2dF :: IncrementY ()
	{
		m_dimensionY += 1;
	}
	void Size2dF :: DecrementX ()
	{
		m_dimensionX -= 1;
	}
	void Size2dF :: DecrementY ()
	{
		m_dimensionY -= 1;
	}
	float Size2dF :: Product() const
	{
		return m_dimensionX * m_dimensionY;
	}
	bool Size2dF :: Product(float &result) const
	{
		result = m_dimensionX * m_dimensionY;
		return (result != 0);
	}
	bool	Size2dF :: Encapsulates(const Size2dF &siz) const
	{
		if (siz >= *this)
			return false;
		Size2d zero(0,0);
		if (siz < zero)
			return false;
		return true;
	}
	Size2dF Size2dF :: Minimum (const Size2dF &size1, const Size2dF &size2)
	{
		Size2dF sizeMin;

		sizeMin.Set ( size1.GetX() < size2.GetX() ? size1.GetX() : size2.GetX(),
				  size1.GetY() < size2.GetY() ? size1.GetY() : size2.GetY() );
		return sizeMin;
	}
	Size2dF Size2dF :: Maximum (const Size2dF &size1, const Size2dF &size2)
	{
		Size2dF sizeMax;

		sizeMax.Set ( size1.GetX() > size2.GetX() ? size1.GetX() : size2.GetX(),
				  size1.GetY() > size2.GetY() ? size1.GetY() : size2.GetY() );
		return sizeMax;
	}
	Size2dF Size2dF :: IMinimum (const Size2dF &size1, const Size2dF &size2)
	{
		Size2dF sizeMin;

		sizeMin.Set ( (int)size1.GetX() < (int)size2.GetX() ? size1.GetX() : size2.GetX(),
				   (int)size1.GetY() < (int)size2.GetY() ? size1.GetY() : size2.GetY() );
		return sizeMin;
	}
	Size2dF Size2dF :: IMaximum (const Size2dF &size1, const Size2dF &size2)
	{
		Size2dF sizeMax;

		sizeMax.Set ( (int)size1.GetX() > (int)size2.GetX() ? size1.GetX() : size2.GetX(),
				   (int)size1.GetY() > (int)size2.GetY() ? size1.GetY() : size2.GetY() );
		return sizeMax;
	}

}
		
		
		

