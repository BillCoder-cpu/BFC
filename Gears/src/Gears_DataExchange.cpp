//*/
/*
					Gears_DataExchange.cpp : 
	
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

#include "Gears.h"

namespace AppGears
{
DataExchange::DataExchange()
{
}

// fill in the exchange with the deaults in the DS
DataExchange::DataExchange(DataSource *pDS)
{
}

}




///--------------------------------------------------
/**
  Here, the real idea is to have each DX have a little script associated with it that defines the UI fields
and their defaults.   Defaults can also be saved in the registry, explicitly in C++, perhaps script too.

Script Example:
	UINT HUE=20, LIGHTNESS=25;
	Distance DISTANCE=1 foot;
	Checkbox PICKUP_OBJECT_CHECK=true, DISTANCE_CHECK,PERMEATE_CHECK, HUE_CHECK=true, LIGHTNESS_CHECK=true;

- OR - pull the above from the complete dialog text, which we already support, then
there would be no need for a dialog definition in the resource, it would ride around with the DX:

		Start Window WandOptions
			Matrix Size(2,2)
			Button PICKUP_OBJECT_CHECK Checkbox "Pick Up an Object"
			Button PERMEATE_CHECK Checkbox "Permeate"
			
			Matrix Size(2,0)
			Button DISTANCE_CHECK Checkbox "Distance within"
			Textbox DISTANCE Distance Size(13,1) "2 inches"
			
			Matrix Size(2,0)
			Button HUE_CHECK Checkbox Checked "Hue within"
			Textbox HUE Percent Size(3,1) "22%"
			
			Matrix Size(2,0)
			Button LIGHTNESS_CHECK Checkbox Checked "Lightness within"
			Textbox LIGHTNESS Percent Size(3,1) "23%"
			
			Button OK "OK"
			Button CANCEL "Cancel"
		End WandOptions

 */

DX::DX()
 : m_pFieldList(NULL)
	, m_numFields(0)
{
}

DX::~DX()
{
	BFC_RELEASE (m_pFieldList);
}

OVERRIDE bool DX::CreateTable(char *p_ScriptText)
{
	if (p_ScriptText)
	{
/*
Script Example:
		UINT HUE=20, LIGHTNESS=25;
		Distance DISTANCE=1 foot;
		Checkbox PICKUP_OBJECT_CHECK=true, DISTANCE_CHECK,PERMEATE_CHECK, HUE_CHECK=true, LIGHTNESS_CHECK=true;
*/	
	}
	return false;
}

void DX::SetFieldAddress(SDXEntry *pList, const STRING &csName, void *ptr)
{
	UINT	uIndex=0;
	while (1)
	{
		if (csName == pList[uIndex].field_name)
		{
			pList[uIndex].field_ptr = ptr;
			return;
		}
		uIndex++;
	}
}

OVERRIDE bool DX::CreateTable(const SDXEntry *dxList, const UINT numFields)
{
	m_numFields=numFields;
	m_pFieldList = new SDXEntry[m_numFields];

	memcpy (m_pFieldList, dxList, numFields*sizeof(SDXEntry));
	for (UINT uIndex=0;uIndex<m_numFields;uIndex++)
	{
		SDXEntry *pFieldEntry = &m_pFieldList[uIndex];
		if (pFieldEntry->field_ptr == NULL)
		{
			pFieldEntry->b_allocated = true;
			switch (pFieldEntry->field_type)
			{
				case DX_UINT:
					pFieldEntry->field_ptr = new UINT;
					break;
				case DX_DISTANCE:
					pFieldEntry->field_ptr = new Distance;
					break;
				case DX_BUTTONCHECK:
					pFieldEntry->field_ptr = new bool;
					break;
			}
		} else
			pFieldEntry->b_allocated = false;
	}
}


bool DX::RegistrySave (GUI *p_GUI, const STRING *p_csRegistryName) const
{
	if (m_pFieldList)
	{
		if (!p_csRegistryName)
			p_csRegistryName = &m_csRegistryName;
		
		CBfcOS::Registry 	reg(p_GUI, *p_csRegistryName);

		UINT	uIndex=0;
		while (m_pFieldList[uIndex].field_name)
		{
			switch (m_pFieldList[uIndex].field_type)
			{
				case DX_UINT:
					reg.SetUINT(m_pFieldList[uIndex].field_name, *((UINT*)m_pFieldList[uIndex].field_ptr));
					break;
				case DX_DISTANCE:
					break;
				case DX_BUTTONCHECK:
				{
					const UINT	u = *((bool*)m_pFieldList[uIndex].field_ptr);
					reg.SetUINT(m_pFieldList[uIndex].field_name, u);
					break;
				}
			}
			uIndex++;
		}
		return true;
	}
	return false;
}

