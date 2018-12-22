#pragma once
#include "../Scene.h"
#include "object/camera/Camera.h"
#include "object/RenderObject.h"
#include "math/Frustum.h"
#include "light/Light.h"
#include <vector>
namespace SRE {
	class RenderSystem {
	public:		
		RenderSystem(Scene* scene, Camera* camera);
		void render();				
	protected:
		void beforeRender();//��Ⱦ֮ǰ����renderstate		
		void renderImpl();
		void afterRender();//һ֡����	
		void shadowMapRender(std::vector<Light::ptr> lights, std::vector<RenderObject::ptr> meshs);
		void resize(int x, int y, int width, int height);
		void renderMeshs(std::vector<RenderObject::ptr> meshs);
		void projectObject(Object3D::ptr object);
		void setProgram(RenderObject::ptr mesh);
		void setupLights(std::vector<Light::ptr> lights);		
		void setTexture(TextureUnitState::ptr texutre);		
	protected:	
		Scene::ptr _scene;
		Camera::ptr _camera;

		std::vector<RenderObject::ptr> _opaqueMehss;
		std::vector<RenderObject::ptr> _transparentMeshs;
		std::vector<RenderObject::ptr> _shadowMeshs;
		std::vector<Light::ptr> _lights;
		std::vector<Light::ptr> _shadow_lights;
		Frustum _frustum;
		unsigned int _current_texture_unit_count;
		std::string _light_num_define;
		bool _isProjected;

		Shader::ptr _shadowDepth;
		Shader::ptr _cubeShadowDepth;
	};
}


