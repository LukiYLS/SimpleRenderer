#pragma once
#include <memory>
#include "texture/TextureUnitState.h"
#include "graphic/render/Constants.h"
#include "graphic/render/Shader.h"
namespace SRE {
	
	//combine material

	

	//class PhongMaterial;
	//class BasicMaterial;
	//class ShaderMaterial;
	class Material {

	public:
		enum MaterialType {
			BasicMaterial,
			PhongMaterial,
			ShaderMaterial
		};
		typedef std::shared_ptr<Material> ptr;
		Material();
		~Material() = default;
		//virtual Material* asMaterial() { return this; }
		//virtual BasicMaterial* asBasicMaterial() { return NULL; }
		//virtual PhongMaterial* asPhongMaterial() { return NULL; }
		//virtual ShaderMaterial* asShaderMaterial() { return NULL; }
		
		void setFog(bool fog) { _fog = fog; }
		bool getFog()const { return _fog; }

		void setBlendingMode(BlendingMode mode) { _blendingMode = mode; }
		BlendingMode getBlendingMode()const { return _blendingMode; }

		void setCullFaceMode(CullFaceMode mode) { _cullFaceMode = mode; }
		CullFaceMode getCullFaceMode()const { return _cullFaceMode; }

		void setOpacity(float opacity) { _opacity = opacity; }
		float getOpacity()const { return _opacity; }

		void setTransparent(bool transparent) { _transparaent = transparent; }
		bool getTransparent()const { return _transparaent; }

		void setDepthFunc(CompareFunc func) { _depthFunc = func; }
		CompareFunc gettDepthFunc()const { return _depthFunc; }

		void setDepthTest(bool depthTest) { _depthTest = depthTest; }
		bool getDepthTest()const { return _depthTest; }

		void setDepthWrite(bool depthWrite) { _depthWrite = depthWrite; }
		bool getDepthWrite()const { return _depthFunc; }

		void setColorWrite(bool colorWrite) { _colorWrite = colorWrite; }
		bool getColorWrite()const { return _colorWrite; }

		void setWireframe(const bool& wireframe) { _wireframe = wireframe; }
		bool getWireframe()const { return _wireframe; }

		void setWireframeLinewidth(const float& width) { _lineWidth = width; }
		float getWireframeLinewidth()const { return _lineWidth; }

		void setVisible(bool visible) { _visible = visible; }
		bool getVisible()const { return _visible; }

		void setShadeType(ShadeOptions type) { _shadeType = type; }
		ShadeOptions getShadeType()const { return _shadeType; }

		MaterialType getMaterialType()const { return _materialType; }
		void setMaterialType(MaterialType materialType) { _materialType = materialType; }

		TextureUnitState::ptr getMap()const { return _map; }
		void setMap(TextureUnitState::ptr map) { _map = map; }		

		void setColor(const Vector3D& color) { _color = color; }
		Vector3D getColor()const { return _color; }

		void setSpecular(const Vector3D& specular) { _specular = specular; }
		Vector3D getSpecular() const { return _specular; }

		void setShininess(const float& shininess) { _shininess = shininess; }
		float getShininess()const { return _shininess; }

		void setLightMap(TextureUnitState::ptr lightMap) { _lightMap = lightMap; }
		TextureUnitState::ptr getLightMap()const { return _lightMap; }

		void setLightMapIntensity(float lightMapIntensity) { _lightMapIntensity = lightMapIntensity; }
		float getLightMapIntensity()const { return _lightMapIntensity; }

		void setEmissive(const Vector3D& emissive) { _emissive = emissive; }
		Vector3D getEmissive()const { return _emissive; }
		void setEmissiveMap(TextureUnitState::ptr emissiveMap) { _emissiveMap = emissiveMap; }
		TextureUnitState::ptr getEmissiveMap()const { return _emissiveMap; }

		void setDisplacementMap(TextureUnitState::ptr displacementMap) { _displacementMap = displacementMap; }
		TextureUnitState::ptr getDisplacementMap()const { return _displacementMap; }

		void setNormalMap(TextureUnitState::ptr normalMap) { _normalMap = normalMap; }
		TextureUnitState::ptr getNormalMap()const { return _normalMap; }

		void setEnvMap(TextureUnitState::ptr envMap) { _envMap = envMap; }
		TextureUnitState::ptr getEnvMap()const { return _envMap; }

