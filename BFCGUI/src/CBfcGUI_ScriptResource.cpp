//*/
/*
					CBfcGUI_ScriptResource.cpp : 
	
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

//
//  CBfcGUI_ScriptResource.cpp
//
//    Reads resource scripts into memory.
//
// Syntax:
//     Start window WindowName
//        attributes
//     End WindowName
//

#include <BFC/BFCGUI.h>

using namespace CBfc;

namespace CBfcGUI {

static characterPtr BfcRes_KeyWords[] = 
{
	STATICBYTES("Start"),
	STATICBYTES("Define"),
	STATICBYTES("End"),
	STATICBYTES("ResourceName"),
	characterPtr(NULL)
};

static characterPtr BfcRes_AttributeKeys[] = 
{
	STATICBYTES("Hotkey"),
	STATICBYTES("Align"),
	STATICBYTES("Position"),
	STATICBYTES("Shape"),
	STATICBYTES("Size"),
	STATICBYTES("Size_in_characters"),
	STATICBYTES("Default"),
	STATICBYTES("Radio"),
	STATICBYTES("Checkbox"),
	STATICBYTES("Icon"),
	STATICBYTES("Group"),
	STATICBYTES("Checked"),
	STATICBYTES("Number"),
	STATICBYTES("Integer"),
	STATICBYTES("Password"),
	STATICBYTES("Currency"),
	STATICBYTES("Percent"),
	STATICBYTES("Distance"),
	characterPtr(NULL)
};

static characterPtr  BfcRes_HandlerKeys[] = {
	STATICBYTES("OnMouseEnter"),
	STATICBYTES("OnMouseLeave"),
	STATICBYTES("OnLeftClick"),
	STATICBYTES("OnRightClick"),
	characterPtr(NULL)
};

static characterPtr  BfcRes_ResourceKeys[] = {
	STATICBYTES("Window"),
	STATICBYTES("Control"),
	STATICBYTES("Toolbar"),
	STATICBYTES("Menu"),
	STATICBYTES("SubMenu"),
	STATICBYTES("Entry"),
	STATICBYTES("Seperator"),
	STATICBYTES("End"),

	STATICBYTES("Button"),
	STATICBYTES("Label"),
	STATICBYTES("Textbox"),
	STATICBYTES("Cursesbox"),
	STATICBYTES("List"),
	STATICBYTES("Listbox"),
	STATICBYTES("Combobox"),
	
	STATICBYTES("Horizontal_seperator"),
	STATICBYTES("Vertical_seperator"),
	STATICBYTES("DropList"),

	STATICBYTES("Spacer"),
	STATICBYTES("Switcher"),
	STATICBYTES("Matrix"),

	characterPtr(NULL)
};

static characterPtr  BfcRes_ShapeKeys[] = {
	STATICBYTES("Rectangle"),
	STATICBYTES("Bitmap"),
	STATICBYTES("Oval"),
	STATICBYTES("Polygon"),
	characterPtr(NULL)
};



/**
 * 
 * @param resourceStream 
 * @return 
 */
ScriptResource::ScriptResource (CBfc_Stream &resourceStream)
  : CBfcScript::Script_XML (resourceStream)
    , m_nextID (1000)
{
}

void ScriptResource::SetFolder (const Filename &folder)
{
	m_folder = folder;
}


// Reads a thinglist into an array of things
//
//
/**
 * 
 * @return 
 */
ResourceStore *ScriptResource::LoadResources ()
{
	//  CBfc_SingleLock (m_LocalToMe);  // NOTE:: This operation is -Not- thread safe
//	if (m_b_Loaded)
//		return (ResourceStore *)m_p_ResourceStore;
	ResourceStore	*pRes=new ResourceStore;
	if (LoadResourcesInternal(pRes))
		return pRes;
	
	delete pRes;
	return NULL;
}

