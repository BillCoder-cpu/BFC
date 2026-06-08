//*/
/*
					CBfcOS_Application_Fox.h : 
	
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

#ifdef USING_FOX

namespace CBfcOS {

BFC_OS_CLASS Application_Fox
{
public:
	Application_Fox();
	virtual	~Application_Fox();

	virtual int Run (const int argc, const char* argv[]);
	int runModalFor(CBfcGUI::UILayerWindow *);

	CBfcGUI::AppLayerPtr GetLayerAppPointer()
	{
		return m_p_FoxApplication;
	}

protected:
	virtual bool ShutdownAppLayer();
	
	int InitializeAppLayer (const int argc, const char* argv[]);
//	FXApp					*GetFoxApp() const { return m_p_FoxApp; }
//	virtual CBfcGUI_Window * NewMainWindow ();
private:
	CBfcGUI::AppLayerPtr		m_p_FoxApplication;
};

}

#endif	// ifdef USING_FOX


