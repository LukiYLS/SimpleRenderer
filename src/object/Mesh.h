#pragma once
#include "RenderObject.h"
#include "Material.h"
#include <string>
#include <map>
namespace SRE {	
	
	class Mesh
		: public RenderObject
	{
	public:
		typedef std::shared_ptr<Mesh> ptr;
		Mesh();
	public:
		virtual Mesh* asMesh() { return this; }
		virtual const Mesh* asMesh() const { return this; }
		//void addTexture(const std::string& texName) { _textures.push_back(texName); }
		//void removeTexture(const std::string& texName) {}
		void setMaterial(Material::ptr material) { _material = material; }
		Material::ptr getMaterial() const { return _material; }
//		void setShaderName(const std::string& name) { _shader_name = name; }
//		const std::string& getShaderName() { return _shader_name; }
//		void addUniform(Uniform* uniform) { _uniforms.push_back((Uniform::ptr)uniform); }
//		void setRenderState(RenderState* renderstate) { _renderState = (RenderState::ptr)renderstate; }
		//RenderState* getRenderState() { return _renderState.get(); }
		//void setupUniform(Shader* shader);
		//virtual void setShaderUniform(Shader* shader) {}
		bool getReceiveShadow()const { return _receiveShadow; }
		void setReceiveShadow(bool receive) { _receiveShadow = receive; }

		void loadModel(const std::string& path);

		
	protected:	
		
		

		//std::vector<std::string> _textures;
		Material::ptr _material;	
		//std::string _shader_name;
		//std::vector<Uniform::ptr> _uniforms;
		//RenderState::ptr _renderState;
		bool _receiveShadow;
	};
}


