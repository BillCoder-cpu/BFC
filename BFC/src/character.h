//*/
/*
					character.h : 
	
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

//
//		character.h
//
//    type Ascii and Word
//

#ifndef _character_h_INCLUDED
#define _character_h_INCLUDED

extern void copy_memory(BYTEPTR dst, BYTEPTR src, int len);
//
//
//
BFC_CLASS characterPtrM
{
public:
	characterPtrM();
    characterPtrM(const characterPtrA);
    characterPtrM(const void *);
#ifndef _UNICODE_8
    characterPtrM(const BYTEPTR);
    characterPtrM(const character*);
#endif
    characterM *operator [](const unsigned int u_index);

	//	inline characterM &operator *();

	characterU operator *();
    inline bool operator == (characterPtrM &ptr) const
    			{
					return (m_p_pointer == ptr.GetPointer());
				}
    
    void operator = (characterPtrM &ptr);
    void operator = (characterM *ptr);
    void operator = (BYTEPTR ptr);

    void operator += (UINT inc);

    inline void operator = (void *ptr) {
	    m_p_pointer = (characterPtrA)ptr;
    }

    void operator delete (void *ptr);

/*
	inline operator char *() const {
    	return m_p_pointer;
        }
	inline operator BYTEPTR() const {
		return (BYTEPTR)m_p_pointer;
		}

	inline operator characterPtrA() const {
		return (characterPtrA)(character*)this;
		}
*/

	inline operator char*() const {
		return (char*)m_p_pointer;
		}
#ifndef _UNICODE_8
	inline operator character*() const {
		return (character*)m_p_pointer;
		}
#endif

    inline bool operator >= (characterPtrM &ptr) {
            return (m_p_pointer >= ptr.GetPointer ());
    }
    inline bool operator <= (characterPtrM &ptr) {
        return (m_p_pointer <= ptr.GetPointer ());
    }
    inline bool operator > (characterPtrM &ptr) {
        return (m_p_pointer > ptr.GetPointer ());
    }
    inline bool operator < (characterPtrM &ptr) {
        return (m_p_pointer < ptr.GetPointer ());
    }

   	characterPtrM &operator ++();          // Prefix++
	const characterPtrM operator ++(int);  // Postfix++
//	inline characterPtrM &operator --();

	UINT GetNextCharacterLength () const;

    int  store (characterM w);
    int  stav (characterM w);
    inline characterPtrA &GetPointer () {
    	return m_p_pointer;
        }
    inline const characterA * GetPointer () const {
    	return m_p_pointer;
        }
		
	long ReadInteger();
	static	bool 	InsertIntoString(characterPtrM &lpsz, characterU c); 
public:
	static bool isDoubleByteCharacter (characterA b);
    static bool isDoubleByteCharacter (characterU w);
private:
	characterPtrA	m_p_pointer;		// this is it.
};



/////////////////////////////////
// static class
BFC_CLASS SBFC_Character
{
public:
//  STATICBYTES
// 
	static bool			isWhiteSpace (const character c);
	static bool			isAlphaNumeric (const character c);
	static bool 			IsDigit(const character c);

	static unsigned int StringLength(const character *s);
	static unsigned int StringByteLength (const const_characterPtr ptr);

	static double		StringToDouble(const const_characterPtr ptr);
	static long			StringToInteger(const const_characterPtr ptr);
	static void			DecrementCharacterPtr (characterPtr &ptr, characterPtr ptrBase);
    static void			StringCopy (characterPtr dst, const_characterPtr src);
	static void			StringCopyNoZero (characterPtr dst, const_characterPtr src);
    static bool			StringCompare (const_characterPtr dst, const_characterPtr src);
    static bool			StringNCompare (const_characterPtr dst, const_characterPtr src, int length);
	static bool			StringCompareNoCase (const_characterPtr dst, const_characterPtr src);
	
	static int			BytesPerCharacter(UINT c);
    static character	UpperCase (const character c);
//	static character 	toupper(const character c);
	
	static UINT UTF16toUF8_CountBytes(const character* charp_source);
	static UINT UTF16toUF8 (const character *charp_source, char *cp_dest);
	static UINT UTF8toUF16 (const char *cp_source, character *charp_dest);

	static void Block_UTF8toCharacter (char *cp_Source, character *charp_dest,UINT u_CharsInBlock);

};

#define		STATICBYTES(x)		(   characterPtr(BYTEPTR(_TXT(x)))   )

#endif // ifndef _character_h_INCLUDED








