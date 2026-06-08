//*/
/*
					CBfcOS_FileSelector.h : 
	
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

#ifdef WIN32
#	include <io.h>
#	include <direct.h>
#else
#	include <glob.h>
#endif

namespace CBfcOS {

BFC_OS_CLASS FileSelector
{
public:
	FileSelector(CBfc_String *p_cs_filespec=NULL);
	virtual ~FileSelector();

	bool StartIteration (CBfc_String *p_cs_filespec=NULL);
	virtual bool GetNext (CBfc::Filename &fspec);

protected:
	void	Release();
	CBfc::STRING	m_cs_filespec;
	bool			m_b_first;
#ifdef UNIX
	glob_t			*m_p_glob;
	int				m_index;
#else
	HANDLE			m_handle;		// Win equiv.
#endif
};

BFC_OS_CLASS FolderSelector : public FileSelector
{
public:
	FolderSelector(CBfc_String *p_cs_filespec=NULL);

	virtual bool GetNext (CBfc::Filename &fspec);
};

}
