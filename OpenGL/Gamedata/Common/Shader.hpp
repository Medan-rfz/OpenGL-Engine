#pragma once

#include <GL/glew.h>

namespace MEngine::Common
{
	class Shader
	{
	public:
		Shader(const char* vertexPath, const char* fragmentPath);
		GLuint Program();
		void Use();

	private:
		GLuint _program;
	};
}
