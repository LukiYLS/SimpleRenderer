#pragma once
#include <GLFW/glfw3.h>
#include <vector>
#include <memory>
#include "utils/Event.h"
#include "utils/InputDefine.h"
#include "render/RenderSystem.h"
namespace SRE {	
	
	class Win {
		
	public:	
		static Win* getSingleton();
		bool create(const int& width = 800, const int& height = 600, const char* name = "SimpleRenderEngine v1.0");
		void loadRenderSystem(RenderSystem* rs) { _render_system = rs; }
		void startRenderLoop();	
	protected:
		static void cursorPositionCallback(GLFWwindow *window, double xpos, double ypos);
		static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void framebufferSizeCallback(GLFWwindow* window, int width, int height);		
		static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	protected:
		static Win* instance;
		void processInput();
		GLFWwindow* window;				
		RenderSystem* _render_system;		
	};
}

