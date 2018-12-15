#include "Sphere3D.h"

namespace Math {

	void Sphere3D::expandByPoint(const Vector3D& v)
	{
		Vector3D toCenter = v - _center;
		float length = toCenter.length();
		if (length > _radius)
		{
			float halfLength = (length - _radius) / 2;
			_center += toCenter * (halfLength / length);
			_radius += halfLength;
		}		
	}
	void Sphere3D::expandRadiusBy(const Vector3D& v)
	{
		float toCenterLength = (v - _center).length();
		if (toCenterLength > _radius) _radius = toCenterLength;
	}
	void Sphere3D::expandBy(const Sphere3D& sh) {

		float distance = (_center - sh.center()).length();
		
		if (distance + sh.radius() <= _radius)//inside
		{
			return;
		}		
		if (distance + _radius <= sh.radius())//contain
		{
			_center = sh._center;
			_radius = sh._radius;
			return;
		}
	
		double new_radius = (_radius + distance + sh.radius()) * 0.5;
		double ratio = (new_radius - _radius) / distance;

		_center[0] += (sh.center()[0] - _center[0]) * ratio;
		_center[1] += (sh.center()[1] - _center[1]) * ratio;
		_center[2] += (sh.center()[2] - _center[2]) * ratio;

		_radius = new_radius;
	}
	void Sphere3D::expandRadiusBy(const Sphere3D& sh) {
		float distance = (sh._center - _center).length() + sh._radius;
		if (distance > _radius) _radius = distance;
	}

	void Sphere3D::applyMatrix(const Matrix4D& matrix)
	{
		//center *= matrix;

	}
}