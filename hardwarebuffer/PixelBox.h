#pragma once
#include "ColorValue.h"
namespace SRE {
	enum PixelFormat
	{
		/// Unknown pixel format.
		PF_UNKNOWN = 0,
		/// 8-bit pixel format, all bits luminace.
		PF_L8 = 1,
		PF_BYTE_L = PF_L8,
		/// 16-bit pixel format, all bits luminace.
		PF_L16 = 2,
		PF_SHORT_L = PF_L16,
		/// 8-bit pixel format, all bits alpha.
		PF_A8 = 3,
		PF_BYTE_A = PF_A8,
		/// 8-bit pixel format, 4 bits alpha, 4 bits luminance.
		PF_A4L4 = 4,
		/// 2 byte pixel format, 1 byte luminance, 1 byte alpha
		PF_BYTE_LA = 5,
		/// 16-bit pixel format, 5 bits red, 6 bits green, 5 bits blue.
		PF_R5G6B5 = 6,
		/// 16-bit pixel format, 5 bits red, 6 bits green, 5 bits blue.
		PF_B5G6R5 = 7,
		/// 8-bit pixel format, 2 bits blue, 3 bits green, 3 bits red.
		PF_R3G3B2 = 31,
		/// 16-bit pixel format, 4 bits for alpha, red, green and blue.
		PF_A4R4G4B4 = 8,
		/// 16-bit pixel format, 5 bits for blue, green, red and 1 for alpha.
		PF_A1R5G5B5 = 9,
		/// 24-bit pixel format, 8 bits for red, green and blue.
		PF_R8G8B8 = 10,
		/// 24-bit pixel format, 8 bits for blue, green and red.
		PF_B8G8R8 = 11,
		/// 32-bit pixel format, 8 bits for alpha, red, green and blue.
		PF_A8R8G8B8 = 12,
		/// 32-bit pixel format, 8 bits for blue, green, red and alpha.
		PF_A8B8G8R8 = 13,
		/// 32-bit pixel format, 8 bits for blue, green, red and alpha.
		PF_B8G8R8A8 = 14,
		/// 32-bit pixel format, 8 bits for red, green, blue and alpha.
		PF_R8G8B8A8 = 28,
		/// 32-bit pixel format, 8 bits for red, 8 bits for green, 8 bits for blue
		/// like PF_A8R8G8B8, but alpha will get discarded
		PF_X8R8G8B8 = 26,
		/// 32-bit pixel format, 8 bits for blue, 8 bits for green, 8 bits for red
		/// like PF_A8B8G8R8, but alpha will get discarded
		PF_X8B8G8R8 = 27,

		/// 3 byte pixel format, 1 byte for red, 1 byte for green, 1 byte for blue
		PF_BYTE_RGB = PF_B8G8R8,
		/// 3 byte pixel format, 1 byte for blue, 1 byte for green, 1 byte for red
		PF_BYTE_BGR = PF_R8G8B8,
		/// 4 byte pixel format, 1 byte for blue, 1 byte for green, 1 byte for red and one byte for alpha
		PF_BYTE_BGRA = PF_A8R8G8B8,
		/// 4 byte pixel format, 1 byte for red, 1 byte for green, 1 byte for blue, and one byte for alpha
		PF_BYTE_RGBA = PF_A8B8G8R8,

		/// 32-bit pixel format, 2 bits for alpha, 10 bits for red, green and blue.
		PF_A2R10G10B10 = 15,
		/// 32-bit pixel format, 10 bits for blue, green and red, 2 bits for alpha.
		PF_A2B10G10R10 = 16,
		/// DDS (DirectDraw Surface) DXT1 format
		PF_DXT1 = 17,
		/// DDS (DirectDraw Surface) DXT2 format
		PF_DXT2 = 18,
		/// DDS (DirectDraw Surface) DXT3 format
		PF_DXT3 = 19,
		/// DDS (DirectDraw Surface) DXT4 format
		PF_DXT4 = 20,
		/// DDS (DirectDraw Surface) DXT5 format
		PF_DXT5 = 21,
		// 16-bit pixel format, 16 bits (float) for red
		PF_FLOAT16_R = 32,
		// 48-bit pixel format, 16 bits (float) for red, 16 bits (float) for green, 16 bits (float) for blue
		PF_FLOAT16_RGB = 22,
		// 64-bit pixel format, 16 bits (float) for red, 16 bits (float) for green, 16 bits (float) for blue, 16 bits (float) for alpha
		PF_FLOAT16_RGBA = 23,
		// 32-bit pixel format, 32 bits (float) for red
		PF_FLOAT32_R = 33,
		// 96-bit pixel format, 32 bits (float) for red, 32 bits (float) for green, 32 bits (float) for blue
		PF_FLOAT32_RGB = 24,
		// 128-bit pixel format, 32 bits (float) for red, 32 bits (float) for green, 32 bits (float) for blue, 32 bits (float) for alpha
		PF_FLOAT32_RGBA = 25,
		// 32-bit, 2-channel s10e5 floating point pixel format, 16-bit green, 16-bit red
		PF_FLOAT16_GR = 35,
		// 64-bit, 2-channel floating point pixel format, 32-bit green, 32-bit red
		PF_FLOAT32_GR = 36,
		// Depth texture format
		PF_DEPTH = 29,
		// 64-bit pixel format, 16 bits for red, green, blue and alpha
		PF_SHORT_RGBA = 30,
		// 32-bit pixel format, 16-bit green, 16-bit red
		PF_SHORT_GR = 34,
		// 48-bit pixel format, 16 bits for red, green and blue
		PF_SHORT_RGB = 37,
		/// PVRTC (PowerVR) RGB 2 bpp
		PF_PVRTC_RGB2 = 38,
		/// PVRTC (PowerVR) RGBA 2 bpp
		PF_PVRTC_RGBA2 = 39,
		/// PVRTC (PowerVR) RGB 4 bpp
		PF_PVRTC_RGB4 = 40,
		/// PVRTC (PowerVR) RGBA 4 bpp
		PF_PVRTC_RGBA4 = 41,
		// Number of pixel formats currently defined
		PF_COUNT = 42
	};
	enum PixelFormatFlags {
		/// This format has an alpha channel
		PFF_HASALPHA = 0x00000001,
		/** This format is compressed. This invalidates the values in elemBytes,
		elemBits and the bit counts as these might not be fixed in a compressed format. */
		PFF_COMPRESSED = 0x00000002,
		/// This is a floating point format
		PFF_FLOAT = 0x00000004,
		/// This is a depth format (for depth textures)
		PFF_DEPTH = 0x00000008,
		/** Format is in native endian. Generally true for the 16, 24 and 32 bits
		formats which can be represented as machine integers. */
		PFF_NATIVEENDIAN = 0x00000010,
		/** This is an intensity format instead of a RGB one. The luminance
		replaces R,G and B. (but not A) */
		PFF_LUMINANCE = 0x00000020,
		/// This is an integer format
		PFF_INTEGER = 0x00000040
	};

