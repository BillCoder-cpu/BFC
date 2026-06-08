//*/
/*
					CBfcGUI_ResourceEntity.h : 
	
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

namespace CBfcGUI
{
#define BFC_GUIRES_KEY_START	0
#define BFC_GUIRES_KEY_DEFINE	1
#define BFC_GUIRES_KEY_END		2
#define BFC_GUIRES_KEY_NAME	3


typedef enum
{
	BFC_GUIRES_ATTRIBUTE_KEY_HOTKEY = 0,
	BFC_GUIRES_ATTRIBUTE_KEY_ALIGN,
	BFC_GUIRES_ATTRIBUTE_KEY_POSITION,
	BFC_GUIRES_ATTRIBUTE_KEY_SHAPE,
	BFC_GUIRES_ATTRIBUTE_KEY_SIZE,
	BFC_GUIRES_ATTRIBUTE_KEY_SIZE_IN_CHARACTERS,
	BFC_GUIRES_ATTRIBUTE_KEY_DEFAULT,
	BFC_GUIRES_ATTRIBUTE_KEY_RADIO,
	BFC_GUIRES_ATTRIBUTE_KEY_CHECKBOX,
	BFC_GUIRES_ATTRIBUTE_KEY_ICON,
	BFC_GUIRES_ATTRIBUTE_KEY_GROUP,
	BFC_GUIRES_ATTRIBUTE_KEY_CHECKED,
	BFC_GUIRES_ATTRIBUTE_KEY_NUMERIC,
	BFC_GUIRES_ATTRIBUTE_KEY_INTEGER,
	BFC_GUIRES_ATTRIBUTE_KEY_PASSWORD,
	BFC_GUIRES_ATTRIBUTE_KEY_CURRENCY,
	BFC_GUIRES_ATTRIBUTE_KEY_PERCENT,
	BFC_GUIRES_ATTRIBUTE_KEY_DISTANCE,
} EBFC_GUIRES_ATTRIBUTE_KEY;

typedef enum
{
	BFC_GUIRES_HANDLER_KEY_MOUSEENTER,
	BFC_GUIRES_HANDLER_KEY_MOUSELEAVE,
	BFC_GUIRES_HANDLER_KEY_LEFTCLICK,
	BFC_GUIRES_HANDLER_KEY_RIGHTCLICK,
} EBFC_GUIRES_HANDLER_KEY;

typedef enum
  {
	BFC_GUIRES_CONTAINER_KEY_WINDOW,
	BFC_GUIRES_CONTAINER_KEY_CONTROL,
	BFC_GUIRES_CONTAINER_KEY_TOOLBAR,
	BFC_GUIRES_CONTAINER_KEY_MENU,
	BFC_GUIRES_RESOURCE_KEY_SUBMENU,
	BFC_GUIRES_RESOURCE_KEY_MENU_ENTRY,
	BFC_GUIRES_RESOURCE_KEY_SEPERATOR,
	BFC_GUIRES_CONTAINER_KEY_END,

	BFC_GUIRES_RESOURCE_KEY_BUTTON,
	BFC_GUIRES_RESOURCE_KEY_LABEL,
	BFC_GUIRES_RESOURCE_KEY_TEXTBOX,
	BFC_GUIRES_RESOURCE_KEY_CURSESBOX,
	BFC_GUIRES_RESOURCE_KEY_LIST,
	BFC_GUIRES_RESOURCE_KEY_LISTBOX,
	BFC_GUIRES_RESOURCE_KEY_COMBOBOX,
	BFC_GUIRES_RESOURCE_KEY_HORIZONTAL_SEPERATOR,
	BFC_GUIRES_RESOURCE_KEY_VERTICAL_SEPERATOR,
	BFC_GUIRES_RESOURCE_KEY_DROPLIST,
	BFC_GUIRES_RESOURCE_KEY_SPACER,
	BFC_GUIRES_RESOURCE_KEY_SWITCHER,
	BFC_GUIRES_RESOURCE_KEY_MATRIX,
//    BFC_GUIRES_RESOURCE_KEY_	,
 } EBFC_GUIRES_RESOURCE_KEY;


typedef enum
  {
	BFC_GUIRES_SHAPE_KEY_RECTANGLE=0,
	BFC_GUIRES_SHAPE_KEY_BITMAP,
	BFC_GUIRES_SHAPE_KEY_OVAL,
	BFC_GUIRES_SHAPE_KEY_POLYGON
  } EBFC_GUIRES_RESOURCE_SHAPE_KEY;


BFC_GUI_CLASS ResourceStore;

// Examples : switch the switcher, close the dialog, 
BFC_GUI_CLASS ResourceEvent
{
public:
	typedef enum
	{
		BFC_GUIRES_EVENT_SWITCH,
		BFC_GUIRES_EVENT_ENDMODAL,
	} EVENT;

	ResourceEvent(const EVENT eEvent,const CBfc::STRING &csPhrase);
	bool			ProcessPhrase(ResourceStore *pRStore);

	EVENT			GetEvent() const { return m_eEvent; }
	Resource_ID		GetTarget();
	UINT			GetParameter();
private:
	CBfcScript::Phrase	m_csPhrase;
	bool				m_bPhraseProcessed;

	UINT			m_EventParamter;
	EVENT			m_eEvent;
	Resource_ID		m_EventID;		// Act apon this resource ID
};

BFC_GUI_CLASS ResourceHandler : public ResourceEvent
{
public:
	ResourceHandler(const EBFC_GUIRES_HANDLER_KEY eKey,const EVENT eEvent,const CBfc::STRING &csPhrase);
	EBFC_GUIRES_HANDLER_KEY GetHandlerKey() const { return m_eHandler; }
private:
	EBFC_GUIRES_HANDLER_KEY	m_eHandler;
};


BFC_GUI_CLASS ResourceAttributes
{
public:
	ResourceAttributes();
	bool SetShape (CBfcVector::Shape2d *);

	void		SetName	(const CBfc::STRING &csName);
	void		GetName	(CBfc::STRING	&csName) const;
	void		SetText (const CBfc::STRING &csText);
	void		GetText	(CBfc::STRING	&csText) const;
	void		SetSize	(const CBfc::Size2dU &size);
	CBfc::Size2dU GetSize () const;
	CBfc::Size2dU GetPosition () const;
	void		SetGroup	(const CBfc::STRING &csGroup);
	const CBfc::STRING &GetGroup () const;
	void		SetHotkey	(const character cHot);
	bool		GetHotkey	(character &cHot) const;

	void	SetAttribute(const EBFC_GUIRES_ATTRIBUTE_KEY eKey);
	void	UnsetAttribute(const EBFC_GUIRES_ATTRIBUTE_KEY eKey);
	bool	HasAttribute(const EBFC_GUIRES_ATTRIBUTE_KEY eKey) const;

	void SetAttributeFlags(ULONG flags) {
		m_attribute_flags |= flags;
		}
	void UnsetAttributeFlags(ULONG flags) {
		m_attribute_flags &= (~flags);
		}
	ULONG GetAttributeFlags() const	{
			return m_attribute_flags;
		}
public:
	CBfc::Position2dU		m_position;
	CBfc::STRING		m_cs_name;			// Used by C++ header file generator.
	CBfc::STRING		m_cs_text;			// Default text
protected:
	UINT			ConvertAttributeKeyToFlag(const EBFC_GUIRES_ATTRIBUTE_KEY eKey) const;

	character			m_cHotkey;
	CBfc::Size2dU		m_size;
private:
	ULONG				m_attribute_flags;	// binary bits
	CBfc::STRING		m_cs_group;			// Group name
	CBfcVector::Shape2d                *m_p_shape;
  //  EBFC_GUIRES_RESOURCE_SHAPE_KEY    m_shape;
};


BFC_GUI_CLASS ResourceEntity : public ResourceAttributes
{
public:
  ResourceEntity (const Resource_ID ID);
  virtual ~ResourceEntity();

  void SetParent(const Resource_ID parentID);
  void SetType	(const EBFC_GUIRES_RESOURCE_KEY eKey);
  EBFC_GUIRES_RESOURCE_KEY	GetType() const;

  bool HasHandlers() const;
  void AddHandler(ResourceHandler &rh);
  Array<ResourceHandler> *GetHandlerList();
  Resource_ID	GetResourceID() const { return m_Resource_ID; }

  Resource_ID				m_Resource_ID;
  Resource_ID				m_Parent_ID;

  EBFC_GUIRES_RESOURCE_KEY	m_ResourceType;  // Window, button, label, etc.
private:
	Array<ResourceHandler>	m_ResourceHandlerList;
};

BFC_GUI_CLASS ResourceContainer : public ResourceEntity
{
public:
	ResourceContainer (const Resource_ID ID);
	bool	AddResourceEntity(const ResourceEntity *p_resourceEntity);
	Array<ResourceEntity>	*GetEntityList();
private:
	Array<ResourceEntity>		m_resourceEntityList;
};

}

