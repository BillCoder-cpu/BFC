//*/
/*
					CBfc_Filename.h : 
	
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

namespace CBfc
{
#ifdef WINDOWS
#	define ALL_WILD	_TXT("*.*")
#	define	FOLDER_CHAR				'\\'
#	define FOLDER_CHAR_AS_STRING	_TXT("\\")
#else
#	define ALL_WILD	_TXT("*")
#	define	FOLDER_CHAR				'/'
#	define FOLDER_CHAR_AS_STRING	_TXT("/")
#endif

BFC_CLASS Filename : public CBfc_String
{
public:
	Filename() {}
#ifndef _UNICODE_8
	Filename(const char* ptr)
		: CBfc_String(ptr)
			{
				OSFolderChar = FOLDER_CHAR;
			}
#endif
	Filename(const characterPtr ptr)
		: CBfc_String(ptr)
			{
				OSFolderChar = FOLDER_CHAR;
			}
	Filename(const const_characterPtr ptr)
		: CBfc_String(ptr)
			{
				OSFolderChar = FOLDER_CHAR;
			}
	Filename(const CBfc_String &srcString)
		: CBfc_String(srcString)
			{
				OSFolderChar = FOLDER_CHAR;
			}
	virtual	~Filename()
		{}

	inline static char OSFolderChar = FOLDER_CHAR;
	//inline static char myChar = 'A'; // Definition + initialization in one line
	void GetComponents (CBfc_String &cs_path, CBfc_String &cs_name, CBfc_String &cs_ext) const;
	Filename  GetPath () const;
	Filename  GetName () const;
	Filename  GetNameExtension () const;
	Filename  GetExtension () const;

	bool	GetNextSubdir(Filename &next);
			
	void SetComponents (const characterPtr p_path, const characterPtr p_name, const characterPtr p_ext);
	void SetExtention (const CBfc_String &cs_ext);
	void SetName (const CBfc_String &cs_name);
	void SetPath (const CBfc_String &cs_path);
	void PrependPath (const CBfc_String &cs_path);
	void RemovePath (const CBfc_String &cs_path);
	void RemovePath ();
			
	void EnsureTrailingSlash();
	void RemoveTrailingSlash();

	bool UnLink() const;
	bool DeleteFilespec(const bool bKill=false);
	static bool Rename(const CBfc_String &cs_source, const CBfc_String &cs_dest);
	bool FileExists() const;
	
	bool MatchesWildcard(const CBfc_String &cs_wildcard) const;
private:
	void Normalize ();
};

}
