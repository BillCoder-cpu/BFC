//*/
/*
					CBfcScript.cpp : 
	
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
#ifdef	UNIX
#	include <wchar.h>
#endif

using namespace CBfc;

namespace CBfcScript
{

/*******************************************************************/

void Script::Constructor (void)
{
	Reset ();
	STRING	*p_s_cc = new STRING("%%");
	m_saMidlineCommentChars.Add (p_s_cc);
}

void Script::Reset(void)
{
	m_showErrors = m_showWarnings = true;
	newposition();
	m_bSkippingComments = true;
	m_bSkippingWhitespace = true;
	m_bSkippingLinefeeds = true;
	Phrase::Reset();
// 	m_szBufPtr = (characterPtr)NULLPTR;
	m_iWarningCount = m_iErrorCount = 0;
	m_bOkAddComments = true;
}

OVERRIDE void Script::Empty()
{
	Phrase::Empty();
	m_sCommentCache.Empty();
	newposition();
}

void Script::newposition()
{
	m_bWithinQuotes = false;
	m_bWithinEnclosedComment = false;
}

void Script :: SetMidlineCommentIndicator (const STRING &csCommentChars)
{
	STRING	*p_s_cc = new STRING(csCommentChars);	  // midline comment indicator for C language
			
	m_saMidlineCommentChars.Empty();
	m_saMidlineCommentChars.Add (p_s_cc);
}

void Script :: SetMidlineCommentIndicators (const CBfc::StringArray &saCommentChars)
{
//	m_saMidlineCommentChars.Empty();
//	saCommentChars;
}

bool Script::SkipScriptLine ()			// Does Not Filter script comments
{
	BufferNextLine ();
	if (m_szBufPtr && *m_szBufPtr)
	{
		*m_szBufPtr=0;
		return true;
	}
	return false;
}

bool Script::ReadScriptLine_skipcomments (CBfc_Str &s)
{
	if (BufferNextLine())
	{
		s = m_szBufPtr;
		*m_szBufPtr = 0;
		return true;
	}
	return false;
}

bool Script::ReadAheadScript_Line(CBfc_Str &s)
{
	s.Empty ();
	if (BufferNextLine())
	{
		character c;
		characterPtr savePtr = m_szBufPtr;
		int saveIndex = m_iCurrentIndex;
		while (!AtEOL())
		{
			ReadAheadScript_Character(c);
			Phrase::Increment_BufPtr();
			s += c;
		}
		m_iCurrentIndex  = saveIndex;
		m_szBufPtr = savePtr;
		return true;
	}
	return false;	
}

bool Script::SkipScript_Line()
{
	CBfc_Str t;
	return ReadScriptLine (t);
}

bool Script::ReadScriptLine (CBfc_Str &s)		// Filters script comments
{
	s.Empty ();
	if (BufferNextLine())
	{
		character c;
		while (!AtEOL())
		{
			ReadScript_Character(c);
			s += c;
		}
		return true;
	}
	return false;
}


OVERRIDE bool Script::BufferNextLine ()
{
	if (m_szBufPtr && *m_szBufPtr)
		return true;
	
	Phrase::Empty();

	character l;
	do
	{
		if (!BufferScript())
			return false;
		if (WithinComment())		// Don't pay attention to \ at eol if within comment.
			break;
		l = Right();
		if (l == '\\')
			TrimRight(1);
	} while (l == '\\');

// 	if (!m_bSkippingLinefeeds)
// 		*this += '\n';
	Phrase::Reset();
	return true;
}

// takes out comments, etc.
bool Script::BufferScript()
{
	STRING	s;
	do 
	{
		do 
		{
			if (!ReadLine (s)) 
				return false;
			
			m_iMidlineCommentOffset = LocateMidlineComment(s);
			if (m_bSkippingComments)
				ZapMidlineComments (s);
			if (m_bSkippingWhitespace)
				s.TrimLeft();
			if (m_iMidlineCommentOffset >= 0)
				m_iMidlineCommentOffset += STRING::GetLength();
		} while (s.IsEmpty());
		*this += s;
		Phrase::Reset();
		CheckBufferForEnclosedComment();
	} while (!*m_szBufPtr);
	return true;
}

