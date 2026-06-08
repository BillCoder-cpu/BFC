//*/
/*
					bfc_unix.h : 
	
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
#if defined(__GNUC__)
	#include <unistd.h>
#endif

#undef WINDOWS
#undef _WIN32
#undef WIN32

/*
#define	_UNICODE_8
#define UNICODE
#define _UNICODE
*/

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


#define NOGDI

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define BFC_API
#define BFC_TEMPLATE_API BFC_API
#ifdef CPU_32BIT
	#if defined(__GNUC__)
		typedef 		 long long INT64;
		typedef unsigned long long __uint64;
		typedef unsigned long long UINT64;
	#else
		typedef 		 __int64 INT64;
		typedef unsigned __int64 __uint64;
		typedef unsigned __int64 UINT64;
	#endif
#endif

/*
#ifndef min
#	define min(a,b) a<b?a:b
#	define max(a,b) a>b?a:b
#endif
*/

#if defined(__GNUC__)
#	define	__cdecl
#endif

//#if defined(__GNUC__) || defined(__DJGPP__)
//#	define	_UNICODE_8
//#endif

/*
// tchar defs are seldom used
#define _vstprintf	vsprintf
#define	_tclen		strlen
#define	_tcsncmp	strncmp
#define	_tcsinc(x)	x++		
#define	_ttoi		atoi
#define	_istdigit	isdigit
#define	_T(x)		x
*/

