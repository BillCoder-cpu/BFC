//*/
/*
					CBfcScript_Phrase.h : 
	
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


namespace CBfcScript
{

#define PhraseDerivedFrom CBfc::StringBuffer
//#define PhraseDerivedFrom CBfc::STRING

BFC_SCRIPT_CLASS Phrase : public PhraseDerivedFrom
{
public:
	Phrase();
	Phrase(const CBfc::STRING &cs);
	Phrase(const Phrase &ph);
	
	virtual void Empty();
	
	void	Reset();		// Start at the beginning of the phrase.

	static CBfc::STRING	GetDefaultDeliminators();
	void SetDeliminators (const CBfc_String &csDeliminators);
			
	void Set (const CBfc::STRING &cs);

	CBfc::STRING	Remainder() const;
	bool	ReadScriptWord (CBfc_Str &s);
	bool	ReadScriptWord (CBfc_Str &s, const CBfc_String &csDeliminators);
	bool	ReadScriptWord (CBfc_Str &s, const int cDeliminator);
	bool	ReadScriptLetters (CBfc_Str &s);
	
	bool	ReadAheadScriptWord (CBfc_Str &s);
	bool	ReadAheadScriptWord (CBfc_Str &s, const CBfc_String &csDeliminators);
	bool	ReadAheadScriptWord (CBfc_Str &s, const int cDeliminator);
	
	bool	SkipScriptWord();						// skip over the next word
	bool	SkipScriptWord(const CBfc_String &csDeliminators);	// skip over the next word
	bool	SkipScriptWord(const int cDeliminator);	// skip over the next word
	
	bool	SkipScriptCharacter();						// skip over the next word
	bool	ReadAheadScriptCharacter (character &c);

	bool	IsEOL() const { return m_bEOL; }

	character	InterpretCharacter(const CBfc::STRING &csCharRep) const;
	
	void	SkipToNonLetter();
	void	SkipToDeliminator(const CBfc_String &csDeliminators);
	void	SkipDeliminators(const CBfc_String &csDeliminators);
	
	bool 	SkipDeliminator(const character cDelim);
	void	SkipWhiteSpace ();

	int		GetIndex() const { return m_iCurrentIndex; } // returns current offset within buffer
protected:
	
	bool NextIsDeliminator (const CBfc_String &csDeliminators) const;
	virtual void Increment_BufPtr();
	virtual bool ReadScriptWordInternal (CBfc_String *p_sOut, const CBfc_String &csDeliminators, const bool bReadAhead=false);
	virtual 	void Changed();					// called whenever string is finished 
	
// 	bool	ReadScriptWord (characterPtr szDestBuf, const UINT uMaxBufLen, const bool bReadAhead=false);
// 	bool	ReadScriptWord (characterPtr szDestBuf, const UINT uMaxBufLen, const int cDeliminator, const bool bReadAhead=false);

// 	inline bool	IsDefaultDeliminator(const character c) const;
private:
	bool 	FinishReadingScriptWord(const characterPtr szWordStart, CBfc_String *p_sOut, const bool bReadAhead);


public:
	character		m_DelimTriggerChar;
protected:
	int				m_iCurrentIndex;
	bool			m_bEOL;			// End of Line
	characterPtr	m_szBufPtr;
	CBfc::STRING	m_csDeliminators;
};



}

