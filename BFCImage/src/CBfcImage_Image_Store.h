//*/
/*
					CBfcImage_Image_Store.h : 
	
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

namespace CBfcImage
{

BFC_IMAGE_CLASS ScriptImage;

BFC_IMAGE_CLASS	Layer
{
	public:
		Layer(const UINT number, const CBfc::STRING& name)
			:	m_csName(name)
				, m_Number(number)
				{
				}
		UINT				GetNumber() const {
			return m_Number; }
		void		SetNumber(const UINT number) {
					m_Number = number; }
		const CBfc::STRING&	GetName() const {
					return	m_csName; }
		void				SetName(const CBfc::STRING &csName);
	protected:
		UINT				m_Number;
		CBfc::STRING		m_csName;
};


/// Image_Store
/// 	full image buffers with stream support
///   Use this class for working with just simple bitmap images, with no selections or vector objects
BFC_IMAGE_CLASS Image_Store
{
	public:
		Image_Store ();
		Image_Store (const CBfc::Stream &stream);
		friend BFC_IMAGE_CLASS       Image_Buffer;
	public:
		virtual bool		AttachStream(const CBfc::Stream &stream);
		void				Empty();
		
		void				SetModified(const bool bMod) {
							m_b_modified = bMod;	}
		bool				IsModified() const {
							return m_b_modified;	}
		bool				GetImageSize(CBfc::Size2dU &size) const;

		void 				SetNative (const Bitmap *bmp);
		
		bool				SetBitmap (Bitmap *bmp);
		bool				Save (Image_Buffer	*p_buffer);
	public:
		UINT			AddLayer();
		void			EmptyLayer(const UINT uLayer);
		UINT			AvailableLayer() const;
		UINT			NextLayer(const UINT uReferenceLayer) const;
		UINT			PreviousLayer(const UINT uReferenceLayer) const;
		Layer *		LocateLayer(const UINT uLayer) const;
	protected:
		virtual bool		DetermineEntireImageSegment ();
		virtual void		SetSegmentToEntireImage(Image_Segment &seg);
		
		bool				AddBuffer (Image_Buffer *p_buffer);
		Image_Buffer		*ConstructBuffer (Image_Segment * p_segment, Image_EffectsArray &effects);
		Image_Buffer 		*ConstructBuffer (Image_Segment * p_segment, ScriptImage &Script);
	
	protected:
		static	CBfcUtil_Optimization::EBFCU_Optimization	m_e_optimization;
		Image_Info  		m_InfoNative; /// The header of the original data (in the file).
		Image_Segment		m_entire_segment;
	private:
		bool				LoadSegmentBuffer (Image_Segment * p_segment, Image_EffectsArray &effects);
		bool 				LoadSegmentBuffer (Image_Segment * p_segment, ScriptImage &Script);
		Image_Buffer 		*GetCachedBuffer (Image_Segment * p_segment);	/// Try and get a buffer from the cache, only succeeds if already there
		Image_Buffer 		*Load (const Image_Segment * p_segment);		/// Loads (already transformed) segment direct from file
		bool				MakeSegmentBeLoadBalanced (Image_Segment &segment);
		bool				ApplyEffects(Image_Buffer *p_buffer, Image_EffectsArray &effects) const;
	private:
		Image_Format			*m_p_Image_Format;
		CBfc::Array<Image_Buffer*>	m_bufferCache;/// Store up the final buffers
		bool					m_b_modified;
		CBfc::Array<Layer*>		m_Layers;
};

}

