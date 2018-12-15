#include "Vector4D.h"
#include "Vector3D.h"
#include "Matrix4D.h"

namespace Math {
	

	Vector4D::Vector4D(const Vector3D& rhs)
		: x(rhs.x), y(rhs.y), z(rhs.z), w(1.0f)
	{
	}

	Vector4D::~Vector4D()
	{

	}
	inline Vector3D Vector4D::xyz() const
	{
		return Vector3D(x, y, z);
	}
	inline Vector4D& Vector4D::operator = (const Vector3D& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = 1.0f;
		return *this;
	}	
	
}