bool Script::AtQuote()
{
	if (*m_szBufPtr!='"')
		return false;

	if (!m_iCurrentIndex)
		return true;
	SBFC_Character :: DecrementCharacterPtr (m_szBufPtr, characterPtr(m_buffer.GetPtr()));
//	DecrementCharacterPtr (m_szBufPtr);		// can use if we are stringbuffer
	return (*m_szBufPtr++ != '\\');
}

//
// returns false if no comment has built up, else clears cache
//
bool Script::GetCommentCache(CBfc_Str &comment)
{
	if (m_sCommentCache.IsEmpty())
		return false;
	comment = m_sCommentCache;
	m_sCommentCache.Empty ();
	return true;
}

bool	Script::WithinComment()
{
	if (m_bSkippingComments) return false;
	if (m_bWithinEnclosedComment) return true;
	return AfterMidlineComment();
}

bool	Script::AfterMidlineComment()
{
	if (m_iMidlineCommentOffset<0) return false;
	return (m_iCurrentIndex >= m_iMidlineCommentOffset);
}

// returns previous value
bool	Script::SetSkipComments(const bool bOn)
{
	const bool bRval = m_bSkippingComments;
	m_bSkippingComments = bOn;
	return bRval;
}

// returns previous value
bool	Script::SetSkipWhitespace (const bool bOn)
{
	const bool bRval = m_bSkippingWhitespace;
	m_bSkippingWhitespace = bOn;
	return bRval;
}

// returns previous value
bool	Script::SetSkipLinefeeds (const bool bOn)
{
	const bool bRval = m_bSkippingLinefeeds;
	m_bSkippingLinefeeds = bOn;
	if (!bOn && bRval && m_szBufPtr && *m_szBufPtr)		// catch any current line too!
		*this += '\n';
	return bRval;
}


// note how this is only called when m_bSkippingComments is true.
// other-wise we would not be adding to the comment cache if not skipping comments.
// private function - dependent on LocateMidlineComment(), etc.

void Script::ZapMidlineComments (STRING &s)
{						// cut the buffer short!
	if (m_iMidlineCommentOffset >= 0)
	{
		STRING sComment(s);
		sComment.TrimLeft (m_iMidlineCommentOffset);
		if (m_bOkAddComments)
		{
			m_sCommentCache += sComment;
			m_sCommentCache += '\n';
		}
		s = s.Left(m_iMidlineCommentOffset);
	}
}

int Script::LocateMidlineComment (const STRING &s)
{
	int	rval_offset=0;
	if (m_saMidlineCommentChars.GetCount())
	{
		STRING	*p_s = m_saMidlineCommentChars[0];
		const UINT u_len = p_s->GetLength();
		bool	commentPresent;
	
		if (u_len)
		{
			characterPtr	tcp = s.GetPtr();
			while (*tcp)
			{
				commentPresent = true;
				for (UINT u=0; u < u_len; u++)
					if (tcp[u] != (*m_saMidlineCommentChars[0])[u])
					{
						commentPresent = false;
						break;
					}
				if ( commentPresent )
					return rval_offset;
				tcp++;
				rval_offset++;
			}
		}
	}
	return -1;
}


// 
//	if szDestBuf is NULL, just throw away the data.
//
bool Script::ReadScriptWordInternal (CBfc_String *p_sOut, const CBfc_String &csDeliminators, const bool bReadAhead)
{
	if (!BufferNextLine())
		return false;
	return Phrase::ReadScriptWordInternal(p_sOut,csDeliminators,bReadAhead);
}

// Read between two quotes.
bool Script::ReadScriptFilename(CBfc::Filename& fn)
{
	character		c;
	if (ReadAheadScript_Character(c))
	{
		if (c == '"')
			return ReadScript_BetweenDeliminators(false, fn, '"', '"');
		return ReadScriptWord(fn);
	}
	return false;
}

