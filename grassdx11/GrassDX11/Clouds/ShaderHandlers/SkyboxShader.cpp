#include "SkyboxShader.h"

using namespace AvocadoSky;

SkyboxShader::SkyboxShader(Renderer& renderer)
	: Shader(renderer, "Clouds/CompiledShaders/SkyboxShader_Vert.cso", "Clouds/CompiledShaders/SkyboxShader_Pix.cso") {}

SkyboxShader::~SkyboxShader() {}
