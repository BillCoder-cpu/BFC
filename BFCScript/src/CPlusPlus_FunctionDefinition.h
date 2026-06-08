//*/
/*
					CPlusPlus_FunctionDefinition.h : 
	
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

#ifndef CPP__FDF_H_
#define CPP__FDF_H_

namespace CBfcScript
{

	typedef enum {
		E_CPPS_PRIVATE
		, E_CPPS_PROTECTED
		, E_CPPS_PUBLIC
	} E_CPLUSPLUS_SCOPE;

	typedef enum {
		E_CPPCT_CLASS
		, E_CPPCT_STRUCT
		, E_CPPCT_UNION
		, E_CPPCT_ENUM
	} E_CPLUSPLUS_CLASSTYPE;


class CPlusPlus_FunctionName : public CBfc::STRING
{
public:
	CPlusPlus_FunctionName() {}
	CPlusPlus_FunctionName(const CBfc::STRING &name) : STRING(name)
	{
	}
	bool operator != (const CPlusPlus_FunctionName &other);
protected:
	bool GetName(CBfc::STRING &csName, UINT uIndex=0) const;
};


class CPlusPlus_Argument
{
public:
	CPlusPlus_Argument();
	CPlusPlus_Argument(const CBfc::STRING &argdesc);

	void operator = (const CPlusPlus_Argument &copy);
	bool operator != (const CPlusPlus_Argument &other);
	
	bool	SetFromString(const CBfc::STRING &argdesc);
	CBfc::STRING	Text_CSharp(const bool bWithTypes) const;

	CPlusPlus_FunctionName	m_cs_Type;
	CBfc::STRING			m_cs_ArgumentName;
	CBfc::STRING			m_cs_DefaultValue;
	bool				m_b_pointer;
	bool				m_b_reference;
	bool				m_b_const;
	bool				m_b_volatile;
protected:
	bool		IsNativeVartype() const;
	void		Empty();
};

class CPlusPlus_Member : public CPlusPlus_Argument
{
public:
	CPlusPlus_Member() {}
	CPlusPlus_Member(const CBfc::STRING& argdesc) : CPlusPlus_Argument(argdesc)
	{}

	void operator = (const CPlusPlus_Member& copy);
	E_CPLUSPLUS_SCOPE	m_e_scope;
	CBfc::STRING		m_cs_comments;	// Comments associated with this argument
};

struct CPlusPlus_FunctionDefinition
{
public:
	CPlusPlus_FunctionDefinition();
	CPlusPlus_FunctionDefinition (const CPlusPlus_FunctionDefinition &copy);

	bool	ValidateSelf();
	bool MakeArgumentList(CBfc::STRING &sTxt, const bool bWithTypes=true) const;
	bool MakeArgumentList_Sharp(CBfc::STRING &sTxt, const bool bWithTypes=true) const;
	void SetArgumentsFromString (const CBfc::STRING &sArgs);

	void operator = (const CPlusPlus_FunctionDefinition &copy);
	bool operator == (const CPlusPlus_FunctionDefinition &other);
	bool operator += (const CPlusPlus_FunctionDefinition &other);
		
	E_CPLUSPLUS_SCOPE				m_e_scope;
	CBfc::STRING					m_cs_ParentClass;
	CBfc::STRING					m_cs_FunctionName;
	CBfc::STRING					m_cs_ReturnType;
	CBfc::Array<CPlusPlus_Argument>	m_Parameters;
	bool							m_b_static;
	bool							m_b_const;
	bool							m_b_virtual;
	bool							m_b_operator;
	bool							m_b_friend;
	
	CBfc::STRING			m_cs_comments;	// Comments associated with this function
	CBfc::STRING			m_cs_code;		// code block extracted from the source, with comments included!
	
	CBfc::STRING	m_cs_parameters; // for copying purposes
};

class CPlusPlus_ClassDefinition
{
public:
	CPlusPlus_ClassDefinition();
	CPlusPlus_ClassDefinition (CPlusPlus_ClassDefinition *p_class);
	CPlusPlus_ClassDefinition (const CPlusPlus_ClassDefinition &copy);
	virtual ~CPlusPlus_ClassDefinition();
	
	void operator = (const CPlusPlus_ClassDefinition &copy);
			
	CPlusPlus_FunctionDefinition	*FunctionExists(const CPlusPlus_FunctionDefinition &fdef);
	void SetFromClassDef (const CBfc::STRING &ClassDef);

	bool				m_b_ExportMe;
	
	CBfc::STRING		m_cs_ClassName;
	CBfc::STRING		m_cs_NameSpace;
	CBfc::STRING		m_cs_parentclasses;
	CBfc::STRING		m_cs_comments;	// Comments associated with this class
	CBfc::STRING		m_cs_Data;

	// Structure related:
	bool							m_b_typedef;
	E_CPLUSPLUS_CLASSTYPE			m_e_classtype;
	CBfc::STRING					m_cs_tag;

	E_CPLUSPLUS_SCOPE		m_CurrentScope;

	CBfc::Array<CPlusPlus_FunctionDefinition>	m_functions;
	CBfc::Array<CPlusPlus_Member>				m_members;
};


// Used in .h files for Struct, union, enum
class CPlusPlus_StructureDefinition
{
public:
	bool							m_b_typedef;
	E_CPLUSPLUS_CLASSTYPE			m_e_classtype;
	CBfc::STRING					m_cs_tag;
	CBfc::STRING					m_cs_name;
	CBfc::Array <CPlusPlus_Member>	m_Members;
public:
	CPlusPlus_StructureDefinition() {}
	CPlusPlus_StructureDefinition(const CBfc::STRING& declaration, const CBfc::STRING& contents);
	CPlusPlus_StructureDefinition(const CPlusPlus_StructureDefinition& copy);
	CPlusPlus_StructureDefinition(CPlusPlus_StructureDefinition* p_copy);
	void operator = (const CPlusPlus_StructureDefinition& copy);
};

}

#endif		// #ifndef CPP__FDF_H_

