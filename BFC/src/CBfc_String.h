//*/
/*
					CBfc_String.h : 
	
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

#ifndef _BCSTRING_H
#define _BCSTRING_H

#include <stdio.h>
#include <cstdarg>
#include "CBfc_ReferencedObject.h"
#include "character.h"
#include <string>

#define	BFC_MAX_STRING_LENGTH	2048  // Certain code makes this assumption, try not to!!

#define	CBfc_String		CBfc::STRING
#define	CBfc_Str		CBfc_String
#define	CBCString		CBfc_String

#define	CBfc_StringBuffer	CBfc::StringBuffer

namespace CBfc
{

BFC_CLASS STRING	// : public CBfc_ReferencedObject 
					//		Old naming until this baby is ready to roll - my invention.
{
public:
	STRING();
#ifndef _UNICODE_8
	STRING(const char* ptr);
	STRING(const const_characterPtr ptr);
	void operator = (const const_characterPtr ptr);
#endif
	STRING(const std::string &std_s);
	STRING(const characterPtr ptr);
	STRING(const CBfc_String &srcString);
	STRING(const CBfc_String *p_srcString);
	virtual	~STRING();

	void operator = (const char* ptr);
	void operator = (const characterPtr ptr);
	void operator = (const CBfc_String &srcString);
	void SetEqual (const const_characterPtr ptr, unsigned long ulBytesFilled);

	void operator += (const CBfc_String &addString);
	void operator += (const characterPtr addString);
	void operator += (const character addChar);
	void AddPtr (const characterPtr ptr, const UINT BytesToAdd);

	bool operator != (const CBfc_String &cmpString) const;
	bool operator != (const characterPtr cmpString) const;

	bool operator == (const CBfc_String &cmpString) const;
	bool operator == (const characterPtr cmpString) const;

#ifdef _UNICODE_8
	inline operator std::string() {
#ifdef _UNICODE_8
		return std::string(GetPtr());
#else
		havent gone there yet!
		return std::string(GetPtr());
#endif
	}
#endif

	friend STRING operator+( const CBfc_String& str1, const CBfc_String& str2 )
	{
		CBfc_String strResult( str1 );
		strResult += str2;
		return( strResult );
	}
	friend STRING operator+( const CBfc_String& str1, characterPtr sz2 )
	{
		CBfc_String strResult( str1 );
		strResult += sz2;
		return( strResult );
	}
	friend STRING operator+( characterPtr psz1, const CBfc_String& str2 )
	{
		CBfc_String strResult( psz1 );
		strResult += str2;
		return( strResult );
	}
//    inline void operator = (const characterPtr &ptr);
//    inline const characterPtr operator *() const;
	bool		ReferenceBuffer (characterPtr &ptr) ;
	bool		DeReferenceBuffer (characterPtr &cPtr) ;

	bool				IsEmpty () const;
	virtual void		Empty();
	void				ToUpperCase();
	UINT				GetBytesAllocated () const;
	inline unsigned long	GetLength () const {
							return m_nDataLength; }
	inline unsigned long	GetLengthBytes () const {	// Does not include double '/0' at end.
						return m_nByteLength; }

	inline unsigned long GetLengthChars () const {
#ifndef _UNICODE_8
		return GetLength();
#else
		return GetLengthBytes();
#endif
	}
	void       		SetLength(unsigned long uLength);

	// Content Access/Reference Functions
	characterPtr	GetPtr () const {
							return characterPtr(m_buffer.GetPtr ()); }
	characterPtr	GetBufferPtr(void) const {	// Will throw an exception unless the string is locked in memory
							return characterPtr(m_buffer.GetPtr ()); }

	characterPtr	GetBuffer (unsigned int i_maxByteLength);
	bool			ReleaseBuffer ();	       // Returns true if buffer is now unused by anyone.
	characterPtr	GetAtPtr (unsigned int uIndex);
	characterPtr	GetAtPtr_const (unsigned int uIndex) const;

	bool		RemoveQuotes();
	char *		MakeAsciiBuffer() const;
	char *		BorrowAsciiBuffer();
			
	int		CompareNoCase(const CBCString &csCompare ) const;
	int		Compare(const characterPtr lpsz_compare, const unsigned int u_MaxLen = 0) const;
	int		Compare(const CBCString &csCompare, bool b_CaseSensitive = true) const;
	int		CompareNoCase(const characterPtr lpsz_compare, const unsigned int u_MaxLen = 0) const;
	
	bool LeftEquals(const STRING &match) const;

	STRING 		SpanExcluding (characterPtr lpsz);

	void		SetAt(const character c, unsigned int uIndex);
	void		InsertAt(const CBfc_String &insertString, const UINT offset=0);
	character	GetAt (unsigned int uIndex) const;
	inline character operator [] (unsigned int uIndex) const {
						return GetAt (uIndex); }
#ifdef _UNICODE_8
	inline operator const std::string() const {
		return GetPtr();
	}
#endif

	void		RemoveAt(unsigned int uIndex);
	void		Remove(const character c);
	void		RemoveWhitespace();

	bool		EndsWith (const STRING &end) const;

	character	Right() const;
	STRING		Right (unsigned int uCount) const;
	STRING		RightFrom (unsigned int uIndex) const;
	STRING		Left (unsigned int uCount) const;
	STRING		LeftFrom (unsigned int uIndex) const;
	STRING		Mid (unsigned int uLeft, unsigned int uRight) const;

	void		Terminate(const UINT len);

			// returns # of occurances (0 if none)
	int		Replace(const STRING &search, const STRING &replace, const bool bWhole=false, const bool bCase=true);
	void 	Replace (const int iIndex,const STRING &search, const STRING &replace); // single shot replace
	void 	Replace (const int iIndexStart,const int iIndexEnd, const STRING &replace);
	
	bool		Substitute (const StringArray &substitute_array, const StringArray &replace_array);

	void		Trim(const UINT left, const UINT right);
	void		TrimLeft (const UINT count);
	void		TrimRight (const UINT count);
	bool		Trim(void);
	bool		TrimLeft (void);
	bool		TrimRight (void);
	
	bool		TrimLeft (const STRING &match);

	int		Find(const character c, const UINT u_Start=0, const bool b_Reverse=false) const;
	int		Find(const CBCString s, const UINT u_Start=0, const bool bWhole=false, const bool bCase=true) const;
	int		FindOneOf(characterPtr lpsz) const;
	int		FindOneOf(const STRING &cs) const;

	inline int	ReverseFind(const character c, const UINT u_Start=0) const {
					return Find (c, u_Start, true);	}

//	bool	 Format (const STRING &csFormat, ...);
	bool	 Format (const CHARACTER_PTR lpszFormat, ...);
#ifndef _UNICODE_8
	bool	 Format (const char *lpszFormat, ...);
	bool	 Format (const wchar_t* lpszFormat, ...);
	void	 FormatV (const CHARACTER_PTR lpszFormat, va_list argList);
#endif
	void	 FormatV (const char *lpszFormat, va_list argList);

	UINT	ParseLines(const UINT u_Start,STRING &csNext) const;

	static int bfc_strlen(const char* ptr);
protected:
	void		AssessStringLength ();
	virtual 	void Changed() {}					// called whenever string is finished updated

	CBfc_ReferencedAllocation	m_buffer;
	unsigned long			m_nDataLength;  // length of data (including terminator)
	unsigned long			m_nByteLength;
	character *				m_save_ptr;

private:
	bool				IsLocked () const;
	void				Lock ();		// = reference
	void				Lock (int delta);		// = reference
	void				UnLock ();		// = unreference
	void AssessStringLengthDelta (int delta);
	char *					m_ascii_ptr;

//	inline	T*	GetPtr() {//	return pointer to const string
//					return(this->CXrArrayT<T>::GetPtr()); }
};

BFC_CLASS STRING8 : public STRING
{
public:
	STRING8();
#ifndef _UNICODE_8
	STRING8(const char* ptr);
#endif
	STRING8(const characterPtr ptr);
	STRING8(const STRING &srcString);
	STRING8(const STRING *p_srcString);
public:
	char *GetPtr8();
	inline operator std::string() {
//		return std::string (GetPtr8()); // std::string
		return GetPtr8(); // 
	}
protected:
private:
	CBfc_ReferencedAllocation	m_Representation8;
};


BFC_CLASS STRINGEX : public STRING
{
public:
	double GetAsDouble() const;
	UINT GetAsUINT() const;
};

//
BFC_CLASS StringBuffer : public STRING
{
public:
	StringBuffer();
	StringBuffer(const STRING &cs);

	virtual void Empty();
	void DecrementCharacterPtr (characterPtr &ptr); // Assumes ptr is within the buffer!
//	inline characterPtr operator *();
	inline operator characterPtr() const {
		return GetPtr();
	}
	inline operator characterPtr() {
		characterPtr szBufPtr = characterPtr(m_buffer.GetPtr());
		return szBufPtr;
	}
#ifndef _UNICODE_8
	inline operator characterPtrA() const {
		return (characterPtrA)(character*)GetPtr();
	}
#endif

private:
// 	int			m_i_index;	// byte at which next character starts
// 	characterPtr	m_szBufPtr;
};


} // namespace CBfc

#endif   // ndef _BCSTRING_H
