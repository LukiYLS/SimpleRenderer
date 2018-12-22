#pragma once
#include "graphic/render/Shader.h"
#include "Object3D.h"
#include "Material.h"
#include "math/Box3D.h"
#include "math/Sphere3D.h"
#include "hardwarebuffer/PrimitiveData.h"
using Math::Box3D;
using Math::Sphere3D;

namespace SRE {

	//delete
	struct Vertex
	{
		void setPosition(float x,float y, float z){
			position_x = x;
			position_y = y;
			position_z = z;
		}
		void setPosition(const Vector3D& position) {
			position_x = position.x;
			position_y = position.y;
			position_z = position.z;
		}
		void setNormal(float nx, float ny, float nz) {
			normal_x = nx;
			normal_y = ny;
			normal_z = nz;
		}
		void setNormal(const Vector3D& normal) {
			normal_x = normal.x;
			normal_y = normal.y;
			normal_z = normal.z;
		}
		void setTex(float u, float v){
			texcoord_x = u;
			texcoord_y = v;
		}
		float position_x, position_y, position_z;
		float normal_x, normal_y, normal_z;
		float texcoord_x, texcoord_y;
		float diffuse_x, diffuse_y, diffuse_z;
		float tangent_x, tangent_y, tangent_z;
		float bitangent_x, bitangent_y, bitangent_z;
		Vertex()
		{
			position_x = position_y = position_z = 0;
			normal_x = normal_y = normal_z = 0;
			texcoord_x = texcoord_y = 0;
		}
		Vertex(float px, float py, float pz)
		{
			position_x = px;		position_y = py;		position_z = pz;
			normal_x = normal_y = normal_z = 0;
			texcoord_x = texcoord_y = 0;
		}
		Vertex(float px, float py, float pz, float nx, float ny, float nz)
		{
			position_x = px;		position_y = py;		position_z = pz;
			normal_x = nx;		normal_y = ny;		normal_z = nz;
			texcoord_x = texcoord_y = 0;
		}
		Vertex(float px, float py, float pz, float nx, float ny, float nz, float cx, float cy, float cz)
		{
			position_x = px;	position_y = py;	position_z = pz;
			normal_x = nx;		normal_y = ny;		normal_z = nz;
			diffuse_x = cx;     diffuse_y = cy;     diffuse_z = cz;
			texcoord_x = texcoord_y = 0;
		}
		Vertex(float px, float py, float pz, float tx, float ty)
		{
			position_x = px;		position_y = py;		position_z = pz;
			texcoord_x = tx;		texcoord_y = ty;
			normal_x = normal_y = normal_z = 0;
		}
		Vertex(float px, float py, float pz, float nx, float ny, float nz, float tx, float ty)
		{
			position_x = px;		position_y = py;		position_z = pz;
			normal_x = nx;		normal_y = ny;		normal_z = nz;
			texcoord_x = tx;		texcoord_y = ty;
		}
		Vertex(float px, float py, float pz, float nx, float ny, float nz, float tx, float ty,
			float ttx, float tty, float ttz, float bx, float by, float bz)
		{
			position_x = px;		position_y = py;		position_z = pz;
			normal_x = nx;		normal_y = ny;		normal_z = nz;
			texcoord_x = tx;		texcoord_y = ty;
			tangent_x = ttx;		tangent_y = tty; tangent_z = ttz;
			bitangent_x = bx; bitangent_y = by; bitangent_z = bz;
		}

		Vertex operator=(const Vertex &rhs)
		{
			position_x = rhs.position_x;	position_y = rhs.position_y;	position_z = rhs.position_z;
			normal_x = rhs.normal_x;		normal_y = rhs.normal_y;		normal_z = rhs.normal_z;
			texcoord_x = rhs.texcoord_x;	texcoord_y = rhs.texcoord_y;
			tangent_x = rhs.tangent_x; tangent_y = rhs.tangent_y; tangent_z = rhs.tangent_z;
			bitangent_x = rhs.bitangent_x; bitangent_y = rhs.bitangent_y; bitangent_z = rhs.bitangent_z;
			return (*this);
		}
	};
	enum PrimitiveType {
		/// A list of points, 1 vertex per point
		POINT_LIST = 1,
		/// A list of lines, 2 vertices per line
		LINE_LIST = 2,
		/// A strip of connected lines, 1 vertex per line plus 1 start vertex
		LINE_STRIP = 3,
		/// A list of triangles, 3 vertices per triangle
		TRIANGLE_LIST = 4,
		/// A strip of triangles, 3 vertices for the first triangle, and 1 per triangle after that 
		TRIANGLE_STRIP = 5,
		/// A fan of triangles, 3 vertices for the first triangle, and 1 per triangle after that
		TRIANGLE_FAN = 6
	};
	enum DataType{
		GPU,
		CPU
	};


	/**
	baisc draw primitive
	*/
	class RenderObject
		:public Object3D{
	public:
		typedef std::shared_ptr<RenderObject> ptr;
	public:
		RenderObject();
		virtual ~RenderObject() {}
	public:	

		virtual RenderObject* asRenderObject() { return this; }
		virtual const RenderObject* asRenderObject() const { return this; }
		//�������Ƚϴ�ʱ��Ӳ�������������й���
		void setVertexData(VertexData::ptr data) { _vertex_data = data; }
		void setIndexData(IndexData::ptr data) { _index_data = data; }
		//�������Ƚ�Сʱ��ֱ�ӱ�����vertex
		void setVertexData(std::vector<Vertex> vertices) { _vertices = vertices; }
		void setIndexData(std::vector<unsigned int> indices) { _indices = indices; }

		////////////////////////////
		void pushVertex(Vertex vertex);
		///////////////////////////

		void drawPrimitive();

		void setPrimitiveType(PrimitiveType type) { _type = type; }
		void setVisible(bool isVisible) { _isVisible = isVisible; }	
		//��û������ʱ��ʵ����ɫͨ��material����
		bool isUseColor()const { return _useColor; }		
		void setMaterial(Material::ptr material) { _material = material; }
		Material::ptr getMaterial() const { return _material; }
		//�����󽻣���������Ƭ��
		//virtual void raycast(RayCaster* raycaster, AnyValue& intersects);
		bool getReceiveShadow()const { return _receiveShadow; }
		void setReceiveShadow(bool receive) { _receiveShadow = receive; }
		//
		void computeNormals();
		void computeBoundingBox();
		void computeBoundingSphere();
		void setBoundBox(const Box3D& bbx) { _bbx = bbx; }
		void setBoundSphere(const Sphere3D& bs) { _sphere = bs; }
		//BoundingSphere::ptr getBoundSphere();

	protected:		

		void drawVertex();
		virtual void createBuffer();

		PrimitiveType _type;
		bool _isVisible, _useColor;
		uint32_t _vao, _vbo, _ebo;

		Material::ptr _material;
		bool _receiveShadow;
	
		Box3D _bbx;
		Sphere3D _sphere;

		
		VertexData::ptr _vertex_data;
		IndexData::ptr  _index_data;

		bool _vertexChanged;
		bool _bufferCreated;

		std::vector<Vertex> _vertices;
		std::vector<unsigned int> _indices;
	};
}

