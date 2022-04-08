#pragma once

#include "../Engine/Graphics/Shader.h"

namespace AvocadoSky {
	class SkyboxShader : public Shader {
	public:
		SkyboxShader(Renderer& renderer);
		~SkyboxShader();
	};
}