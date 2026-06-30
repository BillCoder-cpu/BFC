//*/
/*
					CBfc_Stream.cpp : 
	
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

#include <BFC/BFC.h>

///////////////////////////////////////////////////////////////////////////////

namespace CBfc {

Stream::Stream (const Stream &bfc_stream, const bool b_threaded)
	: m_b_attached (false)
	, m_p_source (NULL)
	, m_p_CompressionAlgorythm (NULL)
{
	*this = bfc_stream;
	m_ThreadInfo.m_b_threaded = (b_threaded);
}

Stream::Stream (const bool b_threaded)
	: m_b_attached (false)
	, m_p_source (NULL)
	, m_p_CompressionAlgorythm (NULL)
{
	m_ThreadInfo.m_b_threaded = (b_threaded);
}

Stream::Stream (const CBfc::Filename &bfc_filename, const bool b_ReadOnly, const bool b_threaded)
	: m_b_attached (false)
	, m_p_source (NULL)
	, m_p_CompressionAlgorythm (NULL)
	, m_bReadOnly (b_ReadOnly)
{
	m_ThreadInfo.m_b_threaded = (b_threaded);
	AttachFile (bfc_filename, b_ReadOnly);
}

Stream::~Stream ()
{
	Detach ();
}

void Stream::operator = (const Stream &stream)
{
	m_b_attached = stream.m_b_attached;
	if (stream.m_p_source)	m_p_source = (StreamSource*)(stream.m_p_source->Dup());
		else				m_p_source = NULL;
	m_bReadOnly = stream.m_bReadOnly;

//	m_ThreadInfo = stream.m_ThreadInfo;			//
	m_p_CompressionAlgorythm = stream.m_p_CompressionAlgorythm;
}

bool Stream::Detach ()
{
	if (m_b_attached)
	{
		BFC_RELEASE (m_p_source);
		m_b_attached = false;
		return true;
	}
	return true;
}

unsigned long	Stream::FileLength()
{
	if (m_b_attached)
		return m_p_source->FileLength();
	return 0;
}

/**
	* 
	* @return 
	*/
CBfc::FileHandle *Stream::GetFileHandle()
{
	if (m_p_source->GetStreamSource()==CBfc::StreamSource::EBFC_STREAMSOURCE_FILE)
		return ((CBfc::StreamSource_File *)(m_p_source))->GetFileHandle();
	return NULL;
}


// Make a duplicater of this stream
bool Stream::AttachStream(const Stream &stream)
{
	if (Detach())
	{
		*this = stream;
		return true;
	}
	return false;
}

bool Stream::GetFilename(STRING &csFilename) const
{
	if (m_p_source && m_p_source->GetStreamSource() == StreamSource::EBFC_STREAMSOURCE_FILE)
	{
		((StreamSource_File*)m_p_source)->GetFilename(csFilename);
		return true;
	}
	return false;
}

bool Stream::AppendToFile (const CBfc::Filename &filename)
{
	return AttachFile (filename, false);
}

bool Stream::CreateAFile (const CBfc::Filename &filename)
{
	if (Detach())
	{
		filename.UnLink();
		if (!filename.FileExists())
			return AppendToFile (filename);
	}
	return false;
}

// Note -
bool Stream::AttachFile (const CBfc::Filename &filename, const bool b_ReadOnly)
{
	if (Detach())
	{
		m_p_source = new StreamSource_File (filename, b_ReadOnly);
		if (m_p_source)
		{
			if (Open())
			{
				return OnAttach();
			} else
			{
				if (m_p_source->Detach ())
					BFC_RELEASE (m_p_source);
			}
		 }
	}
	return false;
}

bool Stream::OnAttach()
{
	m_b_attached = true;
	return true;
}

bool Stream::AttachMemory (void *p_memory, const unsigned long ul_memoryByteLength)
{
	if (Detach())
	{
		m_p_source = new StreamSource_Memory (p_memory, ul_memoryByteLength);
		if (m_p_source)
			return OnAttach();
	}
	return false;
}

// Read all of 'stream' and write into this stream
bool Stream::AppendStream (Stream &stream)
{
	char				buffer[512];
	const unsigned int	bufsize=512;
	unsigned int		u_bytesRead;

	while (stream.Read (buffer, bufsize, &u_bytesRead))
	{
		if (!Write (buffer, u_bytesRead))
			return false;
	}
	return true;
}

// Read into the bffer, yet return the stream's pointer to it's original location.
bool Stream::ReadAhead (void *dstMem, const unsigned int uCount, unsigned int *p_uBytesRead)
{
	__uint64	pos = Tell();
//const unsigned long& ulOrigin

	bool b = Read (dstMem, uCount, p_uBytesRead);
	Seek(pos, 0, NULL);
	return b;
}

}


