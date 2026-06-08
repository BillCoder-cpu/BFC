//*/
/*
					CBfcImage_Image_Store.cpp : 
	
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
	Note - Image_Store is for more than just 'Images'  any sort of Thing applies.
*/
#include <BFC/BFCImage.h>

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

using namespace CBfc;

namespace CBfcImage
{
// statics
	CBfcUtil_Optimization::EBFCU_Optimization	Image_Store::m_e_optimization = CBfcUtil_Optimization::EBFC_OPTIMIZATION_NOTSET;

/**
 * 
 * @return 
 */
Image_Store::Image_Store ()
	: m_p_Image_Format(NULL)
	, m_b_modified(false)
{
}

/**
 * 
 * @param stream 
 * @return 
 */
Image_Store::Image_Store (const CBfc::Stream &stream)
	: m_p_Image_Format(NULL)
	, m_b_modified(false)
{
	AttachStream(stream);
}

bool Image_Store :: GetImageSize(CBfc::Size2dU &size) const
{
	if (m_p_Image_Format)
		return m_p_Image_Format->GetPage(0)->GetLayer(0)->GetImageSize(size);
	return false;
}


bool Image_Store :: AddBuffer (Image_Buffer *p_buffer)
{
	if (p_buffer)
	{
		m_bufferCache.Add (&p_buffer);
        // Todo: Now, remove any other buffers that this one encapsulates and mark as most recently accessed.
		return true;
	}
	return false;
}

/**
 * 
 * @param p_segment 
 * @param effects 
 * @return 
 */
Image_Buffer * Image_Store :: ConstructBuffer (Image_Segment * p_segment, Image_EffectsArray &effects)
{
	Image_Buffer	*pBuffer = GetCachedBuffer (p_segment);
	if (pBuffer)
		return pBuffer;
	if (LoadSegmentBuffer (p_segment, effects))
		return GetCachedBuffer (p_segment);
	return NULL;
}

Image_Buffer * Image_Store :: ConstructBuffer (Image_Segment * p_segment, ScriptImage &Script)
{
	Image_Buffer	*pBuffer = GetCachedBuffer (p_segment);
	if (pBuffer)
		return pBuffer;
	if (LoadSegmentBuffer (p_segment, Script))
		return GetCachedBuffer (p_segment);
	return NULL;
}

bool Image_Store :: LoadSegmentBuffer (Image_Segment * p_segment, ScriptImage &Script)
{
	Image_Segment	localSegment(*p_segment);
	if (m_e_optimization != CBfcUtil_Optimization::EBFC_OPTIMIZATION_MEMORYINTENSIVE)
		MakeSegmentBeLoadBalanced (localSegment);

	Image_Buffer	*p_buffer = Load (p_segment);
	Script.Process (p_buffer);

	return AddBuffer(p_buffer);
        // Todo: Now, remove any other buffers that this one encapsulates and mark as most recently accessed.
}

/**
 *  Makes sure a given segment is cached.
 * @param p_segment 
 * @param effects 
 * @return 
 */
bool Image_Store :: LoadSegmentBuffer (Image_Segment * p_segment, Image_EffectsArray &effects)
{
	Image_Segment	localSegment(*p_segment);
	if (m_e_optimization != CBfcUtil_Optimization::EBFC_OPTIMIZATION_MEMORYINTENSIVE)
		MakeSegmentBeLoadBalanced (localSegment);

	Image_Buffer	*p_buffer = Load (p_segment);
	ApplyEffects (p_buffer, effects);

	return AddBuffer(p_buffer);
   // Todo: Now, remove any other buffers that this one encapsulates and mark as most recently accessed.
}

// Returns false if full buffer request is not cached.
Image_Buffer * Image_Store :: GetCachedBuffer (Image_Segment * p_segment)
{
	for (unsigned int iIndex=0; iIndex < m_bufferCache.GetCount(); iIndex++)
	{
		Image_Buffer *p_imageBuffer = *(m_bufferCache[iIndex]);
		if (!p_imageBuffer)
		{
			BFC_ASSERT(false,"Image_Store :: GetCachedBuffer");
			return NULL;
		}
		if (p_imageBuffer->GetSegment().EncapsulatesSegment (p_segment))
			return p_imageBuffer->ConstructBuffer (p_segment);
	}
	return NULL;
}

void Image_Store :: Empty()
{
	m_bufferCache.Empty();			// Frees the pointers as it empties the array.
	m_Layers.Empty();
	BFC_RELEASE(m_p_Image_Format);
	SetModified(false);
}

/**
 * 
 * @param p_buffer 
 * @param effects 
 * @return 
 */
bool	Image_Store::ApplyEffects(Image_Buffer *p_buffer, Image_EffectsArray &effects) const
{
	Image_Effect	**p_effect;
	bool		bRval=true;
	
	ULONG		it=effects.StartIteration();
	while ((p_effect = effects.GetNext(it)))
	{
		bRval &= (*p_effect)->ApplyToBuffer(*p_buffer);
	}
	return bRval;
}

/**
 * 
 * @param stream 
 * @return 
 */
bool Image_Store:: AttachStream(const CBfc::Stream &stream)
{
	Empty();
//	m_p_Image_Format = (Image_Format*)new Image_Format_JPEG2000(m_p_app, &stream);
	m_p_Image_Format = (Image_Format*)new Image_Format_JPEG(&stream);
	// read in the header information to set up the colorspace.
	return m_p_Image_Format->LoadHeader(m_InfoNative);
}

void Image_Store::SetNative (const Bitmap *bmp)
{
	m_InfoNative.GetColorSpace() = bmp->GetColorSpace();
//	m_InfoNative.GetResolution() = bmp->GetColorSpace();
}

bool	Image_Store::SetBitmap (Bitmap *bmp)
{
	SetModified(true);
	EmptyLayer (bmp->GetLayer());			// Frees the pointers as it empties the array.
	
	Image_Buffer	*p_buffer=GetCachedBuffer(&m_entire_segment);
	if (!p_buffer)
	{
		p_buffer = new Image_Buffer (&m_InfoNative);
		p_buffer->SetBitmap(bmp, &m_entire_segment);
		return AddBuffer (p_buffer);
	}
	p_buffer->SetBitmap(bmp, &m_entire_segment);
	return true;
}

bool Image_Store :: DetermineEntireImageSegment ()
{
// 	m_entire_segment.Set ();
//  fill me in!
	return false;
}


void Image_Store::SetSegmentToEntireImage(Image_Segment &seg)
{
	seg = m_entire_segment;
//  fill me in!
}

/**
 *  Load direct from file
 * @param p_segment 
 * @return 
 */
Image_Buffer * Image_Store :: Load (const Image_Segment * p_segment)
{
	if (m_p_Image_Format->IsAttached())
	{
		Image_Info	*p_imageInfo = &m_InfoNative;
	
		Image_Buffer	*p_buffer = new Image_Buffer (p_imageInfo);
		if (p_buffer)
		{
			const UINT	uPage=0, uLayer=0;
			Image_Format_Page	*pPage = m_p_Image_Format->GetPage(uPage);
			Image_Format_Layer *pLayer = pPage->GetLayer(uLayer);
			
			p_buffer->LoadBuffer (pLayer, p_segment);
		}

		DetermineEntireImageSegment ();

		return p_buffer;
	}
	return NULL;
}


/**
 * 
 * @param p_segment 
 * @return 
 */
bool		Image_Store :: Save (Image_Buffer	*p_buffer)
{
	if (m_p_Image_Format->IsAttached())
	{
		if (p_buffer)
			return m_p_Image_Format->SaveBuffer (p_buffer);
	}
	return false;
}


// Don't load rediculous settings - move up to next integral dpi, etc.
// If optimization flags are set for speed, just use what they request.
bool Image_Store :: MakeSegmentBeLoadBalanced (Image_Segment &segment)
{
	return true;
}

UINT Image_Store::AddLayer()
{
	const UINT	number = AvailableLayer();
	STRING	name;
	
	name.Format("Layer %d",number);
	Layer	*pLayer = new Layer(number, name);
	m_Layers.Add(&pLayer);
	return number;
}

void Image_Store::EmptyLayer(const UINT uLayer)
{
	for (unsigned int iIndex=0; iIndex < m_bufferCache.GetCount(); iIndex++)
	{
		Image_Buffer *p_imageBuffer = *(m_bufferCache[iIndex]);
		if (!p_imageBuffer->EmptyLayer(uLayer))
		{
			m_bufferCache.RemoveAt(iIndex);
			iIndex--;
		}
	}
}

Layer * Image_Store::LocateLayer(const UINT uLayer) const
{
	ULONG	uIndex = m_Layers.StartIteration();
	Layer	**lpp;
	while ((lpp = m_Layers.GetNext(uIndex)))
		if ((*lpp)->GetNumber() == uLayer)
			return *lpp;
	return NULL;
}

UINT	Image_Store::AvailableLayer() const
{
	UINT	uLayer=1;
	while (LocateLayer(uLayer))
		uLayer++;
	return uLayer;
}

/// Returns the number of the next selection layer
/// Returns 0 if none
UINT	Image_Store::NextLayer(const UINT uReferenceLayer) const
{
	Layer	**lpp;
	UINT	uClosest = -1;
	UINT	uDiff = -1;
	bool bAhead = false;
	ULONG	uIndex = m_Layers.StartIteration();
	while ((lpp = m_Layers.GetNext(uIndex)))
	{
		const UINT	num = (*lpp)->GetNumber();
		if (num > uReferenceLayer)
		{
			bAhead = true;
			if (num - uReferenceLayer < uDiff)
			{
				uClosest = num;
				uDiff = num - uReferenceLayer;
			}
		}
	}
	if (bAhead)
		return uClosest;

	uClosest = -1;
	uIndex = m_Layers.StartIteration();
	while ((lpp = m_Layers.GetNext(uIndex)))
	{
		const UINT	num = (*lpp)->GetNumber();
		if (num && num < uClosest)
			uClosest = num;
	}
	if (uClosest==-1)
		return 0;
	return uClosest;
}

/// Returns the number of the previous selection layer
/// Returns 0 if none
UINT	Image_Store::PreviousLayer(const UINT uReferenceLayer) const
{
	Layer	**lpp;
	UINT	uClosest = -1;
	UINT	uDiff = -1;
	bool	bBehind = false;
	ULONG	uIndex = m_Layers.StartIteration();
	while ((lpp = m_Layers.GetNext(uIndex)))
	{
		const UINT	num = (*lpp)->GetNumber();
		if (num ==0)
			continue;
		if (num < uReferenceLayer)
		{
			bBehind = true;
			if (uReferenceLayer - num< uDiff)
			{
				uClosest = num;
				uDiff = uReferenceLayer - num;
			}
		}
	}
	if (bBehind)
		return uClosest;

	uClosest = 0;
	uIndex = m_Layers.StartIteration();
	while ((lpp = m_Layers.GetNext(uIndex)))
	{
		const UINT	num = (*lpp)->GetNumber();
		if (num > uClosest)
			uClosest = num;
	}
	return uClosest;
}



}


