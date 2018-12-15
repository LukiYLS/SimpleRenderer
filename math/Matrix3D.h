#pragma once
#include <string.h>
namespace Math {
	class Vector3D;
	class Matrix3D{

	public:
		Matrix3D() = default;
		Matrix3D(const Matrix3D& matrix) {
			memcpy(m, matrix.m, 9 * sizeof(double));
		}
		Matrix3D(double m00, double m01, double m02,
			double m10, double m11, double m12,
			double m20, double m21, double m22)
		{
			m[0][0] = m00;
			m[0][1] = m01;
			m[0][2] = m02;
			m[1][0] = m10;
			m[1][1] = m11;
			m[1][2] = m12;
			m[2][0] = m20;
			m[2][1] = m21;
			m[2][2] = m22;
		}
		const double* operator[] (size_t row) const
		{
			return m[row];
		}
		double* operator[] (size_t row)
		{
			return m[row];
		}
		const double* getMatrix() const
		{
			return &m[0][0];
		}
		Vector3D getColumn(size_t col) const;
		void setColumn(size_t col, const Vector3D& vec);
		void fromAxes(const Vector3D& xAxis, const Vector3D& yAxis, const Vector3D& zAxis);
		
		Matrix3D& operator= (const Matrix3D& rkMatrix)
		{
			memcpy(m, rkMatrix.m, 9 * sizeof(double));
			return *this;
		}		
		
		bool operator!= (const Matrix3D& rkMatrix) const
		{
			return !operator==(rkMatrix);
		}
		
		bool operator== (const Matrix3D& rhs) const
		{
			for (size_t row = 0; row < 3; row++)
			{
				for (size_t col = 0; col < 3; col++)
				{
					if (m[row][col] != rhs.m[row][col])
						return false;
				}
			}

			return true;
		}	
		Matrix3D operator+ (const Matrix3D& rhs) const
		{
			Matrix3D kSum;
			for (size_t row = 0; row < 3; row++)
			{
				for (size_t col = 0; col < 3; col++)
				{
					kSum.m[row][col] = m[row][col] +
						rhs.m[row][col];
				}
			}
			return kSum;
		}
	
		Matrix3D operator- (const Matrix3D& rhs) const
		{
			Matrix3D kDiff;
			for (size_t row = 0; row < 3; row++)
			{
				for (size_t col = 0; col < 3; col++)
				{
					kDiff.m[row][col] = m[row][col] -
						rhs.m[row][col];
				}
			}
			return kDiff;
		}
		
		Matrix3D operator* (const Matrix3D& rhs) const
		{
			Matrix3D kProd;
			for (size_t row = 0; row < 3; row++)
			{
				for (size_t col = 0; col < 3; col++)
				{
					kProd.m[row][col] =
						m[row][0] * rhs.m[0][col] +
						m[row][1] * rhs.m[1][col] +
						m[row][2] * rhs.m[2][col];
				}
			}
			return kProd;
		}
		Matrix3D operator- () const
		{
			Matrix3D kNeg;
			for (size_t row = 0; row < 3; row++)
			{
				for (size_t col = 0; col < 3; col++)
					kNeg[row][col] = -m[row][col];
			}
			return kNeg;
		}
		
		Matrix3D operator* (double scale) const
		{
			Matrix3D kProd;
			for (size_t row = 0; row < 3; row++)
			{
				for (size_t col = 0; col < 3; col++)
					kProd[row][col] = scale*m[row][col];
			}
			return kProd;
		}
		Vector3D operator* (const Vector3D& rkVector) const;
		friend Vector3D operator* (const Vector3D& vec, const Matrix3D& matrix);
		friend Matrix3D operator* (double scale, const Matrix3D& rhs);	

		Matrix3D transpose() const;
		bool inverse(Matrix3D& rkInverse, double fTolerance = 1e-06) const;
		Matrix3D inverse(double fTolerance = 1e-06) const;
		double determinant() const;		
		
		//void toAngleAxis(Vector3D& rkAxis, float& rfAngle);
		//void toAngleAxis(Vector3D& rkAxis, float& rfAngle) const {
		//	float r;
		//	toAngleAxis(rkAxis, r);
		//	rfAngle = r;
		//}
		void fromAngleAxis(const Vector3D& rkAxis, const double& fRadians);
		static const Matrix3D Zero;
		static const Matrix3D Identity;
	protected:
		friend class Matrix4D;
		friend class Quaternion;
		double m[3][3];
	};
}