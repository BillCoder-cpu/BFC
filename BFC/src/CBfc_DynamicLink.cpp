//*/
/*
					CBfc_DynamicLink.cpp : 
	
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
 * DynamicLink.h - A WIN32/Linux runtime library loader.
 * Created April 17, 2006, by Michael 'Bigcheese' Spencer.
 */

#include <BFC/BFC.h>


#ifdef WIN32
#	include <windows.h>
#else
#	include <dlfcn.h>
#endif


namespace CBfc
{
	
  DynamicLink::DynamicLink()
  {
     m_libhandle = 0;
  }

  bool DynamicLink::OpenLibrary(char* libname)
  {
#ifdef WIN32
     m_libhandle = LoadLibrary(libname);
#else
     // First we need to add ./ and end with .so.
  /*	int len = strlen(libname);
     len += 6; // Add room for ./, .so, and null.
     char* name = new char[len];
     name[0] = 0;
     strcat(name, "./");
     strcat(name, libname);
     strcat(name, ".so");
     m_libhandle = dlopen(name, RTLD_LAZY);
     delete[] name;
  */
     m_libhandle = dlopen(libname, RTLD_LAZY);
#endif
     return (m_libhandle!=NULL);
  }

  DynamicLink::~DynamicLink()
  {
	 if(m_libhandle)
	 {
#ifdef WIN32
		FreeLibrary((HINSTANCE)m_libhandle);
#else
		dlclose(m_libhandle);
#endif
	 }	
  }

	void * DynamicLink::getFunc(char* funcName)
	{
		void* func = 0;
		if(m_libhandle)
		{
#ifdef WIN32
			func = (void*)GetProcAddress((HINSTANCE)m_libhandle, funcName);
#else
			func = dlsym(m_libhandle, funcName);
#endif
		}
		return func;
	}

}


