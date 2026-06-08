//*/
/*
					CBfcGUI_FoxLayer.cpp : 
	
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

#ifdef USING_FOX

#include "CFoxBFCWindow.h"
#undef CreateDC

using namespace CBfc;

namespace CBfcGUI
{

CBfcImage::ColorSpace	fox_colorspace(CBfcImage::ColorSpace::COLORSPACE_RGBA);

UILayerWindow :: UILayerWindow (GUI *p_GUI,const CBfc::STRING &csTitle,const EBFC_GUI_WINDOW_TYPE eType,UILayerWindow *p_Parent,const Resource_ID resourceID)
	:  m_p_GUI (p_GUI)
	, m_p_Cursor(NULL)
	, m_eWndType(eType)
	, m_b_keygrab(false)
{
	FXApp	*pApp = (FXApp*)m_p_GUI->GetAppLayerPtr();
	
	m_p_Parent = p_Parent?p_Parent:p_GUI->GetMainWindow();
	switch (eType)
	{
		case WND_MAIN:
			m_p_Parent=NULL;
			m_p_FoxWnd = new CFoxMainWindow(pApp,csTitle,this);
			break;
		case WND_TOP:
		case WND_3D:
			m_p_FoxWnd = new CFoxTopWindow(pApp, csTitle, this, m_p_Parent);
			break;
		case WND_DIALOG:
			m_p_FoxWnd = new CFoxDialogWindow(pApp, csTitle, this, m_p_Parent);
			break;
		case WND_CHILD:
			m_p_FoxWnd = new CFoxChildWindow(pApp, this, m_p_Parent);
			break;
		case WND_CURSES:
			m_p_FoxWnd = new CFoxTextWindow(pApp, resourceID, this, m_p_Parent);
			LayerSetText(csTitle);
			break;
		case WND_BUTTON:
			m_p_FoxWnd = new CFoxButtonWindow(pApp, csTitle, resourceID, this, m_p_Parent);
			break;
		case WND_TEXTBOX:
			m_p_FoxWnd = new CFoxTextboxWindow(pApp, csTitle, resourceID, this, m_p_Parent);
			break;
		case WND_LABEL:
			m_p_FoxWnd = new CFoxLabelWindow(pApp, csTitle, resourceID, this, m_p_Parent);
			break;
		case WND_LIST:
			m_p_FoxWnd = new CFoxListWindow(pApp, resourceID, this, m_p_Parent);
			break;
		case WND_LISTBOX:
			m_p_FoxWnd = new CFoxListboxWindow(pApp, resourceID, this, m_p_Parent);
			break;
		case WND_COMBO:
			m_p_FoxWnd = new CFoxComboWindow(pApp, 1, resourceID, this, m_p_Parent);
			break;
		case WND_GL:
			m_p_FoxWnd = new CFoxGLWindow(p_GUI,pApp, resourceID, this, m_p_Parent);
			break;
	}
}

UILayerWindow :: ~UILayerWindow()
{
	BFC_RELEASE(m_p_FoxWnd);
	delete (FXCursor*)m_p_Cursor;
}

bool UILayerWindow :: OnCreate ()
{
	DoCreate();
//  if (m_p_Parent)
//	  GetFoxWindow()->GetAsFox()->reparent(m_p_Parent->GetFoxWindow()->GetAsFox());
	LayerSetFocus();
  return true;
}

void UILayerWindow :: DoCreate ()
{
	GetFoxWindow()->GetAsFox()->create();
}

bool  UILayerWindow :: Create()
{
 	return OnCreate();
}

bool UILayerWindow :: Show()
{
  GetFoxWindow()->GetAsFox()->show(); //PLACEMENT_SCREEN);
  return true;
}

	  /// Set the default cursor for this window
void UILayerWindow :: SetDefaultCursor (const EBFC_GUI_CURSOR eCur)
{
	FXApp	*pApp = (FXApp*)m_p_GUI->GetAppLayerPtr();
	FXCursor	*pCursor = new FXCursor(pApp, (FXStockCursor)eCur);
	if (m_p_Cursor)
		delete (FXCursor*)m_p_Cursor;
	m_p_Cursor = pCursor;

	  GetFoxWindow()->GetAsFox()->setDefaultCursor((FXCursor*)m_p_Cursor);
}

// doesn't do anything yet!
void UILayerWindow :: SetDefaultCursor (CBfcImage::Image &img)
{
	  /// Set the default cursor for this window
	FXApp	*pApp = (FXApp*)m_p_GUI->GetAppLayerPtr();
	FXCursor	*pCursor = new FXCursor(pApp);
	if (m_p_Cursor)
		delete (FXCursor*)m_p_Cursor;
	m_p_Cursor = pCursor;
	GetFoxWindow()->GetAsFox()->setDefaultCursor((FXCursor*)m_p_Cursor);
}

void UILayerWindow :: SetWindowSize (const Size2dU &size)
{
	GetFoxWindow()->GetAsFox()->resize(size.GetX(),size.GetY());
}

void UILayerWindow :: SetWindowPosition (const Position2dU &pos)
{
	GetFoxWindow()->GetAsFox()->move(pos.GetX(), pos.GetY());
}

void UILayerWindow :: SetTextEditable (const bool bEditable)
{
	GetFoxWindow()->FxSetEditable(bEditable);
}

int UILayerWindow :: DoModal()
{
  return GetFoxWindow()->DoModal();
}

void UILayerWindow :: Stop(const int i_exitvalue)
{
	GetFoxWindow()->GetAsFox()->getApp()->stop(i_exitvalue);
}

void UILayerWindow :: EndModal(const int i_exitvalue)
{
	GetFoxWindow()->GetAsFox()->getApp()->stopModal(GetFoxWindow()->GetAsFox(),i_exitvalue) ;
}

bool UILayerWindow :: SizeTextbox(const Size2dU &size)
{
	return GetFoxWindow()->SizeTextbox(size);
}

void UILayerWindow :: LayerReplaceText(const UINT pos,const UINT dlength,character *s,const UINT slength)
{
	GetFoxWindow()->FxReplaceText(pos,dlength,s,slength);
}

void UILayerWindow :: LayerAppendText(const CBfc::STRING &cs)
{
	GetFoxWindow()->FxAppendText(cs);
}

void UILayerWindow :: LayerSetText(const CBfc::STRING &cs)
{
	GetFoxWindow()->FxSetText(cs);
}

void UILayerWindow :: LayerSetTitle(const CBfc::STRING &csName)
{
	GetFoxWindow()->FxSetTitle(csName);
}

bool UILayerWindow :: LayerSetFont(CBfc_String &fontname,double d_pointSize)
{
	return GetFoxWindow()->FxSetFont(fontname.GetPtr());
}

UINT UILayerWindow :: LayerGetText (CBfc::STRING &cs) const
{
	return GetFoxWindow()->FxGetText(cs);
}

UINT  UILayerWindow :: LayerGetIndex() const
{
	return GetFoxWindow()->FxGetIndex();
}

void UILayerWindow :: LayerSelectAll()
{
	GetFoxWindow()->FxSelectAll();
}

Size2dU UILayerWindow :: LayerGetSizeOnScreen(const STRING &cs) const
{
	return GetFoxWindow()->FxGetSizeOnScreen(cs);
}


bool	UILayerWindow :: CreateDCw(const CBfc::Rect2dU &rect2d)
{
	return GetFoxWindow()->CreateDC(rect2d);
}

void	UILayerWindow :: ReleaseDC()
{
	GetFoxWindow()->ReleaseDC();
}


void	UILayerWindow :: SetColor(const UINT color) const
{
	GetFoxWindow()->SetColor(color);
}

void	UILayerWindow :: DrawRectangle(const CBfc::Rect2dU &rect2d) const
{
	GetFoxWindow()->DrawRectangle(rect2d);
}

void	UILayerWindow :: FillRectangle(const CBfc::Rect2dU &rect2d) const
{
	GetFoxWindow()->FillRectangle(rect2d);
}

void	UILayerWindow :: DrawEllipse(const CBfc::Rect2dU &rect2d) const
{
	UINT		x,y,uw,uh;
	rect2d.Get (x,y,uw,uh);

	GetFoxWindow()->GetDC()->drawEllipse(x,y,uw,uh);
}

void	UILayerWindow :: FillEllipse(const CBfc::Rect2dU &rect2d) const
{
	UINT		x,y,uw,uh;
	rect2d.Get (x,y,uw,uh);

	GetFoxWindow()->GetDC()->fillEllipse(x,y,uw,uh);
}

void	UILayerWindow :: DrawPixel(const CBfc::Position2dU &pt) const
{
	GetFoxWindow()->GetDC()->drawPoint(pt.GetX(),pt.GetY());
}

void	UILayerWindow :: DrawLine(const CBfc::Position2dU &pt1,const CBfc::Position2dU &pt2) const
{
	GetFoxWindow()->GetDC()->drawLine(pt1.GetX(),pt1.GetY(),pt2.GetX(),pt2.GetY());
}


void	UILayerWindow :: DrawBitmap (const CBfcImage::Bitmap *pBmp, const CBfc::Rect2dU &dest_rect, const CBfc::Position2dU &source_origin, const double zoom) const
{
	FXDrawable	*fxD = GetFoxWindow()->GetAsFox();
	FXDCWindow dc(fxD);
	FXApp	*pApp = (FXApp*)m_p_GUI->GetAppLayerPtr();
	
	const Size2dU	dest_size(dest_rect.GetSize());
	const FXint		ww = dest_size.GetX();

	UINT 			nLines = 16;
	FXColor		*pixelData = new FXColor[ww * nLines];
	
// 	Size2dU	tsz;
// 	pBmp->GetSize(tsz);
//  	BFC_TRACE (_TXT("Draw bitmap (%d x %d).\n"),  tsz.GetX(), tsz.GetY());
	Position2dU		pos(0,0);	
	Position2dU		dest_pos(dest_rect.TopLeft());
	
	while (1)
	{
		if (pos.GetY() >= dest_size.GetY())
			break;
		const int linmax = dest_size.GetY() - pos.GetY();
		if (linmax < nLines)
			nLines = linmax;
		
		const Position2dU		source_pos(source_origin + (dest_pos / zoom));
		const Size2dU		grabsize(ww,nLines);
		if (pBmp->GetZoomedScanlines ((BYTE*)pixelData, source_pos, grabsize, zoom, fox_colorspace))
		{
			FXImage fxImg (pApp, pixelData, IMAGE_DITHER|IMAGE_KEEP, ww, nLines);
			fxImg.create();		// takes lots of compute power.
// 			int i = fxImg.id();
			dc.drawImage (&fxImg, dest_pos.GetX(), dest_pos.GetY());
		}
		
		const Position2dU offset(0,nLines);
		dest_pos += offset;
		pos += offset;
	}
	delete[] pixelData;
}


void	UILayerWindow :: Dirty()
{
	GetFoxWindow()->GetAsFox()->update();
}

void UILayerWindow::LayerSetFocus()
{
	GetFoxWindow()->GetAsFox()->setFocus();
}

  /// Notification that focus moved to new child
void UILayerWindow::LayerChangeFocus(UILayerWindow *pChild)
{
	GetFoxWindow()->GetAsFox()->changeFocus(pChild->GetFoxWindow()->GetAsFox());
}

void UILayerWindow::SetWindowFocus (void)
{
	GetFoxWindow()->GetAsFox()->setFocus();
	GetFoxWindow()->GetAsFox()->setDefault();
	GetFoxWindow()->GetAsFox()->setInitial();
}

void UILayerWindow::SetWindowDefault()
{
	GetFoxWindow()->GetAsFox()->setDefault();
}

bool UILayerWindow::GrabKeyboard()
{
	bool	bRval = m_b_keygrab;
	if (!m_b_keygrab)
	{
		GetFoxWindow()->GetAsFox()->grabKeyboard();
		m_b_keygrab = true;
	}
	return bRval;
}

bool UILayerWindow::UnGrabKeyboard()
{
	bool	bRval = m_b_keygrab;
	if (m_b_keygrab)
	{
		GetFoxWindow()->GetAsFox()->ungrabKeyboard();
		m_b_keygrab = false;
	}
	return bRval;
}

CBfc::Position2dU	UILayerWindow::GetXYOfPos(const CBfc::Position2dU &pos) const
{
	return GetFoxWindow()->getXYOfPos(pos);
}

void *UILayerWindow::CreateVisual (AppLayerPtr app)
{
	return (void*)new FX::FXGLVisual ((FXApp*)app, FXVisualOptions::VISUAL_DOUBLEBUFFER);
}



Menu::Menu (Window *winp)
{
	m_u_menuDepth=0;
	m_p_target = (void*)winp->GetFoxWindow()->GetAsFox();
	m_p_container = (void *)winp->GetFoxWindow()->GetAsFoxContainer();
	m_topdock=(BYTEPTR)new FXDockSite((FXComposite*)m_p_container,LAYOUT_SIDE_TOP|LAYOUT_FILL_X);
	m_menubar=(BYTEPTR)new FXMenuBar((FXDockSite*)m_topdock,(FXComposite*)m_p_container);
	m_menuTree[0] = NULL;
}

Menu::~Menu ()
{
}


bool Menu::StartSubmenu(const STRING &csText)
{
	if (m_menuTree[m_u_menuDepth])
		if (++m_u_menuDepth >= MAX_MENU_DEPTH)
			return false;
	m_menuTree[m_u_menuDepth]=(BYTEPTR)new FXMenuPane((FXComposite*)m_p_container);
	char *szBuf = csText.MakeAsciiBuffer();
	new FXMenuTitle((FXMenuBar*)m_menubar,szBuf,NULL,(FXMenuPane*)m_menuTree[m_u_menuDepth]);
//				delete[] szBuf;
	return true;
}

void Menu::EndSubmenu()
{
	m_u_menuDepth--;
}

bool Menu::AddEntry(const STRING &csText, const UINT id)
{
	char *szBuf = csText.MakeAsciiBuffer();
	new FXMenuCommand((FXMenuPane*)m_menuTree[m_u_menuDepth],szBuf,NULL,(FXObject*)m_p_target,id);
//	delete[] szBuf;
	return true;
}


}

#endif	// ifdef USING_FOX


