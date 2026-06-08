//*/
/*
					CBfcImage_Object.h : 
	
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

#ifndef __H_BCImgObj
#define __H_BCImgObj

#include <BFC/BFC.h>


#ifdef WINDOWS
#	ifdef BFC_STATICLIB
#		define BFC_IMAGE_API
#		define BFC_IMAGE_TEMPLATE_API
#	else
#	   ifdef BFC_IMAGE_DLL
#			define BFC_IMAGE_API __declspec(dllexport)
#			define BFC_IMAGE_TEMPLATE_API BFC_IMAGE_API
#	   else
#			define BFC_IMAGE_API __declspec(dllimport)
#			define BFC_IMAGE_TEMPLATE_API //BFC_API
#		endif
#	endif
#else
#	ifdef UNIX
#		define BFC_IMAGE_API
#		define BFC_IMAGE_TEMPLATE_API
#	endif
#endif

#define BFC_IMAGE_CLASS class BFC_IMAGE_API
#define BFC_IMAGE_TEMPLATE_CLASS	class BFC_IMAGE_TEMPLATE_API
//#define BFC_IMAGE_CLASS	BFC_CLASS

#define	CBfcImage_Object	CBfc_Object

#endif // ifndef __H_BCImgObj
