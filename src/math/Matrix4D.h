#pragma once
namespace Math {
	class Vector4D;
	class Vector3D;
	class Matrix3D;
	class Quaternion;
	class Matrix4D//column first
	{
	public:
		
		Matrix4D();
		Matrix4D(const Vector4D& v0, const Vector4D& v1, const Vector4D& v2, const Vector4D& v3);
		Matrix4D(double a00, double a01, double a02, double a03,
			double a10, double a11, double a12, double a13,
			double a20, double a21, double a22, double a23,
			double a30, double a31, double a32, double a33);
		~Matrix4D();

	public:
		Matrix4D(const Matrix3D& m3x3)
		{
			operator=(Identity);
			operator=(m3x3);
		}
		double& operator[] (int index) {
			return _m[index];
		}
		const double& operator[] (int index) const {
			return _m[index];
		}
		double& operator() (int row, int col) {
			return _m[col * 4 + row];
		}
		const double& operator() (int row, int col) const {
			return _m[col * 4 + row];
		}

		Matrix4D operator*(double scalar) const {
			return Matrix4D(
				scalar*_m[0],
				scalar*_m[1],
				scalar*_m[2],
				scalar*_m[3],
				scalar*_m[4],
				scalar*_m[5],
				scalar*_m[6],
				scalar*_m[7],
				scalar*_m[8],
				scalar*_m[9],
				scalar*_m[10],
				scalar*_m[11],
				scalar*_m[12],
				scalar*_m[13],
				scalar*_m[14],
				scalar*_m[15]
			);
		}
		Matrix4D operator + (const Matrix4D &m2) const
		{
			Matrix4D r;

			r.m[0][0] = m[0][0] + m2.m[0][0];
			r.m[0][1] = m[0][1] + m2.m[0][1];
			r.m[0][2] = m[0][2] + m2.m[0][2];
			r.m[0][3] = m[0][3] + m2.m[0][3];

			r.m[1][0] = m[1][0] + m2.m[1][0];
			r.m[1][1] = m[1][1] + m2.m[1][1];
			r.m[1][2] = m[1][2] + m2.m[1][2];
			r.m[1][3] = m[1][3] + m2.m[1][3];

			r.m[2][0] = m[2][0] + m2.m[2][0];
			r.m[2][1] = m[2][1] + m2.m[2][1];
			r.m[2][2] = m[2][2] + m2.m[2][2];
			r.m[2][3] = m[2][3] + m2.m[2][3];

			r.m[3][0] = m[3][0] + m2.m[3][0];
			r.m[3][1] = m[3][1] + m2.m[3][1];
			r.m[3][2] = m[3][2] + m2.m[3][2];
			r.m[3][3] = m[3][3] + m2.m[3][3];

			return r;
		}
		
		Matrix4D operator - (const Matrix4D &m2) const
		{
			Matrix4D r;
			r.m[0][0] = m[0][0] - m2.m[0][0];
			r.m[0][1] = m[0][1] - m2.m[0][1];
			r.m[0][2] = m[0][2] - m2.m[0][2];
			r.m[0][3] = m[0][3] - m2.m[0][3];

			r.m[1][0] = m[1][0] - m2.m[1][0];
			r.m[1][1] = m[1][1] - m2.m[1][1];
			r.m[1][2] = m[1][2] - m2.m[1][2];
			r.m[1][3] = m[1][3] - m2.m[1][3];

			r.m[2][0] = m[2][0] - m2.m[2][0];
			r.m[2][1] = m[2][1] - m2.m[2][1];
			r.m[2][2] = m[2][2] - m2.m[2][2];
			r.m[2][3] = m[2][3] - m2.m[2][3];

			r.m[3][0] = m[3][0] - m2.m[3][0];
			r.m[3][1] = m[3][1] - m2.m[3][1];
			r.m[3][2] = m[3][2] - m2.m[3][2];
			r.m[3][3] = m[3][3] - m2.m[3][3];

			return r;
		}
	
		bool operator == (const Matrix4D& m2) const
		{
			if (
				m[0][0] != m2.m[0][0] || m[0][1] != m2.m[0][1] || m[0][2] != m2.m[0][2] || m[0][3] != m2.m[0][3] ||
				m[1][0] != m2.m[1][0] || m[1][1] != m2.m[1][1] || m[1][2] != m2.m[1][2] || m[1][3] != m2.m[1][3] ||
				m[2][0] != m2.m[2][0] || m[2][1] != m2.m[2][1] || m[2][2] != m2.m[2][2] || m[2][3] != m2.m[2][3] ||
				m[3][0] != m2.m[3][0] || m[3][1] != m2.m[3][1] || m[3][2] != m2.m[3][2] || m[3][3] != m2.m[3][3])
				return false;
			return true;
		}
		void operator = (const Matrix3D& mat3);		
		Vector4D operator*(const Vector4D& vec_) const;		
		Vector3D operator*(const Vector3D& vec_) const;			
		Matrix4D operator*(const Matrix4D& mat4_) const;
			

	public:
		Matrix4D  getTranspose(void) const;
		Matrix4D  getInverse() const;
		Matrix3D  getMatrix3x3() const;
		double    determinant() const;	
		void	  decompose(Vector3D& position, Vector3D& scale, Quaternion& orientation);
		void	  scale(const Vector3D& scale);
		void	  setPosition(const Vector3D& pos);

	public:		
		static const Matrix4D Identity;
		static Matrix4D makeIdentity();
		static Matrix4D makeRotationFromQuaternion(const Quaternion& orientation);
		static Matrix4D makeTransformMatrix(const Vector3D& position, const Vector3D& scale, const Quaternion& orientation);
		static Matrix4D makeTranslation(double x, double y, double z);		
		static Matrix4D makeTranslation(const Vector3D& trans);
		static Matrix4D makeScale(double x, double y, double z);		
		static Matrix4D makeScale(const Vector3D& scale);
		static Matrix4D makeRotationAxis(const Vector3D& axis, double angle_in_rad);
		static Matrix4D makeRotationX(const double& angle_in_rad);
		static Matrix4D makeRotationY(const double& angle_in_rad);
		static Matrix4D makeRotationZ(const double& angle_in_rad);
		static Matrix4D createReflection(const Vector3D& normal, double dist_to_origin);
		static Matrix4D lookAt(const Vector3D& pos, const Vector3D& target, const Vector3D& up);
		static Matrix4D makePerspective(double fovy, double aspect, double zNear, double zFar);
		static Matrix4D makeOrthographic(double width, double height, double near_dist, double far_dist);
		static Matrix4D makeOrthographic(double left, double right, double bottom, double top, double n, double f);
	protected:
		union {
			double m[4][4];
			double _m[16];
		};
	};
}