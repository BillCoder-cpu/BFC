//*/
/*
					Script_C.cpp : 
	
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

namespace CBfcScript
{

/*
#define	- record a definition
#undef
#include - just scan for #defines,#includes and for known names into m_KnownTypenames;
#ifdef 
*/
bool Script_C::ProcessDirective()
{
	STRING	s;
	
	SkipScript_Character();
	SkipWhiteSpace();

	if (ReadScriptWord(s))
	{
		if (s=="if")
			ReadIfdefDirective(E_IFDEF_IF);
		else if (s=="ifdef")
			ReadIfdefDirective(E_IFDEF_IFDEF);
		else if (s=="ifndef")
			ReadIfdefDirective(E_IFDEF_IFNDEF);
		else if (s=="else")
			ReadIfdefDirective(E_IFDEF_ELSE);
		else if (s=="endif")
			ReadIfdefDirective(E_IFDEF_ENDIF);
		else
		{
			STRING sl;
			if (!skipping_code())
			{
				if (s=="define")
					ReadDefineDirective();
				else if (s=="undef")
					ReadUndefDirective();
				else if (s=="pragma")
					ReadScriptLine(sl);				// skip pragmas
				else if (s=="include")
				{
					SubstituteDefines();
					ScanIncludefile ();
				}
			} else
				ReadScriptLine(sl);				// skip everything if defned out
		}
		return true;
	}
	return false;
}
// only run define substitutions if not a '#'
bool Script_C::ReadAheadScript_Character_NoDefines(character &c)
{
	if (Script_Source::BufferNextLine())
	{
		c = *m_szBufPtr;
		if (c != '#')
				SubstituteDefines();
		return true;
	}
	return false;
}
				
bool Script_C::ReadBetweenBrackets(CBfc::STRING &s)
{
	bool bRval = false;
	character	c, last_c;
	int depth = 0;

	SetSkipComments(false);
	SkippingStrings(true);
	ReadAheadScript_Character(c);
	if (c != '{')
	{
		SyntaxError (SYNTAX_ERROR,_TXT("Expecting '{' Open Bracket!"));
	} else
	{
		bRval = true;
		SetSkipWhitespace(false);
		last_c = 0;
		while (1)
		{
			if (!ReadScript_Character(c))
			{
				bRval = false;
				break;
			}
			s += c;
	
			if (last_c != '\'')	// skip brackets in single quotes
			{
				if (c == '{')
					depth++;
				else if (c == '}')
				{
					if (--depth <= 0)
						break;
				}
			}
			last_c = c;
		}
		SetSkipWhitespace(true);
	}
	SkippingStrings(false);
	SetSkipComments(true);
	return bRval;
}
		
bool Script_C::LocateDefine(const STRING &tag, UINT &index)
{
	ULONG i = m_defines.StartIteration();
	C_Define	*p_def;
	while ((p_def = m_defines.GetNext(i)))
	{
		if (p_def->m_cs_defname == tag)
		{
			index = i-1;
			return true;
		}
	}
	return false;
}

bool Script_C::ReadDefineDirective()
{
	CBfc::STRING	s,sl,argl,sorg;

	if (AtEOL())
		return false;
	if (ReadScriptWord(s))
	{
		if (!AtEOL())
		{
//			SubstituteDefines();
			if (!AtEOL())
			{
				if (m_DelimTriggerChar == '(')
					ReadScript_ArgumentList(argl);
				////
				{
					Phrase ph_original(*this);
					SubstituteDefines();
					if (!AtEOL())
					{
						if (!ReadScriptLine(sl))
							return false;
						RemoveEnclosedComments(sl);		// brute force method
//						ph_original.SkipScriptWord();
//						ph_original.SkipScriptWord();
						if (m_DelimTriggerChar == '(')
							ph_original.SkipToDeliminator(")");
						ph_original.ReadScriptWord(sorg, '\n');
//						sorg = ph_original;
						RemoveEnclosedComments(sorg);
					}
				}
			}
		}

		AddDefine (s,sl,argl,sorg);
		return true;
	}
	return false;
}


