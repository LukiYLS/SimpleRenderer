#include "Material.h"


namespace SRE {

	Material::Material():
		_fog(false),
		_blendingMode(NoBlending),
		_opacity(1.0),
		_transparaent(false),
		_depthFunc(LessEqualDepth),
		_depthTest(true),
		_depthWrite(true),
		_colorWrite(true),
		_wireframe(false),
		_lineWidth(1.0),
		_visible(true),
		_shadeType(SO_FLAT),
		_materialType(BasicMaterial),
		_map(NULL),
		_color(Vector3D(1.0,1.0,1.0)),
		_specular(Vector3D(0.3, 0.3, 0.3)),
		_shininess(30),
		_lightMap(NULL),
		_emissive(Vector3D(0.0, 0.0, 0.0)),
		_emissiveMap(NULL),
		_displacementMap(NULL),
		_normalMap(NULL),
		_envMap(NULL),
		_specularMap(NULL),
		_alphaMap(NULL),
		_reflectivity(1.0),
		_refractionRatio(0.88),
		_shader(NULL),
		_shaderCreated(false)

	{

	}
}