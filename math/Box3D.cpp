#include "Box3D.h"
#include <math.h>
namespace Math {

	void Box3D::expandByPoint(const Vector3D& point)
	{
		_min.x = std::min(_min.x, point.x);
		_min.y = std::min(_min.y, point.y);
		_min.z = std::min(_min.z, point.z);

		_max.x = std::max(_max.x, point.x);
		_max.y = std::max(_max.y, point.y);
		_max.z = std::max(_max.z, point.z);
	}
}