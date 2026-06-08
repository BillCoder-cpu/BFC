//*/
/*
					CBfcOS_Application_Fox.cpp : 
	
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

#include <BFC/BFCOS.h>

#ifdef USING_FOX

#include <fx.h>

namespace CBfcOS {

Application_Fox::Application_Fox()
: m_p_FoxApplication(NULL)
{
}

Application_Fox::~Application_Fox()
{
	ShutdownAppLayer();
}

bool Application_Fox::ShutdownAppLayer()
{
	if (m_p_FoxApplication)
	{
		FXApp	*p_fxApp= (FXApp*)m_p_FoxApplication;
		p_fxApp->destroy();
		BFC_RELEASE_PTR (p_fxApp);
		m_p_FoxApplication = NULL;
	}
	return true;
}


int Application_Fox::Run (const int argc, const char* argv[])
{
	if (!m_p_FoxApplication)
		return -1;

	InitializeAppLayer (argc, argv);
	FXApp	*p_fxApp= (FXApp*)m_p_FoxApplication;

	return p_fxApp->run ();
}

int Application_Fox::runModalFor(CBfcGUI::UILayerWindow *pWnd)
{
	FXApp	*p_fxApp= (FXApp*)m_p_FoxApplication;

	p_fxApp->refresh();
	return p_fxApp->runModalFor((FX::FXWindow*)pWnd);
}


// Make application
int Application_Fox::InitializeAppLayer (const int argc, const char* argv[])
{
	try
	{
		if (m_p_FoxApplication)
			return true;
//		p_fxApp = new FXApp(m_str_Title.GetPtr(),"BFCGui");
		FXApp *p_fxApp = new FX::FXApp("No Wide?","BFCGui");

		if (p_fxApp)
		{	// Start app
			int	ac=argc;
			p_fxApp->init(ac,(char**)argv);
			p_fxApp->create();
			m_p_FoxApplication = (CBfcGUI::AppLayerPtr)p_fxApp;
			return true;
		}
	} catch (...)
	{
		HANDLE_BFC_EXCEPTION();
	}
	return false;
}



}

#endif // ifdef USING_FOX


