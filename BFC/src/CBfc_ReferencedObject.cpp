//*/
/*
					CBfc_ReferencedObject.cpp : 
	
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

///////////////////***********************************************///////////////
///////////////////***********************************************///////////////
///////////////////***********                         					***********///////////////
///////////////////***********  CBfc_ReferencedObject		***********///////////////
///////////////////***********                         					***********///////////////
///////////////////***********************************************///////////////
///////////////////***********************************************///////////////

CBfc_ReferencedObject::CBfc_ReferencedObject (const CBfc_ReferencedObject *p_reference)
{
	if (p_reference)
	{
		m_p_referenceCount = p_reference->m_p_referenceCount;
		IncrementReference();
	} else
	{
		m_p_referenceCount = new unsigned long;
		*m_p_referenceCount = 1;
	}
}

CBfc_ReferencedObject::~CBfc_ReferencedObject ()
{
	// Don't delete self if 
	if (*m_p_referenceCount == 0 || DecrementReference())
		delete m_p_referenceCount;
//    throw Exception(Exception::EBFC_EXC_UNEVEN_REFERENCECOUNT);
}

void CBfc_ReferencedObject :: IncrementReference ()
{
	if (m_p_referenceCount)
		*m_p_referenceCount += 1;
	else
		throw 0;
//	if (this == (CBfc_ReferencedObject*)0x811c26c)
//		BFC_TRACE (_TXT("Incrementing %lx to %d\n"), this, *m_p_referenceCount);
}

bool CBfc_ReferencedObject::DecrementReference ()
{
	if (m_p_referenceCount)
	{
//if (this == (CBfc_ReferencedObject*)0x811c26c)
//	BFC_TRACE (_TXT("  -- Decrementing %lx from %d\n"), this, *m_p_referenceCount);
		if (*m_p_referenceCount == 0)
			throw;											// Bad condition - reference decremented too many times.

		if (*m_p_referenceCount)
			*m_p_referenceCount -= 1;

  		return (*m_p_referenceCount == 0);
	}
	throw 0;
	return true;
}



