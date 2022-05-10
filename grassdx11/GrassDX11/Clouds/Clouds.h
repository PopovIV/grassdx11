#pragma once
#include "ShaderHandlers/SkyboxShader.h"
#include "ShaderHandlers/SkyPlaneShaderClass.h"
#include "Engine/Graphics/Texture.h"
#include "Examples/GameObjects/Skybox.h"


namespace AvocadoSky {

	class Clouds {

		struct CloudsBuffer {
			float translation;
			float scale;
			float brightness;
			//float padding;
			float gray;
		} cb{};

		Renderer& renderer;

		MeshData meshData;
		Mesh mesh;

		Skybox* skybox;

		SkyPlaneShaderClass shader;
		ConstantBuffer constantBuffer;
		Texture  perturbTexture;
		Texture cloudTexture;

	public:

		Clouds(Renderer& renderer);
		~Clouds();

		void draw(XMMATRIX const& worldMatrix);

		void setSkybox(Skybox& skybox);
	};
}

