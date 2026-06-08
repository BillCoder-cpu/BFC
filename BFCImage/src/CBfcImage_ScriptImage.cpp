//*/
/*
					CBfcImage_ScriptImage.cpp : 
	
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
#include <BFC/BFCImage.h>

using namespace CBfc;

namespace CBfcImage 
{

	static characterPtr Image_KeyWords[] = 
	{
		STATICBYTES("Effect"),
		STATICBYTES("Save"),
		STATICBYTES("Load"),			// Load $(var) with "$(basedir)/image.jpg"
		STATICBYTES(""),
		characterPtr(NULL)
	};

	static characterPtr Image_AttributeKeys[] = 
	{
		STATICBYTES("Position"),
		STATICBYTES("Shape"),
		STATICBYTES("Size"),
		STATICBYTES("Default"),
		STATICBYTES("Radio"),
		STATICBYTES("Checkbox"),
		STATICBYTES("Group"),
		STATICBYTES("Checked"),
		STATICBYTES("Number"),
		STATICBYTES("Integer"),
		STATICBYTES("Password"),
		STATICBYTES("Currency"),
		STATICBYTES("Percent"),
		STATICBYTES("Hotkey"),
		STATICBYTES("Align"),
		characterPtr(NULL)
	};

	static characterPtr  Image_ResourceKeys[] = {
		STATICBYTES("Window"),
		STATICBYTES("Menu"),
		STATICBYTES("SubMenu"),
		STATICBYTES("Entry"),
		STATICBYTES("Seperator"),
		STATICBYTES("End"),

		STATICBYTES("Button"),
		STATICBYTES("Label"),
		STATICBYTES("Textbox"),
		STATICBYTES("Cursesbox"),
		STATICBYTES("List"),
		STATICBYTES("Listbox"),
		STATICBYTES("Combobox"),
	
		STATICBYTES("Horizontal_seperator"),
		STATICBYTES("Vertical_seperator"),
		STATICBYTES("DropList"),

		STATICBYTES("Spacer"),
		STATICBYTES("Switcher"),
		STATICBYTES("Matrix"),

		characterPtr(NULL)
	};

	static characterPtr  BfcRes_ShapeKeys[] = {
		STATICBYTES("Rectangle"),
		STATICBYTES("Bitmap"),
		STATICBYTES("Oval"),
		STATICBYTES("Polygon"),
		characterPtr(NULL)
	};



	ScriptImage::ScriptImage (CBfc_Stream &resourceStream)
	: CBfcScript::Script_XML (resourceStream)
	{
	}

	bool ScriptImage::Process(Image_Buffer *p_buffer)
	{
		return false;
	}

	bool ScriptImage::Process(Image &image)
	{
		return false;
	}
			
}
