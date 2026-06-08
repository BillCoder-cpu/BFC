//*/
/*
					character.cpp : 
	
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

#include "BFCDefs.h"
#include "character.h"

#include <stdlib.h>

#include <locale>
#include <iostream>

///////////////////////////  static CBfc_Character functions ///////////////

UINT SBFC_Character::UTF16toUF8_CountBytes(const character* charp_source)
{
	UINT	uBytes = 1;
	while (1)
	{
		const character c = *charp_source;
		if (!c)
		{
			return uBytes;
		}
		if (characterPtrM::isDoubleByteCharacter(c))
		{
			uBytes++;
		}
		uBytes++;
		charp_source++;
	}
	return 0;
}


// Return number of bytes filled (includeing trailing zero)
UINT SBFC_Character::UTF16toUF8 (const character *charp_source, char *cp_dest)
{
#if 1
	UINT	uBytes = 1;
	while (1)
	{
		const character c = *charp_source;
		if (!c)
		{
			*cp_dest = 0;
			return uBytes;
		}
		if (characterPtrM::isDoubleByteCharacter(c))
		{
			char	*tcp = (char*)charp_source;
			*cp_dest++ = *tcp++;
			*cp_dest++ = *tcp;
			charp_source++;
			uBytes += 2;
		} else
		{
			*cp_dest++ = (char)c;
			charp_source++;
			uBytes++;
		}
	}
	return 0;
#else
	unsigned long ul;
	// first, convert to 32 bit unicode unsigned long characters
	FXUTF16Codec	codec16;
	FXwchar			widepad[512], *wcp = widepad;
	const FXuchar	*ucp = (FXuchar*)charp_source;
  
	ul = codec16.toUnicode(wcp,512,ucp,512);


	// Now convert down to 8 bit unsigned char
	FXUTF8Codec codec8;
	FXuchar *ucd = (FXuchar*)cp_dest;
	wcp = widepad;
	ul = codec8.fromUnicode(ucd,256,wcp,512);
#endif
}

UINT SBFC_Character::UTF8toUF16 (const char *cp_source, character *charp_dest)
{
	UINT	uBytes = sizeof(character);
	while (*cp_source)
	{
		*charp_dest++ = *cp_source++;
		uBytes += sizeof(character);
	}
	*charp_dest++ = 0;
	return uBytes;
}

void SBFC_Character::Block_UTF8toCharacter (char *cp_Source, character *charp_dest,UINT u_CharsInBlock)
{
	char *s = cp_Source + u_CharsInBlock - 1;
	character *d = charp_dest + u_CharsInBlock - 1;
	while (u_CharsInBlock--)
		*d-- = *s--;
}

///////////////////////////// characterPtrM class //////////////////////////////

characterPtrM :: characterPtrM()
{
}

characterPtrM :: characterPtrM(const characterPtrA p_pointer)
	: m_p_pointer (p_pointer)
{
}

#ifndef _UNICODE_8
characterPtrM :: characterPtrM(const BYTEPTR p_pointer)
	: m_p_pointer ((char*)p_pointer)
{
}
#endif

characterPtrM :: characterPtrM(const void *p_pointer)
	: m_p_pointer ((char*)p_pointer)
{
}

#ifndef _UNICODE_8
characterPtrM :: characterPtrM(const character* p_pointer)
	: m_p_pointer ((characterPtrA)p_pointer)
{
}
#endif

//
//
UINT characterPtrM::GetNextCharacterLength () const
{
// For now, only 2 bytes maximum
	if (isDoubleByteCharacter(*m_p_pointer) )
		return 2;
	else
		return 1;
}

characterM *characterPtrM :: operator [](const unsigned int u_index)
{
	unsigned int	u = u_index;
	characterPtrA	ptr = m_p_pointer;
// For now, only 2 bytes maximum

	while (*ptr && u--)
	{
		ptr++;
		if ( isDoubleByteCharacter( * ptr ) )
			ptr++;
	}
	return (characterM*)ptr;
//	return *cp;
}

characterU characterPtrM :: operator *()
{
	if ( *m_p_pointer )
	{
		if (isDoubleByteCharacter(*m_p_pointer) )
			return *((characterU*)m_p_pointer);
	}
	return 	(characterU)*((unsigned char *)m_p_pointer);

//	return 	(characterM)(unsigned char)*m_p_pointer;
}

void characterPtrM :: operator += (UINT inc)
{
	while (inc)
	{
		++( *this );    // Uses the prefix operator
		inc--;
	}
}

// Prefix ++
characterPtrM &characterPtrM :: operator ++()
{
	if (isDoubleByteCharacter(*m_p_pointer))
		m_p_pointer ++;
	 m_p_pointer++;
	return *this;
}

// Postfix ++
const characterPtrM characterPtrM :: operator ++(int )
{
	characterPtrM   tcp = *this;
	++( *this );    // Uses the prefix operator
	return ( tcp );
}


void characterPtrM :: operator = (characterPtrM &ptr)
{
	m_p_pointer = ptr.GetPointer();
}

void characterPtrM :: operator = (characterM *ptr)
{
	m_p_pointer = (characterPtrA)ptr;
}

void characterPtrM :: operator = (BYTEPTR ptr)
{
	m_p_pointer = (characterPtrA)ptr;
}


//inline characterPtrM characterPtrM :: operator --()
//{
//}


void characterPtrM :: operator delete (void *ptr)
{
	characterPtrM *p_character = (characterPtrM *)ptr;
	if (p_character && p_character->GetPointer())
	{
		delete p_character->GetPointer();
		p_character->GetPointer()=NULL;
	}
}


bool characterPtrM :: isDoubleByteCharacter (characterA c)
{
	return (c & 0x80) != 0;
}

bool characterPtrM :: isDoubleByteCharacter (characterU w)
{
	return (w & 0x80) != 0;
}


int characterPtrM :: store (characterM w)
{
	if (w==0 || characterPtrM::isDoubleByteCharacter(w))
	{
		*((characterM*)m_p_pointer) = w;
		return 2;
	}
	*m_p_pointer = (char)w;
	return 1;
}

int characterPtrM :: stav (characterM w)
{
	if (w==0 || characterPtrM::isDoubleByteCharacter(w))
	{
		*((characterM*)m_p_pointer) = w;
		m_p_pointer += 2;
		return 2;
	}
	*m_p_pointer++ = (char)w;
	return 1;
}

// Moves poiner forward past next int and returns the integer's value.
long characterPtrM :: ReadInteger()
{
//	long l_rval = SBFC_Character::StringToInteger((character *)this);
	long l_rval =  atoi(m_p_pointer);
	for (; *(char*)this != '\0' && SBFC_Character::IsDigit(**this); (*this)++)
		;
	return l_rval;

}

/**
 *  Assumes a NULL terminated string
 * @param lpsz 
 * @param c 
 * @return 
 */
