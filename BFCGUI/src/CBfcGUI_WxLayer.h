//*/
/*
					CBfcGUI_WxLayer.h : 
	
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

// CfcGUI_FoxLayer.h
//  Integration of Fox into BFCGUI
//

#include "CWxBFCWindow.h"

namespace CBfcGUI
{
	// Redefine this class to put in a different GUI layer than Fox

BFC_GUI_CLASS GUI;

BFC_GUI_CLASS UILayerWindow : protected CWxBFCWindow
{
public:
   CBfcGUI_UILayerWindow (CBfcGUI *p_GUI, CBfcGUI_UILayerWindow *p_parent=NULL);
   inline bool Create ();
	bool Show();

	GUI *GUI() const {
		return m_p_GUI;	}

	void SetText(const CBfc_String &cs);
	void SetText(character *s);
	void SetSize (CBfc_2dSize &size);

	virtual int DoModal();

protected:
	virtual void EndModal(const int i_exitvalue);

	virtual int OnMessage (CBfcGUI_Message &msg)=0;

	virtual bool OnRedraw(const CBfcVector::Shape2d_PTR p_shapeDraw=NULL)=0;

private:
	GUI					*m_p_GUI;
	UILayerWindow	*m_p_Parent;
};

}


