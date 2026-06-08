//*/
/*
					Bfc_DebugStatic.h : 
	
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


#if _MSC_VER > 1000
#	pragma once
#endif

#if 0 //def UNIX
#	ifdef _DEBUG
		extern void BfcDebugStatic_Trace (const CHARACTER_PTR lpszFormat, ...);
#else
		extern void BfcRelease_Trace (const CHARACTER_PTR lpszFormat, ...);
#endif
#else	// ifdef UNIX		// Intended for Internal use only
	extern "C" 
	{
#	ifdef _DEBUG
		extern void __cdecl BfcDebugStatic_Trace (const CHARACTER_PTR lpszFormat, ...);
#	else
		extern void __cdecl BfcRelease_Trace (const CHARACTER_PTR lpszFormat, ...);
#	endif
	};
#endif


