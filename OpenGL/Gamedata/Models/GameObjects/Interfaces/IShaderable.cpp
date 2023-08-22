#include "IShaderable.hpp"

namespace MEngine::Models::GameObjects
{
	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	void IShaderable::SetShader(Common::Shader* shader)
	{
		this->shader = shader;
	}

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
	void IShaderable::ShaderUse()
	{
		shader->Use();
	}
}
