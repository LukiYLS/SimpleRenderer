#pragma once
#include "Camera.h"

namespace SRE {
	class PerspectiveCamera :public Camera {
	public:
		typedef std::shared_ptr<PerspectiveCamera> ptr;
		PerspectiveCamera(float fovy, float aspect, float zNear, float zFar):
			_fovy(fovy), _aspect(aspect), _near(zNear), _far(zFar) {
			type = Perspective;
		}

		virtual Matrix4D getProjectionMatrix() const{ return Matrix4D::makePerspective(_fovy, _aspect, _near, _far); }
		float getNear()const { return _near; }
		float getFar()const { return _far; }
	private:
		float _fovy;
		float _aspect;
		float _near;
		float _far;
	};
}

