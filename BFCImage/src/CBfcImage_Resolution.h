//*/
/*
					CBfcImage_Resolution.h : 
	
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

#ifndef __H_CBfcImage_Resolution
#define __H_CBfcImage_Resolution

#include "CBfcImage_Object.h"

namespace CBfcImage
{

// Can be a dpi, a scale % of original, or a specific target size.
BFC_IMAGE_CLASS Resolution
{
public:
	UINT	GetDotsPerInch ();
	UINT	GetDotsPerMeter();
//	bool	SetAsPercentageOfOriginal ();
//    bool	SetAsResolution ();
//    bool	SetAsTargetSize ();
    void operator = (const Resolution &resolution);
private:
	CBfc_Value	m_dotsPerMeter;
};


}

#endif // ndef __H_CBfcImage_Resolution




