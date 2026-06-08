//*/
/*
					CBfcOS_FileSelector.cpp : 
	
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

#include <BFC/BFCOS.h>

#ifndef UNIX
#	include <windows.h>
/*
#	include <tchar.h>
#	ifndef MAX_PATH
#		define MAX_PATH 260
#	endif
	typedef struct _FILETIME {
	DWORD dwLowDateTime;
	DWORD dwHighDateTime;
	} FILETIME, *PFILETIME, *LPFILETIME;

	typedef struct _WIN32_FIND_DATAA {
		DWORD dwFileAttributes;
		FILETIME ftCreationTime;
		FILETIME ftLastAccessTime;
		FILETIME ftLastWriteTime;
		DWORD nFileSizeHigh;
		DWORD nFileSizeLow;
		DWORD dwReserved0;
		DWORD dwReserved1;
		char   cFileName[ MAX_PATH ];
		char   cAlternateFileName[ 14 ];
	#ifdef _MAC
		DWORD dwFileType;
		DWORD dwCreatorType;
		WORD  wFinderFlags;
	#endif
	} WIN32_FIND_DATAA, *PWIN32_FIND_DATAA, *LPWIN32_FIND_DATAA;
	typedef struct _WIN32_FIND_DATAW {
		DWORD dwFileAttributes;
		FILETIME ftCreationTime;
		FILETIME ftLastAccessTime;
		FILETIME ftLastWriteTime;
		DWORD nFileSizeHigh;
		DWORD nFileSizeLow;
		DWORD dwReserved0;
		DWORD dwReserved1;
		character  cFileName[ MAX_PATH ];
		character  cAlternateFileName[ 14 ];
	#ifdef _MAC
		DWORD dwFileType;
		DWORD dwCreatorType;
		WORD  wFinderFlags;
	#endif
	} WIN32_FIND_DATAW, *PWIN32_FIND_DATAW, *LPWIN32_FIND_DATAW;

	#ifdef _UNICODE_16
		typedef WIN32_FIND_DATAW WIN32_FIND_DATA;
		typedef PWIN32_FIND_DATAW PWIN32_FIND_DATA;
		typedef LPWIN32_FIND_DATAW LPWIN32_FIND_DATA;
	#else
		typedef WIN32_FIND_DATAA WIN32_FIND_DATA;
		typedef PWIN32_FIND_DATAA PWIN32_FIND_DATA;
		typedef LPWIN32_FIND_DATAA LPWIN32_FIND_DATA;
	#endif // UNICODE

#endif // ndef UNIX

#ifndef UNIX
#	define INVALID_HANDLE_VALUE  ((HANDLE)(-1))
#	define FILE_ATTRIBUTE_READONLY         0x00000001
#	define FILE_ATTRIBUTE_HIDDEN           0x00000002
#	define FILE_ATTRIBUTE_SYSTEM           0x00000004
#	define FILE_ATTRIBUTE_DIRECTORY        0x00000010
#	define FILE_ATTRIBUTE_ARCHIVE          0x00000020
#	define FILE_ATTRIBUTE_NORMAL           0x00000080
#	define	FILE_ATTRIBUTE_TEMPORARY		0x00000100
#	define WINAPI
#	define WINBASEAPI // DECLSPEC_IMPORT
typedef const char *				LPCSTR;
	typedef const unsigned short *		LPCWSTR;
	WINBASEAPI HANDLE WINAPI	FindFirstFileA(LPCSTR lpFileName, LPWIN32_FIND_DATA lpFindFileData);
	WINBASEAPI HANDLE WINAPI	FindFirstFileW(LPCWSTR lpFileName, LPWIN32_FIND_DATA lpFindFileData);
	WINBASEAPI BOOL WINAPI		FindNextFileW(HANDLE hFindFile, LPWIN32_FIND_DATA lpFindFileData);
	WINBASEAPI BOOL WINAPI		FindCloseW(HANDLE hFindFile);
#	ifdef _UNICODE_16
#		define FindFirstFile	FindFirstFileW
#		define FindNextFile		FindNextFileW
#		define FindClose		FindCloseW
#	endif
*/
#endif

