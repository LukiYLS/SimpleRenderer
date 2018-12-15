#include "Ray.h"
#include <math.h>
namespace Math {
	
	void Ray::set(const Vector3D& origin, const Vector3D& direction)
	{
		_origin = origin;
		_direction = direction;
	}
	Vector3D Ray::at(const double& distance)
	{
		Vector3D result = _direction * distance;
		return result + _origin;
	}
	double Ray::distanceToPoint(const Vector3D& point)
	{
		return sqrt(distanceSqToPoint(point));
	}
	double Ray::distanceSqToPoint(const Vector3D& point)
	{
		double directionDistance = (point - _origin).dot(_direction);

		if (directionDistance < 0)
			return _origin.squaredDistance(point);

		Vector3D result = _direction * directionDistance + _origin;
		return _origin.squaredDistance(result);
	}
	double Ray::distanceToPlane(const Plane3D& plane)
	{
		//double d = plane.normal.dot(_direction);
		//if (fabs(d) < math_tolerance)
		//{
		//	if (fabs(plane.distanceToPoint(_origin)) < math_tolerance)
		//	{
		//		return 0.0;
		//	}
		//	//
		//}
		//else
		//{

		//}
		return 0.0;
	}

	bool Ray::intersectPlane(const Plane3D& plane, Vector3D& intersect)
	{
		//double d = plane.normal.dot(_direction);
		//double t = plane.normal.dot(_origin); 
		//if (fabs(d) < math_tolerance)
		//{
		//	if (fabs(plane.distanceToPoint(_origin)) < math_tolerance)
		//	{
		//		intersect = _origin;
		//		return true;
		//	}
		//	//
		//	return false;
		//}
		//else
		//{
		//	t = (plane.distance_to_origin - t) / d;
		//	intersect = _origin + _direction*t;
		//	return true;
		//}
		return true;
	}

	bool Ray::intersectSphere(const Sphere3D& sphere, Vector3D& intersect)
	{
		Vector3D v1 = sphere.center() - _origin;
		double tca = v1.dot(_direction);
		double d2 = v1.squaredLength() - tca*tca;
		double radius2 = sphere.radius() * sphere.radius();
		if (d2 > radius2)return false;

		double thc = sqrt(radius2 - d2);
		double t0 = tca - thc;
		double t1 = tca + thc;
		if (t0 < 0 && t1 < 0)return false;
		if (t0 < 0)								
			intersect = at(t1);
		else
			intersect = at(t0);
		return true;
	}

	bool Ray::intersectBox(const Box3D& box, Vector3D& intersect)
	{
		double tmin, tmax, tymin, tymax, tzmin, tzmax;

		double invdirx = 1 / _direction.x,
			invdiry = 1 / _direction.y,
			invdirz = 1 / _direction.z;

		Vector3D origin = _origin;
		if (invdirx >= 0) {

			tmin = (box.xMin() - origin.x) * invdirx;
			tmax = (box.xMax() - origin.x) * invdirx;

		}
		else {

			tmin = (box.xMax() - origin.x) * invdirx;
			tmax = (box.xMin() - origin.x) * invdirx;

		}

		if (invdiry >= 0) {

			tymin = (box.yMin() - origin.y) * invdiry;
			tymax = (box.yMax() - origin.y) * invdiry;

		}
		else {

			tymin = (box.yMax() - origin.y) * invdiry;
			tymax = (box.yMin() - origin.y) * invdiry;

		}

		if ((tmin > tymax) || (tymin > tmax)) return false;

		if (tymin > tmin || tmin != tmin) tmin = tymin;

		if (tymax < tmax || tmax != tmax) tmax = tymax;

		if (invdirz >= 0) {

			tzmin = (box.zMin() - origin.z) * invdirz;
			tzmax = (box.zMax() - origin.z) * invdirz;

		}
		else {

			tzmin = (box.zMax() - origin.z) * invdirz;
			tzmax = (box.zMin() - origin.z) * invdirz;

		}

		if ((tmin > tzmax) || (tzmin > tmax)) return false;

		if (tzmin > tmin || tmin != tmin) tmin = tzmin;

		if (tzmax < tmax || tmax != tmax) tmax = tzmax;

		//return point closest to the ray (positive side)

		if (tmax < 0) return false;

		intersect = at(tmin >= 0 ? tmin : tmax);

		return true;
	}

	bool Ray::intersectTriangle(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3, Vector3D& intersect)
	{
		Vector3D edge1 = v2 - v1;
		Vector3D edge2 = v3 - v1;
		
		Vector3D normal = edge1.cross(edge2);
		

		// Solve Q + t*D = b1*E1 + b2*E2 (Q = kDiff, D = ray direction,
		// E1 = kEdge1, E2 = kEdge2, N = Cross(E1,E2)) by
		//   |Dot(D,N)|*b1 = sign(Dot(D,N))*Dot(D,Cross(Q,E2))
		//   |Dot(D,N)|*b2 = sign(Dot(D,N))*Dot(D,Cross(E1,Q))
		//   |Dot(D,N)|*t = -sign(Dot(D,N))*Dot(Q,N)
		double DdN = _direction.dot(normal);
		int sign;

		if (DdN > 0) {
			
			sign = 1;

		}
		else if (DdN < 0) {

			sign = -1;
			DdN = -DdN;

		}
		else {

			return false;

		}
		Vector3D diff = _origin - v1;
		
		double DdQxE2 = sign * _direction.dot(diff.cross(edge2));

		// b1 < 0, no intersection
		if (DdQxE2 < 0) {

			return false;

		}

		double DdE1xQ = sign * _direction.dot(edge1.cross(diff));

		// b2 < 0, no intersection
		if (DdE1xQ < 0) {

			return false;

		}

		// b1+b2 > 1, no intersection
		if (DdQxE2 + DdE1xQ > DdN) {

			return false;

		}

		// Line intersects triangle, check if ray does.
		double QdN = -sign * diff.dot(normal);

		// t < 0, no intersection
		if (QdN < 0) {

			return false;

		}

		// Ray intersects triangle.
		intersect = at(QdN / DdN);
			return true;
	}

}