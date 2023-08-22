#include "World.hpp"
#include "Camera.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>


namespace MEngine::Models
{
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	MEngine::Models::Camera::Camera()
	{

	}

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	void Camera::Update()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(_eulerAngles.z)) * cos(glm::radians(_eulerAngles.x));
		front.y = sin(glm::radians(_eulerAngles.z)) * cos(glm::radians(_eulerAngles.x));
		front.z = sin(glm::radians(_eulerAngles.x));
		_cameraFront = glm::normalize(front);

		_projection = glm::perspective(glm::radians(_fov), _sidesRatio, _minViewDist, _maxViewDist);
		_view = glm::lookAt(_position, _position + _cameraFront, _cameraUp);
	}

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	glm::mat4 Camera::GetViewMatrix()
	{
		return _view;
	}

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	glm::mat4 Camera::GetProjectionMatrix()
	{
		return _projection;
	}

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	void Camera::SetPosition(glm::vec3 position)
	{
		_position = position;
	}

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	void Camera::MoveTo(MoveDirection dir, float size)
	{
		if (dir == MoveDirection::FORWARD)
		{
			_position += size * _cameraFront;
		}
		else if (dir == MoveDirection::BACKWARD)
		{
			_position -= size * _cameraFront;
		}
		else if (dir == MoveDirection::LEFT)
		{
			_position -= size * glm::normalize(glm::cross(_cameraFront, _cameraUp));
		}
		else if (dir == MoveDirection::RIGHT)
		{
			_position += size * glm::normalize(glm::cross(_cameraFront, _cameraUp));
		}
		else if (dir == MoveDirection::UP)
		{
			_position += size * _cameraUp;
		}
		else if (dir == MoveDirection::DOWN)
		{
			_position -= size * _cameraUp;
		}
	}

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	void Camera::RotateTo(glm::vec3 eulerAngles)
	{
		_eulerAngles -= eulerAngles;

		if (_eulerAngles.x > 89.0f)
			_eulerAngles.x = 89.0f;
		if (_eulerAngles.x < -89.0f)
			_eulerAngles.x = -89.0f;
	}

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	glm::vec3 Camera::GetPosition()
	{
		return _position;
	}
}