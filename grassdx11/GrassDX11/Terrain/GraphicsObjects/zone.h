//--------------------------------------------------------------------------------------
// Zone class handles all the camera movment and terrain grid rendering
//--------------------------------------------------------------------------------------

#ifndef _ZONE_H_
#define _ZONE_H_

#include "frustum.h"
#include "terrain.h"
#include "../Terrain/Engine/Textures/TextureTerrain.h"
#include "../Terrain/Shaders/terrainShader.h"
#include "../Terrain/GraphicsObjects/terrainHeightData.h"
#include <vector>

class Zone {
  public:
    // Function to initialize user interface, camera, position and grid
    bool Initialize(ID3D11Device* device, ID3D11DeviceContext* context, float screenDepth, float terrainRadius, float terrainHeight);
    // Render function
    bool Render(XMMATRIX viewMatrix, XMMATRIX projectionMatrix, XMFLOAT3 cameraPos, XMFLOAT3 lightDir);
    // Function to clear all stuff that was created in initialize function
    void Shutdown();
    // Function to return HM
    ID3D11ShaderResourceView* HeightMapSRV() { return m_textureArray[22].GetTexture(); };
    TerrainHeightData* HeightDataPtr(void) { return m_HeightData; };
  private:
    TerrainHeightData* m_HeightData = nullptr;
    ID3D11Device* m_Device = nullptr;
    ID3D11DeviceContext *m_Context = nullptr;
    float m_terrainRadius = 0.0f;
    float m_terrainHeight = 0.0f;
    TerrainShader* m_terrainShader = nullptr;
    std::vector<TextureTerrain> m_textureArray;
    Terrain* m_Terrain = nullptr;
    Frustum* m_Frustum = nullptr;
};

#endif
