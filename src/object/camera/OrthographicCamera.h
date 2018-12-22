#pragma once
#include "Camera.h"
#include "math/Matrix4D.h"
namespace SRE {
	class OrthographicCamera :public Camera {
	public:
		OrthographicCamera(float left, float right, float bottom, float top, float near, float far) :
			_left(left), _right(right), _bottom(bottom), _top(top), _near(near), _far(far) {
			type = Orthographic;
		}

		virtual Matrix4D getProjectionMatrix() const { return Matrix4D::makeOrthographic(_left, _right, _bottom, _top, _near, _far); }
	private:
		float _left;
		float _right;
		float _bottom;
		float _top;
		float _near;
		float _far;
	};
}
