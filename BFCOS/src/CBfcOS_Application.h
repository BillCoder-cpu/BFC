//*/
/*
					CBfcOS_Application.h : 
	
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

//
//  Application - using common resources.
//     This provides access to:
//
//

#ifdef USING_FOX
#	include	"CBfcOS_Application_Fox.h"
#	define	Application_DerivedFrom	 Application_Fox
#endif
#ifdef USING_WXWIDGETS
#	include	"CBfcOS_Application_WxWidgets.h"
#	define	Application_DerivedFrom	 Application_WxWidgets
#endif

namespace CBfcOS {

BFC_OS_CLASS Application  : public Application_DerivedFrom, public CBfc::ApplicationBase
	{
public:
	Application();
	virtual	~Application();

	bool SetResource (CBfcGUI::ScriptResource *res);
	virtual bool CreateMainWindow (const CBfc::Size2dU &size,const CBfc::STRING csTitle,const CBfc::STRING *p_csMenuName=NULL);

	virtual int 		InitializeAppLayer ();
	void				GetCopyrightString(CBfc_String &s);
//protected:
	CBfcGUI::GUI		*GetGUI() const { return m_p_GUI; }
protected:
	bool				LoadResources(const CBfc::Filename &ResourceFilename);
	CBfc::Stream		m_resource_stream;
private:
	void RegisterBFCOSResources ();

	CBfcGUI::ScriptResource	*m_p_Resource;
	CBfcGUI::GUI		*m_p_GUI;
	CBfc_String			m_str_Title;
};

}






