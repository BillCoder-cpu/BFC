//*/
/*
					CQuickGUIBFCWindow.cpp : 
	
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
*                        Integration of QuickGUI into BFCGui                         *
*                                                                               *
********************************************************************************/
#include <BFC/BFCGUI.h>
#ifdef USING_QUICKGUI

#include "CQuickGUIBFCWindow.h"
using namespace CBfc;

namespace CBfcGUI
{
FXDEFMAP(CFoxMainWindow) CFoxMainWindowMap[]=
{
  FXMAPFUNC(SEL_PAINT,              0, CFoxBFCWindow::onFxPaint),
//  FXMAPFUNC(SEL_PAINT,             CFoxBFCWindow::ID_CANVAS, CFoxBFCWindow::onFxPaint),
  FXMAPFUNC(SEL_KEYPRESS,			0, CFoxBFCWindow::onFxKeyPress),
  FXMAPFUNC(SEL_KEYRELEASE,			0, CFoxBFCWindow::onFxKeyRelease),
  FXMAPFUNC(SEL_LEFTBUTTONPRESS,	0, CFoxBFCWindow::onFxMouseDown),
  FXMAPFUNC(SEL_LEFTBUTTONRELEASE,	0, CFoxBFCWindow::onFxMouseUp),
  FXMAPFUNC(SEL_MOTION,				0, CFoxBFCWindow::onFxMouseMove),
  FXMAPFUNC(SEL_COMMAND,	CFoxBFCWindow::ID_CLEAR,  CFoxBFCWindow::onFxCmdClear),
  FXMAPFUNC(SEL_UPDATE,		CFoxBFCWindow::ID_CLEAR,  CFoxBFCWindow::onFxUpdClear),
  FXMAPFUNC(SEL_FOCUSIN,			0, CFoxBFCWindow::onFxFocusIn),
  FXMAPFUNC(SEL_FOCUSOUT,			0, CFoxBFCWindow::onFxFocusOut),
  FXMAPFUNC(SEL_DESTROY,			0, CFoxBFCWindow::onFxDestroy),
  FXMAPFUNCS(SEL_COMMAND,	0,	0xffff, CFoxBFCWindow::onFxButtonPress),
};

FXIMPLEMENT(CFoxMainWindow,FXMainWindow,CFoxMainWindowMap,ARRAYNUMBER(CFoxMainWindowMap))

//	: FXMainWindow(a,csTitle.GetPtr(),NULL,NULL,DECOR_ALL,4,24,800,600)
CFoxMainWindow::CFoxMainWindow(FXApp *p_App,const CBfc_String &csTitle, UILayerWindow* p_Layer)
	: FXMainWindow(p_App,"Main Window",NULL,NULL,DECOR_ALL,4,24,800,600)
	,	CFoxBFCWindow(WND_MAIN, p_App, p_Layer)
{
	enable();
}

FXWindow *CFoxMainWindow::GetAsFox() const
{
	return (FXWindow *)this;
}

long CFoxMainWindow::HandleAsBase(FXObject*p_sender,FXSelector fxsel,void* ptr)
{
	return FXMainWindow::handle(p_sender,fxsel,ptr);
}

// Message Map
FXDEFMAP(CFoxTopWindow) CFoxTopWindowMap[]=
{
  //________Message_Type_____________________ID____________Message_Handler_______
  FXMAPFUNC(SEL_PAINT,              0, CFoxBFCWindow::onFxPaint),
//  FXMAPFUNC(SEL_PAINT,             CFoxBFCWindow::ID_CANVAS, CFoxBFCWindow::onFxPaint),
  FXMAPFUNC(SEL_KEYPRESS,		0, CFoxBFCWindow::onFxKeyPress),
  FXMAPFUNC(SEL_KEYRELEASE,		0, CFoxBFCWindow::onFxKeyRelease),
  FXMAPFUNC(SEL_LEFTBUTTONPRESS,	0, CFoxBFCWindow::onFxMouseDown),
  FXMAPFUNC(SEL_LEFTBUTTONRELEASE,	0, CFoxBFCWindow::onFxMouseUp),
  FXMAPFUNC(SEL_MOTION,			0, CFoxBFCWindow::onFxMouseMove),
  FXMAPFUNC(SEL_COMMAND, CFoxBFCWindow::ID_CLEAR,  CFoxBFCWindow::onFxCmdClear),
  FXMAPFUNC(SEL_UPDATE,	 CFoxBFCWindow::ID_CLEAR,  CFoxBFCWindow::onFxUpdClear),
  FXMAPFUNC(SEL_FOCUSIN,		0, CFoxBFCWindow::onFxFocusIn),
  FXMAPFUNC(SEL_FOCUSOUT,		0, CFoxBFCWindow::onFxFocusOut),
  FXMAPFUNC(SEL_DESTROY,		0, CFoxBFCWindow::onFxDestroy),
  FXMAPFUNCS(SEL_COMMAND,	0,	0xffff, CFoxBFCWindow::onFxButtonPress),
};
FXIMPLEMENT(CFoxTopWindow,FXTopWindow,CFoxTopWindowMap,ARRAYNUMBER(CFoxTopWindowMap))
// Construct a CFoxBFCWindow
CFoxTopWindow::CFoxTopWindow(FXApp *p_App, const CBfc::STRING &csTitle, UILayerWindow* p_Layer, UILayerWindow *p_Parent)
//: FXTopWindow((FXWindow*)p_Parent->GetFoxWindow(),csTitle.GetPtr(),NULL,NULL,DECOR_ALL,0,0,100,100,10,10,10,10,4,4)
	: FXTopWindow(p_Parent->GetFoxWindow()->GetAsFox(),csTitle.MakeAsciiBuffer(),NULL,NULL,DECOR_ALL|PLACEMENT_OWNER,0,0,800,600,10,10,10,10,4,4)
	,	CFoxBFCWindow(WND_TOP, p_App, p_Layer)
{
	enable();
}

FXWindow *CFoxTopWindow::GetAsFox() const
{
	return (FXWindow *)this;
}

long CFoxTopWindow::HandleAsBase(FXObject*p_sender,FXSelector fxsel,void* ptr)
{
	return FXTopWindow::handle(p_sender,fxsel,ptr);
}

// Message Map
FXDEFMAP(CFoxChildWindow) CFoxChildWindowMap[]=
{
  //________Message_Type_____________________ID____________Message_Handler_______
  FXMAPFUNC(SEL_PAINT,              0, CFoxBFCWindow::onFxPaint),
//  FXMAPFUNC(SEL_PAINT,             CFoxBFCWindow::ID_CANVAS, CFoxBFCWindow::onFxPaint),
  FXMAPFUNC(SEL_KEYPRESS,			0, CFoxBFCWindow::onFxKeyPress),
  FXMAPFUNC(SEL_KEYRELEASE,			0, CFoxBFCWindow::onFxKeyRelease),
  FXMAPFUNC(SEL_LEFTBUTTONPRESS,	0, CFoxBFCWindow::onFxMouseDown),
  FXMAPFUNC(SEL_LEFTBUTTONRELEASE,	0, CFoxBFCWindow::onFxMouseUp),
  FXMAPFUNC(SEL_MOTION,				0, CFoxBFCWindow::onFxMouseMove),
  FXMAPFUNC(SEL_COMMAND,	CFoxBFCWindow::ID_CLEAR,  CFoxBFCWindow::onFxCmdClear),
  FXMAPFUNC(SEL_UPDATE,		CFoxBFCWindow::ID_CLEAR,  CFoxBFCWindow::onFxUpdClear),
  FXMAPFUNC(SEL_FOCUSIN,			0, CFoxBFCWindow::onFxFocusIn),
  FXMAPFUNC(SEL_FOCUSOUT,			0, CFoxBFCWindow::onFxFocusOut),
  FXMAPFUNC(SEL_DESTROY,			0, CFoxBFCWindow::onFxDestroy),
  FXMAPFUNCS(SEL_COMMAND,	0,	0xffff, CFoxBFCWindow::onFxButtonPress),
};
FXIMPLEMENT(CFoxChildWindow,FXComposite,CFoxChildWindowMap,ARRAYNUMBER(CFoxChildWindowMap))

CFoxChildWindow::CFoxChildWindow(FXApp *p_App, UILayerWindow* p_Layer, UILayerWindow* p_Parent)
	: FXComposite(p_Parent->GetFoxWindow()->GetAsFoxContainer(),DECOR_ALL,0,0,800,600)
	, CFoxBFCWindow(WND_CHILD, p_App, p_Layer)
{
	enable();
}

FXWindow *CFoxChildWindow::GetAsFox() const
{
	return (FXWindow *)this;
}

long CFoxChildWindow::HandleAsBase(FXObject*p_sender,FXSelector fxsel,void* ptr)
{
	return FXComposite::handle(p_sender,fxsel,ptr);
}


FXDEFMAP(CFoxButtonWindow) CFoxButtonWindowMap[]=
{
  //________Message_Type_____________________ID____________Message_Handler_______
  FXMAPFUNC(SEL_PAINT,              0, CFoxBFCWindow::onFxPaint),
//  FXMAPFUNC(SEL_PAINT,             CFoxBFCWindow::ID_CANVAS, CFoxBFCWindow::onFxPaint),
  FXMAPFUNC(SEL_KEYPRESS,			0, CFoxBFCWindow::onFxKeyPress),
  FXMAPFUNC(SEL_KEYRELEASE,			0, CFoxBFCWindow::onFxKeyRelease),
  FXMAPFUNC(SEL_LEFTBUTTONPRESS,	0, CFoxBFCWindow::onFxMouseDown),
  FXMAPFUNC(SEL_LEFTBUTTONRELEASE,	0, CFoxBFCWindow::onFxMouseUp),
  FXMAPFUNC(SEL_MOTION,				0, CFoxBFCWindow::onFxMouseMove),

  FXMAPFUNC(SEL_ENTER,				0, CFoxBFCWindow::onFxMouseEnter),
  FXMAPFUNC(SEL_LEAVE,				0, CFoxBFCWindow::onFxMouseLeave),

  FXMAPFUNC(SEL_FOCUSIN,			0, CFoxBFCWindow::onFxFocusIn),
  FXMAPFUNC(SEL_FOCUSOUT,			0, CFoxBFCWindow::onFxFocusOut),
  FXMAPFUNC(SEL_DESTROY,			0, CFoxBFCWindow::onFxDestroy),
};

FXIMPLEMENT(CFoxButtonWindow,FXButton,CFoxButtonWindowMap,ARRAYNUMBER(CFoxButtonWindowMap))

CFoxButtonWindow::CFoxButtonWindow(FXApp *p_App, const CBfc::STRING &csText,const Resource_ID resourceID, UILayerWindow* p_Layer, UILayerWindow *p_Parent)
	: FXButton(p_Parent->GetFoxWindow()->GetAsFoxContainer(),"test",NULL,p_Parent->GetFoxWindow()->GetAsFox(),resourceID,FRAME_RAISED|FRAME_THICK)
	, CFoxBFCWindow(WND_BUTTON, p_App, p_Layer)
{
	SetText(csText);
	m_p_switcher=p_Parent->GetFoxWindow()->GetSwitcher();
}

FXWindow *CFoxButtonWindow::GetAsFox() const
{
	return (FXWindow *)this;
}

long CFoxButtonWindow::HandleAsBase(FXObject*p_sender,FXSelector fxsel,void* ptr)
{
	return FXButton::handle(p_sender,fxsel,ptr);
}

extern CBfcImage::ColorSpace fox_colorspace;

void CFoxButtonWindow::MakeToolbar()
{
	FXuint style = getButtonStyle();
	setButtonStyle(style | FX::BUTTON_TOOLBAR);
}

void CFoxButtonWindow::SetIcon(const CBfcImage::Bitmap *pBmp)
{	
	if (pBmp)
	{
		Size2dU	size;
		pBmp->GetSize(size);
		const UINT	area = size.Product();
		BYTE	*pixelData = new BYTE[area*4];
		
		if (pBmp->GetRectangle(pixelData, size, Position2dU(), fox_colorspace))
		{
// 			Resize(size.GetX(),size.GetY());
// 			GetAsFox()->resize(size.GetX(),size.GetY());
			FXIcon *pIcon = new FXIcon(m_p_FoxApplication, (FX::FXColor*)pixelData, 0, IMAGE_DITHER|IMAGE_KEEP, size.GetX(),size.GetY());
			pIcon->create();		// 
			setIcon(pIcon);		//
		}
	}
}

void CFoxButtonWindow::SetText(const CBfc::STRING &csText)
{
	if (!csText.IsEmpty())
	{
		CBfc::STRING sTemp(csText);
		char *szBuf = sTemp.BorrowAsciiBuffer();
		setText(szBuf);
	}
}

FXDEFMAP(CFoxDialogWindow) CFoxDialogWindowMap[]=
{
  //________Message_Type_____________________ID____________Message_Handler_______
  FXMAPFUNC(SEL_PAINT,              0, CFoxBFCWindow::onFxPaint),
//  FXMAPFUNC(SEL_PAINT,             CFoxBFCWindow::ID_CANVAS, CFoxBFCWindow::onFxPaint),
  FXMAPFUNC(SEL_KEYPRESS,			0, CFoxBFCWindow::onFxKeyPress),
  FXMAPFUNC(SEL_KEYRELEASE,			0, CFoxBFCWindow::onFxKeyRelease),
  FXMAPFUNC(SEL_LEFTBUTTONPRESS,	0, CFoxBFCWindow::onFxMouseDown),
  FXMAPFUNC(SEL_LEFTBUTTONRELEASE,	0, CFoxBFCWindow::onFxMouseUp),
  FXMAPFUNC(SEL_MOTION,				0, CFoxBFCWindow::onFxMouseMove),
  FXMAPFUNC(SEL_COMMAND,	CFoxBFCWindow::ID_CLEAR,  CFoxBFCWindow::onFxCmdClear),
  FXMAPFUNC(SEL_UPDATE,		CFoxBFCWindow::ID_CLEAR,  CFoxBFCWindow::onFxUpdClear),
  FXMAPFUNC(SEL_FOCUSIN,			0, CFoxBFCWindow::onFxFocusIn),
  FXMAPFUNC(SEL_FOCUSOUT,			0, CFoxBFCWindow::onFxFocusOut),
  FXMAPFUNC(SEL_DESTROY,			0, CFoxBFCWindow::onFxDestroy),
  FXMAPFUNCS(SEL_COMMAND,	0,	0xffff, CFoxBFCWindow::onFxButtonPress),
};
FXIMPLEMENT(CFoxDialogWindow,FXDialogBox,CFoxDialogWindowMap,ARRAYNUMBER(CFoxDialogWindowMap))

CFoxDialogWindow::CFoxDialogWindow(FXApp *p_App, const CBfc::STRING &csText, UILayerWindow* p_Layer, UILayerWindow *p_Parent)
	: FXDialogBox(p_Parent ? p_Parent->GetFoxWindow()->GetAsFox():NULL,csText.MakeAsciiBuffer()) //,DECOR_ALL)
	, CFoxBFCWindow(WND_DIALOG, p_App, p_Layer)
{
}

FXWindow *CFoxDialogWindow::GetAsFox() const
{
	return (FXWindow *)this;
}

void CFoxDialogWindow::MakeNormal()		// 
{
//  	FXuint style = getButtonStyle();
//  	setButtonStyle(style | FX::BUTTON_TOOLBAR);
// 	enable();
	setDecorations(FX::DECOR_ALL); // DECOR_TITLE | FX::DECOR_STRETCHABLE);
// 	show(PLACEMENT_OWNER);	
// 	return getApp()->runModalFor(this);
}


long CFoxDialogWindow::HandleAsBase(FXObject*p_sender,FXSelector fxsel,void* ptr)
{
	return FXDialogBox::handle(p_sender,fxsel,ptr);
}

void CFoxDialogWindow::AddSpacer(UINT nCount)
{
	if (nCount==0) nCount=1;
	while (nCount--)
		new FXFrame(GetAsFoxContainer(),FRAME_NONE);
}

void CFoxDialogWindow::AddMatrix(const Size2dU &size)
{
	UINT		x,y;
	FXuint	style;
	
	size.Get(x,y);
	if (x > 0) style=MATRIX_BY_COLUMNS;
	else {
		style=MATRIX_BY_ROWS;
		x=y;
	}
	PushFrame((FXComposite*)new FXMatrix(GetAsFoxContainer(),x,style));
}

void CFoxDialogWindow::AddSwitcher(const Resource_ID rID)
{
	m_p_switcher=new FXSwitcher(GetAsFoxContainer(),LAYOUT_FILL_X|LAYOUT_FILL_Y,0,0,0,0, 0,0,0,0);
	PushFrame((FXComposite*)m_p_switcher);
}

void CFoxDialogWindow::EndFrame()
{
	PopFrame();
}

void CFoxDialogWindow::PushFrame (const FXComposite *p_Frame)
{
	BYTEPTR ptr= (BYTEPTR)p_Frame;
	m_frameArray.Add(&ptr);
}

void CFoxDialogWindow::PopFrame()
{
	m_frameArray.RemoveAt (m_frameArray.GetCountAsULONG()-1);
}

FXComposite *CFoxDialogWindow::GetFrame() const
{
	BYTEPTR *p_ptr = m_frameArray.GetAt(m_frameArray.GetCountAsULONG()-1);
	if (p_ptr)
		return (FXComposite*)*p_ptr;
	return (FXComposite*)this;
}


FXDEFMAP(CFoxTextWindow) CFoxTextWindowMap[]=
{
  //________Message_Type_____________________ID____________Message_Handler_______
  FXMAPFUNC(SEL_PAINT,              0, CFoxBFCWindow::onFxPaint),
//  FXMAPFUNC(SEL_PAINT,             CFoxBFCWindow::ID_CANVAS, CFoxBFCWindow::onFxPaint),
  FXMAPFUNC(SEL_KEYPRESS,			0, CFoxBFCWindow::onFxKeyPress),
  FXMAPFUNC(SEL_KEYRELEASE,			0, CFoxBFCWindow::onFxKeyRelease),
  FXMAPFUNC(SEL_LEFTBUTTONPRESS,	0, CFoxBFCWindow::onFxMouseDown),
  FXMAPFUNC(SEL_LEFTBUTTONRELEASE,	0, CFoxBFCWindow::onFxMouseUp),
  FXMAPFUNC(SEL_MOTION,				0, CFoxBFCWindow::onFxMouseMove),
  FXMAPFUNC(SEL_COMMAND,	CFoxBFCWindow::ID_CLEAR,  CFoxBFCWindow::onFxCmdClear),
  FXMAPFUNC(SEL_UPDATE,		CFoxBFCWindow::ID_CLEAR,  CFoxBFCWindow::onFxUpdClear),
  FXMAPFUNC(SEL_FOCUSIN,			0, CFoxBFCWindow::onFxFocusIn),
  FXMAPFUNC(SEL_FOCUSOUT,			0, CFoxBFCWindow::onFxFocusOut),
  FXMAPFUNC(SEL_DESTROY,			0, CFoxBFCWindow::onFxDestroy),
};
FXIMPLEMENT(CFoxTextWindow,FXText,CFoxTextWindowMap,ARRAYNUMBER(CFoxTextWindowMap))
CFoxTextWindow::CFoxTextWindow(FXApp *p_App,const Resource_ID resourceID, UILayerWindow* p_Layer, UILayerWindow *p_Parent)
	: FXText(p_Parent->GetFoxWindow()->GetAsFoxContainer(),NULL,resourceID,TEXT_SHOWACTIVE)
	, CFoxBFCWindow(WND_CURSES, p_App, p_Layer)
{
	setEditable(true);
	enable();
}

FXWindow *CFoxTextWindow::GetAsFox() const
{
	return (FXWindow *)this;
}

long CFoxTextWindow::HandleAsBase(FXObject*p_sender,FXSelector fxsel,void* ptr)
{
	return FXText::handle(p_sender,fxsel,ptr);
}

void CFoxTextWindow::GetTextSizeOnScreen(CBfc::Size2dU & size,const STRING &cs) const
{
	character	c;
	UINT		index=0, width=0;

	while ((c=cs[index++]))
		width += FXText::charWidth(c,0);
	size.SetX(width);
	size.SetY(FXText::getFont()->getFontHeight());
}

/// Change number of visible rows
 bool CFoxTextWindow :: SizeTextbox(const Size2dU &size)
{
	UINT	rows,cols;
	size.Get(cols,rows);
	setVisibleRows((FXint) rows);
	setVisibleColumns((FXint) cols);
	m_size=size;
	return true;
}

void CFoxTextWindow::SetText(const CBfc::STRING &csText)
{
	if (!csText.IsEmpty())
	{
		CBfc::STRING sTemp(csText);
		char *szBuf = sTemp.BorrowAsciiBuffer();
		setText(szBuf);
	}
}

CBfc::Position2dU CFoxTextWindow::getXYOfPos(const CBfc::Position2dU &pos) const
{
	int	fxpos=pos.GetX() + (pos.GetY() * (m_size.GetX()+1));
	int cpos=getCursorPos();
	return CBfc::Position2dU(getXOfPos(fxpos),getYOfPos(fxpos));
}

void CFoxTextWindow::SelectAll()
{
	selectAll();
}

FXDEFMAP(CFoxTextboxWindow) CFoxTextboxWindowMap[]=
{
  //________Message_Type_____________________ID____________Message_Handler_______
  FXMAPFUNC(SEL_PAINT,              0, CFoxBFCWindow::onFxPaint),
//  FXMAPFUNC(SEL_PAINT,             CFoxBFCWindow::ID_CANVAS, CFoxBFCWindow::onFxPaint),
  FXMAPFUNC(SEL_KEYPRESS,			0, CFoxBFCWindow::onFxKeyPress),
  FXMAPFUNC(SEL_KEYRELEASE,			0, CFoxBFCWindow::onFxKeyRelease),
  FXMAPFUNC(SEL_LEFTBUTTONPRESS,	0, CFoxBFCWindow::onFxMouseDown),
  FXMAPFUNC(SEL_LEFTBUTTONRELEASE,	0, CFoxBFCWindow::onFxMouseUp),
  FXMAPFUNC(SEL_MOTION,				0, CFoxBFCWindow::onFxMouseMove),
  FXMAPFUNC(SEL_FOCUSIN,			0, CFoxBFCWindow::onFxFocusIn),
  FXMAPFUNC(SEL_FOCUSOUT,			0, CFoxBFCWindow::onFxFocusOut),
  FXMAPFUNC(SEL_DESTROY,			0, CFoxBFCWindow::onFxDestroy),
};

//  FXTextField(FXComposite* p,FXint ncols,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=TEXTFIELD_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD);

FXIMPLEMENT(CFoxTextboxWindow,FXTextField,CFoxTextboxWindowMap,ARRAYNUMBER(CFoxTextboxWindowMap))
CFoxTextboxWindow::CFoxTextboxWindow(FXApp *p_App,const CBfc::STRING &csText,const Resource_ID resourceID, UILayerWindow* p_Layer, UILayerWindow *p_Parent)
	: FXTextField(p_Parent->GetFoxWindow()->GetAsFoxContainer(),3,p_Parent->GetFoxWindow()->GetAsFox(),resourceID,TEXTFIELD_LIMITED|TEXTFIELD_NORMAL)
	, CFoxBFCWindow(WND_TEXTBOX, p_App, p_Layer)
{
	SetText(csText);
	FXTextField::setJustify(JUSTIFY_RIGHT);
}

FXWindow *CFoxTextboxWindow::GetAsFox() const
{
	return (FXWindow *)this;
}

long CFoxTextboxWindow::HandleAsBase(FXObject*p_sender,FXSelector fxsel,void* ptr)
{
	return FXTextField::handle(p_sender,fxsel,ptr);
}

void CFoxTextboxWindow::RestrainNumeric()
{
	setTextStyle(TEXTFIELD_REAL|TEXTFIELD_NORMAL|TEXTFIELD_LIMITED);
}

void CFoxTextboxWindow::RestrainInteger()
{
	setTextStyle(TEXTFIELD_INTEGER|TEXTFIELD_NORMAL|TEXTFIELD_LIMITED);
}

void CFoxTextboxWindow::RestrainPassword()
{
	setTextStyle(TEXTFIELD_PASSWD|TEXTFIELD_NORMAL|TEXTFIELD_LIMITED);
}

void CFoxTextboxWindow::RestrainDistance()
{
	setTextStyle(TEXTFIELD_NORMAL|TEXTFIELD_LIMITED);
}

void CFoxTextboxWindow::SetText(const CBfc::STRING &csText)
{
	if (!csText.IsEmpty())
	{
		CBfc::STRING sTemp(csText);
		char *szBuf = sTemp.BorrowAsciiBuffer();
		setText(szBuf);
	}
}


FXDEFMAP(CFoxLabelWindow) CFoxLabelWindowMap[]=
{
  //________Message_Type_____________________ID____________Message_Handler_______
  FXMAPFUNC(SEL_PAINT,              0, CFoxBFCWindow::onFxPaint),
//  FXMAPFUNC(SEL_PAINT,             CFoxBFCWindow::ID_CANVAS, CFoxBFCWindow::onFxPaint),
  FXMAPFUNC(SEL_KEYPRESS,			0, CFoxBFCWindow::onFxKeyPress),
  FXMAPFUNC(SEL_KEYRELEASE,			0, CFoxBFCWindow::onFxKeyRelease),
  FXMAPFUNC(SEL_LEFTBUTTONPRESS,	0, CFoxBFCWindow::onFxMouseDown),
  FXMAPFUNC(SEL_LEFTBUTTONRELEASE,	0, CFoxBFCWindow::onFxMouseUp),
  FXMAPFUNC(SEL_MOTION,				0, CFoxBFCWindow::onFxMouseMove),
  FXMAPFUNC(SEL_FOCUSIN,			0, CFoxBFCWindow::onFxFocusIn),
  FXMAPFUNC(SEL_FOCUSOUT,			0, CFoxBFCWindow::onFxFocusOut),
  FXMAPFUNC(SEL_DESTROY,			0, CFoxBFCWindow::onFxDestroy),
};

//  FXLabel(FXComposite* p,const FXString& text,FXIcon* ic=0,FXuint opts=LABEL_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD);
FXIMPLEMENT(CFoxLabelWindow,FXLabel,CFoxLabelWindowMap,ARRAYNUMBER(CFoxLabelWindowMap))
CFoxLabelWindow::CFoxLabelWindow(FXApp *p_App, const CBfc::STRING &csText,const Resource_ID resourceID, UILayerWindow* p_Layer, UILayerWindow *p_Parent)
	: FXLabel(p_Parent->GetFoxWindow()->GetAsFoxContainer(),"test")
	, CFoxBFCWindow(WND_LABEL, p_App, p_Layer)
{
	SetText(csText);
}

FXWindow *CFoxLabelWindow::GetAsFox() const
{
	return (FXWindow *)this;
}

long CFoxLabelWindow::HandleAsBase(FXObject*p_sender,FXSelector fxsel,void* ptr)
{
	return FXLabel::handle(p_sender,fxsel,ptr);
}


void CFoxLabelWindow::SetText(const CBfc::STRING &csText)
{
	if (!csText.IsEmpty())
	{
		CBfc::STRING sTemp(csText);
		char *szBuf = sTemp.BorrowAsciiBuffer();
		setText(szBuf);
	}
}


FXDEFMAP(CFoxListWindow) CFoxListWindowMap[]=
{
  //________Message_Type_____________________ID____________Message_Handler_______
  FXMAPFUNC(SEL_PAINT,              0, CFoxBFCWindow::onFxPaint),
//  FXMAPFUNC(SEL_PAINT,             CFoxBFCWindow::ID_CANVAS, CFoxBFCWindow::onFxPaint),
  FXMAPFUNC(SEL_KEYPRESS,			0, CFoxBFCWindow::onFxKeyPress),
  FXMAPFUNC(SEL_KEYRELEASE,			0, CFoxBFCWindow::onFxKeyRelease),
  FXMAPFUNC(SEL_LEFTBUTTONPRESS,	0, CFoxBFCWindow::onFxMouseDown),
  FXMAPFUNC(SEL_LEFTBUTTONRELEASE,	0, CFoxBFCWindow::onFxMouseUp),
  FXMAPFUNC(SEL_MOTION,				0, CFoxBFCWindow::onFxMouseMove),
  FXMAPFUNC(SEL_FOCUSIN,			0, CFoxBFCWindow::onFxFocusIn),
  FXMAPFUNC(SEL_FOCUSOUT,			0, CFoxBFCWindow::onFxFocusOut),
  FXMAPFUNC(SEL_DESTROY,			0, CFoxBFCWindow::onFxDestroy),
};

//  FXComboBox(FXComposite *p,FXint cols,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=COMBOBOX_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD);
FXIMPLEMENT(CFoxListWindow,FXList,CFoxListWindowMap,ARRAYNUMBER(CFoxListWindowMap))
CFoxListWindow::CFoxListWindow(FXApp *p_App,const Resource_ID resourceID, UILayerWindow* p_Layer, UILayerWindow *p_Parent)
	: FXList(p_Parent->GetFoxWindow()->GetAsFoxContainer(),p_Parent->GetFoxWindow()->GetAsFox(),resourceID,LIST_BROWSESELECT|LAYOUT_FIX_WIDTH,0,0,0,0)
	, CFoxBFCWindow(WND_LIST, p_App, p_Layer)
{
}

FXWindow *CFoxListWindow::GetAsFox() const
{
	return (FXWindow *)this;
}

long CFoxListWindow::HandleAsBase(FXObject*p_sender,FXSelector fxsel,void* ptr)
{
	return FXList::handle(p_sender,fxsel,ptr);
}



FXDEFMAP(CFoxListboxWindow) CFoxListboxWindowMap[]=
{
  //________Message_Type_____________________ID____________Message_Handler_______
  FXMAPFUNC(SEL_PAINT,              0, CFoxBFCWindow::onFxPaint),
//  FXMAPFUNC(SEL_PAINT,             CFoxBFCWindow::ID_CANVAS, CFoxBFCWindow::onFxPaint),
  FXMAPFUNC(SEL_KEYPRESS,			0, CFoxBFCWindow::onFxKeyPress),
  FXMAPFUNC(SEL_KEYRELEASE,			0, CFoxBFCWindow::onFxKeyRelease),
  FXMAPFUNC(SEL_LEFTBUTTONPRESS,	0, CFoxBFCWindow::onFxMouseDown),
  FXMAPFUNC(SEL_LEFTBUTTONRELEASE,	0, CFoxBFCWindow::onFxMouseUp),
  FXMAPFUNC(SEL_MOTION,				0, CFoxBFCWindow::onFxMouseMove),
  FXMAPFUNC(SEL_FOCUSIN,			0, CFoxBFCWindow::onFxFocusIn),
  FXMAPFUNC(SEL_FOCUSOUT,			0, CFoxBFCWindow::onFxFocusOut),
  FXMAPFUNC(SEL_DESTROY,			0, CFoxBFCWindow::onFxDestroy),
};

//  FXComboBox(FXComposite *p,FXint cols,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=COMBOBOX_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD);
FXIMPLEMENT(CFoxListboxWindow,FXListBox,CFoxListboxWindowMap,ARRAYNUMBER(CFoxListboxWindowMap))
CFoxListboxWindow::CFoxListboxWindow(FXApp *p_App,const Resource_ID resourceID, UILayerWindow* p_Layer, UILayerWindow *p_Parent)
	: FXListBox(p_Parent->GetFoxWindow()->GetAsFoxContainer(),p_Parent->GetFoxWindow()->GetAsFox(),resourceID)
	, CFoxBFCWindow(WND_LISTBOX, p_App, p_Layer)
{
  setNumVisible(4);
}

FXWindow *CFoxListboxWindow::GetAsFox() const
{
	return (FXWindow *)this;
}

long CFoxListboxWindow::HandleAsBase(FXObject*p_sender,FXSelector fxsel,void* ptr)
{
	return FXListBox::handle(p_sender,fxsel,ptr);
}




FXDEFMAP(CFoxComboWindow) CFoxComboWindowMap[]=
{
  //________Message_Type_____________________ID____________Message_Handler_______
  FXMAPFUNC(SEL_PAINT,              0, CFoxBFCWindow::onFxPaint),
//  FXMAPFUNC(SEL_PAINT,             CFoxBFCWindow::ID_CANVAS, CFoxBFCWindow::onFxPaint),
  FXMAPFUNC(SEL_KEYPRESS,			0, CFoxBFCWindow::onFxKeyPress),
  FXMAPFUNC(SEL_KEYRELEASE,			0, CFoxBFCWindow::onFxKeyRelease),
  FXMAPFUNC(SEL_LEFTBUTTONPRESS,	0, CFoxBFCWindow::onFxMouseDown),
  FXMAPFUNC(SEL_LEFTBUTTONRELEASE,	0, CFoxBFCWindow::onFxMouseUp),
  FXMAPFUNC(SEL_MOTION,				0, CFoxBFCWindow::onFxMouseMove),
  FXMAPFUNC(SEL_FOCUSIN,			0, CFoxBFCWindow::onFxFocusIn),
  FXMAPFUNC(SEL_FOCUSOUT,			0, CFoxBFCWindow::onFxFocusOut),
  FXMAPFUNC(SEL_DESTROY,			0, CFoxBFCWindow::onFxDestroy),
};

//  FXComboBox(FXComposite *p,FXint cols,FXObject* tgt=NULL,FXSelector sel=0,FXuint opts=COMBOBOX_NORMAL,FXint x=0,FXint y=0,FXint w=0,FXint h=0,FXint pl=DEFAULT_PAD,FXint pr=DEFAULT_PAD,FXint pt=DEFAULT_PAD,FXint pb=DEFAULT_PAD);
FXIMPLEMENT(CFoxComboWindow,FXComboBox,CFoxComboWindowMap,ARRAYNUMBER(CFoxComboWindowMap))
CFoxComboWindow::CFoxComboWindow(FXApp *p_App,const UINT nCols,const Resource_ID resourceID, UILayerWindow* p_Layer, UILayerWindow *p_Parent)
	: FXComboBox(p_Parent->GetFoxWindow()->GetAsFoxContainer(),nCols,p_Parent->GetFoxWindow()->GetAsFox(),resourceID)
	, CFoxBFCWindow(WND_COMBO, p_App, p_Layer)
{
  setNumVisible(4);
  setEditable(false);
}

FXWindow *CFoxComboWindow::GetAsFox() const
{
	return (FXWindow *)this;
}

long CFoxComboWindow::HandleAsBase(FXObject*p_sender,FXSelector fxsel,void* ptr)
{
	return FXComboBox::handle(p_sender,fxsel,ptr);
}

void CFoxComboWindow::SetText(const CBfc::STRING &csText)
{
	if (!csText.IsEmpty())
	{
		CBfc::STRING sTemp(csText);
		char *szBuf = sTemp.BorrowAsciiBuffer();
		setText(szBuf);
	}
}


///////////////////////////////////////////////////////
///////////////////////////////////////////////////
///////////////////////////////////////////////
///////////////////////////////////////////
///////////////////////////////////////
///////////////////////////////////
CFoxBFCWindow::CFoxBFCWindow(const EBFC_GUI_WINDOW_TYPE eType, FXApp *p_App, UILayerWindow* p_Layer)
	: m_p_FoxApplication (p_App)
	, m_eWndType(eType)
	, m_p_Layer(p_Layer)
	, m_p_Font(NULL)
	, m_p_switcher(NULL)
	, m_p_dc(NULL)
{
  // Initialize private variables
	dirty=0;
}

CFoxBFCWindow::~CFoxBFCWindow()
{
//	BFC_RELEASE_PTR (m_p_Font);
	BFC_RELEASE_PTR (m_p_dc);
}


bool CFoxBFCWindow::CreateDC(const Rect2dU &cliprect)
{
	if (m_p_dc)
		return true;
	FXEvent	event;

	UINT			x,y,w,h;
	cliprect.Get (x,y,w,h);

	event.rect.x = x;
	event.rect.y = y;
	event.rect.w = w;
	event.rect.h = h;
	
	m_p_dc = new FXDCWindow	(this->GetAsFox(),&event);
	return (m_p_dc != NULL);
}

void CFoxBFCWindow::ReleaseDC()
{
	BFC_RELEASE_PTR (m_p_dc);
}

void CFoxBFCWindow::SetColor(const UINT color)
{
	m_p_dc->setForeground(color);
}

void CFoxBFCWindow::DrawRectangle(const CBfc::Rect2dU &rect2d)
{
	UINT		x,y,w,h;
	rect2d.Get (x,y,w,h);

	m_p_dc->drawRectangle(x,y,w,h);
}

void CFoxBFCWindow::FillRectangle(const CBfc::Rect2dU &rect2d)
{
	UINT		x,y,w,h;
	rect2d.Get (x,y,w,h);

	m_p_dc->fillRectangle(x,y,w,h);
}

int CFoxBFCWindow::DoModal()
{
	switch (m_eWndType)
	{
		case WND_DIALOG:
			return ((CFoxDialogWindow*)this)->Execute();
		case WND_CURSES:
		case WND_TEXTBOX:
//			return GetAsFox()->getApp()->run(GetAsFox());
//			return GetAsFox()->getApp()->runPopup(GetAsFox());
			
		default:
			return GetAsFox()->getApp()->runModalFor(GetAsFox());
	}
	return false;
}

FXSwitcher *CFoxBFCWindow::GetSwitcher()
{
	return m_p_switcher;
}

FXComposite *CFoxBFCWindow::GetAsFoxContainer() const
{
	switch (m_eWndType)
	{
		case WND_MAIN:
			return (FXComposite *)(CFoxMainWindow*)this;
		case WND_TOP:
		case WND_3D:
			return (FXComposite *)(CFoxTopWindow*)this;
		case WND_DIALOG:
			return ((CFoxDialogWindow*)this)->GetFrame();
		case WND_CHILD:
			return (FXComposite *)(CFoxChildWindow*)this;
		case WND_CURSES:
			return (FXComposite *)(CFoxTextWindow*)this;
		case WND_BUTTON:
		case WND_LABEL:
		case WND_TEXTBOX:
		case WND_LIST:
		case WND_LISTBOX:
		case WND_COMBO:
		case WND_GL:
			break;
	}
	return NULL;
}

void CFoxBFCWindow::Resize(FXint w,FXint h)
{
//	CFoxBFCWindow_derivedFrom::resize(w,h);
	Size2dU	size(w,h);
	Message	msg(BFCGUI_MSG_RESIZE,(void*)&size);
	
	OnMessage(msg);
}

long CFoxBFCWindow::onFxKeyPress(FXObject*p_sender,FXSelector fxsel,void* ptr)
{
	RecordMessage(p_sender, fxsel, ptr);
	FXEvent *ev=(FXEvent*)ptr;
	const FXchar *cp = ev->text.text();
	void	*vval = (void*)(long)*cp;
	if (vval == NULL)
		vval = (void*)ev->code;
	Message msg(BFCGUI_MSG_KEYPRESS, vval);
	if (OnMessage(msg)==BFCGUIDEFS_MESSAGE_PROCESSED)
		return BFCGUIDEFS_MESSAGE_PROCESSED;
	return HandleAsBase(p_sender, fxsel, ptr);
}

long CFoxBFCWindow::HandleMessage()
{
	return HandleAsBase(m_msg_p_sender, m_msg_fxsel, m_msg_ptr);
}

void CFoxBFCWindow::RecordMessage(FXObject*p_sender,FXSelector fxsel,void* ptr)
{
	m_msg_p_sender=p_sender;
	m_msg_fxsel=fxsel;
	m_msg_ptr=ptr;
}

long CFoxBFCWindow::onFxKeyRelease(FXObject*p_sender,FXSelector fxsel,void* ptr)
{
	RecordMessage(p_sender, fxsel, ptr);
	FXEvent *ev=(FXEvent*)ptr;
	
	Message msg(BFCGUI_MSG_KEYRELEASE,(void*)ev->code);
	if (OnMessage(msg) == BFCGUIDEFS_MESSAGE_PROCESSED)
		return BFCGUIDEFS_MESSAGE_PROCESSED;
	return HandleMessage();
}

// Mouse button was pressed somewhere
long CFoxBFCWindow::onFxMouseDown(FXObject*p_sender,FXSelector fxsel,void*ptr)
{
	RecordMessage(p_sender, fxsel, ptr);
	FXEvent *ev=(FXEvent*)ptr;
//  if (m_p_GLViewer)
//	  m_p_GLViewer->grab();

	Message msg(BFCGUI_MSG_MOUSEDOWN,(void*)(ev->win_y << 16 | ev->win_x));
	if (OnMessage(msg) == BFCGUIDEFS_MESSAGE_PROCESSED)
		return BFCGUIDEFS_MESSAGE_PROCESSED;
	return HandleMessage();
}

// The mouse has moved, draw a line
long CFoxBFCWindow::onFxMouseMove(FXObject*p_sender, FXSelector fxsel, void* ptr)
{
	RecordMessage(p_sender, fxsel, ptr);
  FXEvent *ev=(FXEvent*)ptr;

  // Update ruler arrow locations
  //  hruler->setValue(ev->win_x);
  //  vruler->setValue(ev->win_y);

  // Draw
/*
	if(mdflag)
  {
	  if (m_p_GLViewer)
	  {
		FXDCWindow dc(m_p_GLViewer);		// Get DC for the canvas
		dc.setForeground(drawColor);		// Set foreground color
		dc.drawLine(ev->last_x, ev->last_y, ev->win_x, ev->win_y);		// Draw line
		dirty=1;		// We have drawn something, so now the canvas is dirty
	  }
  }
*/
	const Message msg(BFCGUI_MSG_MOUSEMOVE,(void*)(ev->win_y << 16 | ev->win_x));
	if (OnMessage(msg) == BFCGUIDEFS_MESSAGE_PROCESSED)
		return BFCGUIDEFS_MESSAGE_PROCESSED;
	return HandleMessage();
}

// The mouse button was released again
long CFoxBFCWindow::onFxMouseUp(FXObject*p_sender,FXSelector fxsel,void* ptr)
{
	RecordMessage(p_sender, fxsel, ptr);
	FXEvent *ev=(FXEvent*) ptr;
/*
	if (m_p_GLVisual)
	{
		m_p_GLViewer->ungrab();
		if(mdflag && m_p_GLViewer)
		{
			FXDCWindow dc(m_p_GLViewer);

			dc.setForeground(drawColor);
			dc.drawLine(ev->last_x, ev->last_y, ev->win_x, ev->win_y);

			// We have drawn something, so now the canvas is dirty
			dirty=1;

			// Mouse no longer down
			mdflag=0;
		}
	}
*/
	const Message msg(BFCGUI_MSG_MOUSEUP,(void*)(ev->win_y << 16 | ev->win_x));
	if (OnMessage(msg) == BFCGUIDEFS_MESSAGE_PROCESSED)
		return BFCGUIDEFS_MESSAGE_PROCESSED;
	return HandleMessage();
}

long CFoxBFCWindow::onFxMouseEnter(FXObject*p_sender,FXSelector fxsel,void* ptr)
{
	RecordMessage(p_sender, fxsel, ptr);
	FXEvent *ev=(FXEvent*) ptr;
	const Message msg(BFCGUI_MSG_MOUSEENTER,(void*)(ev->win_y << 16 | ev->win_x));
	if (OnMessage(msg) == BFCGUIDEFS_MESSAGE_PROCESSED)
		return BFCGUIDEFS_MESSAGE_PROCESSED;
	return HandleMessage();
}

long CFoxBFCWindow::onFxMouseLeave(FXObject*p_sender,FXSelector fxsel,void* ptr)
{
	RecordMessage(p_sender, fxsel, ptr);
	FXEvent *ev=(FXEvent*) ptr;
	const Message msg(BFCGUI_MSG_MOUSELEAVE,(void*)(ev->win_y << 16 | ev->win_x));
	if (OnMessage(msg) == BFCGUIDEFS_MESSAGE_PROCESSED)
		return BFCGUIDEFS_MESSAGE_PROCESSED;
	return HandleMessage();
}


// Paint the canvas
long CFoxBFCWindow::onFxPaint(FXObject*p_sender,FXSelector fxsel,void* ptr)
{
	RecordMessage(p_sender, fxsel, ptr);
	FXEvent *ev=(FXEvent*)ptr;
	Rect2dU	rect2d(ev->rect.x,ev->rect.y,ev->rect.w,ev->rect.h);

	Message msg(BFCGUI_MSG_REDRAW,&rect2d);
	if (OnMessage(msg) == BFCGUIDEFS_MESSAGE_NOT_PROCESSED)
		HandleMessage();
	return 1;
}


// Handle the clear message
long CFoxBFCWindow::onFxCmdClear(FXObject*p_sender,FXSelector fxsel,void*ptr)
{
	RecordMessage(p_sender, fxsel, ptr);
/*
	if (m_p_GLViewer)
	{
		FXDCWindow dc(m_p_GLViewer);
		dc.setForeground(m_p_GLViewer->getBackColor());
		dc.fillRectangle(0,0,m_p_GLViewer->getWidth(),m_p_GLViewer->getHeight());
		dirty=0;
	}
*/
  return 1;
}


// Update the clear button:- each gui element (widget) in FOX
// receives a message during idle processing asking it to be updated.
// For example, buttons can be sensitized or desensitized when the
// state of the application changes.
// In this case, we desensitize the sender (the clear button) when
// the canvas has already been cleared, and sensitize it when it has
// been painted (as indicated by the dirty flag).
long CFoxBFCWindow::onFxUpdClear(FXObject* p_sender,FXSelector fxsel,void*ptr)
{
	RecordMessage(p_sender, fxsel, ptr);
  if(dirty)
	p_sender->handle(this->GetAsFox(),FXSEL(SEL_COMMAND,FXWindow::ID_ENABLE),NULL);
  else
	p_sender->handle(this->GetAsFox(),FXSEL(SEL_COMMAND,FXWindow::ID_DISABLE),NULL);

  return 1;
}

long CFoxBFCWindow::onFxFocusIn(FXObject*p_sender, FXSelector fxsel, void* ptr)
{
	RecordMessage(p_sender, fxsel, ptr);
	const Message msg(BFCGUI_MSG_FOCUSIN, ptr);
	long lRval=OnMessage(msg);
	if (lRval == BFCGUIDEFS_MESSAGE_NOT_PROCESSED)
		return HandleMessage();
	return lRval;
}

long CFoxBFCWindow::onFxFocusOut(FXObject*p_sender, FXSelector fxsel, void* ptr)
{
	RecordMessage(p_sender, fxsel, ptr);
	const Message msg(BFCGUI_MSG_FOCUSOUT, ptr);
	long lRval=OnMessage(msg);
	if (lRval == BFCGUIDEFS_MESSAGE_NOT_PROCESSED)
		return HandleMessage();
	return lRval;
}

long CFoxBFCWindow::onFxDestroy(FXObject*p_sender, FXSelector fxsel, void* ptr)
{
	RecordMessage(p_sender, fxsel, ptr);
	const Message msg(BFCGUI_MSG_DESTROY, ptr);
	long lRval=OnMessage(msg);
	if (lRval == BFCGUIDEFS_MESSAGE_NOT_PROCESSED)
		return HandleAsBase(p_sender, fxsel, ptr);
	return lRval;
}

long CFoxBFCWindow::onFxButtonPress(FXObject*p_sender, FXSelector fxsel, void* ptr)
{
	RecordMessage(p_sender, fxsel, ptr);
	Resource_ID	rID=(fxsel&0xffff);
	const Message msg(BFCGUI_MSG_BUTTONPRESS, (void*)rID);
	return OnMessage(msg);
}

int CFoxBFCWindow::OnMessage (const Message &msg)
{
	if (!m_p_Layer)
		return BFCGUIDEFS_MESSAGE_NOT_PROCESSED;
	return m_p_Layer->OnMessage(msg);
}

void CFoxBFCWindow :: FxReplaceText(const UINT pos,const UINT dlength,character *s,const UINT slength)
{
	if (m_eWndType==WND_CURSES)
	{
		STRING csText(s);
//		FXchar	*pad = csText.MakeAsciiBuffer();
		FXchar	*pad = new FXchar[slength+4];
		SBFC_Character::UTF16toUF8 (s, pad);
		((CFoxTextWindow*)this)->replaceText(pos,dlength,pad,slength);
		delete[] pad;
	}
}

void CFoxBFCWindow :: FxAppendText(const CBfc::STRING &cs)
{
	if (m_eWndType==WND_CURSES)
	{
		FXint	length = cs.GetLength();
//		FXchar	*pad = cs.MakeAsciiBuffer();
		FXchar	*pad = new FXchar[length+4];
		SBFC_Character::UTF16toUF8 (cs.GetPtr(), pad);
		((CFoxTextWindow*)this)->appendText(pad, length);
		delete[] pad;
	}
}

void CFoxBFCWindow :: FxSetEditable(const bool bEditable)
{
	switch (m_eWndType)
	{
		case WND_CURSES:
			((CFoxTextWindow*)this)->setEditable(bEditable);
			break;
		case WND_TEXTBOX:
			((CFoxTextboxWindow*)this)->setEditable(bEditable);
			break;
		case WND_COMBO:
			((CFoxComboWindow*)this)->setEditable(bEditable);
			break;
	}
}

void CFoxBFCWindow :: FxSetTitle(const CBfc::STRING &cs)
{
	STRING	csa(cs);
	switch (m_eWndType)
	{
		case WND_MAIN:
			((CFoxMainWindow*)this)->setTitle(csa.MakeAsciiBuffer());
			break;
		case WND_TOP:
			((CFoxTopWindow*)this)->setTitle(csa.MakeAsciiBuffer());
			break;
		case WND_DIALOG:
			((CFoxDialogWindow*)this)->setTitle(csa.MakeAsciiBuffer());
			break;
		case WND_CURSES:
//			((CFoxTextWindow*)this)->setTitle(csa.MakeAsciiBuffer());
			break;
	}
}

CBfc::Size2dU CFoxBFCWindow :: FxGetSizeOnScreen(const CBfc::STRING &cs) const
{
	Size2dU sz(16,16);
	switch (m_eWndType)
	{
		case WND_CURSES:
			((CFoxTextWindow*)this)->GetTextSizeOnScreen(sz,cs);
			break;
	}
	return sz;
}

//FXint buffer_length= m_p_Text->getLength();
void CFoxBFCWindow :: FxSetText(const CBfc::STRING &cs)
{
	switch (m_eWndType)
	{
		case WND_CURSES:
			((CFoxTextWindow*)this)->SetText(cs);
			break;
		case WND_LABEL:
			((CFoxLabelWindow*)this)->SetText(cs);
			break;
		case WND_BUTTON:
			((CFoxButtonWindow*)this)->SetText(cs);
			break;
		case WND_TEXTBOX:
			((CFoxTextboxWindow*)this)->SetText(cs);
			break;
/*
		case WND_LIST:
			((CFoxListWindow*)this)->SetText(cs);
			break;
		case WND_LISTBOX:
			((CFoxListboxWindow*)this)->SetText(cs);
			break;
*/
		case WND_COMBO:
			((CFoxComboWindow*)this)->SetText(cs);
			break;
	}
}

UINT CFoxBFCWindow :: FxGetText(CBfc::STRING &cs)
{
	switch (m_eWndType)
	{
		case WND_CURSES:
			{
				int	len = ((CFoxTextWindow*)this)->getLength();
				FXchar	*pad = new FXchar[len+16];
				((CFoxTextWindow*)this)->getText(pad,len);
				pad[len]=0;
		//		SBFC_Character::UTF8toUF16 (pad, s);
				cs=pad;
				delete pad;
				return len;
			}
		case WND_TEXTBOX:
			{
				cs = ((CFoxTextboxWindow*)this)->getText().text();
		//		SBFC_Character::UTF8toUF16 (pad, s);
				return cs.GetLength();
			}
		case WND_LIST:
		{
			 FXint  index = ((CFoxListWindow*)this)->getCurrentItem();
			 if (index >= 0)
			 {
				FXString	fxs = ((CFoxListWindow*)this)->getItemText(index);
				cs = fxs.text();
				return cs.GetLength();
			 }
		}
			break;
		case WND_LISTBOX:
//			cs = ((CFoxListboxWindow*)this)->getText().text();
			break;
		case WND_COMBO:
			{
				cs = ((CFoxComboWindow*)this)->getText().text();
			}
	}
	return 0;
}

UINT CFoxBFCWindow :: FxGetIndex()
{
	switch (m_eWndType)
	{
		case WND_COMBO:
			return ((CFoxComboWindow*)this)->getCurrentItem();
	}
	return 0;
}

void CFoxBFCWindow :: FxSelectAll()
{
	if (m_eWndType==WND_CURSES)
		((CFoxTextWindow*)this)->SelectAll();
}

bool CFoxBFCWindow :: FxSetFont(character *p_fontSpec)
{
	if (m_eWndType==WND_CURSES)
	{
		FXint	length = SBFC_Character::StringLength(p_fontSpec);
		FXchar	*pad = new FXchar[length+16];
		SBFC_Character::UTF16toUF8 (p_fontSpec, pad);

		FXString fontspec(pad);
		if(!fontspec.empty())
		{
// 			((CFoxTextWindow*)this)->getFont()->getFontDesc(fontdesc);

			FXFontDesc fontdesc;
			((CFoxTextWindow*)this)->getFont()->getFontDesc(fontdesc);

			FXFont *p_Font=new FXFont(m_p_FoxApplication,fontspec);
//    font=new FXFont(getApp(),fontdesc);
			p_Font->create();
			((CFoxTextWindow*)this)->setFont(p_Font);

			if (p_Font)
			{
				((CFoxTextWindow*)this)->setFont(p_Font);
				BFC_RELEASE_PTR (m_p_Font);
				m_p_Font = p_Font;
			}
		}
		delete pad;
	}
	return true;
}

bool CFoxBFCWindow :: SizeTextbox(const Size2dU &size)
{
	switch (m_eWndType)
	{
		case WND_CURSES:
			return ((CFoxTextWindow*)this)->SizeTextbox(size);
		case WND_TEXTBOX:
			((CFoxTextboxWindow*)this)->setNumColumns(size.GetX());
			return true;
/*
		case WND_LIST:
//			((CFoxListWindow*)this)->setNumColumns(size.GetX().GetValue_UINT());
			((CFoxListWindow*)this)->SetNumVisible(size.GetY().GetValue_UINT());
			((CFoxListWindow*)this)->SetNumCols(size.GetX().GetValue_UINT());
			return true;
*/
		case WND_COMBO:
			return ((CFoxComboWindow*)this)->SizeTextbox(size);
	}
	return false;
}

Position2dU CFoxBFCWindow :: getXYOfPos(const Position2dU &pos)
{
	if (m_eWndType==WND_CURSES)
		return ((CFoxTextWindow*)this)->getXYOfPos(pos);
//	else if (m_eWndType==WND_TEXTBOX)
	return pos;
}

void CFoxBFCWindow::SwitchSwitcher(const UINT nPane)
{
	FXint	pane=nPane; // FXSwitcher::ID_OPEN_FIRST + nPane;
	m_p_switcher->handle(GetAsFox(), FXSEL(SEL_COMMAND,FXSwitcher::ID_SETINTVALUE),(void*)&pane);
}

}

#endif	// ifdef USING_QUICKGUI


