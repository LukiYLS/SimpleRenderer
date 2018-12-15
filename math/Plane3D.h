#pragma once
#include "Vector3D.h"
namespace Math {
	class Plane3D {
	public:
		Plane3D();
		Plane3D(double constant, const Vector3D& normal);
		virtual ~Plane3D();
	public:
		double constant()const { return _constant; }
		Vector3D normal()const { return _normal; }
		void set(const Vector3D& normal, const double& constant);
		void setComponents(double x, double y, double z, double constant);
		void normalize();
		double  distanceToPoint(const Vector3D& point) const;
		bool	projectPoint(const Vector3D& origin_vector, Vector3D& out_vector);
		bool    intersect(const Vector3D& origin, const Vector3D& dir, Vector3D& intersect_point);
	protected:
		double _constant;
		Vector3D _normal;
	};
}