#include "TerrainTile.h"
#include "Terrain.h"
namespace SRE {

	TerrainTile::TerrainTile()
	:_blockScale(1.0),
	_heightScale(1.0/10.0){
		

	}
	TerrainTile::TerrainTile(Terrain* terrain, TerrianTile* parent, unsigned int xStart, unsigned int yStart, unsigned int width, unsigned int height, Code code)
	{
		if (terrain->getMaxLevel() < code.level)
		{
			//�����Լ��������ӽڵ�
			unsigned int childWidth = (unsigned int)(((width - 1) * 0.5f) + 1);
			unsigned int childHeight = (unsigned int)(((width - 1) * 0.5f) + 1);
			unsigned int childOffX = childWidth - 1;
			unsigned int childOffY = childHeight - 1;
			unsigned int childLevel = code.level + 1;
			unsigned int xOffset = xStart, yOffset = yStart;
			for (unsigned int i = 0; i < 4; ++i)
			{
				Code childCode;
				childCode.x = code.x * 2 + i % 2;
				childCode.y = code.y * 2 + i / 2;
				childCode.level = code.level + 1;

				if (i == 1)
					xOffset += childOffX;
				if (i == 2)
					yOffset += childOffY;
			
//				_children[i] = new TerrainTile(terrain, this, xOffset, yOffset, childWidth, childHeight, childCode);

			}
		}
		else
		{
			//�ýڵ�Ҷ�ӽڵ�
		}
	}
	
	TerrainTile::~TerrainTile()
	{
		if (_heightData)
			delete[] _heightData;
	}

	void TerrainTile::setWidth(unsigned int width)
	{ 
		_width = width; 
		_verticesNeedUpdate = true;
	}
	unsigned int TerrainTile::getWidth()const 
	{ 
		return _width; 
	}
	void TerrainTile::setHeight(unsigned int  height)
	{ 
		_height = height; 
		_verticesNeedUpdate = true;
	}
	unsigned int TerrainTile::getHeight()const
	{
		return _height;
	}

	void TerrainTile::updateVertexBuffer(HardwareVertexBuffer::ptr buffer)
	{
		//���¸߶���Ϣ����

		//���жϸ����Ƿ񹹽���Ҳ����˵����������Ƿ��Ѿ�����

		if (_verticesNeedUpdate)
		{
			generateVertex();
			_verticesNeedUpdate = false;
			_bufferCreated = false;
		}

		if (_heightNeedUpdate && _heightData)
		{
			for (unsigned int i = 0; i < _height; i++)
				for (unsigned int j = 0; j < _width; j++)
				{
					switch (_alignment)
					{
					case TerrainTile::ALIGN_X_Z:
						_vertices[i*_width + j].position_y = _heightData[i*_width + j];
						break;
					case TerrainTile::ALIGN_X_Y:
						_vertices[i*_width + j].position_z = _heightData[i*_width + j];
						break;
					case TerrainTile::ALIGN_Y_Z:
						_vertices[i*_width + j].position_x = _heightData[i*_width + j];
						break;
					default:
						break;
					}
					
				}
			computeNormals();
			_bufferCreated = false;
		}

	}

	void TerrainTile::importHeightMap(float* heightData)
	{
		//���߶�ֵ
		_heightData = heightData;
		_heightNeedUpdate = true;
	}

