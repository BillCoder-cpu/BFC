//*/
/*
					CBfc_ReferencedObject.h : 
	
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

#ifndef __CBFC_REFERENCEDOBJECT_CPP__
#define __CBFC_REFERENCEDOBJECT_CPP__

// RELEASE it will decrment count
BFC_CLASS  CBfc_ReferencedObject : public CBfc_Object
{
public:
	CBfc_ReferencedObject (const CBfc_ReferencedObject *p_reference=NULL);
    virtual		~CBfc_ReferencedObject();

	virtual void	*Dup () =0;

	unsigned long		GetReferenceCount() const { 
							return *m_p_referenceCount;
							}

	void			IncrementReference ();
    bool			DecrementReference();

private:
	unsigned long	*m_p_referenceCount;
};

#endif // ndef __CBFC_REFERENCEDOBJECT_CPP__


