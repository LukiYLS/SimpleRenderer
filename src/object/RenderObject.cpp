#include "RenderObject.h"
#include "hardwarebuffer/HardwareBufferManager.h"
#include "../tools/RayCaster.h"
namespace SRE {

	RenderObject::RenderObject()
	{
		glGenVertexArrays(1, &_vao);
		_bufferCreated = false;
		_receiveShadow = true;
		_vertexChanged = true;
	}
	void RenderObject::createBuffer()
	{
		VertexData* vertexdata = new VertexData;
		vertexdata->setVertexStart(0);
		vertexdata->setVertexCount(_vertices.size());
		VertexDeclaration::ptr vd = vertexdata->getVertexDeclaration();
		VertexBufferBinding::ptr bind = vertexdata->getVertexBufferBinding();
		unsigned int offset = 0;
		VertexElement::ptr tmp_ve = vd->addElement(0, offset, VET_FLOAT3, VES_POSITION);
		offset += tmp_ve->getTypeSize(VET_FLOAT3);

		tmp_ve = vd->addElement(0, offset, VET_FLOAT3, VES_NORMAL);
		offset += tmp_ve->getTypeSize(VET_FLOAT3);		

		if (_useColor)
		{
			tmp_ve = vd->addElement(0, offset, VET_FLOAT3, VES_DIFFUSE);
			offset += tmp_ve->getTypeSize(VET_FLOAT3);
		}
		else
		{
			tmp_ve = vd->addElement(0, offset, VET_FLOAT2, VES_TEXTURE_COORDINATES);
			offset += tmp_ve->getTypeSize(VET_FLOAT2);
		}

		HardwareVertexBuffer* vertex_buffer = new HardwareVertexBuffer(offset, _vertices.size(), HardwareBuffer::HBU_STATIC_WRITE_ONLY);
		bind->setBinding(0, (HardwareVertexBuffer::ptr)vertex_buffer);
		float* pVertex = static_cast<float*>(vertex_buffer->lock(HardwareBuffer::HBL_DISCARD));

		for (int i = 0; i < _vertices.size(); i++)
		{
			*pVertex++ = _vertices[i].position_x;
			*pVertex++ = _vertices[i].position_y;
			*pVertex++ = _vertices[i].position_z;

			*pVertex++ = _vertices[i].normal_x;
			*pVertex++ = _vertices[i].normal_y;
			*pVertex++ = _vertices[i].normal_z;		

			_bbx.expandByPoint(_vertices[i].position_x, _vertices[i].position_y, _vertices[i].position_z);
			_sphere.expandByPoint(_vertices[i].position_x, _vertices[i].position_y, _vertices[i].position_z);
			//color per vertex
			if (_useColor)
			{
				*pVertex++ = _vertices[i].diffuse_x;
				*pVertex++ = _vertices[i].diffuse_y;
				*pVertex++ = _vertices[i].diffuse_z;
			}
			else
			{
				*pVertex++ = _vertices[i].texcoord_x;
				*pVertex++ = _vertices[i].texcoord_y;
			}
			
		}
		vertex_buffer->unlock();
	
		IndexData* indexdata = new IndexData;
		indexdata->setIndexStart(0);
		indexdata->setIndexCount(_indices.size());
		HardwareIndexBuffer * index_buffer = new HardwareIndexBuffer(HardwareIndexBuffer::IT_16BIT, _indices.size(), HardwareBuffer::HBU_STATIC_WRITE_ONLY);
		indexdata->setHardwareIndexBuffer((HardwareIndexBuffer::ptr)index_buffer);
		unsigned short* pIndices = static_cast<unsigned short*>(index_buffer->lock(HardwareBuffer::HBL_DISCARD));

		for (int i = 0; i < _indices.size(); i++)
		{
			*pIndices++ = _indices[i];
		}
		index_buffer->unlock();
		_vertexChanged = false;
		_bufferCreated = true;
	}

