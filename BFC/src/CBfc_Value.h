//*/
/*
					CBfc_Value.h : 
	
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
    CBfc_Value.h

      A Value in BFC is like the concept of  VARIANT arguments in COM - bSTR, etc.
*/

#ifndef _CBFC_Value_H__
#define _CBFC_Value_H__

#define	CBfc_Value	CBfc::Value

namespace CBfc {

BFC_CLASS MeasureUnit
{
	// Include Monetary (search)
};

BFC_CLASS STRING;

BFC_CLASS Value : public CBfc_Object
{
public:
    Value ();
    Value (const Value &value);
    Value (const double d);
    Value (const int i);
    Value (const unsigned int u);

	bool		SetFromString (const STRING &s);
	bool		RenderToString (STRING &str_out) const;

    double          GetValue_double (void) const;
    UINT             GetValue_UINT (void) const;
    bool             SetValue (const double d);
    bool             SetValue (const int i);
    bool             SetValue (const unsigned int u);
    bool             SetValue (const Value &value);
	
	operator 		void *() const;
	operator 		unsigned int() const;
	operator 		int() const;
	operator		double() const;
	
    bool operator    == (const Value &eqeqValue) const;
    CBfc_Value operator*(const Value &mulValue) const;
    CBfc_Value operator/(const Value &divValue) const;
    CBfc_Value operator+(const Value &addValue) const;
    CBfc_Value operator-(const Value &subValue) const;
    void operator *= (const Value &mulValue);
    void operator += (const Value &addValue);
    void operator -= (const Value &subValue);

    bool operator < (const Value &lessthanValue) const;
    bool operator <= (const Value &lessthanValue) const;
    bool operator > (const Value &greaterthanValue) const;
    bool operator >= (const Value &greaterthanValue) const;

private:
	MeasureUnit		m_MeasureUnit;
    double				m_d_value;
//    VARIANT     m_v_variant;
};

}


#endif // ifndef _CBFC_Value_H__


