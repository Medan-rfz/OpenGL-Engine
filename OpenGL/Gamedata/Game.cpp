#include "Game.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

#include "MockObjects.hpp"
#include "Common/Render.hpp"
#include "Common/TextureLoader.hpp"
#include "Models/GameObjects/Object3D.hpp"
#include "Models/GameObjects/SimpleObject.hpp"

#include "../Helpers/Logger.hpp"
#include "../Helpers/Timer.hpp"

using namespace glm;

using namespace MEngine::Models;
using namespace MEngine::Models::GameObjects;
using namespace MEngine::Common;

namespace MEngine
{
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	Game::Game(OpenGLWindow* window)
	{
		_window = window;
		_prevMousePos = glm::vec2(1920/2, 1080/2);

		_generalShader = new Shader("Shaders\\General.vs", "Shaders\\General.fs");
		_lightShader = new Shader("Shaders\\Light.vs", "Shaders\\Light.fs");

		Initialize();
	}

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	void Game::MainCycle()
	{
		_camera.SetPosition(glm::vec3(-2, 0, 1));
		Render render(&_camera);

		Object3D cubeLight("Objects\\Cube.obj");
		SimpleObject cubeObj("Objects\\Cube.obj");

		Texture texture("Textures\\CubeObj.png");

		cubeLight.SetShader(_lightShader);

		cubeObj.SetShader(_generalShader);
		cubeObj.texture = &texture;

		render.SetLight(&cubeLight);

		while (_window->IsCloseEvent())
		{
			glfwPollEvents();
			MovementUpdate();
			//ComputeFPS();
			_camera.Update();

			float time = glfwGetTime();
			float x = 10 * std::cos(2 * time);
			float y = 10 * std::sin(2 * time);
			cubeLight.SetPosition(glm::vec3(x, y, 10));

			render.RenderObject(&cubeObj);
			render.RenderObject(&cubeLight);

			_window->ResetOfBuffers();
		}
	}

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	void Game::Initialize()
	{
		GLuint vertexArrayID;
		glGenVertexArrays(1, &vertexArrayID);
		glBindVertexArray(vertexArrayID);

		GLuint vertexBuffer;
		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

		// Position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		// Normal
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		// UV-texture
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		glfwSetInputMode(_window->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	void Game::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);

		if (action == GLFW_PRESS)
			_keys[key] = true;
		else if (action == GLFW_RELEASE)
			_keys[key] = false;
	}

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	void Game::MouseCallback(GLFWwindow* window, double xpos, double ypos)
	{
		float moveX = (xpos - _prevMousePos.x) * _sensivity;
		float moveY = (ypos - _prevMousePos.y) * _sensivity;
		_prevMousePos.x = xpos;
		_prevMousePos.y = ypos;

		_camera.RotateTo(glm::vec3(moveY, 0.0f, moveX)); // Only pitch and yaw
	}

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	void Game::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{

	}

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	void Game::MovementUpdate()
	{
		float timestamp = glfwGetTime();
		float timeDuration = timestamp - _prevMoveTimestamp;
		_prevMoveTimestamp = timestamp;

		GLfloat cameraSpeed = 1.0f * timeDuration;
		if (_keys[GLFW_KEY_W])
			_camera.MoveTo(MoveDirection::FORWARD, cameraSpeed);
		if (_keys[GLFW_KEY_S])
			_camera.MoveTo(MoveDirection::BACKWARD, cameraSpeed);
		if (_keys[GLFW_KEY_A])
			_camera.MoveTo(MoveDirection::LEFT, cameraSpeed);
		if (_keys[GLFW_KEY_D])
			_camera.MoveTo(MoveDirection::RIGHT, cameraSpeed);
		if (_keys[GLFW_KEY_LEFT_SHIFT])
			_camera.MoveTo(MoveDirection::UP, cameraSpeed);
		if (_keys[GLFW_KEY_LEFT_CONTROL])
			_camera.MoveTo(MoveDirection::DOWN, cameraSpeed);
	}

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	void Game::ComputeFPS()
	{
		float time = glfwGetTime();
		_FPS = 1.0f / (time - _prevFrameTimestamp);
		_prevFrameTimestamp = time;
		std::cout << "FPS: " << _FPS << '\n';
	}
}

