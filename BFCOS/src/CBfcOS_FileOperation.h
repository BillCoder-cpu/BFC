//*/
/*
					CBfcOS_FileOperation.h : 
	
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
Run either the FolderOperation or the FileOperation on a FileOperationClass object.

*/
namespace CBfcOS {

#ifdef WINDOWS
#	define ALL_WILD	_TXT("*.*")
#else
#	define ALL_WILD	_TXT("*")
#endif

//typedef int (*FileOperation_FunctionPtr)(const CBfc::Filename &fname);

class FileOperationClass
{
	public:
		virtual int	Operate(const CBfc::Filename &fname)=0;
		CBfc::Filename	m_fn_BaseFolder;
};

BFC_OS_CLASS Operation
{
public:
	Operation (const CBfc::Filename &cs_TargetFolder, const bool b_recurse_subfolders) : m_fn_TargetFolder (cs_TargetFolder), m_b_recurse_subfolders (b_recurse_subfolders)
	{}
	void SetFolder(CBfc::Filename &fnFolder);
protected:
	bool		IgnoreFolder (const CBfc::Filename &folder);
protected:
	bool			m_b_recurse_subfolders;
	CBfc::Filename	m_fn_TargetFolder;
public:
	CBfc::STRING	m_cs_ignoreFolderSpec;	// types of folders to skip (.*, etc)
};

BFC_OS_CLASS FileOperation : public Operation
{
	public:
		FileOperation (const CBfc::Filename &cs_TargetFilespec, const bool b_recurse_subfolders);
		int Operate(FileOperationClass *p_opclass);
	private:
		int OperateOnFolder (const CBfc::Filename &folder, FileOperationClass *p_opclass);
		int OperateOnFolderContents (const CBfc::Filename &folder, FileOperationClass *p_opclass);
		const CBfc::Filename	&m_cs_TargetFilespec;
};

BFC_OS_CLASS FolderOperation : public Operation
{
	public:
		FolderOperation (const CBfc::Filename &cs_TargetFolder, const bool b_recurse_subfolders);
		FolderOperation (const bool b_recurse_subfolders);
		int Operate(FileOperationClass *p_opclass);
	private:
		int OperateOnFolder (const CBfc::Filename &folder, FileOperationClass *p_opclass);
};

}
