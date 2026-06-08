//*/
/*
					CBfcOS_FileDialog.cpp : 
	
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
		Todo:
				list folder is wrong list!
	
*/
#include <BFC/BFCOS.h>

using namespace CBfc;
using namespace CBfcGUI;

// So, here we get into the real (fun) stuff:
//	Dialogs with windows inside of them that do different things (toolbar, folder tree, etc..)

// All of the resource scripts for BFCOS are located in CBfcOS_Application.cpp for now.

namespace CBfcOS
{

bool FilesystemEntry::Update()
{
/*
	Update all data:
	bool						m_b_isFolder;
	bool						m_b_isReadOnly;
	UINT						m_uSize;
	CBfc::PointTime	m_ModificationDate;
	CBfc::PointTime	m_CreationDate;
*/
	return false;
};

FileSelection_DX::FileSelection_DX	(const bool b_open, const bool b_multiple_selections, const bool b_select_folder, const CBfc::STRING *p_ExtentionList, const CBfc::Filename *p_StartFolder)
	: m_b_open (b_open)
	, m_b_multiple_selections(b_multiple_selections)
	, m_b_select_folder(b_select_folder)
{
	if (p_StartFolder)
		m_StartFolder=*p_StartFolder;
	if (p_ExtentionList)
		m_ExtentionList = *p_ExtentionList;
}

void FileSelection_DX::SetStartFolder(const CBfc::Filename &StartFolder)
{
	m_StartFolder = StartFolder;
}

void FileSelection_DX::GetStartFolder (CBfc::Filename &StartFolder) const
{
	StartFolder = m_StartFolder;
}

void FileSelection_DX::GetFilemask(CBfc::STRING &Mask) const
{
	Mask = m_ExtentionList;
}

void FileSelection_DX::SetFilesystemEntries(const CBfc::Array<FilesystemEntry> &Files)
{
//	m_Files = Files;
		m_Files.Empty();
		ULONG		idx=Files.StartIteration();
		FilesystemEntry		*p_bc;
		while ((p_bc=Files.GetNext(idx)))
			m_Files.Add(p_bc);
}

void FileSelection_DX::AddFilename(const CBfc::Filename fname, int i_organizer_offset)
{
	FilesystemEntry		bc(fname);
	
	m_Files.InsertAt(i_organizer_offset, &bc);
}

void FileSelection_DX::GetFilesystemEntries(CBfc::Array<FilesystemEntry> &Files) const
{
	Files = m_Files;
}

void FileSelection_DX::GetFilenames(CBfc::Array<CBfc::Filename> &Filenames) const
{
	FilesystemEntry	*pFsE;
	
	ULONG		idx = m_Files.StartIteration();
	while ((pFsE = m_Files.GetNext(idx)))
	{
		Filename	fn (pFsE);
		Filenames.Add (&fn);
	}
}

FileSelection_DP::FileSelection_DP(CBfcGUI::GUI *p_GUI, FileSelection_DX *pDX, CBfcGUI::Window *p_Parent) 
	:	CBfcGUI::DlgDP(p_GUI, pDX, p_Parent)
		{
		}


int	FileSelection_DP::RunDlg(CBfcGUI::DlgDS *pDS)
{
	m_b_cancelled = false;
	if (pDS)
	{
		pDS->SetDP(this);
		pDS->execute();
	}
	{
		FileDialog 	FileDlgDS(GetGUI(),GetDX());

		FileDlgDS.SetDP(this);
		FileDlgDS.execute();
	}
	return m_b_cancelled == 0;
}

bool	FileSelection_DP::ProcessInput(CBfcGUI::Resource_Control *pCtrl, CBfcGUI::DialogWindow *pDS)
{
	STRING	csName;
	if (pDS->GetResourceStore()->LookupResourceName(csName, pCtrl->GetResourceID(), 0))
	{
		if (csName==STRING("OPEN"))
			return false;
		else if (csName==STRING("CANCEL"))
			m_b_cancelled = (true);
			return false;
	}
	return true;
}

/**
 * 
 * @param p_GUI 
 * @param pDX 
 * @param p_Parent 
 * @param p_StartFolder 
 * @return 
 */
FileDialog::FileDialog(CBfcGUI::GUI *p_GUI, DX *pDX, CBfcGUI::Window *p_Parent)
	: CBfcGUI::DialogWindow (p_GUI, STRING("FSelDlg"), p_Parent, p_GUI->GetResourceStore("BFCOS"))
	, m_NavBar (p_GUI,"NavBar",this,p_GUI->GetResourceStore("BFCOS"))
	, m_ToolBar (p_GUI,"ToolBar",this, p_GUI->GetResourceStore("BFCOS"))
	, m_b_organizer(false)
	, m_b_include_subfolders(false)
	, m_organizer_offset(0)
	, m_p_FileList(NULL)
	, m_p_FolderList(NULL)
{
	SetDX(pDX);
	GetDX()->GetStartFolder (m_CurrentFolder);
}


int OVERRIDE FileDialog::OnMessage(const Message &msg)
{
	switch (msg.GetID())
	{
		case BFCGUI_MSG_MOUSEDOWN:
			return DialogWindow::OnMessage(msg);
	}
	return DialogWindow::OnMessage(msg);
}



/**
 * On create, make vertical nav bar, toolbar, file window with filelist, folder window with foldertree, 
 * @return 
 */
bool OVERRIDE FileDialog::OnCreate()
{
	bool bRval = DialogWindow::OnCreate();
	m_p_FileList = (CBfcGUI::ListRC*)Lookup_Resource_Control("FILES");
	m_p_FolderList = (CBfcGUI::ListRC*)Lookup_Resource_Control("FOLDERS");

	SetUI_FolderName (m_CurrentFolder);
	STRING	Mask;
	GetDX()->GetFilemask(Mask);
	SetUI_FileMask(Mask);
	
	if (bRval)
		return LoadCurrentFolder();
	return false;
}


/**
 * 
 * @param csFolder 
 * @return 
 */
bool FileDialog::GetUI_FolderName (Filename &csFolder)
{
	return GetUI_Text("FOLDER", csFolder);
}

bool		FileDialog::GetUI_FileMask (Filename &csMask)
{
	return GetUI_Text("FILETYPES", csMask);
}

/**
 * 		Get the full filename complete with path.
 * @param csFilename 
 * @return 
 */
bool FileDialog::GetUI_FileName (Filename &csFilename)
{
//		ResourceEntity *pRE_File = GetResourceStore()->LookupResourceEntity("FILENAME",GetResourceID());
// 		if (pRE_File)
// 		{
// 			pRE_File->GetText(csFilename);

	if (GetUI_Text("FILENAME", csFilename))
	{
		
		Filename	csFolder;
		GetUI_FolderName (csFolder);
		csFilename.SetPath(csFolder);
		return true;
	}
	return false;
}


bool FileDialog::SetUI_FolderName (const Filename &csFolder)
{
	GetDX()->SetStartFolder(csFolder);
	return SetUI_Text ("FOLDER",csFolder);
}


bool FileDialog::SetUI_FileMask (const Filename &csMask)
{
	return SetUI_Text ("FILETYPES",csMask);
}

/**
 * 
 * @param csFilename 
 * @return 
 */
bool FileDialog::SetUI_FileName (const Filename &csFilename)
{
	return SetUI_Text ("FILENAME",csFilename);
}

/**
 * 
 * @param pButton 
 * @return 
 */
void OVERRIDE FileDialog::UpdateDX(Button *pButton)
{
/*
	STRING	csName;
	if (GetGUI()->GetResourceStore()->LookupResourceName(csName, pButton->GetResourceID(), 0))
	{
		if (csName==STRING("GEN_REPORT"))
			GetDX()->m_bOutput_REPORT = pButton->GetChecked();
	}
*/
}

/**
 * 
 * @param pTxtbox 
 * @return 
 */
void OVERRIDE FileDialog::UpdateDX(Data_Resource_Control *pTxtbox)
{
	STRING			csName;
	if (GetResourceStore()->LookupResourceName(csName, pTxtbox->GetResourceID(), 0))
	{
		if (csName == "FOLDERS")
		{
			m_CurrentFolder = pTxtbox->GetText();
			SetUI_FolderName(m_CurrentFolder);
			LoadCurrentFolder();
		} else if (csName == "FILES")
		{
			SetUI_FileName(pTxtbox->GetText());
			UpdateFilename();
		} else if (csName == "FILETYPES")
		{
			LoadCurrentFolder();
		}
		if (!m_b_organizer)
		{
			if (csName==STRING("FILENAME"))
			{
/*
				Filename		fname(pTxtbox->GetText());
				Filename 		folder;
				GetUI_FolderName(folder);
				fname.SetPath(folder);
*/
				UpdateFilename();
			}
		}
	}
}

/**
 * 
 */
void FileDialog::UpFolder()
{
//	m_CurrentFolder = 
	m_CurrentFolder = m_CurrentFolder.LeftFrom(1);
	m_CurrentFolder = m_CurrentFolder.GetPath();
	SetUI_FolderName(m_CurrentFolder);
	LoadCurrentFolder();
}

bool FileDialog::UpdateFilename()
{
		Filename		fname;
		if (GetUI_FileName(fname))
		{
			CBfc::Array<FilesystemEntry>	Files;
			FilesystemEntry			entry(fname);
			Files.Add(&entry);

			GetDX()->SetFilesystemEntries(Files);
			return true;
		}
		return false;
}

/**
 * 
 * @param rID 
 * @param pRc 
 * @return return false to end modal
 */
bool OVERRIDE FileDialog::ButtonPress (const Resource_ID rID, Resource_Control *pRc)
{
	STRING	csName;
	if (GetResourceStore()->LookupResourceName(csName, pRc->GetResourceID(), 0))
	{
		if (csName=="UP")
		{
			UpFolder();
			return true;
		} else if (csName==STRING("ORGANIZER"))
		{
			return true;
		} else if (csName==STRING("ADD"))
		{
			Filename					fname;
			GetUI_FileName(fname);
			GetDX()->AddFilename(fname, m_organizer_offset);
			RedrawOrganizer();
			return true;
		} else if (csName=="SUBFOLDERS")
		{
			m_b_include_subfolders ^= 1;
			LoadCurrentFolder();
			return true;
		}
	}
	return GetDP()->ProcessInput(pRc, this);
}

/**
 * Fill Me In!!!!!!!
 */
void FileDialog::RedrawOrganizer()
{
}


/**
 * Load up contents of current folder into m_Files.
 * @return 
 */
bool	FileDialog::LoadCurrentFolder()
{
	m_Files.Empty();
	m_Folders.Empty();

	GetUI_FolderName (m_CurrentFolder);
	LoadFolder (m_CurrentFolder);
	FillListControls();
	return true;
}

bool	FileDialog::LoadFolder(const Filename &csFolder)
{
	AddFilesOfFolder (csFolder);
	
	Filename	cs_TargetFolderspec("*");
	cs_TargetFolderspec.SetPath(csFolder);
	
	FolderSelector	dirsel(&cs_TargetFolderspec);
	if (dirsel.StartIteration())
	{
		CBfc::Filename			fname;
		while (dirsel.GetNext (fname))
		{
			FilesystemEntry	fe(fname);
			m_Folders.Add (&fe);
		}
	}
	if (m_b_include_subfolders)
	{
		if (dirsel.StartIteration())
		{
			CBfc::Filename			fname;
			while (dirsel.GetNext (fname))
			{
				if (fname != "." && fname != "..")
				{
					fname.SetPath (csFolder);
					LoadFolder (fname);
				}
			}
		}
	}
	return true;
}

void FileDialog::AddFilesOfFolder (const Filename &csFolder)
{
	Filename	cs_TargetFilespec("*");
	GetUI_FileMask (cs_TargetFilespec);
	
	cs_TargetFilespec.SetPath(csFolder);
	FileSelector			fsel(&cs_TargetFilespec);
	
	if (fsel.StartIteration())
	{
		Filename			fname;
		while (fsel.GetNext (fname))
		{
			FilesystemEntry	fe(fname, csFolder);
//BFC_TRACE (_TXT("Adding filename %ls"), fname.GetPtr());
			m_Files.Add (&fe);
		}
	}
}

void FileDialog::FillListControls()
{
	if (m_p_FileList)
		m_p_FileList->Empty();
	if (m_p_FolderList)
		m_p_FolderList->Empty();
		
	if (m_p_FileList)
	{
		ULONG uIndex = m_Files.StartIteration();
		FilesystemEntry		*p_fse;
		while ((p_fse = m_Files.GetNext(uIndex)))
		{
			Filename	cs(*p_fse);
			if (m_b_include_subfolders)
			{
				cs.SetPath(p_fse->GetFolder().RightFrom(m_CurrentFolder.GetLength()));
			}
			m_p_FileList->AppendItem (cs);
	// instead, we need to format this list  entry via fe.
//				ListControl_Entry		le(fname);
//				m_FileList.Add(&le);
		}
	}
	if (m_p_FolderList)
	{
		ULONG uIndex = m_Folders.StartIteration();
		FilesystemEntry		*p_fse;
		while ((p_fse = m_Folders.GetNext(uIndex)))
		{
			m_p_FolderList->AppendItem (*p_fse);
		}
	}
}



}

