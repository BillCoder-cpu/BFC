//*/
/*
					CBfc_String.cpp : 
	
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

#ifdef UNIX
#	if defined(__GNUC__)
		typedef CHARACTER_PTR		LPCTSTR;
#		include <wchar.h>
#	else
#		include "windef.h"
#		include <tchar.h>
#	endif
#	include <ctype.h>
#else
	#include <Windows.h>
	#include <stdarg.h>
	#include <tchar.h>
//	typedef CHARACTER_PTR		LPCTSTR;
#endif

#if !defined(max)
#	define min(a,b) a<b?a:b
#	define max(a,b) a>b?a:b
#endif


#define	STRING_INITIALIZER	m_nDataLength (0), m_nByteLength (0), m_save_ptr (NULL), m_ascii_ptr (NULL)


namespace CBfc {
/*
STRING_ASCII::operator char *() const 
{
}

STRING_ASCII::STRING_ASCII(const char* ptr)
{
	*this = ptr;
}

void STRING_ASCII :: operator = (const char* ptr)
{
	if (!ptr)
		Empty();
	else
	{
		UINT len = bfc_strlen(ptr);
		if (len >= BFC_MAX_STRING_LENGTH-1)
			throw Exception(Exception::EBFC_EXC_STRING_LIMITATION);
		character pad[BFC_MAX_STRING_LENGTH];
		UINT uLen = SBFC_Character::UTF8toUF16 (ptr, pad);
		SetEqual (pad, uLen);
	}
}
*/
////////////////////////////////

STRING::STRING () : STRING_INITIALIZER
{
}

STRING::STRING(const STRING *p_srcString) : STRING_INITIALIZER {
	*this = *p_srcString;
}

#ifndef _UNICODE_8
STRING::STRING(const char* ptr) : STRING_INITIALIZER {
	*this = ptr;
}
STRING::STRING(const const_characterPtr ptr) : STRING_INITIALIZER {
	*this = ptr;
}

#endif

STRING::STRING(const std::string &std_s) : STRING_INITIALIZER {
	*this = std_s.c_str();
}

STRING::STRING(const characterPtr ptr) : STRING_INITIALIZER {
	*this = ptr;
}

STRING::STRING(const STRING &srcString) : STRING_INITIALIZER {
	*this = srcString;
}

STRING::~STRING() {
	BFC_RELEASE (m_ascii_ptr);
	UnLock ();
}

void STRING::UnLock ()
{
	if (m_save_ptr)
	{
		m_buffer.DeReferenceBytes (m_save_ptr);
		m_save_ptr = NULL;
	}
}

void STRING::Lock ()
{
#ifdef _DEBUG
	if (IsLocked())		// For Now!! - in future, nest
	{
		ASSERT(0,"STRING::Lock");
		throw Exception (Exception::EBFC_EXC_ILLEGAL_ACCESS_ALREADYLOCKED);
	}
#endif
	m_buffer.ReferenceBytes (0, m_buffer.GetBytesAllocated (), m_save_ptr);
	AssessStringLength ();
	Changed();
}

void STRING::Lock (int bytechange)
{
#ifdef _DEBUG
	if (IsLocked())		// For Now!! - in future, nest
	{
		ASSERT(0,"STRING::Lock");
		throw Exception (Exception::EBFC_EXC_ILLEGAL_ACCESS_ALREADYLOCKED);
	}
#endif
	AssessStringLengthDelta (bytechange);
	Changed();
}

/*
void STRING::LockSet (int bytelength)
{
	if (IsLocked())		// For Now!! - in future, nest
	{
		ASSERT(0);
		throw Exception (Exception::EBFC_EXC_ILLEGAL_ACCESS_ALREADYLOCKED);
	}
//	AssessStringLengthDelta (bytechange);
	Changed();
}
*/

bool STRING::IsLocked () const
{
	return (m_save_ptr != NULL);
}


void STRING::operator += (const STRING &addString)
{
	if (!addString.IsEmpty())
		AddPtr (addString.GetPtr(), addString.GetLengthBytes());
}

void STRING::operator += (const characterPtr addString)
{
	const UINT uLen = SBFC_Character::StringByteLength(addString);
	if (uLen)
		AddPtr (addString, uLen);
}

void STRING::operator += (const character addChar)
{
// 	AddPtr (characterPtr(&addChar),SBFC_Character::BytesPerCharacter(addChar));
	AddPtr (characterPtr(&addChar),sizeof(character));
}

void STRING::InsertAt(const STRING &insertString, const UINT offset)
{
	const UINT uLen = insertString.GetLengthBytes();
	if (uLen)
	{
		UnLock ();
		if ( m_buffer.EnsureBytesAllocated (GetLengthBytes() + uLen) )
		{
			characterPtr	cp(GetPtr());
			cp += offset;

			const UINT	uOurLen = SBFC_Character::StringByteLength(cp)+sizeof(character);
			copy_memory (BYTEPTR(cp)+uLen, BYTEPTR(cp), uOurLen);	// make space for insrtion, include trailing zero
			memcpy (cp,insertString.GetPtr(),uLen);
		}
		Lock ();		// Re-Reference at each operator = assignment
	}
}

