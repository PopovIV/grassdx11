#include "pch.h"
#include "Clouds.h"
#include "SettingsController.h"

using namespace AvocadoSky;

Clouds::Clouds(Renderer& renderer): skybox(nullptr), meshData(DefaultMesh::SKY_PLANE, 1024, 1024, false), mesh(renderer, this->meshData),
shader(renderer), constantBuffer(renderer, sizeof(CloudsBuffer)),renderer(renderer),
perturbTexture(renderer, TextureFilter::BILINEAR, TextureFormat::R16G16B16A16_UNORM, TextureEdgeSampling::REPEAT),
cloudTexture(renderer, TextureFilter::BILINEAR, TextureFormat::R8G8B8A8_UNORM, TextureEdgeSampling::REPEAT) {
	
	//Load dds clouds textures
	this->cloudTexture.createFromFile("Clouds/Resources/Textures/cloud001.dds");
	this->perturbTexture.createFromFile("Clouds/Resources/Textures/perturb001.dds");

	this->constantBuffer.setPS();

	cb.brightness = 0.3f;
	cb.scale = 0.3f;
	//cb.padding = 10.0f;
	cb.translation = 0.0f;
	cb.gray = 0.9f;
}

Clouds::~Clouds(){}

void Clouds::draw(XMMATRIX const& worldMatrix) {

	this->constantBuffer.setPS();

	cb.translation += SettingsController::translationSpeed/10000;

	if (cb.translation > 1.0f)
	{
		cb.translation -= 1.0f;
	}

	cb.brightness = SettingsController::brightness;
	cb.scale = SettingsController::scale;

	this->shader.set();
	this->constantBuffer.update(&this->cb);
	this->cloudTexture.setPS(0);
	this->perturbTexture.setPS(1);

	this->shader.update(renderer, XMMatrixTranslation(0.0f, 50.0f, 0.0f) * worldMatrix, true);
	
	this->mesh.draw();
}

void Clouds::setSkybox(Skybox& skybox) {
	this->skybox = &skybox;
}
