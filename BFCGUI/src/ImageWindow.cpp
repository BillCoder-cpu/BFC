//*/
/*
					ImageWindow.cpp : 
	
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

namespace CBfcGUI
{
/**
 * 
 * @return 
 */
ImageWindow :: ImageWindow (GUI *p_GUI, CBfcImage::Image *p_Image, Window *p_Parent)
	:  ImageWindow_GUIBase (p_GUI, "Image", WND_TOP, p_Parent)
		, m_zoom(1)
		, m_p_Image(p_Image)
{
	SetDefaultCursor(CURSOR_MOVE);
}


void ImageWindow::SetImage(CBfcImage::Image *p_Image)
{
	m_p_Image = p_Image;
	Dirty();
}

/**
bool ImageWindow::Open(const Stream &stream)
{
	if (m_p_Image->AttachStream(stream))
	{
		OptimizeLook ();
		return true;
	}
	return false;
}
*/

void ImageWindow::OptimizeLook()
{
	if (m_p_Image)
	{
		static Position2dU	GoodPos(0,20);
		const	Position2dU		MaxPos(640,480);
		const Position2dU		PosChange(40,50);
		const Size2dU		GoodSize (500,380);
		
		GoodPos += PosChange;
		if (GoodPos > MaxPos)
			GoodPos.Set (Position2dU(0,20)+PosChange);
		SetWindowPosition(GoodPos);
		SetWindowSize(GoodSize);
		
		Size2dU	size;
		
		if (m_p_Image->GetImageSize(size))
			m_zoom = GoodSize.GetX() / size.GetX();
// 	BFC_TRACE (_TXT("Optimize: image size (%d x %d)\n"), size.GetX(), size.GetY());
		if (m_zoom == 0) m_zoom = 1;
		Dirty();
	}
}

/**
 * 
 * @param stream 
 * @return 
 */
bool ImageWindow::Save(const Stream &stream)
{
	if (m_p_Image->AttachStream(stream))
	{
		const CBfcImage::Image_Segment *pSeg=NULL;
		return m_p_Image->Save(pSeg);
	}
	return false;
}

/**
 * 
 * @param rect2d 
 * @return 
 */
int ImageWindow::OnPaint(const CBfc::Rect2dU &paint_rect)
{
	CBfcImage::Image_Buffer   		*pBuf;
	const CBfcImage::Image_Segment	*pSeg=NULL;
	
	if (m_zoom == 0)
		return false;
	if ((pBuf = m_p_Image->GetBuffer(pSeg)))
	{
		CBfcImage::Bitmap	*pBmp = pBuf->GetBitmap();
		if (pBmp)
			DrawBitmap (pBmp, paint_rect, m_origin, m_zoom);
	// do not delete this pBuf, we only have  copy that is active as long as the ImageWindow::Image Exists
	// later, really should add mechanism to count instances of it and tell the image when we are done with it.
	// now, it's a memory leak i think!
		return true;
	} else
		return ImageWindow_GUIBase::OnPaint(paint_rect);
}

void ImageWindow::ZoomIn()
{
	m_zoom *= 1.25;
	Dirty();
}

void ImageWindow::ZoomOut()
{
	m_zoom	/= 1.25;
	Dirty();
}


Point2dU ImageWindow::ScreenToImage	(const Point2dU pointScreen) const
{
	const Point2dU	pointImage(m_origin + (pointScreen/GetZoom()));
	return pointImage;
}

CBfcImage::Bitmap *ImageWindow::GetBitmap (const UINT uLayer)
{
	CBfcImage::Image_Buffer   *pBuf;
	const CBfcImage::Image_Segment *pSeg=NULL;

	if ((pBuf = m_p_Image->GetBuffer(pSeg)))
		return pBuf->GetBitmap(uLayer);
	return NULL;
}

UINT	ImageWindow::LayerUnderPoint(const CBfc::Point2dU &pointWin)
{
	const Point2dU pointImage(ScreenToImage(pointWin));
	UINT	uNextLayer = m_p_Image->m_uSelectionLayer;

	do {
		CBfcImage::Bitmap *pBmp = GetBitmap(uNextLayer);
		if (pBmp)
		{
			Rect2dU	r;
			pBmp->GetRect(r);
			if (r.Encapsulates(pointImage))
			{
				const CBfcImage::Bitmap_Alpha	*pAlpha = pBmp->GetAlpha();
				if (pAlpha)
				{
					if ((*pAlpha)[pointImage-r.TopLeft()])
						return uNextLayer;
				} else
					return uNextLayer;
			}
		// check to see if it contains the point
		}		
		uNextLayer = m_p_Image->NextLayer(uNextLayer);
	} while (uNextLayer != m_p_Image->m_uSelectionLayer);
	return 0;
}


/**
 * 
 * @param csOperation - An Image Script command set that has been (or is to be!) applied to the image
 * @return 
 */
bool ImageWindow::RegisterOperation (const STRING &csOperation)
{
	// This info is saved inside of the image itself.
	// The undo mechanics can be here, but the record must be in the image because
	// this window's image can be re-assigned.
	m_p_Image->SetModified(true);
	return true;
}
		
		
}




