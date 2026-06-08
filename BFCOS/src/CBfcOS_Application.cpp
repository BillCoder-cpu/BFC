//*/
/*
					CBfcOS_Application.cpp : 
	
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

#ifdef	UNIX
#	include <wchar.h>
#endif

#ifdef _UNICODE_8
#define tprintf	printf
#else
#define tprintf	wprintf
#endif


using namespace CBfc;

namespace CBfcOS {

Application::Application()
: m_p_GUI(NULL)
{
}

Application::~Application()
{
	ShutdownAppLayer();
}

bool Application::LoadResources(const Filename &ResourceFilename)
{
	bool	bRval = false;
	
	Filename	resname(ResourceFilename);
	resname.SetPath(m_ResourceFolder);
	
	m_resource_stream.AttachFile(resname);

	if (m_resource_stream.IsAttached())
	{
		CBfcGUI::ScriptResource	*pRes = new CBfcGUI::ScriptResource(m_resource_stream);
		SetResource(pRes);
		bRval = (pRes!=NULL);
		if (bRval)
		{
			const Filename	rp(ResourceFilename.GetPath());
			pRes->SetFolder (rp);
		}
	}
	if (!bRval)
		tprintf (_TXT("Unable to load resource file %ls\n"),resname.GetPtr());
	return bRval;
}

bool Application::SetResource (CBfcGUI::ScriptResource *res)
{
	m_p_Resource=res;
	return true;
}

void Application::GetCopyrightString(CBfc_String &s)
{
	s = m_str_Title;
	s += (_TXT("Copyright (C) 2004-2007 by William P. Foster, all rights reserved\n"));
	CBfc::STRING	cs;
	OS_Static::GetCreditsString(cs);
	s += cs;
}


bool Application::CreateMainWindow (const CBfc::Size2dU &size,const CBfc::STRING csTitle,const CBfc::STRING *p_csMenuName)
{
	if (m_p_GUI)
	{
		if (m_p_GUI->GetMainWindow())
			return true;

		CBfcGUI::MenuWindow	*pWndMain = new CBfcGUI::MenuWindow(m_p_GUI,csTitle,CBfcGUI::WND_MAIN);

		m_p_GUI->SetMainWindow(pWndMain,p_csMenuName);
		pWndMain->SetWindowSize (size);
		return true;
	}
	return false;
}

int Application::InitializeAppLayer ()
{
	int i_Rval = Application_DerivedFrom::InitializeAppLayer(m_argc, m_argv);
	if (i_Rval)
	{
		if (!m_p_GUI)
			m_p_GUI = new CBfcGUI::GUI (this, m_p_Resource);
		if (!m_p_GUI)
			i_Rval = 0;
		else
			RegisterBFCOSResources ();
	}
	return i_Rval;
}

extern character *bfcos_resource_script;


// There are various dialogs in memory for BFCOS, such as the file selection dialog.
// This function reads them from memory and tells the gui to store them for us.
void Application::RegisterBFCOSResources ()
{	
	Stream		s;
// 	const unsigned long ul_memoryByteLength=sizeof(bfcos_resource_script);
	const unsigned long ul_memoryByteLength=SBFC_Character::StringByteLength(bfcos_resource_script);
	try
	{
		if (s.AttachMemory (bfcos_resource_script, ul_memoryByteLength))
		{
			CBfcGUI::ScriptResource	*pRes = new CBfcGUI::ScriptResource(s);
			CBfcGUI::ResourceStore *pRS=pRes->LoadResources(); 
			
			GetGUI()->RegisterResourceStore(pRS);
//			BFC_RELEASE(pRes);
		}
	} catch (...)
	{
		throw;
	}
}

character *bfcos_resource_script = _TXT("\n\
ResourceName BFCOS\n\
\n\
Start Window FSelDlg Size (570,460) \"File Selection.\"\n\
	Matrix Size(4,0)\n\
	Button UP \"Up\" \n\
	Label \"Folder\"\n\
	Textbox FOLDER Size(37,1) \"/home/bill\"\n\
	Button SUBFOLDERS Checkbox \"Include Subfolders\"\n\
\
	Matrix Size(2,0)\n\
	Label \"Folders\"\n\
	List FOLDERS Size(62,5) \"\"\n\
\n\
	Matrix Size(2,0)\n\
	Label \"File types\"\n\
	DropList FILETYPES Size(5,6) \"*\",\"*.cal\"\n\
\n\
	Matrix Size(2,0)\n\
	Label \"Files\"\n\
	List FILES Size(64,12) \"\"\n\
	\n\
	Matrix Size(5,0)\n\
	Label \"File name\"\n\
	Textbox FILENAME Size(20,1) \"\"\n\
	Button ORGANIZER \"Organize\"\n\
	Button OPEN \"Open\"\n\
	Button CANCEL \"Cancel\"\n\
End FSelDlg\n\
\n\
");

}
