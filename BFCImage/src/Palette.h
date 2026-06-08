//*/
/*
					Palette.h : 
	
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
	
	BFC_IMAGE_CLASS Bitmap;
			
	extern bool GeneratePalette (const Bitmap *pBmp,UINT *palFill,const UINT uPalsize,const CBfc::Rect2dU *pRect=NULL);

#define	MAXPAL	256		/// Get rid of this hardcode for sure later
	
	BFC_IMAGE_CLASS	Palette
	{
		public:
			Palette();
			Palette(const Palette *p_paldup);
			
			Palette *Dup() const;
			
			UINT	GetNumberOfColors() const { return m_uColorCount; }
			bool	Generate(const Bitmap *pBmp,const UINT uPalsize, const CBfc::Rect2dU *pRect=NULL);
			Color	GetColor (const UINT uIndex) const;
			void	GetColor (const UINT uIndex, Color &c) const;
			
			UINT	ColorToIndex (const Color &c) const;
		protected:
		private:
			UINT	m_uColorCount;
			UINT	m_uColors[MAXPAL];
	};

	BFC_IMAGE_CLASS	PaletteCounter : public Palette
	{
		public:
			PaletteCounter (const Palette *p_palette=NULL);
			
			void IncrementSample(const UINT uColor);
			bool GetPrimaryColor(Color &c) const;
		private:
			UINT			m_Occurance[MAXPAL];
	};
}
