//*/
/*
					CBfc_LinkedList.cpp : 
	
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


CBfc_LinkedList::CBfc_LinkedList()
	: m_uObjectCount(0)
{
}

CBfc_LinkedList::~CBfc_LinkedList()
{
}


CBfc_LinkedObject::CBfc_LinkedObject()
{
}

CBfc_LinkedObject::~CBfc_LinkedObject()
{
}



bool CBfc_LinkedList::InsertSibling (CBfc_LinkedObject *pInsertObject, CBfc_LinkedObject *pAfter)
{
	return true;
}

bool CBfc_LinkedList::InsertChild (CBfc_LinkedObject *pInsertObject, CBfc_LinkedObject *pParent, CBfc_LinkedObject *pAfterChild)
{
	return true;
}

bool CBfc_LinkedList::Serialize (const bool bWrite, CBfc_Stream *pStream)
{
	return true;
}

