#pragma once
#include <string.h>
#include "RenderObject.h"



namespace SRE {

	class Code
	{
	public:
		Code() {}
		~Code() {}
	public:
		bool operator>(const Code& right_) const;
		bool operator<(const Code& right_) const;
		bool operator==(const Code& geocode) {
			int nRes = memcmp(&mData, &geocode, sizeof(mData));
			if (nRes == 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

	public:

		union {
			struct {
				int x;
				int y;
				int level;
			};
			int mData[3];
		};
	};
	/*
	������Ƭ��LOD������LOD�Ĺ����ǻ����Ĳ�������������ÿ����Ƭ�����ĸ��ӽڵ�
	*/
	class Terrain;
	class TerrainTile
		:public RenderObject {
	public:
		friend class Terrain;
		TerrainTile();
		/************************************************************************/
		/* ������Ƭ�����Ĳ����ָ�,xStart,yStart���½���ʼ������*/
		/************************************************************************/
		TerrainTile(Terrain* terrain, TerrianTile* parent, unsigned int xStart, unsigned int yStart, unsigned int width, unsigned int height, Code code);
		~TerrainTile();

		enum Alignment
		{
			/// ��������XZƽ�棨Ҳ����˵�߶�ֵ������Y�����ϣ�
			ALIGN_X_Z = 0,			
			ALIGN_X_Y = 1,			
			ALIGN_Y_Z = 2
		};
		void updateVertexBuffer(HardwareVertexBuffer::ptr buffer);
		void importHeightMap(float* heightMap);
		RenderObject* createFromRandomHeght(int width, int height);
		RenderObject* createMeshFromHeightmap(const char* fileName);

		size_t getSize()const { return _size; }

		void setWidth(unsigned int width);
		unsigned int getWidth()const;
		void setHeight(unsigned int  height);
		unsigned int getHeight()const;
		Code getCode()const { return _code; }


		
	protected:
		void generateVertex();
		void computerNormal();
		float getHeightValue(const unsigned char* data, unsigned char pixelSize);
	protected:
		int _width, _height;		
	
		Sphere3D _bounding_shpere;
		float *_heightData;
		float _blockScale;
		float _heightScale;

		bool _verticesNeedUpdate;
		bool _heightNeedUpdate;
		Code _code;//�����������е�����
		unsigned int _xStart, _yStart;
		size_t _size;
		TerrianTile* _parent;
		TerrianTile* _children[4];

		Alignment _alignment;
	};
	
}