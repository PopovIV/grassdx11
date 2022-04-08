#include "PerlinNoise.h"

PerlinNoise::PerlinNoise(Renderer& renderer) :meshData(DefaultMesh::SQUARE, 0, 0, false),
mesh(renderer, this->meshData), shader(renderer), constantBuffer(renderer, sizeof(TIMESTRUCT)), renderer(renderer) {

	this->mesh.setWorldMatrix(XMMatrixScaling(1.0f, 1.0f, 1.0f));
	this->ts.ScreenWidth = 1920;
	this->ts.ScreenHeight = 1080;
}

PerlinNoise::~PerlinNoise() {}

void PerlinNoise::draw() {

	// Update and set shader buffer
	int windowWidth = 1920;
	int windowHeight = 1080;

	this->ts.Time = 0;
	this->ts.ScreenHeight = windowHeight;
	this->ts.ScreenWidth = windowWidth;

	this->constantBuffer.update(&this->ts);

	// Update shader
	this->shader.update(renderer, this->mesh.getWorldMatrix());

	// Set shader to render mesh with
	this->shader.set();

	// Render mesh
	this->mesh.draw();
}
