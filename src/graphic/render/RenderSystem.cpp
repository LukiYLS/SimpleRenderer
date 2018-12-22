#include "RenderSystem.h"
#include "RenderState.h"
#include "utils/CamerControl.h"
#include "utils/Event.h"
#include "utils/UtilsHelp.h"
#include "light/DirectionLight.h"
#include "light/PointLight.h"
#include "light/SpotLight.h"
#include "utils/MathHelper.h"
#include <iostream>
using namespace Utils;
namespace SRE {
	
	RenderSystem::RenderSystem(Scene* scene, Camera* camera)
	{
		_scene = (Scene::ptr)scene;
		_camera = (Camera::ptr)camera;
		_isProjected = false;
		_shadowDepth = NULL;
		_cubeShadowDepth = NULL;
		//
		CameraControl::ptr cc = std::make_shared<CameraControl>(camera);
		EventManager::Inst()->registerReceiver("mouse.event", cc);
		EventManager::Inst()->registerReceiver("keyboard.event", cc);
	}
	/*

	*/
	void RenderSystem::render()
	{		
		beforeRender();
		renderImpl(); 

		afterRender();
	}
	void RenderSystem::beforeRender()
	{		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		//RenderState::init();
	}
	/*
	true render
	*/
	void RenderSystem::renderImpl()
	{
		if (_camera == NULL)
		{
			std::cout << "SB,There is no camera!" << std::endl;
			return;
		}
		Object3D::ptr root = _scene->getSceneRoot();
		root->updateMatrixWorld();

		if (_camera->getParent())_camera->updateMatrixWorld();
		_frustum.setFromMatrix(_camera->getProjectionMatrix()*_camera->getViewMatrix());

		//Sort each object
		if (!_isProjected)
		{
			projectObject(root);
			_isProjected = true;
		}

		if (_scene->getUseShadowMap())
		{
			shadowMapRender(_lights, _shadowMeshs);	
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			RenderState::setViewPort(0, 0, 800, 600);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
		//use lights
		setupLights(_lights);

		////sort(),

		//start render
		
		//glDepthFunc(GL_LEQUAL);
		Skybox::ptr skybox = _scene->getSkybox();
		if (skybox)
			skybox->render(_camera.get());
		else
		{
			//clear color
		}
		//glDepthFunc(GL_LESS);
		if (_opaqueMehss.size()>0) renderMeshs(_opaqueMehss);

		// transparent pass (back-to-front order)

		if (_transparentMeshs.size()>0) renderMeshs(_transparentMeshs);
		//_scene->render(_camera.get());

		
	}
	/*
	uniform need?
	*/
	void RenderSystem::setupLights(std::vector<Light::ptr> lights)
	{
		unsigned int numDirectionLight = 0;
		unsigned int numPointLight = 0;
		unsigned int numSpotLight = 0;

		std::vector<DirectionLight*> directionLights;
		
		for (auto light : lights)
		{
			Vector3D color = light->getColor();
			float intensity = light->getIntensity();
			Light::LightType type = light->getType();
			Vector3D target = light->getLightTarget();
			if (type == Light::AmbientLightType)
			{

			}
			else if (type == Light::DirectionLightType)
			{				
				DirectionLight* directionLight = light->asDirectionLight();
				DirectionalLightUniform uniform_dir;

				//Vector3D direction = dir->getDirection();
				
				Vector3D position = directionLight->getWorldPosition();
				Vector3D direction =  position - target ;//default target(0,0,0)
				direction.normalize();
				uniform_dir.direction = direction;
				uniform_dir.color = color * intensity;
				bool castShadow = directionLight->getCastShadow();
				uniform_dir.shadow = castShadow;
				//no nead
				uniform_dir.shadowBias = light->getShadowBias();
				uniform_dir.shadowRadius = light->getShadowRadius();
				uniform_dir.shadowMapSize = light->getShadowMapSize();				

				directionLight->setNumber(numDirectionLight);
				directionLight->setUniform(uniform_dir);
				numDirectionLight++;

			}
			else if (type == Light::PointLightType)
			{
				PointLight* pointLight = light->asPointLight();
				PointLightUniform uniform_point;

				
				uniform_point.distance = pointLight->getDistance();
				uniform_point.position =  pointLight->getPosition();
				uniform_point.color = color * intensity;
				uniform_point.decay = pointLight->getDecay();
				bool castShadow = pointLight->getCastShadow();
				uniform_point.shadow = castShadow;

				uniform_point.shadowBias = light->getShadowBias();
				uniform_point.shadowRadius = light->getShadowRadius();
				uniform_point.shadowMapSize = light->getShadowMapSize();

				pointLight->setNumber(numPointLight);
				pointLight->setUniform(uniform_point);
				numPointLight++;
			}
			else if (type == Light::SpotLightType)
			{
				SpotLight* spotLight = light->asSpotLight();
				SpotLightUniform uniform_spot;

				Vector3D position = spotLight->getWorldPosition();
				Vector3D direction = position - target;//default target(0,0,0)
				direction.normalize();
				uniform_spot.direction = direction;
				uniform_spot.distance = spotLight->getDistance();
				uniform_spot.position = spotLight->getPosition();
				uniform_spot.color = color * intensity;
				uniform_spot.decay = (uniform_spot.distance == 0.0) ? 0.0 : spotLight->getDecay();
				uniform_spot.coneCos = cos(spotLight->getAngle());
				uniform_spot.penumbraCos = cos(spotLight->getAngle() * (1 - spotLight->getPenumbra()));
				bool castShadow = spotLight->getCastShadow();
				uniform_spot.shadow = castShadow;
				
				uniform_spot.shadowBias = light->getShadowBias();
				uniform_spot.shadowRadius = light->getShadowRadius();
				uniform_spot.shadowMapSize = light->getShadowMapSize();

				spotLight->setNumber(numSpotLight);
				spotLight->setUniform(uniform_spot);
				numSpotLight++;
			}

		}
		string dir_define = "#define NUM_DIR_LIGHTS ";
		string point_define = "#define NUM_POINT_LIGHTS ";
		string spot_define = "#define NUM_SPOT_LIGHTS ";

		_light_num_define = dir_define + StringHelp::Int2String(numDirectionLight) + "\n" +
			point_define + StringHelp::Int2String(numPointLight) + "\n" +
			spot_define + StringHelp::Int2String(numSpotLight) + "\n";

	}
	/*
	what's the problem,how to advance
	*/
	void RenderSystem::renderMeshs(std::vector<RenderObject::ptr> meshs)
	{
		for (auto mesh : meshs)
		{
			_current_texture_unit_count = 0;
			Material::ptr material = mesh->getMaterial();
			RenderState::setMaterial(material);//before render,set render envi
			setProgram(mesh);			
			mesh->drawPrimitive();
			glBindTexture(GL_TEXTURE_2D, 0);
			glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

		}
	}
	/*
	it's too... long, build shader and set material property,and upload 
	it must fit in all differect material, so how?
	*/
	void RenderSystem::setProgram(RenderObject::ptr mesh)
	{	
	
		Material::ptr material = mesh->getMaterial();
		Material::MaterialType type = material->getMaterialType();
		Shader* shader = material->getShader();
		if (type == Material::ShaderMaterial) {
			std::cout << "start create error";

			//only set uniform
			if(shader==NULL)
				return;
			shader->use();
			shader->setMat4("modelMatrix", mesh->getWorldMatrix());
			shader->setMat4("viewMatrix", _camera->getViewMatrix());
			shader->setMat4("projectionMatrix", _camera->getProjectionMatrix());
			//set uniform
			shader->uplaod();
			return;
		}
		//std::cout << "start create shader";

		if (!material->isShaderCreated())//first frame
		{
			//Shader *shader_mat = new Shader;
			//assemble their shader,corresponding to the material

			//1.build define information
			std::cout << "start create shader";

			shader = new Shader;
			std::string defineStr;

			if (_scene->getUseFog() && material->getFog())
			{
				defineStr += "#define USE_FOG\n";
			}
			if (material->getMap())
			{
				defineStr += "#define USE_MAP\n";
				//_textures.push_back(material->getMap());
			}
			if (material->getLightMap())
			{
				defineStr += "#define USE_LIGHTMAP\n";
			}
			if (material->getDisplacementMap())
			{
				defineStr += "#define USE_DISPLACEMENTMAP\n";
			}
			if (material->getEnvMap())
			{
				defineStr += "#define USE_ENVMAP\n";
				EnvMapType envmaptype = material->getEnvMapType();
				switch (envmaptype)
				{
				case CubeReflectionMapping:
				case CubeRefractionMapping:
					defineStr += "#define ENVMAP_TYPE_CUBE\n";
					break;

				case CubeUVReflectionMapping:
				case CubeUVRefractionMapping:
					defineStr += "#define ENVMAP_TYPE_CUBE_UV\n";
					break;

				case EquirectangularReflectionMapping:
				case EquirectangularRefractionMapping:
					defineStr += "#define ENVMAP_TYPE_EQUIRE\n";
					break;

				case SphericalReflectionMapping:
					defineStr += "ENVMAP_TYPE_SPHERE\n";
					break;
				default:
					break;
				}
				switch (envmaptype) {

				case CubeRefractionMapping:
				case EquirectangularRefractionMapping:
					defineStr += "#define ENVMAP_MODE_REFRACTION\n";
					break;
				default:
					break;

				}
				switch (material->getEnvMapBlendMode()) {

				case MultiplyOperation:
					defineStr += "#define ENVMAP_BLENDING_MULTIPLY\n";
					break;

				case MixOperation:
					defineStr += "#define ENVMAP_BLENDING_MIX\n";
					break;

				case AddOperation:
					defineStr += "#define ENVMAP_BLENDING_ADD\n";
					break;

				}
			}
			if (material->getSpecularMap())
			{
				defineStr += "#define USE_SPECULARMAP\n";
			}
			if (material->getAlphaMap())
			{
				defineStr += "#define USE_AlPHAMAP\n";
			}
			if (material->getAoMap())
			{
				defineStr += "#define USE_AOMAP\n";
			}

			if (mesh->isUseColor())
			{
				//这个define是指用vertex color
				//defineStr += "#define USE_COLOR\n";
			}
			if (_scene->getUseShadowMap())
			{
				defineStr += "#define USE_SHADOWMAP\n";
				defineStr += "#define SHADOWMAP_TYPE_PCF\n";
				//shadwomap type
			}
			std::cout << "start create shader source";

			std::string vertexStr, fragmentStr;
			std::string my_file_path = std::string(SRC_PATH);
			std::string vspath, fspath;
			switch (type)
			{
			case Material::BasicMaterial:
				vspath = my_file_path + "/src/assets/shader/basicMaterial.vs";
				fspath = my_file_path + "/src/assets/shader/basicMaterial.fs";
				vertexStr = StringHelp::readFileToStr(vspath.c_str());
				fragmentStr = StringHelp::readFileToStr(fspath.c_str());
				break;
			case Material::ShaderMaterial:			
				break;
			case Material::PhongMaterial:
				vspath = my_file_path + "/src/assets/shader/phongMaterial.vs";
				fspath = my_file_path + "/src/assets/shader/phongMaterial.fs";
				vertexStr = StringHelp::readFileToStr(vspath.c_str());
				fragmentStr = StringHelp::readFileToStr(fspath.c_str());
				break;		
			default:
				break;
			}
			std::string version = "#version 400 \n";
			std::string vertex_shader = version + _light_num_define + defineStr + vertexStr;
			std::string fragment_shader = version + _light_num_define + defineStr + fragmentStr;

			// std::cout << "shader source:" << std::endl;
			// std::ofstream out("vertex.txt");
    		// out << vertex_shader.c_str();
    		// out.close();
			// std::ofstream out1("fragment.txt");
    		// out << fragment_shader.c_str();
    		// out.close();
			//  std::cout << vertex_shader << std::endl;
			//  std::cout << fragment_shader << std::endl;
			shader->load(vertex_shader.c_str(), fragment_shader.c_str());

			material->setShader(shader);

		}
		//update uniform......
		shader->use();
		shader->setMat4("modelMatrix", mesh->getWorldMatrix());
		shader->setMat4("viewMatrix", _camera->getViewMatrix());
		shader->setMat4("projectionMatrix", _camera->getProjectionMatrix());
		shader->setVec3("cameraPosition", _camera->getPosition());
		shader->setMat3("normalMatrix", MathHelper::getNormalMatrix(mesh->getWorldMatrix()));

		shader->setFloat("opacity", material->getOpacity());
		shader->setVec3("diffuse", material->getColor());
		shader->setVec3("emissive", material->getEmissive());
		shader->setVec3("specular", material->getSpecular());
		shader->setFloat("shininess", material->getShininess());

		if (_scene->getUseFog() && material->getFog())
		{
			Fog fog = _scene->getFog();
			shader->setFloat("fogNear", fog.near);
			shader->setFloat("fogFar", fog.far);
			shader->setVec3("fogColor", fog.color);
		}

		TextureUnitState::ptr map = material->getMap();
		if (map)
		{
			Matrix3D uvTransfrom = Matrix3D::Identity;
			shader->setMat3("uvTransform", uvTransfrom);
			setTexture(map);
			shader->setInt("map", _current_texture_unit_count);
			_current_texture_unit_count++;
		}
		TextureUnitState::ptr lightMap = material->getLightMap();
		if (lightMap)
		{
			setTexture(lightMap);
			shader->setInt("lightMap", _current_texture_unit_count);
			shader->setFloat("lightMapIntensity", material->getLightMapIntensity());
			_current_texture_unit_count++;
		}

		TextureUnitState::ptr aoMap = material->getAoMap();
		if (aoMap)
		{
			setTexture(aoMap);
			shader->setInt("aoMap", _current_texture_unit_count);
			shader->setFloat("aoMapIntensity", material->getAoMapIntensity());
			_current_texture_unit_count++;
		}

		TextureUnitState::ptr alphaMap = material->getAlphaMap();
		if (alphaMap)
		{
			setTexture(alphaMap);
			shader->setInt("alphaMap", _current_texture_unit_count);			
			_current_texture_unit_count++;
		}

		TextureUnitState::ptr specularMap = material->getSpecularMap();
		if (specularMap)
		{
			setTexture(specularMap);
			shader->setInt("specularMap", _current_texture_unit_count);			
			_current_texture_unit_count++;
		}
		

		TextureUnitState::ptr envMap = material->getEnvMap();
		if (envMap)
		{			
			setTexture(envMap);
			shader->setInt("envMap", _current_texture_unit_count);
			_current_texture_unit_count++;
			shader->setFloat("reflectivity", material->getReflectivity());
			shader->setFloat("refractionRatio", material->getRefractionRatio());
			float flipEnvMap = envMap->getTexture()->getTextureTarget() == TEX_TYPE_CUBE_MAP ? 1.0 : -1.0;
			shader->setFloat("flipEnvMap", flipEnvMap);
		}
		if (_scene->getUseShadowMap() && mesh->getReceiveShadow())
		{
			
		}
		//light upload...
		for (auto light : _lights)
		{
			light->upload(shader);
			if (_scene->getUseShadowMap())
				light->uploadShadow(shader, _current_texture_unit_count);
		}
			
		
	}
	/*
	something problem,
	*/
	void RenderSystem::setTexture(TextureUnitState::ptr texture)
	{
		UVWAddressingMode mode = texture->getTextureAddressingMode();
		//FilterOptions minFilter = texture->getTextureFiltering(FT_MIN);
		//FilterOptions magFilter = texture->getTextureFiltering(FT_MAG);
		//FilterOptions mipFilter = texture->getTextureFiltering(FT_MIP);

		GLenum target = texture->getTexture()->getTextureTarget();

		//there is some problem
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		
		glTexParameteri(target, GL_TEXTURE_WRAP_S, mode.u);
		glTexParameteri(target, GL_TEXTURE_WRAP_T, mode.v);
		glTexParameteri(target, GL_TEXTURE_WRAP_R, mode.w);

		texture->getTexture()->bindTextureUnit(_current_texture_unit_count);
		//glBindTexture(target, 0);
	}
	/*
	sort object,how to avoid execute every frame?
	from root object to child node ,tranvse node according different pt
	*/
	void RenderSystem::projectObject(Object3D::ptr object)
	{
		//if (object->visible = false)return;
		if (object->asRenderObject())
		{
			RenderObject::ptr mesh = (RenderObject::ptr)object->asRenderObject();
			//if (_frustum.intersectsSphere(*mesh->getBoundSphere().get()))
			{
				Material::ptr material = mesh->getMaterial();
				if (material->getTransparent())
				{
					if (std::find(_transparentMeshs.begin(), _transparentMeshs.end(), mesh) == _transparentMeshs.end())
						_transparentMeshs.push_back(mesh);
				}
				else
				{
					if (std::find(_opaqueMehss.begin(), _opaqueMehss.end(), mesh) == _opaqueMehss.end())
						_opaqueMehss.push_back(mesh);
				}

				if (mesh->getReceiveShadow())
					_shadowMeshs.push_back(mesh);


			}	
			//int a = mesh.use_count();

		}
		else if (object->asLight())
		{
			Light::ptr light = (Light::ptr)object->asLight();
			if (std::find(_lights.begin(), _lights.end(), light) == _lights.end())
				_lights.push_back((Light::ptr)light);
			if (light->getCastShadow())
			{
				if (std::find(_shadow_lights.begin(), _shadow_lights.end(), light) == _shadow_lights.end())
					_shadow_lights.push_back((Light::ptr)light);
			}
				

		}		
		else if (true/*object->asSprite()*/)
		{

		}
		else if (object->asBillboardCollection())
		{
			//BillboardCollection* bbc = object->asBillboardCollection();
			//bbc->init();
			//_plugins.push_back(bbc);
		}
		else if (true/*object->asParticleSystem()*/)
		{

		}
		else
		{

		}
		unsigned int count = object->getChildCount();
		for (unsigned int i = 0; i < count; i++)
		{
			Object3D::ptr child = object->getChild(i);
			projectObject(child);
		}	
	}
	/*
	what fuck! why place here,should i create a shadow map plugin
	*/
	void RenderSystem::shadowMapRender(std::vector<Light::ptr> lights, std::vector<RenderObject::ptr> meshs)
	{
		//
		if (lights.empty())
			return;

		//use for point light ,shit!!!
		Vector3D cubeDirections[6] = { Vector3D(1, 0, 0),Vector3D(-1, 0, 0),Vector3D(0, 1, 0),
			Vector3D(0, -1, 0),Vector3D(0, 0, 1),Vector3D(0, 0, -1) };

		Vector3D cubeUps[6] = {
			Vector3D(0, -1, 0), Vector3D(0, -1, 0), Vector3D(0, 0, 1),
			Vector3D(0, 0, -1), Vector3D(0, -1, 0), Vector3D(0, -1, 0)
		};
		
		Matrix4D cubeShadowMatrix[6];
		std::string my_file_path = std::string(SRC_PATH);
		std::string vspath, fspath;
		if(_shadowDepth ==NULL){
			vspath = my_file_path + "/src/assets/shader/shadowmapdepth.vs";
			fspath = my_file_path + "/src/assets/shader/shadowmapdepth.fs";
			_shadowDepth = std::make_shared<Shader>(vspath.c_str(), fspath.c_str());

		}
		if (_cubeShadowDepth == NULL)
			vspath = my_file_path + "/src/assets/shader/pointshadowmapdepth.vs";
			fspath = my_file_path + "/src/assets/shader/pointshadowmapdepth.fs";
			std::string gspath = my_file_path + "/src/assets/shader/pointshadowmapdepth.gs";
			_cubeShadowDepth = std::make_shared<Shader>(vspath.c_str(), fspath.c_str(), gspath.c_str());
		
		Matrix4D shadowMatrix;

		for (auto light : lights)
		{
			Light::LightType type = light->getType();			
			Camera* shadowCamera = light->getShadowCamera();
			Vector2D mapSize = light->getShadowMapSize();
			Vector3D cameraPosition = light->getWorldPosition();
			shadowCamera->setPosition(cameraPosition);
			shadowCamera->lookAt(0.0, 0.0, 0.0);//??
			if (type == Light::PointLightType)
			{				
				for (int i = 0; i < 6; i++)
				{
					shadowCamera->lookAt(shadowCamera->getPosition(), shadowCamera->getPosition() + cubeDirections[i], cubeUps[i]);
					cubeShadowMatrix[i] = shadowCamera->getProjectionMatrix()*shadowCamera->getViewMatrix();
				}
				
			}
			else{				

				Matrix4D matrix(
					0.5, 0.0, 0.0, 0.0,
					0.0, 0.5, 0.0, 0.0,
					0.0, 0.0, 0.5, 0.0,
					0.5, 0.5, 0.5, 1.0
				);

				Matrix4D view = shadowCamera->getViewMatrix();

				Matrix4D projection = shadowCamera->getProjectionMatrix();

				shadowMatrix = matrix * projection * view;

			}
			//create fbo
			FrameBuffer* fb = light->getShadowFrameBuffer();
			if (fb == NULL)
			{
				if (type == Light::PointLightType)
				{
					fb = new FrameBufferCube(mapSize.x, mapSize.y, FrameBuffer::DepthBuffer);
				}
				else
					fb = new FrameBuffer2D(mapSize.x, mapSize.y, FrameBuffer::DepthBuffer);				
				light->setShadowFrameBuffer(fb);
			}
			light->setShadowMatrix(shadowMatrix);
			
			//FrameBuffer::ptr fbo = std::make_shared<FrameBuffer>();
			//fbo->createFrameBufferWithTexture(mapSize.x, mapSize.y);
			////save shadow infomation(matrix ,fbo)
			//Light::ShadowInfo shadowInfo;
			//shadowInfo.shadowMatrix = shadowMatrix;
			//shadowInfo.depthFBO = fbo;
			//light->setShadowInfo(shadowInfo);

			fb->bindForWriting();

			if (type == Light::PointLightType)
			{
				_cubeShadowDepth->use();
				for (unsigned int i = 0; i < 6; ++i)
					_cubeShadowDepth->setMat4(("shadowMatrices[" + std::to_string(i) + "]").c_str(), cubeShadowMatrix[i]);
				_cubeShadowDepth->setVec3("lightPosition", light->getPosition());
				PerspectiveCamera* pointCamera = (PerspectiveCamera*)shadowCamera;
				_cubeShadowDepth->setFloat("farPlane", pointCamera->getFar());
				for (auto mesh : meshs)
				{
					_cubeShadowDepth->use();
					_cubeShadowDepth->setMat4("modelMatrix", mesh->getWorldMatrix());
					mesh->drawPrimitive();
				}		

			}
			else
			{
				for (auto mesh : meshs)
				{
					_shadowDepth->use();
					_shadowDepth->setMat4("modelMatrix", mesh->getWorldMatrix());
					_shadowDepth->setMat4("viewMatrix", shadowCamera->getViewMatrix());
					_shadowDepth->setMat4("projectionMatrix", shadowCamera->getProjectionMatrix());
					mesh->drawPrimitive();
				}
			}				

			
		}
		
	}
	void RenderSystem::resize(int x, int y, int width, int height)
	{
		ViewPort::ptr vp = _camera->getViewPort();
		vp->setViewport(x, y, width, height);
	}
	void RenderSystem::afterRender()
	{
		//reset ...
		//_render_mesh.clear();
		//_lights.clear();

	}		
}