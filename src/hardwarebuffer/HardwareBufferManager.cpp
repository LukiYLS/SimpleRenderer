#include "HardwareBufferManager.h"
#include "VertexElement.h"
#include <memory>

namespace SRE {


	HardwareBufferManager* HardwareBufferManager::_singleton(0);

	HardwareBufferManager* HardwareBufferManager::getSingletonPtr()
	{
		if (!_singleton)
			_singleton = new HardwareBufferManager();

		return _singleton;
	}


	HardwareBufferManager::~HardwareBufferManager()
	{
		free(_bufferpool);
	}
	HardwareBufferManager::HardwareBufferManager()
	{
		_bufferpool = (char*)malloc(sizeof(char) * POOLSIZE);

		BufferAlloc *ptr = (BufferAlloc*)_bufferpool;
		ptr->size = POOLSIZE - sizeof(BufferAlloc);
		ptr->free = 1;
	}

	void* HardwareBufferManager::allocate(unsigned int size)
	{
		//��������ֽڶ���
		if (size % 4 != 0)
			size += 4 - (size % 4);

		unsigned int bufferpos = 0;

		while (bufferpos < POOLSIZE)
		{
			BufferAlloc* next = (BufferAlloc*)(_bufferpool + bufferpos);

			if (next->free && next->size >= size)
			{
				if (next->size > size + sizeof(BufferAlloc))
				{
					unsigned int offset = (unsigned int)sizeof(BufferAlloc) + size;
					BufferAlloc* split_alloc = (BufferAlloc*)(_bufferpool + bufferpos + offset);
					split_alloc->free = 1;
					split_alloc->size = next->size - sizeof(BufferAlloc) - size;
					next->size = size;
				}
				next->free = 0;
				return ++next;
			}

			bufferpos += sizeof(BufferAlloc) + next->size;
		}

		return 0;
	}

	void HardwareBufferManager::deallocate(void* ptr)	
	{
		unsigned int bufferpos = 0;
		BufferAlloc *last = 0;

		while (bufferpos < POOLSIZE)
		{
			BufferAlloc* current = (BufferAlloc*)(_bufferpool + bufferpos);
			if ((_bufferpool + bufferpos + sizeof(BufferAlloc)) == ptr)
			{
				current->free = 1;
				if (last&& last->free)
				{
					bufferpos -= (last->size + (unsigned int)sizeof(BufferAlloc));
					last->size += current->size + sizeof(BufferAlloc);
					current = last;
				}
				unsigned int offset = bufferpos + current->size + sizeof(BufferAlloc);
				if (offset < POOLSIZE)
				{
					BufferAlloc *next = (BufferAlloc*)(_bufferpool + offset);
					if (next->free)
						current->size += next->size + sizeof(BufferAlloc);
				}

				return;
			}
			bufferpos += (unsigned int)sizeof(BufferAlloc) + current->size;
			last = current;
		}
	}

	VertexDeclaration::ptr HardwareBufferManager::createVertexDeclaration(void)
	{
		VertexDeclaration::ptr vd = std::make_shared<VertexDeclaration>();
		return vd;
	}
	VertexBufferBinding::ptr HardwareBufferManager::createVertexBufferBinding(void)
	{
		VertexBufferBinding::ptr vb = std::make_shared<VertexBufferBinding>();
		return vb;
	}

	GLenum HardwareBufferManager::getGLUsege(unsigned int usage)
	{
		switch (usage)
		{
		case HardwareBuffer::HBU_STATIC:
		case HardwareBuffer::HBU_STATIC_WRITE_ONLY:
			return GL_STATIC_DRAW_ARB;
		case HardwareBuffer::HBU_DYNAMIC:
		case HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY:
			return GL_DYNAMIC_DRAW_ARB;
		case HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE:
			return GL_STREAM_DRAW_ARB;
		default:
			return GL_DYNAMIC_DRAW_ARB;
		};
	}

	GLenum HardwareBufferManager::getGLType(unsigned int type)
	{
		switch (type)
		{
		case VET_FLOAT1:
		case VET_FLOAT2:
		case VET_FLOAT3:
		case VET_FLOAT4:
			return GL_FLOAT;
		case VET_SHORT1:
		case VET_SHORT2:
		case VET_SHORT3:
		case VET_SHORT4:
			return GL_SHORT;
		case VET_COLOUR:
		case VET_COLOUrABGR:
		case VET_COLOUrARGB:
		case VET_UBYTE4:
			return GL_UNSIGNED_BYTE;
		default:
			return 0;
		};
	}


}