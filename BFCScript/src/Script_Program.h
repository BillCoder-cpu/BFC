//*/
/*
					Script_Program.h : 
	
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

BFC_CLASS Variable : public CBfc::Value
{
public:
	typedef enum	{
		VAR_STRING,
		VAR_VALUE
	} EVariableType;
	
	Variable();
	virtual ~Variable();
private:
	EVariableType		m_vartype;
	CBfc::STRING		*m_p_string;
};

// strips out comments automatically
// dumber than BfcScript, only designed to 'parse' C#, C, C++, PHP, etc. sources
BFC_CLASS Script_Source : public Script_XML
{
	public:
		Script_Source() {}
		Script_Source (CBfc::Stream &bfc_stream)
	: Script_XML(bfc_stream)
				, m_b_skipping_strings(false)
				{
				}
				void SkippingStrings(const bool bOn)
				{
					m_b_skipping_strings = bOn;
				}
	protected:
		bool	m_b_skipping_strings;
};

BFC_CLASS Program 
{
public:
	virtual bool 			Run ();
protected:
	virtual 	bool 		Evaluate_Statement	(const CBfc::STRING &cs);
	
	bool						Evaluate_Variable		(Variable &varDest, const CBfc::STRING &varName);		// given name, retreive var
	bool 					Assign_Variable (const Variable &varSrc , CBfc::STRING &varName);
private:

private:
	CBfc::StringArray		m_array_VariableNames;
	CBfc::ArrayPtr			m_array_Variables;
};


BFC_CLASS Script_Program : public Script_Source, public Program
{
public:
	Script_Program(CBfc_Stream &bfc_stream);
	virtual ~Script_Program();

public:
	virtual bool 			Run ();

	bool						Assign_Variable();
protected:
	virtual bool			Compile();

	bool						GetNextStatement(CBfc::STRING &cs);
};


}


