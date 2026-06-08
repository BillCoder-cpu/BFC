//*/
/*
					Gears_DataExchange.h : 
	
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

#define	GEARS_CLASS	class

namespace AppGears
{
	typedef enum {
		DX_DISTANCE,
		DX_BUTTONCHECK,
		DX_UINT,
	} EDXFieldType;

	typedef struct {
		const char *	field_name;
		EDXFieldType	field_type;
		void *		field_ptr;
		bool			b_allocated;
	} SDXEntry;

	GEARS_CLASS DX	// old style - here for older compatability , don't use this!
	{
public:
		DX();
		virtual ~DX();
	//	access variables presented to the UI (get and set via name string)
		virtual void GetSetCheck (const STRING &csName, bool &bCheck, const bool bSet=false) const;
		virtual void GetSetText (const STRING &csName, STRING &csText, const bool bSet=false) const;
		void	GetSetUINT (const STRING &csName, UINT &u, const bool bSet=false) const;
	
		virtual bool CreateTable(char *p_ScriptText=NULL);	// Create the field list
		virtual bool CreateTable(const SDXEntry *dxList, const UINT numFields);
		static void SetFieldAddress(SDXEntry *pList, const STRING &csName, void *ptr);
public:
		bool RegistrySave	(CBfcGUI::GUI *p_GUI, const CBfc::STRING *p_csRegistryName=NULL) const;
		bool RegistryLoad	(CBfcGUI::GUI *p_GUI, const CBfc::STRING *p_csRegistryName=NULL);
		bool	GetMemberBool (const CBfc::STRING &sName) const;
		UINT	GetMember (const CBfc::STRING &sName) const;
	// 	bool	GetMember (const CBfc::STRING &sName, Distance &value) const;
protected:
		int	LocateField(const STRING &csName) const;
protected:
		UINT			StringToUINT (const CBfc::STRING &s) const;
		double			StringToDouble (const CBfc::STRING &s) const;
		CBfc::STRING	DoubleToString (const double d) const;
		CBfc::STRING	UINTToString (const UINT u) const;
protected:
		CBfc::STRING	m_csRegistryName;
		UINT			m_numFields;		// DX is asked for it's fields by name, 
		SDXEntry		*m_pFieldList;
	};

	GEARS_CLASS DataExchange : public DX
	{
public:
		DataExchange();
		DataExchange(DataSource *pDS);  // fill in the exchange with the defaults in the DS
	};

}

