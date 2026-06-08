//*/
/*
					CBfcGUI_ScriptResource.h : 
	
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

///////////////////////////////////////////////////////////////////////

BFC_GUI_CLASS ScriptResource : public CBfcScript::Script_XML
{
 public:
	//  ScriptResource ();  // Constuctor
	ScriptResource (CBfc_Stream &resourceStream);
	virtual ~ScriptResource() {}

	void SetFolder (const Filename &folder);
	ResourceStore *LoadResources ();
	bool LoadString (Resource_ID resourceID, CBfc_String &destString);   // Load a string from the resource
	bool ReadNextResourceContainer (ResourceContainer &resourceContainer);
	ResourceEntity *ReadNextResourceEntity ();
	bool Read_ResourceShape (ResourceEntity &resourceEntity);
 protected:
	bool LoadResourcesInternal (ResourceStore *pRes);
	bool PickupName(ResourceEntity *p_resourceEntity);
	bool PickupAttributes(ResourceEntity &resourceEntity);
	bool PickupHandlers(ResourceEntity &resourceEntity);
	bool PickupText(ResourceEntity *p_resourceEntity);
 private:
//	volatile bool m_b_Loaded;
//	volatile ResourceStore * m_p_ResourceStore;

	CBfc::Filename	m_folder;
	Resource_ID		m_nextID;
};

}

