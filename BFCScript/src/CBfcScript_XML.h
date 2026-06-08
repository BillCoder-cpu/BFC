//*/
/*
					CBfcScript_XML.h : 
	
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

namespace CBfcScript
{

BFC_CLASS Script_XML : public Script
{
public:
  Script_XML();
  Script_XML (CBfc_Stream &bfc_stream);
  virtual ~Script_XML() {}

//  bool	ReadScript(CBfc_DataArray &data);

  bool	WriteARecord (const CBfcData::Archive_Record &record);

    typedef enum BFC_API tagEBFCScript_XMLMark {
        EBFCScript_XMLMark_TAG_START,
        EBFCScript_XMLMark_ATTRIBUTE,
        EBFCScript_XMLMark_VALUE,
        EBFCScript_XMLMark_TAG_END,
		EBFCScript_XMLMark_EOF,
    } EBFCScript_XMLMark;

	bool ReadTagPairs(CBfc::StringMap2d &data);

	EBFCScript_XMLMark ReadNext(CBfc::STRING &s);
	bool ReadToTagEnd (const CBfc::STRING &s_tag);

	virtual inline bool Rewind()
				{
					m_b_withinTag = false;
					return Script::Rewind();
				}

	bool DumpXML ();
	bool WriteAnXMLTag (const CBfc::STRING &cs_FieldName, const CBfc::STRING &cs_FieldData);
private:
	EBFCScript_XMLMark ReadNext_Internal(CBfc::STRING &s);
	bool			WriteAField (const CBfcData::Archive_Field &ArchiveField, CBfcData::Archive_Field_Header *p_ArchiveFieldHeader);

	CBfc::STRING	m_s_currentTag;
	bool			m_b_withinTag;

	EBFCScript_XMLMark	m_last_mark;
	CBfc::STRING		m_last_string;
};

}