// Read between two quotes.
bool Script::ReadScriptString (CBfc::STRING &s)
{
	return ReadScript_BetweenDeliminators (false, s, '"', '"');
}

// Read int one phrase from a NameList.
//  Comma deliminated
bool Script::ReadScriptPhrase (CBfc_Str &s)
{
	bool r;
	r = ReadScriptWord (s, ',');
	return r;
}

/*
	took out converting to strings only to save cpu cycles with strings - need it?
// return false on EOF.
bool Script::ReadScriptPhrase (characterPtr szDestBuf, const UINT uMaxBufLen)
{
	if (ReadScriptWord (szDestBuf, uMaxBufLen, ','))
	{
		SkipDeliminator(',');			// skip final delim
		return true;
	}
	return false;
}
*/

// Skips the final deliminator
bool Script::ReadScript_BetweenDeliminators (const bool bNest, CBfc_Str &s, const character cBegin_deliminator, const character cEnd_deliminator)
{
	if (BufferNextLine())
	{
		if (*m_szBufPtr == cBegin_deliminator)
		{
			Skip_Bufferchar();
			if (bNest)
			{
				int		nest = 0;
				STRING	delim;
				delim += cBegin_deliminator;
				delim += cEnd_deliminator;
				while (ReadScriptWord (s,delim))
				{
					if (SkipDeliminator(cEnd_deliminator))
						if (nest--==0) {
							if (m_bSkippingWhitespace)
								SkipWhiteSpace();
							return true;
						}
					SkipDeliminator (cBegin_deliminator);
					nest++;
				}
				return false;
			} else
			{
				bool bRval = ReadScriptWord (s, (int)cEnd_deliminator);
				SkipDeliminator(cEnd_deliminator);
				if (m_bSkippingWhitespace)
					SkipWhiteSpace();
				return bRval;
			}
		}
	}
	return false;
}


bool Script::SkipScript_Character()
{
	character c;
	return ReadScript_Character(c);
}

bool Script::ReadScript_Character(character &c)
{
	if (ReadAheadScript_Character(c))
	{
		if (AtEOL())
			return BufferNextLine();
		Skip_Bufferchar();
		if (m_bSkippingWhitespace)		// added these 2 lines 1/18/11 - may break something!
			SkipWhiteSpace();			//  to fix readline when tabs are at end of line
		return true;
	}
	return false;
}

bool Script::ReadAheadScript_Character(character &c)
{
	if (!m_bSkippingWhitespace && AtEOL())
	{
		c = '\n';
		return true;
	}
	do {
		if (!BufferNextLine())
			return false;
		
		if (m_bSkippingWhitespace)
			SkipWhiteSpace();
		c = *m_szBufPtr;
	} while (!c);
	return true;
}

bool Script::AtEOL()
{
	return (m_szBufPtr && !*m_szBufPtr);
}


// checks for Enclosed comments within a comment and sets a flag if we are within a comment
void Script::Skip_Bufferchar()
{
	Phrase::Increment_BufPtr();
	CheckBufferForEnclosedComment();
}

// 01/11 For this function, don't call Script's version of the Increment_BufPtr, it will catch you again!
void Script::CheckBufferForEnclosedComment()
{
	if (!AfterMidlineComment())
	{
		if (!m_bWithinQuotes)
		{
			if (*m_szBufPtr=='/')
			{
				if (!m_bWithinEnclosedComment && m_szBufPtr[1]=='*')
				{
					m_bWithinEnclosedComment = true;
					if (m_bSkippingComments)
					{
						if (m_bOkAddComments)
						{
							m_sCommentCache += *m_szBufPtr;
							m_sCommentCache += m_szBufPtr[1];
						}
						Phrase::Increment_BufPtr();
						Phrase::Increment_BufPtr();
					}
				}
			} else if (AtQuote())
			{
				m_bWithinQuotes = true;
			}
				/// Doesn't do this:
					/// turn off comments even after midline comment!!!!
					/// we don't support that crap
			if (m_bWithinEnclosedComment && *m_szBufPtr=='/')
			{
				if (m_iCurrentIndex && m_szBufPtr[-1]=='*')
					m_bWithinEnclosedComment = false;
			}
		} else if (AtQuote())
				m_bWithinQuotes = false;
			
		if (m_bWithinEnclosedComment && m_bSkippingComments)
			JumpPastEnclosedComment();
	}
}

