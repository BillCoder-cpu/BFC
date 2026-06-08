//*/
/*
					CBfcGUI_DialogWindow.cpp : 
	
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

namespace CBfcGUI {

DialogWindow::DialogWindow(GUI *p_GUI, const STRING &ResourceName,  Window *p_Parent, ResourceStore *p_ResourceStore, const EBFC_GUI_WINDOW_TYPE eType)
	: ResourceWindow(p_GUI, ResourceName, eType, p_Parent, p_ResourceStore)
		, m_pDP(NULL)
{
}

DialogWindow::DialogWindow(GUI *p_GUI, character *pMemScript, Window *p_Parent)
	: ResourceWindow(p_GUI, pMemScript, p_Parent)
		, m_pDP(NULL)
{
}

//contents=new FXHorizontalFrame(this,LAYOUT_SIDE_BOTTOM|FRAME_NONE|LAYOUT_FILL_X|PACK_UNIFORM_WIDTH);
bool OVERRIDE DialogWindow::OnCreate()
{
	ResourceContainer *pRC=GetResourceContainer();
	const bool bRval = ResourceWindow::OnCreate();
	if (pRC)
	{
		CreateEntryList(pRC->GetEntityList());
		SetWindowPosition (pRC->GetPosition());
		SetWindowSize(pRC->GetSize());
	}
// 	const bool bRval = ResourceWindow::OnCreate();
	UpdateDS();
	return bRval;
}

///
/// Create all of the sub-windows indicated in the resource store
///
bool DialogWindow::CreateEntryList(CBfc::Array<ResourceEntity> *pResEntityList)
{
	ResourceEntity	*pResEntity;
	bool			b_FrameCreated=false;
	
	AddMatrix(Size2dU(1,0));		// Specify cols/rows and #
	ULONG uIr=pResEntityList->StartIteration();
	while (pResEntity=pResEntityList->GetNext(uIr))
	{
		STRING	csText;
		Resource_Control	*pRC=NULL;
		switch (pResEntity->GetType())
		{
		case BFC_GUIRES_RESOURCE_KEY_BUTTON:
			{
				Button	*pButton;

				pResEntity->GetText(csText);
				
				if (pResEntity->HasAttribute(BFC_GUIRES_ATTRIBUTE_KEY_ICON))
				{
					pButton=new Button(GetGUI(),this,"",pResEntity->GetResourceID());
					pButton->LoadBitmap (csText);
				} else
					pButton=new Button(GetGUI(),this,csText,pResEntity->GetResourceID());

				if (pResEntity->HasAttribute(BFC_GUIRES_ATTRIBUTE_KEY_CHECKBOX))
					pButton->MakeCheckbox();
				if (pResEntity->HasAttribute(BFC_GUIRES_ATTRIBUTE_KEY_RADIO))
				{
					pButton->MakeRadio();
					pButton->SetGroup(pResEntity->GetGroup());
				}
				if (pResEntity->HasAttribute(BFC_GUIRES_ATTRIBUTE_KEY_CHECKED))
					pButton->SetChecked(true);
				pRC=(Resource_Control*)pButton;
			}
			break;
		case BFC_GUIRES_RESOURCE_KEY_LABEL:
			pResEntity->GetText(csText);
			pRC=(Resource_Control*)new Label(GetGUI(),this,csText,pResEntity->GetResourceID());
			break;
		case BFC_GUIRES_RESOURCE_KEY_TEXTBOX:
			{
				TextBox	*pTextbox;
				pResEntity->GetText(csText);
				pTextbox=new TextBox(GetGUI(),this,csText,pResEntity->GetResourceID());
				
				if (pResEntity->HasAttribute(BFC_GUIRES_ATTRIBUTE_KEY_NUMERIC)
					|| pResEntity->HasAttribute(BFC_GUIRES_ATTRIBUTE_KEY_CURRENCY)
					|| pResEntity->HasAttribute(BFC_GUIRES_ATTRIBUTE_KEY_PERCENT))
						pTextbox->SetAttribute(BFC_GUIRES_ATTRIBUTE_KEY_NUMERIC);
					
				if (pResEntity->HasAttribute(BFC_GUIRES_ATTRIBUTE_KEY_INTEGER))
					pTextbox->SetAttribute(BFC_GUIRES_ATTRIBUTE_KEY_INTEGER);
					
				if (pResEntity->HasAttribute(BFC_GUIRES_ATTRIBUTE_KEY_PASSWORD))
					pTextbox->SetAttribute(BFC_GUIRES_ATTRIBUTE_KEY_PASSWORD);

				if (pResEntity->HasAttribute(BFC_GUIRES_ATTRIBUTE_KEY_DISTANCE))
					pTextbox->SetAttribute(BFC_GUIRES_ATTRIBUTE_KEY_DISTANCE);
		
				pRC=(Resource_Control*)pTextbox;
				pRC->SizeTextbox(pResEntity->GetSize());
			}
			break;
		case BFC_GUIRES_RESOURCE_KEY_CURSESBOX:
			{
				CursesBox	*pCursesBox;
				pResEntity->GetText(csText);
				pCursesBox=new CursesBox(GetGUI(),this,csText,pResEntity->GetResourceID());
				
				pRC=(Resource_Control*)pCursesBox;
				pRC->SizeTextbox(pResEntity->GetSize());
			}
			break;
		case BFC_GUIRES_RESOURCE_KEY_LIST:
			{
				ListRC *pListrc = new ListRC(GetGUI(),this,pResEntity->GetResourceID());
				pResEntity->GetText(csText);
				STRING	csNext;
				UINT	u_Start=0;
				while (u_Start=csText.ParseLines(u_Start,csNext))
					pListrc->AppendItem(csNext);
				pListrc->SetNumVisible(pResEntity->GetSize().GetY());
				pListrc->SetNumCols(pResEntity->GetSize().GetX());
//				pListrc->SetSize(pResEntity->GetSize());
				pRC=(Resource_Control*)pListrc;
			}
			break;
		case BFC_GUIRES_RESOURCE_KEY_LISTBOX:
			{
				ListBox *pListbox = new ListBox(GetGUI(),this,pResEntity->GetResourceID());
				pResEntity->GetText(csText);
				STRING	csNext;
				UINT	u_Start=0;
				while (u_Start=csText.ParseLines(u_Start,csNext))
					pListbox->AppendItem(csNext);
				pListbox->SetNumVisible(pResEntity->GetSize().GetY());
				pRC=(Resource_Control*)pListbox;
			}
			break;
		case BFC_GUIRES_RESOURCE_KEY_DROPLIST:
		case BFC_GUIRES_RESOURCE_KEY_COMBOBOX:
			{
				ComboBox *pCombo = new ComboBox(GetGUI(),this,pResEntity->GetSize().GetX(),pResEntity->GetResourceID());
				pResEntity->GetText(csText);
				STRING	csNext;
				UINT	u_Start=0;
				while (u_Start=csText.ParseLines(u_Start,csNext))
					pCombo->AppendItem(csNext);
				pRC=(Resource_Control*)pCombo;
			}
			break;
		case BFC_GUIRES_RESOURCE_KEY_SPACER:
			AddSpacer(pResEntity->GetSize());
			break;
		case BFC_GUIRES_RESOURCE_KEY_MATRIX:
			if (b_FrameCreated)
				EndFrame();
			AddMatrix(pResEntity->GetSize());		// Specify cols/rows and #
			b_FrameCreated = true;
			break;
		case BFC_GUIRES_RESOURCE_KEY_SWITCHER:
			AddSwitcher(pResEntity->GetResourceID());
			AddWindows(pResEntity);
			EndFrame();	// Switcher is filled, stop referencing it for new components
			break;
		case BFC_GUIRES_CONTAINER_KEY_CONTROL:
			AddWindows (pResEntity);
			break;
		case BFC_GUIRES_RESOURCE_KEY_HORIZONTAL_SEPERATOR:
//			new ComboBox(GetGUI(),this,pResEntity->GetSize().GetX().GetValue_UINT(),pResEntity->GetResourceID());
			break;
		case BFC_GUIRES_RESOURCE_KEY_VERTICAL_SEPERATOR:
			break;
		}
		if (pRC)
		{
			AddResourceControl(pRC);
			pRC->UpdateHandlers(pResEntity);
			if (pResEntity->HasAttribute(BFC_GUIRES_ATTRIBUTE_KEY_DEFAULT))
				pRC->SetWindowDefault();
		}
	}
	if (b_FrameCreated)
		EndFrame();
	EndFrame();
	return true;
}

// loop through each window in the switcher's window list (text field)
bool DialogWindow::AddWindows(const ResourceEntity *pResEntity)
{
	STRING	csNext, csText;

	pResEntity->GetText(csText);
	UINT	u_Start=0;
	while (u_Start=csText.ParseLines(u_Start,csNext))
		if (!AddWindow (csNext))
			return false;
	return true;
}

bool DialogWindow::AddWindow (const STRING &csNext)
{
	const Resource_ID rID=GetResourceStore()->LookupResourceID(csNext);
	if (rID)
	{
		ResourceContainer *pRContainer=GetResourceStore()->LookupResourceContainer(rID);
		if (pRContainer)
			CreateEntryList(pRContainer->GetEntityList());
		return true;
	}
	return false;
}

void DialogWindow::AddMatrix(const Size2dU &size)
{
	CFoxDialogWindow*	p_foxWnd=(CFoxDialogWindow*)GetFoxWindow();
	p_foxWnd->AddMatrix(size);
}

void DialogWindow::AddSwitcher(const Resource_ID rID)
{
	CFoxDialogWindow*	p_foxWnd=(CFoxDialogWindow*)GetFoxWindow();
	p_foxWnd->AddSwitcher(rID);
}

void DialogWindow::AddSpacer(const CBfc::Size2dU &size)
{
	CFoxDialogWindow*	p_foxWnd=(CFoxDialogWindow*)GetFoxWindow();
	p_foxWnd->AddSpacer(size.GetX());
}

void DialogWindow::EndFrame()
{
	CFoxDialogWindow*	p_foxWnd=(CFoxDialogWindow*)GetFoxWindow();
	p_foxWnd->EndFrame();
}

int OVERRIDE DialogWindow::OnDestroy()
{
	m_ResourceControl_List.Empty();
	return Window::OnDestroy();
}

// Like UpdateData() - will update all of the fields.
void DialogWindow::UpdateDX()
{
	ULONG	uli=m_ResourceControl_List.StartIteration();
	BYTEPTR	*p_ptr;

	while (p_ptr=m_ResourceControl_List.GetNext(uli))
	{
		Resource_Control	*pRC=(Resource_Control*)*p_ptr;
		switch (pRC->GetWindowType())
		{
			case WND_TEXTBOX:
			case WND_COMBO:
			case WND_LIST:
			case WND_LISTBOX:
				UpdateDX((Data_Resource_Control*)pRC);
				break;
			case WND_BUTTON:
				UpdateDX((Button*)pRC);
				break;
		}
	}
}

// Like UpdateData() - will update all of the fields.
void DialogWindow::UpdateDS(void)
{
	ULONG	uli=m_ResourceControl_List.StartIteration();
	BYTEPTR	*p_ptr;

	while (p_ptr=m_ResourceControl_List.GetNext(uli))
	{
		Resource_Control	*pRC=(Resource_Control*)*p_ptr;
		switch (pRC->GetWindowType())
		{
			case WND_TEXTBOX:
			case WND_COMBO:
			case WND_LABEL:
			case WND_LIST:
			case WND_LISTBOX:
			case WND_BUTTON:
				UpdateDS(pRC);
				break;
		}
	}
}

void OVERRIDE DialogWindow::UpdateDX(Data_Resource_Control *pRc)
{
	STRING	csName;
	if (GetResourceStore()->LookupResourceName(csName, pRc->GetResourceID(), 0))
	{
		const bool	bSet = true;
		STRING	csText(pRc->GetText());
		GetDX()->GetSetText(csName, csText, bSet);
	}
}

void OVERRIDE DialogWindow::UpdateDX(Button *pRc)
{
	STRING	csName;
	if (GetResourceStore()->LookupResourceName(csName, pRc->GetResourceID(), 0))
	{
		const bool	bSet = true;
		bool		bCheck = pRc->GetChecked();
		GetDX()->GetSetCheck (csName, bCheck, bSet);
	}
}

void OVERRIDE DialogWindow::UpdateDS(Resource_Control *pRc)
{
	STRING	csName;
	const bool	bSet = false;
	const DX	*pDX;
	
	if ((pDX = GetDX()))
	  if (GetResourceStore()->LookupResourceName(csName, pRc->GetResourceID(), 0))
		switch (pRc->GetWindowType())
		{
			case WND_TEXTBOX:
			case WND_COMBO:
//			case WND_LABEL:
			case WND_LIST:
			case WND_LISTBOX:
			{
// 				STRING	csText(pRc->GetText());
				STRING	csText;
				if (pDX->GetSetText(csName, csText, bSet))
					pRc->SetText(csText);
				break;
			}
			case WND_BUTTON:
			{
// 				bool	bCheck = ((Button*)pRc)->GetChecked();
				bool	bCheck;
				pDX->GetSetCheck (csName, bCheck, bSet);
				((Button*)pRc)->SetChecked(bCheck);
				break;
			}
		}
}

bool OVERRIDE DialogWindow::ButtonPress (const Resource_ID rID, Resource_Control *pRc)
{
	if (!GetDP())
		return false;
	return GetDP()->ProcessInput(pRc, this);
}

int OVERRIDE DialogWindow::OnMessage(const Message &msg)
{
	switch (msg.GetID())
	{
		case BFCGUI_MSG_BUTTONPRESS:
			{
				const Resource_ID		rID = (Resource_ID)msg.GetParameter();
				Resource_Control *pRC=Lookup_Resource_Control(rID);
				if (pRC)
				{
					switch (pRC->GetWindowType())
					{
						case WND_TEXTBOX:
						case WND_COMBO:
						case WND_LIST:
						case WND_LISTBOX:
//						case WND_CURSES:
							UpdateDX((Data_Resource_Control*)pRC);
							break;
						case WND_BUTTON:
							if (!ButtonPress (rID,pRC))
								EndModal(rID);
							break;
					}
				}
			}
			return BFCGUIDEFS_MESSAGE_PROCESSED;
	}
	return Window::OnMessage(msg);
}

void DialogWindow::AddResourceControl(const Resource_Control *pRc)
{
	BYTEPTR	ptr=(BYTEPTR)pRc;
	m_ResourceControl_List.Add(&ptr);
}


/**
 *   Looks up any resource entity related to this dialog
 * @param csName 
 * @return 
 */
