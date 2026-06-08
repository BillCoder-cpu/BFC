//*/
/*
					CBfc_Distance.h : 
	
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

namespace CBfc {

BFC_CLASS Distance : public Value
{
public:
	typedef enum BFC_API tagEBFC_DistanceUnits {
		EBFC_DISTANCEUNIT_UNIT,				//	a pixel, its logical size depends on the resolution
		EBFC_DISTANCEUNIT_POINT,			//	72   points per inch
		EBFC_DISTANCEUNIT_INCH,
		EBFC_DISTANCEUNIT_FOOT,				//	12   inches per foot
		EBFC_DISTANCEUNIT_YARD,				//	36   inches per yard
		EBFC_DISTANCEUNIT_MILE,				//	5280 feet per mile
		EBFC_DISTANCEUNIT_MICRON,
		EBFC_DISTANCEUNIT_MILLIMETER,		//	
		EBFC_DISTANCEUNIT_CENTIMETER,		//	10   mm     per cm
		EBFC_DISTANCEUNIT_DECIMETER,		//	100  mm     per dm
		EBFC_DISTANCEUNIT_METER,			//	1000 mm     per me
		EBFC_DISTANCEUNIT_KILOMETER,		//	1000 mm     per me
		EBFC_DISTANCEUNIT_LIGHTYEAR			//
    } EBFC_DistanceUnits;

	virtual ~Distance ();
	Distance ();
	Distance (const Value &value, const EBFC_DistanceUnits units);
	EBFC_DistanceUnits GetUnits () const {
		return m_distanceUnits;
	}
	bool Set (const Value &value, const EBFC_DistanceUnits units);
	void GetAsString(STRING &sDesc) const;
	bool SetFromString(const STRING &sDesc);
private:
	EBFC_DistanceUnits	m_distanceUnits;
};


}






