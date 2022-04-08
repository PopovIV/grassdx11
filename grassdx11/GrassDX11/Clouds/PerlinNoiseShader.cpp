#include "pch.h"
#include "ShaderHandlers/PerlinNoiseShader.h"

PerlinNoiseShader::PerlinNoiseShader(Renderer& renderer)
	: Shader(renderer, "CompiledShaders/TestV.cso", "CompiledShaders/TestP.cso", std::vector<D3D11_INPUT_ELEMENT_DESC> {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		}) {}

PerlinNoiseShader::~PerlinNoiseShader() {}
