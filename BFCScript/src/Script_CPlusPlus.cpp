//*/
/*
					Script_CPlusPlus.cpp : 
	
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

/*
search c++ file first without includes
  when find a function in c++ and classname given, but no class exists, add empty classdef
  also must then locate existing classdef when class encountered in .h
*/

using namespace CBfc;
using namespace std;

namespace CBfcScript
{
	Script_CPlusPlus::Script_CPlusPlus (CBfc::Stream &bfc_stream,const CBfc::STRING &csIncludePaths,const CBfc::STRING &csSkipIncludes, const CBfc::STRING &csDefines, const bool bSkipAllIncludes)
		: Script_C(bfc_stream, csIncludePaths, csSkipIncludes, csDefines, bSkipAllIncludes)
			, m_b_skipping_included_classdefs(0)
			, m_count_classdefs_found(0)
			, m_b_adding_classdefs(true)
			, m_p_Classes(NULL), m_p_Structures(NULL)
	{
// 		m_p_Classes = new CBfc::Array<CPlusPlus_ClassDefinition>;
	}

	Script_CPlusPlus::~Script_CPlusPlus()
	{
		BFC_RELEASE(m_p_Classes);
		BFC_RELEASE(m_p_Structures);
	}

	//
	//
	//
	//
	bool Script_CPlusPlus::LoadSources_Local()
	{
		BFC_RELEASE (m_p_Classes);
		m_p_Classes = new CBfc::Array<CPlusPlus_ClassDefinition>;
		BFC_RELEASE(m_p_Structures);
		m_p_Structures = new CBfc::Array<CPlusPlus_StructureDefinition>;

		m_b_adding_classdefs = true;

		const bool bNameOnly = true;
		AddClass(CLANG_CLASSNAME, bNameOnly);	//

		SkipIncludedClassdefs(false);
		do {
			while (ProcessNext());
		} while (PopSource());			// did we get pushed into a header file include??
		SkipIncludedClassdefs(false);
		m_b_adding_classdefs = false;

		// todo - broken! if classdef encountered during initial scan in cpp file itself.
		m_searchfor_classdef_count = m_p_Classes->GetCount();
		return true;
	}

	void Script_CPlusPlus::Reset()
	{
		Rewind();
		m_defines.Empty();
	}
	
	void Script_CPlusPlus::PushClass(CPlusPlus_ClassDefinition *p_cl)
	{
		m_ClassStack.Add (&p_cl);
		m_CurrentClassName = p_cl->m_cs_ClassName;
		m_CurrentClassScope = p_cl->m_CurrentScope;
	}

	void Script_CPlusPlus::PopClass()
	{
		m_ClassStack.RemoveLast();
		if (m_ClassStack.GetCount()>0)
		{
			m_CurrentClassName = (*m_ClassStack.GetLast())->m_cs_ClassName;
			m_CurrentClassScope = (*m_ClassStack.GetLast())->m_CurrentScope;
		} else
			m_CurrentClassName.Empty();
	}

	void Script_CPlusPlus::PushNameSpace(const STRING &s)
	{
		m_NameSpaceStack.Add (&s);
		m_CurrentNameSpace = s;
	}

	void Script_CPlusPlus::PopNameSpace()
	{
		m_NameSpaceStack.RemoveLast();
		if (m_NameSpaceStack.GetCount()>0)
			m_CurrentNameSpace = *(m_NameSpaceStack.GetLast());
		else
			m_CurrentNameSpace.Empty();
	}


	bool Script_CPlusPlus::OkToDeclare() const
	{
		return (!m_b_skipping_included_classdefs || m_StreamStack.IsEmpty());
	}


	//  find, add if not present
	CPlusPlus_ClassDefinition *Script_CPlusPlus::AddClass(const STRING &ClassDef, const bool bNameOnly)
	{
		CPlusPlus_ClassDefinition tcd;
	
		if (bNameOnly)
			tcd.m_cs_ClassName = ClassDef;
		else
			tcd.SetFromClassDef(ClassDef);
	
		CPlusPlus_ClassDefinition	*pclass;
		bool	bAdd = false;
		pclass = LocateClass (tcd.m_cs_ClassName);
		if (!pclass)
		{
			if (!m_b_adding_classdefs)
				return NULL;
			pclass = new CPlusPlus_ClassDefinition();
			bAdd = true;
			
			STRING 	sTxt;
			sTxt.Format ("!!Adding Class %s", ClassDef.GetPtr());
			SyntaxError (SYNTAX_WARNING,sTxt.GetPtr());
		}
		if (!WithinInclude())
			pclass->m_b_ExportMe = true;
		pclass->m_cs_NameSpace = m_CurrentNameSpace;
		if (!ClassDef.IsEmpty())
		{
			pclass->SetFromClassDef (ClassDef);
			GetCommentCache(pclass->m_cs_comments);
		}

			
		if (bAdd)
		{
			if (!m_p_Classes->Add(pclass))
			{
				delete pclass;
				return NULL;
			}
			delete pclass;
			pclass = LocateClass (tcd.m_cs_ClassName);
		}
		return pclass;
	}

