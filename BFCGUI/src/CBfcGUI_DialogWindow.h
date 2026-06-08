//*/
/*
					CBfcGUI_DialogWindow.h : 
	
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
/*

These windows are DLGDS datasources

	So:

	certain buttons are known to end or modify the dialog, thus the DS can process
	these itself, otherwise:

		Signal the DX on any input
		Then, Signal the DP on any input.
			DP can return value to bring down the dialog.

	some dialog (cwiz) start, stop, change timer, etc.

		The DS can process it's own onmouseover/click to dynamically restructure\
	the dialog/activate different resource control groups, change button looks, etc.

*/

namespace CBfcGUI
{

// using namespace Gears;
#include "DX.temp.inc.cpp"

BFC_GUI_CLASS DP
{
public:
	DP(DX *pDX);
protected:
	DX	*GetDX() const;
private:
	DX	*m_pDX;		// Pointer to the data exchange class
};

BFC_GUI_CLASS DialogWindow;

BFC_GUI_CLASS DlgDP : public DP
{
public:
	DlgDP(GUI *p_GUI, DX *pDX=NULL, Window *p_Parent=NULL);

public:	// required for any DP that has a DlgDS
	virtual int	RunDlg(DialogWindow *pDlgDS=NULL)=0;
	int RunDlg (Window *p_Parent, const STRING &DialogName);
	
	virtual bool	ProcessInput(Resource_Control *, DialogWindow *pDS)=0;	// return false to bring down the DS
	GUI		*GetGUI() const { return m_p_GUI; }
private:
	GUI		*m_p_GUI;
};

BFC_GUI_CLASS CDefault_DlgDP : public DlgDP
{
public:
	CDefault_DlgDP(GUI *p_GUI, DX *pDX=NULL, Window *p_Parent=NULL);
	virtual int		RunDlg(DialogWindow *pDlgDS=NULL);
	virtual bool	ProcessInput(Resource_Control *, DialogWindow *pDS);
};

#define DlgDS	DialogWindow

BFC_GUI_CLASS DialogWindow : public ResourceWindow, public DataSource
{
public:
// 	DialogWindow(GUI *p_GUI, Window *p_Parent=NULL);
	DialogWindow(GUI *p_GUI, const STRING &ResourceName,  Window *p_Parent=NULL, ResourceStore *p_ResourceStore=NULL, const EBFC_GUI_WINDOW_TYPE eType=WND_DIALOG);
	DialogWindow(GUI *p_GUI, character *pScript, Window *p_Parent=NULL);

	void SetDP(DlgDP *pDP) { m_pDP=pDP; }

	virtual int		OnDestroy();
	void			UpdateDX(void); // const bool bSet=true);
	void			UpdateDS(void);

	virtual int	execute();

	CBfc::ArrayPtr	*GetResourceControlList() { return &m_ResourceControl_List; }
	virtual bool	OnCreate();
protected:
	virtual int		OnMessage(const Message &msg);
	
	virtual void	UpdateDX(Data_Resource_Control *pRc);
	virtual void	UpdateDX(Button *pButton);
	virtual void	UpdateDS(Resource_Control *pRc);
	virtual bool	ButtonPress (const Resource_ID rID, Resource_Control *pRc);
protected:
	
	bool		GetUI_Text(const STRING csResourceName, STRING &csText);
	bool		SetUI_Text (const STRING &csResourceName, const STRING &csText);
	
	DlgDP	*	GetDP() const { return m_pDP; }

	void	AddSpacer(const CBfc::Size2dU &size);
	void	AddMatrix(const CBfc::Size2dU &size);
	void	AddSwitcher(const Resource_ID rID);
	void	EndFrame();
	void	AddResourceControl(const Resource_Control *pRc);
	
	ResourceEntity 	*	LookupResourceEntity(const CBfc::STRING &csName);
	Resource_Control *	Lookup_Resource_Control(const CBfc::STRING &csName);
	Resource_Control *	Lookup_Resource_Control(const Resource_ID rID);
	bool			CreateEntryList(Array<ResourceEntity> *pResEntityList);
	bool 	AddWindows(const ResourceEntity *pResEntity);
	bool 	AddWindow (const STRING &csNext);
private:
	CBfc::ArrayPtr			m_ResourceControl_List;
	DlgDP				*	m_pDP;
};

//////////////////////////////////////

/*
class DialogDS : public DialogWindow, DataSource
{
public:
	DialogDS(GUI *p_GUI, const STRING &ResourceName,  Window *p_Parent=NULL)
	: DialogWIndow (p_GUI, ResourceName, p_Parent)
	{
	}

	virtual bool Acquire (DataExchange &DX);
};
*/

/*
		ImageLabels labels;
		if (Image.ReadImageLabels(labels))
			labels.PopulateDX(DX);
	
		if (pDS->Acquire (DX))			// fills DX if sucessful (if (RunDlg()) FillDX(DX);)
		{
			labels.ReadDX(DX);
			Image.SaveImageLabels(labels);
		}
	}
*/

}


