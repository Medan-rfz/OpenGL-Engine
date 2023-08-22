#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

namespace MEngine::Models
{
	enum class MoveDirection 
	{
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,
		UP,
		DOWN
	};

	class Camera
	{
	public:
		Camera();

		void Update();
		glm::mat4 GetViewMatrix();
		glm::mat4 GetProjectionMatrix();

		void SetPosition(glm::vec3 position);
		void MoveTo(MoveDirection dir, float size);
		void RotateTo(glm::vec3 eulerAngles);

		glm::vec3 GetPosition();

	private:
		float _fov = 75.0f;
		float _sidesRatio = 16.0f / 9.0f;
		float _minViewDist = 0.1f;
		float _maxViewDist = 100.0f;

		glm::mat4 _view;
		glm::mat4 _projection;
		glm::vec3 _position = glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 _eulerAngles = glm::vec3(0.0f, 0.0f, 0.0f);

		glm::vec3 _cameraUp = glm::vec3(0.0f, 0.0f, 1.0f);
		glm::vec3 _cameraFront = glm::vec3(1.0f, 0.0f, 0.0f);
		glm::vec3 _cameraRight = glm::normalize(glm::cross(_cameraUp, _cameraFront));
	};
}


