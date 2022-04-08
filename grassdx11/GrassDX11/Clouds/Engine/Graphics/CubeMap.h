#pragma once

#include "Texture.h"

namespace AvocadoSky {
	class CubeMap : public Texture {
	public:
		CubeMap(Renderer& renderer, TextureFilter filter = TextureFilter::BILINEAR,
			TextureFormat textureFormat = TextureFormat::R8G8B8A8_UNORM,
			TextureEdgeSampling textureEdgeSampling = TextureEdgeSampling::CLAMP);
		~CubeMap();

		virtual bool createAsRenderTexture(unsigned int faceWidth, unsigned int faceHeight) override;
		virtual bool createSRV() override;
	};
}