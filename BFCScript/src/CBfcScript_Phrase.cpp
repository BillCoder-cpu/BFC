//*/
/*
					CBfcScript_Phrase.cpp : 
	
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

#include <BFC/BFCScript.h>

using namespace CBfc;

namespace CBfcScript
{

static STRING csDefaultDeliminators(" =(*/-+\t\n\r");

/*
bool Phrase::IsDefaultDeliminator(const character c) const
{
	return (!c || SBFC_Character::isWhiteSpace(*m_szBufPtr) || c=='=' || c=='(');
}
*/

Phrase::Phrase()
	: m_csDeliminators(csDefaultDeliminators)
{
	Reset();
}

Phrase::Phrase(const CBfc::STRING &cs)
	: PhraseDerivedFrom(cs)
		,m_csDeliminators(csDefaultDeliminators)
{
	Reset();
}

Phrase::Phrase(const Phrase &ph)
	: PhraseDerivedFrom(ph)
		,m_csDeliminators(csDefaultDeliminators)
{
	Reset();
	m_iCurrentIndex = ph.GetIndex();
	m_szBufPtr += m_iCurrentIndex;
}

void Phrase::Reset()
{
	 m_szBufPtr=GetPtr();
	 m_iCurrentIndex = 0;
}

OVERRIDE void Phrase::Empty ()
{
	PhraseDerivedFrom::Empty();		// mamma
	Reset();
}

void Phrase::Set (const CBfc::STRING &cs)
{
	*this = cs;
	Reset();
}

void Phrase::SkipWhiteSpace ()
{
	while (SBFC_Character::isWhiteSpace(*m_szBufPtr))
		Phrase::Increment_BufPtr();	// Skip initial spaces
	m_bEOL = (!*m_szBufPtr);	// Are we at the End Of Line?
}


OVERRIDE void Phrase::Changed()
{
	 m_szBufPtr=GetPtr();
	 m_szBufPtr += m_iCurrentIndex;
	 m_bEOL = (!*m_szBufPtr);	// Are we at the End Of Line?
}

STRING	Phrase::GetDefaultDeliminators()
{
	return csDefaultDeliminators;
}

void Phrase::SetDeliminators (const CBfc_String &csDeliminators)
{
	m_csDeliminators = csDeliminators;
}

STRING Phrase::Remainder() const
{
	return STRING(m_szBufPtr);
}

bool Phrase::ReadScriptWord (CBfc_Str &s)
{
	return ReadScriptWord(s,m_csDeliminators);
}

bool Phrase::ReadScriptWord (CBfc_Str &s, const CBfc_String &csDeliminators)
{
	bool bRval = ReadScriptWordInternal (&s, csDeliminators);
	return bRval;
}

bool Phrase::ReadScriptWord (CBfc_Str &s, const int cDeliminator)
{
	character	clist[ ]= { cDeliminator, 0 };
	const CBfc_String csDeliminators(clist);

	return ReadScriptWordInternal(&s, csDeliminators);
}


bool Phrase::ReadAheadScriptWord (CBfc_Str &s)
{
	return ReadAheadScriptWord(s,m_csDeliminators);
}

bool Phrase::ReadAheadScriptWord (CBfc_Str &s, const CBfc_String &csDeliminators)
{
	bool bRval = ReadScriptWordInternal (&s, csDeliminators,true);
	return bRval;
}

bool Phrase::SkipScriptWord()						// skip over the next word
{
	return SkipScriptWord(m_csDeliminators);
}

bool Phrase::SkipScriptWord(const CBfc_String &csDeliminators)	// skip over the next word
{
	return ReadScriptWordInternal (NULL, csDeliminators, false);
}

bool Phrase::SkipScriptWord(const int cDeliminator)	// skip over the next word
{
	character	clist[ ]= { cDeliminator, 0 };
	const CBfc_String csDeliminators(clist);
	return SkipScriptWord (csDeliminators);
}

bool Phrase::SkipScriptCharacter()
{
	m_bEOL = (!m_szBufPtr || !*m_szBufPtr);	// Are we at the End Of Line?
	if (m_bEOL)
		return false;
	Phrase::Increment_BufPtr();
	SkipWhiteSpace();
	return true;
}

void Phrase::Increment_BufPtr()
{
	m_szBufPtr++;
	m_iCurrentIndex++;
}

bool Phrase::ReadAheadScriptCharacter (character &c)
{
	m_bEOL = (!m_szBufPtr || !*m_szBufPtr);	// Are we at the End Of Line?
	if (m_bEOL) {
		c = 0;
		return false;
	}
	c = *m_szBufPtr;
	return true;
}

bool Phrase::ReadAheadScriptWord (CBfc_Str &s, const int cDeliminator)
{
	character	clist[ ]= { cDeliminator, 0 };
	const CBfc_String csDeliminators(clist);

	return ReadScriptWordInternal (&s,csDeliminators,true);
}


