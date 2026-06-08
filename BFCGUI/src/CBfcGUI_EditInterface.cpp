//*/
/*
					CBfcGUI_EditInterface.cpp : 
	
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

namespace CBfcGUI {

int EditInterface::OnMessage (const Message &msg)
{
	switch (msg.GetID())
	{
		// Send these messages on to the object being edited!
		// So, Vector Shapes will all have mouse edit functions - yuck!
		//
		case BFCGUI_MSG_MOUSEDOWN:
			return OnMouseDown(msg.GetXY());
		case BFCGUI_MSG_MOUSEMOVE:
			return OnMouseMove(msg.GetXY());
		case BFCGUI_MSG_MOUSEUP:
			return OnMouseUp(msg.GetXY());
		case BFCGUI_MSG_MOUSEDOUBLECLICK:
			return OnMouseDoubleClick (msg.GetXY());
		case BFCGUI_MSG_MOUSEENTER:
			return OnMouseEnter ();
		case BFCGUI_MSG_MOUSELEAVE:
			return OnMouseLeave ();
		case BFCGUI_MSG_KEYPRESS:
			return OnKeyDown ((character)msg.GetParameter());
		case BFCGUI_MSG_KEYRELEASE:
			return OnKeyUp ((character)msg.GetParameter());
	}
	return BFCGUIDEFS_MESSAGE_NOT_PROCESSED;
}

int EditInterface::OnKeyUp (const character key)
{
	return BFCGUIDEFS_MESSAGE_NOT_PROCESSED;
}
int EditInterface::OnKeyDown (const character key)
{
	return BFCGUIDEFS_MESSAGE_NOT_PROCESSED;
}

int EditInterface::OnMouseMove(const Point2dU &pt)
{
	return BFCGUIDEFS_MESSAGE_NOT_PROCESSED;
}
int EditInterface::OnMouseDown(const Point2dU &pt)
{
	return BFCGUIDEFS_MESSAGE_NOT_PROCESSED;
}
int EditInterface::OnMouseUp(const Point2dU &pt)
{
	return BFCGUIDEFS_MESSAGE_NOT_PROCESSED;
}

int EditInterface:: OnMouseDoubleClick (const Point2dU &pt)
{
	return BFCGUIDEFS_MESSAGE_NOT_PROCESSED;
}

int EditInterface::OnMouseEnter ()
{
	return BFCGUIDEFS_MESSAGE_NOT_PROCESSED;
}

int EditInterface::OnMouseLeave ()
{
	return BFCGUIDEFS_MESSAGE_NOT_PROCESSED;
}

}
