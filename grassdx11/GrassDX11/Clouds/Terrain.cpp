#include "pch.h"
#include "Terrain.h"

Terrain::Terrain(Renderer& renderer) : skybox(nullptr), meshData(DefaultMesh::PLANE, 10, 10, false), mesh(renderer, this->meshData),
shader(renderer), constantBuffer(renderer, sizeof(TerrainBuffer)), renderer(renderer),

hightmapTexture(renderer, TextureFilter::BILINEAR, TextureFormat::R16G16B16A16_UNORM, TextureEdgeSampling::REPEAT),
dirtTexture(renderer, TextureFilter::BILINEAR, TextureFormat::R16G16B16A16_UNORM, TextureEdgeSampling::REPEAT),
colormapTexture(renderer, TextureFilter::BILINEAR, TextureFormat::R8G8B8A8_UNORM, TextureEdgeSampling::REPEAT) {

	//Load dds clouds textures
	this->hightmapTexture.createFromFile("Resources/Textures/terrain/colorm01.bmp");
	this->dirtTexture.createFromFile("Resources/Textures/terrain/dirt01.dds");
	this->colormapTexture.createFromFile("Resources/Textures/terrain/heightmap01.bmp");

	this->constantBuffer.setPS();

	tb.ambientColor = XMFLOAT4(0.05f, 0.05f, 0.05f, 1.0f);
	tb.diffuseColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	tb.lightDirection = XMFLOAT3(-0.5f, -1.0f, 0.0f);
}

Terrain::~Terrain() {}

void Terrain::draw() {
	this->constantBuffer.update(&this->tb);

	this->dirtTexture.setPS(0);
	//this->perturbTexture.setPS(1);

	XMMATRIX newMatrix = this->skybox->getWorldMatrix();


	this->shader.update(renderer, this->mesh.getWorldMatrix(), true);
	this->shader.set();
	this->mesh.draw();
}

void Terrain::setSkybox(Skybox& skybox) {
	this->skybox = &skybox;
}
