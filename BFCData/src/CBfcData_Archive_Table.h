//*/
/*
					CBfcData_Archive_Table.h : 
	
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
  Te concept of
  the Archive has the capability to maintain records in compressed or uncompressed format

  Most recent records are cached,


	Archive - contains one or more Tables.
	Table - Has a base format that all records follow, and each record can have additional fields.
			Consists of one base table of fields and zero or more records.
	Record - has all of the base fields, plus optional additional fields.
*/


#ifndef _BFC_BCARCHIVE_TABLE_H_
#define  _BFC_BCARCHIVE_TABLE_H_

namespace CBfcData
{

BFC_DATA_CLASS Archive_Table : public CBfcDATA_Object
{
public:
	bool GetBaseFields ();	// variable sized fields have the lengths in the record header.
	bool GetRecord ();
	bool SetRecord ();
	bool SetCache (long i_numRecordsToCache);

	void Trash();
	void Restore();

	Archive_Field_Header &GetBaseFieldHeader(const unsigned long uIndex) const {
									return *m_Base_FieldHeaders[uIndex];
								}
	unsigned long GetBaseFieldCount() const {
									return m_Base_FieldHeaders.GetCountAsULONG();
								}

private:
	CBfc::Array<Archive_Field_Header>	m_Base_FieldHeaders;

	long														m_i_numRecordsToCache;
	CBfc::Array <Archive_Record>			m_recordCache;
	CBfc::Stream										*m_p_SourceStream;
	
	CBfc_CompressionAlgorythm				*m_p_CompressionAlgorythm;
};


//BCBestCompression	*m_p_CompressionAlgorythm;


}

#endif // ndef _BFC_BCARCHIVE_TABLE_H_

