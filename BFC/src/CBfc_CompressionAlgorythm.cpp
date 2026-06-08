//*/
/*
					CBfc_CompressionAlgorythm.cpp : 
	
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
	CBfc_CompressionAlgorythm.cpp


*/

#include "CBfc_CompressionAlgorythm.h"

//CBfc_CompressionAlgorythm::EBFC_CompressionAlgorythm
//         CBfc_CompressionRLE::m_ECompressionAlgorythm = EBFC_CMPRALG_RLE;


EBFC_RETURNVALUE CBfc_CompressionRLE :: CompressBytes (const BYTE_PTR p_inData, long l_inLength, BYTE_PTR p_outData, long &l_outLength)
{
	return EBFC_EXC_Success;
}

EBFC_RETURNVALUE CBfc_CompressionRLE :: DecompressBytes (const BYTE_PTR p_inData, BYTE_PTR &p_outData, const long l_maxOutLength, long &l_outLength)
{
	return EBFC_EXC_Success;
}



