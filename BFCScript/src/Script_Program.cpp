//*/
/*
					Script_Program.cpp : 
	
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
	Parameters can be of Array or Matrix form.
	IsArray(), IsMatrix()
	no return values
	

*/


using namespace CBfc;
/*
	Sample Program Script:
	
	
	VAR	A = 10.2;
	var string="Hello", x=0;
	
	for (x=0; x < 
	
*/
namespace CBfcScript
{


Variable::Variable()
	: m_vartype(VAR_VALUE)
	, m_p_string(NULL)
{
}

Variable::~Variable()
{
}

#define	BFC_PROGKEY_VAR			0
#define	BFC_PROGKEY_FOR			1
#define	BFC_PROGKEY_FOREACH		2
#define	BFC_PROGKEY_DO			3
#define	BFC_PROGKEY_WHILE			4
#define	BFC_PROGKEY_FUNCTION		5
#define	BFC_PROGKEY_IF			6

/*
	Example function (& indicates that the variable can be modified by the function):
		function decent (a,b,&c)
		{
			if (a=="Hello")
				c=17;
			else 
				c = b * 14;
		}
*/
static characterPtr Program_KeyWords[] = 
{
	STATICBYTES("var"),
	STATICBYTES("for"),
	STATICBYTES("foreach"),
	STATICBYTES("do"),
	STATICBYTES("while"),
	STATICBYTES("function"),
	STATICBYTES("if"),
	characterPtr(NULL)
};

Script_Program::Script_Program(CBfc_Stream &bfc_stream)
	: Script_Source(bfc_stream)
{
}

Script_Program::~Script_Program()
{
}

bool Script_Program::GetNextStatement(CBfc::STRING &cs)
{
	return false;
}

bool Script_Program::Compile ()
{
try
	{
		STRING	cs;
		int			iKey;

		if (MatchScriptKey (Program_KeyWords, iKey))
		{
			switch (iKey) {
				case BFC_PROGKEY_VAR:	// Syntax Error- should be handled (optionally) by the base class.
					Assign_Variable();
					break;
			}
		}
		while (GetNextStatement (cs))
		{
			Evaluate_Statement(cs);
		}
		return true;
	}
 catch (...)
	{
		return false;
	}
}

OVERRIDE bool Script_Program::Run ()
{
	if (Compile())
		return Program::Run();
	return false;
}


/**
	 Reads the variable assignment from the script.
**/
bool Script_Program::Assign_Variable()
{
	return false;
}


/**
	* Compiler and Interpreter should work together
**/
OVERRIDE bool Program::Run ()
{
		return true;
}

OVERRIDE bool Program::Evaluate_Statement	(const STRING &cs)
{
	return false;
}

bool Program::Assign_Variable (const Variable &varSrc , STRING &varName)
{
	return false;
}

bool	Program::Evaluate_Variable	(Variable &varDest, const STRING &varName)		// given name, retreive var
{
	INT64	i=m_array_VariableNames.Find (varName);
	if (i >=0)
	{
		Variable *pVar = (Variable*)m_array_Variables[i];
		varDest = *pVar;
		return true;
	}
	return false;
}

}
