//*/
/*
					CBfcLocal_Terminal.h : 
	
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

// Event Driven Kernal

//  I have a problem with this class being defined as local - what if the terminal is not local??
//  - then term gets different process.
//  I think it matter of upside down-ian terminology - local ok, in my context, the programming context.
// Method of restricting the ability to power multiple computers at once wiht the same context.
//
//  True, so true my long windian friend.   I am sure that this is the proper terminology, see the word terminal in terminology?
//  Terminals can be multiple but must be related to software as single terminals, thus CBfcLocal_Terminal.
//
//

//#include <bfc.h>

// USerID // - a HANDLE, as it were, to each terminal

BFC_LOCAL_CLASS CBfcLocal_Terminal;
//
// perhaps this is the class for the new Network directory:
BFC_LOCAL_CLASS CBfcLocal_WorkGroup : public CBfcLocal_Object
{
public:
    typedef  unsigned long UserID;
    const CBfcLocal_Terminal   &GetLocalTerminal (CBfcLocal_WorkGroup::UserID UserID);
};

//
//
BFC_LOCAL_CLASS CBfcLocal_Terminal : public CBfcLocal_Object
{
    //  Video Caps
private:
    CBfcLocal_WorkGroup::UserID m_UserID;
    CBfc_2dArea					m_bfc_Area_ScreenDimensions;
    // On Keypress
};




