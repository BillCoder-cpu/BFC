//*/
/*
					CBfc_Filename.cpp : 
	
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
#include "BFC/BFC.h"
#ifdef WINDOWS
#	include <windows.h>
#	include <io.h>
#endif
#ifdef UNIX
#	include <fnmatch.h>
#endif

// #include <iostream>

namespace CBfc {

//char Filename::OSFolderChar = FOLDER_CHAR;

#ifndef WINDOWS			// Unix variation (standard)
bool Filename::FileExists() const
{
// 	bool OS_Static::GetFileAttributes(const Filename &fName)

	STRING8	s8(*this);
	FILE	*fp;
	if ((fp = fopen (s8.GetPtr8(), "rb"))) {
		fclose (fp);
		return 1;
	}            
	return 0;
}

bool Filename::UnLink() const
{
	STRING8	s8(*this);

	unlink (s8.GetPtr8());
	return true;
// 	return (unlink (s8.GetPtr8()) == 0);
}

bool Filename::Rename(const CBfc_String &cs_source, const CBfc_String &cs_dest)
{
	STRING8	s8Src(cs_source), s8Dst(cs_dest);
	return (rename (s8Src.GetPtr8(), s8Dst.GetPtr8()) != 0);
}
#else
bool Filename::FileExists() const
{
	FILE	*fp;
	
#ifdef _UNICODE_16
	if ((fp = _wfopen (GetPtr(), _TXT("rb")))) {
#else
	if ((fp = fopen (GetPtr(), _TXT("rb")))) {
#endif
		fclose (fp);
		return 1;
	}            
	return 0;
}

/*
// if bKill is true, destroys contents of folder
bool Filename::DeleteFilespec(const bool bKill)
{
/*
typedef struct _SHFILEOPSTRUCT {
	HWND hwnd;
	UINT wFunc;
	LPCTSTR pFrom;
	LPCTSTR pTo;
	FILEOP_FLAGS fFlags;
	BOOL fAnyOperationsAborted;
	LPVOID hNameMappings;
	LPCTSTR lpszProgressTitle;
} SHFILEOPSTRUCT, *LPSHFILEOPSTRUCT;

	CBfc_String	cs(*this);
	SHFILEOPSTRUCT	sop;
	UINT	uLen = GetLengthBytes();
	BYTE	*pad = new BYTE[uLen+(2*sizeof(character))];

	memcpy (pad, GetPtr(), uLen+sizeof(character));
	memset (pad+uLen, 0, 2*sizeof(character));
	
	sop.hwnd=NULL;
	sop.wFunc=FO_DELETE;
	sop.pFrom=(LPCSTR)pad;
	sop.pTo=NULL;
	sop.fFlags=FOF_FILESONLY|FOF_NORECURSION|FOF_SILENT|FOF_NOCONFIRMATION;
	sop.fAnyOperationsAborted=0;
	sop.hNameMappings=NULL;
	sop.lpszProgressTitle=NULL;

	bool bRval=(SHFileOperation(&sop)==0);
	delete[] pad;
	return bRval;
}
*/

bool Filename::UnLink() const
{
#ifdef _UNICODE_16
	return (_wunlink (GetPtr()) == 0);
//	return (DeleteFileW(GetPtr()) != 0);
#else
	return (DeleteFileA(GetPtr()) != 0);
#endif
}

bool Filename::Rename(const CBfc_String &cs_source, const CBfc_String &cs_dest)
{
#ifdef _UNICODE_16
	return (_wrename (cs_source.GetPtr(), cs_dest.GetPtr()) != 0);
#else
	return (rename (cs_source.GetPtr(), cs_dest.GetPtr()) != 0);
#endif
}
#endif

