//*/
/*
					CBfcLocal_Computer.h : 
	
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


#ifndef __CBFCLOCAL_COMPUTER_H__
#define __CBFCLOCAL_COMPUTER_H__

BFC_LOCAL_CLASS CBfcLocal_Computer : public CBfcLocal_Object
{
public:
    typedef enum BFC_API tagEBFC_OSFamily {
        EBFC_OSFAMILY_Posix,
        EBFC_OSFAMILY_Windows,
    } EBFC_OSFamily;

    typedef enum BFC_API tagEBFC_OperatingSystem {
        EBFC_OS_Linux,
        EBFC_OS_FreeBSD,
        EBFC_OS_UnixGeneric,
        EBFC_OS_Windows2000,
        EBFC_OS_WindowsXP,
    } EBFC_OperatingSystem;

    bool Get_OperatingSystem (EBFC_OperatingSystem &e_os, EBFC_OSFamily &e_osFamily);
};


#endif // __CBFCLOCAL_COMPUTER_H__