bool ScriptResource::LoadResourcesInternal (ResourceStore *pRes)
{
try
	{
	int	iKey;

	while ( MatchScriptKey (BfcRes_KeyWords, iKey)  && iKey!=BFCSCRIPT_KEY_NONE)
	{
		switch (iKey) {
			case BFCSCRIPT_KEY_NONE:	// Syntax Error- should be handled (optionally) by the base class.
			  // f.iLineNumber;
				break;
			case BFC_GUIRES_KEY_START:
			  {
			    ResourceContainer *p_resourceContainer = new ResourceContainer(m_nextID++);
			    if (!ReadNextResourceContainer (*p_resourceContainer))
					throw 0;
				pRes->AddResourceContainer(p_resourceContainer);
			  }
			case BFC_GUIRES_KEY_DEFINE:
		        break;
		    case BFC_GUIRES_KEY_END:  // End of resource definition encountered.
			      // Match the next word with the object being defined (throw away next word)
				SkipScriptWord();		// ski pname for now
		    case BFC_GUIRES_KEY_NAME:  // Naming of this resource script
				{
					STRING	csName;
					if (!ReadScriptWord(csName))
						throw 0;
					pRes->SetName(csName);
				}
				break;
		}
	}
	pRes->PostLoad();
	return true;
	}
 catch (...)
	{
		return false;
	}
}

//  ReadNextResourceContainer()
//
//
/**
 * 
 * @param resourceContainer 
 * @return 
 */
bool  ScriptResource::ReadNextResourceContainer (ResourceContainer &resourceContainer)
{
	int iResourceKey;

	if (!MatchScriptKey (BfcRes_ResourceKeys, iResourceKey))   // Determine what sort of resource is being started.
	  return false;
	resourceContainer.SetType((EBFC_GUIRES_RESOURCE_KEY)iResourceKey);

	PickupName(&resourceContainer);
	PickupAttributes(resourceContainer);
	PickupText(&resourceContainer);

	STRING	sResourceName;
	resourceContainer.GetName(sResourceName);
	
	switch (iResourceKey)
	{
		case BFC_GUIRES_CONTAINER_KEY_WINDOW:
		case BFC_GUIRES_CONTAINER_KEY_CONTROL:
		case BFC_GUIRES_CONTAINER_KEY_TOOLBAR:
		case BFC_GUIRES_CONTAINER_KEY_MENU:
			while (1)
			{
				ResourceEntity *p_resourceEntity = ReadNextResourceEntity ();
				if (!p_resourceEntity)
					break;
				if (p_resourceEntity->GetType() == BFC_GUIRES_CONTAINER_KEY_END)
				{
					STRING	sName;
					p_resourceEntity->GetName(sName);
					if (sName == sResourceName)
					{
						delete p_resourceEntity;
						break;
					}
				}
				p_resourceEntity->SetParent(resourceContainer.GetResourceID());
				resourceContainer.AddResourceEntity(p_resourceEntity);
			}
			break;
	}
	return true;
}

// ReadNextResourceEntity ()
//
/**
 * 
 * @return 
 */
ResourceEntity *ScriptResource::ReadNextResourceEntity ()
{
	int iResourceKey;
	if (!MatchScriptKey (BfcRes_ResourceKeys, iResourceKey))   // What sort of resource is being started?
	  throw;
	if (iResourceKey == BFCSCRIPT_KEY_NONE)
		return NULL;
	ResourceEntity *p_resourceEntity = new ResourceEntity(m_nextID++);

  try
  {
	p_resourceEntity->SetType((EBFC_GUIRES_RESOURCE_KEY)iResourceKey);

	if (iResourceKey != BFC_GUIRES_RESOURCE_KEY_SPACER)
	{
		PickupName(p_resourceEntity);	// pick up the name
		PickupAttributes(*p_resourceEntity);
		PickupHandlers(*p_resourceEntity);
		PickupText(p_resourceEntity);
	} else
		PickupAttributes(*p_resourceEntity);

    return p_resourceEntity;
  } catch (...)
  {
	BFC_RELEASE(p_resourceEntity);
	throw;
  }
}

/**
 * 
 * @param p_resourceEntity 
 * @return 
 */
