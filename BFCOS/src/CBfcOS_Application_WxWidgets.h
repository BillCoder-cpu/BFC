//*/
/*
					CBfcOS_Application_WxWidgets.h : 
	
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

#ifdef USING_WXWIDGETS

BFC_OS_CLASS CBfcOS_Application_WxWidgets
{
public:
	CBfcOS_Application_WxWidgets();
	virtual	~CBfcOS_Application_WxWidgets();

	bool SetResource (CBfcGUI_ScriptResource *res);

	virtual int Run ();
	CBfcGUI_App *GetLayerAppPointer()	{
		return NULL;
	}
protected:
	int InitializeAppLayer (const int argc, const char* argv[]);
//	virtual CBfcGUI_MainWindow * NewMainWindow ();
	virtual bool ShutdownAppLayer();

private:
};

#endif	// ifdef USING_WXWIDGETS