// Filenames in the form:
//     path/na.me.ext
//
void Filename::GetComponents (CBfc_String &cs_path, CBfc_String &cs_name, CBfc_String &cs_ext) const
{
	int ext_revpos = ReverseFind('.', 0);
	int slash_revpos = ReverseFind('/', 0);
	int name_revpos = ReverseFind('\\',0);
	if (slash_revpos < name_revpos)
		slash_revpos = name_revpos;

	if (ext_revpos==0)		// If ends in '.', is not a real extension
		ext_revpos = -1;
	if (name_revpos < 0)
		name_revpos = slash_revpos;
	else if (slash_revpos < name_revpos)	// Note: We are in reverse!
		name_revpos = slash_revpos;
	// don't include ./ or ../ type of deals, or folders with period in them.
	if (name_revpos >= 0 && ext_revpos > name_revpos)
		ext_revpos = -1;

	int	namestart_pos;
	
	if (name_revpos > 0)
	{
		namestart_pos = GetLengthChars()-name_revpos;
		cs_path = Left(namestart_pos);
	} else
	{
		namestart_pos = 0;
		cs_path.Empty();
	}
	if (ext_revpos < 0)
	{
		cs_ext.Empty();
		cs_name = Right(GetLengthChars()-namestart_pos);
	} else
	{
		cs_ext = Right(ext_revpos);
		cs_name = Mid(namestart_pos, GetLengthChars()-ext_revpos-2);
	}
}

void Filename::RemoveTrailingSlash()
{
	character cr = Right();
	if (cr == '/' || cr == '\\')
			TrimRight(1);
}

void Filename::EnsureTrailingSlash()
{
	if (IsEmpty())
		*this += OSFolderChar;
	else
	{
		character cr = Right();
		if (cr != '/' && cr != '\\')
			*this += OSFolderChar;
	}
}

//
// 
//
bool Filename::GetNextSubdir(Filename &next)
{
	int index = Find(OSFolderChar);
	if (index == -1)
		return false;
	
	next = Left(index+1);
	*this = RightFrom(index+1);
	return true;
}

void Filename::SetComponents (const characterPtr p_path, const characterPtr p_name, const characterPtr p_ext)
{
	Filename	cs_path;
	CBfc_String		cs_name, cs_ext;

	GetComponents (cs_path, cs_name, cs_ext);
// wprintf (_TXT("Get Comps %ls | %ls | %ls\n"), cs_path.GetPtr(), cs_name.GetPtr(), cs_ext.GetPtr());
	if (p_path) cs_path = p_path;
	if (p_name) cs_name = p_name;
	if (p_ext) cs_ext = p_ext;
	if (!cs_path.IsEmpty()) {
		cs_path.Normalize();
		cs_path.EnsureTrailingSlash();
	}
	
// wprintf (_TXT("  Set Comps %ls | %ls | %ls\n\n"), cs_path.GetPtr(), cs_name.GetPtr(), cs_ext.GetPtr());

	if (cs_path=="./" || cs_path==".\\")
		this->Empty();
	else
		*this = cs_path;
	*this += cs_name;
	if (!cs_ext.IsEmpty())
	{
		*this += _TXT(".");
		*this += cs_ext;
	}
}

void Filename::SetExtention (const CBfc_String &cs_ext)
{
	SetComponents ((characterPtr)NULLPTR, (characterPtr)NULLPTR, cs_ext.GetPtr());
}

void Filename::SetName (const CBfc_String &cs_name)
{
	SetComponents ((characterPtr)NULLPTR, cs_name.GetPtr(), (characterPtr)NULLPTR);
}

void Filename::SetPath (const CBfc_String &cs_path)
{
	SetComponents (cs_path.GetPtr(), (characterPtr)NULLPTR, (characterPtr)NULLPTR);
}

// Make all occurances of the folder char the correct way!
void Filename::Normalize()
{
    STRING bad, good;
    if (OSFolderChar == '\\') {
        good = "\\"; bad = "/";
    } else {
        good = "/"; bad = "\\";
    }
    Replace(bad, good);
}

/// put cs_path and then filename 
void Filename::PrependPath (const CBfc_String &cs_path)
{
	Filename fn(cs_path);
	fn.Normalize();
	fn.EnsureTrailingSlash();
	*this = fn+*this;
}

