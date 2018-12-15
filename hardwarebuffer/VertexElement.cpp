#include "VertexElement.h"


namespace SRE {

	VertexElement::VertexElement(unsigned short source, size_t offset, Vertex_Element_Type type,
		Vertex_Element_Semantic semantic, unsigned short index)
		: _source(source), _offset(offset), _type(type), _semantic(semantic), _index(index)
	{

	}

	size_t VertexElement::getSize(void) const
	{
		switch (_type)
		{
		case VET_FLOAT1:
			return sizeof(float);
		case VET_FLOAT2:
			return sizeof(float) * 2;
		case VET_FLOAT3:
			return sizeof(float) * 3;
		case VET_FLOAT4:
			return sizeof(float) * 4;
		case VET_SHORT1:
			return sizeof(short);
		case VET_SHORT2:
			return sizeof(short) * 2;
		case VET_SHORT3:
			return sizeof(short) * 3;
		case VET_SHORT4:
			return sizeof(short) * 4;
		case VET_UBYTE4:
			return sizeof(unsigned char) * 4;
		}
		return 0;
	}

	size_t VertexElement::getTypeSize(Vertex_Element_Type type) const
	{
		switch (type)
		{
		case VET_FLOAT1:
			return sizeof(float);
		case VET_FLOAT2:
			return sizeof(float) * 2;
		case VET_FLOAT3:
			return sizeof(float) * 3;
		case VET_FLOAT4:
			return sizeof(float) * 4;
		case VET_SHORT1:
			return sizeof(short);
		case VET_SHORT2:
			return sizeof(short) * 2;
		case VET_SHORT3:
			return sizeof(short) * 3;
		case VET_SHORT4:
			return sizeof(short) * 4;
		case VET_UBYTE4:
			return sizeof(unsigned char) * 4;
		}
		return 0;
	}
	unsigned short VertexElement::getTypeCount(Vertex_Element_Type type)
	{
		switch (type)
		{
		case VET_COLOUR:
		//case VET_COLOUR_ABGR:
		//case VET_COLOUR_ARGB:
			return 1;
		case VET_FLOAT1:
			return 1;
		case VET_FLOAT2:
			return 2;
		case VET_FLOAT3:
			return 3;
		case VET_FLOAT4:
			return 4;
		case VET_SHORT1:
			return 1;
		case VET_SHORT2:
			return 2;
		case VET_SHORT3:
			return 3;
		case VET_SHORT4:
			return 4;
		case VET_UBYTE4:
			return 4;
		}
	}
}