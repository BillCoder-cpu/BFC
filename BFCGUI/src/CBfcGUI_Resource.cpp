//*/
/*
					CBfcGUI_Resource.cpp : 
	
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
#include "CFoxBFCWindow.h"

using namespace CBfc;
using namespace CBfcImage;

namespace CBfcGUI {

Resource_Control::Resource_Control (GUI *p_GUI, Window *p_Parent,const CBfc_String &csText,const Resource_ID resourceID, const EBFC_GUI_WINDOW_TYPE eType)
	: Window (p_GUI, csText, eType, p_Parent, resourceID)
	, m_s_Text(csText)
	, m_pResourceEntity(NULL)
{
}

void Resource_Control::UpdateHandlers(ResourceEntity *pResEntity)
{
	if (pResEntity->HasHandlers())
		m_pResourceEntity=pResEntity;
}

int Resource_Control::OnMouseEnter ()
{
	// tell the switcher to switch
	ProcessHandlers(BFC_GUIRES_HANDLER_KEY_MOUSEENTER);
	return BFCGUIDEFS_MESSAGE_NOT_PROCESSED;
}

int Resource_Control::OnMouseLeave ()
{
	ProcessHandlers(BFC_GUIRES_HANDLER_KEY_MOUSELEAVE);
	return BFCGUIDEFS_MESSAGE_NOT_PROCESSED;
}

int Resource_Control::OnMouseDown (const CBfc::Point2dU &pt)
{
	// tell the switcher to switch
	ProcessHandlers(BFC_GUIRES_HANDLER_KEY_LEFTCLICK);
	return BFCGUIDEFS_MESSAGE_NOT_PROCESSED;
}

void Resource_Control::ProcessHandlers(const EBFC_GUIRES_HANDLER_KEY eHandlerKey)
{
	if (m_pResourceEntity)
	{
		CBfc::Array<ResourceHandler> *pHandlerList=m_pResourceEntity->GetHandlerList();

		ULONG	uli=pHandlerList->StartIteration();
		while(ResourceHandler *pHan=pHandlerList->GetNext(uli))
		{
			if (pHan->GetHandlerKey()==eHandlerKey)
				ProcessEvent(*pHan);
		}
	}
}
void Resource_Control::ProcessEvent(ResourceEvent &rEV)
{
	switch (rEV.GetEvent())
	{
		case ResourceEvent::BFC_GUIRES_EVENT_SWITCH:
			GetFoxWindow()->SwitchSwitcher(rEV.GetParameter());
			break;
		case ResourceEvent::BFC_GUIRES_EVENT_ENDMODAL:
			break;
	}
}

void OVERRIDE Resource_Control::SetText(const STRING &csText)
{
	m_s_Text=csText;
//		m_pResourceEntity->
	LayerSetText(m_s_Text);
}

const STRING Resource_Control::GetText() 
{
	LayerGetText(m_s_Text);
	return m_s_Text;
}

void Resource_Control::GetText(CBfc::STRING &csText) 
{
	LayerGetText(m_s_Text);
	csText = m_s_Text;
}


Label::Label (GUI *p_GUI, Window *p_Parent,const CBfc_String &csText,const Resource_ID resourceID)
	: Resource_Control (p_GUI, p_Parent,csText, resourceID, WND_LABEL)
{
}

Button::Button (GUI *p_GUI, Window *p_Parent,const CBfc_String &csText,const Resource_ID resourceID)
	: Resource_Control (p_GUI, p_Parent,csText, resourceID, WND_BUTTON)
	, m_bCheckbox(false)
	, m_bRadio(false)
	, m_bChecked(false)
	, m_pBitmap(NULL)
{
}

Button::~Button()
{
	BFC_RELEASE(m_pBitmap);
}

bool Button::LoadBitmap(const CBfc::Filename &file)
{
	Filename	fullfile(file), respath;
	
	GetGUI()->GetAppPtr()->GetResourceFolder(respath);
	fullfile.PrependPath(respath);
	Stream	s(fullfile);
	if (s.IsAttached())
	{
		Image			img(s);
		Image_Buffer	*pbuf;
		
		const CBfcImage::Image_Segment *p_segment=NULL;
		pbuf = img.GetBuffer(p_segment);
#if 1
		BFC_RELEASE(m_pBitmap);
		m_pBitmap = pbuf->GetBitmap();
		if (m_pBitmap)
		{
			Size2dU size;
			m_pBitmap->GetSize(size);
			SetWindowSize(size);
		}
		((CFoxButtonWindow*)GetFoxWindow())->MakeToolbar();
#else
		Bitmap *pBmp = pbuf->GetBitmap();
		((CFoxButtonWindow*)GetFoxWindow())->MakeToolbar();
		((CFoxButtonWindow*)GetFoxWindow())->SetIcon(pBmp);
		BFC_RELEASE (pBmp);
		BFC_RELEASE (pbuf);
#endif
		return true;
	}
	return false;
}

void Button::SetChecked(const bool bChecked)
{
	m_bChecked=bChecked;
}

bool Button::GetChecked() const
{
	return m_bChecked;
}

void Button::MakeCheckbox()
{
	m_bCheckbox=true;
	((CFoxButtonWindow*)GetFoxWindow())->setPadLeft(16);
}

void Button::MakeRadio()
{
	m_bRadio=true;
	((CFoxButtonWindow*)GetFoxWindow())->setPadLeft(16);
}

CBfc::STRING Button::GetGroup() const
{
	return m_csGroup;
}

void Button::SetGroup(const CBfc::STRING &cs)
{
	m_csGroup=cs;
}

int OVERRIDE Button::OnMouseDown (const CBfc::Point2dU &pt)
{
	if (m_bRadio)
	{
		// Uncheck the other radio buttons in the same group.
		DialogWindow	*pParent=(DialogWindow*)GetParent();
		CBfc::ArrayPtr	*rcList = pParent->GetResourceControlList();

		ULONG	uli=rcList->StartIteration();
		BYTEPTR	*p_ptr;

		while (p_ptr=rcList->GetNext(uli))
		{
			Resource_Control	*pRC=(Resource_Control*)*p_ptr;
			if (pRC->GetWindowType()==WND_BUTTON)
			{
				Button	*pBut=(Button*)pRC;
				if (pBut->GetGroup()==GetGroup())
				{
					pBut->SetChecked(false);
					pBut->Dirty();
				}
			}
		}
		SetChecked(true);

	} else if (m_bCheckbox)
		m_bChecked ^= 1;
	return Resource_Control::OnMouseDown(pt);
}

int	OVERRIDE Button::OnPaint(const Rect2dU &rect2d)
{
	CFoxBFCWindow *pFoxWnd=GetFoxWindow();

	pFoxWnd->HandleMessage();		// Call base
	// Now overwrite
	if (m_pBitmap)
	{
		const Position2dU origin(0,0);
		DrawBitmap (m_pBitmap, rect2d, origin, 1.0);
	}
	if (m_bRadio)
	{
		if (CreateDCw(rect2d))
		{
			SetColor(CBfcImage::Color::WHITE);
			DrawEllipse(Rect2dU(4,4,10,10));
			if (m_bChecked)
				FillEllipse(Rect2dU(6,6,7,7));
			ReleaseDC();
		}
	} else if (m_bCheckbox)
	{
		if (CreateDCw(rect2d))
		{
			SetColor(CBfcImage::Color::WHITE);
			DrawRectangle(Rect2dU(4,4,11,11));
			if (m_bChecked)
			{
				DrawLine(Position2dU(6,9),Position2dU(10,13));
				DrawLine(Position2dU(9,13),Position2dU(13,5));
			}
			ReleaseDC();
		}
	}
	return BFCGUIDEFS_MESSAGE_PROCESSED;
}


TextBox::TextBox (GUI *p_GUI, Window *p_Parent,const CBfc_String &csText,const Resource_ID resourceID)
	: Data_Resource_Control (p_GUI, p_Parent, csText, resourceID, WND_TEXTBOX)
{
}

void TextBox::SetAttribute(const EBFC_GUIRES_ATTRIBUTE_KEY attribute)
{
	CFoxTextboxWindow *pFoxWnd=(CFoxTextboxWindow*)GetFoxWindow();
	switch (attribute)
	{
		case BFC_GUIRES_ATTRIBUTE_KEY_NUMERIC:
			pFoxWnd-> RestrainNumeric();
			break;
		case BFC_GUIRES_ATTRIBUTE_KEY_INTEGER:
			pFoxWnd-> RestrainInteger();
			break;
		case BFC_GUIRES_ATTRIBUTE_KEY_PASSWORD:
			pFoxWnd-> RestrainPassword();
			break;
		case BFC_GUIRES_ATTRIBUTE_KEY_DISTANCE:
			pFoxWnd-> RestrainDistance();
			break;
	}
}

CursesBox::CursesBox (GUI *p_GUI, Window *p_Parent,const CBfc_String &csText,const Resource_ID resourceID)
	: Data_Resource_Control (p_GUI, p_Parent, csText, resourceID, WND_CURSES)
{
}

//int CursesBox:: (*IsEnabled)()			// button calls this to see if should display or react
			
Data_Resource_Control::Data_Resource_Control (GUI *p_GUI, Window *p_Parent,const CBfc_String &csText,
						const Resource_ID resourceID,const EBFC_GUI_WINDOW_TYPE eType)
: Resource_Control(p_GUI,p_Parent,csText,resourceID,eType)
{
}

const double Data_Resource_Control::GetValue() 
{
	Value	value;

	value.SetFromString (GetText());
	return value.GetValue_double();
}

const UINT Data_Resource_Control::GetValue_UINT() 
{
	Value	value;

	value.SetFromString (GetText());
	return value.GetValue_UINT();
}

UINT Data_Resource_Control::GetIndex() const
{
	return LayerGetIndex();
}


ListRC::ListRC (GUI *p_GUI,Window *p_Parent,const Resource_ID resourceID)
	: Data_Resource_Control (p_GUI, p_Parent, "", resourceID, WND_LIST)
{
}

/*
OVERRIDE int ListRC::OnMouseDown (const CBfc::Point2dU &pt)
{
	
}
*/

