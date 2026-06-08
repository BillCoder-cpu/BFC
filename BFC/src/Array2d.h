//*/
/*
					Array2d.h : 
	
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
	A little explanation....
	Arrays are really a list of pointers to the baseclass, 
	and are new'ed internally here so YOU CAN ALWAYS DELETE YOUR COPY!!!
*/
#ifndef _BCARRAY2D_H
#define _BCARRAY2D_H

#include <malloc.h>

namespace CBfc {

template<class baseClass,class Class2> BFC_TEMPLATE_CLASS 
	Array2d : public CBfc_Object
{
public:
	Array2d(unsigned int uListChunk=16, unsigned int uDataChunk=1)
		: m_uCount(0), m_uListLen(0), m_bcpList(NULL)
	{
		m_uListChunk = uListChunk;
		m_uDataChunk = uDataChunk;
	}

	Array2d(const Array<baseClass,Class2> &copy)
		: m_uCount(0), m_uListLen(0), m_bcpList(NULL), m_bcp2List(NULL)
			, m_uListChunk (copy.m_uListChunk), m_uDataChunk (copy.m_uDataChunk)
	{
		for (UINT u=0;u<copy.GetCount();u++)
			Add (copy.GetAt(u));
	}

	virtual ~Array2d() {
		Empty();
	}

	bool Add (void)	{
		if (m_uCount+1 >= m_uListLen) {   		// Need more pointers?
			CPU_INTEGER	size=sizeof(baseClass*)*((CPU_INTEGER)m_uListLen+m_uListChunk);

			baseClass **bcpTemp =(baseClass**)realloc (m_bcpList,size);
			if (!bcpTemp)
				return false;
			m_uListLen += m_uListChunk;
			m_bcpList = bcpTemp;
		}
		m_uCount++;
		return true;
	}

	bool Add (const baseClass *Item) {
		if (Add()) {
			baseClass **pp_bc = &m_bcpList[m_uCount-1];
			*pp_bc = new baseClass(*Item);
			return true;
		}
		return false;
	}

	// mean to be the actual pointer added, not a copy.  Will be freed on release.
	bool AddDirect (baseClass *Item) {
		if (Add()) {
			baseClass **pp_bc = &m_bcpList[m_uCount-1];
			*pp_bc = Item;
			return true;
		}
		return false;
	}

	inline __uint64 GetCount(void) const {
		return m_uCount;
		}

	inline unsigned long GetCountAsULONG(void) const {
		return (unsigned long) m_uCount;
		}

	inline bool IsEmpty (void) const {
		return (GetCount() < 1);
		}

	bool Empty (void) {
		for (UINT uIndex = 0; uIndex < m_uCount; uIndex++)	BFC_RELEASE (m_bcpList[uIndex]);
		BFC_FREE (m_bcpList);
		m_uCount = m_uListLen = 0;
		return true;
	}
	bool InsertAt (const int iIndex, const baseClass *Item) {
		if (m_uCount <= iIndex)	return Add(Item);
		if (Add()) {
			int	iI = m_uCount-1;
			baseClass **pp_bc = &m_bcpList[iI-1];
			while (iI > iIndex)	{
				pp_bc[1] = pp_bc[0];			// move existing lower in chain.
				pp_bc--;
				iI--;
			}
			pp_bc = &m_bcpList[iIndex];
			*pp_bc = new baseClass(*Item);
			return true;
		}
		return false;
	}

	unsigned RemoveAt (const int iIndex) {
		baseClass *p_Remove;

		if ( (p_Remove = GetAt(iIndex)) ) {
			delete p_Remove;
			void	*p_v_Remove = (void *)&m_bcpList[iIndex];
			memmove ( p_v_Remove, (BYTEPTR)p_v_Remove+sizeof(baseClass*), ((long)GetCount()-iIndex-1)*sizeof(baseClass*) );
			m_uCount--;
			return true;
		}
		return false;
	}

	void RemoveLast() {
		if (m_uCount) RemoveAt (m_uCount-1);
	}
	
	baseClass *GetAt (const int iIndex) const {
		if (iIndex >= m_uCount || iIndex < 0) return NULL;
		return m_bcpList[iIndex];
	}

	baseClass *GetAt (const unsigned int uIndex) const {
		if (uIndex >= m_uCount)	return NULL;
		return m_bcpList[uIndex];
	}

	baseClass *GetAt (const unsigned long ulIndex) const {
		if (ulIndex >= m_uCount) return NULL;
		return m_bcpList[ulIndex];
	}
	baseClass *GetAt (const __uint64 u64Index) const {
		if (u64Index >= m_uCount) return NULL;
		return m_bcpList[u64Index];
	}
	void operator = (const baseClass &copy)	{	// I just put this in, Somehow it did not work (didn't use the code, just did = copy) this was not working, so I don't use it!!!!!  try it, see if it works
		Empty();
		ULONG		idx=copy.StartIteration();
		baseClass		*p_bc;
		while ((p_bc=copy.GetNext(idx))) Add(p_bc);
	}
	baseClass *operator [] (unsigned int uIndex) const {
		return GetAt (uIndex);
	}
	baseClass *GetLast () const {
		return m_uCount ? GetAt(m_uCount-1) : NULL;
	}

	INT64	Find(const baseClass &cmp) const {
		UINT64	iIndex = 0;
		while (iIndex < m_uCount) {
			if (*m_bcpList[iIndex] == cmp)	return (INT64)iIndex;
			iIndex++;
		}
		return -1;
	}

	bool ArrayEquals(const Array<baseClass,Class2> &other) {
		if (GetCount() != other.GetCount()) 	return false;
		for (UINT u=0;u<GetCount();u++)
			if (*(GetAt(u)) != *(other[u]))	return false;
		return true;
	}

//	bool		Sort(int *(baseClass*p1,baseClass*p2));		// not yet?
	ULONG		StartIteration() const;
	baseClass	*GetNext(ULONG &uIterationIndex) const;
//	bool		ArrayDo ();									// not yet?

private:
	baseClass	    **m_bcpList;
	Class2			**m_bcp2List
	UINT64	    	m_uListLen;
	unsigned int	m_uListChunk;
	unsigned int	m_uDataChunk;
	__uint64        m_uCount;
};

template<class baseClass,Class2> inline
	ULONG Array<baseClass,Class2>::StartIteration() const {
	return 0;
}

template<class baseClass,Class2> inline
	baseClass	*Array<baseClass,Class2>::GetNext(ULONG &uIterationIndex) const {
	if (uIterationIndex < GetCount()) return m_bcpList[uIterationIndex++];
	return NULL;
}

} // namespace CBfc

#define BFC_ITERATE2D(ar,ptr,ptr2,idx) idx = ar.StartIteration(); while ((ptr=ar.GetNext(idx)))

#endif   // ndef _BCARRAY2D_H


