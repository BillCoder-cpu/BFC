//*/
/*
					CBfcImage_ScriptImage.h : 
	
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

	Needs to be able to do certain things.
	
	works apon a single image, possibly creating multiple images.
	
	Examples:
		Variable $(basedir) = "~/Images/"
		
		set DPI=300 (dpcm=100)
		Resize Crop Whitespace 4" by 6", 100 dpcm
		Effect AutoAdjust
		
		Image	img1;
		Load img1 with "$(basedir)watermark.gif"
		Merge with img1.
		
		Convert ColorSpace Indexed_8
		Save as $(basename)_water.$(extension).
		

*/

namespace CBfcImage
{

	///////////////////////////////////////////////////////////////////////
	///
	///
	/// Script_Var is like Script_XML only that certain things are supported, like
	/// 		Variable $(basedir);
	///			Set $(basedir) "~/Images/";
	///			
	///
	//////////////////////////////////////////////////////////////////////

	BFC_IMAGE_CLASS ScriptImage : public CBfcScript::Script_XML
	{
		public:
	//  ScriptResource ();  // Constuctor
			ScriptImage (CBfc_Stream &resourceStream);
			virtual ~ScriptImage() {}

			bool Process(Image &image);
			bool Process(Image_Buffer *p_buffer);

		protected:
		private:
	};

}

