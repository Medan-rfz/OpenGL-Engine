#include "Object3D.hpp"

#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <glm/ext/matrix_transform.hpp>

#define FILE_OBJ_VERTEX_CODE	"v"
#define FILE_OBJ_TEXTURE_CODE	"vt"
#define FILE_OBJ_NORMAL_CODE	"vn"
#define FILE_OBJ_INDEX_CODE		"f"

namespace MEngine::Models::GameObjects
{
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	Object3D::Object3D(const char* file)
	{
		ReadFromOBJ(file);
		GenerateVBO();

		_position = { 0.0f, 0.0f, 0.0f };
		_rotate = { 0.0f, 0.0f, 0.0f };
		_scale = 1.0f;
		_modelMatrix = GetModelViewMatrix(_position, _rotate, _scale);
	}

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	Object3D::~Object3D()
	{

	}

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	void Object3D::GenerateVBO()
	{
		std::vector<float> VBO;
		VBO.reserve(vertexIndices.size() * 5);

		for (int i = 0; i < vertexIndices.size(); i++)
		{
			VBO.push_back(modelVertices[vertexIndices[i]].x);
			VBO.push_back(modelVertices[vertexIndices[i]].y);
			VBO.push_back(modelVertices[vertexIndices[i]].z);
			VBO.push_back(normalVertices[normalIndices[i]].x);
			VBO.push_back(normalVertices[normalIndices[i]].y);
			VBO.push_back(normalVertices[normalIndices[i]].z);
			VBO.push_back(uvVertices[uvIndices[i]].s);
			VBO.push_back(uvVertices[uvIndices[i]].t);
		}

		if(_VBO) delete _VBO;
		_sizeVBO = VBO.size();
		_VBO = new float[_sizeVBO];
		memcpy(_VBO, VBO.data(), _sizeVBO * sizeof(float));		
	}

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	float* Object3D::GetVBO()
	{
		return _VBO;
	}

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	int Object3D::SizeVBO()
	{
		return _sizeVBO;
	}

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	size_t Object3D::GetVertexCount()
	{
		return vertexIndices.size();
	}

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	glm::mat4 Object3D::GetModelMatrix()
	{
		return _modelMatrix;
	}

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	void Object3D::SetPosition(glm::vec3 position)
	{
		_position = position;
		_modelMatrix = GetModelViewMatrix(_position, _rotate, _scale);
	}

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	void Object3D::SetRotate(glm::vec3 angle)
	{
		_rotate = angle;
		_modelMatrix = GetModelViewMatrix(_position, _rotate, _scale);
	}

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	void Object3D::SetScale(float scale)
	{
		_scale = scale;
		_modelMatrix = GetModelViewMatrix(_position, _rotate, _scale);
	}

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	void Object3D::MoveTo(glm::vec3 duration)
	{
	}

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	void Object3D::Rotate(glm::vec3 duration)
	{

	}

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	glm::vec3 Object3D::GetPosition()
	{
		return _position;
	}

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	bool Object3D::ReadFromOBJ(const char* file)
	{
		std::ifstream stream(file);

		if (!stream.is_open())
		{
			// TODO Add logger
			return false;
		}

		std::string line;
		while (std::getline(stream, line))
		{
			auto code = line.substr(0, line.find(" "));

			if (code == FILE_OBJ_VERTEX_CODE)
			{
				glm::vec3 res;
				sscanf_s(line.c_str(), "%*s %f %f %f", &res.x, &res.y, &res.z);
				modelVertices.push_back(res);
			}
			else if (code == FILE_OBJ_TEXTURE_CODE)
			{
				glm::vec2 res;
				sscanf_s(line.c_str(), "%*s %f %f", &res.s, &res.t);
				uvVertices.push_back(res);
			}
			else if (code == FILE_OBJ_NORMAL_CODE)
			{
				glm::vec3 res;
				sscanf_s(line.c_str(), "%*s %f %f %f", &res.x, &res.y, &res.z);
				normalVertices.push_back(res);
			}
			else if (code == FILE_OBJ_INDEX_CODE)
			{
				auto countVertex = std::count(line.begin(), line.end(), ' ');

				if (countVertex == 3)
				{
					int x, y, z;
					int xt, yt, zt;
					int xn, yn, zn;

					sscanf_s(line.c_str(), "%*s %d/%d/%d %d/%d/%d %d/%d/%d", &x, &xt, &xn, &y, &yt, &yn, &z, &zt, &zn);

					vertexIndices.push_back(x - 1);
					vertexIndices.push_back(y - 1);
					vertexIndices.push_back(z - 1);

					uvIndices.push_back(xt - 1);
					uvIndices.push_back(yt - 1);
					uvIndices.push_back(zt - 1);

					normalIndices.push_back(xn - 1);
					normalIndices.push_back(yn - 1);
					normalIndices.push_back(zn - 1);
				}
				else if (countVertex == 4)
				{
					int x1, x2, x3, x4;
					int xt1, xt2, xt3, xt4;
					int xn1, xn2, xn3, xn4;

					sscanf_s(line.c_str(), "%*s %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", 
						&x1, &xt1, &xn1,
						&x2, &xt2, &xn2, 
						&x3, &xt3, &xn3, 
						&x4, &xt4, &xn4);

					vertexIndices.push_back(x1 - 1);
					vertexIndices.push_back(x2 - 1);
					vertexIndices.push_back(x3 - 1);
					vertexIndices.push_back(x1 - 1);
					vertexIndices.push_back(x3 - 1);
					vertexIndices.push_back(x4 - 1);

					uvIndices.push_back(xt1 - 1);
					uvIndices.push_back(xt2 - 1);
					uvIndices.push_back(xt3 - 1);
					uvIndices.push_back(xt1 - 1);
					uvIndices.push_back(xt3 - 1);
					uvIndices.push_back(xt4 - 1);

					normalIndices.push_back(xn1 - 1);
					normalIndices.push_back(xn2 - 1);
					normalIndices.push_back(xn3 - 1);
					normalIndices.push_back(xn1 - 1);
					normalIndices.push_back(xn3 - 1);
					normalIndices.push_back(xn4 - 1);
				}
			}
		}

		stream.close();
		return true;
	}

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	//bool Object3D::LoadTexture(const char* textiireFile)
	//{
	//	return Common::TextureLoader::LoadPngImage("A:\\YandexDisk\\MyProject\\1C++\\OpenGL\\OpenGL\\Objects\\textures\\Test.png",
	//		textureWidth, textureHeight, &textureData);
	//}

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	glm::mat4 Object3D::GetModelViewMatrix(glm::vec3 position, glm::vec3 anglesDegree, float scale)
	{
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 translateMatrix = glm::translate(model, position);
		glm::mat4 scaleMatrix = glm::scale(model, glm::vec3(scale, scale, scale));
		glm::mat4 rotateMatrix = glm::rotate(model, anglesDegree.x * glm::pi<float>() / 180.0f, glm::vec3(1.0f, 0.0f, 0.0f))
			* glm::rotate(model, anglesDegree.y * glm::pi<float>() / 180.0f, glm::vec3(0.0f, 1.0f, 0.0f))
			* glm::rotate(model, anglesDegree.z * glm::pi<float>() / 180.0f, glm::vec3(0.0f, 0.0f, 1.0f));

		return translateMatrix * rotateMatrix * scaleMatrix * model;
	}
}
