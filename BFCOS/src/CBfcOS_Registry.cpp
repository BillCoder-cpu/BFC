//*/
/*
					CBfcOS_Registry.cpp : 
	
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

#include <BFC/BFCOS.h>

#include <fx.h>

namespace CBfcOS {

Registry::Registry (CBfcGUI::GUI *p_GUI, const CBfc_String &section)
	: m_p_GUI(p_GUI)
{
//	using namespace FX;

	FXApp	*foxapp = (FXApp*)m_p_GUI->GetAppLayerPtr();
	FXbool	asciiMode=true;
	foxapp->reg().setAsciiMode  (asciiMode);
	m_p_section = section.MakeAsciiBuffer();
}

Registry::~Registry()
{
	BFC_RELEASE_ARRAY (m_p_section);
}

bool Registry::SetUINT(const CBfc_String &key, const UINT U)
{
	FXApp	*foxapp = (FXApp*)m_p_GUI->GetAppLayerPtr();
	char	*p_key = key.MakeAsciiBuffer();
 	FXbool bRval = foxapp->reg().writeUnsignedEntry(m_p_section,p_key, U);
//	FXbool bRval = foxapp->reg().writeUIntEntry(m_p_section,p_key, U);
	delete[] p_key;
	return bRval != 0;
}

bool Registry::GetUINT(const CBfc_String &key, UINT &rU, const UINT defaultU) const
{
	FXApp	*foxapp = (FXApp*)m_p_GUI->GetAppLayerPtr();
	char	*p_key = key.MakeAsciiBuffer();
	if (p_key)
	{
		rU = foxapp->reg().readUnsignedEntry(m_p_section, p_key, defaultU);
//		rU = foxapp->reg().readUIntEntry(m_p_section, p_key, defaultU);
		delete[] p_key;
	}
	return true;
}

bool Registry::SetValue(const CBfc_String &key, const CBfc_Value &value)
{
	return false;
}

bool Registry::GetValue(const CBfc_String &key, CBfc_Value &rValue, const CBfc_Value &defaultValue) const
{
	return false;
}

bool Registry::SetString(const CBfc_String &key, const CBfc_String &value)
{
	FXApp	*foxapp = (FXApp*)m_p_GUI->GetAppLayerPtr();
	FXbool bRval = false;
	
	char	*p_key = key.MakeAsciiBuffer();
	char	*p_value = value.MakeAsciiBuffer();
	if (p_key && p_value)
	{
		bRval = foxapp->reg().writeStringEntry(m_p_section,p_key, p_value);
		delete[] p_key;
		delete[] p_value;
	}
	return bRval != 0;
}

bool Registry::GetString(const CBfc_String &key, CBfc_String &rval, const CBfc_String &defaultValue) const
{
	FXApp	*foxapp = (FXApp*)m_p_GUI->GetAppLayerPtr();
	char	*p_key = key.MakeAsciiBuffer();
	char	*p_default = defaultValue.MakeAsciiBuffer();
    const FXchar *p_val = foxapp->reg().readStringEntry(m_p_section,p_key,p_default);

	if (p_val)	// Put this (p_val) into character format.
	{
		SBFC_Character::UTF8toUF16 (p_val, rval.GetBuffer(512));
		rval.ReleaseBuffer();
	} else
		rval = defaultValue;

	delete[] p_key;
	delete[] p_default;
	return true;
}



}

