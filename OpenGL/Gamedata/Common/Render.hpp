#pragma once
#include "Shader.hpp"
#include "../Models/Camera.hpp"
#include "../Models/GameObjects/Object3D.hpp"
#include "../Models/GameObjects/SimpleObject.hpp"

using namespace MEngine::Models;
using namespace MEngine::Models::GameObjects;

namespace MEngine::Common
{
	class Render
	{
	public:
		//Render();
		Render(Camera* camera);

		void SetShader(Shader* shader);
		void SetLight(Object3D* obj);
		void RenderObject(Object3D* obj);
		void RenderObject(SimpleObject* obj);
		void SetViewMatrix(glm::mat4 viewMatrix);

		float* VBO = 0;

	private:
		Shader* _shader;
		Camera* _camera;
		Object3D* _light;
		glm::mat4 _viewMatrix;
		GLuint _modelMatrixID = 0;
		GLuint _viewMatrixID = 0;
		GLuint _projectionMatrixID = 0;
		GLuint _objectColorID = 0;
		GLuint _lightColorID = 0;
		GLuint _lightPosID = 0;
		GLuint _cameraPosID = 0;
	};
}
