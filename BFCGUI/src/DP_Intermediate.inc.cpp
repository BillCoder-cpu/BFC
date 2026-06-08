//*/
/*
					DP_Intermediate.inc.cpp : 
	
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


DP::DP(DX *pDX)
	: m_pDX(pDX)
{
}

CDefault_DlgDP::CDefault_DlgDP(GUI *p_GUI, DX *pDX, Window *p_Parent)
: DlgDP (p_GUI, pDX, p_Parent)
{
}

int CDefault_DlgDP::RunDlg(DialogWindow *pDlgDS)
{
	if (pDlgDS)
	{
		pDlgDS->SetDP(this);
		const int iRval = pDlgDS->execute();
		return iRval;
	}
	return false;
}

bool CDefault_DlgDP::ProcessInput(Resource_Control *pRC, DialogWindow *pDS)
{
	return false;
}

DX	*DP::GetDX() const
{
	return m_pDX;
}

DlgDP::DlgDP(GUI *p_GUI, DX *pDX, Window *p_Parent)
	: DP(pDX)
	, m_p_GUI(p_GUI)
{
}

int DlgDP::RunDlg (Window *p_Parent, const STRING &DialogName)
{
	return RunDlg(new CBfcGUI::DialogWindow (GetGUI(), DialogName, p_Parent));
}


