//*/
/*
					CBfcImage_Color.cpp : 
	
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

#include "BFC/BFCImage.h"

namespace CBfcImage
{

Color::Color()
	: m_b_LAB_set(false)
	, m_Pxl(0xffffff)
{
}

Color::Color(const EBFC_Color eCol)
{
	switch (eCol)
	{
		case WHITE:
			m_Pxl = 0xffffff;
			break;
		case BLACK:
			m_Pxl = 0;
			break;
		case RED:
			m_Pxl = 0xff;
			break;
		case GREEN:
			m_Pxl = 0xff00;
			break;
		case BLUE:
			m_Pxl = 0xff0000;
			break;
		case CYAN:
			m_Pxl = 0xffff00;
			break;
		case MAGENTA:
			m_Pxl = 0xff00ff;
			break;
		case YELLOW:
			m_Pxl = 0xffff;
			break;
		case GREY:
			m_Pxl = 0x808080;
			break;
		case LIGHT_GREY:
			m_Pxl = 0xC0C0C0;
			break;
		case DARK_GREY:
			m_Pxl = 0x404040;
			break;
	}
}

bool Color::SetRGB()
{
	if (m_b_LAB_set)
	{
		unsigned char	r,g,b;
		LABtoRGB (m_L,m_A,m_B,r,g,b);
		m_RGBA.m_r = r;
		m_RGBA.m_g = g;
		m_RGBA.m_b = b;
		return true;
	}
	return false;
}

bool Color::SetLAB()
{
	RGBtoLAB (m_RGBA.m_r, m_RGBA.m_g, m_RGBA.m_b, m_L, m_A, m_B);
	m_b_LAB_set = true;
	return m_b_LAB_set;
}

void Color::SetLAB(const UINT L, const UINT A, const UINT B)
{
	m_L=L;	m_A=A;	m_B=B;
	m_b_LAB_set = true;
	SetRGB();
}

void Color::SplitLAB (UINT &L, UINT &A, UINT &B)
{
	if (!m_b_LAB_set)
		SetLAB();
	L=m_L;	A=m_A;	B=m_B;
}

void Color::SplitHSL (UINT &H, UINT &S, UINT &L) const
{
	unsigned char h,s,l;
	RGBtoHSL (m_RGBA.m_r, m_RGBA.m_g, m_RGBA.m_b, h, s, l);
	H = h;		S = s;		L = l;
}


/// Return a UINT representing how close this color is to this.
/// The lower the value, the closer it is
UINT	Color::Closeness (const Color &c) const
{
	return DELTA(m_RGBA.m_r,c.m_RGBA.m_r)+DELTA(m_RGBA.m_g,c.m_RGBA.m_g)+DELTA(m_RGBA.m_b,c.m_RGBA.m_b);
}

unsigned char Color::GetBrightness()
{
	UINT	L,A,B;
	SplitLAB(L,A,B);
	return L * 255 / 100;
}

void Color::AdjustBrightness (int adjust)
{
	UINT	L,A,B;

	SplitLAB(L,A,B);
	L = L * 255 / 100;
	
	if (adjust < 0)
	{
		if (L < (0-adjust))
			L = 0;
		else
			L += adjust;
	} else
	{
		L += adjust;
		if (L>255)
			L=255;
	}
	L = L * 100 / 255;
	SetLAB (L,A,B);
}

void Color::LABtoRGB (unsigned char L,unsigned char A,unsigned char B,unsigned char &r,unsigned char &g,unsigned char &b)
{
	CLabRgb	convert;
	
	ColorVector3	lab, rgb;
	
	lab.coordinate[0] = (double)L;
	lab.coordinate[1] = (double)A / 255;
	lab.coordinate[2] = (double)B / 255;
	
	convert.LabToRgb (lab, rgb);
	
	r = (unsigned char)(rgb.coordinate[0] * 255);
	g = (unsigned char)(rgb.coordinate[1] * 255);
	b = (unsigned char)(rgb.coordinate[2] * 255);
}

void Color::RGBtoLAB (unsigned char r,unsigned char g,unsigned char b,unsigned char &L,unsigned char &A,unsigned char &B)
{
	CLabRgb	convert;
	
	ColorVector3	lab, rgb;
	
	rgb.coordinate[0] = (double)r / 255;
	rgb.coordinate[1] = (double)g / 255;
	rgb.coordinate[2] = (double)b / 255;
	
	convert.RgbToLab (rgb, lab);
	
	L = (unsigned char)(lab.coordinate[0]);
	A = (unsigned char)(lab.coordinate[1] * 255);
	B = (unsigned char)(lab.coordinate[2] * 255);
}

#include <math.h>

#define TVector3		ColorVector3

ColorMatrix3	CLabRgb::RgbXyz = {{1, 0, 0, 0, 1, 0, 0, 0, 1}};
ColorMatrix3	CLabRgb::XyzRgb = {{1, 0, 0, 0, 1, 0, 0, 0, 1}};

// CCIR recommended values
TVector3		CLabRgb::PhosphorX	= {{0.64, 0.30, 0.15}};
TVector3		CLabRgb::PhosphorY	= {{0.33, 0.60, 0.06}};
TVector3		CLabRgb::WhitePoint = {{0.95, 1.0000, 1.09}};
		
CLabRgb::CLabRgb()
	: m_Gamma ( 1 / 0.45)
{
	InitTransformationMatrices();
}
	
void CLabRgb:: RgbToLab(const TVector3 &Rgb, TVector3 &Result)
{
	TVector3	ir;
	
	RgbToXyz(Rgb, ir);
	XyzToLab(ir, Result);
}

void CLabRgb:: LabToRgb(const TVector3 &Lab, TVector3 &Result)
{
	TVector3	ir;
	
	LabToXyz(Lab, ir);
	XyzToRgb(ir, Result);
}

void CLabRgb::MultiplyMatrix3ByVector3(const ColorMatrix3 &M,  const TVector3 &V, TVector3 &Result)
{
	int	I,J;
	
	for (I=0;I<3;I++)
	{
		Result.coordinate[I] = 0.0;
		for (J=0;J<3;J++)
			Result.coordinate[I] += M.member[I][J] * V.coordinate[J];
	}
}

void CLabRgb:: MultiplyMatrix3ByMatrix3(const ColorMatrix3 &M1, const ColorMatrix3 &M2, ColorMatrix3 &Result)
{
	int I,J,K;
	
	for (I=0; I<3; I++)
		for (J=0; J<3; J++)
		{
			Result.member[I][J] = 0.0;

			for (K=0;K<3;K++)
				Result.member[I][J] = Result.member[I][J] + M1.member[I][K] * M2.member[K][J];
		}
}

void CLabRgb:: InvertMatrix3(const ColorMatrix3 &M, ColorMatrix3 &Result)
{
	int I,J;
	double D=0;

	for (I=0; I<3; I++)
		D = D + M.member[0][I] * (M.member[1][Next(I)] * M.member[2][Prev(I)] - M.member[1][Prev(I)] * M.member[2][Next(I)]);
	
//	memfill(Result, sizeof(Result), 0);
	for (I=0; I<3; I++)
	{
		for (J=0;J<3;J++)
		{
			Result.member[J][I] = (M.member[Next(I)][Next(J)] * M.member[Prev(I)][Prev(J)] - M.member[Next(I)][Prev(J)] * M.member[Prev(I)][Next(J)]) / D;
		}
	}
}

void CLabRgb:: LabToXyz(const TVector3 &Lab, TVector3 &Result)
{
	double	LL = (Lab.coordinate[0] + 16) / 116;
	Result.coordinate[0] = WhitePoint.coordinate[0] * Cube(LL + Lab.coordinate[1] / 500);
	Result.coordinate[1] = WhitePoint.coordinate[1] * Cube(LL);
	Result.coordinate[2] = WhitePoint.coordinate[2] * Cube(LL - Lab.coordinate[2] / 200);
}
	
void CLabRgb:: XyzToRgb(const TVector3 &Xyz, TVector3 &Result)
{
	int	I;
	
	MultiplyMatrix3ByVector3(XyzRgb, Xyz, Result);
	for (I=0; I<3; I++)
	{
		if (Result.coordinate[I] <= 0.0)
			Result.coordinate[I] = 0;
		else 
			Result.coordinate[I] = exp(log(Result.coordinate[I]) / m_Gamma);
	}
}

void CLabRgb:: RgbToXyz(const TVector3 &Rgb, TVector3 &Result)
{
	int	I;
	
	TVector3 cr = Rgb;
	for (I=0; I<3; I++)
	{
		if (cr.coordinate[I] <= 0.0)
			cr.coordinate[I] = 0;
		else 
			cr.coordinate[I] = exp(log(cr.coordinate[I]) * m_Gamma);
	}
	MultiplyMatrix3ByVector3(RgbXyz, cr, Result);
}

void CLabRgb::XyzToLab(const TVector3 &Xyz, TVector3 &Result)
{
	double	YY = CubeRoot(Xyz.coordinate[1] / WhitePoint.coordinate[1]);
	
	Result.coordinate[0] = 116 * YY - 16;
	Result.coordinate[1] = 500 * (CubeRoot(Xyz.coordinate[0] / WhitePoint.coordinate[0]) - YY);
	Result.coordinate[2] = 200 * (YY - CubeRoot(Xyz.coordinate[2] / WhitePoint.coordinate[2]));
}

int CLabRgb::Next(const int I)
{
	int Result = I + 1;
	if (Result > 2)
		Result = Result - 3;
	return Result;
}

int CLabRgb::Prev(const int I)
{
	int Result = I - 1;
	if (Result < 0)
		Result = Result + 3;
	return Result;
}

void CLabRgb::InitTransformationMatrices ()
{
	int				I,J;
	TVector3		C;
	ColorMatrix3	CToXyz, XyzToC;
		
	for (I=0; I<3; I++)
	{
		CToXyz.member[0][I] = PhosphorX.coordinate[I];
		CToXyz.member[1][I] = PhosphorY.coordinate[I];
		CToXyz.member[2][I] = 1 - PhosphorX.coordinate[I] - PhosphorY.coordinate[I];
	}
				
	InvertMatrix3(CToXyz, XyzToC);
	MultiplyMatrix3ByVector3(XyzToC, WhitePoint, C);
	
	for (I=0; I<3;I++)
		for (J=0;J<3;J++)
			RgbXyz.member[I][J] = CToXyz.member[I][J] * C.coordinate[J];

	InvertMatrix3(RgbXyz, XyzRgb);
}



double CLabRgb::CubeRoot(const double X)
{
	if (X >= (216 / 24389))
		return exp(log(X) / 3);
	else
		return (841 / 108) * X + (4 / 29);
}

double CLabRgb::Cube(const double X)
{
	if (X >= (6 / 29))
		return X * X * X;
	else
		return (108 / 841) * (X - (4 / 29));
}



///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
/*
HSLtoRGB (unsigned char H, unsigned char S, unsigned char L, unsigned char &R unsigned char &G, unsigned char &B)
{ 
	if (L<=0.5)
		: PUT l*(s+1) IN m2
	ELSE: PUT l+s-l*s IN m2
	PUT l*2-m2 IN m1
	PUT hue.to.rgb(m1, m2, h+1/3) IN r
	PUT hue.to.rgb(m1, m2, h    ) IN g
	PUT hue.to.rgb(m1, m2, h-1/3) IN b
	RETURN (r, g, b)

    HOW TO RETURN hue.to.rgb(m1, m2, h): 
			IF h<0: PUT h+1 IN h
			IF h>1: PUT h-1 IN h
			IF h*6<1: RETURN m1+(m2-m1)*h*6
			IF h*2<1: RETURN m2
			IF h*3<2: RETURN m1+(m2-m1)*(2/3-h)*6
			RETURN m1
*/