	CPlusPlus_ClassDefinition *Script_CPlusPlus::LocateClass(const STRING &ClassName)
	{
		if (!ClassName.IsEmpty())
		{
			CPlusPlus_ClassDefinition *p_class;
			ULONG	index = m_p_Classes->StartIteration ();
			while (p_class = m_p_Classes->GetNext(index))
			{
				if (p_class->m_cs_ClassName == ClassName)
					return p_class;
			}
		}
		return NULL;
	}

	//
	// AddFunction -
	//  Add it to the class that it is a member of, or to the main list.
	//
	// returns false if exact function already exists, but fills it in first with any addt'l data.
	bool Script_CPlusPlus::AddFunction(CPlusPlus_FunctionDefinition *p_fdef)
	{
		CPlusPlus_ClassDefinition	*p_class;
		if (p_fdef->m_cs_ParentClass.IsEmpty())
		{											// no class specified, add to global pack
			p_class = LocateClass(CLANG_CLASSNAME); // Special classname for C style funcitons without parent classes
	// 		BYTEPTR bp_fdef = (BYTEPTR)p_fdef;
	// 		m_FunctionList.Add (&bp_fdef);
		} else
		{
			p_class = LocateClass(p_fdef->m_cs_ParentClass);
			if (!p_class)
				p_class = AddClass(p_fdef->m_cs_ParentClass, true);
		}
		if (!p_class)
			return false;
		if (!WithinInclude())
			p_class->m_b_ExportMe = true;
		CPlusPlus_FunctionDefinition *p_oldfdef = p_class->FunctionExists(*p_fdef);
		if (p_oldfdef)
		{
			*p_oldfdef += *p_fdef;
			return false;
		}
		p_class->m_functions.Add(p_fdef);
		return true;
	}

	//
	//
	//
	bool Script_CPlusPlus::Process_Function_Declaration(const STRING &sline)
	{
		if (Process_Function_Declaration_internal(sline))
			return true;
	//  	SyntaxError(SYNTAX_ERROR,_TXT("Bad/Malformed Function Declaration."));
		return false;
	}


	// static function
	bool Script_CPlusPlus::Detect_function_modifier (CPlusPlus_FunctionDefinition &fdef)
	{
		if (fdef.m_cs_ReturnType == "inline")
			return true;
		if (fdef.m_cs_ReturnType == "friend")
		{
			fdef.m_b_friend = true;
			return true;
		}
		if (fdef.m_cs_ReturnType == "static")
		{
			fdef.m_b_static = true;
			return true;
		}
		if (fdef.m_cs_ReturnType == "virtual")
		{
			fdef.m_b_virtual = true;
			return true;
		}
		return false;
	}

	// static function
	bool Script_CPlusPlus::Detect_partial_returntype(CPlusPlus_FunctionDefinition &fdef)
	{
		if (fdef.m_cs_ReturnType == "unsigned"
//			|| fdef.m_cs_ReturnType == "unsigned"
			)
			return true;
		return false;
	}
	
	bool Script_CPlusPlus::Process_Class_Declaration(const STRING &s)
	{
		STRING 	sTxt;
		CPlusPlus_ClassDefinition *p_classdef=NULL;
		if (OkToDeclare())
		{
			p_classdef = AddClass (s, false);
			if (p_classdef)
			{
				sTxt.Format ("Class Declaration %s", p_classdef->m_cs_ClassName.GetPtr());
				if (!p_classdef->m_cs_parentclasses.IsEmpty())
				{
					sTxt += " : ";
					sTxt += p_classdef->m_cs_parentclasses;
				}
				SyntaxError (SYNTAX_WARNING,sTxt.GetPtr());

				PushClass(p_classdef);
				SkipDeliminator('{');
				return true;
			}
		}
		return ReadBetweenBrackets (sTxt);
	}

