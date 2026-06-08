//*/
/*
					ResourceWindow.cpp : 
	
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

#include <BFC/BFCGUI.h>

using namespace CBfc;

namespace CBfcGUI
{

#include "DX_Intermediate.inc.cpp"		// working decent way, but not advanced enough!!! replacement in Gears
#include "DP_Intermediate.inc.cpp"

ResourceWindow::ResourceWindow(GUI *p_GUI, const STRING &csTitle, Window *p_Parent)
	: MenuWindow(p_GUI, csTitle, p_Parent?WND_CHILD:WND_TOP, p_Parent)
	, m_pRC(NULL)
{
	InitializeResourceID();
}


ResourceWindow::ResourceWindow(GUI *p_GUI, const STRING &ResourceName, const EBFC_GUI_WINDOW_TYPE eType, Window *p_Parent, ResourceStore *p_ResourceStore)
	: MenuWindow(p_GUI, ResourceName, eType, p_Parent, p_ResourceStore ? p_ResourceStore->LookupResourceID(ResourceName) : p_GUI->GetResourceStore()->LookupResourceID(ResourceName), p_ResourceStore)
	, m_pRC(NULL)
{
	InitializeResourceID();
}
	

ResourceWindow::ResourceWindow(GUI *p_GUI,  character *pMemScript, Window *p_Parent)
	: MenuWindow(p_GUI, STRING("Resource"), pMemScript, WND_DIALOG, p_Parent)
	, m_pRC(NULL)
{
	InitializeResourceID();
}

ResourceContainer *ResourceWindow::GetResourceContainer() const
{
	return m_pRC;
}

// Utilize by sources that derive from the standard resource script by
// including the definition in memory or something.
void ResourceWindow::SetResourceContainer(ResourceContainer *p_RC)
{
	m_pRC = p_RC;

	STRING	csName;
	GetResourceContainer()->GetText(csName);
	if (csName.IsEmpty())
		GetResourceContainer()->GetName(csName);
	LayerSetTitle(csName);
}

void ResourceWindow::InitializeResourceID()
{
	if (GetResourceID())
	{
		ResourceContainer *pRC = GetResourceStore()->LookupResourceContainer(GetResourceID());
		if (pRC)
			SetResourceContainer(pRC);
	}
}



}
