//*/
/*
					CBfcGUI_MessageBox.h : 
	
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

#define	OK_MASK					0x01
#define	CANCEL_MASK			0x02
#define 	NO_MASK					0x08
#define	YES_MASK					0x04
#define 	YES_TO_ALL_MASK		0x10

BFC_GUI_CLASS  MessageBox : public DialogWindow
{
public:
	MessageBox(GUI *p_GUI, const CBfc_String &str_Message, Window *p_Parent=NULL);
	
	virtual ~MessageBox()
	{}

	int Alert(int type_mask=OK_MASK);
protected:

private:
//	UINT		m_u_Type;
	CBfc_String	m_str_Message;
	CBfc_String	m_str_Title;
};

}




