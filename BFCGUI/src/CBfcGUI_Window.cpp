//*/
/*
					CBfcGUI_Window.cpp : 
	
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

#include <BFC/BFCGUI.h>

using namespace CBfc;

namespace CBfcGUI
{

/**
 * 
 * @param p_GUI 
 * @param csTitle 
 * @param eType 
 * @param p_Parent 
 * @param resourceID 
 * @param p_ResourceStore 
 * @return 
 */
Window::Window (GUI *p_GUI, const CBfc::STRING &csTitle,const EBFC_GUI_WINDOW_TYPE eType,Window *p_Parent,const Resource_ID resourceID,ResourceStore *p_ResourceStore)
  : UILayerWindow (p_GUI,csTitle,eType,p_Parent,resourceID)
  , TerminalWindow (p_Parent)
  , m_resourceID(resourceID)
  ,	m_p_ResourceStore(p_ResourceStore)
  , m_b_ResourceStore_Needs_Deregister(false)
{
//  Constructor ();
}

/**
 * 
 * @param p_GUI 
 * @param csTitle 
 * @param p_MemScript 
 * @param eType 
 * @param p_Parent 
 * @return 
 */
Window::Window (GUI *p_GUI, const CBfc::STRING &csTitle,character *p_MemScript,const EBFC_GUI_WINDOW_TYPE eType,Window *p_Parent)
  : UILayerWindow (p_GUI,csTitle,eType,p_Parent,(int)p_MemScript)
  , TerminalWindow (p_Parent)
  , m_resourceID(0)
  ,	m_p_ResourceStore(NULL)
  , m_b_ResourceStore_Needs_Deregister(false)
{
//  Constructor ();
	// We need to call these two functions and pass in pointer to temp GUI resource data, unlike BFCOS which hardcodes it resource stuff for now!!!!!!!!

	Stream		s;
	const unsigned long ul_memoryByteLength=SBFC_Character::StringByteLength(p_MemScript);
	
    if (s.AttachMemory (p_MemScript, ul_memoryByteLength))
	{
		ScriptResource *pScript = new CBfcGUI::ScriptResource(s);
		CBfcGUI::ResourceStore *pRS = pScript->LoadResources(); 
		delete pScript;
		GetGUI()->RegisterResourceStore(pRS);
		m_b_ResourceStore_Needs_Deregister = true;
		m_p_ResourceStore = pRS;  //GetGUI()->GetResourceStore("BFCOS")
		m_resourceID = pRS->LookupResourceID("Window");
	}
}

/**
 * 
 * @return 
 */
Window::~Window()
{
	if (m_b_ResourceStore_Needs_Deregister && m_p_ResourceStore)
		GetGUI()->UnregisterResourceStore(m_p_ResourceStore);		// frees the pointer
}


bool Window::Constructor ()
{
  bool bOk = OnCreate ();
  return bOk;
}

bool Window :: OnCreate ()
{
	return UILayerWindow::OnCreate();
}


int Window::OnDestroy()
{
   return BFCGUIDEFS_MESSAGE_NOT_PROCESSED;
}

int Window :: OnPaint(const Rect2dU &rect2d)
{
/*
	if (m_p_GLViewer)
	{
		FXDCWindow dc(m_p_GLViewer,ev);
		dc.setForeground(m_p_GLViewer->getBackColor());
		dc.fillRectangle(ev->rect.x,ev->rect.y,ev->rect.w,ev->rect.h);
	}
*/
	return BFCGUIDEFS_MESSAGE_NOT_PROCESSED;
}

int Window::OnResize(const CBfc::Size2dU &size)
{
	return BFCGUIDEFS_MESSAGE_NOT_PROCESSED;
}

void Window::SetCanvasSize (const CBfc::Size2dU &size)
{
	Size2dU	margins(8,20);
	SetWindowSize(size + margins);		// Leav enough extra for scroll bars and menus and borders
}

/////////////////////////////////////////////////////////////////////////
// Virtual overrides section

/**
 * 
 * @param p_shapeDraw 
 * @return 
 */
bool Window::OnRedraw (const CBfcVector::Shape2d *p_shapeDraw)
{
  CBfcVector::Shape2d	*p_drawShape=NULL;

	if (m_p_ShapeOutline)
		p_drawShape = (CBfcVector::Shape2d*)m_p_ShapeOutline->Dup();

	if (m_p_parentWindow) 
	{
		CBfcVector::Shape2d_PTR p_parentOutlineShape;

			//This window must fit in the parent window
		if (m_p_parentWindow->GetOutlineShape(p_parentOutlineShape))
		{
			if (p_drawShape)
				p_drawShape->LimitTo (*p_parentOutlineShape);
			else
				p_drawShape = (CBfcVector::Shape2d*)p_parentOutlineShape->Dup();
		}
	}
	if (IsDirty ())
		RenderInternal ();
	bool b_rVal = ReflectInternalImage (*p_drawShape);
	BFC_RELEASE ( p_drawShape );
	return b_rVal;
}

bool Window::ReflectInternalImage (const CBfcVector::Shape2d &shapeDraw)
{
	// Draw to the O.S.
	return false;
}

// Draws to the intenal CBfcImage
/**
 * 
 * @param  
 * @return 
 */
bool Window::RenderInternal (void)
{
	RenderOutline (*m_p_ShapeOutline);
	SetClean();
	return true;
}


/**
 * 
 * @param shapeDraw 
 */
void Window::RenderOutline (CBfcVector::Shape2d &shapeDraw)
{
	Brush_Solid	brush(m_OutlineColor);

//	, const CBfcVector_2dShape &shapeClip
	brush.DoBrush (m_InternalImage, shapeDraw, *m_p_ShapeClip);

//	drawShape. ();
//	DrawShape (brush, m_ShapeOutline, drawShape);
}

// Override!
int OVERRIDE Window::DoModal()
{
  if (IsVisible())
	  UILayerWindow::Show();
  return UILayerWindow::DoModal();
}

/**
 * 
 * @param msg 
 * @return 
 */
int OVERRIDE Window::OnMessage (const Message &msg)
{
	switch (msg.GetID())
	{
		case	BFCGUI_MSG_REDRAW:
			return OnPaint(*(Rect2dU*)msg.GetParameter());		// Need to supply the size!
		case	BFCGUI_MSG_RESIZE:
			return OnResize(*(Size2dU*)msg.GetParameter());
		case	BFCGUI_MSG_DESTROY:
			return OnDestroy();
	}
	return TerminalWindow::OnMessage (msg);
}

ResourceStore *Window::GetResourceStore()
{
	if (!m_p_ResourceStore)
		m_p_ResourceStore = GetGUI()->GetResourceStore();
	return m_p_ResourceStore;
}

void	Window::SetColor(const CBfcImage::Color &color) const
{
	UINT	r,g,b;
	color.SplitRGB (r,g,b);
	UINT	uc = r<<16 | g<<8 | b;
	UILayerWindow::SetColor(uc);
}

void Window::SetTitle(const CBfc::STRING &csTitle)
{
	LayerSetTitle(csTitle);
}

}


