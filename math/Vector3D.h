#pragma once
#include <math.h>
#include <algorithm>
#include "Vector2D.h"
#include "Quaternion.h"
namespace Math {

	class Vector4D;
	class Matrix4D;
	class Quaternion;
	class Vector3D
	{
	public:
		double x, y, z;
	public:
	
		Vector3D()
			:x(0), y(0), z(0)
		{

		}		
		Vector3D(const double& x_, const double& y_, const double& z_)
			: x(x_), y(y_), z(z_)
		{

		}
		Vector3D(const Vector4D& v4_);

		~Vector3D();

		void operator=(const Vector4D& vec);		

	public:
		explicit Vector3D(const int coord[3])
		{
			x = (double)coord[0];
			y = (double)coord[1];
			z = (double)coord[2];
		}

		explicit Vector3D(double* const r)
			: x(r[0]), y(r[1]), z(r[2])
		{
		}

		explicit Vector3D(const double scaler)
			: x(scaler)
			, y(scaler)
			, z(scaler)
		{
		}

		Vector2D xy() const
		{
			return Vector2D(x, y);
		}
		
		void swap(Vector3D& other)
		{
			std::swap(x, other.x);
			std::swap(y, other.y);
			std::swap(z, other.z);
		}

		double operator [] (const size_t i) const
		{
			return *(&x + i);
		}

		double& operator [] (const size_t i)
		{
			return *(&x + i);
		}		
		double* ptr()
		{
			return &x;
		}		
		const double* ptr() const
		{
			return &x;
		}

		Vector3D& operator = (const Vector3D& rhs)
		{
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;

			return *this;
		}

		Vector3D& operator = (const double scale)
		{
			x = scale;
			y = scale;
			z = scale;

			return *this;
		}

		bool operator == (const Vector3D& rhs) const
		{
			return (x == rhs.x && y == rhs.y && z == rhs.z);
		}

		bool operator != (const Vector3D& rhs) const
		{
			return (x != rhs.x || y != rhs.y || z != rhs.z);
		}

		// arithmetic operations
		Vector3D operator + (const Vector3D& rhs) const
		{
			return Vector3D(
				x + rhs.x,
				y + rhs.y,
				z + rhs.z);
		}

		Vector3D operator - (const Vector3D& rhs) const
		{
			return Vector3D(
				x - rhs.x,
				y - rhs.y,
				z - rhs.z);
		}

		Vector3D operator * (const double scale) const
		{
			return Vector3D(
				x * scale,
				y * scale,
				z * scale);
		}

		Vector3D operator * (const Vector3D& rhs) const
		{
			return Vector3D(
				x * rhs.x,
				y * rhs.y,
				z * rhs.z);
		}

		Vector3D operator* (const Quaternion& quat)const;

		Vector3D operator / (const double scale) const
		{		

			double fInv = 1.0f / scale;

			return Vector3D(
				x * fInv,
				y * fInv,
				z * fInv);
		}

		Vector3D operator / (const Vector3D& rhs) const
		{
			return Vector3D(
				x / rhs.x,
				y / rhs.y,
				z / rhs.z);
		}

		const Vector3D& operator + () const
		{
			return *this;
		}

		Vector3D operator - () const
		{
			return Vector3D(-x, -y, -z);
		}

		Vector3D& operator += (const Vector3D& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;

			return *this;
		}

		Vector3D& operator += (const double scale)
		{
			x += scale;
			y += scale;
			z += scale;
			return *this;
		}

		Vector3D& operator -= (const Vector3D& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;

			return *this;
		}

		Vector3D& operator -= (const double scale)
		{
			x -= scale;
			y -= scale;
			z -= scale;
			return *this;
		}

		Vector3D& operator *= (const double scale)
		{
			x *= scale;
			y *= scale;
			z *= scale;
			return *this;
		}

		Vector3D& operator *= (const Vector3D& rhs)
		{
			x *= rhs.x;
			y *= rhs.y;
			z *= rhs.z;

			return *this;
		}

		Vector3D& operator /= (const Vector3D& rhs)
		{
			x /= rhs.x;
			y /= rhs.y;
			z /= rhs.z;

			return *this;
		}

		Vector3D& operator /= (const double scale)
		{
			//assert(fScalar != 0.0);

			double fInv = 1.0f / scale;

			x *= fInv;
			y *= fInv;
			z *= fInv;

			return *this;
		}

		bool operator < (const Vector3D& rhs) const
		{
			if (x < rhs.x && y < rhs.y && z < rhs.z)
				return true;
			return false;
		}

		bool operator > (const Vector3D& rhs) const
		{
			if (x > rhs.x && y > rhs.y && z > rhs.z)
				return true;
			return false;
		}


	public:
		double length() const
		{
			return sqrt(x * x + y * y + z * z);
		}

