//*/
/*
					CBfc_Stream.h : 
	
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

#ifndef _BFC_BCSTREAM_H_
#define  _BFC_BCSTREAM_H_

#include "CBfc_StreamSource.h"

namespace CBfc {

BFC_CLASS StreamThreadInfo
{
public:
	bool    m_b_threaded;
//	HANDLE	m_h_eventRead;			// Event for multi-threaded case
};

#define CBfc_Stream CBfc::Stream

//      Streams.   Read from the stream with a separate thread for better thouroughput
BFC_CLASS Stream : public CBfc_Object
{
public:
	Stream (const CBfc_Stream &bfc_stream, const bool b_threaded=false);
	Stream (const bool b_threaded=false);
	Stream (const CBfc::Filename &bfc_filename,const bool b_ReadOnly=true, const bool b_threaded=false);
	virtual ~Stream();

	bool Detach (void);
	bool CreateAFile (const CBfc::Filename &filename);
	bool AppendToFile (const CBfc::Filename &filename);
	bool AttachFile (const CBfc::Filename &filename, const bool b_ReadOnly=true);
	bool AttachStream(const CBfc_Stream &stream);
	bool AttachMemory (void *p_memory, const unsigned long ul_memoryByteLength);
	inline bool IsAttached (void) const {
		return m_b_attached;
	}
	bool GetFilename(STRING &csFilename) const;

	CBfc::FileHandle *GetFileHandle();

	virtual inline bool Seek(const INT64& n64Offset, const unsigned long& ulOrigin, __uint64* pun64NewPosition = NULL)
				{
					return m_p_source->Seek (n64Offset, ulOrigin, pun64NewPosition);
				}

	virtual inline bool Rewind()
				{
					const unsigned long ulOrigin = 0;
					return Seek(0,ulOrigin);
				}

	virtual inline __uint64	Tell()
				{
					return m_p_source->Tell ();
				}

	inline bool Flush()
				{
					return m_p_source->Flush ();
				}

	inline bool Open ()
				{
					return m_p_source->Open ();
				}
	inline bool Close ()
				{
					if (IsAttached())
						return m_p_source->Close ();
					return true;
				}
	bool ReadAhead (void *dstMem, const unsigned int uCount, unsigned int *p_uBytesRead=NULL);
	inline bool Read (void *dstMem, const unsigned int uCount, unsigned int *p_uBytesRead=NULL)
				{
					return m_p_source->Read (dstMem, uCount, p_uBytesRead);
				}
	inline bool Write (void *srcMem, const unsigned int uCount, unsigned int *p_uBytesWritten=NULL)
				{
					return m_p_source->Write (srcMem, uCount, p_uBytesWritten);
				}
	inline bool Write (const CBfc_String &cs)
				{
					return m_p_source->Write (cs.GetPtr(), cs.GetLengthBytes(), NULL);
				}
	bool AppendStream (CBfc_Stream &stream);

	void operator = (const CBfc_Stream &stream); 
protected:
	virtual bool 				OnAttach();
			
	bool							m_b_attached;
	StreamSource               	*	m_p_source;
	bool                        	m_bReadOnly;

	StreamThreadInfo				m_ThreadInfo;
	bool							m_b_threaded;			//
	CBfc_CompressionAlgorythm	*	m_p_CompressionAlgorythm;
private:
};

}

#endif // define  _BFC_BCSTREAM_H_

