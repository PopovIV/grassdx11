#pragma once

#include "../../Engine/Graphics/MeshData.h"
#include "../../Engine/Graphics/Mesh.h"
#include "../../Engine/Graphics/CubeMap.h"
#include "../../Engine/Graphics/ComputeShader.h"
#include "../../ShaderHandlers/SkyboxShader.h"
#include "../../ShaderHandlers/PerlinNoiseShader.h"

class PerlinNoise {		

private:
	
	struct TIMESTRUCT
	{
		float Time;
		float ScreenWidth;
		float ScreenHeight;
		float padding;
	} ts{};

	MeshData meshData;
	Mesh mesh;
	ConstantBuffer constantBuffer;
	PerlinNoiseShader shader;

	Renderer& renderer;

public:
	PerlinNoise(Renderer& renderer);
	~PerlinNoise();

	void draw();
};