#if 0
void Color::RGBtoHSL (unsigned char R,unsigned char G,unsigned char B,unsigned char &H,unsigned char &S,unsigned char &L)
{
	double	dRed, dGreen, dBlue;
	double	dMax, dMin;
	double	dHue, dSat, dLum;
    
	dRed = (double)R / 255;
	dGreen = (double)G / 255;
	dBlue = (double)B / 255;
   
	if (R > G)
	{
		if (R > B)
			dMax = dRed;
		else
			dMax = dBlue;
		if (G < B)
			dMin = dGreen;
		else
			dMin = dBlue;
	} else if (G > B)
	{
		dMax = dGreen;
		if (R < B)
			dMin = dRed;
		else
			dMin = dBlue;
	} else
	{
		dMax = dBlue;
		dMin = dGreen;
	}
	dLum = (dMax + dMin) / 2;
   
	if (dMax == dMin)
	{
		dSat = 0;
		dHue = 0;
	} else
	{
		if (dLum < 0.5)
			dSat = (dMax - dMin) / (dMax + dMin);
		else
			dSat = (dMax - dMin) / (2 - dMax - dMin);
        
		if (dMax == dRed)
			dHue = (dGreen - dBlue) / (dMax - dMin);
		else if (dMax == dGreen)
			dHue = 2 + (dBlue - dRed) / (dMax - dMin);
		else
			dHue = 4 + (dRed - dGreen) / (dMax - dMin);
	}

	if (dHue < 0)
		H = 240 + (dHue * 239 / 6);
	else
		H = dHue * 239 / 6;
    
	S = (dSat * 239);
	L = (dLum * 239);
}

