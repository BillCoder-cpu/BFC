//*/
/*
					CBfcScript_XML.cpp : 
	
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


#include <BFC/BFCScript.h>
#ifdef	UNIX
#	include <wchar.h>
#endif
/*
	I really should be using a database class here.

	Here is an example XML database entry.

   <book id="bk101">
      <author>Gambardella, Matthew</author>
      <title>XML Developer's Guide</title>
      <genre>Computer</genre>
      <price>44.95</price>
      <publish_date>2000-10-01</publish_date>
      <description>An in-depth look at creating applications 
      with XML.</description>
   </book>
*/

namespace CBfcScript
{

Script_XML::Script_XML ()
	: m_b_withinTag (false)
	  , m_last_mark (EBFCScript_XMLMark_EOF)
{}

Script_XML::Script_XML (CBfc_Stream &bfc_stream)
  : Script (bfc_stream)
	  , m_b_withinTag (false)
	  , m_last_mark (EBFCScript_XMLMark_EOF)
{
}

bool Script_XML :: WriteARecord (const CBfcData::Archive_Record &ArchiveRecord)
{
	CBfc_String cs_Name, cs_Identifier;

	if (ArchiveRecord.GetName(cs_Name) && ArchiveRecord.GetIdentifierString(cs_Identifier))
	{
		if (WriteLine ((const CHARACTER_PTR)"<%s id=\"%s\">", cs_Name.GetPtr(), cs_Identifier.GetPtr()))
		{
			CBfcData::Archive_Field			ArchiveField;
			CBfcData::Archive_Field_Header	*p_ArchiveFieldHeader;

			unsigned long position = ArchiveRecord.EnumerateFields();
			while (ArchiveRecord.GetNextField(position, ArchiveField, &p_ArchiveFieldHeader));
				WriteAField (ArchiveField, p_ArchiveFieldHeader);		// Write out each field
			return WriteLine ((const CHARACTER_PTR)"</%s>", cs_Name.GetPtr());
		}
	}
	return false;
}

bool Script_XML :: WriteAField (const CBfcData::Archive_Field &ArchiveField, CBfcData::Archive_Field_Header *p_ArchiveFieldHeader)
{
	CBfc_String cs_FieldName, cs_FieldData;

	if (p_ArchiveFieldHeader && p_ArchiveFieldHeader->GetFieldName (cs_FieldName) && ArchiveField.GetDataAsString(cs_FieldData))
		return WriteAnXMLTag(cs_FieldName, cs_FieldData);
	return false;
}


bool Script_XML :: WriteAnXMLTag (const CBfc_String &cs_FieldName, const CBfc_String &cs_FieldData)
{
	CBfc_String	cs;

	cs.Format(_TXT("<%s>%s</%s>"), cs_FieldName.GetPtr(), cs_FieldData.GetPtr(), cs_FieldName.GetPtr());
	return WriteLine (cs.GetPtr());
//	return WriteLine ((const CHARACTER_PTR)"<%s>%s</%s>", cs_FieldName.GetPtr(), cs_FieldData.GetPtr(), cs_FieldName.GetPtr());
}

Script_XML::EBFCScript_XMLMark Script_XML :: ReadNext(CBfc_String &s)
{
//	m_last_mark = ReadNext(s);
//	if (m_last_mark == EBFCScript_XMLMark_TAG_END)	// Currently, The only one we need the string for.
//		m_last_string = s;
//	return m_last_mark;
//}
//
//
//Script_XML::EBFCScript_XMLMark Script_XML :: ReadNext_Internal(CBfc_String &s)
//{
	const character		Begin_deliminator(*_TXT("<"));
	const character		End_deliminator(*_TXT(">"));
	const character		Tag_Close(*_TXT("/"));
	character c;

//return EBFCScript_XMLMark_EOF;
	while (1)
	{
		if (!ReadAheadScript_Character(c))
			return EBFCScript_XMLMark_EOF;
		if (c == Tag_Close)
		{
			ReadScript_Character(c);
			s = CBfc_String(_TXT("/")) + m_s_currentTag;
			return EBFCScript_XMLMark_TAG_END;
		}

		if (m_b_withinTag)
		{
			if (c == End_deliminator)
			{
				ReadScript_Character(c);
				m_b_withinTag = false;
			} else
			{
				// These must be attributes
				if (!ReadScriptWord(s, CBfc_String(_TXT("> \t"))))
					return EBFCScript_XMLMark_EOF;
			    return EBFCScript_XMLMark_ATTRIBUTE;
			}
		} else
		{
			if (c == Begin_deliminator)
			{
				ReadScript_Character(c);
				if (!ReadAheadScript_Character(c))
					return EBFCScript_XMLMark_EOF;
				m_b_withinTag = true;
				if (c == Tag_Close)
				{
					if (!ReadScriptWord(s, CBfc_String(_TXT(">"))))
						return EBFCScript_XMLMark_EOF;
					return EBFCScript_XMLMark_TAG_END;
				} else
				{
					if (!ReadScriptWord(s, CBfc_String(_TXT("/> \t"))))
						return EBFCScript_XMLMark_EOF;
					m_s_currentTag = s;
					return EBFCScript_XMLMark_TAG_START;
				}
			} else
			{			// Everything in here is the current value:
				if (!ReadScriptWord(s, Begin_deliminator))
					return EBFCScript_XMLMark_EOF;
				return EBFCScript_XMLMark_VALUE;
			}
		}
	}
}

bool Script_XML::ReadToTagEnd (const CBfc_String &s_tag)
{
	CBfc_String			s_look = CBfc_String(_TXT("/")) + s_tag;

	// Check to see if it is already there.
	if (m_last_mark == EBFCScript_XMLMark_TAG_END && m_last_string == s_look)
		return true;

	CBfc_String			s;
	EBFCScript_XMLMark	mark;

	do
	{
		mark = ReadNext(s);
//		if (mark == EBFCScript_XMLMark_TAG_END && s == s_look)
//			return true;
	} while (mark != EBFCScript_XMLMark_EOF);
	return false;
}

bool Script_XML::ReadTagPairs(CBfc::StringMap2d &data)
{
	Script_XML::EBFCScript_XMLMark mark;
	CBfc_String	s;
	do
	{
		s.Empty();
		mark = ReadNext(s);
		switch (mark)
		{
			case Script_XML::EBFCScript_XMLMark_TAG_START:
				break;
			case Script_XML::EBFCScript_XMLMark_TAG_END:
				break;
			case Script_XML::EBFCScript_XMLMark_ATTRIBUTE:
				break;
			case Script_XML::EBFCScript_XMLMark_VALUE:
				{
//		CBfc_String	cs;
//		cs.Format(_TXT("adding key %s, value %s!\n"),m_s_currentTag.GetPtr(),s.GetPtr());
//		fwprintf (stderr, cs.GetPtr());
				}
				data.Add(m_s_currentTag, s);
				break;
		}
	} while (mark != Script_XML::EBFCScript_XMLMark_EOF);
	return true;
}

#ifdef _UNICODE_8
	#define tprintf	printf
#else
	#define tprintf	wprintf
#endif

// This routine is to dump out all of the tags as they are interpreted
//  - mainly for debugging this XML code.
bool Script_XML::DumpXML ()
{
	Script_XML::EBFCScript_XMLMark mark;
	CBfc_String	s;

	do
	{
		mark = ReadNext(s);
		tprintf (_TXT("Marker: "));
		switch (mark)
		{
			case Script_XML::EBFCScript_XMLMark_TAG_START:
				tprintf (_TXT("START-TAG"));
				break;
			case Script_XML::EBFCScript_XMLMark_TAG_END:
				tprintf (_TXT("END-TAG"));
				break;
			case Script_XML::EBFCScript_XMLMark_ATTRIBUTE:
				tprintf (_TXT("ATTRIB"));
				break;
			case Script_XML::EBFCScript_XMLMark_VALUE:
				tprintf (_TXT("VALUE"));
				break;
			case Script_XML::EBFCScript_XMLMark_EOF:
				tprintf (_TXT("EOF"));
				break;
		}
		tprintf (_TXT(". \"%s"), s.GetPtr());
		tprintf (_TXT("\"\n"));
	} while (mark != Script_XML::EBFCScript_XMLMark_EOF);
	return true;
}


}