namespace CBfcOS 
{

FileSelector::FileSelector(CBfc_String *p_cs_filespec)
{
#ifdef UNIX
	m_p_glob = NULL;
#else
	m_handle = INVALID_HANDLE_VALUE;
#endif
	if (p_cs_filespec)
		m_cs_filespec = *p_cs_filespec;
	else
		m_cs_filespec = _TXT("*.*");
}

FileSelector::~FileSelector()
{
	Release();
}

void FileSelector::Release()
{
#ifdef UNIX
	if (m_p_glob)
	{
		globfree (m_p_glob);
		BFC_RELEASE (m_p_glob);
	}
#else
	if (m_handle != INVALID_HANDLE_VALUE)
	{
		FindClose (m_handle);
		m_handle = INVALID_HANDLE_VALUE;
	}
#endif
}

// boom - this shit replies on the current folder,
//			which eliminates the ability to multi-task
bool FileSelector::StartIteration (CBfc_String *p_cs_filespec)
{
	if (p_cs_filespec)
		m_cs_filespec = *p_cs_filespec;

	Release();		// Remove any preivous runs
	m_b_first = true;
	return true;
}

#ifdef UNIX
bool FileSelector::GetNext (CBfc::Filename &fspec)
{
	if (m_b_first)
	{
		STRING8	filespec8(m_cs_filespec);
		m_p_glob = new glob_t;
		if (glob(filespec8.GetPtr8(), GLOB_MARK, NULL, m_p_glob))
			return false;
		m_b_first = false;
		m_index = 0;
	}
	while (m_index < m_p_glob->gl_pathc)
	{
		CBfc::Filename	fullname(m_p_glob->gl_pathv[m_index++]);
		fspec = fullname.GetNameExtension();
		// If triling slash, then this is a folder
		CBfc::STRING sr(fspec.Right(1));
		if (sr != _TXT("/"))
			return true;
	}
	return false;
}
#else
bool FileSelector::GetNext (CBfc::Filename &fspec)
{
	WIN32_FIND_DATA	ffd;

	if (m_b_first)
	{
		STRING8	filespec8(m_cs_filespec);
		m_handle = FindFirstFile(filespec8.GetPtr8(), &ffd);
//		CBfc::Filename	filespec(m_cs_filespec);
//		m_handle = FindFirstFile(filespec.GetPtr(), &ffd);
	}
	if (m_handle == INVALID_HANDLE_VALUE)
		return false;
	do
	{
		if (m_b_first)
			m_b_first = false;
		else
		{
			if (!FindNextFile (m_handle, &ffd))
				return false;
		}
	} while (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
	fspec = CBfc::Filename(ffd.cFileName);
	return true;
}
#endif

//----------------------------------------------------------------------------//

FolderSelector::FolderSelector(CBfc_String *p_cs_filespec)
	: FileSelector(p_cs_filespec)
{
}

#ifdef UNIX
bool FolderSelector::GetNext (CBfc::Filename &fspec)
{
	if (m_b_first)
	{
		STRING8	filespec8(m_cs_filespec);
		m_p_glob = new glob_t;
		if (glob(filespec8.GetPtr8(), GLOB_ONLYDIR, NULL, m_p_glob))
			return false;
		m_b_first = false;
		m_index = 0;
	}
	while (m_index < m_p_glob->gl_pathc)
	{
		fspec = CBfc::Filename(m_p_glob->gl_pathv[m_index++]);
		if (fspec != _TXT(".") && fspec != _TXT(".."))
			return true;
	}
	return false;
}
#else
bool FolderSelector::GetNext (CBfc::Filename &fspec)
{
	WIN32_FIND_DATA	ffd;

	if (m_b_first)
	{
		STRING8	filespec8(m_cs_filespec);
		m_handle = FindFirstFile(filespec8.GetPtr8(), &ffd);
//		CBfc::Filename	filespec(m_cs_filespec);
//		m_handle = FindFirstFile(filespec.GetPtr(), &ffd);
	}
	if (m_handle == INVALID_HANDLE_VALUE)
		return false;
	do
	{
		do
		{
			if (m_b_first)
				m_b_first = false;
			else
			{
				if (!FindNextFile (m_handle, &ffd))
					return false;
			}
		} while (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY));
		fspec = CBfc::Filename(ffd.cFileName);
	} while (fspec == _TXT(".") || fspec == _TXT(".."));
	return true;
}
#endif
}
