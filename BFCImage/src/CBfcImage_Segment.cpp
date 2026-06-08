//*/
/*
					CBfcImage_Segment.cpp : 
	
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

//
//  CBfcImage_Segment.cpp
//

#include <BFC/BFCImage.h>

namespace CBfcImage
{

	using namespace CBfc;
	
bool Image_Segment :: operator== (Image_Segment &otherSegment)
{
	return (GetSourceRectangle() == otherSegment.GetSourceRectangle());
}

void Image_Segment :: SetScale (ValuePair &scale)
{
    m_Scale = scale;
}

void Image_Segment :: GetScale (ValuePair &scale) const
{
    scale = m_Scale;
}


bool Image_Segment :: EncapsulatesSegment (Image_Segment *p_segment)
{
	// If scale is too small, cant
    if (m_Scale < p_segment->GetScale())
    	return false;
    if (!m_rectSource.Encapsulates (p_segment->GetSourceRectangle()))
    	return false;
    return true;
}

}