void STRING::AddPtr (const characterPtr ptr, const UINT BytesToAdd)
{
	UnLock ();
	if ( m_buffer.EnsureBytesAllocated (GetLengthBytes() + BytesToAdd) )
	{
//		SBFC_Character :: StringCopy (characterPtr(m_buffer.GetPtr()+GetLengthBytes()), ptr);
		BYTEPTR	end(m_buffer.GetPtr()+GetLengthBytes());
		memcpy (end, ptr, BytesToAdd);
		memset (end+BytesToAdd, 0, sizeof(character));
	}
	Lock (BytesToAdd);		// Re-Reference at each operator = assignment
}

void STRING::operator = (const STRING &srcString)
{
	SetEqual (srcString.GetPtr(), srcString.GetLengthBytes());
}

void STRING :: operator = (const characterPtr ptr)
{
	if (!ptr)	Empty();
	else		SetEqual (ptr, SBFC_Character :: StringByteLength (ptr));
}

#ifndef _UNICODE_8
void STRING :: operator = (const const_characterPtr ptr)
{
	if (!ptr)	Empty();
	else		SetEqual (ptr, SBFC_Character :: StringByteLength (ptr));
}
#endif

void STRING :: operator = (const char* ptr)
{
	if (!ptr)
		Empty();
	else
	{
		UINT len = bfc_strlen(ptr);
		if (len >= BFC_MAX_STRING_LENGTH-1)
			throw Exception(Exception::EBFC_EXC_STRING_LIMITATION);
		character pad[BFC_MAX_STRING_LENGTH];
		UINT uLen = SBFC_Character::UTF8toUF16 (ptr, pad);
		SetEqual (pad, uLen);
	}
}

int STRING::bfc_strlen(const char* ptr)
{
	int count = 0;
	while (count < BFC_MAX_STRING_LENGTH)
	{
		if (*ptr++ == 0)
			return count;
		count++;
	}
	return count;
}


// ulBytesFilled does not include the trailing zero
void STRING :: SetEqual (const const_characterPtr ptr, unsigned long ulBytesFilled)
{
	if (!ptr || !ulBytesFilled)
		Empty();
	else
	{
/*
		if (m_buffer.GetBytesAllocated() > ulBytesFilled &&
			 m_buffer.GetBytesAllocated() - ulBytesFilled > 500)
			m_buffer.Free ();								// Optional!!!!!
*/
		UnLock ();
		if ( m_buffer.EnsureBytesAllocated ( ulBytesFilled + sizeof(character) ) )
		{
			BYTEPTR buffer = m_buffer.GetPtr();
			memcpy (buffer, ptr, ulBytesFilled);
			buffer += ulBytesFilled;
			const characterPtr p_zero = (characterPtr)buffer;
			*p_zero = 0;
		}
//		SBFC_Character :: StringCopy (characterPtr(m_buffer.GetPtr()), ptr);
		Lock ();		// Re-Reference at each operator = assignment
	}
}

bool STRING::operator != (const STRING &cmpString) const
{
	return Compare(cmpString) != 0;
}

bool STRING::operator != (const characterPtr cmpString) const
{
	return Compare(cmpString) != 0;
}


bool STRING::operator == (const STRING &cmpString) const
{
	return Compare(cmpString) == 0;
}

bool STRING::operator == (const characterPtr cmpString) const
{
	return Compare(cmpString) == 0;
}


bool STRING::LeftEquals(const STRING &match) const
{
	return match.Compare(this->GetPtr(),GetLengthChars()) == 0;
}

//inline const characterPtr STRING :: operator *() const
//{
//	characterPtr cp = m_buffer;
//	return (const characterPtr) cp;
//}


// SetLength()
// Fills in any additional space with spaces.
// Does not yet make strings smaller!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void STRING::SetLength(unsigned long uLength)
{
	const long iLenDiff = uLength - GetLength();
	if (iLenDiff > 0)
	{
		UnLock ();
		if ( m_buffer.EnsureBytesAllocated (GetLengthBytes() + (iLenDiff * sizeof(character))) )
		{
			characterPtrM	end(m_buffer.GetPtr()+GetLengthBytes());
			for (long i=0; i<iLenDiff; i++)
				end.stav(' ');
			end.stav(0);
		}
		Lock ();		// Re-Reference at each operator = assignment
	}
}

void STRING :: Empty()
{
	UnLock();
	m_buffer.Free ();
	m_nByteLength = m_nDataLength = 0;
	m_save_ptr = NULL;
	BFC_RELEASE (m_ascii_ptr);
}