// Parse a ; deliminated list of defines
void Script_C::AddDefines(const CBfc::STRING &csDefines)
{
	STRING csDef;

	Phrase ph(csDefines);
	ph.Reset();
	while (ph.ReadScriptWord(csDef,"=;"))
	{
		STRING value("1"), argl;

		if (ph.m_DelimTriggerChar == '=')
		{
			ph.SkipScriptCharacter();
			ph.ReadScriptWord(value,";");
			value.RemoveQuotes();
		}
		AddDefine (csDef, value, argl, value);
		ph.SkipDeliminator(';');
	}
}

void Script_C::AddDefine (const STRING &tag, const STRING &value, const STRING &argl, const STRING &original_value)
{
/*
#ifdef _DEBUG
	STRING debug_stop("BFC_GUI_CLASS");
	if (tag==debug_stop)
	{
		STRING	sTxt;
		sTxt.Format ("Define %s TO-BE %s", tag.GetPtr(), value.GetPtr());
		SyntaxError (SYNTAX_WARNING,sTxt.GetPtr());
	}
#endif
*/
	if (tag != value)
	{
		UINT index;
		if (!LocateDefine(tag,index))
		{
			C_Define	def(tag,value, original_value);
			
			def.SetArgumentString(argl);
			m_defines.Add(&def);
		}
	}
}

bool Script_C::ReadUndefDirective()
{
	CBfc::STRING	s,sl;
	if (ReadScriptWord(s))
	{
		UINT index;
		if (LocateDefine(s,index))
			m_defines.RemoveAt(index);
		return true;
	}
	return false;
}

// 
bool Script_C::ReadIfdefDirective(const E_C_IFDEF eif)
{
	bool bOff = skipping_code();
	bool rval = ReadIfdefDirective_internal(eif);
// 	if (bOff != skipping_code())
// 		SyntaxError (SYNTAX_WARNING, bOff ? "code on +++++++++++" : "code off ---------");
	return rval;
}


bool Script_C::ReadIfdefDirective_internal(E_C_IFDEF eif)
{
	CBfc::STRING	sl;
	
	switch (eif)
	{
		case E_IFDEF_ELSE:
			if (m_ifdef_on_depth == m_ifdef_depth)
				m_ifdef_on_depth--;
			else if (m_ifdef_on_depth == m_ifdef_depth-1)
				m_ifdef_on_depth++;
			return true;
		case E_IFDEF_ENDIF:
			if (m_ifdef_on_depth == m_ifdef_depth)
				m_ifdef_on_depth--;
			m_ifdef_depth--;
			return true;
	}
	bool		b_yes = true;

	if (AtEOL() || ReadScriptLine(sl))	// defines substitution is taking this out too early!
//	if (ReadScriptWord(s))
	{
		UINT index;
		Phrase ph(sl);
		STRING	tag;
		character c;

		if (eif == E_IFDEF_IF)
		{
			ph.ReadAheadScriptCharacter(c);
			if (c == '!')
				ph.SkipScriptCharacter();
			ph.ReadAheadScriptWord(tag);
			if (tag == "defined")
			{
				ph.SkipScriptWord();
				eif = (c == '!') ? E_IFDEF_IFNDEF : E_IFDEF_IFDEF;
			}
		}

		ph.ReadAheadScriptCharacter(c);
		if (c == '(')
				ph.SkipScriptCharacter();
		ph.ReadScriptWord(tag);
		if (c == '(')
		{
			ph.ReadAheadScriptCharacter(c);
			if (c == ')')
				ph.SkipScriptCharacter();
			else if (tag.Right() == ')')
				tag.TrimRight(1);
		}

		b_yes = LocateDefine(tag,index);
		switch (eif)
		{
			case E_IFDEF_IF:
				if (b_yes)
					sl = m_defines[index]->m_cs_substitute;
				if (sl.IsEmpty() || sl[0] == '0')
					b_yes = false;
				else
					b_yes = true;
				break;
			case E_IFDEF_IFNDEF:			// invert logic on ndef
				b_yes = !b_yes;
				break;
			case E_IFDEF_IFDEF:
				break;
		}
		if (b_yes)
		{
			if (m_ifdef_on_depth == m_ifdef_depth)
				m_ifdef_on_depth++;
		}
		m_ifdef_depth++;
		return true;
	}
	return false;
}

