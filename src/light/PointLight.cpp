#include "PointLight.h"
#include <sstream>


namespace SRE {
	PointLight::PointLight():
		_distance(500.0),
		_decay(1.0)
	{

	}
	void PointLight::upload(Shader* shader)
	{
		std::stringstream ss;
		std::string number;
		ss << _number;
		ss >> number;
		std::string uniform_name_pre = "pointLights[].";
		if (_number < 10)
			uniform_name_pre.insert(12, number, 0, 1);
		else
			uniform_name_pre.insert(12, number, 0, 2);


		shader->use();

		std::string position = uniform_name_pre + "position";
		shader->setVec3(position.c_str(), _uniform.position);

		std::string color = uniform_name_pre + "color";
		shader->setVec3(color.c_str(), _uniform.color);

		std::string distance = uniform_name_pre + "distance";
		shader->setFloat(distance.c_str(), _uniform.distance);

		std::string decay = uniform_name_pre + "decay";
		shader->setFloat(decay.c_str(), _uniform.decay);

		std::string shadow = uniform_name_pre + "shadow";
		shader->setBool(shadow.c_str(), _uniform.shadow);

		std::string shadowBias = uniform_name_pre + "shadowBias";
		shader->setFloat(shadowBias.c_str(), _uniform.shadowBias);

		std::string shadowRadius = uniform_name_pre + "shadowRadius";
		shader->setFloat(shadowRadius.c_str(), _uniform.shadowRadius);

		std::string shadowMapSize = uniform_name_pre + "shadowMapSize";
		shader->setVec2(shadowMapSize.c_str(), _uniform.shadowMapSize);

		std::string shadowCameraNear = uniform_name_pre + "shadowCameraNear";
		shader->setFloat(shadowCameraNear.c_str(), _shadow_camera->getNear());

		std::string shadowCameraFar = uniform_name_pre + "shadowCameraFar";
		shader->setFloat(shadowCameraFar.c_str(), _shadow_camera->getFar());
		
		//shader->unUse();
	}
	void PointLight::uploadShadow(Shader* shader, unsigned int& currectTextureUnit)
	{
		std::stringstream ss;
		std::string number;
		ss << _number;
		ss >> number;
		/*std::string uniform_name_matrix = "pointShadowMatrix[]";
		if (_number < 10)
			uniform_name_matrix.insert(18, number, 0, 1);
		else
			uniform_name_matrix.insert(18, number, 0, 2);*/

		shader->use();

		/*Matrix4D shadowMatrix = _shadowMatrix;
		shader->setMat4(uniform_name_matrix.c_str(), shadowMatrix);*/

		std::string uniform_name_map = "pointShadowMap[]";
		if (_number < 10)
			uniform_name_map.insert(15, number, 0, 1);
		else
			uniform_name_map.insert(15, number, 0, 2);
		shader->setInt(uniform_name_map.c_str(), currectTextureUnit);
		if (_shadowFB != NULL)
			_shadowFB->bindForReading(currectTextureUnit);
		++currectTextureUnit;
	}
}