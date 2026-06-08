//*/
/*
					CBfcGUI_Window.h : 
	
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

#define USING_FOX
//#define USING_WXWIDGETS
//#define USING_QUICKGUI

namespace CBfcGUI {
#ifdef USING_FOX
//#	define AppLayerPtr FXApp
typedef void* AppLayerPtr;
#endif
#ifdef USING_WXWIDGETS
	class AppLayerPtr;
#endif
}

#ifdef USING_FOX
#	include "CBfcGUI_FoxLayer.h"     // Fox
#endif
#ifdef USING_QUICKGUI
	class AppLayerPtr;
#	include "CBfcGUI_QuickGUILayer.h"     // QuickGUI
#endif
#ifdef USING_WXWIDGETS
#	include "CBfcGUI_WxLayer.h"     // WxWidgets
#endif

namespace CBfcGUI {

BFC_GUI_CLASS Window : public UILayerWindow, public TerminalWindow
{
public:
	Window (GUI *p_GUI, const CBfc::STRING &csTitle, const EBFC_GUI_WINDOW_TYPE eType=WND_TOP, Window *p_Parent=NULL,const Resource_ID resourceID=0,ResourceStore *p_ResourceStore=NULL);
	Window (GUI *p_GUI, const CBfc::STRING &csTitle, character *pMemScript, const EBFC_GUI_WINDOW_TYPE eType=WND_TOP, Window *p_Parent=NULL);
	virtual ~Window();

	virtual int 			DoModal();
	
	Resource_ID				GetResourceID() const { return m_resourceID; }
	virtual ResourceStore 	*GetResourceStore();

	void SetCanvasSize (const CBfc::Size2dU &size);
	void	SetColor(const CBfcImage::Color &color) const;
	void SetTitle(const CBfc::STRING &csTitle);

public:
	virtual int			OnMessage(const Message &msg);
	virtual bool 		OnRedraw (const CBfcVector::Shape2d *p_shapeDraw=NULL);
	virtual bool		OnCreate ();
protected:
	virtual int			OnDestroy();
	virtual int			OnPaint(const CBfc::Rect2dU &rect2d);
	virtual int			OnResize(const CBfc::Size2dU &size);
	
	bool RenderInternal (void);
	bool ReflectInternalImage (const CBfcVector::Shape2d &shapeDraw);
	void RenderOutline (CBfcVector::Shape2d &shapeDraw);

private:
	bool 	Constructor ();

	CBfcVector::Shape2d		*m_pBorder;
	CBfcImage::Bitmap		m_InternalImage;						// Things get draw here and then re-displayed
//	CBfcImage_bitmap			m_CurrentlyDisplayedBitmap;	// Here is what the screen looks like now.

	Resource_ID				m_resourceID;
	ResourceStore			*m_p_ResourceStore;
	bool					m_b_ResourceStore_Needs_Deregister;
};


}


