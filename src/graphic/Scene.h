#pragma once
#include "object/Object3D.h"
#include <map>
#include <vector>
#include <string>
#include "object/Skybox.h"
using std::string;
using std::map;
using std::vector;


namespace SRE {
	struct Fog {

		Vector3D color;
		float near;
		float far;
		Fog() :color(Vector3D(1.0, 1.0, 1.0)),
			near(1.0),
			far(1000.0)
		{

		}
	};

	class Scene {
	public:
		typedef std::shared_ptr<Scene> ptr;
		Scene();
	public:
		void setSceneRoot(Object3D::ptr root) { _root = root; }
		Object3D::ptr const getSceneRoot()const { return _root; }		
		void setSkybox(Skybox::ptr skybox) { _skybox = skybox; }
		Skybox::ptr getSkybox() { return _skybox; } 
		void setUseShadowMap(bool isUse) { _useShadowMap = isUse; }
		bool getUseShadowMap()const { return _useShadowMap; }
		bool getUseFog()const { return _useFog; }
		void setUseFog(bool isUse) { _useFog = isUse; }
		Fog getFog()const { return _fog; }
		void setFog(Fog fog) { _fog = fog; }
		bool neadUpdate()const { return _neadUpdate; }
	protected:
	
		void update();
	
	protected:		
		Skybox::ptr _skybox;
		Object3D::ptr _root;	
		bool _useShadowMap, _useFog, _neadUpdate;
		Fog _fog;
	};
}