// here is where we can just begin to do things like:
//		replace foreach(value in array) with StartIteration, GetNext() combo macro.
//		in our own source language, like C#
// here is the simple way, next our own sources.

// uh oh, what about defines like this:
// #	define	BFC_RELEASE_ARRAY(a) { if(a) { delete[] a; a = NULL; } }
// #	define	BFC_RELEASE_PTR(p) { if(p) { delete p; p = NULL; } }
// #	define	BFC_RELEASE(x)	   { if(x) { delete x; x = NULL; } }
void Script_C::SubstituteDefines()
{
	if (GetSkippingComments())
	{
		STRING	s;
//		Phrase ph((Phrase &)*this);
		Phrase ph(*this);
	
		while (1)
		{
			int 	iWordStart = ph.GetIndex();
	
			if (!ph.ReadScriptLetters(s))	// Skip to next whole word
				break;
			
			C_Define	*p_def;
			ULONG	index = m_defines.StartIteration();
			while ((p_def = m_defines.GetNext(index)))
			{
				if (s == p_def->m_cs_defname)
				{
					if (p_def->m_cs_args.IsEmpty())		// Simple replacement?
						Replace (iWordStart, s, p_def->m_cs_substitute);
					else 
					{
						STRING	argl;
						
						ReadScript_ArgumentList(argl);
						
						const int 	iWordEnd = ph.GetIndex();
						Replace (iWordStart,iWordEnd,p_def->m_cs_substitute);
	//#define test(a,b,c,d)	 with(a) do (b) until (c);
					}
					ph = *this;
					ph.Reset();
					break;
				}
			}
		}
	}
}

void Script_C::DetectWorkingFolder()
{
	if (m_p_source->GetStreamSource()==CBfc::StreamSource::EBFC_STREAMSOURCE_FILE)
	{
		CBfc::StreamSource_File *pfilesrc = (CBfc::StreamSource_File*)m_p_source;
		CBfc::Filename fn;
		pfilesrc->GetFilename(fn);
		m_cs_pwdWorkingFrom = fn.GetPath();
		
// 		STRING sTxt;
// 		sTxt.Format(_TXT("Popped to %s"),fn.GetNameExtension().GetPtr());
// 		SyntaxError (SYNTAX_WARNING,sTxt.GetPtr());
// 		if (fn.GetNameExtension() == "fx.h")
// 			SyntaxError(SYNTAX_WARNING,_TXT("stop!"));
	}
}

// read a until next dealio
// returns deliminator in finalc
bool Script_C::ReadSourceLine (CBfc::STRING &s, character &finalc)
{
	if (ReadScriptWord (s,"{;")) {
		if (!ReadAheadScript_Character(finalc))
			return false;
		while (finalc != '{' && finalc != ';')
		{
			STRING	sadd;							// put multiple lines together
			if (!ReadScriptWord (sadd,"{;"))
				return false;
			s += sadd;
			if (!ReadAheadScript_Character(finalc))
				return false;
		}
		return true;
	}
	return false;
}



OVERRIDE bool Script_C::BufferNextLine ()
{
	if (m_szBufPtr && *m_szBufPtr)
		return true;
	if (Script_Source::BufferNextLine())
	{
		SubstituteDefines();
		return true;
	}
	return false;
}

bool Script_C::PushSource(const CBfc::Filename &sl)
{
	if (m_csa_scannedincludes.Find(sl) != -1)
		return true;
	m_csa_scannedincludes.Add (&sl);

	if (m_bSkipAllIncludes)
		return true;
	CBfc::Filename	fn;
	const int ilocate = m_pi.LocateFile (sl, fn, m_cs_pwdWorkingFrom);
	if (ilocate == -1)		// skip this file!
		return true;

	if (!ilocate)
	{
		STRING	sTxt;
		sTxt.Format ("Include File %s not Located!", sl.GetPtr());
		SyntaxError (SYNTAX_ERROR,sTxt.GetPtr());
		return false;
	}
	
	const bool bRO = true;
	STRING	sTxt;
	
	CBfc::StreamSource_File	*p_sf = new CBfc::StreamSource_File(fn,bRO);
	if (p_sf->Open())
	{
		PushSource(p_sf);
		m_cs_pwdWorkingFrom = fn.GetPath();
//			sTxt.Format (" <<<<< Into Include: %s  <<<<<<<<", fn.GetPtr());
//			SyntaxError (SYNTAX_WARNING,sTxt.GetPtr());
		return true;
	}
	delete p_sf;
	
	sTxt.Format ("Missing Include: %s!", fn.GetPtr());
	SyntaxError (SYNTAX_ERROR,sTxt.GetPtr());
	return false;
}

