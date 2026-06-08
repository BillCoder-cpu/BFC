//*/
/*
					CBfcGUI_TerminalWindow.h : 
	
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

namespace CBfcGUI {

BFC_GUI_CLASS TerminalWindow;

BFC_GUI_CLASS TerminalWindow // : public EditInterface
{
public:
	TerminalWindow (TerminalWindow *p_Parent=NULL);
	// Creates a window within this one.
	TerminalWindow	*NewWindow(const CBfc::Rect2d &r_position);

	virtual int DoModal();

	virtual int OnMessage(const Message &msg);
	
	virtual int OnKeyUp (character key);
	virtual int OnKeyDown (character key);

	virtual int OnMouseMove (const CBfc::Point2dU &pt);  // This is an override so we get control of the main window.
	virtual int OnMouseDown (const CBfc::Point2dU &pt);  //
	virtual int OnMouseDoubleClick (const CBfc::Point2dU &pt);    //
	virtual int OnMouseUp ();    //

	virtual int OnMouseEnter ();    //
	virtual int OnMouseLeave ();  //

	virtual int OnFocusIn ();    // 
	virtual int OnFocusOut ();   // etc.

	bool GetWindowOutline (CBfcVector::Shape2d &shape_outline);		// For now we are square -but we can be an outline
	bool SetWindowOutline (CBfcVector::Shape2d &shape_outline);

	bool	IsVisible(void) const {
		return m_b_Visible;
	}
	void SetVisible (const bool bOn) {
		m_b_Visible = bOn;
	}
	bool	IsDirty(void) const {
		return m_b_Dirty;
	}
	void SetDirty (void) {
		m_b_Dirty = true;
	}
	void SetClean (void) {
		m_b_Dirty = false;
	}

	bool GetOutlineShape (CBfcVector::Shape2d_PTR &p_shape) const;
	void SetClip (const CBfcVector::Shape2d_PTR &shapeClip);
protected:
	bool					m_b_Docked;	// unimplimented
	bool					m_b_Dirty, m_b_Visible;
	TerminalWindow			*m_p_parentWindow;
	CBfcImage::Color			m_OutlineColor;
	CBfcVector::Shape2d		*m_p_ShapeOutline;		// Describes the edges of this window.
	CBfcVector::Shape2d		*m_p_ShapeClip;		// Resrict all drawing to this.
};

}