	void RenderObject::drawVertex()
	{
		if(!_bufferCreated)createBuffer();
		GLint prim_type;
		switch (_type)
		{
		case POINT_LIST:
			prim_type = GL_POINTS;
			break;
		case LINE_LIST:
			prim_type = GL_LINES;
			break;
		case LINE_STRIP:
			prim_type = GL_LINE_STRIP;
			break;
		case TRIANGLE_LIST:
			prim_type = GL_TRIANGLES;
			break;
		case TRIANGLE_STRIP:
			prim_type = GL_TRIANGLE_STRIP;
			break;
		case TRIANGLE_FAN:
			prim_type = GL_TRIANGLE_FAN;
			break;
		default:
			prim_type = GL_TRIANGLES;
		}	
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBindVertexArray(_vao);
		if (_indices.empty())
			glDrawArrays(prim_type, 0, _vertices.size());
		else
			glDrawElements(prim_type, _indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
	void RenderObject::drawPrimitive()
	{
		if (_vertices.size() > 0 && !_bufferCreated)
			createBuffer();
			
		if (!_vertex_data)
			return;
		
		glBindVertexArray(_vao);
		VertexElementList elements = _vertex_data->getVertexDeclaration()->getElements();
		for (VertexElementList::iterator iter = elements.begin(); iter != elements.end(); iter++)
		{
			VertexElement::ptr elem = (*iter);
			unsigned int vert_start = _vertex_data->getVertexStart();
			unsigned short source = elem->getSource();
			HardwareVertexBuffer::ptr vertex_buffer = _vertex_data->getVertexBufferBinding()->getBuffer(source);
			if (!vertex_buffer)
				continue;		

			void *buffer_data = 0;

			glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer->getBufferID());

			buffer_data = (void*)elem->getOffset();
			if (vert_start)
			{
				buffer_data = static_cast<char*>(buffer_data) + vert_start * vertex_buffer->getVertexSize();
			}

			Vertex_Element_Semantic sem = elem->getSemantic();

			switch (sem)
			{
			case VES_POSITION:
				glVertexAttribPointer(0,
					VertexElement::getTypeCount(elem->getType()), HardwareBufferManager::getGLType(elem->getType()),
					GL_FALSE, vertex_buffer->getVertexSize(), buffer_data);
				glEnableVertexAttribArray(0);
				break;

			case VES_NORMAL:
				glVertexAttribPointer(1,
					VertexElement::getTypeCount(elem->getType()), HardwareBufferManager::getGLType(elem->getType()),
					GL_FALSE, vertex_buffer->getVertexSize(), buffer_data);
				glEnableVertexAttribArray(1);
				break;

			case VES_TEXTURE_COORDINATES:
				glVertexAttribPointer(2,
					VertexElement::getTypeCount(elem->getType()), HardwareBufferManager::getGLType(elem->getType()),
					GL_FALSE, vertex_buffer->getVertexSize(), buffer_data);
				glEnableVertexAttribArray(2);
				break;

			case VES_DIFFUSE:
				glVertexAttribPointer(3,
					VertexElement::getTypeCount(elem->getType()), HardwareBufferManager::getGLType(elem->getType()),
					GL_FALSE, vertex_buffer->getVertexSize(), buffer_data);
				glEnableVertexAttribArray(3);
				break;			

			default:
				break;
			}
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		GLint prim_type;
		switch (_type)
		{
		case POINT_LIST:
			prim_type = GL_POINTS;
			break;
		case LINE_LIST:
			prim_type = GL_LINES;
			break;
		case LINE_STRIP:
			prim_type = GL_LINE_STRIP;
			break;
		case TRIANGLE_LIST:
			prim_type = GL_TRIANGLES;
			break;
		case TRIANGLE_STRIP:
			prim_type = GL_TRIANGLE_STRIP;
			break;
		case TRIANGLE_FAN:
			prim_type = GL_TRIANGLE_FAN;
			break;
		default:
			prim_type = GL_TRIANGLES;
		}

		if (_index_data)
		{		
			void *buffer_data = 0;
			HardwareIndexBuffer::ptr index_buf = _index_data->getHardwareIndexBuffer();
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buf->getBufferID());
			buffer_data = (char*)NULL + _index_data->getIndexStart() * index_buf->getIndexSize();
			GLenum index_type = (index_buf->getIndexType() == HardwareIndexBuffer::IT_16BIT) ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT;			
			glDrawElements(prim_type, _index_data->getIndexCount(), index_type, buffer_data);
		}
		else
		{
			glDrawArrays(prim_type, 0, _vertex_data->getVertexCount());
		}
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);
		glBindVertexArray(0);
	}
	void RenderObject::computeNormals()
	{		
		if (_vertices.size() == 0)
			return;
		if (_indices.size() > 0)
		{
			for (int i = 0; i < _indices.size(); i += 3)
			{
				int index = _indices[i];
				Vector3D v1 = Vector3D(_vertices[index].position_x, _vertices[index].position_y, _vertices[index].position_z);
				index = _indices[i + 1];
				Vector3D v2 = Vector3D(_vertices[index].position_x, _vertices[index].position_y, _vertices[index].position_z);
				index = _indices[i + 2];
				Vector3D v3 = Vector3D(_vertices[index].position_x, _vertices[index].position_y, _vertices[index].position_z);

				Vector3D v12 = v1 - v2;
				Vector3D v23 = v2 - v3;
				Vector3D normal = v12.cross(v23);
				normal.normalize();
				_vertices[_indices[i]].normal_x += normal.x;
				_vertices[_indices[i]].normal_y += normal.y;
				_vertices[_indices[i]].normal_z += normal.z;

				_vertices[_indices[i + 1]].normal_x += normal.x;
				_vertices[_indices[i + 1]].normal_y += normal.y;
				_vertices[_indices[i + 1]].normal_z += normal.z;

				_vertices[_indices[i + 2]].normal_x += normal.x;
				_vertices[_indices[i + 2]].normal_y += normal.y;
				_vertices[_indices[i + 2]].normal_z += normal.z;

			}
		}
		else
		{

		}
	}
	void RenderObject::computeBoundingBox()
	{

	}
	void RenderObject::computeBoundingSphere()
	{

	}	
	/*void RenderObject::raycast(RayCaster* raycaster, AnyValue& intersects)
	{
		//with boundingbox intersect

	

		Vector3D intersect;
		if (!raycaster->getRay()->intersectSphere(_sphere, intersect))return;

	}*/
}