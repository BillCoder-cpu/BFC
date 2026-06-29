//*/
/*
					CFoxBFCWindow.h : 
	
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

//#define FOXDLL

//#ifdef BFC_GUI_DLL
//#	define FOXDLL_EXPORTS
//#endif

#ifdef UNIX
#	undef WIN32
#endif

#include <fx.h>
#include <fx3d.h>
#include <fxkeys.h>

#ifdef WIN32
// Stupid, stupid hog windows #defines this stuff
#	undef CreateDC
#	undef ReplaceText
#	undef LoadBitmap
#endif

namespace CBfcGUI
{
//
//  Goal:
//   Layer to Derive all of BFC_GUI messages from the Fox toolkit (single machine environment).
//      Also be able to easily switch models and Derive all of BFCGui messages from Java (multi machine environment)
//
//

BFC_GUI_CLASS	UILayerWindow;

BFC_GUI_CLASS CFoxBFCWindow
{                                // Macro for class hierarchy declarations
	friend class UILayerWindow;
	friend class GetlineWindow;

//	FXDECLARE(CFoxBFCWindow)
public:
  // CFoxBFCWindow's constructor
	CFoxBFCWindow(const EBFC_GUI_WINDOW_TYPE eType, FXApp *p_App, UILayerWindow* p_Layer);
	virtual ~CFoxBFCWindow();
  // Initialize
	virtual void Resize(FXint w,FXint h);

  // Messages for our class
  enum{
    ID_CANVAS=FXMainWindow::ID_LAST,
    ID_CLEAR,
    ID_LAST
    };

	virtual long HandleAsBase(FXObject*p_sender,FXSelector fxsel,void* ptr)=0;
	long	HandleMessage();	// process as base

	int		DoModal();

	void	SwitchSwitcher(const UINT nPane);
	bool	CreateDC(const Rect2dU &rect2d);
	void	ReleaseDC();
	void	SetColor(const UINT color);
	void	DrawRectangle(const CBfc::Rect2dU &rect2d);
	void	FillRectangle(const CBfc::Rect2dU &rect2d);
	CBfc::Position2dU	getXYOfPos(const CBfc::Position2dU &pos);
	FXComposite *GetAsFoxContainer() const;
	virtual FXWindow *GetAsFox() const =0;
protected:
	CFoxBFCWindow()  {}
protected:
	
	bool	SizeTextbox(const CBfc::Size2dU &size);
	int		OnMessage (const Message &msg);
	void	FxSetTitle(const CBfc::STRING &cs);
	void	FxSetText(const CBfc::STRING &cs);
	void	FxAppendText(const CBfc::STRING &cs);
	void	FxReplaceText(const UINT pos,const UINT dlength,character *s,const UINT slength);
	bool	FxSetFont(character *p_fontSpec);
	UINT	FxGetText(CBfc::STRING &cs);
	void	FxSetEditable(const bool bEditable);
	UINT	FxGetIndex();
	void	FxSelectAll();
	
	CBfc::Size2dU	FxGetSizeOnScreen(const CBfc::STRING &cs) const;
	
	UILayerWindow		*GetLayer() const { return m_p_Layer; }
	FXDCWindow			*GetDC() const { return m_p_dc; }
private:
	void				RecordMessage(FXObject*p_sender,FXSelector fxsel,void* ptr);
	FXObject			*m_msg_p_sender;
	FXSelector	 		m_msg_fxsel;
	void				*m_msg_ptr;

public:				// Message handlers
	long onFxPaint(FXObject*,FXSelector,void*);
	long onFxKeyPress(FXObject*,FXSelector,void* ptr);
	long onFxKeyRelease(FXObject*,FXSelector,void* ptr);
	long onFxMouseDown(FXObject*,FXSelector,void*);
	long onFxMouseUp(FXObject*,FXSelector,void*);
	long onFxMouseMove(FXObject*,FXSelector,void*);
	long onFxMouseEnter(FXObject*,FXSelector,void*);
	long onFxMouseLeave(FXObject*,FXSelector,void*);
	long onFxCmdClear(FXObject*,FXSelector,void*);
	long onFxUpdClear(FXObject*,FXSelector,void*);
	long onFxFocusIn(FXObject*,FXSelector,void*);
	long onFxFocusOut(FXObject*,FXSelector,void*);
	long onFxButtonPress(FXObject*,FXSelector,void*);
	long onFxDestroy(FXObject*,FXSelector,void*);

	FXSwitcher				*GetSwitcher();
protected:
	FXApp					*m_p_FoxApplication;
	FXFont					*m_p_Font;

	FXSwitcher				*m_p_switcher;
//  FXRuler           *hruler;                  // Horizontal ruler
//  FXRuler           *vruler;                  // Vertical ruler
private:
	EBFC_GUI_WINDOW_TYPE	m_eWndType;
	UILayerWindow			*m_p_Layer;
	int						dirty;                   // Canvas has been painted?
	FXDCWindow				*m_p_dc;
};

BFC_GUI_CLASS CFoxTopWindow : public FXTopWindow, public CFoxBFCWindow
{
	FXDECLARE(CFoxTopWindow)
public:
	CFoxTopWindow(FXApp *p_App, const CBfc::STRING &csTitle, UILayerWindow* p_Layer, UILayerWindow* p_Parent);
	virtual FXWindow *GetAsFox() const;
	virtual long HandleAsBase(FXObject*p_sender,FXSelector fxsel,void* ptr);
protected:
	CFoxTopWindow(){}
};

BFC_GUI_CLASS CFoxChildWindow : public CFoxBFCWindow,  public FXComposite
{
	FXDECLARE(CFoxChildWindow)
public:
	CFoxChildWindow(FXApp *p_App, UILayerWindow* p_Layer, UILayerWindow* p_Parent);
	virtual FXWindow *GetAsFox() const;
	virtual long HandleAsBase(FXObject*p_sender,FXSelector fxsel,void* ptr);
protected:
	CFoxChildWindow(){}
};

BFC_GUI_CLASS CFoxMainWindow : public CFoxBFCWindow, public FXMainWindow
{
  FXDECLARE(CFoxMainWindow)
public:
	CFoxMainWindow(FXApp* a,const CBfc::STRING &csTitle, UILayerWindow* p_Layer);
	virtual FXWindow *GetAsFox() const;
	virtual long HandleAsBase(FXObject*p_sender,FXSelector fxsel,void* ptr);
protected:
	CFoxMainWindow(){}
private:
//	FXMenuBar	*m_p_menubar;
};

BFC_GUI_CLASS CFoxDialogWindow : public CFoxBFCWindow, public FXDialogBox
{
	FXDECLARE(CFoxDialogWindow)

public:
	CFoxDialogWindow(FXApp *p_App,const CBfc::STRING &csText, UILayerWindow* p_Layer, UILayerWindow* p_Parent);
	virtual FXWindow *GetAsFox() const;
	virtual long HandleAsBase(FXObject*p_sender,FXSelector fxsel,void* ptr);

	FXComposite *GetFrame() const;
	int Execute() {
		return  execute(PLACEMENT_OWNER);
	}
	void	AddMatrix(const CBfc::Size2dU &size);
	void	AddSwitcher(const Resource_ID rID);
	void	EndFrame();
	void	AddSpacer(UINT nCount);
	void	MakeNormal();
protected:
	CFoxDialogWindow () {}
private:
	void	PushFrame (const FXComposite *p_Frame);
	void	PopFrame ();

	CBfc::ArrayPtr	m_frameArray;
};

BFC_GUI_CLASS CFoxButtonWindow : public CFoxBFCWindow, public FXButton
{
  FXDECLARE(CFoxButtonWindow)
public:
	CFoxButtonWindow(FXApp *p_App,const CBfc::STRING &csText,const Resource_ID resourceID, UILayerWindow* p_Layer, UILayerWindow* p_Parent);
	virtual FXWindow *GetAsFox() const;
	virtual long HandleAsBase(FXObject*p_sender,FXSelector fxsel,void* ptr);

	void MakeToolbar();
	void SetText(const CBfc::STRING &csText);
	void SetIcon(const CBfcImage::Bitmap *pBmp);
protected:
	CFoxButtonWindow(){}
private:
};

BFC_GUI_CLASS CFoxTextWindow : public CFoxBFCWindow, public FXText
{
  FXDECLARE(CFoxTextWindow)
public:
	CFoxTextWindow(FXApp *p_App,const Resource_ID resourceID, UILayerWindow* p_Layer, UILayerWindow* p_Parent);
	virtual FXWindow *GetAsFox() const;
	virtual long HandleAsBase(FXObject*p_sender,FXSelector fxsel,void* ptr);

	void SelectAll();
	bool SizeTextbox(const CBfc::Size2dU &size);
	void SetText(const CBfc::STRING &csText);

	CBfc::Position2dU getXYOfPos(const CBfc::Position2dU &pos) const;
	void GetTextSizeOnScreen(CBfc::Size2dU & size,const STRING &cs) const;
protected:
	CFoxTextWindow(){}
private:
	CBfc::Size2dU	m_size;
};

BFC_GUI_CLASS CFoxTextboxWindow : public CFoxBFCWindow, public FXTextField
{
  FXDECLARE(CFoxTextboxWindow)
public:
	CFoxTextboxWindow(FXApp *p_App,const CBfc::STRING &csText,const Resource_ID resourceID, UILayerWindow* p_Layer, UILayerWindow* p_Parent);
	virtual FXWindow *GetAsFox() const;
	virtual long HandleAsBase(FXObject*p_sender,FXSelector fxsel,void* ptr);

	void SetText(const CBfc::STRING &csText);
	void RestrainNumeric();
	void RestrainInteger();
	void RestrainPassword();
	void RestrainDistance();

protected:
	CFoxTextboxWindow(){}
private:
};


BFC_GUI_CLASS CFoxLabelWindow : public CFoxBFCWindow, public FXLabel
{
  FXDECLARE(CFoxLabelWindow)
public:
	CFoxLabelWindow(FXApp *p_App,const CBfc::STRING &csText,const Resource_ID resourceID, UILayerWindow* p_Layer, UILayerWindow* p_Parent);
	virtual FXWindow *GetAsFox() const;
	virtual long HandleAsBase(FXObject*p_sender,FXSelector fxsel,void* ptr);

	void SetText(const CBfc::STRING &csText);
protected:
	CFoxLabelWindow(){}
private:
};

BFC_GUI_CLASS CFoxListWindow : public CFoxBFCWindow, public FXList
{
  FXDECLARE(CFoxListWindow)
public:
	CFoxListWindow(FXApp *p_App,const Resource_ID resourceID, UILayerWindow* p_Layer, UILayerWindow* p_Parent);
	virtual FXWindow *GetAsFox() const;
	virtual long HandleAsBase(FXObject*p_sender,FXSelector fxsel,void* ptr);

//	void SetText(const CBfc::STRING &csText);
protected:
	CFoxListWindow(){}
private:
};

BFC_GUI_CLASS CFoxListboxWindow : public CFoxBFCWindow, public FXListBox
{
  FXDECLARE(CFoxListboxWindow)
public:
	CFoxListboxWindow(FXApp *p_App,const Resource_ID resourceID, UILayerWindow* p_Layer, UILayerWindow* p_Parent);
	virtual FXWindow *GetAsFox() const;
	virtual long HandleAsBase(FXObject*p_sender,FXSelector fxsel,void* ptr);

//	void SetText(const CBfc::STRING &csText);
protected:
	CFoxListboxWindow(){}
private:
};

BFC_GUI_CLASS CFoxComboWindow : public CFoxBFCWindow, public FXComboBox
{
  FXDECLARE(CFoxComboWindow)
public:
	CFoxComboWindow(FXApp *p_App,const UINT nCols,const Resource_ID resourceID, UILayerWindow* p_Layer, UILayerWindow* p_Parent);
	virtual FXWindow *GetAsFox() const;
	virtual long HandleAsBase(FXObject*p_sender,FXSelector fxsel,void* ptr);

	void SetText(const CBfc::STRING &csText);
protected:
	CFoxComboWindow(){}
private:
};

BFC_GUI_CLASS GUI;
// GL (Graphics Layer) rendering surface.
BFC_GUI_CLASS CFoxGLWindow : public CFoxBFCWindow, public FXGLViewer
{
  FXDECLARE(CFoxGLWindow)
public:
	CFoxGLWindow(GUI *p_GUI,AppLayerPtr p_App,const Resource_ID resourceID, UILayerWindow* p_Layer, UILayerWindow* p_Parent);
	virtual FXWindow *GetAsFox() const;
	virtual long HandleAsBase(FXObject*p_sender,FXSelector fxsel,void* ptr);

protected:
	CFoxGLWindow(){}
private:
};


}


