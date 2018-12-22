#include "Image.h"
#include <cstring>
#include <iostream>
namespace SRE {

	Image::Image()
		: _width(0),
		  _height(0),
		  _depth(0),
		 _bufSize(0),
		_numMipMaps(0),
		_pixelFormat(PF_UNKNOWN),
		_buffer(NULL)
	{
		FreeImage_Initialise();
	}
	Image::Image(const Image& image)
		:_buffer(NULL)
	{
		*this = image;
	}
	Image & Image::operator = (const Image &image)
	{
		if (_buffer)
		{
			free(_buffer);
			_buffer = 0;
		}
		_width = image._width;
		_height = image._height;
		_depth = image._depth;
		//mFormat = image.mFormat;
		_bufSize = image._bufSize;
		_numMipMaps = image._numMipMaps;
		_buffer = (unsigned char*)malloc(sizeof(char) * _bufSize);
		memcpy(_buffer, image._buffer, _bufSize);			
		//_buffer = image._buffer;	

		return *this;
	}
	Image::~Image()
	{
		if (_buffer)
		{
			free(_buffer);
			_buffer = 0;
		}
		FreeImage_DeInitialise();
	}
	bool Image::load(const std::string& file_name)
	{
		FREE_IMAGE_FORMAT  fif = FIF_UNKNOWN;
		fif = FreeImage_GetFIFFromFilename(file_name.c_str());

		if (fif == FIF_UNKNOWN)
		{
			return false;
		}

		FIBITMAP * dib;
		if (FreeImage_FIFSupportsReading(fif))
		{
			dib = FreeImage_Load(fif, file_name.c_str());
		}
		else
		{
			return false;
		}

		return decode2(dib);
	}
	bool Image::save(const std::string& file_name)
	{
		if (!_buffer)
			return false;

		FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(file_name.c_str());
		
		FIBITMAP* dib = toBitMap();
		bool success = false;
		if (FreeImage_Save(fif, dib, file_name.c_str(), 0))
		{
			success = true;
		}
		else
		{
			success = false;
		}
		FreeImage_Unload(dib);

		return success;
	}
	bool Image::decode(FIBITMAP* dib)
	{
		if (!dib)
		{
			return false;
		}

		unsigned int width = FreeImage_GetWidth(dib);
		unsigned int height = FreeImage_GetHeight(dib);
		if ((width == 0) || (height == 0))
		{
			return false;
		}
		

		BYTE* bits = FreeImage_GetBits(dib);
		if (bits == 0)
		{
			return false;
		}

		BITMAPINFOHEADER* bitmap_header = FreeImage_GetInfoHeader(dib);
		if (bitmap_header->biBitCount == 32)
		{
			//RGBA
			//dib = FreeImage_ConvertTo32Bits(dib);
		}
		else
		{
			//RGB
			dib = FreeImage_ConvertTo32Bits(dib);
			if (!dib)
				return false;
			bits = FreeImage_GetBits(dib);
			
			_pixelSize = 4;
		}
		
		_width = width;
		_height = height;
		_depth = 1;
		_numMipMaps = 0;
		int bit_count = FreeImage_GetLine(dib)*_height;
		int bytespp = FreeImage_GetLine(dib) / FreeImage_GetWidth(dib);
		for (long index = 0; index < bit_count; index += bytespp)
		{
			unsigned char temp_color = bits[index];
			bits[index] = bits[index + 2];
			bits[index + 2] = temp_color;
		}
		//这里怎么能写死呢？？？
		_pixelFormat = PF_BYTE_RGBA;
		_buffer = (unsigned char*)malloc(sizeof(char) * bit_count);
		memcpy(_buffer, bits, sizeof(char) * bit_count);
		_bufSize = bit_count;
		free(bits);
		return true;
		
	}
	bool Image::decode2(FIBITMAP* dib)
	{
		if (!dib)
		{
			return false;
		}

		unsigned int width = FreeImage_GetWidth(dib);
		unsigned int height = FreeImage_GetHeight(dib);
		if ((width == 0) || (height == 0))
		{
			return false;
		}
		_width = width;
		_height = height;
		_depth = 1;
		_numMipMaps = 0;

		FREE_IMAGE_TYPE imageType = FreeImage_GetImageType(dib);
		FREE_IMAGE_COLOR_TYPE colorType = FreeImage_GetColorType(dib);
		_bpp = FreeImage_GetBPP(dib);

		switch (imageType)
		{
		case FIT_UNKNOWN:
		case FIT_COMPLEX:
		case FIT_UINT32:
		case FIT_INT32:
		case FIT_DOUBLE:
		default:

			break;
		case FIT_BITMAP:
			// Standard image type
			// Perform any colour conversions for greyscale
			if (colorType == FIC_MINISWHITE || colorType == FIC_MINISBLACK)
			{
				FIBITMAP* newBitmap = FreeImage_ConvertToGreyscale(dib);
				// free old bitmap and replace
				FreeImage_Unload(dib);
				dib = newBitmap;
				// get new formats
				_bpp = FreeImage_GetBPP(dib);
			}
			// Perform any colour conversions for RGB
			else if (_bpp < 8 || colorType == FIC_PALETTE || colorType == FIC_CMYK)
			{
				FIBITMAP* newBitmap = NULL;
				if (FreeImage_IsTransparent(dib))
				{
					// convert to 32 bit to preserve the transparency 
					// (the alpha byte will be 0 if pixel is transparent)
					newBitmap = FreeImage_ConvertTo32Bits(dib);
				}
				else
				{
					// no transparency - only 3 bytes are needed
					newBitmap = FreeImage_ConvertTo24Bits(dib);
				}

				// free old bitmap and replace
				FreeImage_Unload(dib);
				dib = newBitmap;
				// get new formats
				_bpp = FreeImage_GetBPP(dib);
			}

			// by this stage, 8-bit is greyscale, 16/24/32 bit are RGB[A]
			switch (_bpp)
			{
			case 8:
				_pixelFormat = PF_L8;
				break;
			case 16:
				// Determine 555 or 565 from green mask
				// cannot be 16-bit greyscale since that's FIT_UINT16
				if (FreeImage_GetGreenMask(dib) == FI16_565_GREEN_MASK)
				{
					_pixelFormat = PF_R5G6B5;
				}
				else
				{
					// FreeImage doesn't support 4444 format so must be 1555
					_pixelFormat = PF_A1R5G5B5;
				}
				break;
			case 24:
				// FreeImage differs per platform
				//     PF_BYTE_BGR[A] for little endian (== PF_ARGB native)
				//     PF_BYTE_RGB[A] for big endian (== PF_RGBA native)
#if FREEIMAGE_COLORORDER == FREEIMAGE_COLORORDER_RGB
				_pixelFormat = PF_BYTE_RGB;
#else
				_pixelFormat = PF_BYTE_BGR;
#endif
				break;
			case 32:
#if FREEIMAGE_COLORORDER == FREEIMAGE_COLORORDER_RGB
				_pixelFormat = PF_BYTE_RGBA;
#else
				_pixelFormat = PF_BYTE_BGRA;
#endif
				break;


			};
			break;
		case FIT_UINT16:
		case FIT_INT16:
			// 16-bit greyscale
			_pixelFormat = PF_L16;
			break;
		case FIT_FLOAT:
			// Single-component floating point data
			_pixelFormat = PF_FLOAT32_R;
			break;
		case FIT_RGB16:
			_pixelFormat = PF_SHORT_RGB;
			break;
		case FIT_RGBA16:
			_pixelFormat = PF_SHORT_RGBA;
			break;
		case FIT_RGBF:
			_pixelFormat = PF_FLOAT32_RGB;
			break;
		case FIT_RGBAF:
			_pixelFormat = PF_FLOAT32_RGBA;
			break;


		};

		BYTE* bits = FreeImage_GetBits(dib);
		int bit_count = FreeImage_GetLine(dib)*_height;	
		//_pixelSize = bit_count / (_width*_height);

		_buffer = (unsigned char*)malloc(sizeof(char) * bit_count);
		memcpy(_buffer, bits, sizeof(char) * bit_count);
		_bufSize = bit_count;

		return true;

	}

