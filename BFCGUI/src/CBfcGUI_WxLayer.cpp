//*/
/*
					CBfcGUI_WxLayer.cpp : 
	
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

#ifdef USING_WXWIDGETS

namespace CBfcGUI
{

CBfcGUI_UILayerWindow :: CBfcGUI_UILayerWindow (GUI *p_GUI, CBfcGUI_UILayerWindow *p_Parent)
	:  m_p_GUI (p_GUI)
	, m_p_Parent(p_Parent)
	, CWxBFCWindow(p_Parent ? p_Parent : (wxScrolledWindow*)p_GUI->m_p_MainWindow)
{
}

bool CBfcGUI_UILayerWindow :: Create ()
{
  CWxBFCWindow::Create(m_p_Parent, m_windowID);
  CWxBFCWindow::SetFocus();
  return true;
}

bool CBfcGUI_UILayerWindow :: Show()
{
  return CWxBFCWindow::Show( TRUE );
}

void CBfcGUI_UILayerWindow :: SetSize (CBfc_2dSize &size)
{
	UINT	w,h;
    size.Get (w,h);
	CWxBFCWindow::DoSetSize (-1,-1,w,h);
}

int CBfcGUI_UILayerWindow :: DoModal()
{
//  return GetGUI()->GetApp()->runModalFor(this);
	return false;
}

void CBfcGUI_UILayerWindow :: EndModal(const int i_exitvalue)
{
//	GetGUI()->GetApp()->stopModal(this,i_exitvalue) ;
}


void CBfcGUI_UILayerWindow :: SetText(const CBfc_String &cs)
{
	SetText(cs.GetPtr());
}

void CBfcGUI_UILayerWindow :: SetText(character *s)
{
	if (m_p_Text)
	{
	}
}

}


#endif	// ifdef USING_WXWIDGETS


