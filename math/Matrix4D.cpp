#include "Matrix4D.h"
#include "Matrix3D.h"
#include "Quaternion.h"
#include "Vector3D.h"
#include "Vector4D.h"
#define math_tolerance 1e-14

namespace Math {


	const Matrix4D Matrix4D::Identity(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
	Matrix4D::Matrix4D()
	{

	}

	Matrix4D::Matrix4D(const Vector4D& v0, const Vector4D& v1, const Vector4D& v2, const Vector4D& v3)
	{
		_m[0] = v0[0];
		_m[1] = v0[1];
		_m[2] = v0[2];
		_m[3] = v0[3];
		_m[4] = v1[0];
		_m[5] = v1[1];
		_m[6] = v1[2];
		_m[7] = v1[3];
		_m[8] = v2[0];
		_m[9] = v2[1];
		_m[10] = v2[2];
		_m[11] = v2[3];
		_m[12] = v3[0];
		_m[13] = v3[1];
		_m[14] = v3[2];
		_m[15] = v3[3];
	}

	Matrix4D::~Matrix4D()
	{

	}

	Matrix4D::Matrix4D(double a00, double a01, double a02, double a03,
		double a10, double a11, double a12, double a13,
		double a20, double a21, double a22, double a23,
		double a30, double a31, double a32, double a33)
	{
		_m[0] = a00;
		_m[1] = a01;
		_m[2] = a02;
		_m[3] = a03;
		_m[4] = a10;
		_m[5] = a11;
		_m[6] = a12;
		_m[7] = a13;
		_m[8] = a20;
		_m[9] = a21;
		_m[10] = a22;
		_m[11] = a23;
		_m[12] = a30;
		_m[13] = a31;
		_m[14] = a32;
		_m[15] = a33;
	}

	Matrix4D Matrix4D::getInverse()const
	{
		/*double a0 = _m[0] * _m[5] - _m[1] * _m[4];
		double a1 = _m[0] * _m[6] - _m[2] * _m[4];
		double a2 = _m[0] * _m[7] - _m[3] * _m[4];
		double a3 = _m[1] * _m[6] - _m[2] * _m[5];
		double a4 = _m[1] * _m[7] - _m[3] * _m[5];
		double a5 = _m[2] * _m[7] - _m[3] * _m[6];

		double b0 = _m[8] * _m[13] - _m[9] * _m[12];
		double b1 = _m[8] * _m[14] - _m[10] * _m[12];
		double b2 = _m[8] * _m[15] - _m[11] * _m[12];
		double b3 = _m[9] * _m[14] - _m[10] * _m[13];
		double b4 = _m[9] * _m[15] - _m[11] * _m[13];
		double b5 = _m[10] * _m[15] - _m[11] * _m[14];

		// Calculate the determinant.
		double det = a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0;

		if (fabs(det) < math_tolerance)
		{
			return Identity;
		}
		Matrix4D mat4_;
		mat4_[0] = _m[5] * b5 - _m[6] * b4 + _m[7] * b3;
		mat4_[1] = -_m[1] * b5 + _m[2] * b4 - _m[3] * b3;
		mat4_[2] = _m[13] * a5 - _m[14] * a4 + _m[15] * a3;
		mat4_[3] = -_m[9] * a5 + _m[10] * a4 - _m[11] * a3;

		mat4_[4] = -_m[4] * b5 + _m[6] * b2 - _m[7] * b1;
		mat4_[5] = _m[0] * b5 - _m[2] * b2 + _m[3] * b1;
		mat4_[6] = -_m[12] * a5 + _m[14] * a2 - _m[15] * a1;
		mat4_[7] = _m[8] * a5 - _m[10] * a2 + _m[11] * a1;

		mat4_[8] = _m[4] * b4 - _m[5] * b2 + _m[7] * b0;
		mat4_[9] = -_m[0] * b4 + _m[1] * b2 - _m[3] * b0;
		mat4_[10] = _m[12] * a4 - _m[13] * a2 + _m[15] * a0;
		mat4_[11] = -_m[8] * a4 + _m[9] * a2 - _m[11] * a0;

		mat4_[12] = -_m[4] * b3 + _m[5] * b1 - _m[6] * b0;
		mat4_[13] = _m[0] * b3 - _m[1] * b1 + _m[2] * b0;
		mat4_[14] = -_m[12] * a3 + _m[13] * a1 - _m[14] * a0;
		mat4_[15] = _m[8] * a3 - _m[9] * a1 + _m[10] * a0;
		mat4_ = mat4_*(1.0 / det);
		return mat4_;*/


		

		double	n11 = _m[0], n21 = _m[1], n31 = _m[2], n41 = _m[3];
		double	n12 = _m[4], n22 = _m[5], n32 = _m[6], n42 = _m[7];
		double	n13 = _m[8], n23 = _m[9], n33 = _m[10], n43 = _m[11];
		double	n14 = _m[12], n24 = _m[13], n34 = _m[14], n44 = _m[15];

		double	t11 = n23 * n34 * n42 - n24 * n33 * n42 + n24 * n32 * n43 - n22 * n34 * n43 - n23 * n32 * n44 + n22 * n33 * n44;
		double  t12 = n14 * n33 * n42 - n13 * n34 * n42 - n14 * n32 * n43 + n12 * n34 * n43 + n13 * n32 * n44 - n12 * n33 * n44;
		double  t13 = n13 * n24 * n42 - n14 * n23 * n42 + n14 * n22 * n43 - n12 * n24 * n43 - n13 * n22 * n44 + n12 * n23 * n44;
		double	t14 = n14 * n23 * n32 - n13 * n24 * n32 - n14 * n22 * n33 + n12 * n24 * n33 + n13 * n22 * n34 - n12 * n23 * n34;

		double det = n11 * t11 + n21 * t12 + n31 * t13 + n41 * t14;

		if (fabs(det) < math_tolerance)
		{
			return Identity;
		}

		double detInv = 1 / det;
		Matrix4D mat;
		mat[0] = t11 * detInv;
		mat[1] = (n24 * n33 * n41 - n23 * n34 * n41 - n24 * n31 * n43 + n21 * n34 * n43 + n23 * n31 * n44 - n21 * n33 * n44) * detInv;
		mat[2] = (n22 * n34 * n41 - n24 * n32 * n41 + n24 * n31 * n42 - n21 * n34 * n42 - n22 * n31 * n44 + n21 * n32 * n44) * detInv;
		mat[3] = (n23 * n32 * n41 - n22 * n33 * n41 - n23 * n31 * n42 + n21 * n33 * n42 + n22 * n31 * n43 - n21 * n32 * n43) * detInv;

		mat[4] = t12 * detInv;
		mat[5] = (n13 * n34 * n41 - n14 * n33 * n41 + n14 * n31 * n43 - n11 * n34 * n43 - n13 * n31 * n44 + n11 * n33 * n44) * detInv;
		mat[6] = (n14 * n32 * n41 - n12 * n34 * n41 - n14 * n31 * n42 + n11 * n34 * n42 + n12 * n31 * n44 - n11 * n32 * n44) * detInv;
		mat[7] = (n12 * n33 * n41 - n13 * n32 * n41 + n13 * n31 * n42 - n11 * n33 * n42 - n12 * n31 * n43 + n11 * n32 * n43) * detInv;

		mat[8] = t13 * detInv;
		mat[9] = (n14 * n23 * n41 - n13 * n24 * n41 - n14 * n21 * n43 + n11 * n24 * n43 + n13 * n21 * n44 - n11 * n23 * n44) * detInv;
		mat[10] = (n12 * n24 * n41 - n14 * n22 * n41 + n14 * n21 * n42 - n11 * n24 * n42 - n12 * n21 * n44 + n11 * n22 * n44) * detInv;
		mat[11] = (n13 * n22 * n41 - n12 * n23 * n41 - n13 * n21 * n42 + n11 * n23 * n42 + n12 * n21 * n43 - n11 * n22 * n43) * detInv;

		mat[12] = t14 * detInv;
		mat[13] = (n13 * n24 * n31 - n14 * n23 * n31 + n14 * n21 * n33 - n11 * n24 * n33 - n13 * n21 * n34 + n11 * n23 * n34) * detInv;
		mat[14] = (n14 * n22 * n31 - n12 * n24 * n31 - n14 * n21 * n32 + n11 * n24 * n32 + n12 * n21 * n34 - n11 * n22 * n34) * detInv;
		mat[15] = (n12 * n23 * n31 - n13 * n22 * n31 + n13 * n21 * n32 - n11 * n23 * n32 - n12 * n21 * n33 + n11 * n22 * n33) * detInv;

		return mat;
	}

	Matrix3D Matrix4D::getMatrix3x3() const
	{
		Matrix3D m3x3;
		m3x3.m[0][0] = m[0][0];
		m3x3.m[0][1] = m[0][1];
		m3x3.m[0][2] = m[0][2];
		m3x3.m[1][0] = m[1][0];
		m3x3.m[1][1] = m[1][1];
		m3x3.m[1][2] = m[1][2];
		m3x3.m[2][0] = m[2][0];
		m3x3.m[2][1] = m[2][1];
		m3x3.m[2][2] = m[2][2];
		return m3x3;

	}

	void Matrix4D::decompose(Vector3D& position, Vector3D& scale, Quaternion& orientation)
	{
		double lx = Vector3D(_m[0], _m[1], _m[2]).length();
		double ly = Vector3D(_m[4], _m[5], _m[6]).length();
		double lz = Vector3D(_m[8], _m[9], _m[10]).length();

		double det = determinant();
		if (det < 0)
			lx = -lx;
		position.x = _m[12];
		position.y = _m[13];
		position.z = _m[14];		
		
		double invLx = 1 / lx;
		double invLy = 1 / ly;
		double invLz = 1 / lz;

		Matrix4D copy = *this;

		copy[0] *= invLx;
		copy[1] *= invLx;
		copy[2] *= invLx;

		copy[4] *= invLy;
		copy[5] *= invLy;
		copy[6] *= invLy;

		copy[8] *= invLz;
		copy[9] *= invLz;
		copy[10] *= invLz;

		orientation.setFromRotationMatrix(copy);

		scale.x = lx;
		scale.y = ly;
		scale.z = lz;

	}

	void Matrix4D::scale(const Vector3D& scale)
	{		
		double x = scale.x, y = scale.y, z = scale.z;

		_m[0] *= x; _m[4] *= y; _m[8] *= z;
		_m[1] *= x; _m[5] *= y; _m[9] *= z;
		_m[2] *= x; _m[6] *= y; _m[10] *= z;
		_m[3] *= x; _m[7] *= y; _m[11] *= z;		
	}
	void Matrix4D::setPosition(const Vector3D& pos)
	{
		_m[12] = pos.x;
		_m[13] = pos.y;
		_m[14] = pos.z;
	}

	Vector4D Matrix4D::operator*(const Vector4D& v) const
	{
		return Vector4D(
			m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w,
			m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w,
			m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w,
			m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w
		);
	}
	
	Vector3D Matrix4D::operator*(const Vector3D& v) const
	{
		Vector3D r;

		double fInvW = 1.0f / (m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3]);

		r.x = (m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3]) * fInvW;
		r.y = (m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3]) * fInvW;
		r.z = (m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3]) * fInvW;

		return r;
	}

	Matrix4D Matrix4D::operator*(const Matrix4D& m2) const
	{
		return Matrix4D(
			_m[0] * m2[0] + _m[4] * m2[1] + _m[8] * m2[2] + _m[12] * m2[3],
			_m[1] * m2[0] + _m[5] * m2[1] + _m[9] * m2[2] + _m[13] * m2[3],
			_m[2] * m2[0] + _m[6] * m2[1] + _m[10] * m2[2] + _m[14] * m2[3],
			_m[3] * m2[0] + _m[7] * m2[1] + _m[11] * m2[2] + _m[15] * m2[3],

			_m[0] * m2[4] + _m[4] * m2[5] + _m[8] * m2[6] + _m[12] * m2[7],
			_m[1] * m2[4] + _m[5] * m2[5] + _m[9] * m2[6] + _m[13] * m2[7],
			_m[2] * m2[4] + _m[6] * m2[5] + _m[10] * m2[6] + _m[14] * m2[7],
			_m[3] * m2[4] + _m[7] * m2[5] + _m[11] * m2[6] + _m[15] * m2[7],

			_m[0] * m2[8] + _m[4] * m2[9] + _m[8] * m2[10] + _m[12] * m2[11],
			_m[1] * m2[8] + _m[5] * m2[9] + _m[9] * m2[10] + _m[13] * m2[11],
			_m[2] * m2[8] + _m[6] * m2[9] + _m[10] * m2[10] + _m[14] * m2[11],
			_m[3] * m2[8] + _m[7] * m2[9] + _m[11] * m2[10] + _m[15] * m2[11],

			_m[0] * m2[12] + _m[4] * m2[13] + _m[8] * m2[14] + _m[12] * m2[15],
			_m[1] * m2[12] + _m[5] * m2[13] + _m[9] * m2[14] + _m[13] * m2[15],
			_m[2] * m2[12] + _m[6] * m2[13] + _m[10] * m2[14] + _m[14] * m2[15],
			_m[3] * m2[12] + _m[7] * m2[13] + _m[11] * m2[14] + _m[15] * m2[15]
		);
	}

	void Matrix4D::operator = (const Matrix3D& mat3)
	{
		m[0][0] = mat3.m[0][0]; m[0][1] = mat3.m[0][1]; m[0][2] = mat3.m[0][2];
		m[1][0] = mat3.m[1][0]; m[1][1] = mat3.m[1][1]; m[1][2] = mat3.m[1][2];
		m[2][0] = mat3.m[2][0]; m[2][1] = mat3.m[2][1]; m[2][2] = mat3.m[2][2];
	}

	double Matrix4D::determinant() const
	{
		double a0 = _m[0] * _m[5] - _m[1] * _m[4];
		double a1 = _m[0] * _m[6] - _m[2] * _m[4];
		double a2 = _m[0] * _m[7] - _m[3] * _m[4];
		double a3 = _m[1] * _m[6] - _m[2] * _m[5];
		double a4 = _m[1] * _m[7] - _m[3] * _m[5];
		double a5 = _m[2] * _m[7] - _m[3] * _m[6];
		double b0 = _m[8] * _m[13] - _m[9] * _m[12];
		double b1 = _m[8] * _m[14] - _m[10] * _m[12];
		double b2 = _m[8] * _m[15] - _m[11] * _m[12];
		double b3 = _m[9] * _m[14] - _m[10] * _m[13];
		double b4 = _m[9] * _m[15] - _m[11] * _m[13];
		double b5 = _m[10] * _m[15] - _m[11] * _m[14];
		double det = a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;
		return det;
	}

	Matrix4D Matrix4D::getTranspose() const
	{
		return Matrix4D(
			_m[0], _m[4], _m[8], _m[12],
			_m[1], _m[5], _m[9], _m[13],
			_m[2], _m[6], _m[10], _m[14],
			_m[3], _m[7], _m[11], _m[15]
		);
	}

	Matrix4D Matrix4D::makeIdentity()
	{
		return Matrix4D(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		);
	}

	Matrix4D Matrix4D::makeRotationFromQuaternion(const Quaternion& orientation)
	{		

		double x = orientation.x, y = orientation.y, z = orientation.z, w = orientation.w;
		double x2 = x + x, y2 = y + y, z2 = z + z;
		double xx = x * x2, xy = x * y2, xz = x * z2;
		double yy = y * y2, yz = y * z2, zz = z * z2;
		double wx = w * x2, wy = w * y2, wz = w * z2;

		Matrix4D mat;
		mat[0] = 1 - (yy + zz);
		mat[4] = xy - wz;
		mat[8] = xz + wy;

		mat[1] = xy + wz;
		mat[5] = 1 - (xx + zz);
		mat[9] = yz - wx;

		mat[2] = xz - wy;
		mat[6] = yz + wx;
		mat[10] = 1 - (xx + yy);

		// last column
		mat[3] = 0;
		mat[7] = 0;
		mat[11] = 0;

		// bottom row
		mat[12] = 0;
		mat[13] = 0;
		mat[14] = 0;
		mat[15] = 1;

		return mat;
	}
	
	Matrix4D Matrix4D::makeTransformMatrix(const Vector3D& position, const Vector3D& scale, const Quaternion& orientation)
	{
		Matrix4D rot = Matrix4D::makeRotationFromQuaternion(orientation);	
		rot.scale(scale);
		rot.setPosition(position);	
		return rot;
	}

	Matrix4D Matrix4D::makeRotationAxis(const Vector3D& axis, double angle_in_rad)
	{
		double ax = axis[0];
		double ay = axis[1];
		double az = axis[2];
		// Make sure the input axis is normalized.
		double n = ax*ax + ay*ay + az*az;
		if (n != 1.0)
		{
			// Not normalized.
			n = sqrt(n);
			// Prevent divide too close to zero.
			if (n > 0.000001)
			{
				n = 1.0f / n;
				ax *= n;
				ay *= n;
				az *= n;
			}
		}
		double c = cos(angle_in_rad);
		double s = sin(angle_in_rad);
		double t = 1 - c;
		double x = axis.x, y = axis.y, z = axis.z;
		double tx = t * x, ty = t * y;
		return Matrix4D(
			tx * x + c, tx * y - s * z, tx * z + s * y, 0,
			tx * y + s * z, ty * y + c, ty * z - s * x, 0,
			tx * z - s * y, ty * z + s * x, t * z * z + c, 0,
			0, 0, 0, 1
		);
	}
	Matrix4D Matrix4D::makeRotationX(const double& angle_in_rad)
	{
		double c = cos(angle_in_rad), s = sin(angle_in_rad);
		return Matrix4D(
			1, 0, 0, 0,
			0, c, s, 0,
			0, -s, c, 0,
			0, 0, 0, 1

		);	
	}
	Matrix4D Matrix4D::makeRotationY(const double& angle_in_rad)
	{
		double c = cos(angle_in_rad), s = sin(angle_in_rad);

		return Matrix4D(
			c, 0, -s, 0,
			0, 1, 0, 0,
			s, 0, c, 0,
			0, 0, 0, 1
		);
	}
	Matrix4D Matrix4D::makeRotationZ(const double& angle_in_rad)
	{
		double c = cos(angle_in_rad), s = sin(angle_in_rad);

		return Matrix4D(
			c, s, 0, 0,
			-s, c, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		);
	}

	Matrix4D Matrix4D::makeTranslation(double x, double y, double z) {
		return makeTranslation(Vector3D(x, y, z));
	}

	Matrix4D Matrix4D::makeTranslation(const Vector3D& trans)
	{
		Matrix4D r;
		r.m[0][0] = 1.0; r.m[0][1] = 0.0; r.m[0][2] = 0.0; r.m[0][3] = 0.0;
		r.m[1][0] = 0.0; r.m[1][1] = 1.0; r.m[1][2] = 0.0; r.m[1][3] = 0.0;
		r.m[2][0] = 0.0; r.m[2][1] = 0.0; r.m[2][2] = 1.0; r.m[2][3] = 0.0;
		r.m[3][0] = trans.x; r.m[3][1] = trans.y; r.m[3][2] = trans.z; r.m[3][3] = 1.0;

		return r;
	}

	Matrix4D Matrix4D::makeScale(double x, double y, double z) {
		return makeScale(Vector3D(x, y, z));
	}

	Matrix4D Matrix4D::makeScale(const Vector3D& scale)
	{
		Matrix4D r;
		r.m[0][0] = scale.x; r.m[0][1] = 0.0; r.m[0][2] = 0.0; r.m[0][3] = 0.0;
		r.m[1][0] = 0.0; r.m[1][1] = scale.y; r.m[1][2] = 0.0; r.m[1][3] = 0.0;
		r.m[2][0] = 0.0; r.m[2][1] = 0.0; r.m[2][2] = scale.z; r.m[2][3] = 0.0;
		r.m[3][0] = 0.0; r.m[3][1] = 0.0; r.m[3][2] = 0.0; r.m[3][3] = 1.0;

		return r;
	}

	Matrix4D Matrix4D::createReflection(const Vector3D& normal, double dist_to_origin)
	{
		double k = -2.0f * dist_to_origin;

		double nxy2 = -2 * normal[0] * normal[1];
		double nxz2 = -2 * normal[0] * normal[2];
		double nyz2 = -2 * normal[1] * normal[2];
		double one_xx2 = 1.0f - 2.0f*normal[0] * normal[0];
		double one_yy2 = 1.0f - 2.0f*normal[1] * normal[1];
		double one_zz2 = 1.0f - 2.0f*normal[2] * normal[2];
		return Matrix4D(
			one_xx2, nxy2, nxz2, k*normal[0],
			nxy2, one_yy2, nyz2, k*normal[1],
			nxz2, nyz2, one_zz2, k*normal[2],
			0, 0, 0, 1.0
		);
	}

	Matrix4D Matrix4D::lookAt(const Vector3D& pos, const Vector3D& target, const Vector3D& up)
	{
		Vector3D look = pos - target;
		look.normalize();
		Vector3D new_up(up);
		new_up.normalize();
		Vector3D right = new_up.cross(look);
		right.normalize();
		new_up = look.cross(right);
		return Matrix4D(
			right[0], new_up[0], look[0], 0,
			right[1], new_up[1], look[1], 0,
			right[2], new_up[2], look[2], 0,
			-(right.dot(pos)), -(new_up.dot(pos)), -(look.dot(pos)), 1
		);
	}

	Matrix4D Matrix4D::makePerspective(double fovy, double aspect, double zNear, double zFar)
	{
		double f_n = 1.0 / (zFar - zNear);
		double theta = fovy * 0.5;

		double divisor = tan(theta);
		double factor = 1.0 / divisor;

		return Matrix4D(
			(1.0 / aspect) * factor, 0, 0, 0,
			0, factor, 0, 0,
			0, 0, (-(zFar + zNear)) * f_n, -1.0,
			0, 0, -2.0 * zFar * zNear * f_n, 0
		);
	}

	Matrix4D Matrix4D::makeOrthographic(double width, double height, double near_dist, double far_dist)
	{
		double f_n = 1.0 / (far_dist - near_dist);
		return Matrix4D(
			2.0 / width, 0, 0, 0,
			0, 2.0 / height, 0, 0,
			0, 0, -2.0*f_n, 0,
			0, 0, -(far_dist + near_dist)*f_n, 1.0
		);
	}

	Matrix4D Matrix4D::makeOrthographic(double left, double right, double bottom, double top, double n, double f)
	{
		Matrix4D OP;

		OP[0] = 2.0f / (right - left);
		OP[1] = 0.0f;
		OP[2] = 0.0f;
		OP[3] = 0.0f;

		OP[4] = 0.0f;
		OP[5] = 2.0f / (top - bottom);
		OP[6] = 0.0f;
		OP[7] = 0.0f;

		OP[8] = 0.0f;
		OP[9] = 0.0f;
		OP[10] = -2.0f / (f - n);
		OP[11] = 0.0f;

		OP[12] = -(right + left) / (right - left);
		OP[13] = -(top + bottom) / (top - bottom);
		OP[14] = -(f + n) / (f - n);
		OP[15] = 1.0f;

		return OP;
	}
}