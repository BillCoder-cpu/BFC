//*/
/*
					CBfcGUI.cpp : 
	
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

//
//
//

#include <BFC/BFCGUI.h>

// #include "CFoxBFCWindow.h"

using namespace CBfc;

namespace CBfcGUI
{

GUI::GUI (CBfcOS::Application *p_App, ScriptResource *res)
	: m_p_Application(p_App)
	, m_p_MainWindow(NULL)
	, m_p_GLVisual(NULL)
//	, m_p_ResourceStore(NULL)
{
	if (res)
		m_p_ResourceStore = res->LoadResources(); 
//	Load m_p_ResourceStore
}


Window *GUI::NewWindow ()
{
	Window *pWnd = new Window(this,"");
	return pWnd;
}

bool GUI::SetMainWindow(MenuWindow *p_MainWindow,const CBfc::STRING *p_csMenuName)
{
	m_p_MainWindow=p_MainWindow;
	if (m_p_MainWindow)
	{
		if (p_csMenuName)
		{
			CBfcGUI::Resource_ID	rMenuID=GetResourceStore()->LookupResourceID(*p_csMenuName);
			if (rMenuID)
				m_p_MainWindow->AddMenu(GetResourceStore()->LookupResourceContainer(rMenuID));
		}
#ifdef USING_FOX
		m_p_MainWindow->Create();
		m_p_MainWindow->Show();
#endif
		return true;
	}
	return false;
}

bool GUI::CreateMainWindow (const Size2dU &size, const CBfc::STRING &csTitle)
{
	if (!m_p_MainWindow)
		SetMainWindow(new MenuWindow(this,csTitle,WND_MAIN));
	if (m_p_MainWindow)
	{
		m_p_MainWindow->SetWindowSize (size);
		return true;
	}
	return false;
}

FX::FXGLVisual *GUI::GetVisual()
{
	if (!m_p_GLVisual)
		m_p_GLVisual = (FX::FXGLVisual *)UILayerWindow::CreateVisual (m_p_Application->GetLayerAppPointer());
	return m_p_GLVisual;
}

//
// Make sure to call UnregisterResourceStore before deleting the data p_ResourceStore unless at end of program.
bool GUI::RegisterResourceStore	(ResourceStore* p_ResourceStore)
{
	if (p_ResourceStore)
		return m_ResourceStores.Add(&p_ResourceStore);
	return false;
}

//
//
bool	GUI::UnregisterResourceStore(ResourceStore* p_ResourceStore)
{
	INT64	index=m_ResourceStores.Find(p_ResourceStore);
	if (index <0)
		return false;
	return (m_ResourceStores.RemoveAt((int)index) != 0);
}

/**
 *  Default to the main one, but could be asking for a supplemental resource store.
 * @param resname 
 * @return 
 */
ResourceStore	*GUI::GetResourceStore(char *resname)
{
	if (resname)
	{
		STRING	csSearchName(resname);
		ResourceStore** pp_ResourceStore;
		ULONG		uIndex=m_ResourceStores.StartIteration();
		while ((pp_ResourceStore=m_ResourceStores.GetNext(uIndex)))
		{
			STRING	csName;
			(*pp_ResourceStore)->GetName(csName);
			if (csName == csSearchName)
				return *pp_ResourceStore;
		}
		throw 0;
		return NULL;
	}
	return m_p_ResourceStore;
}

AppLayerPtr	GUI::GetAppLayerPtr ()
{
	return m_p_Application->GetLayerAppPointer(); 
}

CBfcOS::Application *GUI::GetAppPtr ()
{
	return m_p_Application;  
}

DialogWindow *GUI::LoadDialog(const CBfc::STRING &csIDName,Window *pParent)
{
	return new DialogWindow(this,csIDName,pParent);
// 	Resource_ID	rID=m_p_ResourceStore->LookupResourceID(csIDName);
// 	if (rID)
// 	{
// 		DialogWindow	*pDlgWnd = new DialogWindow(this,pParent,rID);
// 		return pDlgWnd;
// 	}
// 	return NULL;
}

}



