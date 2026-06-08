//*/
/*
					CBfcImage_2dArrayPixel.h : 
	
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

BFC_IMAGE_CLASS Image_2dArrayPixel : public CBfc_Object
{
public:
	Image_2dArrayPixel(const ColorSpace &colorSpace);
	Image_2dArrayPixel(const CBfc::Size2dU &size2d, const ColorSpace &colorSpace, CBfc_ReferencedAllocation *p_DupAllocation=NULL);
    virtual ~Image_2dArrayPixel();
    
    Image_2dArrayPixel *Dup()const;
    
    bool crop(const CBfc::Rect2dU &chunk);
    bool Enlarge(const CBfc::Size2dU &size);

    BYTE           *GetPtr (const CBfc::Position2dU &pos, const UINT u_membersNeeded) const;
    BYTE           *GetPtr (const UINT u_x, const UINT u_y, const UINT u_membersNeeded) const;
    bool            ReleasePtr (BYTE *p);
    UINT            BytesRequiredToStore (const UINT u_pixelCount) const;
	void		  SetSize(const CBfc::Size2dU &size2d);		// Re-allocates
protected:
private:
	void			Allocate();
private:
    ColorSpace				m_colorSpace;
    UINT                    		m_u_effectiveBitsPerPixel;
    CBfc::Size2dU				m_size;
    UINT                		m_u_pitchBytes;
    CBfc_ReferencedAllocation 	*m_p_allocation;
};

}


