//*/
/*
					CBfc_LinkedList.h : 
	
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
// CBfc_LinkedList.h
//
BFC_CLASS CBfc_LinkedObject
{
public:
	CBfc_LinkedObject();
	virtual			~CBfc_LinkedObject();

	CBfc_LinkedObject *GetNext () const;
	CBfc_LinkedObject *GetPrevious () const;
	CBfc_LinkedObject *GetChild () const;
private:
	CBfc_LinkedObject *m_pNext;
	CBfc_LinkedObject *m_pPrev;
	CBfc_LinkedObject *m_pChild;
};

// Linked list of Vocal replacements

//
//
BFC_CLASS	CBfc_LinkedList
{
public:
	CBfc_LinkedList();
	virtual			~CBfc_LinkedList();

	bool InsertSibling (CBfc_LinkedObject *pInsertObject, CBfc_LinkedObject *pAfter);
	bool InsertChild (CBfc_LinkedObject *pInsertObject, CBfc_LinkedObject *pParent, CBfc_LinkedObject *pAfterChild);
	CBfc_LinkedObject *GetHead () const {
							return m_pHead;	}

	bool Serialize (const bool bWrite, CBfc_Stream *pStream);
private:
	CBfc_LinkedObject			*m_pHead;
	unsigned long				m_uObjectCount;
	CBfc::ArrayPtr				m_ObjectIndexArray;
};











