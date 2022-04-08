#include "Skybox.h"
#include "../../Engine/Application/Time.h"
#include "..\..\SettingsController.h"

using namespace AvocadoSky;

Skybox::Skybox(Renderer& renderer) : meshData(DefaultMesh::CUBE, 0, 0, true), mesh(renderer, this->meshData),
	shader(renderer), constantBuffer(renderer, sizeof(SkyboxBuffer)),
	renderer(renderer), skyCubeMap(renderer), 
	preethamCreatorShader(renderer, "Clouds/CompiledShaders/PreethamSkyCreator_Comp.cso", CUBE_FACE_WIDTH/16, CUBE_FACE_HEIGHT/16 , 6 / 2){
	
	// Make the mesh big enough to not clip into another mesh
	this->mesh.setWorldMatrix(XMMatrixScaling(1000.0f, 1000.0f, 1000.0f));
	// Create cube map as render texture
	this->skyCubeMap.createAsRenderTexture(CUBE_FACE_WIDTH, CUBE_FACE_HEIGHT);
	// Preetham creator shader
	this->preethamCreatorShader.addRenderTexture(this->skyCubeMap);
	this->preethamCreatorShader.addConstantBuffer(this->constantBuffer);

	// Set constants in shader buffer struct
	this->sb.faceWidth = CUBE_FACE_WIDTH;
	this->sb.faceHeight = CUBE_FACE_HEIGHT;

}

Skybox::~Skybox() {}

void Skybox::draw(XMMATRIX const& worldMatrix) {

	this->sunDir = XMFLOAT3(0.0f, cos(SettingsController::time), sin(SettingsController::time));

	// Update and set shader buffer
	this->sb.sunDir = this->sunDir;
	this->sb.turbidity = SettingsController::turbidity;
	this->constantBuffer.update(&this->sb);

	this->preethamCreatorShader.run();



	

	// Set sky box to use in pixel shader
	this->skyCubeMap.setPS();

	// Update shader
	this->shader.update(renderer, XMMatrixScaling(1000.0f, 1000.0f, 1000.0f) * worldMatrix);

	// Set shader to render mesh with
	this->shader.set(); 
	// Render mesh
	this->mesh.draw();
}

CubeMap& Skybox::getCubeMap()
{
	return this->skyCubeMap;
}

const XMMATRIX& Skybox::getWorldMatrix()const {
	return this->mesh.getWorldMatrix();
}

const XMFLOAT3& Skybox::getSunDir() const
{
	return this->sunDir;
}



