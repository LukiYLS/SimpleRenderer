#pragma once
#include "math/Vector3D.h"
#include "math/Vector4D.h"
namespace SRE {
	
	//����pick�ķ������������⣿

	//framebuffer
	Math::Vector4D GetColorByIndex(int index);
	int GetIndexByColor(int r, int g, int b);
	int GetPickedColorIndexUnderMouse(int x, int y);

	//raycast
	//void Get3DRayUnderMouse(glm::vec3* v1, glm::vec3* v2);
	bool RaySphereCollision(Math::Vector3D vSphereCenter, float fSphereRadius, Math::Vector3D vA, Math::Vector3D vB);

}