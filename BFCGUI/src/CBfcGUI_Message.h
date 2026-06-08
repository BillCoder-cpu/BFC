//*/
/*
					CBfcGUI_Message.h : 
	
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
#define   BFCGUIDEFS_MESSAGE_PROCESSED      1
#define   BFCGUIDEFS_MESSAGE_NOT_PROCESSED  0

#define	BFCGUI_MSG_NO_OP				0

#define	BFCGUI_MSG_KEYPRESS				0x1001
#define	BFCGUI_MSG_KEYRELEASE			0x1000
#define	BFCGUI_MSG_MOUSEMOVE			0x1002
#define	BFCGUI_MSG_MOUSEUP				0x1003
#define	BFCGUI_MSG_MOUSEDOWN			0x1004
#define	BFCGUI_MSG_MOUSEDOUBLECLICK		0x1005
#define	BFCGUI_MSG_MOUSEENTER			0x1006
#define	BFCGUI_MSG_MOUSELEAVE			0x1007
#define	BFCGUI_MSG_FOCUSIN				0x1008
#define	BFCGUI_MSG_FOCUSOUT				0x1009
#define	BFCGUI_MSG_DESTROY				0x100A

#define	BFCGUI_MSG_REDRAW				0x1020
#define	BFCGUI_MSG_RESIZE				0x1021
#define	BFCGUI_MSG_BUTTONPRESS			0x1022

namespace CBfcGUI
{

	typedef unsigned int	Message_ID;


BFC_GUI_CLASS Message
{
public:
	Message(const Message_ID ID=BFCGUI_MSG_NO_OP,void *parameter1=NULL)
		: m_ID(ID), m_parameter1((uintptr_t)parameter1)
	{}

	Message(const Message_ID ID,uintptr_t parameter1)
		: m_ID(ID), m_parameter1(parameter1)
	{}

	void Set (const Message_ID ID, void *parameter1)
	{
		m_ID = ID;
		m_parameter1 = (uintptr_t)parameter1;
	}

	Message_ID GetID() const {
		return m_ID;
	}
//	Resource_ID	GetButton() const {
//		return (Resource_ID)m_parameter1;
//	}
	uintptr_t GetParameter() const {
		return m_parameter1;
	}
	CBfc::Point2dU GetXY() const
	{
		intptr_t	u=(intptr_t)m_parameter1;
		return CBfc::Point2dU (u&0xffff, u>>16);
	}
private:
	Message_ID	m_ID;
	uintptr_t	m_parameter1;
};

}


