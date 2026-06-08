//*/
/*
					CBfc_Angle.cpp : 
	
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

*/

#include <BFC/BFC.h>

CBfc_Angle::CBfc_Angle ()
	:m_units (AngleUnits_Degrees)
{
}


void CBfc_Angle::SetInDegrees (const CBfc_Value &NewValue)
{
	SetValue (NewValue);
	m_units = AngleUnits_Degrees;
}

void CBfc_Angle::SetInRadians (const CBfc_Value &NewValue)
{
	SetValue (NewValue);
	m_units = AngleUnits_Radians;
}

void CBfc_Angle::GetInDegrees (CBfc_Angle &DestAngle) const
{
	DestAngle = *this;
}

void CBfc_Angle::GetInRadians (CBfc_Angle &DestAngle) const
{
	DestAngle = *this;
}

#define	RADIAN_MULTIPLIER		1.0
#define	DEGREE_MULTIPLIER		(180.0 / 3.14159265358)

void CBfc_Angle::GetInDegrees (CBfc_Value &DestValue) const
{
	switch (m_units)
	{
		case AngleUnits_Degrees:
			DestValue.SetValue (*(CBfc_Value*)this);
			break;
		case AngleUnits_Radians:
			DestValue.SetValue (GetValue_double()*DEGREE_MULTIPLIER/RADIAN_MULTIPLIER);
			break;
	}
}

void CBfc_Angle::GetInRadians (CBfc_Value &DestValue) const
{
	switch (m_units)
	{
		case AngleUnits_Degrees:
			DestValue.SetValue (GetValue_double()*RADIAN_MULTIPLIER/DEGREE_MULTIPLIER);
			break;
		case AngleUnits_Radians:
			DestValue.SetValue (*(CBfc_Value*)this);
			break;
	}
}

