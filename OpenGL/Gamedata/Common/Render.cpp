#include "Render.hpp"

#include <GL/glew.h>
#include "../../Helpers/Logger.hpp"
#include "../../Helpers/Timer.hpp"

namespace MEngine::Common
{
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	Render::Render(Camera* camera)
	{
		_camera = camera;
	}

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	void Render::SetViewMatrix(glm::mat4 viewMatrix)
	{
		_viewMatrix = viewMatrix;
	}

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	void Render::SetShader(Shader* shader)
	{
		_shader = shader;
		auto program = _shader->Program();

		_modelMatrixID = glGetUniformLocation(program, "model");
		_viewMatrixID = glGetUniformLocation(program, "view");
		_projectionMatrixID = glGetUniformLocation(program, "projection");

		_objectColorID = glGetUniformLocation(program, "objectColor");

		_lightColorID = glGetUniformLocation(program, "lightColor");
		_lightPosID = glGetUniformLocation(program, "lightPos");

		_cameraPosID = glGetUniformLocation(program, "cameraPos");
	}

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	void Render::SetLight(Object3D* obj)
	{
		_light = obj;
	}

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	void Render::RenderObject(Object3D* obj)
	{
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		SetShader(obj->shader);
		obj->ShaderUse();

		auto model = obj->GetModelMatrix();
		auto view = _camera->GetViewMatrix();
		auto projection = _camera->GetProjectionMatrix();
		auto cameraPosition = _camera->GetPosition();
		auto lightPosition = _light->GetPosition();

		glUniformMatrix4fv(_modelMatrixID, 1, GL_FALSE, &model[0][0]);
		glUniformMatrix4fv(_viewMatrixID, 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(_projectionMatrixID, 1, GL_FALSE, &projection[0][0]);
		glUniform3f(_objectColorID, 1.0f, 0.5f, 0.3f);
		glUniform3f(_lightColorID, 1.0f, 1.0f, 1.0f);
		glUniform3f(_lightPosID, lightPosition.x, lightPosition.y, lightPosition.z);
		glUniform3f(_cameraPosID, cameraPosition.x, cameraPosition.y, cameraPosition.z);

		glBufferData(GL_ARRAY_BUFFER, obj->SizeVBO() * sizeof(float), obj->GetVBO(), GL_STATIC_DRAW);
		glDrawArrays(GL_TRIANGLES, 0, obj->GetVertexCount());

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	}

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	void Render::RenderObject(SimpleObject* obj)
	{
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		SetShader(obj->shader);
		obj->ShaderUse();

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, obj->texture->Widght(), obj->texture->Height(), 
			0, GL_RGBA, GL_UNSIGNED_BYTE, obj->texture->Data());
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		auto model = obj->GetModelMatrix();
		auto view = _camera->GetViewMatrix();
		auto projection = _camera->GetProjectionMatrix();
		auto cameraPosition = _camera->GetPosition();
		auto lightPosition = _light->GetPosition();

		glUniformMatrix4fv(_modelMatrixID, 1, GL_FALSE, &model[0][0]);
		glUniformMatrix4fv(_viewMatrixID, 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(_projectionMatrixID, 1, GL_FALSE, &projection[0][0]);
		glUniform3f(_objectColorID, 1.0f, 0.5f, 0.31f);

		glUniform3f(_lightColorID, 1.0f, 1.0f, 1.0f);
		glUniform3f(_lightPosID, lightPosition.x, lightPosition.y, lightPosition.z);

		glUniform3f(_cameraPosID, cameraPosition.x, cameraPosition.y, cameraPosition.z);

		auto vertices = obj->GetVBO();
		glBufferData(GL_ARRAY_BUFFER, obj->SizeVBO() * sizeof(float), vertices, GL_STATIC_DRAW);

		glDrawArrays(GL_TRIANGLES, 0, obj->GetVertexCount());

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	}
}
