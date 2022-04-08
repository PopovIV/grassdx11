#include "SkyPlaneShaderClass.h"

using namespace AvocadoSky;

SkyPlaneShaderClass::SkyPlaneShaderClass(Renderer& renderer)
	: Shader(renderer, "Clouds/CompiledShaders/CloudsShader_Vert.cso", "Clouds/CompiledShaders/CloudsShader_Pix.cso", 
		std::vector<D3D11_INPUT_ELEMENT_DESC>{ 
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }}) {}

SkyPlaneShaderClass::~SkyPlaneShaderClass() {}