bool ScriptResource::PickupName(ResourceEntity *p_resourceEntity)
{
	STRING	csName;
	bool	bNameSet = false;
	switch (p_resourceEntity->GetType())
	{
		case BFC_GUIRES_CONTAINER_KEY_WINDOW:
		case BFC_GUIRES_CONTAINER_KEY_CONTROL:
		case BFC_GUIRES_CONTAINER_KEY_TOOLBAR:
		case BFC_GUIRES_RESOURCE_KEY_BUTTON:
		case BFC_GUIRES_RESOURCE_KEY_TEXTBOX:
		case BFC_GUIRES_RESOURCE_KEY_CURSESBOX:
		case BFC_GUIRES_RESOURCE_KEY_LIST:
		case BFC_GUIRES_RESOURCE_KEY_LISTBOX:
		case BFC_GUIRES_RESOURCE_KEY_COMBOBOX:
		case BFC_GUIRES_RESOURCE_KEY_DROPLIST:
		case BFC_GUIRES_RESOURCE_KEY_SWITCHER:
		case BFC_GUIRES_CONTAINER_KEY_MENU:
		case BFC_GUIRES_RESOURCE_KEY_SUBMENU:
		case BFC_GUIRES_CONTAINER_KEY_END:
			if (!ReadScriptWord(csName))
				throw 0;
			p_resourceEntity->SetName(csName);
			bNameSet=true;
			break;
		case BFC_GUIRES_RESOURCE_KEY_LABEL:
		case BFC_GUIRES_RESOURCE_KEY_HORIZONTAL_SEPERATOR:
		case BFC_GUIRES_RESOURCE_KEY_VERTICAL_SEPERATOR:
		case BFC_GUIRES_RESOURCE_KEY_MENU_ENTRY:		// No Name at All!
				// These type don't necessessarily have a name
			{
				character		c;
				if (!ReadAheadScript_Character(c))
					throw 0;
				if (c != '"')
				{
					if (!ReadScriptWord(csName))
						throw 0;
					p_resourceEntity->SetName(csName);
					bNameSet=true;
				}
			}
			break;
			break;
	}
	return bNameSet;
}

/**
 * 
 * @param resourceEntity 
 * @return 
 */
bool ScriptResource::PickupAttributes(ResourceEntity &resourceEntity)
{
	// pick up any attributes
	int iAttrib;
	do
	{
	  if (!MatchScriptKey (BfcRes_AttributeKeys, iAttrib))   // Determine what sort of Attribute is present.
	    return false;
	  switch (iAttrib)
	  {
		case BFCSCRIPT_KEY_NONE:
			return true;
		case BFC_GUIRES_ATTRIBUTE_KEY_POSITION:
		  // Read an x,y pair of unsigned integers surrounded by Paranthesis.
		{
			Position2dU pos;
		  if (!ReadScript_ArgumentList_2dPair (pos))
		    return false;
		  resourceEntity.m_position.Set (pos);
		}
		  break;

		case BFC_GUIRES_ATTRIBUTE_KEY_SHAPE:
		  if (!Read_ResourceShape(resourceEntity))
		    return false;
		  break;

		case BFC_GUIRES_ATTRIBUTE_KEY_SIZE:
		case BFC_GUIRES_ATTRIBUTE_KEY_SIZE_IN_CHARACTERS:
			{
				Size2dU size;
				if (!ReadScript_ArgumentList_2dPair (size))
					return false;
				switch (iAttrib)
				{
					case BFC_GUIRES_ATTRIBUTE_KEY_SIZE_IN_CHARACTERS:
					{
						Size2dU mul(8,16);
						size *= mul;
						break;
					}
				}
				resourceEntity.SetSize(size);
			}
			break;
		case BFC_GUIRES_ATTRIBUTE_KEY_GROUP:
			{
				character	c;
				if (!ReadAheadScript_Character(c))
					return false;
				if (c=='=')
				{
					CBfc::STRING csGroup;
					ReadScript_Character(c);
					ReadScriptWord(csGroup);
					resourceEntity.SetGroup(csGroup);
				}
			}
			break;
		case BFC_GUIRES_ATTRIBUTE_KEY_HOTKEY:
			{
				STRING csHotkey;
				if (ReadScriptWord(csHotkey))
					resourceEntity.SetHotkey(InterpretCharacter(csHotkey));
			}
			break;
		case BFC_GUIRES_ATTRIBUTE_KEY_ALIGN:

			break;
		case BFC_GUIRES_ATTRIBUTE_KEY_RADIO:
		case BFC_GUIRES_ATTRIBUTE_KEY_CHECKBOX:
		case BFC_GUIRES_ATTRIBUTE_KEY_ICON:
		case BFC_GUIRES_ATTRIBUTE_KEY_DEFAULT:
		case BFC_GUIRES_ATTRIBUTE_KEY_CHECKED:
		case BFC_GUIRES_ATTRIBUTE_KEY_NUMERIC:
		case BFC_GUIRES_ATTRIBUTE_KEY_INTEGER:
		case BFC_GUIRES_ATTRIBUTE_KEY_PASSWORD:
		case BFC_GUIRES_ATTRIBUTE_KEY_CURRENCY:
		case BFC_GUIRES_ATTRIBUTE_KEY_PERCENT:
		case BFC_GUIRES_ATTRIBUTE_KEY_DISTANCE:
			resourceEntity.SetAttribute((CBfcGUI::EBFC_GUIRES_ATTRIBUTE_KEY)iAttrib);
			break;
	  }
	} while (1);
	return true;
}

