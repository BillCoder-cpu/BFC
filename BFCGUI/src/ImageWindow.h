//*/
/*
					ImageWindow.h : 
	
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
	
// #define ImageWindow_GUIBase CBfcGUI::DialogWindow
#define ImageWindow_GUIBase CBfcGUI::MenuWindow

class ImageWindow : public ImageWindow_GUIBase
{
	public:
		ImageWindow (GUI *p_GUI, CBfcImage::Image *p_Image=NULL, Window *p_Parent=NULL);
// 		ImageWindow (GUI *p_GUI, const STRING &ResourceName, Window *p_Parent=NULL, ResourceStore *p_ResourceStore=NULL);
	public:
// 		bool Open(const Stream &stream);
		void 			SetImage(CBfcImage::Image *p_Image);
		
		CBfcImage::Image	*GetImage() const
					{ return m_p_Image; }
		bool 			Save(const Stream &stream);
		
		void 			ZoomIn();
		void 			ZoomOut();
		UINT			LayerUnderPoint(const CBfc::Point2dU &pointScreen);
		Point2dU 		ScreenToImage	(const Point2dU pointScreen) const;

		void			OptimizeLook();
		double		GetZoom() const { return m_zoom; }
		Position2dU 	GetOrigin() const { return m_origin; }
	protected:
		virtual int		OnPaint(const CBfc::Rect2dU &paint_rect);
		
	protected:
		CBfcImage::Bitmap	*GetBitmap(const UINT uLayer=(UINT)ALL_LAYERS);
	protected:
		bool			RegisterOperation (const STRING &csOperation);
				
		Position2dU		m_origin;
		CBfcImage::Image	*m_p_Image;
	private:
		double		m_zoom;
	private:
};

}