void Color::RGBtoHSL (unsigned char R,unsigned char G,unsigned char B,unsigned char &H,unsigned char &S,unsigned char &L)
{
	double	dRed, dGreen, dBlue;
	double	dMax, dMin;
	double	dHue, dSat, dLum;
	double	dDelta;
    
	dRed = (double)R / 255;
	dGreen = (double)G / 255;
	dBlue = (double)B / 255;
   
	if (R > G)
{
		if (R > B)
			dMax = dRed;
		else
			dMax = dBlue;
		if (G < B)
			dMin = dGreen;
		else
			dMin = dBlue;
} else if (G > B)
{
		dMax = dGreen;
		if (R < B)
			dMin = dRed;
		else
			dMin = dBlue;
} else
{
		dMax = dBlue;
		dMin = dGreen;
}
	dLum = (dMax + dMin) / 2;
   
	dDelta = (dMax-dMin);
	if (dDelta == 0)
{
		dSat = 0;
		dHue = 0;
} else
{
		dSat =  dDelta / dMax;
		if (dRed == dMax)
{
			dHue = (dGreen - dBlue) / dDelta;
			if (dHue < 0.0)
				dHue += 6.0;
}
		else if (dGreen == dMax)
{
			dHue = 2.0 + (dBlue - dRed) / dDelta;
}
		else
{
			dHue = 4.0 + (dRed - dGreen) / dDelta;
}
		dHue /= 6.0;
}

// 	H = (dHue * 239);
// 	S = (dSat * 239);
// 	L = (dLum * 239);
	
	H = (dHue * 255);
	S = (dSat * 255);
	L = (dLum * 255);
}

