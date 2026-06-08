//*/
/*
					CBfcOS_Static.cpp : 
	
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

#include <BFC/BFCOS.h>
#ifdef UNIX
#	include <stdlib.h>
#	include <sys/stat.h>
// #include <sys/types.h>
// #include <unistd.h>
#endif

namespace CBfcOS
{

void OS_Static::GetCreditsString(CBfc::STRING &sCredits)
{
	sCredits = STATICBYTES  (" This software uses BFC Toolkit by W.P.Foster with thanks to Elie Ahad.\n");
//	sCredits += STATICBYTES  ("  .\n");
#ifdef USING_FOX
	sCredits += STATICBYTES ("  This software uses the FOX Toolkit (http://www.fox-toolkit.org).\n");
#endif
}

bool OS_Static::GetCurrentPath(CBfc::Filename &getcwd)
{
#ifdef UNIX
	char *p_saz = get_current_dir_name();
	getcwd = p_saz;
	free (p_saz);
	return true;
#else
	_wgetcwd (getcwd.GetBuffer(512),256);
	getcwd.ReleaseBuffer();
	return true;
#endif
}

bool OS_Static::SetCurrentPath(const CBfc::Filename &cwd)
{
#ifdef UNIX
	STRING	cwdRW(cwd);
	return chdir (cwdRW.BorrowAsciiBuffer()) == 0;
#else
	return (_wchdir(cwd.GetPtr()) != 0);
//	throw 100;
#endif
}	

// example   cwd == /home/bill/Sources/C++/Engines
//   and foldername == '.'
//
void OS_Static::MakePathAbsolute(CBfc::Filename &foldername)
{
	while (foldername[0] == '.')
	{
		UINT	len=1;
		if (foldername[1] == '.')
			break;
		if (foldername[1] == FOLDER_CHAR)
			len=2;
		foldername.TrimLeft(len);
	}
	CBfc::Filename	cwd;
	if (GetCurrentPath(cwd))
		foldername.PrependPath(cwd);
}


// returns 0 if file or folder does not exist
bool OS_Static::GetFileAttributes(const Filename &fName)
{
#ifdef UNIX
	Filename fn(fName);
	struct stat	ss;
	
	return  stat(fn.BorrowAsciiBuffer(), &ss) == 0;
#else
	return false;
#endif
}


bool OS_Static::CreateDirectory (const Filename &dir)
{
#ifdef UNIX
	if (GetFileAttributes(dir))
		return true;
	Filename dn(dir);
	return mkdir(dn.BorrowAsciiBuffer(),0x1ed) == 0;
#else
	return false;
#endif
}

bool OS_Static::ForceDirectory (const Filename &force)
{
	Filename	fnCreate (force);
	Filename	fnNext, fnAccumulate;
	
	while (fnCreate.GetNextSubdir(fnNext))
	{
		fnNext.PrependPath(fnAccumulate);
		fnAccumulate = fnNext;
		if (!CreateDirectory (fnNext))
			return false;
	}
	return true;
#if 0 //def WINDOWS
    /**************************************
	* Check the path to see if it is valid
	*/
	dptr = dir+1;
	if (*dptr == ':') {					/* see if a drive is specified */
		drive[0] = *dir;
		dir += 2;
	} else {
		error ("Error - no drive letter specified");
		return false;
	}
	/* move to the root directory of the selected drive*/
	if (_chdrive (drive[0]&0xf) || _chdir (drive)) {
		error ("Error - Drive %c: does not exist.", drive[0]);
		return false;
	}
    /***********************************************
	* Check to make sure subdirectory name is valid
	*/
	while (*dir != 0) {
		if (*dir == '\\')  *dir++;

//		l = strcspm (
		dptr = subdir;
		for (i = 0; (c = *dir) != 0 && *dir != '\\'; i++) {
			dir++;
			if ((c < '0' || c > 'z') && c != ' ' && c != '.') {
				error ("Error - Invalid directory name");
				return false;
			}
			*dptr++ = c;
		}
		*dptr = 0;
		/* move to the selected directory */
		if (_chdir (subdir)) {			  /* if the dir does not exist, */
			/* attempt to create it	*/
			if (_mkdir (subdir) != 0) {	/* if create failed,	*/
				error ("Error - cannot create subdirectory %s.",(int)subdir);
				return false;
			}
			/* attempt to change dir again */
			if (_chdir (subdir)) {			  /* if it still fails, */
				error ("Error - cannot select subdirectory %s.",(int)subdir);
				return false;
			}			/* end of if (inregs.x.cflag)	*/
		}			/* end of if (inregs.x.cflag)	*/
	}				/* end of while (*dir)		*/
	return true;
#endif
}

#ifndef UNIX
#	include <Windows.h>
#endif

bool OS_Static::SysCommand (const CBfc::STRING &sCommand)
{
#ifdef UNIX
	STRING	sMod(sCommand);
	return (system (sMod.BorrowAsciiBuffer()) != -1);
#else
    STARTUPINFOW si;
    PROCESS_INFORMATION pi;

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

	CreateProcessW(NULL, sCommand.GetPtr(), NULL, NULL, 0, 0, NULL,NULL,&si,&pi);
	CloseHandle (pi.hProcess);
	CloseHandle (pi.hThread);
	return true;
#endif
}
}

