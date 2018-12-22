

#include "PickTool.h"
#include "object/camera/Camera.h"
#include <GL/glew.h>
using namespace Math;

#define RGB_WHITE (0xFF | (0xFF<<8) | (0xFF<<16))

namespace SRE
{
	//�Ȱѳ���render to texture��ÿ����������������ͬ������ɫ��Ȼ��ͨ��ʰȡ��ɫ���õ�����������Ϣ
	Vector4D GetColorByIndex(int index)
	{
		int r = index & 0xFF;
		int g = (index >> 8) & 0xFF;
		int b = (index >> 16) & 0xFF;

		return Vector4D(float(r) / 255.0f, float(g) / 255.0f, float(b) / 255.0f, 1.0f);
	}

	int GetIndexByColor(int r, int g, int b)
	{

		return (r) | (g << 8) | (b << 16);
	}

	int GetPickedColorIndexUnderMouse(int x, int y)
	{

		unsigned char bArray[4];
		glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, bArray);
		int iResult = GetIndexByColor(bArray[0], bArray[1], bArray[2]);
		if (iResult == RGB_WHITE)return -1;
		return iResult;
	}

	void Get3DRayUnderMouse(int x, int y,int width, int height, Vector3D* v1, Vector3D* v2,Camera::ptr camera)
	{		

		Vector4D viewport = Vector4D(0.0f, 0.0f, width, height);

		//*v1 = glm::unProject(glm::vec3(float(x), float(y), 0.0f), camera->getViewMatrix(),camera->getProjectMatrix(), viewport);
		//*v2 = glm::unProject(glm::vec3(float(x), float(y), 1.0f), camera->getViewMatrix(), camera->getProjectMatrix(), viewport);
	}

	bool RaySphereCollision(Math::Vector3D vSphereCenter, float fSphereRadius, Math::Vector3D vA, Math::Vector3D vB)
	{
		// Create the vector from end point vA to center of sphere
		Vector3D vDirToSphere = vSphereCenter - vA;

		// Create a normalized direction vector from end point vA to end point vB
		Vector3D vLineDir = (vB - vA).normalize();

		// Find length of line segment
		float fLineLength =(vA - vB).length();

		// Using the dot product, we project the vDirToSphere onto the vector vLineDir
		float t = vDirToSphere.dot(vLineDir);

		Vector3D vClosestPoint;
		// If our projected distance from vA is less than or equal to 0, the closest point is vA
		if (t <= 0.0f)
			vClosestPoint = vA;
		// If our projected distance from vA is greater thatn line length, closest point is vB
		else if (t >= fLineLength)
			vClosestPoint = vB;
		// Otherwise calculate the point on the line using t and return it
		else
			vClosestPoint = vA + vLineDir*t;

		// Now just check if closest point is within radius of sphere
		return (vSphereCenter - vClosestPoint).length() <= fSphereRadius;
	}
}

