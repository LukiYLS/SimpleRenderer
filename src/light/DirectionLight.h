#pragma once

#include "Light.h"
#include "object/camera/OrthographicCamera.h"

namespace SRE {

	struct DirectionalLightUniform {
		Vector3D direction;
		Vector3D color;

		int shadow;
		float shadowBias;
		float shadowRadius;
		Vector2D shadowMapSize;
	};

	class DirectionLight : public Light {

	public:
		typedef std::shared_ptr<DirectionLight> ptr;	

		Vector3D getDirection()const { return _direction; }
		void setDirection(const Vector3D& direction) { _direction = direction; }
		void setUniform(DirectionalLightUniform uniform) { _uniform = uniform; }

		virtual DirectionLight* asDirectionLight() { return this; }
		virtual void upload(Shader* shader);
		virtual void uploadShadow(Shader* shader, unsigned int& currectTextureUnit);
		virtual LightType getType()const { return DirectionLightType; }

		virtual Camera* getShadowCamera()const { return _shadow_camera.get(); }
		virtual void setShadowCamera(OrthographicCamera* camera) { _shadow_camera = (OrthographicCamera::ptr)camera; }

	protected:
		Vector3D _direction;		
		OrthographicCamera::ptr _shadow_camera;
		DirectionalLightUniform _uniform;
	};
}