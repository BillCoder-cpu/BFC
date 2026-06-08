//*/
/*
					Script_CPlusPlus.h : 
	
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
// Script_CPlusPlus.h

#include "../../BFCScript/src/CPlusPlus_FunctionDefinition.h"

#define csCPP_Deliminators 		STRING(" =(*/-+\t\n\r:")
#define	CLANG_CLASSNAME			STRING("CLaNg_BFClasName")	// Unique Id to assign the 'class' that C type functions belong to

namespace CBfcScript
{

class Script_CPlusPlus : public Script_C
{
public:
	Script_CPlusPlus (CBfc::Stream &bfc_stream,const CBfc::STRING &csIncludePaths,const CBfc::STRING &csSkipIncludes, const CBfc::STRING &csDefines, const bool bSkipAllIncludes);
	virtual ~Script_CPlusPlus();
	bool LoadSources_Local();

	static bool Detect_Scope(const STRING& w, E_CPLUSPLUS_SCOPE& scope);

protected:
	void SkipIncludedClassdefs(const bool bOn) { m_b_skipping_included_classdefs = bOn; }
	bool OkToDeclare() const;
	
	bool ProcessNext();
	bool Process_Class_Declaration(const STRING &s);
	bool Process_Function_Declaration(const STRING &s);
	CPlusPlus_ClassDefinition *AddClass(const STRING &ClassDef, const bool bNameOnly);
	CPlusPlus_ClassDefinition *LocateClass(const STRING &ClassName);
	bool AddFunction(CPlusPlus_FunctionDefinition *p_fdef);

	bool WithinClassdef() const { return (m_ClassStack.GetCount()>0); }

	void PushNameSpace(const STRING &s);
	void PopNameSpace();
	void PushClass(CPlusPlus_ClassDefinition *p_cl);
	void PopClass();
private:
	static bool Detect_function_modifier (CPlusPlus_FunctionDefinition &fdef);
	static bool Detect_partial_returntype(CPlusPlus_FunctionDefinition &fdef);
	void Reset();
	bool Process_Function_Declaration_internal(const STRING &s);

protected:
	CBfc::STRING			m_CurrentNameSpace;	// Comments associated with this function
	CBfc::StringArray		m_NameSpaceStack;
	
	CBfc::STRING			m_CurrentClassName;	// Comments associated with this function
	E_CPLUSPLUS_SCOPE		m_CurrentClassScope;
	CBfc::Array<CPlusPlus_ClassDefinition*>		m_ClassStack;
	
	CBfc::StringArray		m_KnownTypenames;
	CBfc::ArrayPtr			m_FunctionList;
	
	bool					m_b_skipping_included_classdefs;
	bool					m_b_adding_classdefs;
	UINT					m_count_classdefs_found, m_searchfor_classdef_count;

public:
	CBfc::Array<CPlusPlus_ClassDefinition>		*m_p_Classes;
	CBfc::Array<CPlusPlus_StructureDefinition>	*m_p_Structures;
};



}