bool STRING :: IsEmpty () const
{
	return (m_nByteLength == 0 || GetBytesAllocated() == 0);
}

UINT STRING :: GetBytesAllocated () const
{
	return m_buffer.GetBytesAllocated ();
}



// Called whenever the string is added on to
void STRING :: AssessStringLengthDelta (int delta)
{
	const UINT byteSize = m_buffer.GetBytesAllocated();
	m_buffer.ReferenceBytes (0, byteSize, m_save_ptr);
	
	if ( byteSize )
	{
		characterPtr cp = (characterPtr)((BYTEPTR)m_save_ptr + m_nByteLength);
		m_nByteLength += delta;
		
		characterPtr  cp_end;
		cp_end = (characterPtr)((BYTEPTR)m_save_ptr + byteSize);

		while (cp < cp_end && *cp)
		{
			m_nDataLength += 1;
			cp++;
		}
		if (cp == cp_end)	// Make sure ends in a zero (we have a little pad here courtesy of m_buffer!)
#ifdef _UNICODE_8_MBCS
			cp.stav (0);
#else
			*cp = 0;
#endif
	} else
		m_nDataLength = m_nByteLength = 0;
}


// Called whenever the string is changed
void STRING :: AssessStringLength ()
{
	character*	ptr;

	const UINT byteSize = m_buffer.GetBytesAllocated();
	if ( byteSize && m_buffer.ReferenceBytes (0, byteSize, ptr) )
	{
		characterPtr cp;
		cp = (characterPtr)ptr;
		characterPtr  cp_end;
		cp_end = (characterPtr)((BYTEPTR)ptr + byteSize);

		m_nDataLength = 0;
		while (cp < cp_end && *cp)
		{
			m_nDataLength += 1;
			cp++;
		}
		m_nByteLength = (BYTEPTR)(character*)cp - (BYTEPTR)ptr;
		if (cp == cp_end)		// Make sure we end in a zero (we have a little padding here courtesy of m_buffer!)
#ifdef _UNICODE_8_MBCS
			cp.stav (0);
#else
			*cp = 0;
#endif
	} else
		m_nDataLength = m_nByteLength = 0;
}

// returns 0 on match
int	STRING::CompareNoCase(const STRING &csCompare) const
{
	const bool	b_CaseSensitive = false;
	return Compare (csCompare, b_CaseSensitive);
}

// returns 0 apon match
int	STRING::Compare(const STRING &csCompare, bool b_CaseSensitive) const
{
	if (GetLengthChars() == csCompare.GetLengthChars())
	{
		characterPtr	tp = csCompare.GetBufferPtr ();
		if (tp)
		{
			if (b_CaseSensitive)
				return Compare(tp, GetLengthChars());
			else
				return CompareNoCase(tp, GetLengthChars());
		}
		if (IsEmpty())
			return 0;
	}
	return -1;
}


// returns 0 on first characters identical
int STRING::Compare(const characterPtr lpsz_compare, const unsigned int u_MaxLen) const
{
	int				i_rVal = -1;
	CHARACTER_PTR	ptr;
	UINT			u_Index = 0;
	UINT			u_CompareLen = GetLengthChars();
	characterPtr	lpsz = lpsz_compare;

	if (IsEmpty())
		return (*lpsz != 0);

	if (u_MaxLen)
		u_CompareLen = min (u_MaxLen, u_CompareLen);

	if ( u_CompareLen && m_buffer.ReferenceBytes (0, (u_CompareLen+1)*sizeof(character), ptr) )
	{
		i_rVal = 0;
		characterPtr tcp_compare (ptr);
		while (u_Index < u_CompareLen)
		{
			bool b_break = (*tcp_compare==0 || *lpsz==0);
#ifdef _UNICODE_8_MBCS
			const UINT u_CharacterLength = tcp_compare.GetNextCharacterLength();
			if (*tcp_compare++ != *lpsz++)
			{
				i_rVal = (char*)(character*)tcp_compare-ptr;
				break;
			}
			u_Index += u_CharacterLength;
#else
			if (*tcp_compare++ != *lpsz++)
			{
				i_rVal = tcp_compare-ptr;
				break;
			}
			u_Index++;
#endif
			if (b_break)
				break;
		}
		m_buffer.DeReferenceBytes (ptr);
	}
	return i_rVal;
}


