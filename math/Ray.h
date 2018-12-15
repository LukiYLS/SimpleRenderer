#pragma once
#include "Vector3D.h"
#include "Sphere3D.h"
#include "Box3D.h"
#include "Plane3D.h"
#include <memory>

namespace Math {

	class Ray {
	public:
		typedef std::shared_ptr<Ray> ptr;
		Ray() = default;
		Ray(const Vector3D& origin, const Vector3D& direction)
			:_origin(origin),_direction(direction){}
		~Ray() = default;
	public:
		//according to distance from origin ,return position
		void set(const Vector3D& origin, const Vector3D& direction);
		Vector3D at(const double& distance);
		double distanceToPoint(const Vector3D& point);
		double distanceSqToPoint(const Vector3D& point);
		double distanceToPlane(const Plane3D& plane);
		bool intersectSphere(const Sphere3D& sphere, Vector3D& intersect);
		bool intersectPlane(const Plane3D& plane, Vector3D& intersect);
		bool intersectBox(const Box3D& box, Vector3D& intersect);
		bool intersectTriangle(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3, Vector3D& intersect);
	protected:
		Vector3D _origin;
		Vector3D _direction;
	};
}