#pragma once
#include <GL/glew.h>
#include <vector>
#include <string>
#include "camera/Camera.h"
#include "texture/Texture.h"
#include "graphic/render/Shader.h"
#include "Mesh.h"
namespace SRE {
	class Skybox
		:public Object3D{
	public:
		typedef std::shared_ptr<Skybox> ptr;
		Skybox();
		Skybox(std::vector<std::string> fileNames);
		void setTexture(Texture::ptr texture) { _cubeMap = texture; }
		Texture::ptr getTexture()const { return _cubeMap; }
		~Skybox();
		void render(Camera* camera);
	private:
		Texture::ptr _cubeMap;
		Shader::ptr _skyboxShader;
		RenderObject::ptr _skybox;
	};
}