bool 	 characterPtrM :: InsertIntoString(characterPtrM &lpsz, characterU c)
{
	const int 	n = SBFC_Character :: BytesPerCharacter(c);
	char *p = (char*)lpsz;
	const int	sLen = strlen(p);
	
	if (sLen)
		copy_memory (BYTEPTR(p+n), BYTEPTR(p), sLen);
		
	lpsz.store(c);
	p += sLen+n;
	p[0]  = 0;
	p[1]  = 0;
	p[2]  = 0;
	p[3]  = 0;
	return true;
}

void copy_memory(BYTEPTR dst, BYTEPTR src, int len)
{
	if (len > 0)
	{
		if (dst<src)
		{
			while (len--)
				*dst++ = *src++;
		} else if (dst>src)
		{
			dst += len-1;
			src += len-1;
			while (len--)
				*dst-- = *src--;
		}
	}
}

/////////
//// Static character functions
/////////

int	SBFC_Character :: 	BytesPerCharacter(UINT c)
{
	return characterPtrM :: isDoubleByteCharacter((characterU)c) ? 2 : 1;
}

void SBFC_Character :: DecrementCharacterPtr (characterPtr &ptr, characterPtr ptrBase)
{
#ifdef _UNICODE_8
	characterPtr	tempPtr = ptrBase;
	while (*ptrBase && ptrBase < ptr)
	{
		tempPtr = ptrBase;
		ptrBase++;
	}
	ptr = tempPtr;
#else
	ptr--;
#endif
}

