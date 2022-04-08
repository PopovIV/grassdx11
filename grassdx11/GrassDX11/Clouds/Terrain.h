#pragma once

#include "ShaderHandlers/TerrainShaderClass.h"
#include "Engine/Graphics/Texture.h"
#include "Examples/GameObjects/Skybox.h"

class Terrain
{
	struct TerrainBuffer {
		XMFLOAT4 ambientColor;
		XMFLOAT4 diffuseColor;
		XMFLOAT3 lightDirection;

		float padding;
	} tb{};

	Renderer& renderer;

	MeshData meshData;
	Mesh mesh;

	Skybox* skybox;

	TerrainShaderClass shader;
	ConstantBuffer constantBuffer;
	Texture hightmapTexture;
	Texture colormapTexture;
	Texture dirtTexture;

public:
	Terrain(Renderer& renderer);
	~Terrain();

	void draw();	

	void setSkybox(Skybox& skybox);
};

