//*/
/*
					CBfc_StreamSource.h : 
	
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

namespace CBfc {

BFC_CLASS CBfc_MemoryBuffer
{
public:
	void Free ();
private:
};


BFC_CLASS StreamSource : public CBfc_ReferencedObject
{
public:
	typedef enum BFC_API tagEBFC_StreamSource {
		EBFC_STREAMSOURCE_FILE,
		EBFC_STREAMSOURCE_MEMORY,
	} EBFC_StreamSource;
public:
	StreamSource (const CBfc_ReferencedObject *p_reference=NULL)
		: CBfc_ReferencedObject(p_reference)
		, m_bOpen(false)
	{}
	virtual ~StreamSource();

	bool Open ();
	bool Close (void);
	virtual bool OpenIt () { return true; }
	virtual bool CloseIt (void) { return true; }
	virtual bool Detach (void) { return true; }
	virtual bool Sleep (void) { return true; }
	virtual bool Awaken (void) { return true; }

    virtual bool			Read (void *dstMem, const unsigned int uCount, unsigned int *p_uBytesRead=NULL) = 0;
    virtual bool			Write (const void *srcMem, const unsigned int uCount, unsigned int *p_uBytesWritten=NULL) = 0;
    virtual bool			Seek(const INT64& n64Offset, const unsigned int uSeekType, __uint64* pun64NewPosition = NULL) = 0;
	virtual unsigned long	FileLength() = 0;
	virtual __uint64		Tell() = 0;
    virtual	bool			Flush() { return true; }

	virtual void*			Dup(void) =0;
	
	EBFC_StreamSource	GetStreamSource() const { return m_streamSource; }
	
protected:
	EBFC_StreamSource			m_streamSource;
	bool						m_bOpen;
};

BFC_CLASS StreamSource_Memory : public StreamSource
{
public:
	StreamSource_Memory (const StreamSource_Memory*);
	StreamSource_Memory (const STRING &s);
	StreamSource_Memory (void *p_memory, const unsigned long ul_memoryByteLength);
	virtual ~StreamSource_Memory();

    virtual bool			Detach (void);
	virtual bool			Seek(const INT64& n64Offset, const unsigned int uSeekType, __uint64* pun64NewPosition = NULL);
	virtual UINT64			Tell();
    virtual bool			Read (void *dstMem, const unsigned int uCount, unsigned int *p_uBytesRead=NULL);
    virtual bool			Write (const void *srcMem, const unsigned int uCount, unsigned int *p_uBytesWritten=NULL);
	virtual unsigned long	FileLength();

	virtual void		*	Dup(void);
protected:
    CBfc_ReferencedAllocation	m_memoryBuffer;
    UINT64						m_n_memoryOffset;
};

BFC_CLASS FileHandle : public CBfc_ReferencedObject
{
public:
	FileHandle();
	FileHandle(const Filename &fn,const bool b_ReadOnly);
	virtual ~FileHandle();
	
	virtual void	*Dup ();
	bool	IsOpen() const;

	bool		Seek(const INT64& n64Offset, const unsigned int uSeekType, __uint64* pun64NewPosition = NULL);
	UINT64      Tell();
	bool        Read (void *dstMem, const unsigned int uCount, unsigned int *p_uBytesRead=NULL);
	bool		Write (const void *srcMem, const unsigned int uCount, unsigned int *p_uBytesWritten=NULL);
		
	void operator = (const FileHandle &copy);

#ifdef	MICROSOFT_WINDOWS
	long FileLength ();
	HFILE	GetFileHandle() const { return m_hFile; }
protected:
	HFILE				m_hFile;		// HANDLE for CreateFile, etc.
#endif
#ifdef UNIX
public:
	INT64 FileLength ();
	FILE				*Get_fp()  const { return m_fp; }
protected:
	FILE  				*m_fp;
#endif
};

BFC_CLASS StreamSource_File : public StreamSource
{
public:
	StreamSource_File (StreamSource_File *);
    StreamSource_File (const CBfc::Filename &filename, const bool b_ReadOnly, const bool b_Temporary=false);
	virtual ~StreamSource_File();

	virtual bool        OpenIt ();
    virtual bool        CloseIt (void);
    virtual bool		Seek(const INT64& n64Offset, const unsigned int uSeekType, __uint64* pun64NewPosition = NULL);
    virtual UINT64      Tell();
    virtual bool        Read (void *dstMem, const unsigned int uCount, unsigned int *p_uBytesRead=NULL);
    virtual bool		Write (const void *srcMem, const unsigned int uCount, unsigned int *p_uBytesWritten=NULL);
	virtual unsigned long	FileLength();

	virtual bool Sleep (void);
	virtual bool Awaken (void);

	virtual void	*	Dup(void);
	
	virtual FileHandle	*	GetFileHandle() { return m_p_fhan; }
	
	void 				GetFilename(STRING &fn) const;
protected:
	bool				m_b_ReadOnly;
	CBfc::Filename		m_filenameSource;
private:
	FileHandle			*m_p_fhan;

	__uint64			m_SleepOffset;	// used for hibernation
	void				SetInternalFlags(const bool b_ReadOnly);
};

}

