//*/
/*
					CBfc_ReferencedAllocation.h : 
	
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

#define	MAX_REFERENCED_ALLOCATION		640000000

BFC_CLASS CBfc_ReferencedAllocation : public CBfc_ReferencedPointer
{
public:
	CBfc_ReferencedAllocation (const CBfc_ReferencedAllocation *p_reference=NULL);
	~CBfc_ReferencedAllocation ();

	virtual void *		Dup();
	virtual bool		Free (void);
	virtual bool		Delete (void);

	inline unsigned long GetBytesAllocated () const {
		return m_nAllocLength; }

	bool		SetToAllocation (CBfc_ReferencedAllocation &duper);
	bool		SetToMemory (const void *p_memory, const unsigned long ul_memoryByteLength);
	bool		SetToData (const void *p_data, const unsigned long ul_memoryByteLength);
	void		ReleaseMemoryAssignment (void);

	bool		SetBytesAllocated (const unsigned int u_byteLength);
	bool		EnsureBytesAllocated (const unsigned int u_byteLength);


	bool		ReferenceAll (BYTEPTR &ptr) const;
	bool		ReferenceBytes (const UINT64 n_offset, const unsigned int uCount, char * &ptr) const;
	bool		ReferenceBytes (const UINT64 n_offset, const unsigned int uCount, BYTE_PTR &ptr) const;
	bool		ReferenceBytes (const UINT64 n_offset, const unsigned int uCount, WORD_PTR &ptr) const;
#if 1 //def UNIX
	bool		ReferenceBytes (const UINT64 n_offset, const unsigned int uCount, wchar_t * &ptr) const;
#endif
	bool		DeReferenceBytes (void *p) const;

	inline BYTEPTR 	GetEndPtr() const {
		return GetPtr() + GetBytesAllocated (); }


protected:
	UINT				m_uPadding;

	bool				m_bMemoryAssignedExternally;
	bool				m_bReadOnly;
private:
	unsigned long		m_nAllocLength;       // length of allocation
};


