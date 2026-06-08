//*/
/*
					CBfcGUI_ResourceStore.cpp : 
	
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

void ResourceStore::SetName(const STRING &cs)
{
	m_name = cs;
}

void ResourceStore::GetName(STRING &cs) const		// returns the name of this reource store
{
	cs = m_name;
}

	// Do a Post-Load Processing after fully loaded to resolve names, etc.
void ResourceStore::PostLoad()
{
	ResourceContainer *pRC;

	ULONG uIr=m_resourceContainerList.StartIteration();
	while (pRC = m_resourceContainerList.GetNext(uIr))
		PostLoad(pRC);
}

void ResourceStore::PostLoad(ResourceContainer *pRC)
{
	ResourceEntity				*pRE;
	CBfc::Array<ResourceEntity>	*pEntities=pRC->GetEntityList();
	ULONG uIr=pEntities->StartIteration();
	while (pRE=pEntities->GetNext(uIr))
		PostLoad(pRE);
}

void ResourceStore::PostLoad(ResourceEntity *pRE)
{
	if (pRE->HasHandlers())
	{
		ResourceHandler				*pRH;
		CBfc::Array<ResourceHandler> *pHandlers=pRE->GetHandlerList();
		ULONG	uli=pHandlers->StartIteration();
		while (pRH=pHandlers->GetNext(uli))
		{
			pRH->ProcessPhrase(this);
		}
	}
}

// Load a string from the resource
bool ResourceStore::LoadString (const STRING &csIDName, STRING &destString)
{
	Resource_ID resourceID=LookupResourceID(csIDName);
	if (resourceID)
		return LoadString(resourceID,destString);
	return false;
}

// Load a string from the resource
bool ResourceStore::LoadString (const Resource_ID resourceID, STRING &destString)
{
	ResourceEntity	*pRE;

	ULONG uIr=m_resourceEntityList.StartIteration();
	while (pRE = m_resourceEntityList.GetNext(uIr))
		if (pRE->m_Resource_ID == resourceID)
		{
			pRE->GetName(destString);
			return true;
		}
	return false;
}

bool ResourceStore::AddResourceEntity(const ResourceEntity *p_resourceEntity)
{
	return m_resourceEntityList.Add(p_resourceEntity);
}

bool ResourceStore::AddResourceContainer(const ResourceContainer *p_resourceContainer)
{
	return m_resourceContainerList.Add(p_resourceContainer);
}

ResourceContainer *ResourceStore::LookupResourceContainer(const Resource_ID resourceID)
{
	ResourceContainer *pRC;

	ULONG uIr=m_resourceContainerList.StartIteration();
	while (pRC = m_resourceContainerList.GetNext(uIr))
		if (pRC->m_Resource_ID==resourceID)
			return pRC;
	return NULL;
}

Resource_ID ResourceStore::LookupResourceID(const STRING &csIDName, const Resource_ID parentID)
{
	Resource_ID	rID=0;
	ResourceEntity	*pRE=LookupResourceEntity(csIDName,parentID);
	if (pRE)
		rID=pRE->GetResourceID();
	return rID;
}

ResourceEntity *ResourceStore::LookupResourceEntity(const CBfc::STRING &csIDName, const Resource_ID parentID)
{
	ResourceEntity	*pRE=NULL;

	if (parentID==0)
	{
		pRE=LookupResourceEntity(csIDName,&m_resourceEntityList,parentID);
		if (pRE==NULL)
		{
			ResourceContainer *pRC;

			ULONG uIr=m_resourceContainerList.StartIteration();
			while (pRE==NULL && (pRC = m_resourceContainerList.GetNext(uIr)))
			{
				STRING	csName;
				pRC->GetName(csName);
				if (csName == csIDName)
					pRE=pRC;
				else
					pRE=LookupResourceEntity(csIDName,pRC->GetEntityList(),parentID);
			}
		}
	} else
	{
		ResourceContainer *pRC;

		ULONG uIr=m_resourceContainerList.StartIteration();
		while (pRE==NULL && (pRC = m_resourceContainerList.GetNext(uIr)))
		{
			if(parentID==pRC->m_Resource_ID) // container must match parent
			{
				pRE=LookupResourceEntity(csIDName,pRC->GetEntityList(),0);
				break;
			}
		}
	}
	return pRE;
}

// Looks up an ID within
// Has 2 loops for optimum speed.
ResourceEntity *ResourceStore::LookupResourceEntity(const CBfc::STRING &csIDName, CBfc::Array<ResourceEntity> *pEntityArray, const Resource_ID parentID) const
{
	ResourceEntity	*pRE;

	ULONG uIe=pEntityArray->StartIteration();
	if (parentID)
	{
		while (pRE = pEntityArray->GetNext(uIe))
		{
			if (pRE->m_Parent_ID==parentID && pRE->m_cs_name==csIDName)
				return pRE;
		}
	} else
	{
		while (pRE = pEntityArray->GetNext(uIe))
		{
			if (pRE->m_cs_name==csIDName)
				return pRE;
		}
	}
	return (ResourceEntity *)NULL;
}

bool ResourceStore::LookupResourceName(CBfc::STRING &csIDName, const Resource_ID rID, const Resource_ID parentID)
{
	if (parentID==0)
	{
		if (!LookupResourceName(csIDName,&m_resourceEntityList,rID,parentID))
		{
			ResourceContainer *pRC;

			ULONG uIr=m_resourceContainerList.StartIteration();
			while ((pRC = m_resourceContainerList.GetNext(uIr)))
			{
				if (rID==pRC->m_Resource_ID)
				{
					pRC->GetName(csIDName);
					return true;
				}
				if (LookupResourceName(csIDName,pRC->GetEntityList(),rID,parentID))
					return true;
			}
		}
	} else
	{
		ResourceContainer *pRC;

		ULONG uIr=m_resourceContainerList.StartIteration();
		while ((pRC = m_resourceContainerList.GetNext(uIr)))
		{
			if(parentID==pRC->m_Resource_ID) // container must match parent
				return LookupResourceName(csIDName,pRC->GetEntityList(),rID,0);
		}
	}
	return false;
}

bool ResourceStore::LookupResourceName(CBfc::STRING &csIDName, CBfc::Array<ResourceEntity> *pEntityArray, const Resource_ID rID, const Resource_ID parentID) const
{
	ResourceEntity	*pRE;

	ULONG uIe=pEntityArray->StartIteration();
	if (parentID)
	{
		while (pRE = pEntityArray->GetNext(uIe))
		{
			if (pRE->m_Parent_ID==parentID && rID==pRE->m_Resource_ID)
			{
				pRE->GetName(csIDName);
				return true;
			}
		}
	} else
	{
		while (pRE = pEntityArray->GetNext(uIe))
		{
			if ( rID==pRE->m_Resource_ID)
			{
				pRE->GetName(csIDName);
				return true;
			}
		}
	}
	return false;
}


}


