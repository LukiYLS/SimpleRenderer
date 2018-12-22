#pragma once
#include <GL/glew.h>
#include <memory>
#include <map>
#include "object/Material.h"
namespace SRE {
	class RenderState {//������
		
		
		enum StateList {
			DepthTest = GL_DEPTH_TEST,
			Blend = GL_BLEND,
			CullFace = GL_CULL_FACE,
			StencilTest = GL_STENCIL_TEST,
			ScissorTest = GL_SCISSOR_TEST
		};		
	public:		
		typedef std::shared_ptr<RenderState> ptr;
		RenderState();
		void use();
		void enable(StateList state) { _state_map[state] = true; }
		void disable(StateList state) { _state_map[state] = false; }
		void setDepthFunc(CompareFunc func) { depthFunc = func; }
		void setStencilFunc(CompareFunc func) { stencilFunc = func; }
		void setCullFace(CullFaceMode face);
		void setBlendingFunc();
		//void init();	
//		static void disable(StateList state) { glDisable(state); }
		static void setViewPort(int x, int y, int width, int height);
		static void setMaterial(Material::ptr material);
		static void init();
		static void reset();
		static void setBlending();
		//static void setDepthFunc(CompareFunc func);
		static void setStencilTest();
		static void setMask();
	protected:		
		typedef std::map<StateList, bool> StateMap;
		StateMap _state_map;
		CullFaceMode mode;
		CompareFunc depthFunc;
		CompareFunc stencilFunc;
	};
}

