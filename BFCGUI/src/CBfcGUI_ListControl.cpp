//*/
/*
					CBfcGUI_ListControl.cpp : 
	
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

namespace CBfcGUI
{

ListControl_Entry::ListControl_Entry (const STRING &csName)
:	CBfc::STRING(csName)
{
}

ListControl::ListControl(GUI *p_GUI, const CBfc::STRING &csTitle, const EBFC_GUI_WINDOW_TYPE eType, Window *p_Parent,const Resource_ID resourceID)
: Data_Resource_Control (p_GUI, p_Parent, csTitle, resourceID, eType)
{
}

ListControl::~ListControl()
{
}

}
