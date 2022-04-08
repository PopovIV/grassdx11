#pragma once

#include "../Engine/Graphics/Shader.h"


namespace AvocadoSky {
	class SkyPlaneShaderClass : public Shader {
	public:
		SkyPlaneShaderClass(Renderer& renderer);
		~SkyPlaneShaderClass();
	};
}