/////////////////////////////
// Skips past the deliminators
bool Phrase::ReadScriptWordInternal (CBfc_String *p_sOut, const CBfc_String &csDeliminators, const bool bReadAhead)
{
	if (!m_szBufPtr || !*m_szBufPtr)
	{
		m_bEOL=true;
		if (p_sOut)	p_sOut->Empty();
		return false;
	}
	if (csDeliminators.Find (' ') >= 0)	SkipWhiteSpace();		// Added this on a whim after having to skip space after reading argumentlist!
	
	// Find the beginning and the ending of the Word,
	const characterPtr 	szWordStart = m_szBufPtr;
	const int			iWordStart = m_iCurrentIndex;
	
	const bool bOnlyLetters = csDeliminators.IsEmpty();
	if (bOnlyLetters)
		SkipToNonLetter();
	else
	{
		if (!NextIsDeliminator(csDeliminators))
			SkipToDeliminator(csDeliminators);
//		else
//			SkipDeliminators(csDeliminators);
	}
	m_DelimTriggerChar = *m_szBufPtr;

	bool bRval = true;
	if (p_sOut)				// Load up the output buffer
	{
		const characterPtr szWordEnd = m_szBufPtr;
		BYTEPTR bpBufStart=(BYTEPTR)(character*)szWordStart;
		unsigned long	u_stringByteLength = (BYTEPTR)(character*)szWordEnd - bpBufStart;
// 		if (u_stringByteLength >= uMaxBufLen)	u_stringByteLength = uMaxBufLen;

		if (u_stringByteLength)
			p_sOut->SetEqual (szWordStart, u_stringByteLength);
		else
		{
			p_sOut->Empty();
			bRval = false;
		}
	}
	if (bReadAhead)
	{
		m_szBufPtr = szWordStart;
		m_iCurrentIndex = iWordStart;
		m_bEOL = false;
	} else
		SkipWhiteSpace();	// sets m_bEOL
	return bRval;
}


bool Phrase::ReadScriptLetters (CBfc_Str &s)
{
	const STRING	csDeliminators;	// use empty string to trigger ascii letters reaction!
	bool bRval = ReadScriptWordInternal (&s, csDeliminators);
	return bRval;
}

bool isletter (const character c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c=='_' || (c >= '0' && c <= '9');
}

// also skips numbers!!!!!!
// returns true if deliminator hit before the end of the line
//
void Phrase::SkipToNonLetter()
{
	register character c = *m_szBufPtr;
	if ( isletter(c) )
	{
		while (1)
		{
			c = *m_szBufPtr;
			if ( isletter(c) )
				Phrase::Increment_BufPtr();
			else
				break;
		}
	} else
	{
		while (1)
		{
			c = *m_szBufPtr;
			if ( !c || isletter(c) )
				break;
			else
				Phrase::Increment_BufPtr();
		}
	}
	m_bEOL = (!*m_szBufPtr);	// Are we at the End Of Line?
}

bool Phrase::NextIsDeliminator (const CBfc_String &csDeliminators) const
{
	const character c=*m_szBufPtr;
	if (!c)
		return true;
	return ( csDeliminators.Find(c) != -1 );
}

// returns true if deliminator hit before the end of the line
void Phrase::SkipToDeliminator(const CBfc_String &csDeliminators)
{
	while (!NextIsDeliminator(csDeliminators))
		Phrase::Increment_BufPtr();
	m_bEOL = (!*m_szBufPtr);	// Are we at the End Of Line?
}

bool Phrase::SkipDeliminator(const character cDelim)
{
	const character c=*m_szBufPtr;
	if (c && c == cDelim)
	{
		Phrase::Increment_BufPtr();
		m_bEOL = (!*m_szBufPtr);	// Are we at the End Of Line?
		return true;
	}
	return false;	
}

// returns false at end of buffer, true if more characters
void Phrase::SkipDeliminators(const CBfc_String &csDeliminators)
{
	character c;
	while(1)
	{
		c=*m_szBufPtr;
		if (!c) {
			m_bEOL = true;
			return;
		}
		if (!SBFC_Character::isWhiteSpace(c) && csDeliminators.Find(c) == -1)
		{
			m_bEOL = false;
			return;
		}
		Phrase::Increment_BufPtr();// skip the delim we found
	}
}


// Interpret a character representation, such as ^Q, ALT_F4, Ctrl_f, Ctrl_Alt_Del, ESC, etc...
character Phrase::InterpretCharacter(const CBfc::STRING &csCharRep) const
{
	if (csCharRep.GetLength()==1)
		return csCharRep[0];
	STRING	cs(csCharRep);
	cs.ToUpperCase();
	switch (cs[0])
	{
		case '^':
			return cs[1]-'A'+1;
		case 'A':
			break;
		case 'C':
			break;
	}
	return 0;
}


}


