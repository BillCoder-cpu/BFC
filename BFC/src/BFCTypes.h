//*/
/*
					BFCTypes.h : 
	
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
// CPU_INTEGER is the maximum integer size for the runnning processor
#ifdef CPU_32BIT
    typedef unsigned long    CPU_INTEGER;
#endif
#ifdef CPU_64BIT
    typedef unsigned long long    CPU_INTEGER;
#endif

	typedef unsigned long	BFC_RVAL;

	typedef int				HFILE;
    typedef void*			HANDLE;
    
    typedef unsigned long   DWORD;
    typedef unsigned long   ULONG;
    typedef int             BOOL;
    typedef unsigned char   BYTE;
    typedef unsigned char   uchar;
    typedef unsigned short  WORD;
    typedef unsigned int    UINT;

    typedef BYTE * 	BYTEPTR;
    typedef BYTE * 	BYTE_PTR;

	typedef	WORD *	WORDPTR;
	typedef	WORD *	WORD_PTR;

    typedef void * 	VOIDPTR;

	typedef int (*functionPtr)();
	typedef int (*FUNCTION_PTR)();


/////////////////////////////////////////////////
//		Basic Character Defs'

typedef char			characterA;		// BYTEPTR
typedef unsigned short	characterW;		// WORDPTR
#if 1 //def UNIX
	typedef wchar_t	characterU;			// LONGPTR
#pragma GCC diagnostic ignored "-Wwrite-strings"
#else
	typedef unsigned short	characterU;	// WORDPTR
#endif
typedef char			characterM;		// WORDPTR

//
//
typedef characterA * characterPtrA;			// old style ASCII
typedef characterU * characterPtrU;			// UNICODE - Chinese
typedef characterU * characterPtrW;			// Word
//typedef characterM * characterPtrM;			// MBCS - Japanese.

#ifdef _UNICODE_16
	typedef characterU		character;
#	define	characterPtr	characterPtrU
#	define _TXT(x)			(L ## x)
	typedef const characterU * const_characterPtr;
#endif
#ifdef _UNICODE_8
#	ifdef	BFC_USE_MBCS
		#define	_UNICODE_8_MBCS
		typedef characterM		character;
		#	define	characterPtr	characterPtrM
#	else
		typedef characterA		character;
		typedef characterPtrA	characterPtr;
		typedef const characterA * const_characterPtr;
//		#	define	characterPtr	characterPtrA
#	endif
#	define	_TXT(x)			(x)
#endif

#define CharacterPtr	characterPtr

typedef character *	CHARACTER_PTR;
