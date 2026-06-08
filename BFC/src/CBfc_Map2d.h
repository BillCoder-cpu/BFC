//*/
/*
					CBfc_Map2d.h : 
	
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

#ifndef _BFC_MAP2D_H_
#define  _BFC_MAP2D_H_

namespace CBfc
{

#define	dataClass	CBCString
#define indexClass	CBCString
//template<class indexClass,class dataClass> BFC_TEMPLATE_CLASS 
BFC_CLASS StringMap2d : public CBfc_Object
{
public:
	inline bool Add (const indexClass& key, const dataClass& data)
	{
		return (m_indexArray.Add(&key) && m_dataArray.Add(&data));
	}

	inline dataClass &operator [] (const indexClass& icKey)
	{
		INT64		i = m_indexArray.Find(icKey);
		if (i >= 0)
		{
			dataClass	*p_dc = m_dataArray.GetAt((UINT64)i);
			if (p_dc)
				return *p_dc;
		}

		static dataClass dc;
		return dc;
	}

protected:
public:
	Array<CBCString>	m_indexArray;
	Array<CBCString>	m_dataArray;
};

//template<class indexClass, class dataClass> inline
//	dataClass& CBfc_StringMap2d::operator [] (const indexClass& icKey)


//template<class indexClass, class dataClass> inline
//	bool CBfc_StringMap2d::Add (const indexClass& key, const dataClass& data)

} // namespace

#endif

