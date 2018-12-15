#pragma once
#include "HardwareBuffer.h"
#include <GL/glew.h>
#include<memory>
namespace SRE {

	//index buffer�� vertex buffer�������ƣ�����ʵ�ַŵ�HardwareBuffer��
	class HardwareIndexBuffer : public HardwareBuffer
	{
	public:
		enum IndexType {
			IT_16BIT,
			IT_32BIT
		};
		typedef std::shared_ptr<HardwareIndexBuffer> ptr;
		HardwareIndexBuffer(IndexType index_type, unsigned int num_indices, HardwareBuffer::Usage usage, bool use_shadow_buffer = false);
		~HardwareIndexBuffer();
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
		GLuint  getBufferID() { return _indexBufferID; }
		unsigned int  getIndexSize() { return _indexSize; }
		IndexType getIndexType() { return _indexType; }
	protected:

		GLuint _indexBufferID;
		IndexType _indexType;
		unsigned int _numIndexes;
		unsigned int _indexSize;
		bool _useShadowBuffer;
		unsigned char* _data;
		unsigned int _sizeInBytes;
		Usage  _usage;
		unsigned int _lockSize;
		unsigned int _lockStart;
		bool _isLocked;
		//���ڴ��ȡ����
		bool   _lockFromPool;
		unsigned int _scrachSize;
		unsigned int _scrachOffset;
		void * _scrachPtr;
		bool _scratchNeedUpload;
	};
}