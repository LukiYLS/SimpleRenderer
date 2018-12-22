#pragma once
#include <string>
#include <map>
using std::string;
using std::map;
namespace SRE {

	enum BlendingMode{
		NoBlending = 0,
		NormalBlending = 1,
		AdditiveBlending = 2,
		SubtractiveBlending = 3,											
		MultiplyBlending = 4,																 
		CustomBlending	= 5																				
	};

	enum CompareFunc
	{
		NeverDepth = GL_NEVER,
		AlwaysDepth = GL_ALWAYS,
		LessDepth = GL_LESS,
		LessEqualDepth = GL_LEQUAL,
		GreaterEqualDepth = GL_GEQUAL,
		GreaterDepth = GL_GREATER,
		NotEqualDepth = GL_NOTEQUAL
	};
	enum CullFaceMode
	{
		Front = GL_FRONT,
		Back = GL_BACK,
		DoubleSide = GL_FRONT_AND_BACK
	};

	enum ShadeOptions
	{
		SO_FLAT,
		SO_GOURAUD,
		SO_PHONG
	};
	enum FogMode
	{
		/// No fog. Duh.
		FOG_NONE,
		/// Fog density increases  exponentially from the camera (fog = 1/e^(distance * density))
		FOG_EXP,
		/// Fog density increases at the square of FOG_EXP, i.e. even quicker (fog = 1/e^(distance * density)^2)
		FOG_EXP2,
		/// Fog density increases linearly between the start and end distances
		FOG_LINEAR
	};

	enum EnvMapType {
		CubeReflectionMapping,
		CubeRefractionMapping,
		CubeUVReflectionMapping,
		CubeUVRefractionMapping,
		EquirectangularReflectionMapping,
		EquirectangularRefractionMapping,
		SphericalReflectionMapping
	};
	enum EnvMapBlendMode {
		MultiplyOperation,
		MixOperation,
		AddOperation
	};

	enum ShadowMapType {
		PCFShadowMap,
		PCFSoftShadowMap
	};
	
	
	
	const string vertex_attribute = "layout(location=0)in vec3 position;\nlayout(location =1) in vec3 normal;\nlayout(location=2)in vec3 color;\nlayout(location=3)in vec2 texCoord;\nuniform mat4 modelMatrix;\nuniform mat4 viewMatrix;\nuniform mat4 projectionMatrix;\n";

	const string fog_vertex_define = "#ifdef USE_FOG\n\tvarying float fogDepth;\n#endif";

	const string uv_vertex_define = "#if define (USE_MAP) || define (USE_NORMALMAP)\nvaying vec2 uv;\nuniform vec3 uvTransform;\n#endif";

	const string uv2_vertex_define = "#if define(USE_LIGHTMAP) || define(USE_AOMAP)\nvarying vec2 uv2;\n#endif";

	const string envmap_vertex_define = "#ifdef USE_ENVMAP\n#if defined(USE_BUMPMAP) || defined(USE_NORMALMAP) || defined(PHONG)\n\tvarying vec3 worldPosition;\n#else\n\tvarying vec3 reflect;\n\tuniform float refractionRatio;\n\t#endif\n#endif\n";

	const string color_vertex_define = "#ifdef USE_COLOR\n\tvarying vec3 Color;\n#endif\n";

	const string shadowmap_vertex_define = "#ifdef USE_SHADOWMAP\n\t#if NUM_DIR_LIGHTS > 0\n\t\tuniform mat4 directionShadowMatrix[NUM_DIR_LIGHTS];\n\t\tvarying vec4 directionShadowCoord[NUM_DIR_LIGHTS];\n\t#endif\n\t#if NUM_SPOT_LIGHTS > 0\n\t\tuniform mat4 spotShadowMatrix[NUM_SPOT_LIGHTS];\n\t\tvarying vec4 spotShadowCoord[NUM_SPOT_LIGHTS];\n\t#endif\n\t#if NUM_POINT_LIGHTS > 0\n\t\tuniform mat4 pointShadowMatrix[NUM_POINT_LIGHTS];\n\t\tvarying vec4 pointShadowCoord[NUM_POINT_LIGHTS];\n\t#endif\n#endif";

	const string uv_vertex = "#if define (USE_MAP) || define (USE_NORMALMAP)\nuv = (uvTransform * vec3(uv, 1)).xy;\n#endif";

	const string uv2_vertex = "#if define(USE_LIGHT_MAP) || define(USE_ AOMAP)\nuv2 = uv2;\n#endif";

	const string color_vertex = "#ifdef USE_COLOR\n\tColor = color;\n#endif\n";

	const string worldposition_vertex = "#if defined(USE_ENVMAP) || defined(PHONG) || defined(USE_SHADOWMAP)\n\tvec4 worldPosition = modelMatrix * vec4( position, 1.0 );\n#endif";

	const string project_vertex = "vec4 mvPosition = viewMatrix * modelMatrix * vec4(position,1.0);\ngl_Position = projectionMatrix * vec4(mvPosition, 1.0);\n";

	const string envmap_vertex = "#ifdef USE_ENVMAP\n\t#if defined(USE_BUMPMAP) || defined(USE_NORMALMAP) || defined(PHONG)\n\t\tworldPosition = (modelMatrix * vec4(position,1.0)).xyz;\n\t#else\n\t\tvec3 cameraToVertex = normalize(worldPosition - cameraPosition);\n\t\tvec3 worldNormal = normalize((vec4(normal,0.0)*viewMatrix).xyz);\n\t\t#ifdef ENVMAP_REFLECTION\n\t\t\treflect = reflect(cameraToVertex,worldNormal);\n\t\t#else\n\t\treflect = refract(cameraToVertex, worldNormal, refractionRatio);\n\t\t#endif\n\t#endif\n#endif";

	const string shadowmap_vertex = "#ifdef USE_SHADOWMAP\n\t#if NUM_DIR_LIGHTS > 0\n\tfor(int i=0;i< NUM_DIR_LIGHTS;i++){\n\t\tdirectionShadowCoord[i] = directionShadowMatrix[i] * worldPosition;\n\t}\n\t#endif\n\t#if NUM_SPOT_LIGHTS > 0\n\tfor(int i=0;i<NUM_SPOT_LIGHTS;i++){\n\t\tspotShadowCoord[i] = spotShadowMatrix[i]*worldPosition;\n\t}\n\t#endif\n\t#if NUM_POINT_LIGHTS > 0 \n\tfor(int i=0;i<NUM_POINT_LIGHTS;i++){\n\t\tpointShadowCoord[i] =pointShadowMatrix[i] * worldPosition;\n\t}\n\t#endif\n#endif";

	const string fog_vertex = "#ifdef USE_FOG\n\tfogDepth = -mvPosition.z;\n#endif";

	const string light_define = "uniform vec3 ambientLightColor;\nvec3 getAmbientLightIrradiance(const in vec3 ambientLightColor){\n\tvec3 irradiance = ambientLightColor;#ifdef PHYSICALLY_CORRECT_LIGHTS\n\t\tirradiance *= PI;\n\t#endif\n\treturn irradiance;\n}\n#if NUM_DIR_LIGHTS >0";
		

	//const string phong_vertex = "#define PHONG\nvarying vec3 viewPosition;\n#ifdef FLAT_SHADED\n\tvarying vec3 vNormal;\n#endif" +
	//	uv_vertex_define + envmap_vertex_define + color_vertex_define + fog_vertex_define + shadowmap_vertex_define;
	


}