void ListRC::Empty()
{
	((CFoxListWindow*)GetFoxWindow())->clearItems();
}

void ListRC::AppendItem(const CBfc::STRING &csItem)
{
	char	pad[512];
	SBFC_Character::UTF16toUF8 (csItem.GetPtr(), pad);
	((CFoxListWindow*)GetFoxWindow())->appendItem(pad);
}

OVERRIDE void ListRC::SetText(const CBfc::STRING &csText)
{
	Empty();
	STRING	csNext;
	UINT	u_Start=0;
	while (u_Start=csText.ParseLines(u_Start,csNext))
		AppendItem(csNext);
}

void ListRC::SetNumVisible(const int n)
{
	((CFoxListWindow*)GetFoxWindow())->setNumVisible(n);
//	((CFoxListWindow*)GetFoxWindow())->layout();
}

void ListRC::SetNumCols(const int n)
{
	((CFoxListWindow*)GetFoxWindow())->resize(n*8, 160);
}


ListBox::ListBox (GUI *p_GUI,Window *p_Parent,const Resource_ID resourceID)
	: Data_Resource_Control (p_GUI, p_Parent, "", resourceID, WND_LISTBOX)
{
}

void ListBox::Empty()
{
	((CFoxListboxWindow*)GetFoxWindow())->clearItems();
}

