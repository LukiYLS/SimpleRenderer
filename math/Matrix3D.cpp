#include "Matrix3D.h"
#include "Vector3D.h"
namespace Math {

	const Matrix3D Matrix3D::Zero(0, 0, 0, 0, 0, 0, 0, 0, 0);
	const Matrix3D Matrix3D::Identity(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);
	Vector3D Matrix3D::getColumn(size_t col) const
	{
		return Vector3D(m[0][col], m[1][col], m[2][col]);
	}

	void Matrix3D::setColumn(size_t col, const Vector3D& vec)
	{
		m[0][col] = vec.x;
		m[1][col] = vec.y;
		m[2][col] = vec.z;
	}
	void Matrix3D::fromAxes(const Vector3D& xAxis, const Vector3D& yAxis, const Vector3D& zAxis)
	{
		setColumn(0, xAxis);
		setColumn(1, yAxis);
		setColumn(2, zAxis);
	}	
	//-----------------------------------------------------------------------
	Vector3D Matrix3D::operator* (const Vector3D& rhs) const
	{
		Vector3D kProd;
		for (size_t row = 0; row < 3; row++)
		{
			kProd[row] =
				m[row][0] * rhs[0] +
				m[row][1] * rhs[1] +
				m[row][2] * rhs[2];
		}
		return kProd;
	}
	//-----------------------------------------------------------------------
	Vector3D operator* (const Vector3D& vec, const Matrix3D& matrix)
	{
		Vector3D kProd;
		for (size_t row = 0; row < 3; row++)
		{
			kProd[row] =
				vec.x * matrix.m[0][row] +
				vec.y * matrix.m[1][row] +
				vec.z * matrix.m[2][row];
		}
		return kProd;
	}
	//-----------------------------------------------------------------------

	//-----------------------------------------------------------------------
	Matrix3D operator* (double scale, const Matrix3D& rhs)
	{
		Matrix3D kProd;
		for (size_t row = 0; row < 3; row++)
		{
			for (size_t col = 0; col < 3; col++)
				kProd[row][col] = scale*rhs.m[row][col];
		}
		return kProd;
	}
	//-----------------------------------------------------------------------
	Matrix3D Matrix3D::transpose() const
	{
		Matrix3D kTranspose;
		for (size_t row = 0; row < 3; row++)
		{
			for (size_t col = 0; col < 3; col++)
				kTranspose[row][col] = m[col][row];
		}
		return kTranspose;
	}
	//-----------------------------------------------------------------------
	bool Matrix3D::inverse(Matrix3D& rkInverse, double fTolerance) const
	{		

		rkInverse[0][0] = m[1][1] * m[2][2] -
			m[1][2] * m[2][1];
		rkInverse[0][1] = m[0][2] * m[2][1] -
			m[0][1] * m[2][2];
		rkInverse[0][2] = m[0][1] * m[1][2] -
			m[0][2] * m[1][1];
		rkInverse[1][0] = m[1][2] * m[2][0] -
			m[1][0] * m[2][2];
		rkInverse[1][1] = m[0][0] * m[2][2] -
			m[0][2] * m[2][0];
		rkInverse[1][2] = m[0][2] * m[1][0] -
			m[0][0] * m[1][2];
		rkInverse[2][0] = m[1][0] * m[2][1] -
			m[1][1] * m[2][0];
		rkInverse[2][1] = m[0][1] * m[2][0] -
			m[0][0] * m[2][1];
		rkInverse[2][2] = m[0][0] * m[1][1] -
			m[0][1] * m[1][0];

		double fDet =
			m[0][0] * rkInverse[0][0] +
			m[0][1] * rkInverse[1][0] +
			m[0][2] * rkInverse[2][0];

		if (abs(fDet) <= fTolerance)
			return false;

		double fInvDet = 1.0f / fDet;
		for (size_t row = 0; row < 3; row++)
		{
			for (size_t col = 0; col < 3; col++)
				rkInverse[row][col] *= fInvDet;
		}

		return true;
	}
	
	Matrix3D Matrix3D::inverse(double fTolerance) const
	{
		Matrix3D kInverse = Matrix3D::Zero;
		inverse(kInverse, fTolerance);
		return kInverse;
	}

	double Matrix3D::determinant() const
	{
		double fCofactor00 = m[1][1] * m[2][2] -
			m[1][2] * m[2][1];
		double fCofactor10 = m[1][2] * m[2][0] -
			m[1][0] * m[2][2];
		double fCofactor20 = m[1][0] * m[2][1] -
			m[1][1] * m[2][0];

		double fDet =
			m[0][0] * fCofactor00 +
			m[0][1] * fCofactor10 +
			m[0][2] * fCofactor20;

		return fDet;
	}

	void Matrix3D::fromAngleAxis(const Vector3D& rkAxis, const double& fRadians)
	{
		double fCos = cos(fRadians);
		double fSin = sin(fRadians);
		double fOneMinusCos = 1.0f - fCos;
		double fX2 = rkAxis.x*rkAxis.x;
		double fY2 = rkAxis.y*rkAxis.y;
		double fZ2 = rkAxis.z*rkAxis.z;
		double fXYM = rkAxis.x*rkAxis.y*fOneMinusCos;
		double fXZM = rkAxis.x*rkAxis.z*fOneMinusCos;
		double fYZM = rkAxis.y*rkAxis.z*fOneMinusCos;
		double fXSin = rkAxis.x*fSin;
		double fYSin = rkAxis.y*fSin;
		double fZSin = rkAxis.z*fSin;

		m[0][0] = fX2*fOneMinusCos + fCos;
		m[0][1] = fXYM - fZSin;
		m[0][2] = fXZM + fYSin;
		m[1][0] = fXYM + fZSin;
		m[1][1] = fY2*fOneMinusCos + fCos;
		m[1][2] = fYZM - fXSin;
		m[2][0] = fXZM - fYSin;
		m[2][1] = fYZM + fXSin;
		m[2][2] = fZ2*fOneMinusCos + fCos;
	}
}