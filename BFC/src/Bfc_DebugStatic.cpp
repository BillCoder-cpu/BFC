//*/
/*
					Bfc_DebugStatic.cpp : 
	
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
#include "BFCDefs.h"
#include <stdio.h>
#ifdef UNIX
#	include <wchar.h>
#else
#	include <tchar.h>
#endif

#ifdef UNIX
extern "C" 
{
	
void BfcDebugStatic_Trace (const CHARACTER_PTR lpszFormat,int v1, int v2, int v3, int v4, int v5, int v6, int v7, int v8, int v9, int v10)
{
#	ifdef _UNICODE_8
	fprintf (stderr, lpszFormat, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
#else
	fwprintf (stderr, lpszFormat, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
#endif
	fflush (stderr);
}

void BfcRelease_Trace (const CHARACTER_PTR lpszFormat, ...)
{
	return;
}

}
#else
extern "C" 
{

void __cdecl BfcDebugStatic_Trace (const CHARACTER_PTR lpszFormat, int v1, int v2, int v3, int v4, int v5, int v6, int v7, int v8, int v9, int v10)
{
	_ftprintf (stderr, lpszFormat, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
	fflush (stderr);
/*
	va_list list;
    va_start (list, string);
	vaEnumValue = va_arg (list, char *);
	while (vaEnumValue != -1)
		vaEnumValue = va_arg (list, char *);
    va_end(argList);
*/
}

void __cdecl BfcRelease_Trace (const CHARACTER_PTR lpszFormat, int v1, int v2, int v3, int v4, int v5, int v6, int v7, int v8, int v9, int v10)
{
	return;
}

/*
char		errfile[FILENAME_LENGTH] = "ERRFILE.err";
static FILE	*err_fp = NULL;
static char	were_errors = false;

init_errfile (char *filename)
{ 
	char	ie_pad[FILENAME_LENGTH], lpad[FILENAME_LENGTH];

	if (filename) strcpy (errfile, filename);
	if (errfile[1] != ':' && errfile[0] != '\\') {
		getcwd (ie_pad, 100);
		mk_fname (lpad, ie_pad, errfile);
		strcpy (errfile, lpad);
	}
	unlink (errfile);
	were_errors = false;
// 	err_fp = fopen (errfile, "a");
}

err_printf (s, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10)
char *s;
{
	FILE	*fp;
	char	epf_pad[256];

	fp = err_fp;
	if (!fp) fp = fopen (errfile, "a");
	if (!fp) {
		strcpy (errfile, "pixo.err");
		fp = fopen (errfile, "a");
	}
	strcpy (epf_pad, s);
	s = epf_pad;
	strcat (s, "\n");
	if (fp) {
		were_errors = true;
		fprintf (fp, s, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
		if (!err_fp) fclose (fp);
		else fflush (fp);
	}
}
*/
}
#endif