	/** Pixel component format */
	enum PixelComponentType
	{
		PCT_BYTE = 0,    /// Byte per component (8 bit fixed 0.0..1.0)
		PCT_SHORT = 1,   /// Short per component (16 bit fixed 0.0..1.0))
		PCT_FLOAT16 = 2, /// 16 bit float per component
		PCT_FLOAT32 = 3, /// 32 bit float per component
		PCT_SINT = 4,   /// Signed integer per component
		PCT_UINT = 5,   /// Unsigned integer per component
		PCT_COUNT = 6    /// Number of pixel types
	};
	class PixelBox{
	public:
		typedef std::shared_ptr<PixelBox> ptr;
		PixelBox(unsigned int width, unsigned int height, unsigned int depth, PixelFormat PixelFormat, void *data);
		~PixelBox() {};
	public:
		/**
		* Get colour value from a certain location in the PixelBox. The z coordinate
		* is only valid for cubemaps and volume textures. This uses the first (largest)
		* mipmap.
		*/
		ColorValue::ptr getColourAt(unsigned int x, unsigned int y, unsigned int z);

		/**
		* Set colour value at a certain location in the PixelBox. The z coordinate
		* is only valid for cubemaps and volume textures. This uses the first (largest)
		* mipmap.
		*/
		void setColourAt(ColorValue::ptr color_value, unsigned int x, unsigned int y, unsigned int z);


		 
		/*  get the format of the box*/
		 
		PixelFormat getPixelFormat() const;


		 
		/*  get pixel data*/
		 
		void * getData() const;

		 
		/* set pixel data                    */                                                 
		 
		void setData(void *data);

		 
		/* get/set top */                                                                    
	
		virtual unsigned int getTop() const { return _top; }
		virtual void setTop(unsigned int top) { _top = top; }

	
		/* get bottom                                                                     */
	
		virtual unsigned int getBottom() const { return _bottom; }
		virtual void setBottom(unsigned int bottom) { _bottom = bottom; }

		 
		/* get left                                                                     */
		 
		virtual unsigned int getLeft() const { return _left; }
		virtual void setLeft(unsigned int left) { _left = left; }

		 
		/* get right                                                                     */
		 
		virtual unsigned int getRight() const { return _right; }
		virtual void setRight(unsigned int right) { _right = right; }

		 
		/* get front                                                                     */
		 
		virtual unsigned int getFront() const { return _front; }
		virtual void setFront(unsigned int front) { _front = front; }

		 
		/* get back                                                                     */
		 
		virtual unsigned int getBack() const { return _back; }
		virtual void setBack(unsigned int back) { _back = back; }

		 
		/*  get width*/
		 
		virtual unsigned int getWidth() const;


		 
		/* get height*/
		 
		virtual unsigned int getHeight() const;

		 
		/* get depth(for 3D texture)                                                                     */
		 
		virtual unsigned int getDepth() const;

		 
		/* is contain                                                                     */
		 
		virtual bool isContains(PixelBox::ptr box) const;

		 
		/* �õ����ؿ���Ӽ�                                                                     */
		 
		virtual PixelBox::ptr getSubVolume(PixelBox::ptr box) const;

		unsigned int getRowPitch()const { return _rowPitch; }
		void setRowPitch(unsigned int row_pitch) { _rowPitch = row_pitch; }

		unsigned int getSlicePitch() const { return _slicePitch; }
		void setSlicePitch(unsigned int slice_pitch) { _slicePitch = slice_pitch; }
	public:
	

		void setConsecutive();
		size_t getConsecutive()const;
		void allocateBuffer(size_t _size_in_bytes_);

		void deallocBuffer();
	private:
		void *_data;   //��������
		PixelFormat _format;
		unsigned int _slicePitch;  //��ȿ��֮��ļ��
		unsigned int _rowPitch;    //�м��
		unsigned int  _left, _top, _right, _bottom, _front, _back;


	};
}