// 1/11 For this function, don't call Script's version of the Increment_BufPtr, it will catch you again!
// SO, it only applies to the Phrase buffer, it does not guarantee to get you past the comment, just to eol or past comment.
void Script::JumpPastEnclosedComment()
{
	while (*m_szBufPtr)
	{
		if (*m_szBufPtr == '*' && m_szBufPtr[1] == '/')
		{
			if (m_bOkAddComments)
				m_sCommentCache += *m_szBufPtr;
			
			Phrase::Increment_BufPtr();
			if (m_bOkAddComments)
				m_sCommentCache += *m_szBufPtr;
			Phrase::Increment_BufPtr();
			m_bWithinEnclosedComment = false;
			break;
		}
		if (m_bOkAddComments)
			m_sCommentCache += *m_szBufPtr;
		Phrase::Increment_BufPtr();
	}
	if (m_bOkAddComments)
		m_sCommentCache += '\n';
	if (!*m_szBufPtr) // 3/9/09 added if unknown adverse effect??
		Phrase::Empty();
}

void Script::RemoveEnclosedComments(CBfc_Str &s)
{
	STRING new_s;
	int index = 0;
	bool in_quotes = false;

	while (index < s.GetLength())
	{
		if (in_quotes)
		{
			if (s[index] == '"')
				in_quotes = false;
		} else
		{
			if (s[index] == '"')
				in_quotes = true;
			else
				if (s[index] == '/' && s[index+1] == '*')
				{
					index+= 2;
					while (index < s.GetLength()-1 && (s[index] != '*' || s[index+1] != '/'))
						index++;
					continue;
				}
		}
		new_s += s[index];
		index++;
	}
	s = new_s;
}

bool Script::ReadScript_Number(CBfc::Value &v)
{
	float x;
	STRING  cs;
	if (!ReadScriptWord(cs)) return false;
	return v.SetFromString (cs);
}

//
// Reads the contents of parenthesis pair into string
//
bool Script::ReadScript_ArgumentList (CBfc_Str &s)
{
	const character Begin_deliminator(*STATICBYTES("("));
	const character End_deliminator(*STATICBYTES(")"));
	return ReadScript_BetweenDeliminators (true, s, Begin_deliminator, End_deliminator);
}

bool Script::ReadScript_ArgumentList_2dPair (ValuePairU &pair)
{
	ValuePair vp;
	if (ReadScript_ArgumentList_2dPair (vp)) {
		pair.Set ((UINT)vp.GetX(), (UINT)vp.GetY());
		return true;
	}
	return false;
}

//
//    Format: "(x,y)"
bool Script::ReadScript_ArgumentList_2dPair (ValuePair &pair)
{
	STRING  cs;
	if (!ReadScript_ArgumentList (cs))	// Reads contents of parenthesis into string
		return false;

	float x,y;
//	const char * cp = (const char *)(character*)(cs.GetPtr()); // .GetPointer();
#ifdef _UNICODE_8
	sscanf (cs.GetPtr(), _TXT("%f,%f"), &x, &y);
#else
	swscanf (cs.GetPtr(), _TXT("%f,%f"), &x, &y);
#endif
	if(cs.Find(',')==-1) y = 1;				// If only one value, second value is assumed to be 1
	return pair.Set (CBfc_Value (x),CBfc_Value(y));
}

