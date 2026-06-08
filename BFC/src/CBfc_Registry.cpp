//*/
/*
					CBfc_Registry.cpp : 
	
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

namespace CBfc {

Registry::Registry(const STRING &csRegname)
: m_csRegname(csRegname)
{
}

bool Registry::PutValue(const STRING &csKey, const Value &value)
{
	return true;
}

bool Registry::PutDouble(const STRING &csKey, const double dVal)
{
	return true;
}

bool Registry::PutString(const STRING &csKey, const STRING &csVal)
{
	return true;
}

bool Registry::PutUINT(const STRING &csKey, const UINT uVal)
{
	return true;
}

///////////////////////////////////////////////


bool Registry::GetValue(const STRING &csKey, Value &value) const
{
	return true;
}

bool Registry::GetDouble(const STRING &csKey, double &dVal) const
{
	return true;
}

bool Registry::GetString(const STRING &csKey, STRING &csVal) const
{
	return true;
}

bool Registry::GetUINT(const STRING &csKey, UINT &uVal) const
{
	return true;
}



void ApplicationBase::Initialize (const int argc, const char* argv[], const STRING &csResourcePath)
{
	Filename	runfile(argv[0]);
	m_BaseFolder = runfile.GetPath();
	if (csResourcePath.IsEmpty())
		m_ResourceFolder = m_BaseFolder;
	else
	{
		m_ResourceFolder = csResourcePath;
		if (csResourcePath.GetAt(0) != '/')
			m_ResourceFolder.SetPath (m_BaseFolder);
	}
	m_argc = argc;
	m_argv = argv;
}

} // namespace CBfc


