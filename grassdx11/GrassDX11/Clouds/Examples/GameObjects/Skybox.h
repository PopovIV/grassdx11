#pragma once

#include "../../Engine/Graphics/MeshData.h"
#include "../../Engine/Graphics/MeshClass.h"
#include "../../Engine/Graphics/CubeMap.h"
#include "../../Engine/Graphics/ComputeShader.h"
#include "../../ShaderHandlers/SkyboxShader.h"



namespace AvocadoSky {
	class Skybox {
	private:
		static const int CUBE_FACE_WIDTH = 256;
		static const int CUBE_FACE_HEIGHT = 256;

		struct SkyboxBuffer {
			XMFLOAT3 sunDir;
			float turbidity;

			int faceWidth;
			int faceHeight;

			int padding[2];
		} sb{};



		MeshData meshData;
		Mesh mesh;

		ConstantBuffer constantBuffer;
		CubeMap skyCubeMap;
		ComputeShader preethamCreatorShader;
		SkyboxShader shader;

		Renderer& renderer;

		XMFLOAT3 sunDir;

	public:

		Skybox(Renderer& renderer);
		~Skybox();

		void draw(XMMATRIX const &worldMatrix);

		CubeMap& getCubeMap();

		const XMFLOAT3& getSunDir() const;

		const XMMATRIX& getWorldMatrix() const;
	};
}