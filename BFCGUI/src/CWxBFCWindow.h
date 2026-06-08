//*/
/*
					CWxBFCWindow.h : 
	
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

// CWxBFCWindow.h

#define	WXUSINGDLL
//#define WXMAKINGDLL

//#pragma warning 
#include <wx/wx.h>

#define CWxBFCWindow_derivedFrom wxScrolledWindow


BFC_GUI_CLASS CWxBFCWindow : public CWxBFCWindow_derivedFrom
{                  // Macro for class hierarchy declarations
public:
  // CWxBFCWindow's constructor
	CWxBFCWindow(wxWindow	*p_Parent);
	virtual ~CWxBFCWindow();
 //   virtual void create();

	bool MakeGLViewer();							// 
	bool MakeTextbox(const bool b_Editable=false);	// Make this into a text window

    virtual bool ProcessEvent(wxEvent& event);		// Handle all events.

    void OnPaint(wxPaintEvent &event);
    void OnMouseMove(wxMouseEvent &event);
protected:
	CWxBFCWindow(){}

public:					  // Messages for our class
  enum{
//    ID_CANVAS=FXMainWindow::ID_LAST,
    ID_CLEAR,
    ID_LAST
    };

  enum{					  // ID's in possible use.
	  ID_TEXT,
  };
protected:
	virtual int OnMessage (CBfcGUI_Message &msg);

public:
protected:
	unsigned int			m_windowID;
	static unsigned int		m_su_NextWindowID;

	void	*m_p_GLViewer;
	void	*m_p_GLVisual;
	void	*m_p_Text;
private:
};


BFC_GUI_CLASS CBfcGUI_MainWindow : public wxFrame
{
public:
	CBfcGUI_MainWindow(CBfcGUI_App* a);
protected:
	CBfcGUI_MainWindow(){}
private:
	CBfc_Array<wxMenu*>  m_MenuArray;    // pointers to windows belonging to this GUI
	wxToolBar *			m_Toolbar;
};





