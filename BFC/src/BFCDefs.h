//*/
/*
					BFCDefs.h : 
	
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
#ifndef __BFCDEFS_H_
#define __BFCDEFS_H_

#define	CPU_32BIT
#undef	CPU_64BIT

#define BFC_CLASS 			class BFC_API
#define BFC_TEMPLATE_CLASS	class BFC_TEMPLATE_API

#ifdef UNIX
#	include "bfc_unix.h"
#else
#	include "bfc_windows.h"
#endif
#undef _MBCS
#include "BFCTypes.h"


#define	DELTA(A,B)	(A>B?A-B:B-A)

//#define	ZERO		(0)
#ifndef NULL
#	define NULL	(0)
#endif
//#define	NULLPTR	(unsigned char *)NULL
#define	NULLPTR	((void *)NULL)

typedef enum tagBCE_RETURNVALUE
{
        EBFC_EXC_Success,
        EBFC_EXC_Success_,
        EBFC_EXC_Failure_Okay,
        EBFC_EXC_Failure_Uknown,
        EBFC_EXC_Failure_Horiffic,
} EBFC_RETURNVALUE;

#	define	BFC_RELEASE_ARRAY(a) { if(a) { delete[] a; a = NULL; } }
#	define	BFC_RELEASE_PTR(p) { if(p) { delete p; p = NULL; } }
#	define	BFC_RELEASE(x)	   { if(x) { delete x; x = NULL; } }
#	define	BFC_FREE(x)			{ if(x) { free(x); x = NULL; } }
#	define	BFC_GLOBAL	extern
//    typedef unsigned short WCHAR;    // wc,   16-bit UNICODE character
//    typedef const WCHAR *LPCWSTR;
//    typedef const char *LPCSTR;
//    typedef WCHAR *LPWSTR;
//    typedef char *LPSTR;

//Distance Conversions
#define	CENTIMETERS_PER_METER	100
#define	INCHES_PER_METER		39.3700787402
#define	INCHES_PER_FOOT			12
#define	INCHES_PER_YARD			36
#define	FEET_PER_MILE			5280
#define	FEET_PER_YARD			3

#include "BFCDefs_KeyDefs.h"

//	OVERRIDE is used to signify that this is a virtual function
#define	OVERRIDE
// extern class CBfc_Exception;

#define BFC_RVAL_SUCCESS			true
#define BFC_RVAL_FAILURE			false
#define BFC_RVAL_ERROR				2
//#define BFC_RVAL_
//#define BFC_RVAL_
//#define BFC_RVAL_
//#define BFC_RVAL_

/////////////////////////////////////////////////
// Debugging

#ifndef TRACE
#	define TRACE	BFC_TRACE
#endif

#define	ASSERT	BFC_ASSERT
#ifdef _DEBUG
#	define BFC_TRACE	BfcDebugStatic_Trace
#   define BFC_ASSERT(x,msg) { if (!x) TRACE (_TXT("! BFC CODE ASSERTION: %ls\n"), _TXT(msg));	}
#else
#	define BFC_TRACE	BfcRelease_Trace
#   define BFC_ASSERT(x,msg)
#endif

// Not working yet - wel have our drawers down, so to speak.
//#define	HANDLE_BFC_EXCEPTION()	{ BFC_TRACE("ERROR: Unexpected Exception!"); }

#define	HANDLE_BFC_EXCEPTION()	{  }


///////////////////////////////////////
///

#include "CBfc_Object.h"
#include "CBfc_ReferencedObject.h"

#endif // ndef __BFCDEFS_H_

