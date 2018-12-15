#include "Quaternion.h"
#include "Matrix3D.h"
#include "Matrix4D.h"
#include "Vector3D.h"
#include <math.h>
namespace Math {

	void Quaternion::setFromRotationMatrix(const Matrix4D& rot)
	{
		// http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm

		// assumes the upper 3x3 of m is a pure rotation matrix (i.e, unscaled)


		double	m11 = rot[0], m12 = rot[1], m13 = rot[2];
		double	m21 = rot[4], m22 = rot[5], m23 = rot[6];
		double	m31 = rot[8], m32 = rot[9], m33 = rot[10];

		double trace = m11 + m22 + m33;
		double s;

		if (trace > 0.0) {

			s = 0.5 / sqrt(trace + 1.0);

			w = 0.25 / s;
			x = (m32 - m23) * s;
			y = (m13 - m31) * s;
			z = (m21 - m12) * s;

		}
		else if (m11 > m22 && m11 > m33) {

			s = 2.0 * sqrt(1.0 + m11 - m22 - m33);

			w = (m32 - m23) / s;
			x = 0.25 * s;
			y = (m12 + m21) / s;
			z = (m13 + m31) / s;

		}
		else if (m22 > m33) {

			s = 2.0 * sqrt(1.0 + m22 - m11 - m33);

			w = (m13 - m31) / s;
			x = (m12 + m21) / s;
			y = 0.25 * s;
			z = (m23 + m32) / s;

		}
		else {

			s = 2.0 * sqrt(1.0 + m33 - m11 - m22);

			w = (m21 - m12) / s;
			x = (m13 + m31) / s;
			y = (m23 + m32) / s;
			z = 0.25 * s;

		}
	}

	void Quaternion::toRotationMatrix(Matrix4D& rot) const
	{
		double fTx = x + x;
		double fTy = y + y;
		double fTz = z + z;
		double fTwx = fTx*w;
		double fTwy = fTy*w;
		double fTwz = fTz*w;
		double fTxx = fTx*x;
		double fTxy = fTy*x;
		double fTxz = fTz*x;
		double fTyy = fTy*y;
		double fTyz = fTz*y;
		double fTzz = fTz*z;

		rot[0] = 1.0f - (fTyy + fTzz);
		rot[1] = fTxy - fTwz;
		rot[2] = fTxz + fTwy;
		rot[4] = fTxy + fTwz;
		rot[5] = 1.0f - (fTxx + fTzz);
		rot[6] = fTyz - fTwx;
		rot[8] = fTxz - fTwy;
		rot[9] = fTyz + fTwx;
		rot[10] = 1.0f - (fTxx + fTyy);
	}

	void Quaternion::setFromAxisAngle(const double& angle, const Vector3D axis)
	{
		double fHalfAngle(0.5*angle);
		double fSin = sin(fHalfAngle);
		w = cos(fHalfAngle);
		x = fSin*axis.x;
		y = fSin*axis.y;
		z = fSin*axis.z;
	}

	//-----------------------------------------------------------------------
	float InvSqrt(float x)
	{
		float xhalf = 0.5f*x;
		int i = *(int*)&x;
		i = 0x5f3759df - (i >> 1);
		x = *(float*)&i;
		x = x*(1.5f - xhalf*x*x);
		return x;
	}
	void Quaternion::toAngleAxis(double& angle, Vector3D& axis) const
	{
		// The quaternion representing the rotation is
		//   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)

		double fSqrLength = x*x + y*y + z*z;
		if (fSqrLength > 0.0)
		{
			angle = 2.0*acos(w);
			double fInvLength = InvSqrt(fSqrLength);
			axis.x = x*fInvLength;
			axis.y = y*fInvLength;
			axis.z = z*fInvLength;
		}
		else
		{
			// angle is 0 (mod 2*pi), so any axis will do
			angle = double(0.0);
			axis.x = 1.0;
			axis.y = 0.0;
			axis.z = 0.0;
		}
	}

	void Quaternion::fromAxes(const Vector3D* axis)
	{
		Matrix4D rot;
		for (size_t iCol = 0; iCol < 3; iCol++)
		{
			rot[iCol] = axis[iCol].x;
			rot[iCol + 4] = axis[iCol].y;
			rot[iCol + 8] = axis[iCol].z;
		}
		setFromRotationMatrix(rot);
	}
	
