#include "PixelUtil.h"

namespace SRE {
	//���ظ�ʽ��˵��
	struct PixelFormatDescription
	{
		char *name;
		unsigned char elemBytes;
		unsigned int flags;
		PixelComponentType componentType;
		unsigned char componentCount;
		unsigned char rbits, gbits, bbits, abits;
		unsigned int rmask, gmask, bmask, amask;
		unsigned char rshift, gshift, bshift, ashift;
	};

	PixelFormatDescription _pixelFormats[PF_COUNT] = {

		{ "PF_UNKNOWN",
		/* Bytes per element */
		0,
		/* Flags */
		0,
		/* Component type and count */
		PCT_BYTE, 0,
		/* rbits, gbits, bbits, abits */
		0, 0, 0, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//-----------------------------------------------------------------------
		{ "PF_L8",
		/* Bytes per element */
		1,
		/* Flags */
		PFF_LUMINANCE | PFF_NATIVEENDIAN,
		/* Component type and count */
		PCT_BYTE, 1,
		/* rbits, gbits, bbits, abits */
		8, 0, 0, 0,
		/* Masks and shifts */
		0xFF, 0, 0, 0, 0, 0, 0, 0
		},
		//-----------------------------------------------------------------------
		{ "PF_L16",
		/* Bytes per element */
		2,
		/* Flags */
		PFF_LUMINANCE | PFF_NATIVEENDIAN,
		/* Component type and count */
		PCT_SHORT, 1,
		/* rbits, gbits, bbits, abits */
		16, 0, 0, 0,
		/* Masks and shifts */
		0xFFFF, 0, 0, 0, 0, 0, 0, 0
		},
		//-----------------------------------------------------------------------
		{ "PF_A8",
		/* Bytes per element */
		1,
		/* Flags */
		PFF_HASALPHA | PFF_NATIVEENDIAN,
		/* Component type and count */
		PCT_BYTE, 1,
		/* rbits, gbits, bbits, abits */
		0, 0, 0, 8,
		/* Masks and shifts */
		0, 0, 0, 0xFF, 0, 0, 0, 0
		},
		//-----------------------------------------------------------------------
		{ "PF_A4L4",
		/* Bytes per element */
		1,
		/* Flags */
		PFF_HASALPHA | PFF_LUMINANCE | PFF_NATIVEENDIAN,
		/* Component type and count */
		PCT_BYTE, 2,
		/* rbits, gbits, bbits, abits */
		4, 0, 0, 4,
		/* Masks and shifts */
		0x0F, 0, 0, 0xF0, 0, 0, 0, 4
		},
		//-----------------------------------------------------------------------
		{ "PF_BYTE_LA",
		/* Bytes per element */
		2,
		/* Flags */
		PFF_HASALPHA | PFF_LUMINANCE,
		/* Component type and count */
		PCT_BYTE, 2,
		/* rbits, gbits, bbits, abits */
		8, 0, 0, 8,
		/* Masks and shifts */
		0,0,0,0,0,0,0,0
		},
		//-----------------------------------------------------------------------
		{ "PF_R5G6B5",
		/* Bytes per element */
		2,
		/* Flags */
		PFF_NATIVEENDIAN,
		/* Component type and count */
		PCT_BYTE, 3,
		/* rbits, gbits, bbits, abits */
		5, 6, 5, 0,
		/* Masks and shifts */
		0xF800, 0x07E0, 0x001F, 0,
		11, 5, 0, 0
		},
		//-----------------------------------------------------------------------
		{ "PF_B5G6R5",
		/* Bytes per element */
		2,
		/* Flags */
		PFF_NATIVEENDIAN,
		/* Component type and count */
		PCT_BYTE, 3,
		/* rbits, gbits, bbits, abits */
		5, 6, 5, 0,
		/* Masks and shifts */
		0x001F, 0x07E0, 0xF800, 0,
		0, 5, 11, 0
		},
		//-----------------------------------------------------------------------
		{ "PF_A4R4G4B4",
		/* Bytes per element */
		2,
		/* Flags */
		PFF_HASALPHA | PFF_NATIVEENDIAN,
		/* Component type and count */
		PCT_BYTE, 4,
		/* rbits, gbits, bbits, abits */
		4, 4, 4, 4,
		/* Masks and shifts */
		0x0F00, 0x00F0, 0x000F, 0xF000,
		8, 4, 0, 12
		},
		//-----------------------------------------------------------------------
		{ "PF_A1R5G5B5",
		/* Bytes per element */
		2,
		/* Flags */
		PFF_HASALPHA | PFF_NATIVEENDIAN,
		/* Component type and count */
		PCT_BYTE, 4,
		/* rbits, gbits, bbits, abits */
		5, 5, 5, 1,
		/* Masks and shifts */
		0x7C00, 0x03E0, 0x001F, 0x8000,
		10, 5, 0, 15,
		},
		//-----------------------------------------------------------------------
		{ "PF_R8G8B8",
		/* Bytes per element */
		3,  // 24 bit integer -- special
			/* Flags */
		PFF_NATIVEENDIAN,
		/* Component type and count */
		PCT_BYTE, 3,
		/* rbits, gbits, bbits, abits */
		8, 8, 8, 0,
		/* Masks and shifts */
		0xFF0000, 0x00FF00, 0x0000FF, 0,
		16, 8, 0, 0
		},
		//-----------------------------------------------------------------------
		{ "PF_B8G8R8",
		/* Bytes per element */
		3,  // 24 bit integer -- special
			/* Flags */
		PFF_NATIVEENDIAN,
		/* Component type and count */
		PCT_BYTE, 3,
		/* rbits, gbits, bbits, abits */
		8, 8, 8, 0,
		/* Masks and shifts */
		0x0000FF, 0x00FF00, 0xFF0000, 0,
		0, 8, 16, 0
		},
		//-----------------------------------------------------------------------
		{ "PF_A8R8G8B8",
		/* Bytes per element */
		4,
		/* Flags */
		PFF_HASALPHA | PFF_NATIVEENDIAN,
		/* Component type and count */
		PCT_BYTE, 4,
		/* rbits, gbits, bbits, abits */
		8, 8, 8, 8,
		/* Masks and shifts */
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000,
		16, 8, 0, 24
		},
		//-----------------------------------------------------------------------
		{ "PF_A8B8G8R8",
		/* Bytes per element */
		4,
		/* Flags */
		PFF_HASALPHA | PFF_NATIVEENDIAN,
		/* Component type and count */
		PCT_BYTE, 4,
		/* rbits, gbits, bbits, abits */
		8, 8, 8, 8,
		/* Masks and shifts */
		0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000,
		0, 8, 16, 24,
		},
		//-----------------------------------------------------------------------
		{ "PF_B8G8R8A8",
		/* Bytes per element */
		4,
		/* Flags */
		PFF_HASALPHA | PFF_NATIVEENDIAN,
		/* Component type and count */
		PCT_BYTE, 4,
		/* rbits, gbits, bbits, abits */
		8, 8, 8, 8,
		/* Masks and shifts */
		0x0000FF00, 0x00FF0000, 0xFF000000, 0x000000FF,
		8, 16, 24, 0
		},
		//-----------------------------------------------------------------------
		{ "PF_A2R10G10B10",
		/* Bytes per element */
		4,
		/* Flags */
		PFF_HASALPHA | PFF_NATIVEENDIAN,
		/* Component type and count */
		PCT_BYTE, 4,
		/* rbits, gbits, bbits, abits */
		10, 10, 10, 2,
		/* Masks and shifts */
		0x3FF00000, 0x000FFC00, 0x000003FF, 0xC0000000,
		20, 10, 0, 30
		},
		//-----------------------------------------------------------------------
		{ "PF_A2B10G10R10",
		/* Bytes per element */
		4,
		/* Flags */
		PFF_HASALPHA | PFF_NATIVEENDIAN,
		/* Component type and count */
		PCT_BYTE, 4,
		/* rbits, gbits, bbits, abits */
		10, 10, 10, 2,
		/* Masks and shifts */
		0x000003FF, 0x000FFC00, 0x3FF00000, 0xC0000000,
		0, 10, 20, 30
		},
		//-----------------------------------------------------------------------
		{ "PF_DXT1",
		/* Bytes per element */
		0,
		/* Flags */
		PFF_COMPRESSED | PFF_HASALPHA,
		/* Component type and count */
		PCT_BYTE, 3, // No alpha
					 /* rbits, gbits, bbits, abits */
		0, 0, 0, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//-----------------------------------------------------------------------
		{ "PF_DXT2",
		/* Bytes per element */
		0,
		/* Flags */
		PFF_COMPRESSED | PFF_HASALPHA,
		/* Component type and count */
		PCT_BYTE, 4,
		/* rbits, gbits, bbits, abits */
		0, 0, 0, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//-----------------------------------------------------------------------
		{ "PF_DXT3",
		/* Bytes per element */
		0,
		/* Flags */
		PFF_COMPRESSED | PFF_HASALPHA,
		/* Component type and count */
		PCT_BYTE, 4,
		/* rbits, gbits, bbits, abits */
		0, 0, 0, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//-----------------------------------------------------------------------
		{ "PF_DXT4",
		/* Bytes per element */
		0,
		/* Flags */
		PFF_COMPRESSED | PFF_HASALPHA,
		/* Component type and count */
		PCT_BYTE, 4,
		/* rbits, gbits, bbits, abits */
		0, 0, 0, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//-----------------------------------------------------------------------
		{ "PF_DXT5",
		/* Bytes per element */
		0,
		/* Flags */
		PFF_COMPRESSED | PFF_HASALPHA,
		/* Component type and count */
		PCT_BYTE, 4,
		/* rbits, gbits, bbits, abits */
		0, 0, 0, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//-----------------------------------------------------------------------
		{ "PF_FLOAT16_RGB",
		/* Bytes per element */
		6,
		/* Flags */
		PFF_FLOAT,
		/* Component type and count */
		PCT_FLOAT16, 3,
		/* rbits, gbits, bbits, abits */
		16, 16, 16, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//-----------------------------------------------------------------------
		{ "PF_FLOAT16_RGBA",
		/* Bytes per element */
		8,
		/* Flags */
		PFF_FLOAT | PFF_HASALPHA,
		/* Component type and count */
		PCT_FLOAT16, 4,
		/* rbits, gbits, bbits, abits */
		16, 16, 16, 16,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//-----------------------------------------------------------------------
		{ "PF_FLOAT32_RGB",
		/* Bytes per element */
		12,
		/* Flags */
		PFF_FLOAT,
		/* Component type and count */
		PCT_FLOAT32, 3,
		/* rbits, gbits, bbits, abits */
		32, 32, 32, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//-----------------------------------------------------------------------
		{ "PF_FLOAT32_RGBA",
		/* Bytes per element */
		16,
		/* Flags */
		PFF_FLOAT | PFF_HASALPHA,
		/* Component type and count */
		PCT_FLOAT32, 4,
		/* rbits, gbits, bbits, abits */
		32, 32, 32, 32,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//-----------------------------------------------------------------------
		{ "PF_X8R8G8B8",
		/* Bytes per element */
		4,
		/* Flags */
		PFF_NATIVEENDIAN,
		/* Component type and count */
		PCT_BYTE, 3,
		/* rbits, gbits, bbits, abits */
		8, 8, 8, 0,
		/* Masks and shifts */
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000,
		16, 8, 0, 24
		},
		//-----------------------------------------------------------------------
		{ "PF_X8B8G8R8",
		/* Bytes per element */
		4,
		/* Flags */
		PFF_NATIVEENDIAN,
		/* Component type and count */
		PCT_BYTE, 3,
		/* rbits, gbits, bbits, abits */
		8, 8, 8, 0,
		/* Masks and shifts */
		0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000,
		0, 8, 16, 24
		},
		//-----------------------------------------------------------------------
		{ "PF_R8G8B8A8",
		/* Bytes per element */
		4,
		/* Flags */
		PFF_HASALPHA | PFF_NATIVEENDIAN,
		/* Component type and count */
		PCT_BYTE, 4,
		/* rbits, gbits, bbits, abits */
		8, 8, 8, 8,
		/* Masks and shifts */
		0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF,
		24, 16, 8, 0
		},
		//-----------------------------------------------------------------------
		{ "PF_DEPTH",
		/* Bytes per element */
		4,
		/* Flags */
		PFF_DEPTH,
		/* Component type and count */
		PCT_FLOAT32, 1, // ?
						/* rbits, gbits, bbits, abits */
		0, 0, 0, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//-----------------------------------------------------------------------
		{ "PF_SHORT_RGBA",
		/* Bytes per element */
		8,
		/* Flags */
		PFF_HASALPHA,
		/* Component type and count */
		PCT_SHORT, 4,
		/* rbits, gbits, bbits, abits */
		16, 16, 16, 16,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//-----------------------------------------------------------------------
		{ "PF_R3G3B2",
		/* Bytes per element */
		1,
		/* Flags */
		PFF_NATIVEENDIAN,
		/* Component type and count */
		PCT_BYTE, 3,
		/* rbits, gbits, bbits, abits */
		3, 3, 2, 0,
		/* Masks and shifts */
		0xE0, 0x1C, 0x03, 0,
		5, 2, 0, 0
		},
		//-----------------------------------------------------------------------
		{ "PF_FLOAT16_R",
		/* Bytes per element */
		2,
		/* Flags */
		PFF_FLOAT,
		/* Component type and count */
		PCT_FLOAT16, 1,
		/* rbits, gbits, bbits, abits */
		16, 0, 0, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//-----------------------------------------------------------------------
		{ "PF_FLOAT32_R",
		/* Bytes per element */
		4,
		/* Flags */
		PFF_FLOAT,
		/* Component type and count */
		PCT_FLOAT32, 1,
		/* rbits, gbits, bbits, abits */
		32, 0, 0, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//-----------------------------------------------------------------------
		{ "PF_SHORT_GR",
		/* Bytes per element */
		4,
		/* Flags */
		PFF_NATIVEENDIAN,
		/* Component type and count */
		PCT_SHORT, 2,
		/* rbits, gbits, bbits, abits */
		16, 16, 0, 0,
		/* Masks and shifts */
		0x0000FFFF, 0xFFFF0000, 0, 0,
		0, 16, 0, 0
		},
		//-----------------------------------------------------------------------
		{ "PF_FLOAT16_GR",
		/* Bytes per element */
		4,
		/* Flags */
		PFF_FLOAT,
		/* Component type and count */
		PCT_FLOAT16, 2,
		/* rbits, gbits, bbits, abits */
		16, 16, 0, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//-----------------------------------------------------------------------
		{ "PF_FLOAT32_GR",
		/* Bytes per element */
		8,
		/* Flags */
		PFF_FLOAT,
		/* Component type and count */
		PCT_FLOAT32, 2,
		/* rbits, gbits, bbits, abits */
		32, 32, 0, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//-----------------------------------------------------------------------
		{ "PF_SHORT_RGB",
		/* Bytes per element */
		6,
		/* Flags */
		0,
		/* Component type and count */
		PCT_SHORT, 3,
		/* rbits, gbits, bbits, abits */
		16, 16, 16, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//-----------------------------------------------------------------------
		{ "PF_PVRTC_RGB2",
		/* Bytes per element */
		0,
		/* Flags */
		PFF_COMPRESSED,
		/* Component type and count */
		PCT_BYTE, 3,
		/* rbits, gbits, bbits, abits */
		0, 0, 0, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//-----------------------------------------------------------------------
		{ "PF_PVRTC_RGBA2",
		/* Bytes per element */
		0,
		/* Flags */
		PFF_COMPRESSED | PFF_HASALPHA,
		/* Component type and count */
		PCT_BYTE, 4,
		/* rbits, gbits, bbits, abits */
		0, 0, 0, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//-----------------------------------------------------------------------
		{ "PF_PVRTC_RGB4",
		/* Bytes per element */
		0,
		/* Flags */
		PFF_COMPRESSED,
		/* Component type and count */
		PCT_BYTE, 3,
		/* rbits, gbits, bbits, abits */
		0, 0, 0, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//-----------------------------------------------------------------------
		{ "PF_PVRTC_RGBA4",
		/* Bytes per element */
		0,
		/* Flags */
		PFF_COMPRESSED | PFF_HASALPHA,
		/* Component type and count */
		PCT_BYTE, 4,
		/* rbits, gbits, bbits, abits */
		0, 0, 0, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		}
	};
	unsigned int fixedToFixed(unsigned int value, unsigned int n, unsigned int p)
	{
		if (n > p)
		{
			value >>= n - p;
		}
		else if (n < p)
		{
			if (value == 0)
				value = 0;
			else if (value == (static_cast<unsigned int>(1) << n) - 1)
				value = (1 << p) - 1;
			else    value = value*(1 << p) / ((1 << n) - 1);
		}
		return value;
	}

	static inline unsigned int floatToFixed(const float value, const unsigned int bits)
	{
		if (value <= 0.0f) return 0;
		else if (value >= 1.0f) return (1 << bits) - 1;
		else return (unsigned int)(value * (1 << bits));
	}

	float fixedToFloat(unsigned value, unsigned int bits)
	{
		return (float)value / (float)((1 << bits) - 1);
	}

	void int_write(void *dest, int n, unsigned int value)
	{
		switch (n)
		{
		case 1:
			((unsigned char*)dest)[0] = (unsigned char)value;
			break;
		case 2:
			((unsigned short*)dest)[0] = (unsigned short)value;
			break;
		case 3:   
			((unsigned char*)dest)[2] = (unsigned char)((value >> 16) & 0xff);
			((unsigned char*)dest)[1] = (unsigned char)((value >> 8) & 0xff);
			((unsigned char*)dest)[0] = (unsigned char)((value) & 0xff);
			break;
		case 4:
			((unsigned int*)dest)[0] = (unsigned int)value;
			break;
		}
	}

	unsigned int int_read(const void *src, int n) {
		switch (n) {
		case 1:
			return ((unsigned char*)src)[0];
		case 2:
			return ((unsigned short*)src)[0];
		case 3:
			return ((unsigned int)((unsigned char*)src)[0]) |
				((unsigned int)((unsigned char*)src)[1] << 8) |
				((unsigned int)((unsigned char*)src)[2] << 16);
		case 4:
			return ((unsigned int*)src)[0];
		}
		return 0;
	}
	inline const PixelFormatDescription &getDescriptionFor(const PixelFormat fmt)
	{
		const int ord = (int)fmt;
		//assert(ord >= 0 && ord<PF_COUNT);

		return _pixelFormats[ord];
	}
	unsigned int PixelUtil::getFlags(PixelFormat format)
	{
		return getDescriptionFor(format).flags;
	}
	bool PixelUtil::isCompressed(PixelFormat format)
	{
		return (PixelUtil::getFlags(format) & PFF_COMPRESSED) > 0;
	}
	
	size_t PixelUtil::getNumElemBytes(PixelFormat format)
	{
		return getDescriptionFor(format).elemBytes;
	}
	bool PixelUtil::hasAlpha(PixelFormat format)
	{
		return (PixelUtil::getFlags(format) & PFF_HASALPHA) > 0;
	}
	bool PixelUtil::isFloatingPoint(PixelFormat format)
	{
		return (PixelUtil::getFlags(format) & PFF_FLOAT) > 0;
	}
	bool PixelUtil::isInteger(PixelFormat format)
	{
		return (PixelUtil::getFlags(format) & PFF_INTEGER) > 0;
	}
	//-----------------------------------------------------------------------
	
	bool PixelUtil::isDepth(PixelFormat format)
	{
		return (PixelUtil::getFlags(format) & PFF_DEPTH) > 0;
	}
	void PixelUtil::getBitDepths(PixelFormat format, int rgba[4])
	{
		const PixelFormatDescription &des = getDescriptionFor(format);
		rgba[0] = des.rbits;
		rgba[1] = des.gbits;
		rgba[2] = des.bbits;
		rgba[3] = des.abits;
	}
	unsigned int PixelUtil::getMemorySize(unsigned int width, unsigned int height, unsigned int depth, PixelFormat format)
	{
		
		if (isCompressed(format))  
		{
			switch (format)
			{
			case PF_DXT1:  
				return ((width + 3) / 4) * ((height + 3) / 4) * 8 * depth;
			case PF_DXT2:  
			case PF_DXT3:
				return ((width + 3) / 4) * ((height + 3) / 4) * 16 * depth;
			case PF_DXT4: 
			case PF_DXT5:
				return ((width + 3) / 4) * ((height + 3) / 4) * 16 * depth;
			}
		}
		else
			return width * height * depth * getNumElemBytes(format);
	}
	GLenum PixelUtil::getGLOriginFormat(PixelFormat format)
	{
		switch (format)
		{
		case PF_A8:
			return GL_ALPHA;
		case PF_L8:
			return GL_LUMINANCE;
		case PF_L16:
			return GL_LUMINANCE;
		case PF_BYTE_LA:
			return GL_LUMINANCE_ALPHA;
		case PF_R3G3B2:
			return GL_RGB;
		case PF_A1R5G5B5:
			return GL_BGRA;
		case PF_R5G6B5:
			return GL_RGB;
		case PF_B5G6R5:
			return GL_BGR;
		case PF_A4R4G4B4:
			return GL_BGRA;
		case PF_R8G8B8:
			return GL_BGR;
		case PF_B8G8R8:
			return GL_RGB;
		case PF_X8R8G8B8:
		case PF_A8R8G8B8:
			return GL_BGRA;
		case PF_X8B8G8R8:
		case PF_A8B8G8R8:
			return GL_RGBA;
		case PF_B8G8R8A8:
			return GL_BGRA;
		case PF_R8G8B8A8:
			return GL_RGBA;
		case PF_A2R10G10B10:
			return GL_BGRA;
		case PF_A2B10G10R10:
			return GL_RGBA;
		case PF_FLOAT16_R:
			return GL_LUMINANCE;
		case PF_FLOAT16_GR:
			return GL_LUMINANCE_ALPHA;
		case PF_FLOAT16_RGB:
			return GL_RGB;
		case PF_FLOAT16_RGBA:
			return GL_RGBA;
		case PF_FLOAT32_R:
			return GL_LUMINANCE;
		case PF_FLOAT32_GR:
			return GL_LUMINANCE_ALPHA;
		case PF_FLOAT32_RGB:
			return GL_RGB;
		case PF_FLOAT32_RGBA:
			return GL_RGBA;
		case PF_SHORT_RGBA:
			return GL_RGBA;
		case PF_SHORT_RGB:
			return GL_RGB;
		case PF_SHORT_GR:
			return GL_LUMINANCE_ALPHA;
		case PF_DXT1:
			return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		case PF_DXT3:
			return GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		case PF_DXT5:
			return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		default:
			return 0;
		}
	}
	GLenum PixelUtil::getGLOriginDataType(PixelFormat format)
	{
		switch (format)
		{
		case PF_A8:
		case PF_L8:
		case PF_R8G8B8:
		case PF_B8G8R8:
		case PF_BYTE_LA:
			return GL_UNSIGNED_BYTE;
		case PF_R3G3B2:
			return GL_UNSIGNED_BYTE_3_3_2;
		case PF_A1R5G5B5:
			return GL_UNSIGNED_SHORT_1_5_5_5_REV;
		case PF_R5G6B5:
		case PF_B5G6R5:
			return GL_UNSIGNED_SHORT_5_6_5;
		case PF_A4R4G4B4:
			return GL_UNSIGNED_SHORT_4_4_4_4_REV;
		case PF_L16:
			return GL_UNSIGNED_SHORT;
		case PF_X8B8G8R8:
		case PF_A8B8G8R8:
			return GL_UNSIGNED_BYTE;
		case PF_X8R8G8B8:
		case PF_A8R8G8B8:
			return GL_UNSIGNED_BYTE;
		case PF_B8G8R8A8:
			return GL_UNSIGNED_INT_8_8_8_8;
		case PF_R8G8B8A8:
			return GL_UNSIGNED_INT_8_8_8_8;
		case PF_A2R10G10B10:
			return GL_UNSIGNED_INT_2_10_10_10_REV;
		case PF_A2B10G10R10:
			return GL_UNSIGNED_INT_2_10_10_10_REV;
		case PF_FLOAT16_R:
		case PF_FLOAT16_GR:
		case PF_FLOAT16_RGB:
		case PF_FLOAT16_RGBA:
			return GL_HALF_FLOAT_ARB;
		case PF_FLOAT32_R:
		case PF_FLOAT32_GR:
		case PF_FLOAT32_RGB:
		case PF_FLOAT32_RGBA:
			return GL_FLOAT;
		case PF_SHORT_RGBA:
		case PF_SHORT_RGB:
		case PF_SHORT_GR:
			return GL_UNSIGNED_SHORT;
		default:
			return 0;
		}
	}
	GLenum PixelUtil::getGLInternalFormat(PixelFormat format, bool hwGamma)
	{
		switch (format)
		{
		case PF_L8:
			return GL_LUMINANCE8;
		case PF_L16:
			return GL_LUMINANCE16;
		case PF_A8:
			return GL_ALPHA;
		case PF_A4L4:
			return GL_LUMINANCE4_ALPHA4;
		case PF_BYTE_LA:
			return GL_LUMINANCE8_ALPHA8;
		case PF_R3G3B2:
			return GL_R3_G3_B2;
		case PF_A1R5G5B5:
			return GL_RGB5_A1;
		case PF_R5G6B5:
		case PF_B5G6R5:
			return GL_RGB5;
		case PF_A4R4G4B4:
			return GL_RGBA4;
		case PF_R8G8B8:
		case PF_B8G8R8:
		case PF_X8B8G8R8:
		case PF_X8R8G8B8:
			return GL_RGB8;
		case PF_A8R8G8B8:
		case PF_B8G8R8A8:
			return GL_RGBA8;
		case PF_A2R10G10B10:
		case PF_A2B10G10R10:
			return GL_RGB10_A2;
		case PF_FLOAT16_R:
			return GL_LUMINANCE16F_ARB;
		case PF_FLOAT16_RGB:
			return GL_RGB16F_ARB;
		case PF_FLOAT16_GR:
			return GL_LUMINANCE_ALPHA16F_ARB;
		case PF_FLOAT16_RGBA:
			return GL_RGBA16F_ARB;
		case PF_FLOAT32_R:
			return GL_LUMINANCE32F_ARB;
		case PF_FLOAT32_GR:
			return GL_LUMINANCE_ALPHA32F_ARB;
		case PF_FLOAT32_RGB:
			return GL_RGB32F_ARB;
		case PF_FLOAT32_RGBA:
			return GL_RGBA32F_ARB;
		case PF_SHORT_RGBA:
			return GL_RGBA16;
		case PF_SHORT_RGB:
			return GL_RGB16;
		case PF_SHORT_GR:
			return GL_LUMINANCE16_ALPHA16;
		case PF_DXT1:
			return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		case PF_DXT3:
			return GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		case PF_DXT5:
			return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		default:
			return GL_RGBA8;
		}
	}
	PixelFormat PixelUtil::getClosestOGREFormat(GLenum fmt)
	{
		switch (fmt)
		{
		case GL_LUMINANCE8:
			return PF_L8;
		case GL_LUMINANCE16:
			return PF_L16;
		case GL_ALPHA8:
			return PF_A8;
		case GL_LUMINANCE4_ALPHA4:
			// Unsupported by GL as input format, use the byte packed format
			return PF_BYTE_LA;
		case GL_LUMINANCE8_ALPHA8:
			return PF_BYTE_LA;
		case GL_R3_G3_B2:
			return PF_R3G3B2;
		case GL_RGB5_A1:
			return PF_A1R5G5B5;
		case GL_RGB5:
			return PF_R5G6B5;
		case GL_RGBA4:
			return PF_A4R4G4B4;
		case GL_RGB8:
		case GL_SRGB8:
			return PF_X8R8G8B8;
		case GL_RGBA8:
		case GL_SRGB8_ALPHA8:
			return PF_A8R8G8B8;
		case GL_RGB10_A2:
			return PF_A2R10G10B10;
		case GL_RGBA16:
			return PF_SHORT_RGBA;
		case GL_RGB16:
			return PF_SHORT_RGB;
		case GL_LUMINANCE16_ALPHA16:
			return PF_SHORT_GR;
		case GL_LUMINANCE_FLOAT16_ATI:
			return PF_FLOAT16_R;
		case GL_LUMINANCE_ALPHA_FLOAT16_ATI:
			return PF_FLOAT16_GR;
		case GL_LUMINANCE_ALPHA_FLOAT32_ATI:
			return PF_FLOAT32_GR;
		case GL_LUMINANCE_FLOAT32_ATI:
			return PF_FLOAT32_R;
		case GL_RGB_FLOAT16_ATI: // GL_RGB16F_ARB
			return PF_FLOAT16_RGB;
		case GL_RGBA_FLOAT16_ATI:
			return PF_FLOAT16_RGBA;
		case GL_RGB_FLOAT32_ATI:
			return PF_FLOAT32_RGB;
		case GL_RGBA_FLOAT32_ATI:
			return PF_FLOAT32_RGBA;
		case GL_COMPRESSED_RGB_S3TC_DXT1_EXT:
		case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
		case GL_COMPRESSED_SRGB_S3TC_DXT1_EXT:
		case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT:
			return PF_DXT1;
		case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:
		case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT:
			return PF_DXT3;
		case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:
		case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT:
			return PF_DXT5;
		default:
			return PF_A8R8G8B8;
		};
	}
	GLenum PixelUtil::getClosestGLInternalFormat(PixelFormat format, bool hwGamma)
	{
		GLenum format_ = getGLInternalFormat(format, hwGamma);
		if (format_ == GL_NONE)
		{
			if (hwGamma)
				return GL_SRGB8;
			else
				return GL_RGBA8;
		}
		else
			return format_;
	}
	size_t PixelUtil::getMaxMipmaps(unsigned int width, unsigned int height, unsigned int depth, PixelFormat format)
	{
		size_t count = 0;
		if ((width > 0) && (height > 0) && (depth > 0))
		{
			do {
				if (width>1)     width = width / 2;
				if (height>1)    height = height / 2;
				if (depth>1)     depth = depth / 2;
				/*
				NOT needed, compressed formats will have mipmaps up to 1x1
				if(PixelUtil::isValidExtent(width, height, depth, format))
				count ++;
				else
				break;
				*/

				count++;
			} while (!(width == 1 && height == 1 && depth == 1));
		}
		return count;
	}
	unsigned int PixelUtil::optionalPO2(unsigned int value)
	{
		return 0;
	}

	void PixelUtil::packColor(ColorValue::ptr color, const PixelFormat pf, void* dest)
	{
		packColor(color->r(), color->g(), color->b(), color->a(), pf, dest);
	}
	void PixelUtil::packColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a, const PixelFormat pf, void* dest)
	{
		//�������
		unsigned int odr = (unsigned int)pf;
		if (odr < 0 || odr >= PF_COUNT)
		{
			//assert or log
		}
		if (_pixelFormats[odr].flags & PFF_NATIVEENDIAN)
		{
			unsigned int value = ((fixedToFixed(r, 8, _pixelFormats[odr].rbits) << _pixelFormats[odr].rshift) & _pixelFormats[odr].rmask) |
				((fixedToFixed(g, 8, _pixelFormats[odr].gbits) << _pixelFormats[odr].gshift) & _pixelFormats[odr].gmask) |
				((fixedToFixed(b, 8, _pixelFormats[odr].bbits) << _pixelFormats[odr].bshift) & _pixelFormats[odr].bmask) |
				((fixedToFixed(a, 8, _pixelFormats[odr].abits) << _pixelFormats[odr].ashift) & _pixelFormats[odr].amask);
			int_write(dest, _pixelFormats[odr].elemBytes, value);
		}
		else
		{
			packColor((float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f, (float)a / 255.0f, pf, dest);
		}
	}

	void PixelUtil::packColor(float r, float g, float b, float a, PixelFormat pf, void *dest)
	{

	}

	ColorValue::ptr PixelUtil::unpackColor(PixelFormat pf, const void* src)
	{		
		float r, g, b, a;
		unpackColor(&r, &g, &b, &a, pf, src);
		ColorValue *color_ = new ColorValue(r, g, b, a);
		ColorValue::ptr colour_ptr(color_);
		return colour_ptr;
	}
	void PixelUtil::unpackColor(float *r, float *g, float *b, float *a, PixelFormat pf, const void* src)
	{

	}
	void PixelUtil::unpackColor(unsigned char *r, unsigned char *g, unsigned char *b, unsigned char *a, PixelFormat pf, const void* src)
	{
		unsigned int odr = (unsigned int)pf;
		if (odr < 0 || odr > 0)
		{
			//assert or log
		}
		unsigned int value = int_read(src, _pixelFormats[odr].elemBytes);
		//������ͼ
		if (_pixelFormats[odr].flags & PFF_LUMINANCE)
		{
			//����ֻ��Rͨ��
			*r = *g = *b = fixedToFloat((value & _pixelFormats[odr].rmask) >> _pixelFormats[odr].rshift, _pixelFormats[odr].rbits);
		}
		else
		{
			*r = fixedToFloat((value & _pixelFormats[odr].rmask) >> _pixelFormats[odr].rshift, _pixelFormats[odr].rbits);
			*g = fixedToFloat((value & _pixelFormats[odr].gmask) >> _pixelFormats[odr].gshift, _pixelFormats[odr].gbits);
			*b = fixedToFloat((value & _pixelFormats[odr].bmask) >> _pixelFormats[odr].bshift, _pixelFormats[odr].bbits);
		}
		if (_pixelFormats[odr].flags & PFF_HASALPHA)
		{
			*a = fixedToFloat((value & _pixelFormats[odr].amask) >> _pixelFormats[odr].ashift, _pixelFormats[odr].abits);
		}
		else
		{
			*a = 1.0f;
		}
	}
}