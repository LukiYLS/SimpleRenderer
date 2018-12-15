#pragma once
#include <GL/glew.h>
#include "HardwareBuffer.h"
#include "HardwareIndexBuffer.h"
#include "HardwareVertexBuffer.h"
#include "VertexDeclaration.h"
#include "VertexBufferBinding.h"
namespace SRE {


	#define DefaultMapBufferThreshold (1024 * 32)//���ڴ��������ֵ
	//32λ�ṹ��λ��
	struct BufferAlloc
	{
		/// Size in bytes
		unsigned int size : 31;
		/// Free? (pack with size)
		unsigned int free : 1;
	};

	#define POOLSIZE 1 * 1024 * 1024
	#define ALIGNMENT 32

	class HardwareBufferManager {
	public:
		HardwareBufferManager();
		~HardwareBufferManager();
	public:
		static HardwareBufferManager& getSingleton(void);
		static HardwareBufferManager* getSingletonPtr(void);
		

		HardwareIndexBuffer::ptr
			createIndexBuffer(HardwareIndexBuffer::IndexType itype, unsigned int num_indexes,
				HardwareBuffer::Usage usage, bool use_shadow_buffer = false);
		HardwareVertexBuffer::ptr createVertexBuffer(unsigned int vertex_size, unsigned int num_verts, HardwareBuffer::Usage usage,
			bool use_shadow_buffer = false);
		VertexDeclaration::ptr createVertexDeclaration(void);

		void destroyVertexDeclaration(VertexDeclaration::ptr decl);

		VertexBufferBinding::ptr createVertexBufferBinding(void);

		void destroyVertexBufferBinding(VertexBufferBinding::ptr binding);

		unsigned int getMapBufferThreshold() { return DefaultMapBufferThreshold; }
		void* allocate(unsigned int size);
		void deallocate(void* ptr);
		static GLenum getGLUsege(unsigned int usage);
		static GLenum getGLType(unsigned int type);
	
		
	protected:
		static HardwareBufferManager* _singleton;
		char* _bufferpool;

	};
}