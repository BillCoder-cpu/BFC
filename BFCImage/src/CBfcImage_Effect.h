//*/
/*
					CBfcImage_Effect.h : 
	
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
   CBfcImage_Effect.h
*/

namespace CBfcImage
{

BFC_IMAGE_CLASS Image_Effect : public CBfcImage_Object
{
	public:
		virtual ~Image_Effect()
			{}
	public:
		virtual bool ApplyToBuffer (Image_Buffer &buffer)
						{ return false; }
		virtual bool Requires_Assessment_of_Entire_Image()
						{ return false; }
//		virtual bool	AssessImage (Image &image);		// this gets diffuicult because we must provide a partialy processed image
};

typedef Image_Effect	Image_Filter;

typedef CBfc::Array<Image_Effect *> Image_EffectsArray;

}

