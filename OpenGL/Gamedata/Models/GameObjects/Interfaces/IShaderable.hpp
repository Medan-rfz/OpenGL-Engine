#pragma once
#include "../../../Common/Shader.hpp"

namespace MEngine::Models::GameObjects
{
	class IShaderable
	{
	public:
		Common::Shader* shader;
		void SetShader(Common::Shader* shader);
		void ShaderUse();
	};
}