void SBFC_Character :: StringCopy (characterPtr dst, const_characterPtr src)
{
	while (*src)
	{
		*(character*)dst = *src;
		src++;
		dst++;
	}
	*(character*)dst = (character)0;
}

void SBFC_Character :: StringCopyNoZero (characterPtr dst, const_characterPtr src)
{
	while (*src)
	{
		*(character*)dst = *src;
		src++;
		dst++;
	}
}

bool SBFC_Character :: StringCompare (const_characterPtr dst, const_characterPtr src)
{
	while (*dst && *src)
	{
		if (*src++ != *dst++)
			return 1;	// Not a match
	}
	return false;	// Sucessful compare - strings are a match.
}

bool SBFC_Character :: StringNCompare (const_characterPtr dst, const_characterPtr src, int length)
{
	while (*dst && *src && length > 0)
	{
		if (*src++ != *dst++)
			return 1;	// Not a match
		length--;
	}
	return false;	// Sucessful compare - strings are a match.
}

bool SBFC_Character :: StringCompareNoCase (const_characterPtr dst, const_characterPtr src)
{
	while (*dst && *src)
	{
		if (UpperCase(*src++) != UpperCase(*dst++))
			return 1;	// Not a match
	}
	return false;	// Sucessful compare - strings are a match.
}

unsigned int SBFC_Character::StringLength(const character *s)
{
	unsigned int uLength = 0;
	character	*cp = (character*)s;
	while (*cp++)
		uLength++;
	return uLength;
}

unsigned int SBFC_Character :: StringByteLength (const const_characterPtr ptr)
{
	unsigned int	u_len = 0;

	try
	{
		character *cp = (character*)ptr;
		while (*cp)
		{
			u_len += sizeof(character);
			cp++;
		}
	} catch (...)
	{
		u_len = 0;
	}
	return u_len;
}

double	SBFC_Character :: StringToDouble(const const_characterPtr ptr)
{
#ifdef _UNICODE_8
	return atof(ptr);
#endif
#ifdef _UNICODE_16
#	ifdef	UNIX
		return wcstod (ptr, NULL); //const wchar_t*, wchar_t**);
#	else
		return _wtof(ptr);
#	endif
#endif
}

long	SBFC_Character :: StringToInteger(const const_characterPtr ptr)
{
#ifdef _UNICODE_8
	return atoi(ptr);
#endif
#ifdef _UNICODE_16
#	ifdef	UNIX
		return wcstol (ptr, NULL, 10); //const wchar_t*, wchar_t**);
#	else
		return _wtoi(ptr);
#	endif
#endif
}

bool SBFC_Character :: isWhiteSpace (const character c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

bool SBFC_Character :: isAlphaNumeric (const character c)
{
	if (c>='0' && c <= '9')
		return true;
	const char uc = UpperCase(c);
	return (uc >= 'A' && uc <= 'Z');
}

// I should be using the locales from Unix.
bool SBFC_Character :: IsDigit(const character c)
{
	return ((c >= '0' && c <= '9') || c == '.' || c == '-');
}

character SBFC_Character :: UpperCase (const character c)
{
//	return SBFC_Character::toupper(c);
	return toupper(c);
//	if (c >= 'a' && c <= 'z') c -= ('a' - 'A');
//    return c;
}

/*
character SBFC_Character::toupper(const character c)
{
#ifdef UNIX
	std::locale loc1 ( "" );
#else
	std::locale loc1 ( "English_Australia" );
#endif
	return std::use_facet<std::ctype<character> > ( loc1 ).toupper ( c );
}
*/

