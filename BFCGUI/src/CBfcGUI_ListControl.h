//*/
/*
					CBfcGUI_ListControl.h : 
	
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

namespace CBfcGUI
{

BFC_GUI_CLASS ListControl_Entry : public CBfc::STRING
{
public:
	ListControl_Entry (const STRING &csName);
private:
	CBfcImage::Bitmap	*m_p_Bitmap;
};

BFC_GUI_CLASS ListControl : public Data_Resource_Control, public Array<ListControl_Entry>
{
public:
	ListControl(GUI *p_GUI, const CBfc::STRING &csTitle, const EBFC_GUI_WINDOW_TYPE eType=WND_CHILD, Window *p_Parent=NULL,const Resource_ID resourceID=0);
	virtual	~ListControl();
private:
// need columns of data with column headers, 
//	Array<ListControl_Entry>	m_EntryArray;
};

}

