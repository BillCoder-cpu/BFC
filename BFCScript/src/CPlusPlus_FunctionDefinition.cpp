//*/
/*
					CPlusPlus_FunctionDefinition.cpp : 
	
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
using namespace std;

namespace CBfcScript
{


//
bool CPlusPlus_FunctionName::operator != (const CPlusPlus_FunctionName &other)
{
	STRING	n1,n2;
	UINT	uIndex = 0;

	while (1)
	{
		if (!GetName(n1,uIndex)) return false;
		if (!other.GetName(n2,uIndex)) return false;
		if (n1 != n2)
			return true;
		uIndex++;
	}
}


// returns the name at the position specified (from the end)
// Example   :   three::two::one::zero
bool CPlusPlus_FunctionName::GetName (STRING &csName, UINT uIndex) const
{
	int	i=0;
	const bool b_Reverse = true;
	while (1)
	{
		i = Find (':',i,b_Reverse);
		if (uIndex == 0) 
		{
			if (i >= 0)
				csName = Right (i);
			else
				csName = *this;
			return true;
		}
		if (i== -1)
			return false;
		i += 2;				// skip past the '::'
		uIndex--;
	}
}

//-------------------------------------------------------------------------------------------------------------

	CPlusPlus_Argument::CPlusPlus_Argument()
	{
		Empty();
	}
	
	CPlusPlus_Argument::CPlusPlus_Argument(const CBfc::STRING &argdesc)
	{
		Empty();
		SetFromString(argdesc);
	}

	void CPlusPlus_Argument::Empty ()
	{
		m_b_const = m_b_volatile = m_b_pointer = m_b_reference = false;
		m_cs_Type.Empty();
		m_cs_ArgumentName.Empty();
		m_cs_DefaultValue.Empty();
	}

	void CPlusPlus_Argument::operator = (const CPlusPlus_Argument &copy)
	{
		m_cs_Type = copy.m_cs_Type;
		m_cs_ArgumentName = copy.m_cs_ArgumentName;
		m_cs_DefaultValue = copy.m_cs_DefaultValue;
		m_b_pointer = copy.m_b_pointer;
		m_b_reference = copy.m_b_reference;
		m_b_const = copy.m_b_const;
		m_b_volatile = copy.m_b_volatile;
	}

	// used by ArrayEquals	
	bool CPlusPlus_Argument::operator != (const CPlusPlus_Argument &other)
	{
		if (m_cs_Type != other.m_cs_Type)
			return true;
//		if (m_cs_ArgumentName != other.m_cs_ArgumentName)	// actually header and source files can have differing argument names.
//			return true;
		return false;
	}
	
// example: FXObject*p_sender,const FXSelector &fxsel,
//CFoxTopWindow (, FXApp *p_App,   const,   UILayerWindow,   UILayerWindow);
// (FXApp *p_App, const CBfc::STRING &csTitle, UILayerWindow* p_Layer, UILayerWindow *p_Parent)
	bool CPlusPlus_Argument::SetFromString(const CBfc::STRING &argdesc)
	{
		bool		bRval = false;
		character	c;
		STRING		word;
		
		Phrase	ph(argdesc);
		STRING	delims(ph.GetDefaultDeliminators());
		delims += '&';
		Empty();
		do
		{
			ph.SkipWhiteSpace();
			if (!ph.ReadScriptWord(word,delims))
				break;
			if (word == "friend")
			{
				break;
			}
			if (word=="const")
			{
				m_b_const = true;
				continue;
			}
			if (word=="volatile")
			{
				m_b_volatile = true;
				continue;
			}
			if (word=="unsigned")
			{
				m_cs_Type += 'u';
				continue;
			}
			m_cs_Type += word;

			ph.SkipWhiteSpace();
			if (ph.ReadAheadScriptCharacter(c))
			{
				if (c == ':')
					continue;
				if (c == '*' || c == '&')
				{
					if (c == '*')
						m_b_pointer = true;
					else
						m_b_reference = true;
					ph.SkipScriptCharacter();
					ph.SkipWhiteSpace();
				}
			}
			if (!ph.ReadScriptWord(m_cs_ArgumentName))
				break;
			if (ph.ReadAheadScriptCharacter(c) && c == '=')
			{
				ph.SkipScriptCharacter();
				ph.ReadScriptWord(m_cs_DefaultValue);
			}
			bRval = true;
			break;
		} while (1);
		return bRval;
	}

	bool CPlusPlus_Argument::IsNativeVartype() const
	{
		STRING	localType(m_cs_Type);
		localType.ToUpperCase();
		return (localType == "UINT" || localType == "INT" || localType == "LONG" || localType == "ULONG");
	}

	CBfc::STRING CPlusPlus_Argument::Text_CSharp(const bool bWithTypes) const
	{
		STRING sTxt;
		if (!(m_cs_Type == "void") || !m_cs_ArgumentName.IsEmpty())	// avoid the void by itself allowed by C++ but not C#
		{
			if (bWithTypes)
			{
				// [MarshalAs(UnmanagedType.ByValArray, SizeConst = )]
				if (m_b_volatile)
					sTxt += "volatile ";
				if (m_b_reference && IsNativeVartype())
					sTxt += "ref ";
				sTxt += (m_cs_Type);
				if (m_b_pointer)
					sTxt += "[]"; //'*';
				sTxt += " ";
			}
			sTxt += (m_cs_ArgumentName);
		}
		return sTxt;
	}
	
	void CPlusPlus_Member::operator = (const CPlusPlus_Member& copy)
	{
		CPlusPlus_Argument::operator = (copy);
		m_e_scope = copy.m_e_scope;
		m_cs_comments = copy.m_cs_comments;
	}
//-------------------------------------------------------------------------------------------------------------

CPlusPlus_FunctionDefinition::CPlusPlus_FunctionDefinition()
{
	m_e_scope = E_CPPS_PUBLIC;
	m_b_operator = false;
	m_b_static = false;
	m_b_virtual = false;
	m_b_const = false;
	m_b_friend = false;
}

CPlusPlus_FunctionDefinition::CPlusPlus_FunctionDefinition (const CPlusPlus_FunctionDefinition &copy)
{
	*this = copy;
}

void CPlusPlus_FunctionDefinition::operator = (const CPlusPlus_FunctionDefinition &copy)
{
	m_e_scope = copy.m_e_scope;
	m_cs_ParentClass = copy.m_cs_ParentClass;
	m_cs_FunctionName = copy.m_cs_FunctionName;
	m_cs_ReturnType = copy.m_cs_ReturnType;
	m_b_static = copy.m_b_static;
	m_b_const = copy.m_b_const;
	m_b_virtual = copy.m_b_virtual;
	m_b_friend = copy.m_b_friend;
	
	m_cs_comments = copy.m_cs_comments;	// Comments associated with this function
	m_cs_code = copy.m_cs_code;		// code block extracted from the source, with comments included!

// 	CBfc::Array<CPlusPlus_Argument>	m_Parameters;
	SetArgumentsFromString (copy.m_cs_parameters);
}

// returns false if invalid function definition
bool CPlusPlus_FunctionDefinition::ValidateSelf()
{
	while (m_cs_FunctionName[0] == '(')
		m_cs_FunctionName.TrimLeft(1);
	return true;
}

//
// Generates a string with the arguments as they would be in CSHarp
//
//   all pointers become array[] (i.e. '*' becomes '[]')
//
bool CPlusPlus_FunctionDefinition::MakeArgumentList_Sharp(STRING &sTxt, const bool bWithTypes) const
{
	sTxt.Empty();
	CPlusPlus_Argument	*p_arg;
				//	next, write the p_func->m_Parameters
	ULONG	index = m_Parameters.StartIteration ();
	while (p_arg = m_Parameters.GetNext(index))
	{
		STRING csArg = p_arg->Text_CSharp(bWithTypes);
		if (!csArg.IsEmpty())
		{
			if (!sTxt.IsEmpty())
				sTxt += ", ";
			sTxt += csArg;
		}
	}
	return (!sTxt.IsEmpty());
}

bool CPlusPlus_FunctionDefinition::MakeArgumentList(STRING &sTxt, const bool bWithTypes) const
{
	sTxt.Empty();
	CPlusPlus_Argument	*p_arg;
				//	next, write the p_func->m_Parameters
	ULONG	index = m_Parameters.StartIteration ();
	while (p_arg = m_Parameters.GetNext(index))
	{
		if (!sTxt.IsEmpty())
			sTxt += ", ";
		if (bWithTypes)
		{
			sTxt += (p_arg->m_cs_Type);
			sTxt += " ";
			if (p_arg->m_b_pointer)
				sTxt += '*';
			if (p_arg->m_b_reference)
				sTxt += '&';
		}
		sTxt += (p_arg->m_cs_ArgumentName);
	}
	return (!sTxt.IsEmpty());
}

	bool CPlusPlus_FunctionDefinition::operator == (const CPlusPlus_FunctionDefinition &other)
	{
		if (m_cs_FunctionName != other.m_cs_FunctionName)
			return false;
		if (m_b_const != other.m_b_const)
			return false;
			// check m_Parameters for same count and type for overrides!
		return m_Parameters.ArrayEquals(other.m_Parameters);
	}
		
	// merge info from other def
	bool CPlusPlus_FunctionDefinition::operator += (const CPlusPlus_FunctionDefinition &other)
	{
// todo - each m_Param add info
		if (other.m_b_static) m_b_static = true;
		if (other.m_b_virtual) m_b_virtual = true;
// 		if (other.m_b_const) m_b_const = true;
		if (other.m_b_friend) m_b_friend = true;
		if (!other.m_cs_code.IsEmpty()) m_cs_code = other.m_cs_code;
		return true;
	}

	void CPlusPlus_FunctionDefinition::SetArgumentsFromString (const STRING &sArgs)
	{
		m_cs_parameters = sArgs;
		if (m_cs_parameters[0] == '(')
			m_cs_parameters.TrimLeft(1);
		
		Phrase ph(m_cs_parameters);
		STRING sarg;
		while (ph.ReadScriptWord(sarg,','))
		{
			CPlusPlus_Argument	arg(sarg);
			m_Parameters.Add(&arg);
			ph.SkipDeliminator(',');
		}
	}

CPlusPlus_FunctionDefinition *CPlusPlus_ClassDefinition::FunctionExists(const CPlusPlus_FunctionDefinition &fdef)
{
	int index = m_functions.Find(fdef);
	if (index==-1)
		return NULL;
	return m_functions[index];
}




//-------------------------------------------------------------------------------------------------------------

CPlusPlus_ClassDefinition::CPlusPlus_ClassDefinition ()
	: m_b_ExportMe (false), m_CurrentScope(E_CPPS_PRIVATE)
		, m_b_typedef (false), m_e_classtype (E_CPPCT_CLASS)
{
}

CPlusPlus_ClassDefinition::CPlusPlus_ClassDefinition (const CPlusPlus_ClassDefinition &copy)
{
	*this = copy;
}

CPlusPlus_ClassDefinition::CPlusPlus_ClassDefinition (CPlusPlus_ClassDefinition *p_class)
{
	*this = *p_class;
}

CPlusPlus_ClassDefinition::~CPlusPlus_ClassDefinition()
{
	m_functions.Empty();
	m_members.Empty();
}

void CPlusPlus_ClassDefinition:: operator = (const CPlusPlus_ClassDefinition &copy)
{
	m_cs_ClassName = copy.m_cs_ClassName;
	m_cs_parentclasses = copy.m_cs_parentclasses;
	m_cs_NameSpace = copy.m_cs_NameSpace;
	m_functions = copy.m_functions;
	m_members = copy.m_members;
	m_cs_comments = copy.m_cs_comments;
	m_b_ExportMe=copy.m_b_ExportMe;
	m_CurrentScope=copy.m_CurrentScope;
	m_cs_Data = copy.m_cs_Data;
// Structure related
	m_b_typedef = copy.m_b_typedef;
	m_e_classtype = copy.m_e_classtype;
	m_cs_tag = copy.m_cs_tag;
}

// needs to support template<typelist> class name : public parent
void CPlusPlus_ClassDefinition::SetFromClassDef (const STRING &ClassDef)
{
	Phrase ph(ClassDef);

// 	STRING delims(Phrase::GetDefaultDeliminators());
// 	delims += ":";
	STRING	s;
	ph.ReadAheadScriptWord(s);
	if (s == "typedef")
	{		// Pick up the actual struct type
		m_b_typedef = true;
		ph.SkipScriptWord();
		ph.ReadAheadScriptWord(s);
	}
	if (s == "class")
	{
		m_e_classtype = E_CPPCT_CLASS;
		ph.SkipScriptWord();
	}
	else if (s == "struct")
	{
		m_e_classtype = E_CPPCT_STRUCT;
		m_CurrentScope = E_CPPS_PUBLIC;	// Structures default to public
		ph.SkipScriptWord();
	}
	
	ph.ReadScriptWord(m_cs_ClassName,csCPP_Deliminators);
	if (m_cs_ClassName.IsEmpty())
		m_cs_ClassName = "typedef_tag";
		// looks like : public parent1, protected parent2
	if (ph.SkipScriptCharacter())		// skip the ':' deliminator if it exists
	{
		m_cs_parentclasses.Empty();
		STRING	ParentClass;
		while (!ph.IsEOL())
		{
			ph.ReadScriptWord(ParentClass);
			m_cs_parentclasses += ParentClass + " ";
		}
	}
}

CPlusPlus_StructureDefinition::CPlusPlus_StructureDefinition(const CPlusPlus_StructureDefinition& copy)
{
	*this = copy;
}

CPlusPlus_StructureDefinition::CPlusPlus_StructureDefinition(CPlusPlus_StructureDefinition* p_copy)
{
	*this = *p_copy;
}


CPlusPlus_StructureDefinition::CPlusPlus_StructureDefinition(const CBfc::STRING& declaration, const CBfc::STRING& contents)
{
	/*
	E_CPLUSPLUS_SCOPE current_scope = E_CPLUSPLUS_SCOPE::E_CPPS_PUBLIC;
	{
		CBfc::STRING	w;
		//		m_b_typedef;
		//		E_CPLUSPLUS_STRUCTTYPE				m_e_structtype;
		Phrase ph(declaration);
		ph.ReadScriptWord(w);
		m_b_typedef = (w == "typedef");
		if (m_b_typedef)
			ph.ReadScriptWord(w);
		if (w == "enum")
			m_e_structtype = E_CPPST_ENUM;
		else if (w == "union")
			m_e_structtype = E_CPPST_UNION;
		else if (w == "struct")
			m_e_structtype = E_CPPST_STRUCT;
		ph.ReadScriptWord(m_cs_tag);
	}
	{
		Phrase ph(contents);
		CBfc::STRING next;
		character c;

		while (ph.ReadAheadScriptCharacter(c))
		{
			ph.ReadScriptWord(next, '\n');
			if (c == '}')
			{
				if (m_b_typedef)
				{
					Phrase td(next);
					td.SkipScriptCharacter();
					td.ReadScriptWord(m_cs_name);
				}
				break;
			}
			if (c != '{')
			{
				if (Script_CPlusPlus::Detect_Scope(next, current_scope))
				{
					ph.SkipScriptCharacter();
				}
				else
				{
					CPlusPlus_Member	arg(next);
					arg.m_e_scope = current_scope;
					m_Members.Add(&arg);
				}
			}
		}
	}
	*/
}

void CPlusPlus_StructureDefinition:: operator = (const CPlusPlus_StructureDefinition& copy)
{
//	m_cs_NameSpace = copy.m_cs_NameSpace;
	m_cs_name = copy.m_cs_name;
	m_cs_tag = copy.m_cs_tag;
	m_b_typedef = copy.m_b_typedef;
//	m_e_structtype = copy.m_e_structtype;
	m_Members = copy.m_Members;
}


}
