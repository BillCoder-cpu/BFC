//*/
/*
					CBfc_Distance.cpp : 
	
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

namespace CBfc {

character *DistanceNames[] = 
{
	_TXT("Units"), _TXT("Points"), _TXT("Inches"), _TXT("Feet"), _TXT("Yards"),
	_TXT("Miles"), _TXT("Microns"), _TXT("mm"), _TXT("cm"), _TXT("decimeters"),
	_TXT("meters"), _TXT("km"), _TXT("LightYears")
};

Distance::Distance ()
{
	m_distanceUnits=EBFC_DISTANCEUNIT_UNIT;
}

Distance::~Distance()
{
}

Distance::Distance (const Value &value, const EBFC_DistanceUnits units)
	: Value (value)
	, m_distanceUnits (units)
{
}

bool Distance::Set (const Value &value, const EBFC_DistanceUnits units)
{
	Value::SetValue(value);
	m_distanceUnits = units;
	return true;
}

bool Distance::SetFromString(const STRING &sDesc)
{
	Value	value;
	value.SetFromString (sDesc);
	Value::SetValue(value);
	EBFC_DistanceUnits units = EBFC_DISTANCEUNIT_INCH;
	m_distanceUnits = units;
	return true;
}

void Distance::GetAsString(STRING &sDesc) const
{
	const double	dVal=GetValue_double();
	const UINT		uNameIndex=(UINT)m_distanceUnits;
	
	switch (m_distanceUnits)
	{
		case EBFC_DISTANCEUNIT_INCH:
			if (dVal >= 12)
			{
				UINT	feet = (UINT)(dVal/12);
				double	inches = dVal - (feet * 12);
				sDesc.Format(_TXT("%d %s, %f %s"), feet, DistanceNames[EBFC_DISTANCEUNIT_FOOT], inches, DistanceNames[uNameIndex]);
				break;
			}// Fall thru
		default:
			sDesc.Format(_TXT("%f %s"),dVal, DistanceNames[uNameIndex]);
			break;
	}
}



}
