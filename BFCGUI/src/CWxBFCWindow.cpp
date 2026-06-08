//*/
/*
					CWxBFCWindow.cpp : 
	
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
/********************************************************************************
*                                                                               *
*                        Integration of WxWidgets into BFCGui                   *
*                                                                               *
********************************************************************************/

#include <BFC/BFCGUI.h>

#ifdef USING_WXWIDGETS

namespace CBfcGUI
{

unsigned int CWxBFCWindow::m_su_NextWindowID = 0;

CWxBFCWindow::~CWxBFCWindow()
{
	BFC_RELEASE_PTR (m_p_Text);
	BFC_RELEASE_PTR (m_p_GLVisual);
	BFC_RELEASE_PTR (m_p_GLViewer);
}

// Construct a CFoxBFCWindow
CWxBFCWindow::CWxBFCWindow(wxWindow *p_Parent)
	: CWxBFCWindow_derivedFrom(p_Parent,m_su_NextWindowID)
	, m_p_GLViewer(NULL), m_p_GLVisual(NULL), m_p_Text(NULL)
{
	m_windowID =  m_su_NextWindowID++;
}

// Construct a CFoxBFCWindow
CBfcGUI_MainWindow::CBfcGUI_MainWindow(CBfcGUI_App *a)
	: wxFrame(NULL,-1,wxString(_TXT("BFCGui Application")))
{
}

/*
BEGIN_EVENT_TABLE(CWxBFCWindow, CWxBFCWindow_derivedFrom)
    EVT_PAINT  (CWxBFCWindow::OnPaint)
    EVT_MOTION (CWxBFCWindow::OnMouseMove)
END_EVENT_TABLE()
*/

/*
// Create and initialize
void CWxBFCWindow::create()
{
  CWxBFCWindow_derivedFrom::create();	// Create the window
}
*/

void CWxBFCWindow::OnPaint(wxPaintEvent &WXUNUSED(event))
{
	/*
    wxPaintDC dc(this);
    PrepareDC(dc);

    m_owner->PrepareDC(dc);

    dc.SetBackgroundMode( m_owner->m_backgroundMode );
    if ( m_owner->m_backgroundBrush.Ok() )
        dc.SetBackground( m_owner->m_backgroundBrush );
    if ( m_owner->m_colourForeground.Ok() )
        dc.SetTextForeground( m_owner->m_colourForeground );
    if ( m_owner->m_colourBackground.Ok() )
        dc.SetTextBackground( m_owner->m_colourBackground );

    if ( m_owner->m_textureBackground) {
        if ( ! m_owner->m_backgroundBrush.Ok() ) {
            wxBrush b(wxColour(0,128,0), wxSOLID);
            dc.SetBackground(b);
        }
    }

    if ( m_clip )
        dc.SetClippingRegion(100, 100, 100, 100);

    dc.Clear();

    if ( m_owner->m_textureBackground )
    {
        dc.SetPen(*wxMEDIUM_GREY_PEN);
        for ( int i = 0; i < 200; i++ )
            dc.DrawLine(0, i*10, i*10, 0);
    }

    switch ( m_show )
    {
        case Show_Default:
            DrawDefault(dc);
            break;
        case Show_Circles:
            DrawCircles(dc);
            break;
        case Show_Regions:
            DrawRegions(dc);
            break;
        case Show_Text:
            DrawText(dc);
            break;
        case Show_Lines:
            DrawTestLines( 0, 100, 0, dc );
            DrawTestLines( 0, 320, 1, dc );
            DrawTestLines( 0, 540, 2, dc );
            DrawTestLines( 0, 760, 6, dc );
            break;
        case Show_Brushes:
            DrawTestBrushes(dc);
            break;
        case Show_Polygons:
            DrawTestPoly(dc);
            break;
        case Show_Mask:
            DrawImages(dc);
            break;
        case Show_Ops:
            DrawWithLogicalOps(dc);
            break;
    }
	*/
}

void CWxBFCWindow::OnMouseMove(wxMouseEvent &event)
{
/*
    wxClientDC dc(this);
    PrepareDC(dc);
    m_owner->PrepareDC(dc);

    wxPoint pos = event.GetPosition();
    long x = dc.DeviceToLogicalX( pos.x );
    long y = dc.DeviceToLogicalY( pos.y );
    wxString str;
    str.Printf( wxT("Current mouse position: %d,%d"), (int)x, (int)y );
    m_owner->SetStatusText( str );
*/
}


int CWxBFCWindow::OnMessage (const CBfcGUI_Message &msg)
{
	ASSERT(0,"CWxBFCWindow::OnMessage");
	return 0;
}


bool CWxBFCWindow::MakeTextbox(const bool b_Editable)
{
	if (m_p_Text)
		return true;
	return m_p_Text!= NULL;
}

bool CWxBFCWindow::MakeGLViewer()
{
	if (m_p_GLViewer)
		return true;

	return m_p_GLViewer != NULL;
}

bool CWxBFCWindow::ProcessEvent(wxEvent& event)		// Handle all events.
{
	// Translate things into OnMessage() calls
	CBfcGUI_Message msg;

	const int			Id = event.GetId();
	const wxEventType	EventType = event.GetEventType();
	const wxObject		*p_EventObject = event.GetEventObject();

	if (EventType == wxEVT_KEY_DOWN)
	{
		wxKeyEvent *p_KeyEvent = (wxKeyEvent*)&event;
		msg.Set (BFCGUI_MSG_KEYPRESS, (void*)p_KeyEvent->GetKeyCode());
	} else if (EventType == wxEVT_KEY_UP)
	{
		wxKeyEvent *p_KeyEvent = (wxKeyEvent*)&event;
		msg.Set (BFCGUI_MSG_KEYRELEASE, (void*)p_KeyEvent->GetKeyCode());
	}
	if (msg.GetID() == BFCGUI_MSG_NO_OP)
		return (OnMessage (msg) != 0);
	return false;
}


}

#endif // ifdef USING_WXWIDGETS







