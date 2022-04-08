#pragma once

#include "../Engine/Graphics/Shader.h"

namespace AvocadoSky {
	class TextureShader : public Shader
	{
	private:
	public:
		TextureShader(Renderer& renderer);
		~TextureShader();
	};
}