// If cs_path is the first part of the filename, remove it!
void Filename::RemovePath (const CBfc_String &cs_path)
{
	if (cs_path.GetLengthChars() == GetLengthChars())
	{
		if (*this == cs_path)
			Empty();
	} else
	{
		Filename fn(cs_path);
		fn.EnsureTrailingSlash();
		if (this->Find(fn)==0)
			*this = Right (GetLengthChars()-fn.GetLengthChars());
	}
}

void Filename::RemovePath ()
{
	*this = GetNameExtension();
}

Filename Filename::GetPath () const
{
	Filename	cs_path;
	CBfc_String		cs_name, cs_ext;

	GetComponents (cs_path, cs_name, cs_ext);
	return cs_path;
}

Filename  Filename::GetName () const
{
	Filename	cs_path, cs_name, cs_ext;

	GetComponents (cs_path, cs_name, cs_ext);
	return cs_name;
}

Filename  Filename::GetNameExtension () const
{
	Filename	cs_path, cs_name, cs_ext;

	GetComponents (cs_path, cs_name, cs_ext);
	if (!cs_ext.IsEmpty())
	{
		cs_name += _TXT(".");
		cs_name += cs_ext;
	}
	return cs_name;
}

Filename  Filename::GetExtension () const
{
	Filename	cs_path, cs_name, cs_ext;

	GetComponents (cs_path, cs_name, cs_ext);
	return cs_ext;
}

#ifndef UNIX
//////////////////////////////////////////////////////////////////////////
//    WildcardMatch
//        pszString    - Input string to match
//        pszMatch    - Match mask that may contain wildcards like ? and *
//    
//        A ? sign matches any character, except an empty string.
//        A * sign matches any string inclusive an empty string.
//        Characters are compared caseless.
bool WildcardMatch(const TCHAR *pszString, const TCHAR *pszMatch) {
    // We have a special case where string is empty ("") and the mask is "*".
    // We need to handle this too. So we can't test on !*pszString here.
    // The loop breaks when the match string is exhausted.
    while (*pszMatch)   {
        // Single wildcard character
        if (*pszMatch==character('?'))   {     // Matches any character except empty string
            if (!*pszString)         return false;
            ++pszString;            ++pszMatch;			// OK next
        }
        else if (*pszMatch==character('*')) {
            // Need to do some tricks.
            // 1. The wildcard * is ignored. 
            //    So just an empty string matches. This is done by recursion.
            //      Because we eat one character from the match string, the
            //      recursion will stop.
            if (WildcardMatch(pszString,pszMatch+1))    return true;      // we have a match and the * replaces no other character
            // 2. Chance we eat the next character and try it again, with a
            //    wildcard * match. This is done by recursion. Because we eat
            //      one character from the string, the recursion will stop.
            if (*pszString && WildcardMatch(pszString+1,pszMatch)) return true;
            // Nothing worked with this wildcard.
            return false;
        } else {
            // Standard compare of 2 chars. Note that *pszSring might be 0
            // here, but then we never get a match on *pszMask that has always
            // a value while inside this loop.
//            if (::CharUpper(MAKEINTRESOURCE(MAKELONG(*pszString++,0))) != ::CharUpper(MAKEINTRESOURCE(MAKELONG(*pszMatch++,0))))
            if (toupper((MAKELONG(*pszString++,0))) != toupper((MAKELONG(*pszMatch++,0))))
                return false;
        }
    }
    // Have a match? Only if both are at the end...
    return !*pszString && !*pszMatch;
}
#endif

bool Filename::MatchesWildcard(const CBfc_String &cs_wildcard) const
{
#ifdef UNIX
		STRING8	wildcard8(cs_wildcard);
		STRING8 fn8(*this);
		return fnmatch(wildcard8.GetPtr8(), fn8.GetPtr8(), FNM_CASEFOLD) == 0;
#else
		return WildcardMatch ((TCHAR*)GetPtr(), (TCHAR*)cs_wildcard.GetPtr());
#endif
}

}





