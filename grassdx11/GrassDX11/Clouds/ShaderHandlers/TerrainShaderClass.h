#pragma once

#include "../Engine/Graphics/Shader.h"

namespace AvocadoSky {
	class TerrainShaderClass : public Shader {
	public:
		TerrainShaderClass(Renderer& renderer);
		~TerrainShaderClass();
	};
}