	RenderObject* TerrainTile::createFromRandomHeght(int width, int height)
	{
		_width = width;
		_height = height;
		generateVertex();
		for (int i = 0; i < _width*_height; i++)
		{
			_vertices[i].position_y = rand() % 5;
		}
		RenderObject* mesh = new RenderObject;
		mesh->setVertexData(_vertices);
		mesh->setIndexData(_indices);
		mesh->computeNormals();
		return mesh;
	}
	RenderObject* TerrainTile::createMeshFromHeightmap(const char* fileName)
	{		
		Image* image = new Image;
		image->load(fileName);
		unsigned char* data = image->data();
		unsigned char bpp = image->BPP();
		_width = image->width();
		_height = image->height();
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;

		/*unsigned int vertexCount = _width*_height;

		VertexData* vertexdata = new VertexData;
		vertexdata->setVertexStart(0);
		vertexdata->setVertexCount(vertexCount);
		VertexDeclaration::ptr vd = vertexdata->getVertexDeclaration();
		VertexBufferBinding::ptr bind = vertexdata->getVertexBufferBinding();
		size_t offset = 0;
		VertexElement::ptr tmp_ve = vd->addElement(0, offset, VET_FLOAT3, VES_POSITION);
		offset += tmp_ve->getTypeSize(VET_FLOAT3);

		tmp_ve = vd->addElement(0, offset, VET_FLOAT3, VES_NORMAL);
		offset += tmp_ve->getTypeSize(VET_FLOAT3);

		tmp_ve = vd->addElement(0, offset, VET_FLOAT2, VES_TEXTURE_COORDINATES);
		offset += tmp_ve->getTypeSize(VET_FLOAT2);

		HardwareVertexBuffer* vertex_buffer = new HardwareVertexBuffer(offset, vertexCount, HardwareBuffer::HBU_STATIC_WRITE_ONLY);
		bind->setBinding(0, (HardwareVertexBuffer::ptr)vertex_buffer);
		float* pVertex = static_cast<float*>(vertex_buffer->lock(HardwareBuffer::HBL_DISCARD));*/

		float terrainWidth = (_width - 1) * _blockScale;
		float terrainHeight = (_height - 1) * _blockScale;
		float halfTerrainWidth = terrainWidth * 0.5f;
		float halfTerrainHeight = terrainHeight * 0.5f;
		const unsigned int bytesPerPixel = bpp / 8;
		for (unsigned int j = 0; j < _height; ++j)
		{
			for (unsigned i = 0; i < _width; ++i)
			{
				unsigned int index = (j * _width) + i;				
				float heightValue = getHeightValue(&data[index * bytesPerPixel], bytesPerPixel);

				float s = (i / (float)(_width - 1));
				float t = (j / (float)(_height - 1));

				float x = (s * terrainWidth) - halfTerrainWidth;
				float y = heightValue * _heightScale;
				float z = (t * terrainHeight) - halfTerrainHeight;

				Vertex vertex;
				vertex.position_x = x;
				vertex.position_y = y;
				vertex.position_z = z;
				vertex.texcoord_x = s;
				vertex.texcoord_y = t;
				vertices.push_back(vertex);

			}
		}
		/*const unsigned int numTriangles = (_width - 1) * (_height - 1) * 2;
		unsigned int index_count = numTriangles * 3;
		IndexData* indexdata = new IndexData;
		indexdata->setIndexStart(0);
		indexdata->setIndexCount(index_count);
		HardwareIndexBuffer * index_buffer = new HardwareIndexBuffer(HardwareIndexBuffer::IT_16BIT, index_count, HardwareBuffer::HBU_STATIC_WRITE_ONLY);
		indexdata->setHardwareIndexBuffer((HardwareIndexBuffer::ptr)index_buffer);
		unsigned short* pIndices = static_cast<unsigned short*>(index_buffer->lock(HardwareBuffer::HBL_DISCARD));*/

		for (unsigned int j = 0; j < (_height - 1); ++j)
		{
			for (unsigned int i = 0; i < (_width - 1); ++i)
			{
				int vertexIndex = (j * _width) + i;
				indices.push_back(vertexIndex);
				indices.push_back(vertexIndex + terrainWidth + 1);
				indices.push_back(vertexIndex + 1);
				indices.push_back(vertexIndex);
				indices.push_back(vertexIndex + terrainWidth);
				indices.push_back(vertexIndex + terrainWidth + 1);			
			}
		}

		/*vertex_buffer->unlock();
		index_buffer->unlock();*/
		RenderObject* mesh = new RenderObject;
		mesh->setVertexData(vertices);
		mesh->setIndexData(indices);
		mesh->computeNormals();
		//mesh->setVertexData((VertexData::ptr)vertexdata);
	//	mesh->setIndexData((IndexData::ptr)indexdata);

		delete image;
		return mesh;

//		Texture::ptr texture = TextureManager::Inst()->loadTexture("heightmap", fileName);
//
//		_width = texture->getWidth();
//		_height = texture->getHeight();
//
//		HardwareTextureBuffer::ptr buffer = texture->getBuffer(0, 0);		
////		float* data = static_cast<float*>(buffer->lock(HardwareBuffer::HBL_READ_ONLY));
//
//		_data = new float[_width * _height];
//		for (int i = 0; i < _height; i++)
//		{
//			for (int j = 0; j < _width; j++)
//			{
//			//	*_data++ = *data++;
//			//	data += 2;
//			}
//		}
		//FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		//FIBITMAP *dib(0);

		//fif = FreeImage_GetFileType(fileName, 0);

		//if (fif == FIF_UNKNOWN)
		//	fif = FreeImage_GetFIFFromFilename(fileName);

		//if (fif == FIF_UNKNOWN)
		//	return;


		//if (FreeImage_FIFSupportsReading(fif))
		//	dib = FreeImage_Load(fif, fileName);

		//if (!dib)
		//	return;

		//dib = FreeImage_ConvertTo24Bits(dib);

		////BYTE *pixels = (BYTE*)FreeImage_GetBits(dib);

		//_width = FreeImage_GetWidth(dib);
		//_height = FreeImage_GetHeight(dib);

		//if ((_width == 0) || (_height == 0))
		//	return;
		//generateVertex();
		//int byteIndex = 0;
		//for (unsigned int i = 0; i < _height; i++)
		//{
		//	for (unsigned int j = 0; j < _width; j++)
		//	{
		//		RGBQUAD color;
		//		FreeImage_GetPixelColor(dib, j, i, &color);
		//		_vertices[i*_width + j].position_y = color.rgbGreen * 256.0f;
		//	}
		//	
		//}


	}
	float TerrainTile::getHeightValue(const unsigned char* data, unsigned char numBytes)
	{
		switch (numBytes)
		{
		case 1:
		{
			return (unsigned char)(data[0]) /*/ (float)0xff*/;
		}
		break;
		case 2:
		{
			return (unsigned short)(data[1] << 8 | data[0]) /*/ (float)0xffff*/;
		}
		break;
		case 3:
		{
			return (unsigned short)(data[2] << 16/* | data[1] << 8*/ | data[0]) /*/ (float)0xffffff*/;
		}
		case 4:
		{
			return (unsigned int)(data[3] << 24 | data[2] << 16 | data[1] << 8 | data[0]) / (float)0xffffffff;
		}
		break;
		default:
		{
			assert(false);  // Height field with non standard pixle sizes
		}
		break;
		}

		return 0.0f;
	}
	void TerrainTile::generateVertex()
	{
		float halfHeight = (_height - 1) / 2;
		float halfWidth = (_width - 2) / 2;
		for (int i = 0; i < _height; i++)
		{
			for (int j = 0; j < _width; j++)
			{
				//�����������
				float x = j - halfWidth;
				float y = 0.0;
				float z = halfHeight - i;
				switch (_alignment)
				{
				case TerrainTile::ALIGN_X_Z:					
					break;
				case TerrainTile::ALIGN_X_Y:
					std::swap(y, z);
					break;
				case TerrainTile::ALIGN_Y_Z:
					std::swap(y, x);
					break;
				default:
					break;
				}
				Vertex v(x, y, z, 0, 1, 0, j / (_width - 1), 1 - i / (_height - 1));
				_vertices.push_back(v);
			}
		}
		for (int i = 0; i < _height - 1; i++)
		{
			for (int j = 0; j < _width - 1; j++)
			{
				//��������������
				_indices.push_back(i*_width + j);
				_indices.push_back(i*_width + j + 1);
				_indices.push_back((i + 1)*_width + j);

				_indices.push_back((i + 1)*_width + j);
				_indices.push_back(i*_width + j + 1);
				_indices.push_back((i + 1)*_width + j + 1);
			}
		}
	}
}