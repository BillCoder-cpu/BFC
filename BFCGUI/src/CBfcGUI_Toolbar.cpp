//*/
/*
					CBfcGUI_Toolbar.cpp : 
	
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
#include <BFC/BFCGUI.h>
#include "CFoxBFCWindow.h"

namespace CBfcGUI
{

ToolBar::ToolBar (GUI *p_GUI, const STRING &ResourceName, Window *p_Parent, ResourceStore *p_ResourceStore)
: DialogWindow (p_GUI,ResourceName,p_Parent,p_ResourceStore) //,WND_TOP)
{
}

OVERRIDE bool ToolBar::OnCreate ()
{
	CFoxDialogWindow *pFoxDlgWnd=(CFoxDialogWindow*)GetFoxWindow();
	pFoxDlgWnd->MakeNormal();
	const bool bRval = DialogWindow::OnCreate();
// 	pFoxDlgWnd->MakeNormal();
	
// 	Show();
// 	show(PLACEMENT_OWNER);
//  	getApp()->refresh();
	
	return bRval;
}

ToolBar::~ToolBar()
{
}

}

