//*/
/*
					CBfc_StreamSource.cpp : 
	
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

//#undef min
//#	define min(a,b) a<b?a:b

namespace CBfc {

StreamSource::~StreamSource()
{
}

bool StreamSource::Open (void)
{
	if (!m_bOpen)
	{
		if (OpenIt())
		{
			m_bOpen = true;
			return true;
		}
		return false;
	}
	return true;
}

bool StreamSource::Close (void) 
{ 
	if (m_bOpen)
	{
		m_bOpen = false;
		return CloseIt();
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////

StreamSource_Memory::StreamSource_Memory (const StreamSource_Memory *p_duper)
	: StreamSource (p_duper)
	, m_memoryBuffer (p_duper->m_memoryBuffer)
{
	m_streamSource = (EBFC_STREAMSOURCE_MEMORY);
//    m_memoryBuffer.SetToAllocation (p_duper->m_memoryBuffer);
	m_n_memoryOffset = p_duper->m_n_memoryOffset;
}

StreamSource_Memory::StreamSource_Memory (void *p_memory, const unsigned long ul_memoryByteLength)
	: m_n_memoryOffset(0)
{
	m_streamSource = (EBFC_STREAMSOURCE_MEMORY);
	m_memoryBuffer.SetToMemory (p_memory, ul_memoryByteLength);
}

StreamSource_Memory::StreamSource_Memory (const STRING &s)
	: m_n_memoryOffset(0)
{
	m_streamSource = (EBFC_STREAMSOURCE_MEMORY);
	m_memoryBuffer.SetToData (s.GetPtr(), s.GetLengthBytes());
}

StreamSource_Memory::~StreamSource_Memory()
{
	if (Close ())
		Detach ();
}

void*	StreamSource_Memory::Dup(void) 
{
	return (void*)(new StreamSource_Memory(this));
}

bool StreamSource_Memory :: Detach ()
{
	m_memoryBuffer.Free ();
	return true;
}

unsigned long StreamSource_Memory :: FileLength()
{
	return m_memoryBuffer.GetBytesAllocated();
}

bool StreamSource_Memory :: Seek(const INT64& n64Offset, const unsigned int uSeekType, __uint64* pun64NewPosition)
{
	switch (uSeekType)
	{
		case SEEK_SET:
			m_n_memoryOffset = n64Offset;
			break;
		case SEEK_END:
			m_n_memoryOffset = m_memoryBuffer.GetBytesAllocated() + n64Offset;
			break;
		case SEEK_CUR:
			m_n_memoryOffset += n64Offset;
			break;
	}
	if (pun64NewPosition)
		*pun64NewPosition = m_n_memoryOffset;
	return true;
}

__uint64 StreamSource_Memory :: Tell()
{
	return m_n_memoryOffset;
}

bool StreamSource_Memory::Write (const void *srcMem, const unsigned int uCount, unsigned int *p_uBytesWritten)
{
	BYTEPTR p_bytes;
	if (m_memoryBuffer.ReferenceBytes (m_n_memoryOffset, uCount, p_bytes))
	{
		memcpy(p_bytes, srcMem, uCount);
		if (p_uBytesWritten)
			*p_uBytesWritten = uCount;
		m_n_memoryOffset += uCount;
		return true;
	}
	return false;
}

bool StreamSource_Memory::Read (void *dstMem, const unsigned int uCount, unsigned int *p_uBytesRead)
{
	BYTEPTR	p_bytes;
	int			iBytesToRead = std::min((unsigned long long)uCount, m_memoryBuffer.GetBytesAllocated()-m_n_memoryOffset);
	if (iBytesToRead>0)
	{
		const UINT	uBytesToRead = iBytesToRead;
		if (m_memoryBuffer.ReferenceBytes (m_n_memoryOffset, uBytesToRead, p_bytes))
		{
			memcpy(dstMem, p_bytes, uBytesToRead);
			if (p_uBytesRead)
				*p_uBytesRead = uBytesToRead;
			m_n_memoryOffset += uBytesToRead;
			return true;
		}
	}
	return false;
}

//------------------------------------------------------------------------------//

StreamSource_File::StreamSource_File (StreamSource_File *p_duper)
	: StreamSource (p_duper)
{
	m_streamSource = (EBFC_STREAMSOURCE_FILE);
	m_bOpen = p_duper->m_bOpen;
// 	m_uFlags = p_duper->m_uFlags;
	m_b_ReadOnly = p_duper->m_b_ReadOnly;
	m_filenameSource = p_duper->m_filenameSource;
	m_SleepOffset = p_duper->m_SleepOffset;

	
	m_p_fhan = (FileHandle*)p_duper->m_p_fhan->Dup();
}

StreamSource_File::StreamSource_File (const CBfc::Filename &filename, const bool b_ReadOnly, const bool b_Temporary)
	: m_p_fhan(NULL)
{
	m_streamSource = (EBFC_STREAMSOURCE_FILE);

	m_filenameSource = filename;
	SetInternalFlags(b_ReadOnly);
}

StreamSource_File::~StreamSource_File()
{
	if (Close ())
		Detach ();
}


void StreamSource_File::SetInternalFlags(const bool b_ReadOnly)
{
	m_b_ReadOnly = b_ReadOnly;
}


OVERRIDE bool StreamSource_File::OpenIt (void)
{
	m_p_fhan = new FileHandle(m_filenameSource,m_b_ReadOnly);
	return m_p_fhan->IsOpen();
}

OVERRIDE bool StreamSource_File::CloseIt (void)
{
	BFC_RELEASE(m_p_fhan);
	return true;
}

bool StreamSource_File::Seek(const INT64& n64Offset, const unsigned int uSeekType, __uint64* pun64NewPosition)
{
	return m_p_fhan->Seek(n64Offset, uSeekType, pun64NewPosition);
}

// lseek

UINT64 StreamSource_File::Tell()
{
	return m_p_fhan->Tell();
}

bool StreamSource_File::Write (const void *srcMem, const unsigned int uCount, unsigned int *p_uBytesWritten)
{
	return m_p_fhan->Write (srcMem, uCount, p_uBytesWritten);
}

bool StreamSource_File::Read (void *dstMem, const unsigned int uCount, unsigned int *p_uBytesRead)
{
	return m_p_fhan->Read (dstMem,uCount,p_uBytesRead);
}

unsigned long StreamSource_File :: FileLength()
{
	return m_p_fhan->FileLength();
}

void*	StreamSource_File::Dup(void)
{
	return (void*) (new StreamSource_File(this));
}

void	StreamSource_File::GetFilename(STRING &fn) const
{
	fn = m_filenameSource;
}

OVERRIDE bool StreamSource_File::Sleep (void) {
	m_SleepOffset = Tell();
	return Close ();
}

OVERRIDE bool StreamSource_File::Awaken (void) {
	if (Open())
	{
		unsigned long ulOrigin = 0;
		__uint64 newpos;
		return Seek(m_SleepOffset, ulOrigin, &newpos);
	}
	return false;
}

OVERRIDE void *FileHandle::Dup ()
{
	FileHandle *pfh = new FileHandle();
	*pfh = *this;
	return (void*)pfh;
}


}



#ifdef WINDOWS
#	include	"CBfc_StreamSource_File_Windows.inc.cpp"
#else
#	include	"CBfc_StreamSource_File_Unix.inc.cpp"
#endif		// Windows

