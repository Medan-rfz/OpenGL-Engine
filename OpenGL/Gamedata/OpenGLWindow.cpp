#include "OpenGLWindow.hpp"

namespace MEngine
{
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	OpenGLWindow::OpenGLWindow()
	{
		window = NULL;

		if (!glfwInit())
		{
			fprintf(stderr, "������ ��� ������������� GLFWn");
			return;
		}

		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(1280, 720, "OpenGL Engine", NULL, NULL);

		if (window == NULL) {
			fprintf(stderr, "���������� ������� ���� GLFW. ���� � ��� Intel GPU, �� �� �� ������������ ������ 3.3. ���������� ������ ������ ��� OpenGL 2.1.n");
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(window);

		glewExperimental = true;
		if (glewInit() != GLEW_OK) {
			fprintf(stderr, "���������� ���������������� GLEWn");
			return;
		}
	}

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	OpenGLWindow::~OpenGLWindow()
	{
		glfwTerminate();
	}

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	void OpenGLWindow::ResetOfBuffers()
	{
		glfwSwapInterval(0);
		glfwSwapBuffers(window);
		glViewport(0, 0, 1920, 1080);
		glClearColor(0.3f, 0.3f, 0.4f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	bool OpenGLWindow::IsCloseEvent()
	{
		return (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) && (glfwWindowShouldClose(window) == 0);
	}
}