	void Quaternion::fromAxes(const Vector3D& xAxis, const Vector3D& yAxis, const Vector3D& zAxis)
	{
		Matrix4D rot;

		rot[0] = xAxis.x;
		rot[4] = xAxis.y;
		rot[8] = xAxis.z;

		rot[1] = yAxis.x;
		rot[5] = yAxis.y;
		rot[12] = yAxis.z;

		rot[2] = zAxis.x;
		rot[6] = zAxis.y;
		rot[13] = zAxis.z;

		setFromRotationMatrix(rot);

	}
	
	void Quaternion::toAxes(Vector3D* axis) const
	{
		Matrix4D rot;

		toRotationMatrix(rot);

		for (size_t iCol = 0; iCol < 3; iCol++)
		{
			axis[iCol].x = rot[iCol];
			axis[iCol].y = rot[iCol + 4];
			axis[iCol].z = rot[iCol + 8];
		}
	}
	
	Vector3D Quaternion::xAxis(void) const
	{
		//double fTx  = 2.0*x;
		double fTy = 2.0f*y;
		double fTz = 2.0f*z;
		double fTwy = fTy*w;
		double fTwz = fTz*w;
		double fTxy = fTy*x;
		double fTxz = fTz*x;
		double fTyy = fTy*y;
		double fTzz = fTz*z;

		return Vector3D(1.0f - (fTyy + fTzz), fTxy + fTwz, fTxz - fTwy);
	}
	
	Vector3D Quaternion::yAxis(void) const
	{
		double fTx = 2.0f*x;
		double fTy = 2.0f*y;
		double fTz = 2.0f*z;
		double fTwx = fTx*w;
		double fTwz = fTz*w;
		double fTxx = fTx*x;
		double fTxy = fTy*x;
		double fTyz = fTz*y;
		double fTzz = fTz*z;

		return Vector3D(fTxy - fTwz, 1.0f - (fTxx + fTzz), fTyz + fTwx);
	}
	
	Vector3D Quaternion::zAxis(void) const
	{
		double fTx = 2.0f*x;
		double fTy = 2.0f*y;
		double fTz = 2.0f*z;
		double fTwx = fTx*w;
		double fTwy = fTy*w;
		double fTxx = fTx*x;
		double fTxz = fTz*x;
		double fTyy = fTy*y;
		double fTyz = fTz*y;

		return Vector3D(fTxz + fTwy, fTyz - fTwx, 1.0f - (fTxx + fTyy));
	}
	
	void Quaternion::toAxes(Vector3D& xaxis, Vector3D& yaxis, Vector3D& zaxis) const
	{
		Matrix4D rot;

		toRotationMatrix(rot);

		xaxis.x = rot[0];
		xaxis.y = rot[4];
		xaxis.z = rot[8];

		yaxis.x = rot[1];
		yaxis.y = rot[5];
		yaxis.z = rot[9];

		zaxis.x = rot[2];
		zaxis.y = rot[6];
		zaxis.z = rot[10];
	}

	
	Quaternion Quaternion::operator+ (const Quaternion& rkQ) const
	{
		return Quaternion(w + rkQ.w, x + rkQ.x, y + rkQ.y, z + rkQ.z);
	}
	
	Quaternion Quaternion::operator- (const Quaternion& rkQ) const
	{
		return Quaternion(w - rkQ.w, x - rkQ.x, y - rkQ.y, z - rkQ.z);
	}
	
	Quaternion Quaternion::operator* (const Quaternion& rkQ) const
	{
		// NOTE:  Multiplication is not generally commutative, so in most
		// cases p*q != q*p.

		double qax = rkQ.x, qay = rkQ.y, qaz = rkQ.z, qaw = rkQ.w;
		double qbx = x, qby = y, qbz = z, qbw = w;

		return Quaternion(
			qax * qbw + qaw * qbx + qay * qbz - qaz * qby,
			qay * qbw + qaw * qby + qaz * qbx - qax * qbz,
			qaz * qbw + qaw * qbz + qax * qby - qay * qbx,
			qaw * qbw - qax * qbx - qay * qby - qaz * qbz
		);
	}

	Vector3D Quaternion::operator* (const Vector3D& v) const
	{
		// nVidia SDK implementation
		Vector3D uv, uuv;
		Vector3D qvec(x, y, z);
		uv = qvec.cross(v);
		uuv = qvec.cross(uv);
		uv *= (2.0f * w);
		uuv *= 2.0f;

		return v + uv + uuv;

	}

