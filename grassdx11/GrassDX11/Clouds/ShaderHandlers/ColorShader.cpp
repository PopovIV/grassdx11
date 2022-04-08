#include "ColorShader.h"

using namespace AvocadoSky;

ColorShader::ColorShader(Renderer& renderer)
	: Shader(renderer, "CompiledShaders/DefaultColorShader_Vert.cso", "CompiledShaders/DefaultColorShader_Pix.cso") {}

ColorShader::~ColorShader() {}
