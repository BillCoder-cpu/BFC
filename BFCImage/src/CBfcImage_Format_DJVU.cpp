//*/
/*
					CBfcImage_Format_DJVU.cpp : 
	
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

#include <BFC/BFCImage.h>
#include <ddjvuapi.h>		// Requires DJVU library ()

using namespace CBfc;

namespace CBfcImage
{

Image_Format_DJVU::Image_Format_DJVU (const CBfc_Stream *p_Stream)
	: Image_Format (p_Stream)
	, m_p_dynalink(NULL)
{
	m_p_dynalink = new DynamicLink();
	if (!m_p_dynalink->OpenLibrary("libdjvulibre.so"))
		BFC_RELEASE(m_p_dynalink);
}

Image_Format_DJVU::~Image_Format_DJVU()
{
	BFC_RELEASE(m_p_dynalink);
}

/**
 * 
 * @param info 
 * @return 
 */
bool OVERRIDE Image_Format_DJVU :: LoadHeader (Image_Info &info)     // 
{
	bool					b_rVal = false;
	if (m_p_dynalink)
	{
		ddjvu_context_t 		**p_ctx = (ddjvu_context_t**) &m_p_ddjvu_context;
		ddjvu_document_t 		**p_doc = (ddjvu_document_t**) &m_p_ddjvu_document;
		char *flag_pagespec = NULL;
		
		Filename fc;
		((StreamSource_File*)m_p_source)->GetFilename(fc);
		STRING8	s8(fc);
	
		ddjvu_context_t *(*f_ddjvu_context_create)(const char *programname);
		
		f_ddjvu_context_create=(ddjvu_context_t *(*)(const char*))m_p_dynalink->getFunc("ddjvu_context_create");
		if (! (*p_ctx = f_ddjvu_context_create("BFCImage")))			// Create context and document
			return false;

		ddjvu_document_t *(*f_ddjvu_document_create_by_filename)(ddjvu_context_t *context,const char *filename,int cache);
		f_ddjvu_document_create_by_filename = (ddjvu_document_t *(*)(ddjvu_context_t*,const char*,int)) m_p_dynalink->getFunc("ddjvu_document_create_by_filename");
				
		if ((*p_doc = f_ddjvu_document_create_by_filename(*p_ctx, s8.GetPtr8(), TRUE)))
		{
			/*
			while (! ddjvu_document_decoding_done(*p_doc))
				handle(TRUE);
//			int i = ddjvu_document_get_pagenum(*p_doc);		// Process all pages
			dopage (0);
			b_rVal = true;
			
			ddjvu_document_release(*p_doc);				// Close
			*/
		}
		void (*f_ddjvu_context_release)(ddjvu_context_t *context);
		f_ddjvu_context_release = (void(*)(ddjvu_context_t *))m_p_dynalink->getFunc("ddjvu_context_release");
		f_ddjvu_context_release(*p_ctx);
	}
	return b_rVal;
}


/////////////////////////////////////////////////////////
// 
//
/**
 * Assumes bfc_bitmap is of the correct known data type
 * @param rect2d_Load 
 * @param bfc_bitmap 
 * @return 
 */
bool Image_Format_DJVU :: LoadRectangle (const CBfc_2dRect &rect2d_Load, Bitmap &bfc_bitmap)     // virtual
{
//	bfc_bitmap = m_bitstore;
    return true;
}

bool Image_Format_DJVU:: Save (/*const*/ Bitmap &bfc_bitmap)
{
	return false;
}


/* Djvuapi events */

void Image_Format_DJVU::handle(int wait)
{
	const ddjvu_message_t *msg;
	ddjvu_context_t 			**p_ctx = (ddjvu_context_t**) &m_p_ddjvu_context;
	
	if (wait)
	{
		ddjvu_message_t *(*f_ddjvu_message_wait)(ddjvu_context_t *context);
		f_ddjvu_message_wait = (ddjvu_message_t *(*)(ddjvu_context_t *))m_p_dynalink->getFunc("ddjvu_message_wait");
		msg = f_ddjvu_message_wait(*p_ctx);
	}
	
	ddjvu_message_t *(*f_ddjvu_message_peek)(ddjvu_context_t *context);
	f_ddjvu_message_peek = (ddjvu_message_t *(*)(ddjvu_context_t *))m_p_dynalink->getFunc("ddjvu_message_peek");
	while ((msg = f_ddjvu_message_peek(*p_ctx)))
	{
		switch(msg->m_any.tag)
		{
			case DDJVU_ERROR:
				fprintf(stderr,"ddjvu: %s\n", msg->m_error.message);
				if (msg->m_error.filename)
					fprintf(stderr,"ddjvu: '%s:%d'\n", msg->m_error.filename, msg->m_error.lineno);
				exit(10);
			default:
				break;
		}
		void (*f_ddjvu_message_pop)(ddjvu_context_t *context);
		f_ddjvu_message_pop = (void(*)(ddjvu_context_t *))m_p_dynalink->getFunc("ddjvu_message_pop");
		f_ddjvu_message_pop(*p_ctx);
	}
}

