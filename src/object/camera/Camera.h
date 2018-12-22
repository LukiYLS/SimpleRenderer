#pragma once
#include "ViewPort.h"
#include "object/Object3D.h"
#include "math/Matrix4D.h"
#include "math/Quaternion.h"
#include "math/Vector3D.h"
#include <memory>
namespace SRE {
	enum CameraType{ Perspective, Orthographic};
	class Camera 
		:public Object3D{
	public:
		typedef std::shared_ptr<Camera> ptr;
		Camera() = default;
		Camera(const Camera&) = default;
		Camera(const Vector3D& pos) :Object3D(pos) {}
		Camera(const Vector3D& pos, const Quaternion& quat) :Object3D(pos, quat) {}
	public:		
	
		void lookAt(const Vector3D& target);
		void lookAt(float x, float y, float z) { lookAt(Vector3D(x, y, z)); }
		void lookAt(const Vector3D& position, const Vector3D target, const Vector3D& up);

		void rotate(float angle, float x, float y, float z) { rotateOnAxis(Vector3D(x, y, z), angle); }

		void yaw(float angle) { rotateOnAxis(_orientation.xAxis(), angle); }
		void pitch(float angle) { rotateOnAxis(_orientation.yAxis(), angle); }
		void roll(float angle) { rotateOnAxis(_orientation.zAxis(),angle); }

		Matrix4D getViewMatrix()const;
		virtual Matrix4D getProjectionMatrix() const { return Matrix4D::makeIdentity(); }	
		void setViewPort(ViewPort::ptr vp) { _view_port = vp; }
		ViewPort::ptr getViewPort() { return _view_port; }
		
		//virtual CameraType getType() { return type; }
		//for mouse and keyboard control
	public:
		//void ProcessKeyboard(float xoffset, float yoffset);
		//void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
		//void ProcessMouseScroll(float yoffset);
		CameraType type;
	private:
		float _movementSpeed;
		float _mouseSensitivity;
		ViewPort::ptr _view_port;
		
	};

}

