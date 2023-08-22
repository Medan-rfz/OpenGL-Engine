#pragma once

#include "Object3D.hpp"
#include "Interfaces/ITexturable.hpp"

namespace MEngine::Models::GameObjects
{
	class SimpleObject : public Object3D, public ITexturable
	{
	public:
		SimpleObject(const char* file);
	private:

	};
}
