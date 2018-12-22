#pragma once


#include "Light.h"
#include "object/camera/PerspectiveCamera.h"

namespace SRE {


	struct SpotLightUniform {
		Vector3D position;
		Vector3D direction;
		Vector3D color;
		float distance;
		float decay;
		float coneCos;
		float penumbraCos;

		int shadow;
		float shadowBias;
		float shadowRadius;
		Vector2D shadowMapSize;
	};
	class SpotLight : public Light {

	public:
		typedef std::shared_ptr<SpotLight> ptr;
		virtual SpotLight* asSpotLight() { return this; }
		virtual void upload(Shader* shader);
		virtual void uploadShadow(Shader* shader, unsigned int& currectTextureUnit);
		virtual LightType getType()const { return SpotLightType; }
		void setUniform(SpotLightUniform uniform) { _uniform = uniform; }	
		float getDistance()const { return _distance; }
		void setDistance(float distance) { _distance = distance; }
		float getDecay()const { return _decay; }
		void setDecay(float decay) { _decay = decay; }
		float getAngle()const { return _angle; }
		void setAngle(float angle) { _angle = angle; }
		float getPenumbra()const { return _penumbra; }
		void setPenumbra(float penumbra) { _penumbra = penumbra; }
		void setShadowCamera(PerspectiveCamera* camera) { _shadow_camera = (PerspectiveCamera::ptr)camera; }
		virtual Camera* getShadowCamera()const { return _shadow_camera.get(); }
	protected:

		float _distance,_decay,_penumbra;
		float _angle;
		PerspectiveCamera::ptr _shadow_camera;
		SpotLightUniform _uniform;
	};
}
