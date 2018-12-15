#pragma once
#include "HardwareBuffer.h"
#include "PixelBox.h"
#include <GL/glew.h>
namespace SRE {
	//ogre���OGL��D3D�ֱ�д�˸��Ե�texturebuffer�����̳���pixelbuffer����Ϊ����ֻ����ogl�����Ե���д��texturebuffer
	class HardwareTextureBuffer : public HardwareBuffer{
	public:
	public:
		typedef std::shared_ptr<HardwareTextureBuffer> ptr;
		HardwareTextureBuffer(GLenum target, GLuint id, GLuint face, GLuint level, HardwareBuffer::Usage usage, bool software_mipmap);
		~HardwareTextureBuffer(){}
	public:

		virtual void* lock(unsigned int offset, unsigned int length, LockOptions options);
		virtual void* lock(LockOptions options);
		//
		PixelBox::ptr lock(PixelBox::ptr box, HardwareBuffer::LockOptions options);
		virtual void unlock(void);

		virtual void readData(unsigned int offset, unsigned int length, void* dest){}
		virtual void writeData(unsigned int offset, unsigned int length, const void* source, bool discardWholeBuffer = false){}

		//virtual void	copyData(HardwareBuffer& src_buffer, unsigned int src_offset, unsigned int dst_offset, unsigned int length, bool discardWholeBuffer = false);
		//virtual void	copyData(HardwareBuffer& src_buffer);

		virtual unsigned int getSizeInBytes(void) const { return _sizeInBytes; }
		virtual Usage getUsage(void) const { return _usage; }

		virtual bool isLocked(void) const { return _isLocked; }
		virtual bool isUseShadowBuffer(void) const { return false; }
		virtual void upload(void){}
		//�ϴ��Կ�
		void blitFromMemory(PixelBox::ptr data, PixelBox::ptr dst);
		void blitFromMemory(PixelBox::ptr data);
		void  upload(PixelBox::ptr data, PixelBox::ptr dst);
		void  download(PixelBox::ptr box);
	protected:

		GLenum _target;
		GLenum _faceTarget;
		GLuint _textureID;
		GLuint _face;
		GLuint _level;
		Usage  _usage;
		bool _softwareMipmap;

		unsigned int _width;
		unsigned int _height;
		unsigned int _depth;

		GLenum _internalFormat;
		PixelFormat _format;

		unsigned int _rowPitch;
		unsigned int _slicePitch;

		unsigned int _sizeInBytes;
		PixelBox::ptr _buffer;
		bool _isLocked;

		PixelBox::ptr _currentLockedBuffer;
		PixelBox::ptr _currentLockBox;
		HardwareBuffer::LockOptions _currentLockOptions;
		//bool _useShadowBuffer;
		//unsigned char* _data;
	};
}