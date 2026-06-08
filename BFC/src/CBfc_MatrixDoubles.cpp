//*/
/*
					CBfc_MatrixDoubles.cpp : 
	
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

#include <BFC/BFC.h>

void CBfc_MatrixDoubles :: operator = (const CBfc_MatrixDoubles &mulMatrix)
{
}

bool CBfc_MatrixDoubles :: IsSameSize (const CBfc_MatrixDoubles &mulMatrix)
{
	CBfc_2dSize	size1, size2;
	if (GetSize(size1) && mulMatrix.GetSize(size2))
		return (size1 == size2);
	return false;
}

void CBfc_MatrixDoubles :: operator *= (const CBfc_MatrixDoubles &mulMatrix)
{
	if (IsSameSize (mulMatrix))
	{
	}
}


