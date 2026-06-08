//*/
/*
					CBfcData_Archive_Field.h : 
	
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

BFC_DATA_CLASS Archive_Field_Header			// : public Archive_Record_Header
{
public:
    typedef enum tagBCE_RETURNVALUE
	{
		VALUE,
		STRING,
		DATE,
		FILENAME,
		RECORD
	} EBFC_ARCHIVE_FIELDTYPE;

	bool SetFieldType (const EBFC_ARCHIVE_FIELDTYPE eType) {
									m_fieldType = eType;
									return true;
								}
	EBFC_ARCHIVE_FIELDTYPE  GetFieldType() const {
									return m_fieldType;
								}

	bool SetFieldName (const CBfc_String &cs_name) {
									m_cs_fieldName = cs_name;
									return true;
								}
	bool GetFieldName (CBfc_String &cs_name) const {
									cs_name = m_cs_fieldName;
									return true;
								}
	void operator = (const Archive_Field_Header &otherHeader);
//	virtual bool	IsARecord();
private:
	EBFC_ARCHIVE_FIELDTYPE	m_fieldType;
    CBfc_String				m_cs_fieldName;
};


BFC_DATA_CLASS Archive_Field
{
public:
//	bool SetName (const CBfc_String &cs_name);
//	bool GetName (CBfc_String &cs_name) const;		// u
	bool GetDataAsString(CBfc_String &) const;
	bool SetDataAsString(CBfc_String &);
protected:
private:
//	Archive_Field_Header		*m_p_fieldHeader;
	long						m_l_dataLength;
	bool						m_b_compressed;			//
//	CBfc_ReferencedPointer		*m_p_data;
	CBfc_ReferencedAllocation	*m_p_data;
};

}


