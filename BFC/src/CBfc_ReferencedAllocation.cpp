//*/
/*
					CBfc_ReferencedAllocation.cpp : 
	
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
#include "BFC/BFC.h"
#include <malloc.h>

///////////////////**********************************************///////////////
///////////////////**********************************************///////////////
///////////////////***********												********///////////////
///////////////////***********	CBfc_ReferencedAllocation		********///////////////
///////////////////***********												********///////////////
///////////////////**********************************************///////////////
///////////////////**********************************************///////////////
CBfc_ReferencedAllocation :: CBfc_ReferencedAllocation (const CBfc_ReferencedAllocation *p_reference)
    : CBfc_ReferencedPointer (p_reference)
	, m_nAllocLength (0)
	, m_uPadding(256)
{
	if (p_reference)
	{
		m_bReadOnly = p_reference->m_bReadOnly;
		m_bMemoryAssignedExternally = p_reference->m_bMemoryAssignedExternally;
		m_nAllocLength = p_reference->m_nAllocLength;
		m_uPadding = p_reference->m_uPadding;
	} else
	{
		m_bReadOnly = false;
		m_bMemoryAssignedExternally = false;
	}
}

CBfc_ReferencedAllocation :: ~CBfc_ReferencedAllocation ()
{
	Free();
}

void *CBfc_ReferencedAllocation::Dup()
{
	return (void*)new CBfc_ReferencedAllocation(this);
}

bool CBfc_ReferencedAllocation :: SetToAllocation (CBfc_ReferencedAllocation &duper)
{
	*this = *(CBfc_ReferencedAllocation*)duper.Dup();
	return true;
}

// Duplicate the data in our buffer
bool CBfc_ReferencedAllocation :: SetToData (const void *p_data, const unsigned long ul_memoryByteLength)
{
	if (SetBytesAllocated (ul_memoryByteLength))
	{
		memcpy (m_ptr, p_data, ul_memoryByteLength);
		return true;
	}
	return false;
}


bool CBfc_ReferencedAllocation :: EnsureBytesAllocated (const unsigned int u_byteLength)
{
	if (m_nAllocLength < u_byteLength)
	{
		if (u_byteLength > MAX_REFERENCED_ALLOCATION)
		{
			ASSERT(0,"CBfc_ReferencedAllocation :: EnsureBytesAllocated");
			return false;
		}
		return SetBytesAllocated (u_byteLength + 4);
	}
    return true;
}

bool CBfc_ReferencedAllocation :: SetBytesAllocated (const unsigned int u_byteLength)
{
	ASSERT (!m_bMemoryAssignedExternally,"CBfc_ReferencedAllocation :: SetBytesAllocated");

    if (m_bReadOnly) return false;
    
    const UINT allocsize = u_byteLength + m_uPadding;
    if (m_ptr)
    {
	    BYTEPTR ptr = (BYTEPTR)realloc (m_ptr, allocsize);
	    if (!ptr)
		    return false;
	    m_ptr = ptr;
    } else
    {
	    m_ptr = (BYTEPTR)malloc (allocsize);
//	    m_ptr = (BYTEPTR)calloc (1, allocsize);
	    if (!m_ptr)
		    return false;
    }
    m_nAllocLength = u_byteLength;
    return true;
}

bool CBfc_ReferencedAllocation :: SetToMemory (const void *p_memory,const  unsigned long ul_memoryByteLength)
{
	Free ();
    m_bMemoryAssignedExternally = true;
	m_bReadOnly = true;
    m_ptr =(BYTEPTR) p_memory;
    m_nAllocLength = ul_memoryByteLength;
	return true;
}

void CBfc_ReferencedAllocation :: ReleaseMemoryAssignment (void)
{
	if (m_bMemoryAssignedExternally)
	{
//		m_bReadOnly = false;
		m_nAllocLength = 0;
 		m_ptr = NULL;
		m_bMemoryAssignedExternally = false;
	}
}

bool CBfc_ReferencedAllocation::ReferenceAll (BYTEPTR &ptr) const
{
    return ReferenceBytes (0, GetBytesAllocated(), ptr);
}

bool CBfc_ReferencedAllocation :: ReferenceBytes (const UINT64 n_offset, const UINT uCount, WORDPTR &ptr) const
{
	BYTE_PTR	bp;
	const bool	bRval = ReferenceBytes(n_offset, uCount, bp);
	ptr = (WORD_PTR)bp;
	return bRval;
}

bool CBfc_ReferencedAllocation :: ReferenceBytes (const UINT64 n_offset, const UINT uCount, char * &ptr) const
{
	BYTE_PTR	bp;
	const bool	bRval = ReferenceBytes(n_offset, uCount, bp);
	ptr = (char *)bp;
	return bRval;
}

#if  1 //def UNIX
bool CBfc_ReferencedAllocation :: ReferenceBytes (const UINT64 n_offset, const UINT uCount, wchar_t * &ptr) const
{
	BYTE_PTR	bp;
	const bool	bRval = ReferenceBytes(n_offset, uCount, bp);
	ptr = (wchar_t *)bp;
	return bRval;
}
#endif	// UNIX

// Modifies uCount to keep it within range.
bool CBfc_ReferencedAllocation :: ReferenceBytes (const UINT64 n_offset,
												  const unsigned int uCount, BYTEPTR &ptr) const
{
	ptr = m_ptr;
    if (n_offset > m_nAllocLength)
		return false;
    ptr +=  (n_offset);

	const __uint64 maxLen = m_nAllocLength - n_offset;
	return (uCount <= maxLen);
}

bool CBfc_ReferencedAllocation :: DeReferenceBytes (void *p) const
{
    return true;
}

bool CBfc_ReferencedAllocation :: Delete ()
{
	if (m_bMemoryAssignedExternally)
	{
		ReleaseMemoryAssignment ();	// If assigned externally, nullify things
		DecrementReference();
		return true;
	} else
	{
		const bool b_rVal = CBfc_ReferencedPointer :: Delete ();
		if (b_rVal)
			m_nAllocLength = 0;
		return b_rVal;
	}
}

bool CBfc_ReferencedAllocation :: Free ()
{
	return this->Delete();
}



