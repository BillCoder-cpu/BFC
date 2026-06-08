//*/
/*
					CBfcData_Archive_Record.cpp : 
	
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

Archive_Record_Header::Archive_Record_Header(Archive_Table *p_ArchiveTable)
	: m_p_ArchiveTable(p_ArchiveTable)
{
}

Archive_Record_Header::~Archive_Record_Header()
{
}

bool Archive_Record_Header::SetName (const CBfc_String &cs_name)
{
	m_cs_RecordName = cs_name;
	return true;
}

bool Archive_Record_Header::GetName (CBfc_String &cs_name) const
{
	cs_name = m_cs_RecordName;
	return true;
}

Archive_Field_Header &Archive_Record_Header::GetFieldHeader(const unsigned long uIndex) const
{
	ASSERT(m_p_ArchiveTable,"Archive_Record_Header::GetFieldHeader");
	const ULONG	ul_basecount = m_p_ArchiveTable->GetBaseFieldCount();
	if (uIndex < ul_basecount)
		return m_p_ArchiveTable->GetBaseFieldHeader(uIndex);
	else
		return *m_ExtraFieldHeaders[uIndex];
}
//--------------------------------------------------------------------------//


// Starts enumerating fields.
unsigned long Archive_Record::EnumerateFields() const
{
	return 0;
}

// Returns false after last field.
bool Archive_Record::GetNextField (unsigned long &uNextIndex, Archive_Field &ArchiveField, 
											Archive_Field_Header **p_p_ArchiveFieldHeader) const
{
	if (uNextIndex >= GetFieldCount())
		return false;
	if (p_p_ArchiveFieldHeader)
		*p_p_ArchiveFieldHeader = &GetFieldHeader(uNextIndex);
	ArchiveField = GetField(uNextIndex++);
	return true;
}

bool Archive_Record::SetName (const CBfc_String &cs_name)
{
	return m_p_Header->SetName(cs_name);
}

bool Archive_Record::GetName (CBfc_String &cs_name) const				// u
{
	return m_p_Header->GetName (cs_name);
}

bool Archive_Record::GetIdentifierString (CBfc_String &cs_Id) const	// Unique to this record.
{
	cs_Id = m_cs_RecordIdentifier;
	return true;
}

Archive_Field &Archive_Record::GetField(const unsigned long uIndex, Archive_Field_Header *p_Header) const
{
	if (p_Header)
		*p_Header = GetFieldHeader(uIndex);
	if (uIndex < GetBaseFieldCount())
		return *m_BaseFields[uIndex];
	else
		return *m_ExtraFields[uIndex];
}

Archive_Field_Header &Archive_Record::GetFieldHeader(const unsigned long uIndex) const
{
	ASSERT (m_p_Header,"Archive_Record::GetFieldHeader");
	return m_p_Header->GetFieldHeader(uIndex);
}


}
