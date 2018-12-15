#pragma once
#include <GL/glew.h>
#include "PixelBox.h"
#include "ColorValue.h"
namespace SRE {

	class PixelUtil {
	public:
		static bool isCompressed(PixelFormat pixel_format);
		static unsigned int getFlags(PixelFormat format);
		static bool hasAlpha(PixelFormat format);
		static unsigned int getMemorySize(unsigned int width, unsigned int height, unsigned int depth, PixelFormat format);
		static bool isFloatingPoint(PixelFormat format);
		static bool isInteger(PixelFormat format);
//		static bool isCompressed(PixelFormat format);
		static bool isDepth(PixelFormat format);
		static size_t getNumElemBytes(PixelFormat format);
		static void getBitDepths(PixelFormat format, int rgba[4]);

		static void packColor(ColorValue::ptr colour, const PixelFormat pf, void* dest);
		static void packColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a_, PixelFormat pf, void *dest);
		static void packColor(float r, float g, float b, float a, PixelFormat pf, void *dest);
		static ColorValue::ptr unpackColor(PixelFormat pf, const void* src);
		static void unpackColor(unsigned char *r, unsigned char *g, unsigned char *b, unsigned char *a, PixelFormat pf, const void* src);
		static void unpackColor(float *r, float *g, float *b, float *a, PixelFormat pf, const void* src);
									
		static GLenum getGLOriginFormat(PixelFormat format);
		static GLenum getGLOriginDataType(PixelFormat format);
		static GLenum getGLInternalFormat(PixelFormat format, bool hwGamma = false);
		static GLenum getClosestGLInternalFormat(PixelFormat format, bool hwGamma = false);
		static PixelFormat getClosestOGREFormat(GLenum fmt) ;
		static size_t getMaxMipmaps(unsigned int width, unsigned int height, unsigned int depth, PixelFormat format);
		static unsigned int optionalPO2(unsigned int value);
	};
}