//*/
/*
					CBfcGUI_MenuWindow.h : 
	
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

namespace CBfcGUI
{

#define	MAX_MENU_DEPTH		10

BFC_GUI_CLASS MenuWindow : public Window
{
public:
	MenuWindow (GUI *p_GUI, const CBfc::STRING &csTitle, const EBFC_GUI_WINDOW_TYPE eType=WND_MAIN, Window *p_Parent=NULL,const Resource_ID resourceID=0,ResourceStore *p_ResourceStore=NULL);
	MenuWindow (GUI *p_GUI, const CBfc::STRING &csTitle, character *pMemScript, const EBFC_GUI_WINDOW_TYPE eType=WND_TOP, Window *p_Parent=NULL);
	~MenuWindow();
public:
	bool AddMenu(ResourceContainer *pRC);
	virtual int OnMessage(const Message &msg);

	virtual int OnKeyDown (character key);
protected:
	void RecordKeyboardShortcut (const STRING &csText, const Resource_ID id);
	
 	Array<ValuePair>	m_KeyboardShortcuts;
};

}

