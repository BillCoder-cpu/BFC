//*/
/*
					CBfcGUI_FoxLayer.h : 
	
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
//  Integration of Fox into BFCGUI
//

namespace CBfcGUI
{
// Redefine this class to put in a different GUI layer than Fox
BFC_GUI_CLASS GUI;
BFC_GUI_CLASS Window;
BFC_GUI_CLASS CFoxBFCWindow;

typedef enum {
	WND_MAIN=0,
	WND_TOP,
	WND_CHILD,
	WND_CURSES,
	WND_3D,
	WND_DIALOG,
	WND_BUTTON,
	WND_TEXTBOX,
	WND_LABEL,
	WND_LIST,
	WND_LISTBOX,
	WND_COMBO,
	WND_GL,
} EBFC_GUI_WINDOW_TYPE;

typedef enum {
	CURSOR_ARROW=1,               /// Default left pointing arrow
	CURSOR_RARROW,                /// Right arrow
	CURSOR_IBEAM,                 /// Text I-Beam
	CURSOR_WATCH,                 /// Stopwatch or hourglass
	CURSOR_CROSS,                 /// Crosshair
	CURSOR_UPDOWN,                /// Move up, down
	CURSOR_LEFTRIGHT,             /// Move left, right
	CURSOR_MOVE                   /// Move up,down,left,right
} EBFC_GUI_CURSOR;

BFC_GUI_CLASS UILayerWindow
{
public:
	UILayerWindow (GUI *p_GUI, const CBfc::STRING &csTitle,const EBFC_GUI_WINDOW_TYPE eType,UILayerWindow *p_parent=NULL,const Resource_ID resourceID=0);
	virtual ~UILayerWindow();

	bool Create();
	bool Show();
	void DoCreate();

	void SetDefaultCursor (const EBFC_GUI_CURSOR eCur);
	void SetDefaultCursor (CBfcImage::Image &img);

	GUI *GetGUI() const {
		return m_p_GUI;	}

	EBFC_GUI_WINDOW_TYPE GetWindowType() const { return m_eWndType; }
	void SetWindowSize (const CBfc::Size2dU &size);
	void SetWindowPosition (const CBfc::Position2dU &pos);
	void SetWindowFocus (void);
	void SetWindowDefault();
	bool SizeTextbox(const CBfc::Size2dU &size);
	void	SetTextEditable (const bool bEditable);
	void	Dirty();

	bool	CreateDCw(const CBfc::Rect2dU &rect2d);
	void	ReleaseDC();
	void	SetColor(const UINT color) const;
	void	DrawRectangle(const CBfc::Rect2dU &rect2d) const;
	void	FillRectangle(const CBfc::Rect2dU &rect2d) const;
	void	DrawEllipse(const CBfc::Rect2dU &rect2d) const;
	void	FillEllipse(const CBfc::Rect2dU &rect2d) const;
	void	DrawPixel(const CBfc::Position2dU &pt) const;
	void	DrawLine(const CBfc::Position2dU &pt1,const CBfc::Position2dU &pt2) const;

	void	DrawBitmap (const CBfcImage::Bitmap *, const CBfc::Rect2dU &dest_rect, const CBfc::Position2dU &source_origin, const double zoom) const;

	bool GrabKeyboard();
	bool UnGrabKeyboard();
	CBfc::Position2dU	GetXYOfPos(const CBfc::Position2dU &pos) const;
	
			
	virtual int DoModal();
	virtual int OnMessage (const Message &msg)=0;
//	bool MakeTextbox(const bool b_Editable=false);	// Make this into a text window
	CFoxBFCWindow *GetFoxWindow() const {
		return m_p_FoxWnd;
	}
	UILayerWindow	*GetParent() const { return m_p_Parent; }
	
	static void *CreateVisual (AppLayerPtr app);

	void	LayerChangeFocus(UILayerWindow *pChild);    // Notification that focus moved to new child
	virtual bool OnCreate ();
protected:
	virtual void Stop(const int i_exitvalue);
	virtual void EndModal(const int i_exitvalue);
	virtual bool OnRedraw(const CBfcVector::Shape2d *p_shapeDraw=NULL)=0;

	void	LayerSetFocus();
	
	void	LayerReplaceText(const UINT pos,const UINT dlength,character *s,const UINT slength);
	void	LayerAppendText(const CBfc::STRING &cs);
	bool	LayerSetFont(CBfc::STRING &fontname,double d_pointSize);
	UINT	LayerGetText(CBfc::STRING &cs) const;
	void	LayerSetText(const CBfc::STRING &cs);
	void	LayerSetTitle(const CBfc::STRING &cs);
	UINT	LayerGetIndex() const;
	void	LayerSelectAll();

	CBfc::Size2dU  LayerGetSizeOnScreen(const CBfc::STRING &cs) const;

	EBFC_GUI_WINDOW_TYPE	m_eWndType;
private:
	GUI						*m_p_GUI;
	void					*m_p_Cursor;		// (is c-cast internally)
	CFoxBFCWindow			*m_p_FoxWnd;
	UILayerWindow			*m_p_Parent;
	bool					m_b_keygrab;		// is keyboard currently grabbed?
};

#define	MAX_MENU_DEPTH		10

class Menu
{
	public:
		Menu(Window *winp);
		virtual ~Menu();

		bool StartSubmenu(const STRING &csText);
		void EndSubmenu();
		bool AddEntry(const STRING &csText, const UINT id);

	private:
		UINT		m_u_menuDepth;
		BYTEPTR		m_topdock, m_menubar, m_menuTree[MAX_MENU_DEPTH];
		void		*m_p_container, *m_p_target;
// 		FXDockSite 	*m_topdock;
// 		FXMenuBar	*m_menubar;
// 		FXMenuPane 	*m_menuTree[MAX_MENU_DEPTH];
};

}



