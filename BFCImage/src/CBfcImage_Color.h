//*/
/*
					CBfcImage_Color.h : 
	
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

BFC_IMAGE_CLASS Color 
{
public:
	typedef enum BFC_API tagEBFC_Color {
	    	WHITE=0,	BLACK,			RED,	GREEN,	BLUE,
		CYAN,		MAGENTA,		YELLOW,
		GREY,		LIGHT_GREY,	DARK_GREY,
	} EBFC_Color;
		
	Color ();
	Color (const EBFC_Color eCol);
public:
	inline void operator	=		(const Color &c);
	inline bool operator	!=		(const Color &c) const;
	inline bool operator	==	(const Color &c) const;
	
	inline void CopyRGB (BYTE *srcptr);
	inline void SetRGB (const UINT r, const UINT g, const UINT b);
	
	inline void CopyRGBA (BYTE *srcptr);
	inline void SetRGBA (const UINT rgba);
	inline void SetGrey (const UINT g);
	inline void SetRGBA (const UINT r, const UINT g, const UINT b, const UINT a);
	
	inline void SplitRGB (UINT &r, UINT &g, UINT &b) const;
	inline void SplitRGBA (UINT &r, UINT &g, UINT &b, UINT &a) const;
	
	inline void TakeDelta(const Color &c);

	inline UINT			GetAs24BitRGB() const;
	inline unsigned short	GetAs16BitRGB() const;
	inline void			Set16bitRGB(const unsigned short us);
	
	void SetLAB (const UINT L, const UINT A, const UINT B);
	void SplitLAB (UINT &L, UINT &A, UINT &B);
	void SplitHSL (UINT &H, UINT &S, UINT &L) const;
	bool SetRGB ();
	bool SetLAB ();
	
	static void LABtoRGB (unsigned char L,unsigned char A,unsigned char B,unsigned char &r,unsigned char &g,unsigned char &b);
	static void RGBtoLAB (unsigned char r,unsigned char g,unsigned char b,unsigned char &L,unsigned char &A,unsigned char &B);
	static void RGBtoHSL (unsigned char R,unsigned char G,unsigned char B,unsigned char &H,unsigned char &S,unsigned char &L);

	unsigned char	GetBrightness();
	void			AdjustBrightness (int adjust);

	UINT			Closeness (const Color &c) const;

protected:
private:
	ColorSpace::EBFC_ColorSpace	m_e_colorSpace;
	union {
		 ULONG				m_Pxl;	// FSL may need more data than this!!!!
		 struct {
			 unsigned char		m_r, m_g, m_b, m_a;
		 } m_RGBA;
	};
	unsigned char			m_L, m_A, m_B;
	bool					m_b_LAB_set;
};

typedef struct { double coordinate[3]; }		ColorVector3;
typedef struct { double	member[3][3]; }	ColorMatrix3;
	
BFC_IMAGE_CLASS CLabRgb
{
	public:
		CLabRgb();
		void	LabToRgb (const ColorVector3 &Lab, ColorVector3 &Rgb);
		void	RgbToLab (const ColorVector3 &Rgb, ColorVector3 &Lab);
	protected:
		void	MultiplyMatrix3ByVector3 (const ColorMatrix3 &M,  const ColorVector3 &V, ColorVector3 &Result);
		void  MultiplyMatrix3ByMatrix3 (const ColorMatrix3 &M1, const ColorMatrix3 &M2, ColorMatrix3 &Result);
		void  InvertMatrix3 (const ColorMatrix3 &M, ColorMatrix3 &Result);
		void  LabToXyz (const ColorVector3 &Lab, ColorVector3 &Result);
		void  XyzToRgb (const ColorVector3 &Xyz, ColorVector3 &Result);
		void  RgbToXyz (const ColorVector3 &Rgb, ColorVector3 &Result);
		void	XyzToLab (const ColorVector3 &Xyz, ColorVector3 &Result);
		int	Next	(const int I);
		int	Prev	(const int I);
		void	InitTransformationMatrices ();
		double CubeRoot	(const double X);
		double Cube		(const double X);
	private:		
		static ColorMatrix3	RgbXyz;
		static ColorMatrix3	XyzRgb;
		
		static ColorVector3	PhosphorX;
		static ColorVector3	PhosphorY;
		static ColorVector3	WhitePoint;
		double			m_Gamma;
};


void Color::SetRGB (const UINT r, const UINT g, const UINT b)
{
	m_RGBA.m_r = r;
	m_RGBA.m_g = g;
	m_RGBA.m_b = b;
	m_RGBA.m_a = 0;
	m_b_LAB_set = false;
//	m_e_colorSpace = ColorSpace::COLORSPACE_RGB;
}

void Color::CopyRGB (BYTE *srcptr)
{
	m_RGBA.m_r = *srcptr++;
	m_RGBA.m_g = *srcptr++;
	m_RGBA.m_b = *srcptr;
	m_RGBA.m_a = 0;
	m_b_LAB_set = false;
}

void Color::CopyRGBA (BYTE *srcptr)
{
	m_RGBA.m_r = *srcptr++;
	m_RGBA.m_g = *srcptr++;
	m_RGBA.m_b = *srcptr++;
	m_RGBA.m_a = *srcptr;
	m_b_LAB_set = false;
}

void	Color::SetRGBA(const UINT rgba)
{
	m_Pxl = rgba;
	m_b_LAB_set = false;
}

void Color::SetGrey (const UINT g)
{
	m_RGBA.m_r = m_RGBA.m_g = m_RGBA.m_b = g;
}

void Color::SetRGBA (const UINT r, const UINT g, const UINT b, const UINT a)
{
	m_RGBA.m_r = r;
	m_RGBA.m_g = g;
	m_RGBA.m_b = b;
	m_RGBA.m_a = a;
	m_b_LAB_set = false;
//	m_e_colorSpace = ColorSpace::COLORSPACE_RGBA;
}

void Color::SplitRGB (UINT &r, UINT &g, UINT &b) const
{
	r = m_RGBA.m_r;
	g = m_RGBA.m_g;
	b = m_RGBA.m_b;
}

void Color::SplitRGBA (UINT &r, UINT &g, UINT &b, UINT &a) const
{
	r = m_RGBA.m_r;
	g = m_RGBA.m_g;
	b = m_RGBA.m_b;
	a = m_RGBA.m_a;
}

UINT	Color::GetAs24BitRGB() const
{
	return m_Pxl & 0xffffff;
}

unsigned short Color::GetAs16BitRGB() const
{
	return (((UINT)(m_RGBA.m_r&0xf8)) << 7) | (((UINT)(m_RGBA.m_g&0xf8)) << 2) | (UINT)(m_RGBA.m_b>>3);
}

void Color::Set16bitRGB(const unsigned short us)
{
	SetRGB  ((us >> 7) & 0xf8, (us >> 2)&0xf8 , (us << 3)&0xff);
}

void Color::operator = (const Color &c)
{
	m_e_colorSpace = c.m_e_colorSpace;
	m_Pxl = c.m_Pxl;
	m_L = c.m_L; 	m_A = c.m_A;	m_B = c.m_B;
	m_b_LAB_set = c.m_b_LAB_set;
}


bool Color :: operator != (const Color &c) const
{
	return !(*this == c);
}

/// needs work - ok for now
bool Color :: operator == (const Color &c) const
{
	if (c.m_Pxl != m_Pxl || c.m_e_colorSpace != m_e_colorSpace)
		return false;
	return true;
}


void Color :: TakeDelta(const Color &c)
{
	m_RGBA.m_r = DELTA(m_RGBA.m_r, c.m_RGBA.m_r);
	m_RGBA.m_g = DELTA(m_RGBA.m_g, c.m_RGBA.m_g);
	m_RGBA.m_b = DELTA(m_RGBA.m_b, c.m_RGBA.m_b);
	m_b_LAB_set = false;
}


}