void Script_C::PushSource(CBfc::StreamSource *p_stream)
{
	if (m_StreamStack.GetCount() > 100)
	{
		SyntaxError(SYNTAX_ERROR,_TXT("#include depth too great!"));
		_exit(-3);
	}
	if (p_stream)
	{
		ClearBuffer();
		m_p_source->Sleep();
		m_StreamStack.Add(&m_p_source);
		m_p_source = p_stream;
		m_LinenumberStack.Add(&m_uLineNumber);
		m_uLineNumber = 0;
		m_bOkAddComments = false;
		newposition();
	}
}
		
bool Script_C::PopSource ()
{
	if (!m_StreamStack.IsEmpty())
	{
		EmptyBuffer();
		delete m_p_source;
		m_p_source = *(m_StreamStack.GetLast());
		m_StreamStack.RemoveLast();
		
		m_uLineNumber = *(m_LinenumberStack.GetLast());
		m_LinenumberStack.RemoveLast();
		DetectWorkingFolder();
	
//  		SyntaxError(SYNTAX_WARNING,_TXT(" >>>> Out of include >>"));
		if (m_StreamStack.IsEmpty())
			SyntaxError(SYNTAX_WARNING,_TXT("*** Popped Back to top"));
			
		m_p_source->Awaken();

		m_bOkAddComments = !WithinInclude();
// 		Empty();
		return true;
	}
	return false;
}

bool Script_C::ScanIncludefile()
{
	STRING	sl;

	ReadScriptLine (sl);
	
	sl.Trim();
	bool garbled = true;
	if (sl[0] == '"' && sl.Right()=='"')
		garbled = false;
	else if (sl[0] == '<' && sl.Right()=='>')
		garbled = false;
	if (garbled)
	{
		STRING	sTxt;
		sTxt.Format ("Garbled Include Statement %s!", sl.GetPtr());
		SyntaxError (SYNTAX_ERROR,sTxt.GetPtr());
		return false;
	}
	sl.Trim(1,1);			// remove the quotes
	
// 	if (sl == "FXObject.h")
// 		SyntaxError (SYNTAX_WARNING,_TXT("stop!"));
	return PushSource (sl);
}

using namespace CBfc;

ParseIncludes::ParseIncludes	()
	: m_phrase_includePath("/usr/include")
{
}

ParseIncludes::ParseIncludes	(const STRING &includePath, const STRING &csSkipIncludes)
	:	m_phrase_includePath("/usr/include;" + includePath), m_phSkipIncludes(csSkipIncludes)
{
}

int ParseIncludes::LocateFile(const Filename &fnLocate, Filename &out_fullPath, const Filename &curdir)
{
	STRING	path;
	
			// check default folder (curdir) first
	Filename	fn(fnLocate);

	if (!m_phSkipIncludes.IsEmpty())
	{
		m_phSkipIncludes.Reset();
		while (m_phSkipIncludes.ReadScriptWord(path,";"))
			if (path == fnLocate)
				return -1;
	}

	fn.PrependPath (curdir);	// in case of folder spec in include statement
	if (fn.FileExists())
	{
		out_fullPath = fn;
		return true;
	}
							// Next, step through paths
	m_phrase_includePath.Reset();
	while (m_phrase_includePath.ReadScriptWord(path,";"))
	{
		m_phrase_includePath.SkipDeliminator(';');
		fn = fnLocate;
		fn.PrependPath (path);	// in case of folder spec in include statement
		if (fn.FileExists())
		{
			out_fullPath = fn;
			return true;
		}
	}
	return false;
}


}
