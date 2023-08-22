#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <GL/glew.h>

#include "../../Common/Shader.hpp"
#include "Interfaces/IShaderable.hpp"

namespace MEngine::Models::GameObjects
{
	class Object3D : public IShaderable
	{
	public:
		std::vector<glm::vec3> modelVertices;
		std::vector<glm::vec2> uvVertices;
		std::vector<glm::vec3> normalVertices;
		std::vector<int> vertexIndices;
		std::vector<int> uvIndices;
		std::vector<int> normalIndices;

		Object3D(const char* file);
		~Object3D();

		float* GetVBO();
		int SizeVBO();
		size_t GetVertexCount();
		glm::mat4 GetModelMatrix();

		void SetPosition(glm::vec3 position);
		void SetRotate(glm::vec3 angle);
		void SetScale(float scale);
		void MoveTo(glm::vec3 duration);
		void Rotate(glm::vec3 duration);

		glm::vec3 GetPosition();

	private:
		float* _VBO = 0;
		int _sizeVBO;
		glm::mat4 _modelMatrix;
		glm::vec3 _position;
		glm::vec3 _rotate;
		float _scale;

		bool ReadFromOBJ(const char* file);
		glm::mat4 GetModelViewMatrix(glm::vec3 position, glm::vec3 anglesDegree, float scale);
		void GenerateVBO();
	};

}
