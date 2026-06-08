//*/
/*
					CBfc_String8.cpp : 
	
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

#include <BFC/BFC.h>

namespace CBfc {

STRING8::STRING8 ()
{
}

STRING8::STRING8 (const STRING *p_srcString)
	: STRING(p_srcString)
{
}

#ifndef _UNICODE_8
STRING8::STRING8 (const char* ptr)
	: STRING(ptr)
{
}
#endif

STRING8::STRING8 (const characterPtr ptr)
	: STRING(ptr)
{
}

STRING8::STRING8 (const STRING &srcString)
	: STRING(srcString)
{
}

char *STRING8::GetPtr8 ()
{
#ifndef _UNICODE_8
	const UINT uLen=GetLengthChars()+4;
	m_Representation8.EnsureBytesAllocated(uLen);
	SBFC_Character::UTF16toUF8 (GetPtr(), (char*)m_Representation8.GetPtr ());
	return (char *)(m_Representation8.GetPtr ());
#else
	return GetPtr();
#endif
}

}


