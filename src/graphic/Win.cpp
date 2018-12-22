#include <GL/glew.h>
#include "Win.h"
#include  <iostream>
#include <list>
using namespace  Utils;
namespace SRE {
	
	Win* Win::instance(0);
	Win* Win::getSingleton() {
		if (!instance)
			instance = new Win();
		return instance;
	}
	std::vector<mouse_event> mouse_events;
	Keys keyboard_events;
	bool button_down = false;
	bool isKeyBoardDown = false;
	std::list<char> key_press;

	bool Win::create(const int& width, const int& height, const char* name)
	{
		glfwInit();
		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glViewport(0, 0, width, height);
		window = glfwCreateWindow(width, height, name, NULL, NULL);
		if (window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return false;
		}
		glfwMakeContextCurrent(window);

		glewExperimental = GL_TRUE;
		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
		{
			std::cout << "OpenGL Error: " << error << std::endl;
		}
		GLenum glewinit = glewInit();
		if (glewinit != GLEW_OK) {
			std::cout << "Glew not okay! " << glewinit;
			exit(EXIT_FAILURE);
		}

		glfwSetCursorPosCallback(window, cursorPositionCallback);
		glfwSetMouseButtonCallback(window, mouseButtonCallback);
		glfwSetKeyCallback(window, keyCallback);
		glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);	
		glfwSetScrollCallback(window, scrollCallback);

		
	}
	void Win::cursorPositionCallback(GLFWwindow *window, double xpos, double ypos)
	{
		if (!button_down)return;
		mouse_event event;
		double seconds = glfwGetTime();
		event.mouse_status = M_MOVE;
		event.time = seconds;
		event.xpos = xpos;
		event.ypos = ypos;
		mouse_events.push_back(event);
	}

	void Win::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		mouse_event event;
		double xpos, ypos;
		event.mouse_status = M_WHEEL;
		//event.wheelvalue = xoffset;
		if (yoffset > 0.0)
			event.wheelvalue = 10.0;
		else
			event.wheelvalue = -10.0;
		double seconds = glfwGetTime();
		glfwGetCursorPos(window, &xpos, &ypos);
		event.time = seconds;
		event.xpos = xpos;
		event.ypos = ypos;
		mouse_events.push_back(event);
	}
	void Win::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
	{
		mouse_event event;
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		double seconds = glfwGetTime();
		event.mouse_status = MOUSE_NONE;
		event.time = seconds;
		event.xpos = xpos;
		event.ypos = ypos;
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		{
			event.mouse_status = LB_DOWN;
			button_down = true;
		}
		else if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
		{
			event.mouse_status = MB_DOWN;
			button_down = true;
		}
		else if (button == GLFW_MOUSE_BUTTON_RIGHT  && action == GLFW_PRESS)
		{
			event.mouse_status = RB_DOWN;
			button_down = true;
		}
		else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		{
			event.mouse_status = LB_UP;
			button_down = false;
		}
		else if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE)
		{
			event.mouse_status = MB_UP;
			button_down = false;
		}
		else if (button == GLFW_MOUSE_BUTTON_RIGHT  && action == GLFW_RELEASE)
		{
			event.mouse_status = RB_UP;
			button_down = false;
		}

		if (event.mouse_status != MOUSE_NONE)
			mouse_events.push_back(event);

	}
	void Win::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		//get register keyboard,where register key 
		
		int state = glfwGetKey(window, key);
		if (state == GLFW_PRESS)
		{
			key_press.push_back(key);
		}
		else if(state == GLFW_RELEASE)
		{
			key_press.remove(key);
		}
		

		if ((key >= 0) && (key <= 255)&&(action = GLFW_PRESS))
		{
			//key_press.push_back(key);
			//isKeyBoardDown = true;
			//keyboard_events.keyDown[key] = true;
		}
		if ((key >= 0) && (key <= 255) && (action = GLFW_RELEASE))
		{
			//key_press.remove(key);
			//isKeyBoardDown = false;
			//keyboard_events.keyDown[key] = false;
		}
		if (key == GLFW_KEY_W && action == GLFW_RELEASE)
		{
			//key_press.remove(key);
			//key_press.push_back(key);
			//keyboard_events.keyDown[key] = false;
			//event->setValue(event_name, 'W');
			//EventManager::Inst()->sendEvent(event);

		}
		if (key == GLFW_KEY_A && action == GLFW_PRESS)
		{
			//event->setValue(event_name, 'A');
			//EventManager::Inst()->sendEvent(event);
		}
		if (key == GLFW_KEY_S && action == GLFW_PRESS)
		{
			//event->setValue(event_name, 'S');
			//EventManager::Inst()->sendEvent(event);
		}
		if (key == GLFW_KEY_D && action == GLFW_PRESS)
		{
			//event->setValue(event_name, 'D');
			//EventManager::Inst()->sendEvent(event);
		}
	}
	void Win::framebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		
		glViewport(0, 0, width, height);

	}
	void Win::processInput()
	{
		unsigned int num_events = mouse_events.size();
		if (mouse_events.size() > 0)
		{
			Event::ptr event = EventManager::Inst()->createEvent();
			mouse_event_vector xx;
			xx._mouse_events = &mouse_events[0];//mouse_events;
			xx._event_num = num_events;
			event->setName("mouse.event");
			event->setValue("mouse.event", xx);
			EventManager::Inst()->sendEvent(event);
		}
		mouse_events.clear();

		//keyboard
		for (auto key : key_press)
		{
			//char* event_name = (char*)"keyboard.event";
			Event::ptr event = EventManager::Inst()->createEvent();		
			event->setName("keyboard.event");
			event->setValue("keyboard.event", key);
			EventManager::Inst()->sendEvent(event);
		}
		if (isKeyBoardDown == true) {
			//only traversal register keyboard

		}
	}
	void Win::startRenderLoop()
	{
		while (!glfwWindowShouldClose(window))
		{			
			processInput();
			_render_system->render();
			glfwSwapBuffers(window);
			glfwPollEvents();
		}

	}
}