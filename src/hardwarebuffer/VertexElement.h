#pragma once
#include <memory>

namespace SRE {

	/// Vertex element semantics, used to identify the meaning of vertex buffer contents
	enum Vertex_Element_Semantic {
		/// Position, 3 reals per vertex
		VES_POSITION = 1,
		/// Blending weights
		VES_BLEND_WEIGHTS = 2,
		/// Blending indices
		VES_BLEND_INDICES = 3,
		/// Normal, 3 reals per vertex
		VES_NORMAL = 4,
		/// Diffuse colours
		VES_DIFFUSE = 5,
		/// Specular colours
		VES_SPECULAR = 6,
		/// Texture coordinates
		VES_TEXTURE_COORDINATES = 7,
		/// Binormal (Y axis if normal is Z)
		VES_BINORMAL = 8,
		/// Tangent (X axis if normal is Z)
		VES_TANGENT = 9

	};

	/// Vertex element type, used to identify the base types of the vertex contents
	enum Vertex_Element_Type
	{
		VET_FLOAT1 = 0,
		VET_FLOAT2 = 1,
		VET_FLOAT3 = 2,
		VET_FLOAT4 = 3,
		/// alias to more specific colour type - use the current rendersystem's colour packing
		VET_COLOUR = 4,
		VET_SHORT1 = 5,
		VET_SHORT2 = 6,
		VET_SHORT3 = 7,
		VET_SHORT4 = 8,
		VET_UBYTE4 = 9,
		/// D3D style compact colour
		VET_COLOUrARGB = 10,
		/// GL style compact colour
		VET_COLOUrABGR = 11
	};


	class VertexElement {
	public:
		typedef std::shared_ptr<VertexElement> ptr;
	public:
		VertexElement(unsigned short source, size_t offset, Vertex_Element_Type type,
			Vertex_Element_Semantic semantic, unsigned short index);
		virtual ~VertexElement(){}
	public:
		/// Gets the vertex buffer index from where this element draws it's values
		virtual unsigned short getSource(void) const { return _source; }
		/// Gets the offset into the buffer where this element starts
		virtual size_t getOffset(void) const { return _offset; }
		/// Gets the data format of this element
		virtual Vertex_Element_Type getType(void) const { return _type; }
		/// Gets the meaning of this element
		virtual Vertex_Element_Semantic getSemantic(void) const { return _semantic; }
		/// Gets the index of this element, only applicable for repeating elements
		virtual unsigned short getIndex(void) const { return _index; }
		/// Gets the size of this element in bytes
		virtual size_t getSize(void) const;
		/// Utility method for helping to calculate offsets
		virtual size_t getTypeSize(Vertex_Element_Type etype) const;

	public:
		static unsigned short getTypeCount(Vertex_Element_Type type);

	private:
		unsigned short _source;
		size_t _offset;
		Vertex_Element_Type _type;
		Vertex_Element_Semantic _semantic;
		unsigned short _index;
	};
}