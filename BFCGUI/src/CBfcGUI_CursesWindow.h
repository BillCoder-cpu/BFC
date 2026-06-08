//*/
/*
					CBfcGUI_CursesWindow.h : 
	
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
#ifndef CWIN_NUB
#define CWIN_NUB

namespace CBfcGUI
{
#undef	ReplaceText

	//////////////////////////////////////

	BFC_GUI_CLASS GetcWindow : public Window
	{
		public:
			GetcWindow (GUI *p_GUI, Window *p_parent);
			character GetC();
		protected:
			virtual int OnKeyDown (character key);
	};


	BFC_GUI_CLASS GetlineWindow : public Window
	{
		public:
			GetlineWindow (GUI *p_GUI, Window *p_parent);
			UINT	Getline(CBfc::STRING &cs);
			virtual int OnFocusIn ();    // 
			virtual int OnFocusOut ();   // etc.
			bool	m_b_keygrab;	// save keygrab state when switching windows.
			bool	m_b_key_in_possession;	// save keygrab state when switching windows.

		protected:
			virtual bool OnCreate();
			virtual int OnKeyDown (character key);
		private:
	};

BFC_GUI_CLASS CursesWindow : public Window
{
public:
	CursesWindow(GUI *p_GUI, Window *p_Parent=NULL,const EBFC_GUI_WINDOW_TYPE eWndType=WND_CURSES,Resource_ID resourceID=0);
	
	void	window (int x, int y);			/* Sets window position	- MUST BE SET!!!! *****/
	void	raw ();
	void	unraw ();

// 	virtual int OnFocusIn ();    // 

	virtual bool	home ();
	virtual bool	clear ();
	virtual bool	moveto (int y,int x);
	virtual bool	moveto (const Position2dU &pt);
	virtual bool	clr_to_eol ();
	virtual bool	bell ();

	bool	SetTextDimensions(const CBfc::Size2dU &dim);
	void	SetText(const CBfc_String &cs);
	void	Space(const UINT pels);
	virtual void SetText(character *s);

	CBfc::Position2dU	GetScreenPosition () const;
	CBfc::Position2dU	GetScreenPosition (const Position2dU &textpos) const;
	CBfc::Position2dU	GetCursorPosition () const;

	CBfc::Size2dU	GetSizeOnScreen (const CBfc_String &cs) const;

protected:
	virtual bool	OnCreate();
	int				getline (STRING &cs);
	character		GetC();
	
	virtual int		OnKeyDown (character key);

private:
	GetlineWindow	*m_p_getline_win;

	UINT		ReplaceText (character *s,UINT posX,UINT posY,UINT u_Length);

				// coordinates of the upper left corner of the window being used	
	int			m_i_windx,		m_i_windy;		//  (x,y) ?dummy?
	int			m_Position_X,	m_Position_Y;	// Current cursor position

	character * 	GetCurrentTextPtr();
	CBfc::Size2dU	m_TextDimensions;		// Size of the Array of characters
};

#if 1
enum {
	rarrow = 0XFF53, larrow = 0XFF51,	uarrow = 0XFF52, darrow=0XFF54,
	helpkey = 0XFF6A,	pageup = 0XFF55,	pagedown = 0XFF56, 	
	CRUBOUT = 0XFF08,	// BACKSPACE
	F1=0xFFBE,		F2=0xFFBF,			F3=0xFFC0, 		F4=0xFFC1,
	F5=0xFFC2,		F6=0xFFC3,			F7=0xFFC4,		F8=0xFFC5,
	F9=0xFFC6,		F10=0xFFC7
	};
#else
extern character GUI_KeyMap[];

#define	rarrow		CBfcGUI::GUI_KeyMap[0]
#define	larrow		CBfcGUI::GUI_KeyMap[1]
#define	uarrow		CBfcGUI::GUI_KeyMap[2]
#define	darrow		CBfcGUI::GUI_KeyMap[3]
#define	helpkey		CBfcGUI::GUI_KeyMap[4]
#define	pageup		CBfcGUI::GUI_KeyMap[5]
#define	pagedown	CBfcGUI::GUI_KeyMap[6]

#define CUP_ARROW		CBfcGUI::GUI_KeyMap[2]
#define CDOWN_ARROW		CBfcGUI::GUI_KeyMap[3]
#define CLEFT_ARROW		CBfcGUI::GUI_KeyMap[1]
#define CRIGHT_ARROW	CBfcGUI::GUI_KeyMap[0]
#define CRUBOUT			CBfcGUI::GUI_KeyMap[7]

#define	F1	CBfcGUI::GUI_KeyMap[8]
#define	F2	CBfcGUI::GUI_KeyMap[9]
#define	F3	CBfcGUI::GUI_KeyMap[10]
#define	F4	CBfcGUI::GUI_KeyMap[11]
#define	F5	CBfcGUI::GUI_KeyMap[12]
#define	F6	CBfcGUI::GUI_KeyMap[13]
#define	F7	CBfcGUI::GUI_KeyMap[14]
#define	F8	CBfcGUI::GUI_KeyMap[15]
#define	F9	CBfcGUI::GUI_KeyMap[16]
#define	F10	CBfcGUI::GUI_KeyMap[17]
#endif

}

#endif		// CWIN_NUB