/**
 * 
 * @param resourceEntity 
 * @return 
 */
bool ScriptResource::PickupHandlers(ResourceEntity &resourceEntity)
{
	int iHandler;
	do
	{
	  if (!MatchScriptKey (BfcRes_HandlerKeys, iHandler))   // Determine what sort of Handler is present.
	    return false;
	  switch (iHandler)
	  {
		case BFCSCRIPT_KEY_NONE:
			return true;
		case BFC_GUIRES_HANDLER_KEY_MOUSEENTER:
		case BFC_GUIRES_HANDLER_KEY_MOUSELEAVE:
		case BFC_GUIRES_HANDLER_KEY_LEFTCLICK:
		case BFC_GUIRES_HANDLER_KEY_RIGHTCLICK:
			{
				ResourceEvent::EVENT	eEvent=ResourceEvent::BFC_GUIRES_EVENT_SWITCH;
				Resource_ID				rDestID=0;
				UINT					uParameter=0;
				CBfcScript::Phrase		phrase;
				STRING					cs;

			    if (!ReadScript_ArgumentList (phrase))	// Reads contents of parenthesis into phrase
					throw 0;
				phrase.Reset();
				if (phrase.ReadScriptWord(cs))
				{
					if (cs=="Switcher")			// Example: OnMouseEnter(Switcher SWITCH_M Mortgage_GenerateOptions)
						eEvent=ResourceEvent::BFC_GUIRES_EVENT_SWITCH;
					else if (cs=="EndModal")	// Example: OnLeftClick(EndModal)
						eEvent=ResourceEvent::BFC_GUIRES_EVENT_ENDMODAL;
					ResourceHandler	rh((EBFC_GUIRES_HANDLER_KEY)iHandler,eEvent,phrase.Remainder());
					resourceEntity.AddHandler(rh);
				}
			}
			break;
	  }
	} while (1);
	return true;
}

/**
 * 
 * @param p_resourceEntity 
 * @return 
 */
bool ScriptResource::PickupText(ResourceEntity *p_resourceEntity)
{
	STRING	csText;
	bool	bTextSet=false;
	// pick up the text
	switch (p_resourceEntity->GetType())
	{
        case BFC_GUIRES_RESOURCE_KEY_BUTTON:
		case BFC_GUIRES_RESOURCE_KEY_LABEL:
		case BFC_GUIRES_RESOURCE_KEY_TEXTBOX:
		case BFC_GUIRES_RESOURCE_KEY_LIST:
		case BFC_GUIRES_RESOURCE_KEY_LISTBOX:
		case BFC_GUIRES_RESOURCE_KEY_CURSESBOX:
		case BFC_GUIRES_RESOURCE_KEY_COMBOBOX:
		case BFC_GUIRES_CONTAINER_KEY_WINDOW:
		case BFC_GUIRES_CONTAINER_KEY_TOOLBAR:
// 		case BFC_GUIRES_CONTAINER_KEY_MENU:
		case BFC_GUIRES_RESOURCE_KEY_SUBMENU:
		case BFC_GUIRES_RESOURCE_KEY_MENU_ENTRY:
			// read in the text
			{
				character		c;
				if (!ReadAheadScript_Character(c))
					throw 0;
				if (c == '"')
				{
					STRING	csText;
					if (!ReadScriptString(csText))
						throw 0;
					p_resourceEntity->SetText(csText);
					bTextSet = true;
				}
			}
			break;
		case BFC_GUIRES_RESOURCE_KEY_DROPLIST:
			{
				STRING	csNextText;
				while(1)
				{
					character		c;
					if (!ReadAheadScript_Character(c))
						throw 0;
					if (c != '"')
						break;

					if (!ReadScriptString(csNextText))
						throw 0;
					csText += csNextText;
					csText += "\n";
					bTextSet = true;

					if (!ReadAheadScript_Character(c))
						throw 0;
					if (c != ',')
						break;
					SkipScript_Character();
				}
				p_resourceEntity->SetText(csText);
			}
			break;
		case BFC_GUIRES_CONTAINER_KEY_CONTROL:
		case BFC_GUIRES_RESOURCE_KEY_SWITCHER:
			// Read in the names of the windows to be switched
			do {
				STRING	csNextWindow;
				if (!ReadScriptWord(csNextWindow))
					throw 0;
				csText += csNextWindow;
				csText += "\n";
				bTextSet = true;
			} while (!IsEOL());
			p_resourceEntity->SetText(csText);
			break;
		case BFC_GUIRES_RESOURCE_KEY_HORIZONTAL_SEPERATOR:
		case BFC_GUIRES_RESOURCE_KEY_VERTICAL_SEPERATOR:
			break;
	}
	return bTextSet;
}