	bool Script_CPlusPlus::Process_Function_Declaration_internal(const STRING &sline)
	{
		STRING 							s;
		character						c;
		bool							bRval = false;
		CPlusPlus_FunctionDefinition	fdef;
		Phrase							pline(sline);
	
		bool good = true;
		do {
			if (!pline.ReadScriptWord(fdef.m_cs_ReturnType,csCPP_Deliminators))
			{
				good = false;
				break;
			}
		} while (Detect_function_modifier (fdef));
		if (good)
		{
			if (Detect_partial_returntype(fdef))
			{
				if (!pline.ReadScriptWord(s, csCPP_Deliminators))
				{
					good = false;
				}
				else
				{
					fdef.m_cs_ReturnType += " " + s;
				}
			}
			if (good)
			{
				if (pline.ReadAheadScriptWord(s))
				{
					if (s == "__fastcall")
						pline.ReadScriptWord(s);
				}
			}
		}

		if (good)
		{
			bool bConstructor=false;

			if (fdef.m_cs_ReturnType == "operator")
			{
				bConstructor = true;		// fools it into the right thing!!
			}

			pline.ReadAheadScriptCharacter(c);
			while (c==':')
			{
				STRING	accum;
				// possiblities : 
				// 		return value has a namespace	- CBfc::Value class::func(args)
				//		constructor						- (CFoxMainWindow::CFoxMainWindow)

				pline.SkipScriptCharacter();		// Skip ::
				pline.ReadAheadScriptCharacter(c);	//  .
				if (c != ':')						//  .
					return false;					// 	.
				pline.SkipScriptCharacter();		//  .

				pline.SkipWhiteSpace();
				pline.ReadScriptWord(accum,csCPP_Deliminators);
				if (accum == fdef.m_cs_ReturnType || accum[0]=='~')		// constructor detected
				{
					fdef.m_cs_ParentClass = fdef.m_cs_ReturnType;
					fdef.m_cs_ReturnType = accum;
					bConstructor = true;
					break;
				} else
				{		// this is a return type (all functions must have one)
					fdef.m_cs_ReturnType += "::";
					fdef.m_cs_ReturnType += accum;
					pline.ReadAheadScriptCharacter(c);
				}
			}
			if (c=='*')
			{
				pline.SkipScriptCharacter();
				fdef.m_cs_ReturnType += '*';
			}

			if (!bConstructor)
			{
				if (fdef.m_cs_ReturnType == m_CurrentClassName || (fdef.m_cs_ReturnType[0] == '~'))
					bConstructor = true;
			}

			if (bConstructor)
			{
				s = fdef.m_cs_ReturnType;
				fdef.m_cs_ReturnType.Empty();
			} else
			{
				if (!pline.ReadScriptWord(s, ": ("))
					return false;
				// maybe return type is a non-recognized define and this is actually a constructor
				if (pline.m_DelimTriggerChar == '(' && s == m_CurrentClassName)
				{
					bConstructor = true;
					fdef.m_cs_ReturnType.Empty();
				}
				pline.SkipWhiteSpace();
			}
/*
	__CLR_OR_THIS_CALL _Lockit()
        : _Locktype(0)
	    {	// default construct
        _Lockit_ctor(this);
	    }
	*/
			if (pline.ReadAheadScriptCharacter(c) && c==':')	// class function encountered
			{
				fdef.m_cs_ParentClass = s;
				pline.SkipScriptCharacter();		// Skip ::
				pline.SkipScriptCharacter();
				pline.ReadScriptWord(fdef.m_cs_FunctionName, "( ");
			} else
			{
				if (!m_CurrentClassName.IsEmpty())  // classname? then use it
				{
					fdef.m_cs_ParentClass = m_CurrentClassName;
					fdef.m_e_scope = m_CurrentClassScope;
				}			
				fdef.m_cs_FunctionName = s;
			}
			if (fdef.m_cs_FunctionName == "operator")
			{
				pline.ReadScriptWord(s, "( ");
				fdef.m_cs_FunctionName += ' ';
				fdef.m_cs_FunctionName += s;
				fdef.m_b_operator = true;		//set it here, somehow use this later! (not yet implemented)
			}
			STRING	arguments;
	// 		ReadScript_ArgumentList
			if (pline.ReadScriptWord(arguments, ")"))
			{
				bRval = true;
				fdef.SetArgumentsFromString(arguments);

				pline.SkipDeliminator(')');
				if (pline.ReadAheadScriptWord(s) && s == "const")
				{
					fdef.m_b_const = true;
					pline.SkipScriptWord();
				}
			}
		}

		ReadAheadScript_Character(c);
		if (c == '{')   //	Read Function Source between brackets into the text area
		{
			if (!ReadBetweenBrackets (fdef.m_cs_code))
				bRval = false;

			if (good)
			{
				pline.SkipWhiteSpace();
				if (pline.ReadAheadScriptCharacter(c) && c == ':')
				{
					s = pline.Remainder();
					s += '\n';
					fdef.m_cs_code.InsertAt(s);
				}
			}

		} else		// we are in the header, just add our information to the existing function
		{
			if (fdef.m_cs_ParentClass.IsEmpty())		// no code, don't define extern functions from headers
				bRval = false;
	//				work here buddy
		}
		if (bRval)	  // Add function takes care of merging with existing!
		{
			if (OkToDeclare() && fdef.ValidateSelf())
			{
				GetCommentCache(fdef.m_cs_comments);
				if (AddFunction (&fdef))
				{
					s.Format ("F_Decl %s::%s ",  fdef.m_cs_ParentClass.GetPtr(), fdef.m_cs_FunctionName.GetPtr());
					if (fdef.m_b_const)
						s += "const ";
					s += '(';
					s += fdef.m_cs_parameters;
					s += ')';
					SyntaxError (SYNTAX_WARNING,s.GetPtr());
				}
			}
		}
		return bRval;
	}



