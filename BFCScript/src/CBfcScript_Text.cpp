//*/
/*
					CBfcScript_Text.cpp : 
	
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
#define ANSI
#include <stdarg.h>
#include <string.h>
/*******************************************************************/

namespace CBfcScript
{

Script_Text::Script_Text ()
{
	Constructor ();
}

Script_Text::Script_Text (Script_Text &bfc_text_stream)
	: CBfc_Stream (bfc_text_stream)
{
	Constructor ();
	m_u_BytesPerCharacter = bfc_text_stream.GetBytesPerCharacter();
}

Script_Text::Script_Text (CBfc_Stream &bfc_stream)
	: CBfc_Stream (bfc_stream)
{
	Constructor ();
}

Script_Text::Script_Text (const CBfc::Filename &bfc_filename, const bool b_ReadOnly)
	: CBfc_Stream(bfc_filename, b_ReadOnly, false)
{
	Constructor ();
}

void Script_Text::Constructor (void)
{
	m_b_SkippingLinefeeds=false;
	m_uLineNumber=0;
// 	m_p_InputBuffer = NULL;
	m_u_BufferIndex = m_u_CharsInBuffer = 0;
	m_u_BytesPerCharacter = sizeof(character);
	m_MaxLineLength = BFCSCRIPT_MAX_LINELENGTH;
	DetectBytesPerCharacter();
			// utilitze m_u_BytesPerCharacter
	m_p_InputBuffer = new character[BFCSCRIPT_TEXT_BUFFERCHARS];
}


Script_Text :: ~Script_Text ()
{
	BFC_RELEASE_ARRAY (m_p_InputBuffer);
// 	EmptyBuffer();
}

OVERRIDE bool Script_Text::OnAttach()
{
	if (Stream::OnAttach())
	{
		DetectBytesPerCharacter();
		return true;
	}
	return false;
}

bool Script_Text::ClearBuffer()
{
	__uint64		newpos;
	return Seek (Tell(), SEEK_SET, &newpos);	// seek empties the buffer for you.
}

void Script_Text::EmptyBuffer()
{
	m_u_BufferIndex = m_u_CharsInBuffer = 0;
}

bool Script_Text::Seek(const INT64& n64Offset, const unsigned int uSeekType, __uint64* pun64NewPosition)
{
	const bool b_rval = CBfc_Stream::Seek (n64Offset, uSeekType, pun64NewPosition);
	if (b_rval)
		EmptyBuffer();
	return b_rval;
}

__uint64 Script_Text::Tell()
{
	UINT64	urval = CBfc_Stream::Tell();
	urval -= ((m_u_CharsInBuffer - m_u_BufferIndex) * m_u_BytesPerCharacter);
	return urval;
}


// Returns the number of bytes in each character, or 0 if non detectable.
//  Also sets the internal knowledge of this value
//   takes a sample of the existing stream.
// Assumes ability to read from this stream
UINT Script_Text::DetectBytesPerCharacter()
{
	char	pad[16];
	UINT	u_BytesPerCharacter = 0;
	UINT	u_BytesRead;

	if (IsAttached() && ReadAhead(pad, 4, &u_BytesRead))
	{
		if (u_BytesRead == 4)
		{
			if (pad[0] != 0)
			{
				if (pad[3] == 0)
				{
					if (pad[2] == 0)
						u_BytesPerCharacter = 4;
					else
						u_BytesPerCharacter = 2;
				} else
				{
					u_BytesPerCharacter = 1;
				}
			}
		}
	}
	if (u_BytesPerCharacter > 0)
		m_u_BytesPerCharacter = u_BytesPerCharacter;
	return u_BytesPerCharacter;
}

void Script_Text::SetBytesPerCharacter(const UINT u_BytesPerCharacter)
{
	m_u_BytesPerCharacter = u_BytesPerCharacter;
}

bool Script_Text::WriteLine (const CBfc_String &cs)
{
	if (cs.GetLength() ==  0 || Write(cs.GetPtr()))
		return Write ("\n");
	return false;
}

bool Script_Text::WriteLine (const CHARACTER_PTR lpszFormat, ...)
{
	CBfc_String string;
	if (lpszFormat && *lpszFormat)
	{
		va_list argList;

		va_start (argList, lpszFormat);
		string.FormatV (lpszFormat, argList);
		va_end (argList);
	}

	string += _TXT("\n");
	m_uLineNumber++;
	return Write (string); // (void *)cp_out, u_bytesout);
}

bool Script_Text::Write (const CHARACTER_PTR lpszFormat, ...)
{
#if 1
	CBfc_String string;
	if (lpszFormat && *lpszFormat)
	{
		va_list argList;

		va_start (argList, lpszFormat);
		string.FormatV (lpszFormat, argList);
		va_end (argList);
	}
	return Write (string); // (void *)cp_out, u_bytesout);
#else
	va_list list;
 
	va_start (list, string);
	vaEnumValue = va_arg (list, char *);
	while (vaEnumValue != -1)
	{
		vaEnumValue = va_arg (list, char *);
	}
	va_end(argList);
#endif
}

bool Script_Text::Write_Tabbified (const CBfc_String &text)
{
	UINT	uIndex = 0;
	int		iNext;

	while (uIndex<text.GetLength())
	{
		Write("\t");
		iNext = text.Find ('\n',uIndex);
		if (iNext < 0)
			return Write (text.RightFrom(uIndex));
		if (!Write (text.Mid (uIndex, iNext)))
			return false;
		uIndex = iNext+1;
	}
	return true;
}


bool Script_Text::ReadLine (CBfc_String &s)
{
	character LineBuffer[4096];
	bool b_Rval;
	 
	do {
		b_Rval = ReadLine (LineBuffer, m_MaxLineLength);
		s = LineBuffer;
		if (!SkippingLinefeeds())
			s += '\n';
	} while (b_Rval && s.IsEmpty());
	return b_Rval;
}


#define	END_OF_FILE	6

bool Script_Text::ReadLine (characterPtr szDestBuf, const unsigned int uMaxBufLen)
{
	character	c;
	UINT		u_CharsRead = 0;
	while (u_CharsRead < uMaxBufLen-1)
	{
		try {
			c = NextCharacter(true);
			if (c == '\r')
			{
				c = NextCharacter(false);
				if (c == '\n')
					continue;
				c = '\n';
			}
		} catch (CBfc::Exception &e)
		{
			if (e.GetType() == CBfc::Exception::EBFC_EXC_END_OF_FILE)
			{
				*szDestBuf = 0;
				return (u_CharsRead > 0);
			}
			throw (e);
		}
		
		if (c == '\n')
			break;
		*szDestBuf++ = c;
		u_CharsRead++;
	}
	*szDestBuf = 0;
	m_uLineNumber++;
	return true;
}

character Script_Text::NextCharacter(const bool bIncrement)
{
	if (m_u_BufferIndex >= m_u_CharsInBuffer)
	{
		if (!RefillBuffer())
			throw (CBfc::Exception(CBfc::Exception::EBFC_EXC_END_OF_FILE));
		m_u_BufferIndex = 0;
	}
	character c = m_p_InputBuffer[m_u_BufferIndex];
	if (bIncrement)
		m_u_BufferIndex++;
	return c;
}

// Read in another buffer
bool Script_Text::RefillBuffer()
{
	UINT	u_BytesInBuffer;
	if (!Read (m_p_InputBuffer, BFCSCRIPT_TEXT_BUFFERCHARS*m_u_BytesPerCharacter, &u_BytesInBuffer))
	{
		m_u_BufferIndex = m_u_CharsInBuffer = 0;
		return false;
	}
	m_u_CharsInBuffer = u_BytesInBuffer / m_u_BytesPerCharacter;
	if (m_u_BytesPerCharacter != sizeof(character))
	{
		switch (m_u_BytesPerCharacter)
		{
			case 1:		// Reading from Ascii stream - must expand
				SBFC_Character::Block_UTF8toCharacter ((char*)m_p_InputBuffer, m_p_InputBuffer, m_u_CharsInBuffer);
				break;
		}
	}
	return (m_u_CharsInBuffer > 0);
}

#if 0
// Utilize the number of bytes in the output stream -
//    Change the string to conform to this # of bytes
bool Script_Text::Write (const CBfc_String &cs)
{
	if (cs.IsEmpty())
		return true;

	char		pad[BFC_MAX_STRING_LENGTH];
	character	*cp_out = (character*)cs.GetPtr();
	UINT		u_bytesout = cs.GetLengthBytes();
	if (m_u_BytesPerCharacter != sizeof(character))
	{
		UINT len = SBFC_Character::StringLength(cp_out);
		if (len >= BFC_MAX_STRING_LENGTH-1)
			throw CBfc::Exception(CBfc::Exception::EBFC_EXC_STRING_LIMITATION);

		switch (m_u_BytesPerCharacter)
		{
			case 1:
				SBFC_Character::UTF16toUF8 (cp_out, pad);
				cp_out = (character*)pad;
				u_bytesout = strlen(pad);
				break;
		}
	}
	return CBfc_Stream::Write (cp_out, u_bytesout, NULL);
}
#else
bool Script_Text::Write (const CBfc_String &cs)
{
	if (cs.IsEmpty())
		return true;

	character	*cp_out = (character*)cs.GetPtr();
	UINT		u_bytesout;
	if (m_u_BytesPerCharacter == sizeof(character))
	{
		u_bytesout = cs.GetLengthBytes();
		return CBfc_Stream::Write(cp_out, u_bytesout, NULL);
	}
	switch (m_u_BytesPerCharacter)
	{
		case 1:
		{
//			CBfc::STRING8	cs8(cs);
			char *ascii = cs.MakeAsciiBuffer();
			u_bytesout = CBfc::STRING::bfc_strlen(ascii);
			cp_out = (character*)ascii;
			bool bRval = CBfc_Stream::Write (cp_out, u_bytesout, NULL);
			delete [] ascii;
			return bRval;
		}
	}
	return false;
}
#endif

bool Script_Text::AppendStreamWithSubstitution (Script_Text &stream, const CBfc::StringArray &substitute_array, const CBfc::StringArray &replace_array)
{
	CBfc_String			s_Buffer;

	while (stream.ReadLine (s_Buffer))
	{
		s_Buffer.Substitute(substitute_array,replace_array);
		if (stream.SkippingLinefeeds()) {
			if (!WriteLine (s_Buffer))	return false;
		} else	{
			if (!Write (s_Buffer))	return false;
		}
	}
	return true;
}

} // namespace


