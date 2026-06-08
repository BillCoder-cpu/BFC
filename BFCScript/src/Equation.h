//*/
/*
					Equation.h : 
	
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

#include <math.h>

#define	powchr '~'

#define	TRUE	1
#define	FALSE	0

namespace CBfcScript
{

class CEquat_User
{
public:
	virtual double isvar (character *e,int c)=0;	// Variables given as cells in the spreadsheet 
	virtual double myfunct (const CBfc::STRING &func_name, character *e, int i)=0;
};


class CEquat
{
public:
	CEquat(CEquat_User *p_eqnUser);
	CEquat(CEquat_User *p_eqnUser, const CBfc_String &str_equation);

	void Set (CEquat_User *p_eqnUser, const CBfc_String &str_equation);
	void Set_Legalized (const CBfc_String &str_equation);
	void Get (CBfc_String &csEqn);

	typedef enum
	{
		LETTER,
		DIGIT,
		SPACE,
		OPERATOR,
	} EType;

	double Calculate();
	double equat (CBfc_String &cs_eqn);
	bool Legalize_Equation (CBfc_String &cs_eqn);
	double equat_legalized(const CBfc_String &cs_eqn);
	

	static EType type (const int c);
	bool is_digit (const int c) const;
	static double constant (const character c);
protected:
	double gaval (character *e,const int i);
	int findopen (character *e,const int c) const;
	int findclose (character *e,const int c) const;
	double varval (character *e,const int c);
	double myatof (character *a) const;
	double myfunct (character *e, int i) const;
	double oper (const double n, const double d, const character o) const;
	double power (const double x,const double y) const;		/* returns x to the y	*/
private:
	CEquat_User		*m_p_eqnUser;
	CBfc_String		m_str_equation;
	double			m_regs[160];
};

}