int STRING::CompareNoCase(characterPtr lpsz_compare, const unsigned int u_MaxLen) const
{
	int							i_rVal = -1;
	CHARACTER_PTR	ptr;
	UINT						u_Index = 0;
	UINT						u_CompareLen = GetLengthChars();
	characterPtr				lpsz = lpsz_compare;

	if (IsEmpty())
		return (*lpsz != 0);
	if (u_MaxLen)
		u_CompareLen = min (u_MaxLen, u_CompareLen);

	if ( u_CompareLen && m_buffer.ReferenceBytes (0, (u_CompareLen+1)*sizeof(character), ptr) )
	{
		characterPtr tcp_compare = ptr;
		i_rVal = 0;

		while ( u_Index < u_CompareLen )
		{
#ifdef _UNICODE_8_MBCS
			const UINT u_CharacterLength = tcp_compare.GetNextCharacterLength();
#endif
			const character c1 = *tcp_compare++;
			const character c2 = *lpsz++;
			if (c1==0 || c2==0) {
				i_rVal = (c1 != c2);
				break;
			}
#ifdef _UNICODE_8_MBCS
			if (SBFC_Character::UpperCase(c1) != SBFC_Character::UpperCase(c2))
			{
				i_rVal = (char *)(character*)tcp_compare - ptr;
				break;
			}
			u_Index += u_CharacterLength;
#else
			if (SBFC_Character::UpperCase(c1) != SBFC_Character::UpperCase(c2))
			{
				i_rVal = tcp_compare-ptr;
				break;
			}
			u_Index++;
#endif
		}
		m_buffer.DeReferenceBytes (ptr);
	}
	return i_rVal;
}

char *STRING::BorrowAsciiBuffer()
{
	BFC_RELEASE (m_ascii_ptr);
	m_ascii_ptr= MakeAsciiBuffer();
	return m_ascii_ptr;
}

char *STRING::MakeAsciiBuffer() const
{
#ifdef _UNICODE_8
	const UINT ulen=GetLengthBytes()+1;
	char *ptr = new char[ulen]; // (ulen);
	memcpy (ptr, GetPtr(), ulen);			// Wont work for MBCS
#else
#	ifdef _UNICODE_16
		char *ptr=NULL;
		UINT ulen = SBFC_Character::UTF16toUF8_CountBytes(GetPtr());
		if (ulen)
		{
			ulen+=4;
			ptr = new char[ulen];
			SBFC_Character::UTF16toUF8 (GetPtr(), ptr);
		} else
		{
			ptr = new char[4];
			ptr[0]=ptr[1]=ptr[2]=ptr[3]=0;
		}
#	else
		ERROR - yet unsupported!
#	endif
#endif
	return ptr;
}

characterPtr STRING :: GetBuffer (unsigned int i_maxByteLength)
{
	m_buffer.IncrementReference ();
	if ( m_buffer.EnsureBytesAllocated (i_maxByteLength) )
		return characterPtr (m_buffer.GetPtr());
	return characterPtr ((BYTEPTR)NULLPTR);
}

// Returns true if buffer is now unused by anyone.
bool STRING :: ReleaseBuffer ()
{
	AssessStringLength ();
	return true;
// 	return m_buffer.DecrementReference ();
}

bool STRING::ReferenceBuffer(characterPtr &cPtr)
{
	CHARACTER_PTR	bytePtr;
	if (m_buffer.ReferenceBytes (0, m_buffer.GetBytesAllocated (), bytePtr))
	{
		cPtr = bytePtr;
		return true;
	} else
	{
		cPtr = (CHARACTER_PTR)NULL;
		return false;
	}
}

bool STRING::DeReferenceBuffer (characterPtr &cPtr) 
{
	if (cPtr)
		return m_buffer.DeReferenceBytes (cPtr);
	else
		return false;
}

/*
characterPtr STRING::GetBufferPtr (void) const
{
	return GetPtr();
	if (IsLocked ())
	{
		return characterPtr	(m_save_ptr);
	} else
		throw Exception (Exception::EBFC_EXC_ILLEGAL_ACCESS_UNLOCKED_CONSTANT);
}
*/

characterPtr STRING::GetAtPtr (unsigned int uIndex)
{
	return GetAtPtr_const (uIndex);
}

characterPtr STRING::GetAtPtr_const (unsigned int uIndex) const
{
	characterPtr cp = GetBufferPtr();
	if ( cp )
	{
		characterPtr cp_end((CHARACTER_PTR)m_buffer.GetEndPtr());
		while (cp < cp_end)
		{
			if (!uIndex--)
				return cp;
			cp++;
		}
	}
	return characterPtr(NULLPTR);
}

void	STRING::RemoveAt(unsigned int uIndex)
{
	STRING	cs;
	if (uIndex)
		cs = Left(uIndex);
	
	if (uIndex < GetLength())
		cs +=  RightFrom(uIndex+1);
	*this = cs;
}

void	STRING::Remove(const character c)
{
	int	index;
	while (1)
	{
		index = Find(c);
		if (index < 0)
			return;
		RemoveAt(index);
	}
}

void	STRING::RemoveWhitespace()
{
	int	index;
	const STRING	ws(" \t\r\n");
	
	while (1)
	{
		index = FindOneOf(ws);
		if (index < 0)
			return;
		RemoveAt(index);
	}
}

// Increases the length og the string if beyond the end
void STRING::SetAt(const character c, unsigned int uIndex)
{
	if (uIndex >= GetLength())
		SetLength(uIndex+1);
	characterPtr cp = GetAtPtr_const(uIndex);
	*cp = c;
}

