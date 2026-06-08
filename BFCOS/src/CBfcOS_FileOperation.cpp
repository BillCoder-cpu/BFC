//*/
/*
					CBfcOS_FileOperation.cpp : 
	
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
//----------------------------------------------------------------------------//

namespace CBfcOS 
{

void Operation::SetFolder(CBfc::Filename &fnFolder) {
	m_fn_TargetFolder=fnFolder;
}

// returns true on folders to ignore
bool Operation::IgnoreFolder (const CBfc::Filename &folder) {
	if (m_cs_ignoreFolderSpec.IsEmpty()) return false;
	return folder.MatchesWildcard(m_cs_ignoreFolderSpec);
}


FileOperation::FileOperation (const CBfc::Filename &cs_TargetFilespec, const bool b_recurse_subfolders)
	: Operation (cs_TargetFilespec.GetPath(), b_recurse_subfolders), m_cs_TargetFilespec(cs_TargetFilespec)
{
	if (m_fn_TargetFolder.IsEmpty())	m_fn_TargetFolder = _TXT(".");
}

int FileOperation::Operate (FileOperationClass *p_opclass)
{
	return OperateOnFolder(m_fn_TargetFolder, p_opclass);
}

int FileOperation::OperateOnFolder (const CBfc::Filename &folder, FileOperationClass *p_opclass)
{
	if (m_b_recurse_subfolders)	{
		CBfc::Filename	folder_fspec(ALL_WILD);
		folder_fspec.SetPath(folder);

		FolderSelector	fs(&folder_fspec);
		CBfc::Filename	sub_folder;

		fs.StartIteration();
		while (fs.GetNext(sub_folder)) {
			if (!IgnoreFolder(sub_folder)) {
//		FinalPath.SetPath(m_fn_TargetFolder);
				sub_folder.SetPath (folder);
				OperateOnFolder(sub_folder, p_opclass);
			}
		}
	}
	OperateOnFolderContents(folder, p_opclass);
	return true;
}

int FileOperation::OperateOnFolderContents (const CBfc::Filename &folder, FileOperationClass *p_opclass)
{
	CBfc::Filename	cs_TargetFilespec(m_cs_TargetFilespec);
	cs_TargetFilespec.SetPath(folder);
//	printf ("\nFolder Contents: folder %ls, spec %ls\n", folder.GetPtr(), cs_TargetFilespec.GetPtr());
	CBfcOS::FileSelector	fsel(&cs_TargetFilespec);

	if (fsel.StartIteration())	{
		CBfc::Filename			fname;
		while (fsel.GetNext (fname)) {
			fname.SetPath(folder);
			if (!p_opclass->Operate (fname))	return false;
		}
	}
	return true;
}

/////////////////////////////////////////////////////////////////////
FolderOperation::FolderOperation (const CBfc::Filename &cs_TargetFolder, const bool b_recurse_subfolders)
	: Operation (cs_TargetFolder, b_recurse_subfolders)
{
}
		
FolderOperation::FolderOperation (const bool b_recurse_subfolders)
	: Operation (_TXT("."), b_recurse_subfolders)
{
}

int FolderOperation::Operate (FileOperationClass *p_opclass)
{
	p_opclass->m_fn_BaseFolder = m_fn_TargetFolder;
	return OperateOnFolder(m_fn_TargetFolder, p_opclass);
}
		
int FolderOperation::OperateOnFolder (const CBfc::Filename &folder, FileOperationClass *p_opclass)
{
	int	raccumulator = 0;
	if (m_b_recurse_subfolders)	{
		CBfc::Filename	folder_fspec(ALL_WILD);
		folder_fspec.SetPath(folder);

		FolderSelector	fs(&folder_fspec);
		CBfc::Filename	sub_folder;

		fs.StartIteration();
		while (fs.GetNext(sub_folder)) {
			if (!IgnoreFolder(sub_folder)) {
				sub_folder.SetPath(folder);
				raccumulator += OperateOnFolder(sub_folder, p_opclass);
			}
		}
	}
	return raccumulator + p_opclass->Operate (folder);	
// 	Filename	fname_op(m_cs_TargetFilespec);
// 	fname_op.SetPath(folder);
// 	return raccumulator + p_opclass->Operate (fname_op);
}

}