		void setEnvMapType(EnvMapType type) { _envMapType = type; }
		EnvMapType getEnvMapType()const { return _envMapType; }

		void setEnvMapBlendMode(EnvMapBlendMode mode) { _envMapBlendMode = mode; }
		EnvMapBlendMode getEnvMapBlendMode()const { return _envMapBlendMode; }

		void setSpecularMap(TextureUnitState::ptr specularMap) { _specularMap = specularMap; }
		TextureUnitState::ptr getSpecularMap()const { return _specularMap; }

		void setAlphaMap(TextureUnitState::ptr alphaMap) { _alphaMap = alphaMap; }
		TextureUnitState::ptr getAlphaMap()const { return _alphaMap; }

		void setAoMap(TextureUnitState::ptr aoMap) { _aoMap = aoMap; }
		TextureUnitState::ptr getAoMap()const { return _aoMap; }

		void setAoMapIntensity(float aoMapIntensity) { _aoMapIntensity = aoMapIntensity; }
		float getAoMapIntensity()const { return _aoMapIntensity; }

		void setReflectivity(float reflectivity) { _reflectivity = reflectivity; }
		float getReflectivity()const { return _reflectivity; }

		void setRefractionRatio(float refractionRatio) { _refractionRatio = refractionRatio; }
		float getRefractionRatio()const { return _refractionRatio; }

		Shader* getShader()const { return _shader.get(); } 
		void setShader(Shader* shader) { _shader = (Shader::ptr)shader; _shaderCreated = true;}

		bool isShaderCreated(){return _shaderCreated;}
		
		/*void setAmbient(const ColorValue& diffuse);
		void setAmbient(float r, float g, float b, float a);
		void getAmbient(float& r, float& g, float& b, float &a)const;

		void setDiffuse(const ColorValue& diffuse);
		void setDiffuse(float r, float g, float b, float a) ;
		void getDiffuse(float& r, float& g, float& b, float &a)const;

		void setSpecular(const ColorValue& diffuse);
		void setSpecular(float r, float g, float b, float a);
		void getSpecular(float& r, float& g, float& b, float &a)const;		

		void setShininess(float shininess);
		float getShininess()const;

		void setEmissiveColor(const ColorValue& diffuse);
		void setEmissiveColor(float r, float g, float b, float a);
		void getEmissiveColor(float& r, float& g, float& b, float& a)const;*/

		//void setReceiveShadows(bool enabled) { mReceiveShadows = enabled; }
		//bool getReceiveShadows(void) const { return mReceiveShadows; }
		//void setTransparencyCastsShadows(bool enabled) { mTransparencyCastsShadows = enabled; }
		//bool getTransparencyCastsShadows(void) const { return mTransparencyCastsShadows; }
		//unsigned short getNumLodLevels(unsigned short schemeIndex) const;
		//unsigned short getNumLodLevels(const String& schemeName) const;
		//void setDepthWriteEnabled(bool enabled);
		//void setLightingEnabled(bool enabled);
		//void setColourWriteEnabled(bool enabled);
		//void setDepthFunction(CompareFunction func);
		//void setCullingMode(CullingMode mode);
		//void setShadingMode(ShadeOptions mode);
		//void setLodLevels(const LodValueList& lodValues);
		//void setSceneBlending(const SceneBlendFactor sourceFactor, const SceneBlendFactor destFactor);
		//void setFog(bool overrideScene,	FogMode mode = FOG_NONE,const ColourValue& colour = ColourValue::White,
		//	Real expDensity = 0.001, Real linearStart = 0.0, Real linearEnd = 1.0);



	protected:		
		BlendingMode _blendingMode;
		CullFaceMode _cullFaceMode;
		EnvMapBlendMode _envMapBlendMode;
		EnvMapType _envMapType;
		CompareFunc _depthFunc;
		ShadeOptions _shadeType;		
		MaterialType _materialType;
		Vector3D _color, _specular, _emissive;
		TextureUnitState::ptr _map, _lightMap, _displacementMap, _normalMap, _envMap, _emissiveMap,_specularMap,_alphaMap,_aoMap;
		bool _fog, _transparaent, _depthTest, _depthWrite, _colorWrite, _visible, _wireframe;
		float _opacity, _lightMapIntensity,_aoMapIntensity,_lineWidth, _shininess, _reflectivity, _refractionRatio;
		Shader::ptr _shader;
		bool _shaderCreated;
	};
}