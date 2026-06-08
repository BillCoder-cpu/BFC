//*/
/*
					CBfc_Value.cpp : 
	
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

#include <BFC/BFC.h>
#include <stdlib.h>

namespace CBfc {

Value :: Value () {
	m_d_value = 0;
}

Value :: Value (const double d) {
	SetValue(d);
}

Value :: Value (const Value &value) {
    SetValue (value);
}
Value :: Value (const int i) {
    SetValue (i);
}
Value :: Value (const unsigned int u) {
    SetValue (u);
}

Value :: operator 		void * () const
{
	return (void *)(long)m_d_value;
}

Value :: operator 		int () const
{
	return (int)m_d_value;
}

Value :: operator 		unsigned int () const
{
	return GetValue_UINT();
}

Value :: operator		double() const
{
	return GetValue_double();
}

bool Value :: operator    == (const Value &eqeqValue) const
{
    return m_d_value == eqeqValue.m_d_value;
}

Value Value :: operator*(const Value &mulValue) const
{
    const double  value = mulValue.m_d_value;
    return Value (m_d_value * value);
}

Value Value :: operator/(const Value &divValue) const
{
    const double  value = divValue.m_d_value;
    return Value (m_d_value / value);
}

Value Value :: operator+(const Value &addValue) const
{
    const double  value = addValue.m_d_value;
    return Value (m_d_value + value);
}

Value Value :: operator - (const Value &subValue) const
{
    return Value (m_d_value - subValue.m_d_value);
}

void Value :: operator *= (const Value &mulValue)
{
    const double  value = mulValue.GetValue_double ();
    m_d_value *= value;
}

void Value :: operator += (const Value &addValue)
{
    const double  value = addValue.GetValue_double ();
    m_d_value += value;
}

void Value :: operator -= (const Value &subValue)
{
    double  value = subValue.GetValue_double ();
    m_d_value -= value;
}

bool Value ::  operator < (const Value &lessthanValue) const
{
    return m_d_value < lessthanValue.m_d_value;
//     return  lessthanValue.m_d_value < m_d_value;
}

bool Value ::  operator <= (const Value &lessthanValue) const
{
    return m_d_value <= lessthanValue.m_d_value;
}

bool Value ::  operator > (const Value &greaterthanValue) const
{
    return m_d_value > greaterthanValue.m_d_value;
}

bool Value ::  operator >= (const Value &greaterthanValue) const
{
    return m_d_value >= greaterthanValue.m_d_value;
}


// Get in Variant form
double Value :: GetValue_double (void) const
{
    return m_d_value;
}

UINT Value :: GetValue_UINT (void) const
{
	return (UINT)(m_d_value + 0.5);		// Round off
}

bool Value :: SetValue (const Value &value)
{
	m_d_value = value.GetValue_double();
    return true;
}

bool Value :: SetValue (const double d)
{
	m_d_value = d;
    return true;
}

bool Value :: SetValue (const int i)
{
	m_d_value = i;
    return true;
}


bool Value :: SetValue (const unsigned int u)
{
	m_d_value = u;
    return true;
}

bool Value::RenderToString (CBfc_String &str_out) const
{
	return str_out.Format(_TXT("%g"), m_d_value);
}

bool Value::SetFromString (const CBfc_String &s)
{
	m_d_value = s.IsEmpty() ? 0.0: SBFC_Character :: StringToDouble(s.GetPtr());
	return true;
}

}
