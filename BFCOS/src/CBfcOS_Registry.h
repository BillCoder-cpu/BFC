//*/
/*
					CBfcOS_Registry.h : 
	
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

namespace CBfcOS {


BFC_OS_CLASS Registry
{
public:
	Registry (CBfcGUI::GUI *p_GUI, const CBfc_String &section);
	virtual ~Registry();

	bool SetUINT(const CBfc_String &key, const UINT U);
	bool GetUINT(const CBfc_String &key, UINT &rU, const UINT defaultU) const;

	bool SetValue(const CBfc_String &key, const CBfc_Value &value);
	bool GetValue(const CBfc_String &key, CBfc_Value &rValue, const CBfc_Value &defaultValue) const;

	bool SetString(const CBfc_String &key, const CBfc_String &value);
	bool GetString(const CBfc_String &key, CBfc_String &rval, const CBfc_String &defaultValue) const;
private:
	CBfcGUI::GUI	*m_p_GUI;
	char			*m_p_section;
};

}
