#pragma once
#include <memory>
#include "object/RenderObject.h"
namespace SRE {

	class GeometryFactory {

	public:		
		static RenderObject* MakeBox(int width, int height, int depth);
		static RenderObject* MakeSphere(double radius, int widthSegments, int heightSegments);
		static RenderObject* MakeQuad(int width, int height);
		//static Mesh* MakeSphereOld(double radius, int widthSegments, int heightSegments);		
		//static Mesh* MakeCone();
		//static Mesh* MakeTube();
	};
}