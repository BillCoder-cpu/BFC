//*/
/*
					CBfcImage_Format_JPEG.cpp : 
	
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
#undef UNIX
#ifdef UNIX
#include <jpeglib.h>
#endif
#include <setjmp.h>

namespace CBfcImage
{

using namespace CBfc;

#ifdef UNIX
struct my_error_mgr 
{
  struct jpeg_error_mgr pub;	/* "public" fields */
  jmp_buf setjmp_buffer;	/* for return to caller */
};
typedef struct my_error_mgr * my_error_ptr;
static void	my_error_exit (j_common_ptr cinfo);
#endif

/**
 * 
 * @param p_Stream 
 * @return 
 */
Image_Format_JPEG::Image_Format_JPEG (const CBfc_Stream *p_Stream)
  : Image_Format (p_Stream)
	, m_p_info(NULL)
	, m_p_error_mgr(NULL)
	, m_i_quality(100)
	, m_Page(this)
{
#ifdef UNIX
	m_p_error_mgr = new (struct my_error_mgr);
#endif
}

/**
 * 
 * @return 
 */
Image_Format_JPEG::~Image_Format_JPEG()
{
#ifdef UNIX
	if (m_p_info)
	{
		j_decompress_ptr p_info = (j_decompress_ptr)m_p_info;
		jpeg_destroy_decompress(p_info);
		delete p_info;
		m_p_info=NULL;
	}
	if (m_p_error_mgr)
	{
		my_error_ptr 	p_jerr;
		p_jerr = (my_error_ptr)m_p_error_mgr;
		delete p_jerr;
		m_p_error_mgr = NULL;
	}
#endif
}

OVERRIDE Image_Format_Page *Image_Format_JPEG::GetPage(const UINT uPage)
{
	return &m_Page;
}

OVERRIDE Image_Format_Layer *Image_Format_Page_JPEG::GetLayer(const UINT uLayer)
{
	m_Layer.SetLayerNumber(uLayer);
#ifdef UNIX
	j_decompress_ptr		p_info = (j_decompress_ptr)(GetFormat()->m_p_info);
	if (p_info)
	{
		const UINT ww=p_info->image_width;
		const UINT hh=p_info->image_height;
		const Size2dU	size (ww,hh);
		m_Layer.SetImageSize(size);
	}
#endif
	return &m_Layer;
}

void Image_Format_JPEG :: SetQuality (int i_quality)
{
	m_i_quality = i_quality;
}

/**
 * 
 * @param info 
 * @return 
 */
