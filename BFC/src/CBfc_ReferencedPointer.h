//*/
/*
					CBfc_ReferencedPointer.h : 
	
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


BFC_CLASS CBfc_ReferencedPointer : public CBfc_ReferencedObject
{
public:
	CBfc_ReferencedPointer (const CBfc_ReferencedPointer* p_reference=NULL);
	virtual ~CBfc_ReferencedPointer();

	inline virtual void operator = (void *ptr) {
		m_ptr = (BYTEPTR)ptr;
	}
	operator void *() const {
		return (void *)m_ptr;
	}
	operator char *() const {
		return (char*)m_ptr;
	}
	BYTEPTR		GetPtr () const {
		 return m_ptr;
	}

 	virtual bool	Delete (void);
protected:
	BYTEPTR		m_ptr;
private:
};




