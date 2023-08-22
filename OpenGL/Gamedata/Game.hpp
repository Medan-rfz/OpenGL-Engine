#pragma once
#include "OpenGLWindow.hpp"
#include "Models/Camera.hpp"
#include "Common/Shader.hpp"


namespace MEngine
{
	class Game
	{
	public:
		
		Game(OpenGLWindow* window);
		void MainCycle();
		void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
		void MouseCallback(GLFWwindow* window, double xpos, double ypos);
		void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

	private:
		Models::Camera _camera;
		OpenGLWindow* _window;

		Common::Shader* _generalShader;
		Common::Shader* _lightShader;

		bool _keys[1024];

		float _prevMoveTimestamp = 0.0f;
		float _prevFrameTimestamp = 0.0f;
		int _FPS = 0;

		glm::vec2 _prevMousePos;
		float _sensivity = 0.05f;

		void Initialize();
		void MovementUpdate();
		void ComputeFPS();
	};
}