bool Script::ReadScript_ArgumentList_3dTriplet (CBfc::ValueTriplet &vector)
{
	STRING  cs;
	if (!ReadScript_ArgumentList (cs)) return false;	// Reads contents of parenthesis into string
	float x,y,z;
#ifdef _UNICODE_8
	sscanf (cs.GetPtr(), _TXT("%f,%f,%f"), &x, &y, &z);
#else
	swscanf (cs.GetPtr(), _TXT("%f,%f,%f"), &x, &y, &z);
#endif
	if(cs.Find(',')==-1) y = 1;				// If only one value, second value is assumed to be 1
	return vector.Set (CBfc_Value (x),CBfc_Value(y),CBfc_Value(z));
}

////////////////////////////  Internal functions ////////////////////////////////////
// return false on EOF.
bool Script::MatchScriptKey (characterPtr WordList[], int &iKey, const UINT step)
{
	STRING		csNextWord;

	if (!ReadAheadScriptWord(csNextWord))
		return false;
	iKey = MatchKey (WordList, csNextWord, step);
	if (iKey != BFCSCRIPT_KEY_NONE)
		SkipScriptWord();
	return true;
}

int Script::MatchKey (characterPtr WordList[], STRING &csWord, const UINT step)
{
	int iKey = 0;
	while (WordList[iKey*step])
	{
		if (csWord==STRING(WordList[iKey*step]))
			return iKey;		// Match found, skip the next script word to pass it by.
		iKey++;
	}
	// No matches were found,
	return BFCSCRIPT_KEY_NONE;
}

void Script::ShowErrors(const bool bErrors, const bool bWarnings)
{
	m_showErrors = bErrors;
	m_showWarnings = bWarnings;
}

void Script::SyntaxError (SYNTAX_ERROR_TYPE type, const char *errstr)
{
	STRING	s(errstr);
	SyntaxError (type, s.GetPtr());
}
		
void Script::SyntaxError (SYNTAX_ERROR_TYPE type, const characterPtr errstr)
{
	bool	bWarning = false, bError = true;
	bool	bSyntax = false, bConstruction = false;
	STRING	sOut, sAdd;

	switch (type)
	{
		case SYNTAX_WARNING:
			bWarning = true;
			bSyntax = true;
			break;
		case SYNTAX_ERROR:
			bError = true;
			bSyntax = true;
			break;
		case CONSTRUCTION_ERROR:
			bError = true;
			bConstruction = true;
			break;
	}
	if (bSyntax) {
		sOut = "SYNTAX ";
	} else if (bConstruction) {
		sOut = "CONSTRUCTION ";
	}
	if (bWarning)
	{
		if (!m_showWarnings)
			return;
		sAdd = "Warning";
		m_iWarningCount++;
	} else if (bError)
	{
		if (!m_showErrors)
			return;
// 		sAdd.Format(_TXT("ERROR #%d"), ++m_iErrorCount);
		sAdd = "ERROR";
	}
	sOut += sAdd;
	
	const int column = GetIndex();
	sAdd.Format (_TXT(" @line #%d col #%d "), m_uLineNumber, column);
	sOut += sAdd;

	Filename	fn;
	
	if (GetFilename(fn))
	{
		sOut += '(';
		sOut += fn;
		sOut += ')';
// 		Emit (fn.GetNameExtension());
	}
	sOut += ":\n";
	
	Emit ("\n      ");
	Emit (sOut);
	Emit (_TXT("           "));
	Emit (errstr);
	Emit (_TXT(".\n"));
}


void Script::Emit(const STRING &txt)
{
// 	fwprintf (stderr, txt.GetPtr());
#ifdef _UNICODE_8
	printf (txt.GetPtr());
#else
	wprintf (txt.GetPtr());
#endif
}

void Script::AppendScript(Script &src)
{
	STRING	s;
	const bool bSave_wht = src.SetSkipWhitespace(false);
	const bool bSave_lf = src.SetSkipLinefeeds(false);
	while (src.ReadScriptLine_skipcomments (s))
		Write(s);
	src.SetSkipLinefeeds(bSave_lf);
	src.SetSkipWhitespace(bSave_wht);
}


}


