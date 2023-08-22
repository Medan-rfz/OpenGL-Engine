#pragma once
#include <GL/glew.h>

#include "../Common/TextureLoader.hpp"

namespace MEngine::Models
{
	class Texture
	{
	public:

		Texture(const char* file);
		int Widght();
		int Height();
		GLubyte* Data();

	private:
		GLubyte* _texture;
		int _widgth;
		int _height;
	};
}
