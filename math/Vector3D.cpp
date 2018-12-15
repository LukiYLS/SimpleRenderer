#include "Vector3D.h"
#include "Vector4D.h"
#include "Matrix4D.h"
#include "Quaternion.h"
namespace Math {


	Vector3D::Vector3D(const Vector4D& v4)
	{
		x = v4.x;
		y = v4.y;
		z = v4.z;
	}

	Vector3D::~Vector3D()
	{

	}

	void Vector3D::operator=(const Vector4D& vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
	}	

	Vector3D Vector3D::operator* (const Quaternion& quat)const
	{
		double ix = quat.w*x + quat.y*z - quat.z*y;
		double iy = quat.w*y + quat.z*x - quat.x*z;
		double iz = quat.w*z + quat.x*y - quat.y*x;
		double iw = -quat.x*x - quat.y*y - quat.z*z;

		Vector3D result;
		result.x = ix * quat.w + iw * -quat.x + iy * -quat.z - iz * -quat.y;
		result.y = iy * quat.w + iw * -quat.y + iz * -quat.x - ix * -quat.z;
		result.z = iz * quat.w + iw * -quat.z + ix * -quat.y - iy * -quat.x;

		return result;
	}
	
}