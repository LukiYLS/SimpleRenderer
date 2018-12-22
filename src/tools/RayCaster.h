#pragma once
#include "math/Vector2D.h"
#include "math/Ray.h"
#include "object/camera/Camera.h"
#include "object/Object3D.h"
#include "utils/AnyValue.h"
using Math::Ray;
namespace SRE {
	class RayCaster {

	public:
		RayCaster(Ray* ray) {};
		RayCaster(Ray* ray, double near, double far) {};

	public:
		Ray::ptr getRay()const { return _ray; }
		void setFromCamera(const Math::Vector2D& coords, Camera* camera);
		void intersectObject(Object3D* object, Utils::AnyValue& intersects, bool recursive);
	protected:
		Ray::ptr _ray;
		double _near;
		double _far;
	};
}