void Image_Format_DJVU::dopage(int pageno)
{
/*
	ddjvu_context_t 			**p_ctx = (ddjvu_context_t**) &m_p_ddjvu_context;
	ddjvu_document_t 		**p_doc = (ddjvu_document_t**) &m_p_ddjvu_document;

	ddjvu_page_t *page;
	// Decode page
	timingdata[0] = ticks();
	if (! (page = ddjvu_page_create_by_pageno(*p_doc, pageno-1)))
		die(i18n("Cannot access page %d."), pageno);
	while (! ddjvu_page_decoding_done(page))
		handle(TRUE);
	timingdata[1] = ticks();
	// Open files
	if (flag_format == 't') 
	{
	#if HAVE_TIFF
		if (! tiff) 
		{
			if (! strcmp(outputfilename,"-"))
				die(i18n("Tiff output requires a valid output file name."));
			else if (! (tiff = TIFFOpen(outputfilename, "w")))
				die(i18n("Cannot open output tiff file '%s'."), outputfilename);
		} else 
		{
			if (! TIFFWriteDirectory(tiff))
				die(i18n("Problem writing TIFF directory."));
		}
	#else
		die(i18n("TIFF output is not compiled"));
	#endif
	} else if (! fout) 
	{
		if (! strcmp(outputfilename,"-"))
		{
			fout = stdout;
	#if defined(__CYGWIN32__)
			setmode(fileno(fout), O_BINARY);
	#elif defined(WIN32)
			_setmode(_fileno(fout), _O_BINARY);
	#endif
		} else if (! (fout = fopen(outputfilename, "wb")))
			die(i18n("Cannot open output file '%s'."), outputfilename);
	}
	// Render
	inform(page, pageno);
	render(page);
	ddjvu_page_release(page);
*/
}

/*
void parse_pagespec(const char *s, int max_page, void (*dopage)(int))
{
  static char *err = I18N("invalid page specification: %s");
  int spec = 0;
  int both = 1;
  int start_page = 1;
  int end_page = max_page;
  int pageno;
  char *p = (char*)s;
  while (*p)
    {
      spec = 0;
      while (*p==' ')
        p += 1;
      if (! *p)
        break;
      if (*p>='0' && *p<='9') {
        end_page = strtol(p, &p, 10);
        spec = 1;
      } else if (*p=='$') {
        spec = 1;
        end_page = max_page;
        p += 1;
      } else if (both) {
        end_page = 1;
      } else {
        end_page = max_page;
      }
      while (*p==' ')
        p += 1;
      if (both) {
        start_page = end_page;
        if (*p == '-') {
          p += 1;
          both = 0;
          continue;
        }
      }
      both = 1;
      while (*p==' ')
        p += 1;
      if (*p && *p != ',')
        die(i18n(err), s);
      if (*p == ',')
        p += 1;
      if (! spec)
        die(i18n(err), s);
      if (end_page < 0)
        end_page = 0;
      if (start_page < 0)
        start_page = 0;
      if (end_page > max_page)
        end_page = max_page;
      if (start_page > max_page)
        start_page = max_page;
      if (start_page <= end_page)
        for(pageno=start_page; pageno<=end_page; pageno++)
          (*dopage)(pageno);
      else
        for(pageno=start_page; pageno>=end_page; pageno--)
          (*dopage)(pageno);
    }
  if (! spec)
    die(i18n(err), s);
}
*/


BinaryData* OVERRIDE Image_Format_DJVU :: GetUserDatafield()
{
	return NULL;
}

bool OVERRIDE Image_Format_DJVU ::  SetUserDatafield(BinaryData	*)
{
	return false;
}

bool OVERRIDE Image_Format_DJVU :: GetTag (const STRING &tag, STRING &data)
{
	return false;
}

bool OVERRIDE Image_Format_DJVU :: SetTag (const STRING &tag, const STRING &data)
{
	return false;
}


}