bool DX::RegistryLoad	(CBfcGUI::GUI *p_GUI, const STRING *p_csRegistryName)
{
	if (m_pFieldList)
	{
		if (!p_csRegistryName)
			p_csRegistryName = &m_csRegistryName;

		CBfcOS::Registry 	reg(p_GUI, *p_csRegistryName);

		UINT	u;
		UINT	uIndex=0;
		while (m_pFieldList[uIndex].field_name)
		{
			switch (m_pFieldList[uIndex].field_type)
			{
				case DX_UINT:
					reg.GetUINT(m_pFieldList[uIndex].field_name, u, 0); 
					*((UINT*)(m_pFieldList[uIndex].field_ptr)) = u;
					break;
				case DX_BUTTONCHECK:
					reg.GetUINT(m_pFieldList[uIndex].field_name, u, 0);
					*((bool *)(m_pFieldList[uIndex].field_ptr)) = u;
					break;
				case DX_DISTANCE:
					break;
			}
			uIndex++;
		}
		return true;
	}
	return false;
}

bool	DX::GetMemberBool (const CBfc::STRING &sName) const
{
	bool bRval=false;
	GetSetCheck(sName,bRval);
	return bRval;
}

UINT	DX::GetMember (const CBfc::STRING &sName) const
{
	UINT uRval=false;
	GetSetUINT(sName,uRval);
	return uRval;
}

/*
bool	DX::GetMember (const CBfc::STRING &sName, UINT &value) const
{
return false;
}

bool	DX::GetMember (const CBfc::STRING &sName, bool &value) const
{
return false;
}

bool	DX::GetMember (const CBfc::STRING &sName, Distance &value) const
{
return false;
}
*/
OVERRIDE void DX::GetSetCheck (const STRING &csName, bool &bCheck, const bool bSet) const
{
	int	Index=LocateField (csName);
	if (Index>=0)
	{
		if (m_pFieldList[Index].field_type == DX_BUTTONCHECK)
		{
			bool	*p_b = (bool *)m_pFieldList[Index].field_ptr;
			if (bSet)
				*p_b = bCheck;
			else
				bCheck = *p_b;
			return;
		}
	}
}

void	DX::GetSetUINT (const STRING &csName, UINT &u, const bool bSet) const
{
	int	Index=LocateField (csName);
	if (Index>=0)
	{
		switch (m_pFieldList[Index].field_type)
		{
			case DX_UINT:
			{
				UINT	*p_u = (UINT *)m_pFieldList[Index].field_ptr;
				if (bSet)
					*p_u = u;
				else
					u = *p_u;
			}
		}
	}
}


OVERRIDE void DX::GetSetText (const STRING &csName, STRING &csText, const bool bSet) const
{
	int	Index=LocateField (csName);
	if (Index>=0)
	{
		switch (m_pFieldList[Index].field_type)
		{
			case DX_UINT:
			{
				UINT	*p_u = (UINT *)m_pFieldList[Index].field_ptr;
				if (bSet)
				{
					Value	v;
					v.SetFromString (csText);
					*p_u = v.GetValue_UINT();
				} else
					csText.Format ("%d", *p_u);
				break;
			}
			case DX_DISTANCE:
			{
				Distance	*p_dist = (Distance *)m_pFieldList[Index].field_ptr;
				if (bSet)
					p_dist->SetFromString (csText);
				else
					p_dist->GetAsString (csText);
				break;
			}
		}
		return;
	}
}

int	DX::LocateField(const STRING &csName) const
{
	if (m_pFieldList)
	{
		UINT	uIndex=0;
		while (uIndex < m_numFields)
		{
			if (csName == m_pFieldList[uIndex].field_name)
				return (int)uIndex;
			uIndex++;
		}
	}
	return -1;
}



UINT DX::StringToUINT (const STRING &p_s) const
{
	Value	value;
	value.SetFromString (p_s);
	return value.GetValue_UINT();
}

double DX::StringToDouble (const STRING &p_s) const
{
	Value	value;
	value.SetFromString (p_s);
	return value.GetValue_double();
}

STRING DX::DoubleToString (const double d) const
{
	Value	val(d);
	STRING	cs_rval;
	val.RenderToString(cs_rval);
	return cs_rval;
}

STRING DX::UINTToString (const UINT u) const
{
	Value	val(u);
	STRING	cs_rval;
	val.RenderToString(cs_rval);
	return cs_rval;
}





