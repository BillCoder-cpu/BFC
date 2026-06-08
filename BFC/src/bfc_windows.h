//*/
/*
					bfc_windows.h : 
	
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
#	define WINDOWS
#	define MICROSOFT_WINDOWS

#	include "BfcUnDefs.h"
#	include <memory.h>
#	include <string.h>

#	ifndef _WIN32
#		define _WIN32
#	endif

#	ifdef STATICLIB
#		define	BFC_STATICLIB
#	endif
#	ifdef BFC_STATICLIB
#		define BFC_API
#		define BFC_TEMPLATE_API
#	else
#		ifdef BFC_DLL
#			define BFC_API __declspec(dllexport)
#			define BFC_TEMPLATE_API BFC_API
#		else
#			define BFC_API __declspec(dllimport)
#			define BFC_TEMPLATE_API __declspec(dllexport)
//#			define BFC_TEMPLATE_API BFC_API
#		endif
#   endif
	typedef 				__int64  INT64;
	typedef unsigned		__int64	__uint64;
	typedef unsigned		__int64	UINT64;

//#	define min(a,b) a<b?a:b
//#	define max(a,b) a>b?a:b

#ifndef MINGW
#	if defined (_UNICODE) && !defined (UNICODE)
#		define UNICODE
#	endif
#	if defined (UNICODE) && !defined (_UNICODE)
#		define _UNICODE
#	endif
#	ifndef _UNICODE
#		define	_UNICODE		// Utilize 16 bit character codes.
#	endif
#	define	_UNICODE_16
#else
#	undef	UNICODE
#	undef	_UNICODE
#	undef	_UNICODE_16
#	define	_UNICODE_8
#endif // ndef MINGW

#   if 0
#       undef BFC_CLASS
#       define BFC_CLASS public __gc class
#   endif
