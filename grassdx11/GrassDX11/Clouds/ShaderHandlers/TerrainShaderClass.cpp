#include "TerrainShaderClass.h"

using namespace AvocadoSky;

TerrainShaderClass::TerrainShaderClass(Renderer& renderer): 
	Shader(renderer, "CompiledShaders/TerrainShader_Vert.cso", "CompiledShaders/TerrainShader_Pix.cso", std::vector<D3D11_INPUT_ELEMENT_DESC> {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA , 0}, },
		true
		) {}

TerrainShaderClass::~TerrainShaderClass()
{
}
