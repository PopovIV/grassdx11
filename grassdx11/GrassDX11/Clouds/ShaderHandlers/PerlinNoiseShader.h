#pragma once

#include "../Engine/Graphics/Shader.h"

namespace AvocadoSky {
	class PerlinNoiseShader : public Shader {
	public:
		PerlinNoiseShader(Renderer& renderer);
		~PerlinNoiseShader();
	};
}