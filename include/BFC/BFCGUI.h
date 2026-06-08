//*/
/*
					BFCGUI.h : 
	
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

/*
	BFCGUI.h

  Copyright (C) 2003 by William P. Foster, all rights reserved.

*/

#ifndef __H_BFCGui_		// pragma once
#define __H_BFCGui_

#include <cstdint>

#include "BFC/BFC.h"
#include "BFC/BFCVector.h"	// Required for 2dShapes
#include "BFC/BFCImage.h"	// Required
#include "BFC/BFCScript.h"  // Required for Resource Scripts
// #include "Gears.h"  // Required for Resource Scripts

typedef unsigned char	BFCGUI_ALPHA_VALUE;	// 8 bit Alpha channel.

namespace CBfcGUI
{
	typedef uintptr_t Resource_ID;
};

#include "../BFCGUI/src/CBfcGUI_Object.h"
#include "../BFCGUI/src/CBfcGUI_Brush.h"
#include "../BFCGUI/src/CBfcGUI_Message.h"

#include "../BFCGUI/src/CBfcGUI_ResourceEntity.h"   // Resource Editor needed.
#include "../BFCGUI/src/CBfcGUI_ResourceStore.h"   // Resource Editor needed.

#include "../BFCGUI/src/CBfcGUI_EditInterface.h"
#include "../BFCGUI/src/CBfcGUI_TerminalWindow.h"
#include "../BFCGUI/src/CBfcGUI_Window.h"
#include "../BFCGUI/src/CBfcGUI_CursesWindow.h"

#include "../BFCGUI/src/CBfcGUI_MenuWindow.h"
#include "../BFCGUI/src/CBfcGUI_Resource.h"	   // Resource Editor needed.
#include "../BFCGUI/src/CBfcGUI_ScriptResource.h"   // Resource Editor needed.

#include "../BFCGUI/src/CBfcGUI_ListControl.h"
#include "../BFCGUI/src/CBfcGUI_TreeControl.h"
#include "../BFCGUI/src/ProgressControl.h"

#include "../BFCGUI/src/CBfcGUI_DialogWindow.h"

#include "../BFCGUI/src/CBfcGUI_MessageBox.h"

#include "../BFCGUI/src/ImageWindow.h"
#include "../BFCGUI/src/CBfcGUI_Toolbar.h"

#include "../BFCGUI/src/CBfcGUI_GLWindow.h"
#include "../BFCGUI/src/CBfcGUI.h"


#include "BFCOS.h"  // 

#endif // ifndef __H_BFCGui_ pragma once






