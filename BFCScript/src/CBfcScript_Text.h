//*/
/*
					CBfcScript_Text.h : 
	
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


#define BFCSCRIPT_MAX_LINELENGTH		4096
#define BFCSCRIPT_TEXT_BUFFERCHARS		4096

namespace CBfcScript
{

BFC_SCRIPT_CLASS  Script_Text : public CBfc::Stream
{
public:
	Script_Text ();
	Script_Text (Script_Text &bfc_text_stream);
	Script_Text (CBfc_Stream &bfc_stream);
	Script_Text (const CBfc::Filename &bfc_filename, const bool b_ReadOnly=true);
	virtual ~Script_Text();

public:
	virtual bool Seek(const INT64& n64Offset, const unsigned long& ulOrigin, __uint64* pun64NewPosition = NULL);
	virtual __uint64	Tell();

	bool AppendStreamWithSubstitution (Script_Text &stream, const CBfc::StringArray &substitute_array, const CBfc::StringArray &replace_array);

	virtual bool	ReadLine (CBfc_String &s);
	bool	ReadLine (characterPtr szDestBuf, const unsigned int uMaxBufLen);
	UINT	DetectBytesPerCharacter();
	inline UINT	GetBytesPerCharacter() const {
																return m_u_BytesPerCharacter; }
	void	SetBytesPerCharacter(const UINT u_BytesPerCharacter);

	bool	WriteLine (const CBfc_String &cs);
	bool	WriteLine (const CHARACTER_PTR lpszFormat, ...);
    bool	Write (const CBfc_String &cs);
    bool	Write (const CHARACTER_PTR lpszFormat, ...);
	bool	Write_Tabbified (const CBfc_String &text);

	void SetMaxLineLength(const UINT maxlen) { m_MaxLineLength = maxlen; }
	UINT	GetLineNumber() const { return m_uLineNumber; }
	virtual inline bool Rewind()
	{
		if (CBfc::Stream::Rewind())
		{
			m_uLineNumber = 0;
			EmptyBuffer();
			return true;
		}
		return false;
	}
	void SetSkippingLinefeeds(const bool bSkip) { m_b_SkippingLinefeeds=bSkip; } // set to true to not give linefeeds during ReadLine(), etc.
protected:
	virtual bool	OnAttach();
protected:
	bool	ClearBuffer();	// retains position in file before Emptying
	void	EmptyBuffer();	// throws away file positioning info.
	virtual bool SkippingLinefeeds() { return m_b_SkippingLinefeeds; }		// see, this may be set differently by the children.
	
	UINT	m_uLineNumber;
	UINT	m_MaxLineLength;
private:
	character NextCharacter(const bool bIncrement);
			
	UINT	m_u_BytesPerCharacter;
	void Constructor (void);
private:		// Output vars
	bool		m_b_SkippingLinefeeds;
	character	*m_p_InputBuffer;
	UINT		m_u_BufferIndex;
	UINT		m_u_CharsInBuffer;
	bool		RefillBuffer();
};


}