/**
 * 
 * @param resourceEntity 
 * @return 
 */
bool ScriptResource::Read_ResourceShape (ResourceEntity &resourceEntity)
{
  int iShape;
  if (!MatchScriptKey (BfcRes_ShapeKeys, iShape))   // Determine what sort of resource is being started.
    return false;
  switch (iShape)
    {
    case BFCSCRIPT_KEY_NONE:
      return false;
    case BFC_GUIRES_SHAPE_KEY_RECTANGLE:
      {
	Size2dU size;
	bool b_rVal = ReadScript_ArgumentList_2dPair (size);
	resourceEntity.SetShape (new CBfcVector::Shape2d_Rect(Rect2d(Position2d(0,0),size)));
	return b_rVal;
      }
    case BFC_GUIRES_SHAPE_KEY_BITMAP:
    case BFC_GUIRES_SHAPE_KEY_OVAL:
    case BFC_GUIRES_SHAPE_KEY_POLYGON:
      break;
    }
  return false;
}



#if 0
// Find a type from it's name.  Throw away parenthesis.
// Returns NULL if non-existant
TYPE *ThingLIBRARY::LocateType (const CBfc_String &s)
{
	// This is not a formula, it is a simple type
	int					iIndex, iLibIndex;
	FormulaString		fs;
	ThingLIBRARY		*pLib;
	TYPE				*pType;
	CBfc_String			ts(s);

	if ( *ts.GetBufferPtr() == '(' ) {		// Remove enclosing parenthesis
		fs.RemoveParenthesis (ts.GetBufferPtr());
		ts = fs;
	}

	// First, look in the basic set for a datatype.

	iIndex = 0;
	while (Basic_Datatype_List[iIndex].m_Datatype) 
	{
		if (!ts.CompareNoCase (Basic_Datatype_List[iIndex].m_sName))
			return &(Basic_Datatype_List[iIndex]);
		iIndex++;
	}

	// Next, search all other Things defined in the Library for a match.
	iLibIndex = 0;
	pLib = this;		// Start with the current lib
	do {
		for (iIndex = 0; iIndex < pLib->m_TypeList.GetCount(); iIndex++) {
			pType = pLib->m_TypeList.GetAt (iIndex);
			if (pType && !ts.CompareNoCase (pType->m_sName)) 
				return pType;
		}
		pLib = Globals.FindLibrary (*(m_IncludeLibraryList.GetAt(iLibIndex++)));
	} while (pLib);
	return NULL;
}

Thing *ThingLIBRARY::LocateThing (const CBfc_String &s)
{
	// This is not a formula, it is a simple type
	int				iIndex, iLibIndex;
	FormulaString	fs;
	ThingLIBRARY	*pLib;
	Thing			*pThing;
	CBfc_String		ts(s);

	if ( *ts.GetBufferPtr() == '(' ) {		// Remove enclosing parenthesis
		fs.RemoveParenthesis (ts.GetBufferPtr());
		ts = fs;
	}

	// Search all Things defined in the Library for a match.
	iLibIndex = 0;
	pLib = this;		// Start with the current lib
	do 
	{
		for (iIndex = 0; iIndex < pLib->m_ThingList.GetCount(); iIndex++) 
		{
			pThing = pLib->m_ThingList.GetAt (iIndex);
			if (pThing && pThing->IsNamed(s))
				return pThing;
		}
		pLib = Globals.FindLibrary (*(m_IncludeLibraryList.GetAt(iLibIndex++)));
	} while (pLib);
	return NULL;
}

#endif

}



