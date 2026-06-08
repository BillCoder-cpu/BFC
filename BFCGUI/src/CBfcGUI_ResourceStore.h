//*/
/*
					CBfcGUI_ResourceStore.h : 
	
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

// Stores all of the information about the resources.
// Does not hold the controls/windows themselves, they are created when used (can have mulitple of them)
BFC_GUI_CLASS ResourceStore
{
public:
	void GetName(STRING &cs) const;		// returns the name of this reource store
	void SetName(const STRING &cs);		// 
	
	void	PostLoad();
	bool	AddResourceContainer(const ResourceContainer *p_resourceContainer);
	bool	AddResourceEntity(const ResourceEntity *p_resourceEntity);

	bool	LoadString (const Resource_ID resourceID, CBfc::STRING &destString);   // Load a string from the resource
	bool	LoadString (const CBfc::STRING &csIDName, CBfc::STRING &destString);   // Load a string from the resource
	ResourceContainer	*LookupResourceContainer(const Resource_ID resourceID);
	ResourceEntity			*LookupResourceEntity(const CBfc::STRING &csIDName, const Resource_ID parentID=0);

	Resource_ID LookupResourceID(const CBfc::STRING &csIDName, const Resource_ID parentID=0);
	bool 			LookupResourceName(CBfc::STRING &csIDName, const Resource_ID rID, const Resource_ID parentID=0);
protected:
	ResourceEntity *LookupResourceEntity(const CBfc::STRING &csIDName, Array<ResourceEntity> *pEntityArray, const Resource_ID parentID=0) const;
	bool LookupResourceName(CBfc::STRING &csIDName, Array<ResourceEntity> *pEntityArray, const Resource_ID rID, const Resource_ID parentID=0) const;
private:
	void PostLoad(ResourceContainer *pRC);
	void PostLoad(ResourceEntity *pRE);

	STRING								m_name;
	Array<ResourceContainer>	m_resourceContainerList;
	Array<ResourceEntity>		m_resourceEntityList;
};

}
