#include "Scene.h"
#include "render/FrameBuffer.h"
namespace SRE {

	Scene::Scene():
		_skybox(NULL),
		_root(NULL),
		_useShadowMap(false),
		_useFog(false),
		_neadUpdate(false)
	{

	}
	void Scene::update()
	{

	}

	//void Scene::render(Camera* camera)
	//{	
		//_root->updateMatrixWorld();		
		//projectObject(_root.get());	
		//if (skybox)
		//	skybox->render(camera);
		//else
		//{
		//	//clear color
		//}
		//if (_enable_shadow)
		//{
		//	//ShadowMapPlugin* sp = new ShadowMapPlugin(_lights, _render_mesh);
		//	//sp->render(camera);			
		//}		
		////render mesh
		////��δ���mesh�ж��renderpass
		//bool first = true;
		//for (auto mesh : _render_mesh)
		//{
		//	//multi_mesh
		//	//Shader* shader = ShaderManager::getSingleton()->getByName(mesh->getShaderName()).get();
		//	//shader->use();
		//	//shader->setMat4("model", mesh->getWorldMatrix());
		//	//shader->setMat4("view", camera->getViewMatrix());
		//	//shader->setMat4("projection", camera->getProjectionMatrix());
		//	//shader->setVec3("v3CameraPos", camera->getPosition());
		//	//shader->setFloat("fCameraHeight", camera->getPosition().length());
		//	//shader->setFloat("fCameraHeight2", camera->getPosition().length()*camera->getPosition().length());
		//	//setupLights(shader);
		//	//mesh->drawPrimitive();
		//	////if (_enable_shadow)mesh->addTexture("shadowMap");
		//	//mesh->setupUniform(shader);
		//	//glEnable(GL_CULL_FACE);
		//	//if (first)
		//	//{
		//		//first = false;

		//		//glCullFace(GL_BACK);
		//	//}
		//	//else
		//	glCullFace(GL_FRONT);
		//	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//	//mesh->draw(shader);
		//}
		//for (auto plugin : _plugins)
		//{
		//	plugin->render(camera);
		//}
		//clearTemp();
	//}
	
	
		
}