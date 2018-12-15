#pragma once

namespace Math {
	class Vector3D;	
	class Matrix4D;
	class Quaternion {
	public:
		double x, y, z, w;
	public:		
		Quaternion()
			: x(0), y(0), z(0), w(1)
		{
		}		
		Quaternion(double x_, double y_, double z_, double w_)
			: x(x_), y(y_), z(z_), w(w_)
		{
		}	
		double operator [] (const unsigned int i) const
		{
			return *(&x + i);
		}		
		double& operator [] (const unsigned int i)
		{
			return *(&x + i);
		}

		void setFromRotationMatrix(const Matrix4D& rot);
		void setFromAxisAngle(const double& angle, const Vector3D axis);

		//void fromRotationMatrix(const Matrix3D& kRot);
		void toRotationMatrix(Matrix4D& rot) const;
		
		void toAngleAxis(double& angle, Vector3D& axis) const;
		
		void fromAxes(const Vector3D* axis);
		void fromAxes(const Vector3D& xAxis, const Vector3D& yAxis, const Vector3D& zAxis);
		
		void toAxes(Vector3D* axis) const;
		void toAxes(Vector3D& xAxis, Vector3D& yAxis, Vector3D& zAxis) const;
		
		Vector3D xAxis(void) const;		
		Vector3D yAxis(void) const;		
		Vector3D zAxis(void) const;

		Quaternion operator+ (const Quaternion& rkQ) const;
		Quaternion operator- (const Quaternion& rkQ) const;
		Quaternion operator* (const Quaternion& rkQ) const;
		Quaternion operator* (double fScalar) const
		{
			return Quaternion(fScalar*w, fScalar*x, fScalar*y, fScalar*z);
		}
		Vector3D operator* (const Vector3D& vec) const;

		bool operator== (const Quaternion& rhs) const
		{
			return (rhs.x == x) && (rhs.y == y) &&
				(rhs.z == z) && (rhs.w == w);
		}
		bool operator!= (const Quaternion& rhs) const
		{
			return !operator==(rhs);
		}
		double norm() const
		{
			return  x*x + y*y + z*z + w*w ;
		}
		double dot(const Quaternion& rkQ) const
		{
			return w*rkQ.w + x*rkQ.x + y*rkQ.y + z*rkQ.z;
		}
		Quaternion Inverse() const
		{
			double fNorm = w*w + x*x + y*y + z*z;
			if (fNorm > 0.0)
			{
				double fInvNorm = 1.0f / fNorm;
				return Quaternion(w*fInvNorm, -x*fInvNorm, -y*fInvNorm, -z*fInvNorm);
			}
			else
			{
				// return an invalid result to flag the error
				return Quaternion(0, 0, 0, 0);
			}
		}
		Quaternion getUnitInverse()const
		{
			return Quaternion(-x, -y, -z, w);
		}
		double getRoll(bool reprojectAxis = true) const;
		double getPitch(bool reprojectAxis = true) const;
		double getYaw(bool reprojectAxis = true) const;
		double normalize(void);

		static Quaternion slerp(float fT, const Quaternion& first, const Quaternion& second);
	};

}