character STRING::GetAt (unsigned int uIndex) const
{
	const characterPtr cp = GetAtPtr_const(uIndex);
	if (cp)
		return *cp;
	return 0;
}

bool STRING::EndsWith (const STRING &end) const
{
	STRING	myend = Right(end.GetLengthChars());
	return myend == end;
}

STRING STRING::Right (unsigned int uCount) const
{
	return RightFrom(GetLengthChars()-uCount);
}

character STRING::Right() const
{
	if (GetLengthChars())
		return GetAt(GetLengthChars()-1);
	return 0;
}

#pragma message ("Needs bounds checking")
STRING STRING::RightFrom (unsigned int uIndex) const
{
	return STRING (GetAtPtr_const (uIndex));
}

STRING STRING::Left (unsigned int uCount) const
{
#if 1
	STRING	rvalString;
	UINT bytes = uCount * sizeof(character);

	rvalString.SetEqual(GetPtr(),bytes);
#else
	STRING	rvalString(*this);
	if (uCount > GetLengthChars())
		uCount = GetLengthChars();
	*((character*)rvalString.GetAtPtr(uCount)) = 0;
#endif
	return rvalString;
}

STRING STRING::LeftFrom (unsigned int uIndex) const
{
	return Left(GetLengthChars()-uIndex);
}

#pragma message ("Needs bounds checking")
STRING STRING::Mid (unsigned int uLeft, unsigned int uRight) const
{
	ASSERT((uRight >= uLeft),"STRING::Mid");
	STRING	rvalString(GetAtPtr_const(uLeft));

	const UINT	uLength = uRight-uLeft+1;
	rvalString.Terminate (uLength);
	return rvalString;
}

void STRING::Terminate(const UINT len)
{
	if (GetLengthChars() > len)
	{
		character *cp = (character*)GetAtPtr(len);
		*cp = 0; //ZERO;
		m_nDataLength = len;
		m_nByteLength = (BYTEPTR)cp - (BYTEPTR)GetPtr();
	}
}


STRING STRING::SpanExcluding (const characterPtr lpsz)
{
	int	iIndex = FindOneOf (lpsz);
	if (iIndex >= 0)
		return Left (iIndex);
	return *this;
}


bool STRING::RemoveQuotes()
{
	if (GetAt(0)=='"')
	{
		UINT	uRight = GetLengthChars();
		if ((uRight > 1))
		{
			uRight--;
			if (GetAt(uRight) == '"')
				uRight--;
		}
		*this = Mid(1,uRight);
		return true;
	}
	return false;
}


void	STRING::Trim(const UINT left, const UINT right)
{
	TrimLeft(left);
	TrimRight(right);
}

void STRING::TrimLeft (const UINT count)
{
	if (count < GetLengthChars())
		*this = Right (GetLengthChars()-count);
	else
		Empty();
}

void STRING::TrimRight (const UINT count)
{
	if (count < GetLengthChars())
		*this = Left (GetLengthChars()-count);
	else
		Empty();
}

bool STRING::Trim(void)
{
	return TrimLeft() | TrimRight();
}

bool STRING::TrimLeft (void)
{
	UINT index=0;
	while (SBFC_Character::isWhiteSpace(GetAt(index)))
		index++;
	if (index)
	{
		TrimLeft(index);
		return true;
	}
	return false;
}

bool STRING::TrimRight (void)
{
	bool bRval = false;
	
	while (SBFC_Character::isWhiteSpace(Right()))
	{
		bRval = true;
		TrimRight(1);
	}
	return bRval;
}

// returns true if trimmed
bool STRING::TrimLeft (const STRING &match)
{
	if (LeftEquals(match))
	{
		TrimLeft (match.GetLength());
		return true;
	}
	return false;
}

static bool isWordEdge(character c)
{
	static STRING	scmp(" \t\r\n\"\\';:.,=-+*/<>&|%!()[]{}");
	return (scmp.Find(c)>=0);
}

int	STRING::Find(const STRING s, const UINT u_Start, const bool bWhole, const bool bCase) const
{
	const			bool b_Reverse=false;
	UINT			u_CompareLen = GetLength();
	const UINT		u_OtherLen = s.GetLength();

	if (u_OtherLen == 0 || u_CompareLen <= u_Start + u_OtherLen)
		return -1;
	u_CompareLen -= u_Start;

	UINT			uIndex = u_Start;
	characterPtr	cp_buffer = GetPtr ();
	
	if ( cp_buffer )
	{
		characterPtr	cp_base(cp_buffer);
		if (b_Reverse)
		{
			cp_buffer += u_CompareLen-u_OtherLen;
		} else
			cp_buffer += u_Start;

	
		bool	b_wordbreak = true;
		while (u_CompareLen >= u_OtherLen && *cp_buffer)
		{
			if (!bWhole || b_wordbreak)
			{
				bool bFound = false;
				if (bCase)
				{
					if (SBFC_Character :: StringCompare (cp_buffer, s.GetPtr()) == 0) bFound = true;
				} else {
					if (SBFC_Character :: StringCompareNoCase (cp_buffer, s.GetPtr()) == 0) bFound = true;
				}
				if (bFound)
				{
					if (!bWhole || isWordEdge(cp_buffer[s.GetLengthChars()]))								
						return uIndex;
				}
			}
			b_wordbreak = isWordEdge (*cp_buffer);
			if (b_Reverse)
				SBFC_Character :: DecrementCharacterPtr(cp_buffer,cp_base);
			else
				cp_buffer++;
			uIndex++;
			u_CompareLen--;
		}
	}
	return -1;
}



