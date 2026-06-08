//*/
/*
					CBfcGUI.h : 
	
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
// CBfcGIU.h
//  Main GUI Class
//

namespace CBfcOS
{
	class Application;
}

namespace FX
{
#ifdef	WIN32
	class __declspec(dllimport) FXGLVisual;
#else
	class FXGLVisual;
#endif
}

namespace CBfcGUI
{

BFC_GUI_CLASS GUI
{
public:
	GUI (CBfcOS::Application *p_App=NULL, ScriptResource *res=NULL); // Some sort of resources file can be specified.

	Window		*NewWindow ();
	bool			CreateMainWindow (const CBfc::Size2dU &size, const CBfc::STRING &csTitle);
	MenuWindow		*GetMainWindow() const { return m_p_MainWindow; }
	bool			SetMainWindow(MenuWindow *p_MainWindow,const CBfc::STRING *p_csMenuName=NULL);
	DialogWindow	*LoadDialog(const CBfc::STRING &csIDName,Window *pParent=NULL);

	bool			RegisterCode (const STRING &name, FUNCTION_PTR CodeBlock);
	ResourceStore			*GetResourceStore(char *resname=NULL);
	bool					RegisterResourceStore	(ResourceStore* p_ResourceStore);
	bool					UnregisterResourceStore(ResourceStore* p_ResourceStore);

	AppLayerPtr				GetAppLayerPtr ();
	CBfcOS::Application		*GetAppPtr ();
	FX::FXGLVisual			*GetVisual();
protected:
private:
	MenuWindow				*m_p_MainWindow;
	CBfcOS::Application		*m_p_Application;
	Array<UILayerWindow*>	m_UIWindowArray;   // pointers to windows belonging to this GUI
	ResourceStore			*m_p_ResourceStore;
	Array<ResourceStore*>	m_ResourceStores;

	FX::FXGLVisual		*m_p_GLVisual;	// Optional visual for GLViewer type windows
};

}
