#pragma once

#include "../Engine/Graphics/Shader.h"

namespace AvocadoSky {
	class ColorShader : public Shader
	{
	private:
	public:
		ColorShader(Renderer& renderer);
		~ColorShader();
	};
}