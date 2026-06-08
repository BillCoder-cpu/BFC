//*/
/*
					CBfc_StreamSource_File_Unix.inc.cpp : 
	
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
	Unix low level File IO
*/

namespace CBfc {

FileHandle::FileHandle()
{
	m_fp = NULL;
}

void FileHandle::operator = (const FileHandle &copy)
{
	IncrementReference();
	m_fp = copy.m_fp;
}

FileHandle::FileHandle(const Filename &fn,const bool b_ReadOnly)
{
	STRING8	fname(fn);
	const char *p = (const char *)fname.GetPtr8();
	m_fp = fopen (p, b_ReadOnly ? "r" : "a+");
	if (!m_fp && !b_ReadOnly)
		m_fp = fopen (p, "w+");
}

bool FileHandle::IsOpen() const
{
	return (m_fp!=NULL);
}

FileHandle::~FileHandle ()
{
	if (GetReferenceCount()==1)
	{
		if (m_fp)
		{
			fclose (m_fp);
			m_fp = NULL;
		}
	}
}


INT64 FileHandle::FileLength ()
{	     /* Set the end of the file: */
	     /* Find current position: */
     INT64 curpos = ftello(m_fp);
     INT64 rval = 0;
     if( curpos != -1L )
	 {
		if (fseeko( m_fp, 0L, SEEK_END ) == 0)
			rval = ftello (m_fp);
		fseek ( m_fp, curpos, SEEK_SET );	// Go back to where we were
	 }  
	 return rval;
}

bool FileHandle::Seek(const INT64& n64Offset, const unsigned long& ulOrigin, __uint64* pun64NewPosition)
{
	if (fseeko (m_fp, n64Offset, SEEK_SET) == 0)
	{
		if (pun64NewPosition)
			*pun64NewPosition = ftello(m_fp);
		return true;
	}
	return false;
}

// lseek

UINT64 FileHandle::Tell()
{
	return m_fp ? ftello(m_fp) : 0;
}

bool FileHandle::Write (const void *srcMem, const unsigned int uCount, unsigned int *p_uBytesWritten)
{
  size_t sizeWritten = fwrite (srcMem, 1, uCount, m_fp);
  if (p_uBytesWritten)
	*p_uBytesWritten = sizeWritten;
  return (sizeWritten > 0);
}

bool FileHandle::Read (void *dstMem, const unsigned int uCount, unsigned int *p_uBytesRead)
{
  size_t sizeRead = fread (dstMem, 1, uCount, m_fp);
  if (p_uBytesRead)
	*p_uBytesRead = sizeRead;
  return sizeRead > 0;
}

}

