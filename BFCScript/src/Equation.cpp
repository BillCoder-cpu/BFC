//*/
/*
					Equation.cpp : 
	
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
	Copyright (C) 1986--2006 by William Paul Foster, all rights reserved.
*/
/****************** equat () equation transformer ******************
                             Version 1.0

  equat (s) - Returns a float value represented by the complex ascii
                string s in equation form.

  Required external functions:
    isvar (s,i) - Returns float value of a variable whose ascii 
                  representation starts at s[i]
    init_range (s) - see sum
    nextrange ()   - see sum


  Used by:
    calc - a transportable spreadsheet using the design of 
         supercalc as a model

 todo:
	- still rounds to int

              created by Bill Foster
                 of Infolab Inc.

********************************************************************/
#include <BFC/BFCScript.h>
namespace CBfcScript
{
// using namespace std;
// extern float sin(), cos (), atan (), exp (), log (), log10 (), fabs ();

/* ASCII EQUATION HANDLER	

	2/7/86
	 WPF
*/

CEquat::CEquat(CEquat_User *p_eqnUser)
	: m_p_eqnUser (p_eqnUser)
{
}

CEquat::CEquat(CEquat_User *p_eqnUser, const CBfc_String &str_equation)
{
	Set (p_eqnUser, str_equation);
}

void CEquat::Set (CEquat_User *p_eqnUser, const CBfc_String &str_equation)
{
	m_str_equation = str_equation;
	Legalize_Equation (m_str_equation);
	if (p_eqnUser)
		m_p_eqnUser = p_eqnUser;
}

void CEquat::Set_Legalized (const CBfc_String &str_equation)
{
	m_str_equation = str_equation;
}

void CEquat::Get (CBfc_String &csEqn)
{
	csEqn = m_str_equation;
}

double CEquat::Calculate()
{
	return equat_legalized(m_str_equation);
}

double CEquat::equat (CBfc_String &cs_eqn)
{
	Legalize_Equation(cs_eqn);
	return equat_legalized(cs_eqn);
}

bool CEquat::Legalize_Equation (CBfc_String &cs_eqn)
{
	cs_eqn.RemoveWhitespace();
	cs_eqn.ToUpperCase();
	return true;
}

double CEquat::equat_legalized(const CBfc_String &cs_eqn)
{
	double f = gaval (cs_eqn.GetPtr(),cs_eqn.GetLength()-1);
#ifdef debug
	printf ("Equat %f\n",f);
#endif
	return (f);
}

double CEquat::gaval (character *e,const int i)
{
	int c,n;

	c = i;
	while (e[--c] != '(')
	{
		if (e[c] == ')')
		{
			n = findopen (e,c);
			m_regs[n] = (gaval (e, c));
			c = n;
		}
		else
			if (type (e[c]) == OPERATOR)
				m_regs[c+1] = (varval (e,c+1));
		if (c==0)
		{
#ifdef debug
			printf ("  Gaval ERROR (no open parenthesis) - %d (%c) : %d\n", c, e[c], m_regs[c]);
#endif
			break;
		}
	}
	m_regs[c] = (varval (e, c+1));
#ifdef debug
	printf ("Gaval at %d (%c) : %d\n", c, e[c], m_regs[c]);
#endif
	return (m_regs[c]);
}

int CEquat::findopen (character *e,const int c) const
{
	int i=c;
	while (e[--i] != '(')
		if (e[i] == ')')
			i = findopen (e,i);
	return (i);
}

int CEquat::findclose (character *e,const int c) const
{
	int i=c;
	while (e[++i] != ')')
		if (e[i] == '(')
			i = findclose (e,i);
	return (i);
}

double CEquat::varval (character *e,const int c)
{
	double var;
	character ch;
	int i=c;

	if (e[i] == '(')
	{
		var = m_regs[i];
		i = findclose (e,i)+1;
	}
	else if (type (e[i]) == DIGIT)
	{
		var = (myatof (e+i));
		do {
			ch = e[++i];
			if (type(ch) == OPERATOR || ch==')') break;
		} while (ch);

//		while ((type (e[++i]) != OPERATOR) && (e[i] != ')') && e[i]);
	}
	else if (type (e[i+2]) == LETTER)
	{
		var = (myfunct (e, i));
		while (e[++i] != '(' );
		i = findclose (e, i)+1;
	}
	else
	{
		var = (m_p_eqnUser->isvar (e,i));
		do {
			ch = e[++i];
			if (type(ch) == OPERATOR || ch==')') break;
		} while (ch);
	}
	if (type (e[i]) == OPERATOR)
	{
		var = (oper (var, m_regs[i+1], e[i]));
#ifdef debug
		printf ("Oper %f at %d (%c)\n", var, i, e[i]);
#endif
	}
#ifdef debug
	printf ("Varval at %d-%d (%c) : %d\n",c , i, e[i], var);
#endif
	return (var);
}


double CEquat::myatof (character *a) const
{
	character pb[20];
	int c = 0;

	while (type (a[c]) == DIGIT)
	{
		pb[c] = a[c];
		c++;
	}
	pb[c] = '\0';
#ifdef debug
	printf ("Myatof %s = %f\n", pb, atof (pb));
#endif
	return SBFC_Character::StringToDouble(pb);
}

//
double CEquat::myfunct (character *e, int i) const
{
	CBfc::STRING	func_src(e);
	CBfc::STRING	func_name;
	double			r_val;

	int end = func_src.Find ('(', i);
	if (end>0)
	{
		func_name = func_src.Mid (i, end-1);
		func_name.ToUpperCase();
		i = end;
	}
	if (func_name == _TXT("LOG"))
		r_val = (log (m_regs[i]));
	else if (func_name == _TXT("LOG10"))
		r_val = (log10 (m_regs[i]));
	else if (func_name == _TXT("SIN"))
		r_val = (sin (m_regs[i]));
	else if (func_name == _TXT("COS"))
		r_val = (cos (m_regs[i]));
	else if (func_name == _TXT("ABS"))
		r_val = (fabs (m_regs[i]));
	else if (func_name == _TXT("EXP"))
		r_val = (exp (m_regs[i]));
	else 
		r_val = m_p_eqnUser->myfunct(func_name,e,i);
	return ((r_val));
}


double CEquat::constant (const character c)
{
	if (c == 'e')
		return ((double)2.7182818);
	if (c == 'P')		// PI
		return ((double)3.14159265358979324);
	return ((double)0);
}

double CEquat::oper (const double n, const double d, const character o) const
{
	switch (o)
	{
		case '+':
			return (n+d);
		case '-':
			return (n-d);
		case '*':
			return (n*d);
		case '/':
			return (n/d);
		case powchr:
			return (power (n,d));
	}
	return ((double)0);
}

double CEquat::power (const double x,const double y) const		/* returns x to the y	*/
{
	double r=x;
	for (int c=1; c<y; c++)
		r *= x;
	return (r);
}


CEquat::EType CEquat::type (const int c)
{
//	cytpe::is(punct)
	if ((c >= '0' && c <= '9') || c == '.')
		return (DIGIT);
	else if (c == ' ' || c == '\t')
		return (SPACE);
	else if (c == '+' || c == '-' || c == '/' || c == '*' || c == powchr)
		return (OPERATOR);

	const int tc = SBFC_Character::UpperCase (c);
	if (tc >= 'A' && tc <= 'Z')
		return (LETTER);
	else
		return (CEquat::EType)(tc);
}

bool CEquat::is_digit (const int c) const
{
	return ((c >= '0' && c <= '9') || c == '.' || c == '-');
}


}

