//*/
/*
					CBfcRIP_Object.h : 
	
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

#ifndef __H_BCGUIObj
#define __H_BCGUIObj

#include <BFC.h>

#ifdef WINDOWS
#   ifdef BFC_GUI_DLL
#		define BFC_GUI_API __declspec(dllexport)
#		define BFC_GUI_TEMPLATE_API BFC_GUI_API
#   else
#		define BFC_GUI_API __declspec(dllimport)
#		define BFC_GUI_TEMPLATE_API //BFC_API
#   endif
#else
#	ifdef UNIX
#		define BFC_GUI_API
#		define BFC_GUI_TEMPLATE_API
#	endif
#endif

#define BFC_GUI_CLASS class BFC_GUI_API
#define BFC_GUI_TEMPLATE_CLASS	class BFC_GUI_TEMPLATE_API

//#define BFC_GUI_CLASS	BFC_CLASS

#define	CBfcGUI_Object	CBfc_Object

#endif // ifndef __H_BCGUIObj
