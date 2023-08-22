#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Gamedata/OpenGLWindow.hpp"
#include "Gamedata/Game.hpp"

MEngine::OpenGLWindow window;
MEngine::Game game(&window);

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	game.KeyCallback(window, key, scancode, action, mode);
}

static void MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	game.MouseCallback(window, xpos, ypos);
}

static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	game.ScrollCallback(window, xoffset, yoffset);
}

int main()
{
	glfwSetKeyCallback(window.window, KeyCallback);
	glfwSetCursorPosCallback(window.window, MouseCallback);
	glfwSetScrollCallback(window.window, ScrollCallback);

	game.MainCycle();

	return 0;
}