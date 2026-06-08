//*/
/*
					CBfcGUI_MessageBox.cpp : 
	
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

namespace CBfcGUI
{

character Msgbox_resource_script[] = _TXT("\n\
ResourceName MSGBOX\n\
\n\
Start Window Window Size (450,260) \"Message:\"\n\
	Label Message \"Yes or No what you think?\"\n\
	Button OPEN \"Ok\"\n\
	Button CANCEL \"Cancel\"\n\
End Window\n\
\n");

//	Matrix Size(2,0)\n\

MessageBox::MessageBox(GUI *p_GUI, const CBfc::STRING &str_Message, Window *p_Parent)
	: DialogWindow (p_GUI, Msgbox_resource_script, p_Parent)
	, m_str_Message(str_Message), m_str_Title("Message!!!")
{

	ResourceEntity *p_RE = GetResourceStore()->LookupResourceEntity("Message", GetResourceID());
	if (p_RE)
		p_RE->SetText(str_Message);
	LayerSetTitle(m_str_Title);
}

int MessageBox::Alert(int type_mask)
{
//	execute();
	CDefault_DlgDP	dp(GetGUI());
	return dp.RunDlg(this);
}

/*
bool MessageBox::ProcessInput(Resource_Control *pRC, DialogWindow *pDS)
{
	return false;
}
*/

}


