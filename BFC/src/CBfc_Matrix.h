//*/
/*
					CBfc_Matrix.h : 
	
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


/*
    CBFc_Matrix.h

*/

#ifndef _BCMATRIX_H
#define _BCMATRIX_H


#include "CBfc_Object.h"
#include "CBfc_ReferencedObject.h"
#include "CBfc_2dSize.h"
BFC_CLASS CBfc_String;

template<class baseClass> BFC_TEMPLATE_CLASS CBfc_2dArrayT : public CBfc_Object
{
public:
    CBfc_2dArrayT(const CBfc_2dSize &size2d, CBfc_ReferencedAllocation *p_useMyAllocation=NULL)
	{
		m_u_sizeX = (UINT)size2d.GetX().GetValue_double();
		m_u_sizeY = (UINT)size2d.GetY().GetValue_double();

		m_u_pitchBytes = sizeof(baseClass) * m_u_sizeX;
		if (p_useMyAllocation)
		{
			m_b_externalAllocation = true;
			m_p_allocation = p_useMyAllocation;
		} else
		{
			m_p_allocation = new CBfc_ReferencedAllocation();
			m_b_externalAllocation = false;
		}
	}

    CBfc_2dArrayT(const UINT u_sizeX=0, const UINT u_sizeY=0, CBfc_ReferencedAllocation *p_useMyAllocation=NULL)
		: m_u_sizeX(u_sizeX), m_u_sizeY(u_sizeY)
	{
		m_u_pitchBytes = sizeof(baseClass) * m_u_sizeX;
		if (p_useMyAllocation)
		{
			m_b_externalAllocation = true;
			m_p_allocation = p_useMyAllocation;
		} else
		{
			m_p_allocation = new CBfc_ReferencedAllocation();
			m_b_externalAllocation = false;
		}
	}
    virtual ~CBfc_2dArrayT()
	{
		if (!m_b_externalAllocation)
			delete m_p_allocation;
	}

    baseClass *GetPtr (UINT u_x, UINT u_y, UINT u_membersNeeded)
	{
		BYTE    *ptr;
		__uint64    n_offset = (u_x * sizeof (baseClass)) + u_y * m_u_pitchBytes;
		m_p_allocation->ReferenceBytes (n_offset, u_membersNeeded*sizeof(baseClass), ptr);
		return (baseClass*)ptr;
	}

	bool GetSize (CBfc_2dSize &size2d) const
	{
		size2d.Set (m_u_sizeX, m_u_sizeY);
		return true;
	}
private:
    UINT                        m_u_sizeX, m_u_sizeY;
    UINT                        m_u_pitchBytes;
    bool                        m_b_externalAllocation;
    CBfc_ReferencedAllocation   *m_p_allocation;
};


typedef	CBfc_2dArrayT<			char>			CBfc_2dArrayChar;
typedef	CBfc_2dArrayT<unsigned	char>			CBfc_2dArrayUnsignedChar;
typedef	CBfc_2dArrayT<			short>			CBfc_2dArrayShort;	
typedef	CBfc_2dArrayT<unsigned	short>			CBfc_2dArrayUnsignedShort;
typedef	CBfc_2dArrayT<			int>			CBfc_2dArrayInt;
typedef	CBfc_2dArrayT<unsigned	int>			CBfc_2dArrayUnsignedInt;
typedef	CBfc_2dArrayT<			long>			CBfc_2dArrayLong;
typedef	CBfc_2dArrayT<unsigned	long>			CBfc_2dArrayUnsignedLong;
typedef	CBfc_2dArrayT<			INT64>		CBfc_2dArrayInt64;
typedef	CBfc_2dArrayT<			UINT64>		CBfc_2dArrayUnsignedInt64;
typedef	CBfc_2dArrayT<			float>			CBfc_2dArrayFloat;
typedef	CBfc_2dArrayT<			double>			CBfc_2dArrayDouble;
typedef	CBfc_2dArrayT<		long	double>			CBfc_2dArrayLongDouble;

//
//
//
BFC_CLASS CBfc_MatrixDoubles : public CBfc_2dArrayDouble
{
public:
	CBfc_MatrixDoubles (const CBfc_2dSize &size2d)
		:	CBfc_2dArrayDouble(size2d)
		{}
	virtual ~CBfc_MatrixDoubles() 	{}

	void operator = (const CBfc_MatrixDoubles &mulMatrix);
	void operator *= (const CBfc_MatrixDoubles &mulMatrix);
	bool IsSameSize (const CBfc_MatrixDoubles &mulMatrix);
private:
};


#endif   // ndef _BCMATRIX_H



