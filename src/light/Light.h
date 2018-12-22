#pragma once
#include "object/Object3D.h"
#include "graphic/render/Shader.h"
#include "graphic/render/FrameBuffer.h"
#include "object/camera/Camera.h"
namespace SRE {	

	class DirectionLight;
	class PointLight;
	class SpotLight;
	class HemisphereLight;
	class Light : public  Object3D{
	public:
		enum LightType {
			AmbientLightType,
			DirectionLightType,
			PointLightType,
			SpotLightType,
			HemisphereLightType,
			NoneType
		};		
		Light() :_color(Vector3D(1.0, 1.0, 1.0)),
			_intensity(1.0), _castShadow(true),
			_shadowMapSize(Vector2D(512.0,512.0)),
			_target(Vector3D(0.0,0.0,0.0)),
			_shadowBias(0.005),
			_shadowRadius(1.0){

		}
		virtual ~Light() = default;

	public:
		typedef std::shared_ptr<Light> ptr;
		virtual Light* asLight() { return this; }
		virtual const Light* asLight() const { return this; }
		virtual DirectionLight* asDirectionLight() { return NULL; }
		virtual PointLight* asPointLight() { return NULL; }
		virtual SpotLight* asSpotLight() { return NULL; }
		virtual HemisphereLight* asHemisphereLight() { return NULL; }

		void setColor(const Vector3D& color) { _color = color; }
		Vector3D getColor()const { return _color; }

		void setIntensity(float intensity) { _intensity = intensity; }
		float getIntensity()const { return _intensity; }

		void setCastShadow(bool isCast) { _castShadow = isCast; }
		bool getCastShadow()const { return _castShadow; }

		virtual void setNumber(unsigned int number) { _number = number; }
		virtual void upload(Shader* shader) { /*shader->setVec3("ambientLightColor",);*/ }
		virtual void uploadShadow(Shader* shader, unsigned int& currectTextureUnit) {}

		virtual LightType getType()const { return NoneType; }

		virtual Camera* getShadowCamera()const { return NULL; }
		virtual void setShadowCamera(Camera* camera){}

		Vector2D getShadowMapSize()const { return _shadowMapSize; }
		void setShadowMapSize(Vector2D shadowMapSize) { _shadowMapSize = shadowMapSize; }

		float getShadowBias()const { return _shadowBias; }
		void setShadowBias(float shadowBias) { _shadowBias = shadowBias; }

		float getShadowRadius()const { return _shadowRadius; }
		void setShadowRadius(float shadowRadius) { _shadowRadius = shadowRadius; }

		Matrix4D getShadowMatrix()const { return _shadowMatrix; }
		void setShadowMatrix(const Matrix4D& matrix) { _shadowMatrix = matrix; }

		FrameBuffer* getShadowFrameBuffer()const { return _shadowFB.get(); }
		void setShadowFrameBuffer(FrameBuffer* fb) { _shadowFB = (FrameBuffer::ptr)fb; }

		void setLightTarget(const Vector3D& target) { _target = target; }
		Vector3D getLightTarget()const { return _target; }

	protected:

		Vector3D _color;
		unsigned int _number;
		float _intensity;
		bool _castShadow;
		//ShadowInfo _shadowInfo;
		Vector2D _shadowMapSize;
		Vector3D _target;

		Matrix4D _shadowMatrix;
		FrameBuffer::ptr _shadowFB;
		float _shadowBias, _shadowRadius;
	};
}