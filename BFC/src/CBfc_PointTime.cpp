//*/
/*
					CBfc_PointTime.cpp : 
	
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

#include <BFC/BFC.h>

#ifdef UNIX
#	include <time.h>
#endif
#ifdef WIN32
#	include <windows.h>
#endif

namespace CBfc {

#define Moment PointTime

bool Moment ::SetDate (WORD w_Month, WORD w_Day, WORD w_Year)
{
	m_wYear = w_Year;
	m_wMonth = WITHIN(w_Month,1,12);
	m_wDay = WITHIN(w_Day,1,31);
	return true;
}

bool Moment::SetTime (WORD w_Hour, WORD w_Minute, WORD w_Second, WORD w_Millisecond)
{
	m_wHour = WITHIN(w_Hour, 0, 24);
	m_wMinute = WITHIN(w_Minute, 0, 60);
	m_wSecond = WITHIN(w_Second, 0, 60);
	m_wMillisecond = WITHIN(w_Millisecond, 0, 1000);
	return true;
}

// Fill in the currentlocal time into the class data
void Moment ::SetToLocalTime()
{
#ifdef UNIX
	time_t		storetime;
	struct tm*	p_timerep;
	
	time(&storetime);
	p_timerep = localtime(&storetime);
	
	m_wYear = p_timerep->tm_year;
	m_wMonth = p_timerep->tm_mon;
	m_wDay = p_timerep->tm_mday;
 	m_wHour = p_timerep->tm_hour;	
	m_wMinute = p_timerep->tm_min;			/* Minutes.	[0-59] */
	m_wSecond = p_timerep->tm_sec;			/* Seconds.	[0-60] (1 leap second) */
	m_wMillisecond = 0;
	m_wDayOfWeek = p_timerep->tm_wday;
	
#endif
#ifdef WIN32
	SYSTEMTIME systime;

	::GetSystemTime(&systime);
	m_wYear = systime.wYear;
	m_wMonth = systime.wMonth;
	m_wDay = systime.wDay;
#endif
}


UINT Moment ::GetYear() const
{
	return (UINT)m_wYear;
}

}



