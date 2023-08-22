#pragma once

#include <GL/glew.h>

namespace MEngine::Common
{
	class TextureLoader
	{
	public:
		static GLuint LoadTGA(const char* path);
		static bool LoadPngImage(const char* file, int& outWidth, int& outHeight, GLubyte** outData);
	};
}