OVERRIDE void ListBox::SetText(const CBfc::STRING &csText)
{
// 	Data_Resource_Control::SetText(csText);
	Empty();
	STRING	csNext;
	UINT	u_Start=0;
	while (u_Start=csText.ParseLines(u_Start,csNext))
		AppendItem(csNext);
}

void ListBox::SetNumVisible(const int n)
{
	((CFoxListboxWindow*)GetFoxWindow())->setNumVisible(n);
}

void ListBox::AppendItem(const CBfc::STRING &csItem)
{
	char	pad[512];
	SBFC_Character::UTF16toUF8 (csItem.GetPtr(), pad);
	((CFoxListboxWindow*)GetFoxWindow())->appendItem(pad);
}


ComboBox::ComboBox (GUI *p_GUI,Window *p_Parent,const UINT nCols,const Resource_ID resourceID)
	: Data_Resource_Control (p_GUI, p_Parent, "", resourceID, WND_COMBO)
{
	((CFoxComboWindow*)GetFoxWindow())->setNumColumns(nCols);
}

OVERRIDE void ComboBox::SetText(const CBfc::STRING &csText)
{
	Empty();
	STRING	csNext;
	UINT	u_Start=0;
	while (u_Start=csText.ParseLines(u_Start,csNext))
		AppendItem(csNext);
}

void ComboBox::Empty()
{
	((CFoxComboWindow*)GetFoxWindow())->clearItems();
}

void ComboBox::AppendItem(const CBfc::STRING &csItem)
{
	char	pad[512];
	SBFC_Character::UTF16toUF8 (csItem.GetPtr(), pad);
	((CFoxComboWindow*)GetFoxWindow())->appendItem(pad);
}



}

