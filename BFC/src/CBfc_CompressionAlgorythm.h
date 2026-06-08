//*/
/*
					CBfc_CompressionAlgorythm.h : 
	
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

CBfc_CompressionAlgorythm.h



*/

#ifndef _BFC_BCCOMPRESSION_ALGORYTHM_H_
#define  _BFC_BCCOMPRESSION_ALGORYTHM_H_

#include "BFCDefs.h"

BFC_CLASS CBfc_CompressionAlgorythm;

typedef struct {
	long				l_headerSignature;	// Provide unique first 4 bytes.
//	CBfc_CompressionAlgorythm :: EBC_CompressionSignature
} CBfc_CompressionHeader;

BFC_CLASS CBfc_CompressionAlgorythm
{
public:
	//  If you are an official BFC compression, you need to be in this list.
	typedef enum
	{
		EBFC_CMPRALG_Unknown,
		EBFC_CMPRALG_Default,
		EBFC_CMPRALG_RLE,
		EBFC_CMPRALG_LZW,
		EBFC_CMPRALG_NO,
	} EBFC_CompressionAlgorythm;

	virtual EBFC_RETURNVALUE	CompressBytes (const BYTE_PTR p_inData, long l_inLength, BYTE *p_outData, long &l_outLength)=0;
	virtual EBFC_RETURNVALUE	DecompressBytes (const BYTE_PTR p_inData, BYTE_PTR &p_outData, const long l_maxOutLength, long &l_outLength)=0;
	virtual bool	IsLossless () { return true; }
protected:
	EBFC_CompressionAlgorythm		m_ECompressionAlgorythm;
};

BFC_CLASS CBfc_CompressionRLE : public CBfc_CompressionAlgorythm
{
public:
	virtual EBFC_RETURNVALUE	CompressBytes (const BYTE_PTR p_inData, long l_inLength, BYTE *p_outData, long &l_outLength)=0;
	virtual EBFC_RETURNVALUE	DecompressBytes (const BYTE_PTR p_inData, BYTE_PTR &p_outData, const long l_maxOutLength, long &l_outLength)=0;
protected:
	static EBFC_CompressionAlgorythm		m_ECompressionAlgorythm;
//	virtual EBC_CompressionSignature EBC_CA_RLE_Compression;
};

BFC_CLASS CBfc_BestCompression : public CBfc_CompressionRLE
{
};

#endif		// ndef _BFC_BCCOMPRESSION_ALGORYTHM_H_
