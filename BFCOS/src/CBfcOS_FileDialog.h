//*/
/*
					CBfcOS_FileDialog.h : 
	
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
// Description: 
//
//
// Author: Bill Foster <wpf_software@hotmail.com>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
	//
	// Displays contents of the current directory list, icon, etc.
	// filetype mask can be selected
	//  also, right click and/or buttons to create folders, rename files, and navigate.
	// Buttons: home, bookmarks, back, parent folder, work directory (where it started)
	//		show folders seperately, tree view
	// UNix needs Devices,Desktop,Home capability in left side navigator window
	//
	// input half:
	//		millions of files can be selected.
	//		optional add/remove files to the lower half, and sort them ,etc.
	//
	// preview pane:
	//		utilize pre-defined previews (text, bitmaps, etc.)
	//		plug-in support for app-specific previews
	//


namespace CBfcOS
{

BFC_OS_CLASS FilesystemEntry : public CBfc::Filename
{
public:
	FilesystemEntry() {}
#ifndef _UNICODE_8
	FilesystemEntry(char* ptr)
		: Filename(ptr)
			{ 	Update(); }
#endif
	FilesystemEntry(characterPtr ptr)
		: Filename(ptr)
			{
				Update();
			}
	FilesystemEntry(const CBfc_String &srcString)
		: Filename(srcString)
			{ 	Update(); }
	FilesystemEntry(const CBfc_String &srcString, const CBfc_String &csFolder)
	: Filename(srcString), m_csFolder(csFolder)
			{ 	Update(); }
	virtual	~FilesystemEntry()
		{}
public:
		bool			Update();		//Read the filesystem with the current name;
		Filename GetFolder() const {
			return m_csFolder;
		}
private:
		bool			m_b_isFolder;
		bool			m_b_isReadOnly;
		UINT			m_uSize;
	CBfc::PointTime		m_ModificationDate;
	CBfc::PointTime		m_CreationDate;
	CBfc::Filename		m_csFolder;
};

BFC_OS_CLASS	FileTreeControl : public CBfcGUI::TreeControl
{
public:
	FileTreeControl(CBfcGUI::GUI *p_GUI, const CBfc::STRING &csTitle, const CBfcGUI::EBFC_GUI_WINDOW_TYPE eType=CBfcGUI::WND_CHILD, CBfcGUI::Window *p_Parent=NULL,const CBfcGUI::Resource_ID resourceID=0);
	virtual	~FileTreeControl();
};

class FileSelection_DX : public CBfcGUI::DX
{
public:
	FileSelection_DX	(const bool b_open, const bool b_multiple_selections, const bool b_select_folder, const CBfc::STRING *p_ExtentionList=NULL, const CBfc::Filename *p_StartFolder=NULL);
public:
	void	SetStartFolder(const CBfc::Filename &StartFolder);
	void	GetStartFolder (CBfc::Filename &StartFolder) const;
	void	SetFilesystemEntries(const CBfc::Array<FilesystemEntry> &Files);
	void	GetFilesystemEntries(CBfc::Array<FilesystemEntry> &Files) const;
	void	GetFilenames(CBfc::Array<CBfc::Filename> &Filenames) const;
	void	GetFilemask(CBfc::STRING &Mask) const;
	void	AddFilename(const CBfc::Filename fname, int i_organizer_offset);
protected:
private:
	CBfc::Filename				m_StartFolder;
	CBfc::Array<FilesystemEntry>		m_Files;
	CBfc::STRING				m_ExtentionList;
	bool						m_b_open,	m_b_multiple_selections,	m_b_select_folder;
};


class FileSelection_DP : public CBfcGUI::DlgDP
{
public:
	FileSelection_DP(CBfcGUI::GUI *p_GUI, FileSelection_DX *pDX, CBfcGUI::Window *p_Parent=NULL);

	virtual int		RunDlg(CBfcGUI::DlgDS *pDS=NULL);
	virtual bool	ProcessInput(CBfcGUI::Resource_Control *, CBfcGUI::DialogWindow *pDS);  // required for any DP that has a DlgDS
protected:
private:
	bool			m_b_cancelled;
};


BFC_OS_CLASS FileDialog : public CBfcGUI::DialogWindow
{
public:
	FileDialog(CBfcGUI::GUI *p_GUI, CBfcGUI::DX *pDX, CBfcGUI::Window *p_Parent=NULL);
protected:
	bool		LoadCurrentFolder();		// 
protected:
	virtual bool	OnCreate();
		bool		LoadFolder(const CBfc::Filename &csFolder);
		void		AddFilesOfFolder (const CBfc::Filename &csFolder);
	
	virtual bool	ButtonPress (const CBfcGUI::Resource_ID rID, CBfcGUI::Resource_Control *pRc);
	virtual int		OnMessage(const CBfcGUI::Message &msg);
	
	FileSelection_DX *GetDX() const { return (FileSelection_DX*)DialogWindow::GetDX(); }
	virtual void	UpdateDX(CBfcGUI::Data_Resource_Control *pTxtbox);
	virtual void	UpdateDX(CBfcGUI::Button *pButton);
	
	void		UpFolder();
	void		RedrawOrganizer();
	bool		UpdateFilename();
private:
	void		FillListControls();
	
	bool		GetUI_FolderName (Filename &csFolder);
	bool		SetUI_FolderName (const Filename &csFolder);
	
	bool		GetUI_FileName (Filename &csFilename);
	bool		SetUI_FileName (const Filename &csFilename) ;

	bool		GetUI_FileMask (Filename &csMask);
	bool		SetUI_FileMask (const Filename &csMask);
private:
	bool					m_b_organizer;
	bool					m_b_include_subfolders;
	int					m_organizer_offset;

	CBfc::Filename			m_CurrentFolder;
	CBfcGUI::ToolBar			m_ToolBar;
	CBfcGUI::ToolBar			m_NavBar;
//	FileTreeControl			m_FolderTree;	// make folder tree optional. 'tis much faster without
	CBfc::Array<FilesystemEntry>	m_Files;
	CBfc::Array<FilesystemEntry>	m_Folders;
	
	CBfcGUI::ListRC			*m_p_FileList;
	CBfcGUI::ListRC			*m_p_FolderList;
};

}
