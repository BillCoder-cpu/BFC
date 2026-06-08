//*/
/*
					CBfc_Exception.h : 
	
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

#ifndef _BFC_ExcEPTION_H
#define _BFC_ExcEPTION_H

namespace CBfc {
// BCE_RETURNVALUE

BFC_CLASS Exception
{
public:
	typedef enum BFC_API tagBCE_Exception
	{
		EBFC_EXC_UNKNOWN,
		EBFC_EXC_COMPOUND,
//		EBFC_EXC_,
		EBFC_EXC_FILEOPEN,
		EBFC_EXC_OUTOFMEMORY,
        EBFC_EXC_UNEVEN_REFERENCECOUNT,
		EBFC_EXC_CANT_DELETE_DUETO_REFERENCECOUNT,
		EBFC_EXC_STRING_LIMITATION,
		EBFC_EXC_OUT_OF_RANGE,

		EBFC_EXC_ILLEGAL_ACCESS_UNLOCKED_CONSTANT,
		EBFC_EXC_ILLEGAL_ACCESS_ALREADYLOCKED,
  
  		EBFC_EXC_END_OF_FILE,

	} EBFC_Exception;


	virtual ~Exception() {};
	Exception () {};
	inline Exception (Exception::EBFC_Exception exception);
	inline Exception (Exception::EBFC_Exception exception, STRING &cs_additionalInfo);

public:
	EBFC_Exception	GetType() { return m_e_exception; }
	bool Log (characterPtr szDescription);
	virtual const characterPtr GetDescription () const;
private:
	EBFC_Exception	m_e_exception;
	STRING				m_cs_additionalInfo;
};


Exception :: Exception (EBFC_Exception e_exception)
	: m_e_exception (e_exception)
{
}

Exception :: Exception (EBFC_Exception exception, STRING &cs_additionalInfo)
	: m_e_exception (exception)
	, m_cs_additionalInfo (cs_additionalInfo)
{
}


class MemoryException : public Exception
{
public:
	MemoryException() { }
	virtual const characterPtr GetDescription () const
	{
		return characterPtr((characterPtrA)"Out Of Memory!");
	}
};

}

#endif // ifndef _BFC_ExcEPTION_H






