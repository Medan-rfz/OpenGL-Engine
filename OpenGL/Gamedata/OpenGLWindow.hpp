#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace MEngine
{
	class OpenGLWindow
	{
	public:
		GLFWwindow* window;

		OpenGLWindow();
		~OpenGLWindow();

		void ResetOfBuffers();
		bool IsCloseEvent();
	};
}