OVERRIDE bool Image_Format_JPEG :: LoadHeader (Image_Info &info)
{
	if (!IsAttached())
		return false;
#ifdef UNIX
	j_decompress_ptr		p_info = (j_decompress_ptr)m_p_info;
	if (!p_info)
	{
		p_info = new struct jpeg_decompress_struct;
		m_p_info = (void *)p_info;
	}

	/* We set up the normal JPEG error routines, then override error_exit. */
	my_error_ptr	p_jerr;
	p_jerr = (my_error_ptr)m_p_error_mgr;
	
	p_info->err = jpeg_std_error(&p_jerr->pub);
	p_jerr->pub.error_exit = my_error_exit;
	/* Establish the setjmp return context for my_error_exit to use. */
	if (setjmp(p_jerr->setjmp_buffer))
		return 0;		 // If we get here, the JPEG code has signaled an error. 	

	p_info->jpeg_color_space = JCS_RGB;
	p_info->num_components = 3;

	jpeg_create_decompress(p_info);		//Now we can initialize the JPEG decompression object.
	jpeg_stdio_src((p_info, GetFileHandle()->Get_fp());		// Step 2: specify data source (eg, a file) 
  (void) jpeg_read_header(p_info, TRUE);		// Step 3: read file parameters with jpeg_read_header() 
  /* We can ignore the return value from jpeg_read_header since
   *   (a) suspension is not possible with the stdio data source, and
   *   (b) we passed TRUE to reject a tables-only JPEG file as an error.
   * See libjpeg.doc for more info.
   */
  
	info.GetSize().Set (p_info->image_width, p_info->image_height);
	p_info->jpeg_color_space = JCS_RGB;
	p_info->num_components = 3;
	
	switch (p_info->jpeg_color_space)
	{
		case JCS_RGB:
			info.GetColorSpace().SetColorSpace(ColorSpace::COLORSPACE_RGB);
			break;
		case JCS_GRAYSCALE:
			info.GetColorSpace().SetColorSpace(ColorSpace::COLORSPACE_GRAY);
			break;
		default:
			return false;
	}
	return true;
#else
	return false;
#endif
}

/**
 * Assumes bfc_bitmap is of the correct known data type
 * @param rect2d_Load 
 * @param bfc_bitmap 
 * @return 
 */
OVERRIDE bool Image_Format_Layer_JPEG :: LoadRectangle (const Rect2dU &rect2d_Load, Bitmap &bfc_bitmap)     // virtual
{
	ColorSpace	cSpace_jpg(ColorSpace::COLORSPACE_BGR);
	ColorSpace	cSpace(ColorSpace::COLORSPACE_RGBA);

	if (!GetFormat()->IsAttached())
		return false;
#ifdef UNIX
	Size2dU	sz;
	GetImageSize(sz);

	bfc_bitmap.Allocate(cSpace, sz);
	my_error_ptr 	p_jerr;
	p_jerr = (my_error_ptr)GetFormat()->m_p_error_mgr;

	if (setjmp(p_jerr->setjmp_buffer)) 
		return 0;		// If we get here, the JPEG code has signaled an error.
 // Step 4: set parameters for decompression */
 // In this example, we don't need to change any of the defaults set by  jpeg_read_header(), so we do nothing here.
	  /* Step 5: Start decompressor */
	j_decompress_ptr	p_info = (j_decompress_ptr)GetFormat()->m_p_info;
	(void) jpeg_start_decompress(p_info);	// We can ignore the return value since suspension is not possible with the stdio data source.
	
	/* We may need to do some setup of our own at this point before reading
	* the data.  After jpeg_start_decompress() we have the correct scaled
	* output image dimensions available, as well as the output colormap
	* if we asked for color quantization.
	* In this example, we need to make an output work buffer of the right size.
	*/ 
	// JSAMPLEs per row in output buffer
	int row_stride = p_info->output_width * p_info->output_components;
	JSAMPARRAY buffer;		/* Output row buffer */
	// Make a one-row-high sample array that will go away when done with image
	buffer = (*p_info->mem->alloc_sarray)
		((j_common_ptr) p_info, JPOOL_IMAGE, row_stride, 1);
	
	// Step 6: while (scan lines remain to be read) jpeg_read_scanlines(...); 
	while (p_info->output_scanline < p_info->output_height) 
	{
		/* jpeg_read_scanlines expects an array of pointers to scanlines.
			* Here the array is only one element long, but you could ask for
			* more than one scanline at a time if that's more convenient.	*/
		(void) jpeg_read_scanlines(p_info, buffer, 1);
		bfc_bitmap.SetScanlines (buffer[0],0,p_info->output_scanline-1, p_info->output_width,cSpace_jpg, 1);
	}
	// Step 7: Finish decompression
	(void) jpeg_finish_decompress(p_info); // We can ignore the return value since suspension is not possible with the stdio data source.
	return true;
#else
	return false;
#endif
}

OVERRIDE bool Image_Format_Layer_JPEG :: SaveBitmap (/*const*/ Bitmap &bfc_bitmap)
{
#ifdef UNIX
	struct	jpeg_compress_struct	cinfo;
	struct	jpeg_error_mgr			jerr;
	JSAMPROW						row_pointer[1];
	
	int		m_i_quality=100;

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&cinfo);
	jpeg_stdio_dest(&cinfo, GetFormat()->GetFileHandle()->Get_fp());

	Size2dU		size;
	if (GetImageSize(size))
	{
		cinfo.image_width = size.GetX();
		cinfo.image_height = size.GetY();
	}
	cinfo.input_components = 3;
	cinfo.in_color_space = JCS_RGB;
	
	jpeg_set_defaults(&cinfo);
	jpeg_set_quality(&cinfo, m_i_quality, true);
	jpeg_start_compress (&cinfo, true);
	
	while (cinfo.next_scanline < cinfo.image_height)
	{
		BYTE *p_scanline = bfc_bitmap.ReferenceBitPtr (0,cinfo.next_scanline,cinfo.image_width);

		row_pointer[0] = p_scanline;
		jpeg_write_scanlines(&cinfo, row_pointer, 1);

		bfc_bitmap.DeReferenceBitPtr (p_scanline);
	}
	
	jpeg_finish_compress(&cinfo);
	jpeg_destroy_compress(&cinfo);		// Release memory
	return true;
#else
	return false;
#endif
}


/*
 * Here's the routine that will replace the standard error_exit method:
 */
#ifdef UNIX
METHODDEF(void) my_error_exit (j_common_ptr cinfo)
{
  /* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
  my_error_ptr myerr = (my_error_ptr) cinfo->err;
  /* Always display the message. */
  /* We could postpone this until after returning, if we chose. */
  (*cinfo->err->output_message) (cinfo);
  /* Return control to the setjmp point */
  longjmp(myerr->setjmp_buffer, 1);
}
#endif


}


