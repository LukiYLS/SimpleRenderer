#pragma once
#include "Vector2D.h"
#include <algorithm>
namespace Math {

	class Vector3D;
	class Matrix4D;
	class Vector4D
	{
	public:
		double x, y, z, w;
	public:
		Vector4D()
			:x(0), y(0), z(0), w(0)
		{

		}

		Vector4D(const double& x_, const double& y_, const double& z_, const double& w_)
			: x(x_), y(y_), z(z_), w(w_)
		{

		}
		
		Vector4D(const Vector3D& rhs);
		
		~Vector4D();


		explicit Vector4D(const double coord[4])
			:x(coord[0]),
			y(coord[1]),
			z(coord[2]),
			w(coord[3])
		{
		}
		
		explicit Vector4D(const int coord[4])
		{
			x = (double)coord[0];
			y = (double)coord[1];
			z = (double)coord[2];
			w = (double)coord[3];
		}

		explicit Vector4D(double* const r)
			: x(r[0]), y(r[1]), z(r[2]), w(r[3])
		{
		}

		explicit Vector4D(const double scaler)
			: x(scaler)
			, y(scaler)
			, z(scaler)
			, w(scaler)
		{
		}	
		
		
		Vector3D xyz() const;
		
		Vector2D xy() const
		{
			return Vector2D(x, y);
		}
		
		void swap(Vector4D& other)
		{
			std::swap(x, other.x);
			std::swap(y, other.y);
			std::swap(z, other.z);
			std::swap(w, other.w);
		}

		double operator [] (const size_t i) const
		{
			assert(i < 4);
			return *(&x + i);
		}

		double& operator [] (const size_t i)
		{
			assert(i < 4);
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
		
		Vector4D& operator = (const Vector4D& rhs)
		{
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
			w = rhs.w;

			return *this;
		}

		Vector4D& operator = (const double scale)
		{
			x = scale;
			y = scale;
			z = scale;
			w = scale;
			return *this;
		}

		bool operator == (const Vector4D& rhs) const
		{
			return (x == rhs.x &&
				y == rhs.y &&
				z == rhs.z &&
				w == rhs.w);
		}

		bool operator != (const Vector4D& rhs) const
		{
			return (x != rhs.x ||
				y != rhs.y ||
				z != rhs.z ||
				w != rhs.w);
		}

		Vector4D& operator = (const Vector3D& rhs);
		
		
		Vector4D operator + (const Vector4D& rhs) const
		{
			return Vector4D(
				x + rhs.x,
				y + rhs.y,
				z + rhs.z,
				w + rhs.w);
		}

		Vector4D operator - (const Vector4D& rhs) const
		{
			return Vector4D(
				x - rhs.x,
				y - rhs.y,
				z - rhs.z,
				w - rhs.w);
		}

		Vector4D operator * (const double scale) const
		{
			return Vector4D(
				x * scale,
				y * scale,
				z * scale,
				w * scale);
		}

		Vector4D operator * (const Vector4D& rhs) const
		{
			return Vector4D(
				rhs.x * x,
				rhs.y * y,
				rhs.z * z,
				rhs.w * w);
		}

		Vector4D operator / (const double scale) const
		{
			assert(scale != 0.0);
			double fInv = 1.0f / scale;
			return Vector4D(
				x * fInv,
				y * fInv,
				z * fInv,
				w * fInv);
		}

		Vector4D operator / (const Vector4D& rhs) const
		{
			return Vector4D(
				x / rhs.x,
				y / rhs.y,
				z / rhs.z,
				w / rhs.w);
		}

		const Vector4D& operator + () const
		{
			return *this;
		}

		Vector4D operator - () const
		{
			return Vector4D(-x, -y, -z, -w);
		}

		friend Vector4D operator * (const double scale, const Vector4D& rhs)
		{
			return Vector4D(
				scale * rhs.x,
				scale * rhs.y,
				scale * rhs.z,
				scale * rhs.w);
		}

		friend Vector4D operator / (const double scale, const Vector4D& rhs)
		{
			return Vector4D(
				scale / rhs.x,
				scale / rhs.y,
				scale / rhs.z,
				scale / rhs.w);
		}

		friend Vector4D operator + (const Vector4D& lhs, const double rhs)
		{
			return Vector4D(
				lhs.x + rhs,
				lhs.y + rhs,
				lhs.z + rhs,
				lhs.w + rhs);
		}

		friend Vector4D operator + (const double lhs, const Vector4D& rhs)
		{
			return Vector4D(
				lhs + rhs.x,
				lhs + rhs.y,
				lhs + rhs.z,
				lhs + rhs.w);
		}

		friend Vector4D operator - (const Vector4D& lhs, double rhs)
		{
			return Vector4D(
				lhs.x - rhs,
				lhs.y - rhs,
				lhs.z - rhs,
				lhs.w - rhs);
		}

		friend Vector4D operator - (const double lhs, const Vector4D& rhs)
		{
			return Vector4D(
				lhs - rhs.x,
				lhs - rhs.y,
				lhs - rhs.z,
				lhs - rhs.w);
		}
		
		Vector4D& operator += (const Vector4D& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			w += rhs.w;

			return *this;
		}

		Vector4D& operator -= (const Vector4D& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			w -= rhs.w;

			return *this;
		}

		Vector4D& operator *= (const double scale)
		{
			x *= scale;
			y *= scale;
			z *= scale;
			w *= scale;
			return *this;
		}

		Vector4D& operator += (const double scale)
		{
			x += scale;
			y += scale;
			z += scale;
			w += scale;
			return *this;
		}

		Vector4D& operator -= (const double scale)
		{
			x -= scale;
			y -= scale;
			z -= scale;
			w -= scale;
			return *this;
		}

		Vector4D& operator *= (const Vector4D& rhs)
		{
			x *= rhs.x;
			y *= rhs.y;
			z *= rhs.z;
			w *= rhs.w;

			return *this;
		}

		Vector4D& operator /= (const double scale)
		{
			assert(scale != 0.0);
			double fInv = 1.0f / scale;
			x *= fInv;
			y *= fInv;
			z *= fInv;
			w *= fInv;
			return *this;
		}

		Vector4D& operator /= (const Vector4D& rhs)
		{
			x /= rhs.x;
			y /= rhs.y;
			z /= rhs.z;
			w /= rhs.w;

			return *this;
		}
		
		double dotProduct(const Vector4D& vec) const
		{
			return x * vec.x + y * vec.y + z * vec.z + w * vec.w;
		}
		double length() const {
			return sqrt(x * x + y * y + z * z + w * w);
		}
		double normalize() {
			double scale = length();
			if (scale < 1e-14)
			{
				assert(0);
				return 0;
			}
			x /= scale;
			y /= scale;
			z /= scale;
			w /= scale;
			return scale;
		}
	};
}