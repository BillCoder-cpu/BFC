//*/
/*
					CBfcOS_Static.h : 
	
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
// Description: 
//
//
// Author: Bill Foster <wpf_software@hotmail.com>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//

namespace CBfcOS 
{

	BFC_OS_CLASS OS_Static
	{
	public:
		static void GetCreditsString(CBfc::STRING &sCredits);
		
		static bool SysCommand (const CBfc::STRING &sCommand);
		
		static bool GetCurrentPath(CBfc::Filename &getcwd);
		static bool SetCurrentPath(const CBfc::Filename &cwd);
		static void MakePathAbsolute(CBfc::Filename &foldername);
		static bool GetFileAttributes(const Filename &fName);
		
		static bool CreateDirectory (const Filename &dir);
		static bool ForceDirectory (const Filename &force);
	};
	
}


