//*/
/*
					CBfc_Angle.h : 
	
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
	CBfc_Angle.h

*/

BFC_CLASS CBfc_Angle : public CBfc_Value
{
public:
	CBfc_Angle ();
	enum EBFC_AngleUnits {
		AngleUnits_Radians,
		AngleUnits_Degrees,
	};

	void SetInDegrees (const CBfc_Value &NewValue);
	void SetInRadians (const CBfc_Value &NewValue);

	void GetInDegrees (CBfc_Angle &DestAngle) const;
	void GetInRadians (CBfc_Angle &DestAngle) const;

	void GetInDegrees (CBfc_Value &DestValue) const;
	void GetInRadians (CBfc_Value &DestValue) const;
protected:
private:
	EBFC_AngleUnits	m_units;
};



