//*/
/*
					CBfcScript.h : 
	
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
/*

*/

#define	BFCSCRIPT_KEY_NONE	-1		// For MatchScriptKey

namespace CBfcScript
{

typedef enum
{
	SYNTAX_WARNING,
	SYNTAX_ERROR,
	CONSTRUCTION_ERROR,
} SYNTAX_ERROR_TYPE;


BFC_SCRIPT_CLASS  Script : public Phrase, public Script_Text
{
public:
	Script ()
	{
		Constructor ();
	}
	
	Script (CBfc::Stream &bfc_stream)
		: Script_Text (bfc_stream)
	{
		Constructor ();
	}

	Script (const CBfc::Filename &bfc_filename, const bool b_ReadOnly=true)
    	: Script_Text (bfc_filename, b_ReadOnly)
    {
		Constructor ();
	}
	virtual ~Script() {}
private:
	void Constructor (void);
public:
	virtual void Empty();		// from Phrase
	virtual void Reset();

	void	SyntaxError (SYNTAX_ERROR_TYPE type, const char *errstr);
	void	SyntaxError (SYNTAX_ERROR_TYPE, const characterPtr errstr);	//
	
	virtual bool	ReadScriptLine (CBfc_Str &s);				// Filters script comments
	virtual bool	ReadScriptLine_skipcomments (CBfc_Str &s);
	virtual bool	SkipScriptLine ();							// Does not Filter script comments
//	bool	ReadScriptLine (characterPtr szDestBuf, const UINT uMaxBufLen);	// Filters script comments

	bool	ReadScriptString (CBfc::STRING &s);
	bool	ReadScriptPhrase (CBfc_Str &s);
	bool	ReadScriptFilename(CBfc::Filename& fn);
		// 	bool	ReadScriptPhrase (characterPtr szDestBuf, const UINT uMaxBufLen);
	bool	MatchScriptKey (characterPtr WordList[], int &iKey, const UINT step=1);
	static int		MatchKey (characterPtr WordList[], STRING &csWord, const UINT step);

	void	SetMidlineCommentIndicator (const CBfc::STRING &csCommentChars);
	void	SetMidlineCommentIndicators (const CBfc::StringArray &saCommentChars);
//	void	SetEnclosedCommentIndicators (const CBfc_StringArray &saCommentChars);
	void	ShowErrors(const bool bErrors, const bool bWarnings);
protected:
	bool			m_bOkAddComments;
	CBfc::StringArray		m_saMidlineCommentChars;
//	CBfc_StringArray		m_saEnclosedCommentChars;
public:
	bool	ReadScript_Number(CBfc::Value &v);
	bool	ReadScript_ArgumentList (CBfc_Str &s);
	bool	ReadScript_ArgumentList_2dPair (CBfc::ValuePair &pair);
	bool	ReadScript_ArgumentList_2dPair (CBfc::ValuePairU &pair);
	bool	ReadScript_ArgumentList_3dTriplet (CBfc::ValueTriplet &vector);
	bool    ReadScript_BetweenDeliminators (const bool bNest, CBfc_Str &s, const character Begin_deliminator, const character End_deliminator);

	bool	ReadAheadScript_Line(CBfc_Str &s);
	bool	SkipScript_Line();
	bool	ReadAheadScript_Character(character &c);
	bool	ReadScript_Character(character &c);
	bool	SkipScript_Character();
	void	AppendScript(Script &src);
public:
	bool	WithinComment();
	bool	SetSkipComments(const bool bOn);
	bool	GetSkippingComments() const { return m_bSkippingComments; }
	bool	SetSkipWhitespace (const bool bOn);
	bool	SetSkipLinefeeds (const bool bOn);
	
	bool	GetCommentCache(CBfc_Str &comment);		// returns false if no comment has built up, else clears cache

	
		// todo - take and fill m_cs_LastComment whenever /* */ is encountered
		// later - Also do for midline comments so we don't lose them (ok for now!!!!! (not really)) 
		// also, dont forget the to implement the quotes filter flag scheme

	int	GetErrorCount() const { return m_iErrorCount; }
	int GetWarningCount() const { return m_iWarningCount; }
	
	bool AtEOL();

	virtual inline bool Rewind()
	{
		if (Script_Text::Rewind())
		{
			Empty();
			Script::Reset();
			return true;
		}
		return false;
	}
protected:
//	virtual void	Increment_BufPtr();
	void			Skip_Bufferchar();

	virtual bool	ReadScriptWordInternal (CBfc_String *p_sOut, const CBfc_String &csDeliminators, const bool bReadAhead=false);

	virtual bool	BufferScript ();
	virtual bool	BufferNextLine ();

	void			newposition();	
	void			Emit(const STRING &s);
	int 			LocateMidlineComment (const STRING &s);
	void			RemoveEnclosedComments(CBfc_Str &s);

	virtual bool SkippingLinefeeds()
	{
		return m_bSkippingLinefeeds;
	}
private:
	bool 			AtQuote();
	bool			AfterMidlineComment();
	void			ZapMidlineComments(CBfc::STRING &s);
	void 			CheckBufferForEnclosedComment();
	void 			JumpPastEnclosedComment();
	
	CBfc_String		m_sCommentCache;
	bool			m_bSkippingComments, m_bSkippingWhitespace, m_bSkippingLinefeeds;
	bool			m_bWithinEnclosedComment;
	bool			m_bWithinQuotes;
	int				m_iMidlineCommentOffset;

	int			m_iWarningCount, m_iErrorCount;

	bool		m_showErrors, m_showWarnings;
};


}