		double squaredLength() const
		{
			return x * x + y * y + z * z;
		}

		double distance(const Vector3D& rhs) const
		{
			return (*this - rhs).length();
		}

		double squaredDistance(const Vector3D& rhs) const
		{
			return (*this - rhs).squaredLength();
		}

		double dot(const Vector3D& vec) const
		{
			return x * vec.x + y * vec.y + z * vec.z;
		}
		Vector3D normalize()
		{
			double length = sqrt(x * x + y * y + z * z);			
			if (length > double(0.0f))
			{
				double fInvLength = 1.0f / length;
				x *= fInvLength;
				y *= fInvLength;
				z *= fInvLength;
			}

			return *this;
		}
		Vector3D cross(const Vector3D& rhs) const
		{
			return Vector3D(
				y * rhs.z - z * rhs.y,
				z * rhs.x - x * rhs.z,
				x * rhs.y - y * rhs.x);
		}
		
		Vector3D midPoint(const Vector3D& vec) const
		{
			return Vector3D(
				(x + vec.x) * 0.5f,
				(y + vec.y) * 0.5f,
				(z + vec.z) * 0.5f);
		}
		
		void makeFloor(const Vector3D& cmp)
		{
			if (cmp.x < x) x = cmp.x;
			if (cmp.y < y) y = cmp.y;
			if (cmp.z < z) z = cmp.z;
		}
		
		void makeCeil(const Vector3D& cmp)
		{
			if (cmp.x > x) x = cmp.x;
			if (cmp.y > y) y = cmp.y;
			if (cmp.z > z) z = cmp.z;
		}

		Vector3D reflect(const Vector3D& normal) const
		{
			return Vector3D(*this - (2 * this->dot(normal) * normal));
		}
		Quaternion getRotationTo(const Vector3D& dest, const Vector3D& fallbackAxis = Vector3D(0.0, 0.0, 0.0))
		{
			// Based on Stan Melax's article in Game Programming Gems
			Quaternion q;
			// Copy, since cannot modify local
			Vector3D v0 = *this;
			Vector3D v1 = dest;
			v0.normalize();
			v1.normalize();

			double d = v0.dot(v1);
			// If dot == 1, vectors are the same
			if (d >= 1.0f)
			{
				return Quaternion(0, 0, 0, 1);
			}
			if (d < (1e-6f - 1.0f))
			{
				//if (fallbackAxis != Vector3D(0.0, 0.0, 0.0))
				//{
				//	// rotate 180 degrees about the fallback axis
				//	q.setFromAxisAngle(M_PI, fallbackAxis);
				//}
				//else
				//{
				//	// Generate an axis
				//	Vector3D axis = Vector3D(1,0,0).cross(*this);
				//	if (axis.isZeroLength()) // pick another if colinear
				//		axis = Vector3::UNIT_Y.crossProduct(*this);
				//	axis.normalize();
				//	q.setFromAxisAngle(Radian(Math::PI), axis);
				//}
			}
			else
			{
				double s =sqrt((1 + d) * 2);
				double invs = 1 / s;

				Vector3D c = v0.cross(v1);

				q.x = c.x * invs;
				q.y = c.y * invs;
				q.z = c.z * invs;
				q.w = s * 0.5f;
				q.normalize();
			}
			return q;
		}

	public:
		friend Vector3D operator * ( const double scale, const Vector3D& rhs )
        {
            return Vector3D(
				scale * rhs.x,
				scale * rhs.y,
				scale * rhs.z);
        }

        friend Vector3D operator / ( const double fScalar, const Vector3D& rkVector )
        {
            return Vector3D(
                fScalar / rkVector.x,
                fScalar / rkVector.y,
                fScalar / rkVector.z);
        }

        friend Vector3D operator + (const Vector3D& lhs, const double rhs)
        {
            return Vector3D(
                lhs.x + rhs,
                lhs.y + rhs,
                lhs.z + rhs);
        }

        friend Vector3D operator + (const double lhs, const Vector3D& rhs)
        {
            return Vector3D(
                lhs + rhs.x,
                lhs + rhs.y,
                lhs + rhs.z);
        }

        friend Vector3D operator - (const Vector3D& lhs, const double rhs)
        {
            return Vector3D(
                lhs.x - rhs,
                lhs.y - rhs,
                lhs.z - rhs);
        }

        friend Vector3D operator - (const double lhs, const Vector3D& rhs)
        {
            return Vector3D(
                lhs - rhs.x,
                lhs - rhs.y,
                lhs - rhs.z);
        }

		static Vector3D lerp(const Vector3D& pa, const Vector3D& pb, double scale) {
			double one_scale = 1.0 - scale;
			return Vector3D(
				pa.x * one_scale + pb.x * scale,
				pa.y * one_scale + pb.y * scale,
				pa.z * one_scale + pb.z * scale
			);
		}
	
	};
}

