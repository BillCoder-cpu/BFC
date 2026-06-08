//*/
/*
					CBfcData_Archive_Field.cpp : 
	
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

#include <BFC/BFCData.h>
namespace CBfcData
{

void Archive_Field_Header::operator = (const Archive_Field_Header &otherHeader)
{
	SetFieldType (otherHeader.GetFieldType());

	CBfc_String	cs_name;
	if (otherHeader.GetFieldName(cs_name))
		SetFieldName (cs_name);
}


/*
bool Archive_Field::GetName (CBfc_String &cs_name) const
{
	cs_name = 
	return true;
}
*/
bool Archive_Field::GetDataAsString(CBfc_String &string) const
{
	BYTEPTR					ptr;

	if (m_p_data->ReferenceAll (ptr))
	{
		string = (char *)ptr;
	    m_p_data->DeReferenceBytes (ptr);
		return true;
	}
	return false;
}

bool Archive_Field::SetDataAsString(CBfc_String &cs)
{
	return m_p_data->SetToData ((const void *)(character*)cs.GetPtr(), cs.GetLengthBytes ());
}
//
//	long					m_l_dataLength;
//	bool					m_b_compressed;			//

}