// SHould call into the string version!
int STRING::Find(const character c, const UINT u_Start, const bool b_Reverse) const
{
	UINT			u_CompareLen = GetLength();

	if (u_CompareLen <= u_Start)
		return -1;
	u_CompareLen -= u_Start;

	UINT	uIndex = u_Start;
//	Lock ();
	characterPtr	cp_buffer = GetPtr ();
	if ( cp_buffer )
	{
		characterPtr	cp_base(cp_buffer);
		if (b_Reverse)
		{
			cp_buffer += u_CompareLen-1;
		} else
			cp_buffer += u_Start;

		while (u_CompareLen && *cp_buffer)
		{
			if ( *cp_buffer == c )
				return uIndex;
			if (b_Reverse)
				SBFC_Character :: DecrementCharacterPtr(cp_buffer,cp_base);
			else
				cp_buffer++;
			uIndex++;
			u_CompareLen--;
		}
	}
//	UnLock ();
	return -1;
}

//
int STRING::FindOneOf(const STRING &csItems) const
{
	UINT	uIndexRval=0;
	const UINT	uLen=GetLength();

	while (uIndexRval < uLen)
		if (csItems.Find(this->GetAt(uIndexRval++)) >= 0)
			return --uIndexRval;
	return -1;
}

//
int STRING::FindOneOf(characterPtr lpsz) const
{
	return FindOneOf(STRING(lpsz));
}

void STRING::ToUpperCase()
{
	character c,v;
	characterPtr cp(GetPtr());
	while ((c=*cp))
	{
		v = SBFC_Character::UpperCase (c);
		if (v != c)
			*cp = v;
		cp++;
	}
}

// Replace every instance of the substring search with replace.
// returns the number of occurances.
int	STRING::Replace(const STRING &search, const STRING &replace, const bool bWhole, const bool bCase)
{
	int	i_count = 0;
	int	iIndex=0;
	do
	{
		iIndex = Find(search, iIndex, bWhole, bCase);
		if (iIndex >= 0)
		{
			Replace (iIndex, search, replace);
			iIndex += replace.GetLengthChars();
			i_count++;
		}
	} while (iIndex >= 0);
	return i_count;
}

void STRING::Replace (const int iIndex,const STRING &search, const STRING &replace)
{
	Replace (iIndex,iIndex + search.GetLengthChars(), replace);
}

// single shot
void STRING::Replace (const int iIndexStart,const int iIndexEnd, const STRING &replace)
{
#if 1
	STRING	sEnd = RightFrom(iIndexEnd);
	
	Terminate (iIndexStart);
	*this += replace;
	*this += sEnd;
#else
	STRING s_r = Left(iIndexStart);
	s_r += replace;
	s_r += RightFrom(iIndexEnd);
	*this = s_r;
#endif
}

// For each member of substitute_array, replace every instance of it in the string with
//  the corresponding member of replace_array.
// Returns true if the string was changed.
bool STRING::Substitute (const StringArray &substitute_array, const StringArray &replace_array)
{
	ULONG	nCount = substitute_array.GetCountAsULONG();
	if (replace_array.GetCountAsULONG() < nCount)
		nCount = replace_array.GetCountAsULONG();
	ULONG	nIndex;
	bool	b_rVal = false;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		STRING	*p_sub, *p_rep;
		p_sub = substitute_array[nIndex];
		p_rep = replace_array[nIndex];
		if (Replace (*p_sub, *p_rep))
			b_rVal = true;
	}
	return b_rVal;
}


/*
bool	 __cdecl STRING::Format (const STRING &csFormat, ...)
{
	STRING8 s8;
	va_list argList;
	va_start (argList, csFormat);
	FormatV (s8.GetPtr8(), argList);
	va_end (argList);
	return true;
}
*/

bool __cdecl STRING::Format (const CHARACTER_PTR lpszFormat, ...)
{
	va_list argList;
	va_start (argList, lpszFormat);
//    CHARACTER_PTR t = va_arg( argList, CHARACTER_PTR);	// Throw away 1st arg
	FormatV (lpszFormat, argList);
	va_end (argList);
	return true;
}

