//*/
/*
					CBfcGUI_TerminalWindow.cpp : 
	
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

TerminalWindow::TerminalWindow(TerminalWindow *p_Parent)
	: m_p_parentWindow(p_Parent), m_b_Dirty(0), m_b_Visible(true)
{
}

int OVERRIDE TerminalWindow::OnMessage (const Message &msg)
{
	switch (msg.GetID())
	{
		case	BFCGUI_MSG_KEYPRESS:
			return OnKeyDown ((character)msg.GetParameter());
		case	BFCGUI_MSG_KEYRELEASE:
			return OnKeyUp ((character)msg.GetParameter());
		case	BFCGUI_MSG_MOUSEMOVE:
			return OnMouseMove (msg.GetXY());  // This is an override so we get control of the main window.
		case	BFCGUI_MSG_MOUSEUP:
			return OnMouseUp ();    //
		case	BFCGUI_MSG_MOUSEDOWN:
			return OnMouseDown (msg.GetXY());  //
		case	BFCGUI_MSG_MOUSEENTER:
			return OnMouseEnter();
		case	BFCGUI_MSG_MOUSELEAVE:
			return OnMouseLeave();
		case	BFCGUI_MSG_MOUSEDOUBLECLICK:
			return OnMouseDoubleClick (msg.GetXY());   //
		case	BFCGUI_MSG_FOCUSIN:
			return OnFocusIn ();  //
		case	BFCGUI_MSG_FOCUSOUT:
			return OnFocusOut ();  // etc.
	}
	return BFCGUIDEFS_MESSAGE_NOT_PROCESSED;
}

int TerminalWindow::OnKeyUp (character c)
{
   return BFCGUIDEFS_MESSAGE_NOT_PROCESSED;
}

int TerminalWindow::OnKeyDown (character c)
{
   return BFCGUIDEFS_MESSAGE_NOT_PROCESSED;
}

int TerminalWindow::OnMouseMove (const CBfc::Point2dU &pt)  // This is an override so we get control of the main window.
{
   return BFCGUIDEFS_MESSAGE_NOT_PROCESSED;
}

int TerminalWindow::OnMouseUp ()    //
{
   return BFCGUIDEFS_MESSAGE_NOT_PROCESSED;
}

int TerminalWindow::OnMouseDown (const CBfc::Point2dU &pt)  //
{
   return BFCGUIDEFS_MESSAGE_NOT_PROCESSED;
}

int TerminalWindow::OnMouseEnter ()    //
{
   return BFCGUIDEFS_MESSAGE_NOT_PROCESSED;
}

int TerminalWindow::OnMouseLeave ()  //
{
   return BFCGUIDEFS_MESSAGE_NOT_PROCESSED;
}

int TerminalWindow::OnMouseDoubleClick (const CBfc::Point2dU &pt)    // etc.
{
   return BFCGUIDEFS_MESSAGE_NOT_PROCESSED;
}

int TerminalWindow::OnFocusIn ()    //
{
   return BFCGUIDEFS_MESSAGE_NOT_PROCESSED;		// bug in fox - must say we processed!!!
}

int TerminalWindow::OnFocusOut ()
{
   return BFCGUIDEFS_MESSAGE_NOT_PROCESSED;
}

bool TerminalWindow::GetOutlineShape (CBfcVector::Shape2d_PTR &p_shape) const
{
	if (m_p_ShapeOutline)
	{
		p_shape = m_p_ShapeOutline;
	}
	return false;
}

void TerminalWindow :: SetClip (const CBfcVector::Shape2d_PTR &p_shapeClip)
{
	BFC_RELEASE (m_p_ShapeClip);
	m_p_ShapeClip = (CBfcVector::Shape2d*)p_shapeClip->Dup();
}

int OVERRIDE TerminalWindow::DoModal()
{
	return false;
}



}
