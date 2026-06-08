//*/
/*
					CBfcUITerminal_Terminal.h : 
	
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

// My version of CWnd
// #define	CWnd	CTerminal


typedef CBfc_Array<CBfcUI_Button>		CBfc_DialogObjects;

// We want docking windows

class CBfcUI_Wnd : public CBfcUITerminal_Terminal
{
public:
protected:
	virtual	void	OnPaint ();	// Override this to draw on me
private:
	 bool	b_docked;
};


class CBfcUI_Dialog : public window
{
public:
protected:
	CBfc_DialogObjects	children;				// Menus and Buttons (shapes)
private:
};

//
//
//
class CTestApp : public CBfcUI_Dialog
{
public:
	CTestApp ();
	virtual bool Login ( long l_loginID, const CBfc_Size &initialFrameSize );
protected:
	virtual	bool OnExit ();				// Must provide exit support
private:
};

bool CTestApp :: Login ( long l_loginID, const CBfc_Size &initialFrameSize );
{
	CBfcUI_Dialog :: Login ( l_loginID, initialFrameSize );
	DrawTextString ("Hello Buddy, I am here");
}

bool CTestApp :: OnExit ()
{
	return true;
}


typedef	CBfc_Array<CBfc_Point>	CBfcUI_Shape;


class CBfcUI_MessageQue_Message
{
	enum {
		MouseEvent,
		KeyBoardEvent,
		VoiceEvent,
		FrameEvent,			// Logout, Exit, Resize window, etc.
	} EventClass;

	E_EventClass	MessageClass;
	long 					m_messageCode;
	char					*m_parameter1;
	char					*m_parameter2;

	virtual    OnMouseEvent (const CBfcUI_MouseEvent &me);	// Override this to receive Mouse Events
	virtual    OnKeyboardEvent (const CBfcUI_KeyboardEvent &ke);
	virtual	OnVoiceEvent (const CBfcUI_VoiceEvent &ve);	// happens when user speaks
	virtual    OnResizeFrame (void);									// Must call GetWindowOutline() for parameters
};

class CBfcUI_MouseEvent : public CBfcUI_MessageQue_Message
{
	CBfc_Coordinate   x,y;
	short			button;
	{
		MouseDown,
		MouseUp,
		MouseClick,
		MouseMove,
		MouseEnter,
		MouseLeave
	};
};


class CBfcUI_MessageQue
{
	GetNextMessage (CBfcUI_MessageQue_Message &message);

};

CBfcUI_MessageQue :: GetNextMessage ()
{
}


/*
CBfcUITerminal_Terminal :: ()
{
}
*/

class CBfcUITerminal_Terminal
{
public:
	CBfcUITerminal_Terminal ();

	virtual bool Login (long l_loginID, const CBfc_Size &initialFrameSize );


protected:
	DrawTextString ();
	CBfcUI_MessageQue		messageQue;

	virtual	bool OnExit () = 0;				// Must provide exit support
	virtual	Terminate ();	  // End the Session :
};

CBfcUITerminal_Terminal::CBfcUITerminal_Terminal ()
{
}

CBfcUITerminal_Terminal ::  ()
{
}



