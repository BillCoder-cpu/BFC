//*/
/*
					CBfc_StreamSource_File_Windows.inc.cpp : 
	
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
	 Todo - use CreateFile, WriteFile, etc. so we can call SetFileTime

*/

#include <io.h>
#include <tchar.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

namespace CBfc {

FileHandle::FileHandle()
{
	m_hFile = (NULL);
}

FileHandle::FileHandle(const Filename &fn,const bool b_ReadOnly)
{
	unsigned long		uFlags;
	
	if (b_ReadOnly)
		uFlags = _O_RDONLY|_O_BINARY;
	else
		uFlags = _O_RDWR|_O_BINARY;
	
#ifdef _UNICODE_8
	m_hFile = _open((character*)fn.GetPtr(), uFlags);
#else
	m_hFile = _wopen((character*)fn.GetPtr(), uFlags);
#endif
	if (m_hFile < 0)
	{
		if (uFlags & (_O_RDWR | _O_WRONLY))
		{
#ifdef _UNICODE_8
			m_hFile = _open((character*)fn.GetPtr(), uFlags|_O_APPEND,_S_IREAD|_S_IWRITE );
			if (m_hFile < 0)
				m_hFile = _open((character*)fn.GetPtr(), uFlags|_O_CREAT,_S_IREAD|_S_IWRITE );
#else
			m_hFile = _wopen((character*)fn.GetPtr(), uFlags|_O_APPEND,_S_IREAD|_S_IWRITE );
			if (m_hFile < 0)
				m_hFile = _wopen((character*)fn.GetPtr(), uFlags|_O_CREAT,_S_IREAD|_S_IWRITE );
#endif
		}
	}
}

void FileHandle::operator = (const FileHandle &copy)
{
	IncrementReference();
	m_hFile = copy.m_hFile;
}

bool FileHandle::IsOpen() const
{
	return (m_hFile>=0);
}

FileHandle::~FileHandle ()
{
	if (GetReferenceCount()==1)
	{
		if (m_hFile)
		{
			_close(m_hFile);                  // Done with file.
			m_hFile = NULL;
		}
	}
}

long FileHandle::FileLength ()
{	     /* Set the end of the file: */
	     /* Find current position: */
     long curpos = _lseek( m_hFile, 0L, SEEK_CUR );
     long rval = 0;
     if( curpos != -1L )
	 {
		long pos = _lseek( m_hFile, 0L, SEEK_END );
		if( pos != -1L )
			rval = pos;
		_lseek( m_hFile, curpos, SEEK_SET );	// Go back to where we were
	 }  
	 return rval;
}

bool FileHandle::Seek(const __int64& n64Offset, const unsigned int uSeekType, __uint64* pun64NewPosition)
{
	__int64 newpos = _lseeki64(m_hFile, n64Offset, uSeekType);
	if (pun64NewPosition)
		*pun64NewPosition = newpos;
	return true;
}

__uint64 FileHandle::Tell()
{
	return _telli64 (m_hFile);
}

bool FileHandle::Write (const void *srcMem, const unsigned int uCount, unsigned int *p_uBytesWritten)
{
	unsigned int bytesWritten;
	if (uCount == 0)
		bytesWritten = 0;
	else
		bytesWritten = _write(m_hFile, srcMem, uCount);
	if (p_uBytesWritten)
		*p_uBytesWritten = bytesWritten;
	return (bytesWritten == uCount);
}

bool FileHandle::Read (void *dstMem, const unsigned int uCount, unsigned int *p_uBytesRead)
{
	int bytesRead = _read(m_hFile, dstMem, uCount);
	if (bytesRead == -1)
		bytesRead = 0;
	if (p_uBytesRead)
		*p_uBytesRead = (unsigned int)bytesRead;
	return (bytesRead>0);
}



}
