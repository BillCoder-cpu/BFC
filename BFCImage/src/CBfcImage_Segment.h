//*/
/*
					CBfcImage_Segment.h : 
	
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

namespace CBfcImage
{


BFC_IMAGE_CLASS Image_Segment
{
public:
    Image_Segment() {};
	bool EncapsulatesSegment	(Image_Segment *p_segment);
	inline Resolution		&GetResolution () {
    	return m_resolution;	}

        // The source rectangle is the same for all scales
        //   it always equals the size within the size of the image at
 	inline CBfc_2dRect			&GetSourceRectangle () {
    	return m_rectSource; }

    bool   operator== (Image_Segment &otherSegment);
protected:
	void SetScale (CBfc::ValuePair &scale);
	void GetScale (CBfc::ValuePair &scale) const;
	CBfc::ValuePair &GetScale(void) {
		return m_Scale;
	}
private:
	CBfc::ValuePair  m_Scale;

	CBfc::Rect2d 	m_rectSource;
	Resolution		m_resolution;
};

}

