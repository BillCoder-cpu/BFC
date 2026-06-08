//*/
/*
					CBfcGUI_ResourceEntity.cpp : 
	
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

namespace CBfcGUI {


ResourceEvent::ResourceEvent(const EVENT eEvent,const STRING &csPhrase)
	: m_eEvent(eEvent)
		, m_csPhrase(csPhrase)
		, m_bPhraseProcessed(0)
{
}

Resource_ID ResourceEvent::GetTarget()
{
	return m_EventID;
}

UINT ResourceEvent::GetParameter()
{
	return m_EventParamter;
}

bool ResourceEvent::ProcessPhrase(ResourceStore *pRStore)
{
	if (!m_bPhraseProcessed)
	{						// Example: OnMouseEnter(Switcher SWITCH_M Mortgage_GenerateOptions)
		STRING	cs;
		m_csPhrase.Reset();
//		, m_EventID(rID)
//		m_EventParameter(uEventParamter)
//	const Resource_ID rID,const UINT uEventParamter)
		if (m_csPhrase.ReadScriptWord(cs))
		{
			ResourceEntity	*pResEntity=pRStore->LookupResourceEntity(cs);
			if (pResEntity)
			{
				m_EventID=pResEntity->GetResourceID();
				if (m_csPhrase.ReadScriptWord(cs))
				{
					STRING	csText;

					pResEntity->GetText(csText);
					STRING	csNext;
					UINT	u_Start=0;
					m_EventParamter=0;
					while (u_Start=csText.ParseLines(u_Start,csNext))
					{
						if (csNext==cs)
							break;
						m_EventParamter++;
					}
				}
			}
		}
		m_bPhraseProcessed=true;
	}
	return m_bPhraseProcessed;
}

ResourceHandler::ResourceHandler(const EBFC_GUIRES_HANDLER_KEY eKey,const EVENT eEvent,const STRING &csPhrase)
	: ResourceEvent(eEvent, csPhrase)
		, m_eHandler(eKey)
{
}

//
// ResourceAttributes ()
//
ResourceAttributes::ResourceAttributes()
	: m_attribute_flags(0)
{
}

//
bool ResourceAttributes::SetShape (CBfcVector::Shape2d_PTR p_shape)
{
  if (m_p_shape) delete m_p_shape;
  m_p_shape = p_shape;
  return true;
}

bool ResourceAttributes::HasAttribute(const EBFC_GUIRES_ATTRIBUTE_KEY eKey) const
{
	return (GetAttributeFlags() & ConvertAttributeKeyToFlag(eKey))!=0;
}

void ResourceAttributes::SetAttribute (const EBFC_GUIRES_ATTRIBUTE_KEY eKey)
{
	SetAttributeFlags(ConvertAttributeKeyToFlag(eKey));
}

void ResourceAttributes::UnsetAttribute (const EBFC_GUIRES_ATTRIBUTE_KEY eKey)
{
	UnsetAttributeFlags(ConvertAttributeKeyToFlag(eKey));
}

UINT ResourceAttributes::ConvertAttributeKeyToFlag(const EBFC_GUIRES_ATTRIBUTE_KEY eKey) const
{
	const ULONG flag=1<<(UINT)eKey;
	return flag;
}

void ResourceAttributes::SetName (const STRING &csName)
{
	m_cs_name = csName;
}

void ResourceAttributes::GetName (STRING &csName) const
{
	csName = m_cs_name;
}

void ResourceAttributes::SetText (const STRING &csText)
{
	m_cs_text=csText;
}

void ResourceAttributes::GetText (STRING &csText) const
{
	csText=m_cs_text;
}

void ResourceAttributes::SetSize (const Size2dU &size)
{
	m_size=size;
}

CBfc::Size2dU ResourceAttributes::GetSize () const
{
	return m_size;
}

CBfc::Size2dU ResourceAttributes::GetPosition () const
{
	return m_position;
}

void ResourceAttributes::SetGroup (const STRING &csGroup)
{
	m_cs_group=csGroup;
}

const CBfc::STRING &ResourceAttributes::GetGroup () const
{
	return m_cs_group;
}

void ResourceAttributes::SetHotkey	(const character cHot)
{
	SetAttribute(BFC_GUIRES_ATTRIBUTE_KEY_HOTKEY);
	m_cHotkey=cHot;
}

bool ResourceAttributes::GetHotkey	(character &cHot) const
{
	if (HasAttribute(BFC_GUIRES_ATTRIBUTE_KEY_HOTKEY))
	{
		cHot=m_cHotkey;
		return true;
	}
	return false;
}


//
// ResourceEntity ()
//
ResourceEntity::ResourceEntity (const Resource_ID ID)
  : m_Resource_ID(ID)
  , m_Parent_ID(0)
{
}

ResourceEntity::~ResourceEntity()
{
}

void ResourceEntity::SetParent(const Resource_ID parentID)
{
	m_Parent_ID = parentID;
}

void ResourceEntity::SetType (const EBFC_GUIRES_RESOURCE_KEY eKey)
{
	m_ResourceType = eKey;
}

EBFC_GUIRES_RESOURCE_KEY ResourceEntity::GetType() const
{
	return m_ResourceType;
}

void ResourceEntity::AddHandler(ResourceHandler &rh)
{
	m_ResourceHandlerList.Add(&rh);
}

bool ResourceEntity::HasHandlers() const
{
	return (m_ResourceHandlerList.GetCount()>0);
}

CBfc::Array<ResourceHandler> *ResourceEntity::GetHandlerList()
{
	return &m_ResourceHandlerList;
}


//
// ResourceContainer
//
ResourceContainer::ResourceContainer(const Resource_ID ID)
: ResourceEntity(ID)
{
}

bool ResourceContainer::AddResourceEntity(const ResourceEntity *p_resourceEntity)
{
	return m_resourceEntityList.Add(p_resourceEntity);
}

CBfc::Array<ResourceEntity>	*ResourceContainer::GetEntityList()
{
	return &m_resourceEntityList;
}

}
