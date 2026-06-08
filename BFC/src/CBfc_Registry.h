//*/
/*
					CBfc_Registry.h : 
	
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



namespace CBfc {

BFC_CLASS Registry // : public CBfc_ReferencedObject // Old naming until this baby is ready to roll - my invention.
{
public:
	Registry(const STRING &csRegname);

	bool PutValue(const STRING &csKey, const Value &value);
	bool PutDouble(const STRING &csKey, const double dVal);
	bool PutString(const STRING &csKey, const STRING &csVal);
	bool PutUINT(const STRING &csKey, const UINT uVal);

	bool GetValue(const STRING &csKey, Value &value) const;
	bool GetDouble(const STRING &csKey, double &dVal) const;
	bool GetString(const STRING &csKey, STRING &csVal) const;
	bool GetUINT(const STRING &csKey, UINT &uVal) const;
private:
	STRING	m_csRegname;
	Filename	m_RegistryFile;
};

BFC_CLASS ApplicationBase // : public Registry
{
	public:
		void Initialize	(const int argc, const char* argv[], const STRING &csResourcePath);
		void			GetResourceFolder(Filename &resfolder) const { resfolder = m_ResourceFolder; }
	protected:
		Filename		m_BaseFolder;
		Filename		m_ResourceFolder;
		int 			m_argc;
		const char**	m_argv;
};



} // namespace CBfc


