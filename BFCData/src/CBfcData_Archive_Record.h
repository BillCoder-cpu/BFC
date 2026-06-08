//*/
/*
					CBfcData_Archive_Record.h : 
	
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

//#pragma once

namespace CBfcData
{

BFC_DATA_CLASS Archive_Table;

BFC_DATA_CLASS Archive_Record_Header
{
public:
  Archive_Record_Header(Archive_Table *p_ArchiveTable);
  virtual ~Archive_Record_Header();

	bool SetName (const CBfc_String &cs_name);
	bool GetName (CBfc_String &cs_name) const;				// 
	Archive_Field_Header &GetFieldHeader(const unsigned long uIndex) const;
private:
	CBfc_String							m_cs_RecordName;
	Archive_Table						*m_p_ArchiveTable;
	CBfc::Array <Archive_Field_Header>	m_ExtraFieldHeaders;
};

// A collection of fields
BFC_DATA_CLASS Archive_Record
{
public:
	bool SetName (const CBfc_String &cs_name);
	bool GetName (CBfc_String &cs_name) const;				// u
	bool GetIdentifierString (CBfc_String &cs_Id) const;	// Unique to this record.

	void Trash();	// Move to the recycling bin
	void Restore();	// Remove from recycling bin

	unsigned long  EnumerateFields() const;
	bool GetNextField(unsigned long &uNextIndex, Archive_Field &ArchiveField,
									Archive_Field_Header	**p_p_ArchiveFieldHeader=NULL) const;

	unsigned long GetFieldCount() const {
									return m_BaseFields.GetCountAsULONG()
											+ m_ExtraFields.GetCountAsULONG();
								}

	Archive_Field			&GetField(const unsigned long uIndex, Archive_Field_Header *p_Header=NULL) const;
	Archive_Field_Header	&GetFieldHeader(const unsigned long uIndex) const;
protected:
	unsigned long GetBaseFieldCount() const {
									return m_BaseFields.GetCountAsULONG();
								}
private:
	CBfc_String							m_cs_RecordIdentifier;
	Archive_Record_Header				*m_p_Header;

	CBfc::Array<Archive_Field>		m_BaseFields;
	CBfc::Array<Archive_Field>		m_ExtraFields;

// no!-    class Archive_Table  *m_p_motherArchiveTable;
};


}