	Image::ptr Image::rescale(Image::ptr image, size_t rescalWidth, size_t rescalHeight)
	{
		if (image)
		{
			Image* result = new Image();
			result = image.get();

			FIBITMAP *dib = FreeImage_Allocate(image->width(), image->height(), image->BPP(), 0, 0, 0);
			FIBITMAP *bit_map = rescale(dib, rescalWidth, rescalHeight);
			BYTE* bits = FreeImage_GetBits(bit_map);
			//result-> = image_info_->image_type;
			//result->pixelFormat() = image->pixelFormat();
			//result->image_width = rescale_width_;
			//result->image_height = rescale_height_;
			//result->data_size = image->image_width*image->image_height*byte_spp_;
			//image->pixel_data = (unsigned char*)malloc(sizeof(char) * image->data_size);
			//memcpy(image->pixel_data, bits, sizeof(char) * image->data_size);

			FreeImage_Unload(bit_map);
			FreeImage_Unload(dib);
			return (Image::ptr)result;
		}
		return NULL;
	}
	FIBITMAP * Image::rescale(FIBITMAP *bit_map, size_t rescalWidth, size_t rescalHeight)
	{
		if (bit_map)
		{
			FIBITMAP* bit_map_ = FreeImage_Rescale(bit_map, rescalWidth, rescalHeight, FILTER_BOX);
			return bit_map_;
		}
		else
		{
			return 0;
		}
		
	}

	FIBITMAP* Image::toBitMap()
	{
		FIBITMAP *dib = FreeImage_Allocate(_width, _height, BPP(), 0, 0, 0);

		int index = 0;
		int byte_spp = FreeImage_GetLine(dib) / FreeImage_GetWidth(dib);
		for (unsigned y = 0; y < FreeImage_GetHeight(dib); y++)
		{
			BYTE *bits = FreeImage_GetScanLine(dib, y);
			for (unsigned x = 0; x < FreeImage_GetWidth(dib); x++)
			{
				bits[FI_RGBA_RED] = _buffer[index++];
				bits[FI_RGBA_GREEN] = _buffer[index++];
				bits[FI_RGBA_BLUE] = _buffer[index++];
				if (BPP() == 4)
				{
					bits[FI_RGBA_ALPHA] = _buffer[index++];
				}
				bits += byte_spp;
			}
		}

		return dib;
	}
}