//*/
/*
					CBfcGUI_CursesWindow.cpp : 
	
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

/*
	A thing of the past, with modern variable-sized fonts in which
	   different characters take up differing amounts of space.
*/
#include <BFC/BFCGUI.h>

namespace CBfcGUI
{

#if 0
echaracter GUI_KeyMap[
	FX::KEY_Right, 	FX::KEY_Left,		FX::KEY_Up, 		FX::KEY_Down,
	FX::KEY_Help,	FX::KEY_Page_Up,	FX::KEY_Page_Down, 	
	FX::KEY_BackSpace,
	FX::KEY_F1,		FX::KEY_F2,			FX::KEY_F3, 		FX::KEY_F4,
	FX::KEY_F5,		FX::KEY_F6,			FX::KEY_F7,			FX::KEY_F8,
	FX::KEY_F9,		FX::KEY_F10
];
#endif


CursesWindow::CursesWindow(GUI *p_GUI, Window *p_Parent, const EBFC_GUI_WINDOW_TYPE eWndType, Resource_ID resourceID)
	: Window(p_GUI, "Curses Window", eWndType, p_Parent, resourceID)
		, m_Position_X (0),  m_Position_Y (0)
		, m_p_getline_win(NULL)
{
}

bool CursesWindow :: OnCreate()
{
	Size2dU	size(64,24);
	STRING csFont(_TXT("fixed,100,normal,regular"));

	Window::OnCreate();
	SetTextDimensions(size);

	bool b = LayerSetFont(csFont,16.0);
	return true;
}

// Sets window position	- MUST BE SET!!!!
void CursesWindow :: window (int x, int y)
{
	m_i_windx = x;
	m_i_windy = y;
}


character * CursesWindow::GetCurrentTextPtr()
{
	UINT	u_DimW, u_DimH;

	m_TextDimensions.Get (u_DimW, u_DimH);
	UINT	offset = m_Position_X + (m_Position_Y * u_DimW);
//	return (m_TextArray + offset);
	ASSERT(0,"CursesWindow::GetCurrentTextPtr");
	return NULL;
}

CBfc::Position2dU CursesWindow::GetScreenPosition() const
{
	return GetXYOfPos(CBfc::Position2dU(m_Position_X,m_Position_Y));
//	UINT	x=m_i_windx + getXOfPos(m_Position_X);
//	UINT	y=m_i_windy + getYOfPos(m_Position_Y);
//	return CBfc::Position2dU(x,y);
}

CBfc::Position2dU CursesWindow::GetScreenPosition(const Position2dU &textpos) const
{
	return GetXYOfPos(textpos);
}

void CursesWindow :: SetText(const CBfc_String &cs)
{
	SetText(cs.GetPtr());
}

CBfc::Size2dU CursesWindow :: GetSizeOnScreen(const CBfc_String &cs) const
{
	return LayerGetSizeOnScreen (cs);
// 	return GetFoxWindow()->LayerGetSizeOnScreen (cs);
}

// 	void SetText(const CBfc_String &cs);
void CursesWindow :: Space(const UINT pels)
{
	static UINT spacewidth = 0;
	if (!spacewidth)
		spacewidth = GetSizeOnScreen(_TXT(" ")).GetX();
	if (spacewidth)
		m_Position_X += pels/spacewidth;
}

void CursesWindow :: SetText(character *text)
{
	character	*s, *p;
	character	pad[512];
	s = text;
	while (*s)
	{
		UINT u_Length = 0;
		p = pad;
		while (*s && *s != _TXT('\n'))
		{
			*p++ = *s++;
			u_Length++;
		}
		*p = 0;
		//  All /n translate to a different position
		m_Position_X += ReplaceText(pad, m_Position_X, m_Position_Y, u_Length);
		if (*s == _TXT('\n'))
		{
			m_Position_X = 0;
			m_Position_Y++;
			s++;
		}
	}
}

UINT CursesWindow::ReplaceText (character *s,UINT posX,UINT posY,UINT u_Length)
{
	UINT	width,height;

	m_TextDimensions.Get(width,height);
	if (posY >= height)
	{
		ASSERT(0,"CursesWindow::ReplaceText");
		posY = height-1;
	}
	if (posX + u_Length > width)
	{
		if (posX < u_Length)
			u_Length = width - posX;
		else
			u_Length = 0;
	}
	if (u_Length)
	{
		UINT pos = posX + (posY*(width+1));
		LayerReplaceText(pos, u_Length, s, u_Length);
	}
	return u_Length;
}

bool CursesWindow::SetTextDimensions(const Size2dU &dim)
{
//	BFC_RELEASE_PTR (m_TextArray);
	UINT	u_ArrayElementCount;
	if (dim.Product(u_ArrayElementCount))
	{
		m_TextDimensions = dim;		// Size of the Array of characters
		SizeTextbox(dim);
		clear();
//		m_TextArray = new character[u_ArrayElementCount];		// store my screen in memory
		return true;
	}
	return false;
}

void CursesWindow :: raw ()
{
//con_init ();
}

void CursesWindow :: unraw ()
{
//con_restore ();
}

bool CursesWindow :: home ()
{
	m_Position_X = m_Position_Y = 0;
	return true;
}

bool CursesWindow :: clear ()
{
	// Erase the entire window.
	CBfc_String sLine;
	UINT width,height;
	m_TextDimensions.Get(width,height);
	for (UINT u_col=0; u_col<width; u_col++)
		sLine += _TXT(" ");
	sLine += _TXT("\n");
	LayerSetText(sLine);
	for (UINT u_line=1; u_line<height; u_line++)
		LayerAppendText(sLine);
	home();
	return true;
}

bool CursesWindow :: moveto (int y,int x)
{
	m_Position_X = x;
	m_Position_Y = y;
	return true;
}

bool CursesWindow :: moveto (const Position2dU &pt)
{
	m_Position_X = pt.GetX();
	m_Position_Y = pt.GetY();
	return true;
}

Position2dU CursesWindow :: GetCursorPosition() const
{
	return Position2dU (m_Position_X,m_Position_Y);
}

bool CursesWindow :: clr_to_eol ()
{
	int	saveX = m_Position_X;
	SetText (_TXT("                                                                                "));
	m_Position_X = saveX;
	return true;
}
bool CursesWindow :: bell ()
{
	putchar (7);
#ifdef WIN32
//	System::Threading::Sleep(100);
#else
	usleep(100);
#endif
	putchar (7);
	return false;
}

/**
	 * 
	 * @param cs 
	 * @return 
 */
int CursesWindow::getline (CBfc::STRING &cs)
{
//	GetlineWindow win(GetGUI(), this);
	

/*
	GUI *pG = new GUI (GetGUI()->GetAppPtr());
	MenuWindow	*pWndPopup = new MenuWindow(pG,"test",CBfcGUI::WND_MAIN);
	const Size2dU size(400,20);
	pWndPopup->SetWindowSize (size);
 	pWndPopup->OnCreate();
	m_p_getline_win = new GetlineWindow(GetGUI(), pWndPopup);
*/
	m_p_getline_win = new GetlineWindow(GetGUI(), this);
	m_p_getline_win->SetWindowPosition(GetScreenPosition());
	
// 			pWndPopup->LayerChangeFocus(m_p_getline_win);
			m_p_getline_win->SetTextEditable(true);
//	pWndPopup->Show();
	
	const int rval = m_p_getline_win->Getline(cs);
	BFC_RELEASE (m_p_getline_win);
//	BFC_RELEASE (pWndPopup);
//	BFC_RELEASE (pG);
// 	
 	LayerSetFocus();
// 	SetWindowFocus();
	
	return rval;
// 	win.SetWindowPosition(GetScreenPosition());
// 	return win.Getline(cs);
}

character CursesWindow::GetC()
{
	GetcWindow win(GetGUI(), NULL); // this);
	
	return win.GetC();
}


int CursesWindow::OnKeyDown (character key)
{
	char keyval = (char)key;
//		EndModal(key&0xff);
	return true;
}

/*
int CursesWindow::OnFocusIn ()    //
{
	if (m_p_getline_win && m_p_getline_win->m_b_keygrab)
		m_p_getline_win->SetWindowFocus();
	return BFCGUIDEFS_MESSAGE_PROCESSED;		// bug in fox - must say we processed!!!
}
/*
int CursesWindow::OnFocusOut ()
{
#ifdef USING_FOX
	if (UnGrabKeyboard())
		m_b_keygrab = true;
#endif
	return BFCGUIDEFS_MESSAGE_PROCESSED;
}
*/

//////////////////////////////////////////////////////

GetlineWindow::GetlineWindow (GUI *p_GUI, Window *p_parent)
	: Window(p_GUI, "", WND_CURSES, p_parent)
		, m_b_keygrab(false), m_b_key_in_possession(false)
{
	OnCreate();
	SetWindowSize(Size2dU(320,16));
}

UINT GetlineWindow::Getline(CBfc::STRING &cs)
{
#ifdef USING_FOX
	m_b_keygrab = true;
	m_b_key_in_possession = true;
	GrabKeyboard();
#endif
	GetGUI()->GetMainWindow()->LayerChangeFocus(this);
//	SetWindowFocus();
	LayerSetFocus();
	Show();
	if (!cs.IsEmpty())
	{
		LayerSetText(cs);
		LayerSelectAll();
	}
// 	LayerSetFocus();
//	OnFocusIn();
	UINT r = DoModal();
#ifdef USING_FOX
	m_b_key_in_possession = false;
	UnGrabKeyboard();
	m_b_keygrab = false;
#endif
	if (r==0x1b) return false;		// ESC was pressed.
	return LayerGetText(cs);
}

int GetlineWindow::OnFocusIn ()    //
{
	const int rval = Window::OnFocusIn();	
#ifdef USING_FOX
 	if ((m_b_keygrab))
	{
		if (!m_b_key_in_possession)
		{
			m_b_key_in_possession = true;
			GrabKeyboard();
		}
	}
#endif
	return rval;
}

int GetlineWindow::OnFocusOut ()
{
#ifdef USING_FOX
 	if (m_b_keygrab)
	{
		if (m_b_key_in_possession)
		{
			m_b_key_in_possession = false;
			UnGrabKeyboard();
		}
	}
#endif
	const int rval = Window::OnFocusOut();
	return rval;
}


int GetlineWindow::OnKeyDown (character key)
{
	short keyval = (short)key;
	switch(keyval & 0xff)
	{
		case '\r':
			EndModal(key);
			return true;
		case 0x1b:
			EndModal(key);
			return true;
	}
// 	OnFocusIn();
//	LayerSetFocus();
// 	SetWindowFocus();
	return false;
}

bool GetlineWindow::OnCreate ()
{
	DoCreate();
	Size2dU	size(80,1);
	SizeTextbox(size);
//		b = LayerSetFont(CBfc_String(_TXT("Courier New,100,normal,regular")),12.0);
	return true;
}

//////////////////////////////////////////////////////

GetcWindow::GetcWindow (GUI *p_GUI, Window *p_parent)
	: Window(p_GUI, "", WND_CURSES, p_parent)
{
	OnCreate();
//	SetVisible (false);
	SetWindowSize(Size2dU(1,1));
	Show();
}

character GetcWindow::GetC()
{
	SetWindowFocus();
#ifdef USING_FOX
	GrabKeyboard();
#endif
	character c = DoModal();
#ifdef USING_FOX
	UnGrabKeyboard();
#endif
	return c;
}

int GetcWindow::OnKeyDown (character key)
{
	char keyval = (char)key;
	if (keyval > 0)
		EndModal(keyval);
//	else
//		EndModal(key&0xff);
	return true;
}



};


