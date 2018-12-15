#pragma once
#include "VertexBufferBinding.h"
#include "VertexDeclaration.h"
#include "HardwareIndexBuffer.h"
namespace SRE {

	class VertexData
	{
	public:
		typedef std::shared_ptr<VertexData> ptr;
	public:
		VertexData();
		~VertexData() {};
	public:
		VertexDeclaration::ptr getVertexDeclaration();
		void setVertexDeclaration(VertexDeclaration::ptr vertex_declaration);

		VertexBufferBinding::ptr getVertexBufferBinding();
		void setVertexBufferBinding(VertexBufferBinding::ptr vertex_bufferbinding);

		unsigned int getVertexStart();
		void setVertexStart(unsigned int start);

		unsigned int getVertexCount();
		void setVertexCount(unsigned int count);
	protected:
		VertexDeclaration::ptr _vertex_declaration;
		VertexBufferBinding::ptr _vertex_bufferbinding;
		size_t _vertex_start;
		size_t _vertex_count;
		
	};
	class IndexData {
	public:
		typedef std::shared_ptr<IndexData> ptr;
	public:
		IndexData();
		~IndexData() {};
	public:
		
		HardwareIndexBuffer::ptr getHardwareIndexBuffer();
		void setHardwareIndexBuffer(HardwareIndexBuffer::ptr vertex_bufferbinding);

		unsigned int getIndexStart();
		void setIndexStart(unsigned int start);

		unsigned int getIndexCount();
		void setIndexCount(unsigned int count);
	protected:
		unsigned int _index_start;
		unsigned int _index_count;
		HardwareIndexBuffer::ptr _index_buffer;
	};
}