#ifndef _UNICODE_8
bool	 __cdecl STRING::Format (const char *lpszFormat, ...)
{
	va_list argList;
	va_start (argList, lpszFormat);
	FormatV (lpszFormat, argList);
	va_end (argList);
	return true;
}
#endif


#define	CHAR_ARG				int		// char
#define	DOUBLE_ARG			double
#define	WIDE_CHAR_ARG	int		// characterW

#define FORCE_ANSI      	0x10000
#define FORCE_UNICODE	0x20000
#define FORCE_INT64     	0x40000

#ifndef _UNICODE_8
void STRING::FormatV(const CHARACTER_PTR lpszFormat, va_list argList)
{
	STRING8 s8(lpszFormat);
	char* ptr = s8.GetPtr8();
	FormatV (ptr, argList);
}
#endif

//
// Include full support for standard %d, %f, %g,
//		plus my own which takes a CBfc_Value & and decides on best way to display.
//
#define INSERT_L	1
void STRING::FormatV(const char *lpsz_Format, va_list argList)
{
	va_list argListSave;
	va_copy (argListSave, argList);
	int nMaxLenChars = 0;					// make a guess at the maximum length of the resulting string
// 	character		outpad[2048];
// 	character		*p_op = outpad;
//	STRING_ASCII		sa(lpszFormat);
#ifdef INSERT_L
	char		inpad[4096];
	strcpy (inpad, lpsz_Format);
#else // ifdef INSERT_L
	char *inpad=lpsz_Format;
#endif // ifdef INSERT_L
	
	characterPtrM	lpsz(inpad);	// Handle MBCS gracefully
	for (; *lpsz != '\0';  lpsz++)
	{
// 		const bool b_PercentPercent = (*lpsz=='%' && lpsz[1]=='%');
		// handle '%' character, but watch out for '%%'
		if (*lpsz != '%' || *(++lpsz) == '%')
		{
			nMaxLenChars += 2; //SBFC_Character::StringLength(lpsz);
			continue;
		}

		int nItemLen = 0;
		int nWidth = 0;						// handle '%' character with format
		for (; *lpsz != '\0'; lpsz++)
		{
			// check for valid flags
			if (*lpsz == '#')
				nMaxLenChars += 2;   // for '0x'
			else if (*lpsz == '*')
				nWidth = va_arg(argList, int);
			else if (*lpsz == '-' || *lpsz == '+' || *lpsz == '0' ||
				*lpsz == ' ')			
					;
			else // hit non-flag character
				break;
		}
		// get width and skip it
		if (nWidth == 0)		// width indicated by
			nWidth = lpsz.ReadInteger ();

		int nPrecision = 0;
		if (*lpsz == '.')
		{
			lpsz++;						// skip past '.' separator (width.precision)
			if (*lpsz == '*')			// get precision and skip it
			{
				nPrecision = va_arg(argList, int);
				lpsz++;
			}
			else
				nPrecision = lpsz.ReadInteger();
//			ASSERT(nPrecision >= 0);
		}

		// should be on type modifier or specifier
		int nModifier = 0;
		if (SBFC_Character :: StringCompare(lpsz, _TXT("I64")) == 0)
		{
			lpsz += 3;
			nModifier = FORCE_INT64;
#if !defined(_X86_) && !defined(_ALPHA_)
			// __int64 is only available on X86 and ALPHA platforms
//			ASSERT(FALSE);
#endif
		}
		else
		{
			switch (*lpsz)
			{			// modifiers that affect size
			case 'h':
				nModifier = FORCE_ANSI;
				lpsz++;
				break;
			case 'l':
				nModifier = FORCE_UNICODE;
				lpsz++;
				break;

			case 'F':			// modifiers that do not affect size
			case 'N':
			case 'L':
				lpsz++;
				break;
			}
		}

		// now should be on specifier
		switch (*lpsz | nModifier)
		{
		// single characters
		case 'c'|FORCE_ANSI:		case 'C'|FORCE_ANSI:
			nItemLen = 2;
			va_arg(argList, CHAR_ARG);
			break;
		case 'c':		case 'C':
#ifndef _UNICODE_16
			nItemLen = 2;
			va_arg(argList, character);
			break;
#endif
		case 'c'|FORCE_UNICODE:		case 'C'|FORCE_UNICODE:
			nItemLen = 2;
			va_arg(argList, WIDE_CHAR_ARG);
			break;

		// strings

		case 's'|FORCE_ANSI:		case 'S'|FORCE_ANSI:
			{
				const characterPtrA pstrNextArg = va_arg(argList, characterPtrA);
				if (pstrNextArg == NULL)
				   nItemLen = 6; // "(null)"
				else
				{
				   nItemLen = bfc_strlen(pstrNextArg);
				   nItemLen = max(1, nItemLen);
				}
			}
			break;

		case 's':		case 'S':
#ifndef _UNICODE_8
#	ifdef INSERT_L
				// 
				characterPtrM::InsertIntoString (lpsz, 'l');
				nMaxLenChars += 1;
				lpsz++;
#	endif	// ifdef INSERT_L
#endif // ifndef _UNICODE_8

#ifdef _UNICODE_32
					Error!
#else
#	ifndef _UNICODE_16
		{
			LPCTSTR pstrNextArg = va_arg(argList, LPCTSTR);
			if (pstrNextArg == NULL)
				nItemLen = 6;  // "(null)"
			else
			{
				nItemLen = SBFC_Character::StringLength(pstrNextArg);
				nItemLen = max(1, nItemLen);
			}
		}
		break;
#	endif	
#endif
		case 's'|FORCE_UNICODE:		case 'S'|FORCE_UNICODE:
			{
				const characterPtrW pstrNextArg = va_arg(argList, characterPtrW);
				if (pstrNextArg == NULL)
				   nItemLen = 6; // "(null)"
				else
				{
				   nItemLen = wcslen((const wchar_t*)pstrNextArg);
				   nItemLen = max(1, nItemLen);
				}
			}
			break;
		}
		
		
		if (nItemLen != 0)		// adjust nItemLen for strings
		{
			if (nPrecision != 0)
				nItemLen = min(nItemLen, nPrecision);
			nItemLen = max(nItemLen, nWidth);
		} else
		{
			switch (*lpsz) 	{
			// integers
			case 'd':			case 'i':			case 'u':			case 'x':			case 'X':			case 'o':
				if (nModifier & FORCE_INT64)
					va_arg(argList, INT64);
				else
					va_arg(argList, int);
				nItemLen = 32;
				nItemLen = max(nItemLen, nWidth+nPrecision);
				break;

			case 'e':			case 'g':			case 'G':
				va_arg(argList, DOUBLE_ARG);
				nItemLen = 128;
				nItemLen = max(nItemLen, nWidth+nPrecision);
				break;

			case 'f':
				va_arg(argList, DOUBLE_ARG);
				nItemLen = 128; // width isn't truncated
				// 312 == bfc_strlen("-1+(309 zeroes).")
				// 309 zeroes == max precision of a double
				nItemLen = max(nItemLen, 312+nPrecision);
				break;

			case 'p':
				va_arg(argList, void*);
				nItemLen = 32;
				nItemLen = max(nItemLen, nWidth+nPrecision);
				break;

			// no output
			case 'n':
				va_arg(argList, int*);
				break;

			default:
//				ASSERT(FALSE);  // unknown formatting option
				;
			}
		}
		nMaxLenChars += nItemLen;			// adjust nMaxLen for output nItemLen
	}

	characterPtr	Ptr = GetBuffer((nMaxLenChars+1)*sizeof(character));
#if  1 //def UNIX
#	ifdef	_UNICODE_16
//		vswprintf(Ptr, nMaxLenChars, inpad, argListSave);
		STRING	tcs(inpad);
#		ifndef MINGW
			vswprintf(Ptr, nMaxLenChars, tcs.GetPtr(), argListSave);
#		else
			vswprintf(Ptr, tcs.GetPtr(), argListSave);
#		endif
#	else
		vsprintf(Ptr, inpad, argListSave);
#	endif
#else
	_vstprintf(Ptr, inpad, argListSave);
#endif
	ReleaseBuffer();

	va_end(argListSave);
}

