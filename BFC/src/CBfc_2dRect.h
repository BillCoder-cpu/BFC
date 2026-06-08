//*/
/*
					CBfc_2dRect.h : 
	
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
//using System;
/*
	 Rectangle stored internally as doubles (values).
*/

namespace CBfc
{

#define CBfc_2dRect CBfc::Rect2d

BFC_CLASS Rect2d;

BFC_CLASS Rect2dU
{
public:
	Rect2dU () {};
	Rect2dU (const UINT left, const UINT top, const UINT width, const UINT height);
	Rect2dU (const Position2dU &position, const Area2dU &size);
	Rect2dU (const Rect2dU &rect2d);

	void Set (const UINT left, const UINT top, const UINT width, const UINT height);
	void Set (const Position2dU &position, const Area2dU &size);
	void Set (const Rect2dU &rect2d);
	void Set (const Area2dU &size);
	void SetPosition (const Position2dU &position);
	void SetSize (const Area2dU &size);

	void Get (Position2dU &position, Area2dU &size) const;
	void Get (UINT &x, UINT &y, UINT &w, UINT &h) const;
	void GetAbsolute (UINT &xul, UINT &yul, UINT &xlr, UINT &ylr) const;
	Position2dU TopLeft() const;
	Position2dU BottomRight() const;
	Size2dU GetSize(void) const;
	UINT Width(void) const;
	UINT Height(void) const;

	bool Encapsulates (const Rect2dU rect2d) const;
	bool Encapsulates (const Point2dU point2d) const;

	void OR(const Rect2dU &rect);
	void SetWidth(UINT w);
	void SetHeight(UINT h);

	Rect2dU operator*(const double dmul) const;
	Rect2dU operator+(const Rect2dU &AddRect) const;
	void operator = (const Rect2dU &rect2d);
	bool operator == (const Rect2dU &rect2d) const;
private:
	Position2dU		m_position;
	Size2dU		m_size;
};

BFC_CLASS Rect2d
{
public:
    Rect2d () {};
	Rect2d (const Value &left, const Value &top, const Value &width, const Value &height);
	Rect2d (const Position2d &position, const Area2d &size);
    Rect2d (const Rect2d &rect2d);

    void Set (const Value &left, const Value &top, const Value &width, const Value &height);
    void Set (const Position2d &position, const Area2d &size);
    void Set (const Rect2d &rect2d);
    void Set (const Area2d &size);
    void SetPosition (const Position2d &position);
    void SetSize (const Area2d &size);

    void Get (Position2d &position, Area2d &size) const;
    void Get (UINT &x1, UINT &y1, UINT &w, UINT &h) const;
	Position2d TopLeft() const;
	Position2d BottomRight() const;
    Size2d GetSize(void) const;
	Value Width(void) const;
	Value Height(void) const;

    bool Encapsulates (const Rect2d rect2d) const;

    void operator = (const Rect2d &rect2d);
    bool operator == (const Rect2d &rect2d) const;
//    void operator *= (const Rect2d &mulRect2d);
private:
	Position2d	m_position;
    Size2d		m_size;
};

}