	bool Script_CPlusPlus::ProcessNext()
	{
		STRING		s;
		character	c;

		if (!ReadAheadScript_Character_NoDefines(c))
			return false;
		if (c == '#')
		{
			ProcessDirective();
			return true;
		}
		if (skipping_code())		// in #ifdef for example
			return SkipScriptLine ();

		switch (c) {
			case ';':
	// 		case '{':
			case ' ':
			case '\t':
			case '\n':
				SkipScript_Character();
				return true;
			case '}':
				SkipScript_Character();
				if (m_CurrentClassName.IsEmpty())
					PopNameSpace();		// Assume namespace has ended
				else
				{
					if ((*m_ClassStack.GetLast())->m_e_classtype == E_CPPCT_STRUCT)
					{
						if ((*m_ClassStack.GetLast())->m_b_typedef)
						{
							if (ReadScriptWord(s))
							{
								(*m_ClassStack.GetLast())->m_cs_tag = s;
								if (m_CurrentClassName == "typedef_tag")
								{
									(*m_ClassStack.GetLast())->m_cs_ClassName = s;
								}
							}
						}
					}
					PopClass();
				}
				return true;
		}

		STRING	w;

		if (WithinClassdef())
		{
			if (ReadAheadScriptWord(w,csCPP_Deliminators) && m_DelimTriggerChar == ':')
			{	// Check for public:, private:, etc.
				if (Detect_Scope(w, m_CurrentClassScope))
				{
					SkipScriptWord(csCPP_Deliminators);
					SkipScriptCharacter();
					return true;
				}
			}
		}

		if (!ReadSourceLine(s, c))	// reads untill { or ;
			return false;

		Phrase ph(s);
		ph.ReadScriptWord(w);
	
		if (c == ';')
		{
			if (s.Find('(') != -1)
			{
				if (w != "using" && w != "typedef")
					Process_Function_Declaration(s);			// assume function definition here.
			} else
			{			
				if (WithinClassdef())
				{   // Probable Data member definition: try it.
					CPlusPlus_Member	arg;
					if (arg.SetFromString(s))
					{
						arg.m_e_scope = m_CurrentClassScope;
						GetCommentCache(arg.m_cs_comments);
						(*m_ClassStack.GetLast())->m_members.Add(&arg);
					}
					else
					{
						(*m_ClassStack.GetLast())->m_cs_Data += s;
						(*m_ClassStack.GetLast())->m_cs_Data += ";\n";
					}
				}
			}
		} else if (c == '{')	// definition block
		{
			if (w == "typedef")
			{		// Pick up the actual struct type
				ph.ReadScriptWord(w);
			}
			if (w=="namespace")
			{
				STRING s2;
				ph.ReadScriptWord(s2);
				PushNameSpace (s2);
				SkipScript_Character();		// skip past bracket
				return true;
			} else if (w=="enum" || w == "union")
			{
				STRING s2;					//	For Now: Skip the Source between brackets.
				if (ReadBetweenBrackets (s2))
				{
					if (WithinClassdef())
					{
						(*m_ClassStack.GetLast())->m_cs_Data += s;
						(*m_ClassStack.GetLast())->m_cs_Data += s2;
					}
/*
					else if (!WithinInclude())
					{
						CPlusPlus_StructureDefinition sdef(s, s2);
						m_p_Structures->Add(&sdef);
					}
*/					return true;

				}
				return false;
			}

			if (w=="template")
			{
				ph.SkipToDeliminator(">");
				ph.SkipDeliminator('>');
				ph.ReadScriptWord(w);
			}
			if (w=="class" ||  w == "struct")
			{
				Process_Class_Declaration(s);
			} else 
			{
				s.Trim();
				const character c = s.Right();
				if (c=='=')			// could be a static data definition
				{
					STRING s2;
					SyntaxError(SYNTAX_ERROR, "UNSUPPORTED data definition");
					return ReadBetweenBrackets (s2);
				} else
				{					// assume function definition here.
					Process_Function_Declaration(s);
				}
			}
		}
		return true;
	}
	
	bool Script_CPlusPlus::Detect_Scope(const STRING &w, E_CPLUSPLUS_SCOPE &scope)
	{
		bool bdo = true;
		if (w == "private")
			scope = E_CPPS_PRIVATE;
		else if (w == "protected")
			scope = E_CPPS_PROTECTED;
		else if (w == "public")
			scope = E_CPPS_PUBLIC;
		else
			bdo = false;
		return bdo;
	}

}
