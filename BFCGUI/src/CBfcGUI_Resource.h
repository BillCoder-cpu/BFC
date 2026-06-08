//*/
/*
					CBfcGUI_Resource.h : 
	
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
	The concept here is to have a normal 3d space with all kind of shapes within it.
	To each shape is attached a container that will process actions, 

	Actions include mouse enter, mouse move, mouse click, mouse unclick
		These shapes behaviour written in C++ as controls.
*/


namespace CBfcGUI
{
	BFC_GUI_CLASS ResourceWindow : public MenuWindow
	{
	public:
		ResourceWindow(GUI *p_GUI, const STRING &csTitle, Window *p_Parent=NULL);
		ResourceWindow(GUI *p_GUI, const STRING &ResourceName, const EBFC_GUI_WINDOW_TYPE eType=WND_TOP, Window *p_Parent=NULL, ResourceStore *p_ResourceStore=NULL);
		ResourceWindow(GUI *p_GUI, character *pScript, Window *p_Parent=NULL);
		
	protected:
		void			InitializeResourceID();
		
		void				SetResourceContainer(ResourceContainer *p_RC);
		ResourceContainer	*	GetResourceContainer() const;
	private:
		ResourceContainer	*	m_pRC;
	};


	// ResourceControl (Not tied to the display, just the processing half)
	BFC_GUI_CLASS Resource_Control : public Window // ResourceWindow
			{
		public:
			Resource_Control (GUI *p_GUI, Window *p_Parent,const CBfc_String &csText,
						const Resource_ID resourceID,const EBFC_GUI_WINDOW_TYPE eType);

			virtual int OnMouseEnter ();  //
			virtual int OnMouseLeave ();  //
			virtual int OnMouseDown (const CBfc::Point2dU &pt);
			
			void				UpdateHandlers(ResourceEntity *pResEntity);
			
			const CBfc::STRING	GetText() ;
			void				GetText(CBfc::STRING &csText) ;
			virtual void		SetText(const CBfc::STRING &csText);

		protected:
			void				ProcessHandlers(const EBFC_GUIRES_HANDLER_KEY eHandlerKey);
			void				ProcessEvent(ResourceEvent &rEV);
			
		protected:
			CBfc::STRING		m_s_Text;
		private:
			ResourceEntity *		m_pResourceEntity;
			};

	BFC_GUI_CLASS Label: public Resource_Control
			{
		public:
			Label (GUI *p_GUI,Window *p_Parent,const CBfc_String &csText,const Resource_ID resourceID);

		//	bool OnMenuSelection ();
			int (*IsEnabled)();		// button calls this to see if should display or react
			int (*MenuItemHandler)();
		private:
			};

	BFC_GUI_CLASS Button: public Resource_Control
		{
		public:
			Button (GUI *p_GUI,Window *p_Parent,const CBfc_String &csText,const Resource_ID resourceID);
			virtual ~Button();

		//	bool OnMenuSelection ();
			int	(*IsEnabled)();		// button calls this to see if should display or react
			int	(*MenuItemHandler)();

			void	MakeCheckbox();
			void	MakeRadio();
			bool	LoadBitmap(const CBfc::Filename &file);

			void	SetChecked(const bool bChecked);
			bool	GetChecked() const;

			CBfc::STRING	GetGroup() const;
			void			SetGroup(const CBfc::STRING &cs);

			virtual int		OnMouseDown (const CBfc::Point2dU &pt);
		protected:
			virtual int		OnPaint(const CBfc::Rect2dU &rect2d);
		private:
			CBfc::STRING	m_csGroup;
			CBfcImage::Bitmap	*m_pBitmap;
			bool			m_bChecked;
			bool			m_bCheckbox;
			bool			m_bRadio;
		};

	BFC_GUI_CLASS Data_Resource_Control: public Resource_Control
	{
		public:
			Data_Resource_Control (GUI *p_GUI, Window *p_Parent,const CBfc::STRING &csText, const Resource_ID resourceID,const EBFC_GUI_WINDOW_TYPE eType);
			const double GetValue() ;
			const UINT GetValue_UINT() ;
			UINT GetIndex() const;
		protected:
	};

	BFC_GUI_CLASS TextBox: public Data_Resource_Control
					{
		public:
			TextBox (GUI *p_GUI, Window *p_Parent,const CBfc_String &csText,const Resource_ID resourceID);

		//	bool OnMenuSelection ();
			int (*IsEnabled)();		// button calls this to see if should display or react
			void SetAttribute(const EBFC_GUIRES_ATTRIBUTE_KEY attribute);
		private:
					};

	BFC_GUI_CLASS CursesBox: public Data_Resource_Control
					{
		public:
			CursesBox (GUI *p_GUI, Window *p_Parent,const CBfc_String &csText,const Resource_ID resourceID);

		//	bool OnMenuSelection ();
			int (*IsEnabled)();		// button calls this to see if should display or react
//			void SetAttribute(const EBFC_GUIRES_ATTRIBUTE_KEY attribute);
		private:
					};

	BFC_GUI_CLASS ListRC: public Data_Resource_Control
					{
		public:
			ListRC (GUI *p_GUI,Window *p_Parent,const Resource_ID resourceID);

			virtual void	SetText(const CBfc::STRING &csText);
			void Empty();
			void AppendItem(const CBfc::STRING &csItem);
			void SetNumVisible(const int n);
			void SetNumCols(const int n);
		//	bool OnMenuSelection ();
			int (*IsEnabled)();		// button calls this to see if should display or react
			int (*MenuItemHandler)();
			
//			virtual int OnMouseDown (const CBfc::Point2dU &pt);  //
		private:
					};
	
	BFC_GUI_CLASS ListBox: public Data_Resource_Control
					{
		public:
			ListBox (GUI *p_GUI,Window *p_Parent,const Resource_ID resourceID);

			virtual void	SetText(const CBfc::STRING &csText);
			void Empty();
			void AppendItem(const CBfc::STRING &csItem);
			void SetNumVisible(const int n);
		//	bool OnMenuSelection ();
			int (*IsEnabled)();		// button calls this to see if should display or react
			int (*MenuItemHandler)();
		private:
					};
	
	BFC_GUI_CLASS ComboBox: public Data_Resource_Control
					{
		public:
			ComboBox (GUI *p_GUI,Window *p_Parent,const UINT nCols,const Resource_ID resourceID);

			virtual void	SetText(const CBfc::STRING &csText);
			void Empty();
			void AppendItem(const CBfc::STRING &csItem);
		//	bool OnMenuSelection ();
			int (*IsEnabled)();		// button calls this to see if should display or react
			int (*MenuItemHandler)();
		private:
					};


}

