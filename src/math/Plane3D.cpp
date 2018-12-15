#include "Plane3D.h"
#define math_tolerance 1e-14
namespace Math {

	Plane3D::Plane3D()
		:_normal(0, 1, 0), _constant(0)
	{

	}

	Plane3D::Plane3D(double distant_to_origin_, const Vector3D& normal_)
		: _constant(distant_to_origin_), _normal(normal_)
	{

	}

	Plane3D::~Plane3D()
	{

	}

	void Plane3D::set(const Vector3D& normal, const double& constant)
	{
		_normal = normal;
		_constant = constant;
	}
	void Plane3D::setComponents(double x, double y, double z, double constant)
	{
		_normal = Vector3D(x, y, z);
		_constant = constant;
	}
	void Plane3D::normalize()
	{
		double inverseNormalLength = 1.0 / _normal.length();
		_normal *= inverseNormalLength;
		_constant *= inverseNormalLength;
	}
	double Plane3D::distanceToPoint(const Vector3D& point) const
	{
		return _normal.dot(point) + _constant;
	}

	bool Plane3D::projectPoint(const Vector3D& origin_vector, Vector3D& out_vector)
	{
		Vector3D tmp_vec(origin_vector);
		tmp_vec.normalize();
		if (fabs(tmp_vec.dot(_normal)) > 1 - math_tolerance)//can not project correct,is this necessary??
		{
			return false;
		}
		else
		{
			out_vector = origin_vector - _normal*(origin_vector*_normal);
		}
		return true;
	}

	bool Plane3D::intersect(const Vector3D& origin, const Vector3D& dir, Vector3D& intersect_point)
	{
		double d = dir.dot(_normal);
		double t = origin.dot(_normal);
		if (fabs(d) < math_tolerance)
		{
			if (fabs(t + _constant) < math_tolerance)
			{
				intersect_point = origin;
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			t = (_constant - t) / d;
			intersect_point = origin + dir*t;
			return true;
		}
	}
}