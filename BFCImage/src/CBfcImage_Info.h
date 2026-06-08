//*/
/*
					CBfcImage_Info.h : 
	
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
	CBfcImage_Dll.h - Include file for the imaging dll
   Copyright (C) 2001-2002 by William Paul Foster, all rights reserved.
*/
/*
   Development note:

   In designing this engine, I will need to think deeply about other libraries
	such as that water bird, the SandPiper.

   Methodology:
	  A pipeline of operations is constructed.
	  This pipeline has a pointer, and you can call process line on that pipeline.
		 At this pointm the next line of data is processed.


  Todo:
	 locate a public domain .FPX library, and go from there (why re-invent the wheel?)



*/

#ifndef __H_CBfcImage_Info
#define __H_CBfcImage_Info

namespace CBfcImage
{

BFC_IMAGE_CLASS Image_Info : public CBfcImage_Object
{
public:
   inline Resolution &GetResolution () {
		return m_resolution; };

   inline ColorSpace &GetColorSpace () {
		return m_colorSpace; };

	inline CBfc::Size2dU &GetSize () {
		return m_size; };

private:
   ColorSpace			m_colorSpace;
   Resolution			m_resolution;	// dpi
   CBfc::Size2dU		m_size;
//   CBfcImage_
};

}

#endif // __H_CBfcImage_Info