// getnext break apart into pieces with \n deliminators
UINT STRING::ParseLines(const UINT u_Start,STRING &csNext) const
{
	int		i_End;
	do {
		i_End=Find('\n',u_Start);
		if (i_End == -1)
			return 0;
	} while (i_End <= u_Start);		// skip empty lines
	csNext=Mid(u_Start,i_End-1);
	return i_End+1;
}

StringBuffer :: StringBuffer()
{
	Empty();
}

OVERRIDE void StringBuffer :: Empty ()
{
	STRING::Empty();
	characterPtr szBufPtr = GetBuffer(75*sizeof(character));		// make a nice rounded default size here
	*(character*)szBufPtr = 0;
	ReleaseBuffer();
}

StringBuffer:: StringBuffer(const STRING &cs)
	: STRING(cs)
{
//	m_szBufPtr = GetPtr();
}

void StringBuffer :: DecrementCharacterPtr (characterPtr &ptr)
{
	SBFC_Character :: DecrementCharacterPtr (ptr, characterPtr(m_buffer.GetPtr()));
}

//inline characterPtr StringBuffer :: operator *()
//{
//	return m_szBufPtr;
//}

double STRINGEX :: GetAsDouble() const
{
	Value	value;

	value.SetFromString (*this);
	return value.GetValue_double();
}

UINT STRINGEX :: GetAsUINT() const
{
	Value	value;

	value.SetFromString (*this);
	return value.GetValue_UINT();
}

} // namespace CBfc