ResourceEntity *DialogWindow::LookupResourceEntity(const CBfc::STRING &csName) 
{
	return GetResourceStore()->LookupResourceEntity(csName, GetResourceID());
}

/**
 *  Looks up the control information related to a child resource entity of this dialog that is a control.
 * @param csName 
 * @return 
 */
Resource_Control *DialogWindow::Lookup_Resource_Control(const CBfc::STRING &csName) 
{
	ResourceEntity *p_RE = LookupResourceEntity(csName);
	if (!p_RE) return NULL;
	return Lookup_Resource_Control(p_RE->GetResourceID());
}


Resource_Control *DialogWindow::Lookup_Resource_Control(const Resource_ID rID) 
{
	ULONG	uli=m_ResourceControl_List.StartIteration();
	BYTEPTR	*p_ptr;

	while (p_ptr=m_ResourceControl_List.GetNext(uli))
	{
		Resource_Control	*pRC=(Resource_Control*)*p_ptr;
		if (pRC->GetResourceID()==rID)
			return pRC;
	}
	return NULL;
}

bool DialogWindow::SetUI_Text (const STRING &csResourceName, const STRING &csText)
{
	Resource_Control 	*pRC = Lookup_Resource_Control(csResourceName);
	if (pRC)
	{
		pRC->SetText(csText);
//  void update(FXint x,FXint y,FXint w,FXint h) const;
//  void update() const;
		return true;
	}
	return false;
}

/**
 * 
 * @param csResourceName 
 * @param csText 
 * @return 
 */
bool DialogWindow::GetUI_Text(const STRING csResourceName, STRING &csText) 
{
	Resource_Control *pRC = Lookup_Resource_Control(csResourceName);
	if (pRC)
	{
		pRC->GetText(csText);
		return true;
	}
	ResourceEntity *pRE = GetResourceStore()->LookupResourceEntity(csResourceName,GetResourceID());
	if (pRE)
	{
		pRE->GetText(csText);
		return true;
	}
	return false;
}

int DialogWindow::execute()
{
	Create();
	return DoModal();
}

}






