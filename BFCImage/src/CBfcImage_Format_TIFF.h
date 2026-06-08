//*/
/*
					CBfcImage_Format_TIFF.h : 
	
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
/*
	CBfcImageFF.h

*/

namespace CBfcImage
{

BFC_IMAGE_CLASS Image_Format_TIFF : public Image_Format
{
public:
	Image_Format_TIFF(const CBfc::Stream *p_Stream)
		: Image_Format(p_Stream)
	{
	}
	
	virtual bool LoadHeader (Image_Info &info);
	virtual bool LoadRectangle (const CBfc::Rect2dU &rect2d_Load, Bitmap &bfc_bitmap);
	

	virtual bool SaveBitmap (/*const*/ Bitmap &bfc_bitmap);

private:

};



}

/*
main()
{
    TIFF* tif = TIFFOpen("myfile.tif", "r");
    if (tif) {
        uint32 imageWidth, imageLength;
        uint32 tileWidth, tileLength;
        uint32 x, y;
        tdata_t buf;

        TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &imageWidth);
        TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &imageLength);
        TIFFGetField(tif, TIFFTAG_TILEWIDTH, &tileWidth);
        TIFFGetField(tif, TIFFTAG_TILELENGTH, &tileLength);
        buf = _TIFFmalloc(TIFFTileSize(tif));
        for (y = 0; y < imageLength; y += tileLength)
            for (x = 0; x < imageWidth; x += tileWidth)
                TIFFReadTile(tif, buf, x, y, 0);
        _TIFFfree(buf);
        TIFFClose(tif);
    }
}

*/


