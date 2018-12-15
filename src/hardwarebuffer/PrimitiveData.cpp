#include "PrimitiveData.h"

#include "HardwareBufferManager.h"
namespace SRE {

	VertexData::VertexData()
	{
		HardwareBufferManager* mgr = HardwareBufferManager::getSingletonPtr();
		_vertex_declaration = mgr->createVertexDeclaration();
		_vertex_bufferbinding = mgr->createVertexBufferBinding();
		_vertex_count = 0;
		_vertex_start = 0;

	}
	VertexDeclaration::ptr VertexData::getVertexDeclaration()
	{
		return _vertex_declaration;
	}
	void VertexData::setVertexDeclaration(VertexDeclaration::ptr vertex_declaration)
	{
		_vertex_declaration = vertex_declaration;
	}

	VertexBufferBinding::ptr VertexData::getVertexBufferBinding()
	{
		return _vertex_bufferbinding;
	}
	void VertexData::setVertexBufferBinding(VertexBufferBinding::ptr vertex_bufferbinding)
	{
		_vertex_bufferbinding = vertex_bufferbinding;
	}

	unsigned int VertexData::getVertexStart()
	{
		return _vertex_start;
	}
	void  VertexData::setVertexStart(unsigned int start)
	{
		_vertex_start = start;
	}
	unsigned int VertexData::getVertexCount()
	{
		return _vertex_count;
	}
	void  VertexData::setVertexCount(unsigned int count)
	{
		_vertex_count = count;
	}

	//============================================================================

	IndexData::IndexData()
	{
		_index_count = 0;
		_index_start = 0;
	}
	void IndexData::setHardwareIndexBuffer(HardwareIndexBuffer::ptr hardware_index_buffer)
	{
		_index_buffer = hardware_index_buffer;
	}
	HardwareIndexBuffer::ptr IndexData::getHardwareIndexBuffer()
	{
		return _index_buffer;
	}

    void IndexData::setIndexStart(unsigned int start)
	{
		_index_start = start;
	}
	unsigned int IndexData::getIndexStart()
	{
		return _index_start;
	}

	void IndexData::setIndexCount(unsigned int count)
	{
		_index_count = count;
	}
	unsigned int IndexData::getIndexCount()
	{
		return _index_count;
	}
}