	double Quaternion::getRoll(bool reprojectAxis) const
	{
		if (reprojectAxis)
		{
			// roll = atan2(localx.y, localx.x)
			// pick parts of xAxis() implementation that we need
			//			double fTx  = 2.0*x;
			double fTy = 2.0f*y;
			double fTz = 2.0f*z;
			double fTwz = fTz*w;
			double fTxy = fTy*x;
			double fTyy = fTy*y;
			double fTzz = fTz*z;

			// Vector3(1.0-(fTyy+fTzz), fTxy+fTwz, fTxz-fTwy);

			return double(atan2(fTxy + fTwz, 1.0f - (fTyy + fTzz)));

		}
		else
		{
			return double(atan2(2 * (x*y + w*z), w*w + x*x - y*y - z*z));
		}
	}

	double Quaternion::getPitch(bool reprojectAxis) const
	{
		if (reprojectAxis)
		{
			// pitch = atan2(localy.z, localy.y)
			// pick parts of yAxis() implementation that we need
			double fTx = 2.0f*x;
			//			double fTy  = 2.0f*y;
			double fTz = 2.0f*z;
			double fTwx = fTx*w;
			double fTxx = fTx*x;
			double fTyz = fTz*y;
			double fTzz = fTz*z;

			// Vector3(fTxy-fTwz, 1.0-(fTxx+fTzz), fTyz+fTwx);
			return double(atan2(fTyz + fTwx, 1.0f - (fTxx + fTzz)));
		}
		else
		{
			// internal version
			return double(atan2(2 * (y*z + w*x), w*w - x*x - y*y + z*z));
		}
	}
	
	double Quaternion::getYaw(bool reprojectAxis) const
	{
		if (reprojectAxis)
		{
			// yaw = atan2(localz.x, localz.z)
			// pick parts of zAxis() implementation that we need
			double fTx = 2.0f*x;
			double fTy = 2.0f*y;
			double fTz = 2.0f*z;
			double fTwy = fTy*w;
			double fTxx = fTx*x;
			double fTxz = fTz*x;
			double fTyy = fTy*y;

			// Vector3(fTxz+fTwy, fTyz-fTwx, 1.0-(fTxx+fTyy));

			return double(atan2(fTxz + fTwy, 1.0f - (fTxx + fTyy)));

		}
		else
		{
			// internal version
			return double(asin(-2 * (x*z - w*y)));
		}
	}

	double Quaternion::normalize(void)
	{
		double len = norm();
		double factor = 1.0f / sqrt(len);
		*this = *this * factor;
		return len;
	}

	Quaternion Quaternion::slerp(float t, const Quaternion& first, const Quaternion& second)
	{

		if (t == 0.0f)
			return first;
		if (t == 1.0f)
			return second;

		Quaternion result;	

		double cosHalfTheta = first.w * second.w + first.x * second.x + first.y * second.y + first.z * second.z;

		if (cosHalfTheta < 0) {

			result.w = -second.w;
			result.x = -second.x;
			result.y = -second.y;
			result.z = -second.z;

			cosHalfTheta = -cosHalfTheta;

		}
		else {

			result = second;

		}

		if (cosHalfTheta >= 1.0) {

			result.w = first.w;
			result.x = first.x;
			result.y = first.y;
			result.z = first.z;			

			return result;

		}

		double sinHalfTheta = sqrt(1.0 - cosHalfTheta * cosHalfTheta);

		if (fabs(sinHalfTheta) < 0.001) {

			result.w = 0.5 * (first.w + result.w);
			result.x = 0.5 * (first.x + result.x);
			result.y = 0.5 * (first.y + result.y);
			result.z = 0.5 * (first.z + result.z);

			return result;

		}

		double halfTheta = atan2(sinHalfTheta, cosHalfTheta);
		double ratioA = sin((1 - t) * halfTheta) / sinHalfTheta;
		double ratioB = sin(t * halfTheta) / sinHalfTheta;

		result.w = (first.w * ratioA + result.w * ratioB);
		result.x = (first.x * ratioA + result.x * ratioB);
		result.y = (first.y * ratioA + result.y * ratioB);
		result.z = (first.z * ratioA + result.z * ratioB);	

		return result;
	}
	
}