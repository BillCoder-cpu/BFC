//*/
/*
					CBfcGUI_MenuWindow.cpp : 
	
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
MenuWindow::MenuWindow (GUI *p_GUI, const CBfc::STRING &csTitle, const EBFC_GUI_WINDOW_TYPE eType, Window *p_Parent,const Resource_ID resourceID,ResourceStore *p_ResourceStore)
	: Window (p_GUI, csTitle, eType, p_Parent, resourceID, p_ResourceStore)
{
}

MenuWindow::MenuWindow (GUI *p_GUI, const CBfc::STRING &csTitle, character *pMemScript, const EBFC_GUI_WINDOW_TYPE eType, Window *p_Parent)
	: Window (p_GUI, csTitle, pMemScript, eType, p_Parent)
{
}

/**
 * 
 * @return 
 */
MenuWindow::~MenuWindow()
{
}


int OVERRIDE MenuWindow::OnMessage(const Message &msg)
{
	return Window::OnMessage(msg);
}

//Currently only good enough for one menu level deep, we need sub-sub menus and an end submenu label
bool MenuWindow::AddMenu(ResourceContainer *pRC)
{
	ResourceEntity	*pMenuEntity;
	CBfc::Array<ResourceEntity> *pMenuEntityList = pRC->GetEntityList();
	STRING		csText;
	Menu		menu(this);

	ULONG uIr=pMenuEntityList->StartIteration();
	while (pMenuEntity=pMenuEntityList->GetNext(uIr))
	{
		switch (pMenuEntity->GetType())
		{
			case BFC_GUIRES_RESOURCE_KEY_SUBMENU:
				pMenuEntity->GetText(csText);
				if (!menu.StartSubmenu(csText))
					return false;
				break;
			case BFC_GUIRES_RESOURCE_KEY_MENU_ENTRY:
				pMenuEntity->GetText(csText);
				{
					const Resource_ID id = pMenuEntity->GetResourceID();
					menu.AddEntry(csText, id);
					RecordKeyboardShortcut (csText, id);
				}
				break;
			case BFC_GUIRES_CONTAINER_KEY_END:
				menu.EndSubmenu();
				break;
		}
	}
	return true;

  // File Menu entries
//  new FXMenuSeparator(menu);
//  new FXMenuCheck(menu,"&Editable\t\tDocument editable.",editor,FXText::ID_TOGGLE_EDITABLE);
/*
  // Recent file menu; this automatically hides if there are no files
  FXMenuSeparator* sep1=new FXMenuSeparator(filemenu);
  sep1->setTarget(&mrufiles);
  sep1->setSelector(FXRecentFiles::ID_ANYFILES);
  new FXMenuCommand(filemenu,NULL,NULL,&mrufiles,FXRecentFiles::ID_FILE_1);
  new FXMenuCommand(filemenu,NULL,NULL,&mrufiles,FXRecentFiles::ID_FILE_2);
  new FXMenuCommand(filemenu,NULL,NULL,&mrufiles,FXRecentFiles::ID_FILE_3);
  new FXMenuCommand(filemenu,NULL,NULL,&mrufiles,FXRecentFiles::ID_FILE_4);
  new FXMenuCommand(filemenu,NULL,NULL,&mrufiles,FXRecentFiles::ID_FILE_5);
  new FXMenuCommand(filemenu,NULL,NULL,&mrufiles,FXRecentFiles::ID_FILE_6);
  new FXMenuCommand(filemenu,NULL,NULL,&mrufiles,FXRecentFiles::ID_FILE_7);
  new FXMenuCommand(filemenu,NULL,NULL,&mrufiles,FXRecentFiles::ID_FILE_8);
  new FXMenuCommand(filemenu,NULL,NULL,&mrufiles,FXRecentFiles::ID_FILE_9);
  new FXMenuCommand(filemenu,NULL,NULL,&mrufiles,FXRecentFiles::ID_FILE_10);
  new FXMenuCommand(filemenu,"&Clear Recent Files",NULL,&mrufiles,FXRecentFiles::ID_CLEAR);
  FXMenuSeparator* sep2=new FXMenuSeparator(filemenu);
  sep2->setTarget(&mrufiles);
  sep2->setSelector(FXRecentFiles::ID_ANYFILES);
  new FXMenuCommand(filemenu,"&Quit\tCtl-Q",getApp()->quiticon,getApp(),Adie::ID_CLOSEALL);
*/
}

void MenuWindow::RecordKeyboardShortcut (const STRING &csText, const Resource_ID id)
{
#if 1
	int	offset = csText.Find('^');
	if (offset >= 0)
	{
		character	c = csText.GetAt (offset+1);
		if (c >= 'A' && c <= 'Z')
			c = c - 'A' + 1;
		else if (c >= 'a' && c <= 'z')
			c = c - 'a' + 1;
		else
			c = 0;
		if (c)
		{
			ValuePair	cut(c,(UINT)id);
			m_KeyboardShortcuts.Add (&cut);
		}
	}
#endif
}

int OVERRIDE MenuWindow::OnKeyDown (character key)
{
#if 1
	ULONG		idx=m_KeyboardShortcuts.StartIteration();
	
	ValuePair	*vp;
	while  ((vp = m_KeyboardShortcuts.GetNext(idx)))
	{
		if ((UINT)vp->GetX() == key)
		{
			return OnMessage(Message (BFCGUI_MSG_BUTTONPRESS, (void *)vp->GetY()));
// 			return BFCGUIDEFS_MESSAGE_PROCESSED;
		}
	}
#endif
	return Window::OnKeyDown(key);
}



} // namespace

