#pragma once
#include "HardwareBuffer.h"
#include <GL/glew.h>
#include<memory>
namespace SRE {

	class HardwareVertexBuffer : public HardwareBuffer
	{
	public:
		typedef std::shared_ptr<HardwareVertexBuffer> ptr;
		HardwareVertexBuffer(unsigned int vertex_size, unsigned int num_vertices, HardwareBuffer::Usage usage, bool use_shadow_buffer = false);
		~HardwareVertexBuffer();
	public:

		virtual void*	lock(unsigned int offset, unsigned int length, LockOptions options);
		virtual void*	lock(LockOptions options);
		virtual void	unlock(void);

		virtual void	readData(unsigned int offset, unsigned int length, void* dest);
		virtual void	writeData(unsigned int offset, unsigned int length, const void* source, bool discardWholeBuffer = false);

		//virtual void	copyData(HardwareBuffer& src_buffer, unsigned int src_offset, unsigned int dst_offset, unsigned int length, bool discardWholeBuffer = false);
		//virtual void	copyData(HardwareBuffer& src_buffer);

		virtual unsigned int	getSizeInBytes(void) const { return _sizeInBytes; }
		virtual Usage	getUsage(void) const { return _usage; }

		virtual bool    isLocked(void) const { return _isLocked; }
		virtual bool	isUseShadowBuffer(void) const { return _useShadowBuffer; }
		virtual void    upload(void);
		GLuint  getBufferID() { return _verexBufferID; }
		unsigned int getVertexSize() { return _vertexSize; }
		unsigned int getVertexNum() { return _numVertices; }
	protected:
		GLuint _verexBufferID;//vbo
		unsigned int _numVertices;//
		unsigned int _vertexSize;

		unsigned int _sizeInBytes;
		Usage  _usage;
		bool _isLocked;
		bool _useShadowBuffer;
		unsigned char* _data;

		//���ڴ��ȡ����
		bool   _lockFromPool;
		unsigned int _scrachSize;
		unsigned int _scrachOffset;
		void * _scrachPtr;

		unsigned int _lockSize;
		unsigned int _lockStart;
		
		bool _scratchNeedUpload;
	};
}