#else
void Color::RGBtoHSL (unsigned char R,unsigned char G,unsigned char B,unsigned char &H,unsigned char &S,unsigned char &L)
{
	int		vMax,vMin,vDelta;
	double	dHue;
	if (R > G)
	{
		if (R > B) vMax = R;
			else vMax = B;

		if (G < B) vMin = G;
			else vMin = B;
	} else if (G > B)
	{
		vMax = G;
		if (R < B) vMin = R;
			else vMin = B;
	} else
	{
		vMax = B;
		vMin = G;
	}
	L = (vMax + vMin) / 2;
   
	vDelta = (vMax-vMin);
	if (vDelta == 0)
	{
		H=S=0;
	} else
	{
		S =  (255 * vDelta) / vMax;
		if (R == vMax)
		{
			dHue = ((int)G - B) / vDelta;
			if (dHue < 0.0)
				dHue += 6.0;
			
			dHue = 6;
		} else if (G == vMax)
		{
			dHue = B;
			dHue -= R;
			dHue /= vDelta;
			dHue += 2.0;
// 			dHue = 2.0 + ((int)B - R) / vDelta;
		} else
		{
			dHue = 4.0 + ((int)R - G) / vDelta;
			
			dHue = 6;

		}
		dHue *= 42.5;		// / 6.0 * 255;		// 	H = (dHue * 239);
		H = (dHue);
	}
}


#endif

/*
uchar Color::RGBtoHighHue (unsigned char R,unsigned char G,unsigned char B)
{
	uchar	HighHue;
	float	dRed, dGreen, dBlue;
	float	dMax, dMin;
	float	dHue, dSat, dLum;
    
	dRed = (float)R / 255;
	dGreen = (float)G / 255;
	dBlue = (float)B / 255;
   
	if (R > G)
	{
		if (R > B)
			dMax = dRed;
		else
			dMax = dBlue;
		if (G < B)
			dMin = dGreen;
		else
			dMin = dBlue;
	} else if (G > B)
	{
		dMax = dGreen;
		if (R < B)
			dMin = dRed;
		else
			dMin = dBlue;
	} else
	{
		dMax = dBlue;
		dMin = dGreen;
	}
	dLum = (dMax + dMin) / 2;
   
	
	if (dMax == dMin)
	{
		dSat = 0;
		dHue = 0;
	} else
	{
		if (dLum < 0.5)
			dSat = (dMax - dMin) / (dMax + dMin);
		else
			dSat = (dMax - dMin) / (2 - dMax - dMin);
        
		if (dMax == dRed)
			dHue = (dGreen - dBlue) / (dMax - dMin);
		else if (dMax == dGreen)
			dHue = 2 + (dBlue - dRed) / (dMax - dMin);
		else
			dHue = 4 + (dRed - dGreen) / (dMax - dMin);
	}

	return HighHue;
	if (dHue < 0)
		H = 240 + (dHue * 239 / 6);
	else
		H = dHue * 239 / 6;

*/

}

