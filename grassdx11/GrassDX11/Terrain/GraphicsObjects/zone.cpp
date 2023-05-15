#include "zone.h"

// Function to initialize user interface, camera, position and grid
bool Zone::Initialize(ID3D11Device* device, ID3D11DeviceContext* context, float screenDepth, float terrainRadius, float terrainHeight) {
    m_Device = device;
    m_Context = context;

    m_terrainRadius = terrainRadius;
    m_terrainHeight = terrainHeight;

    // Create the frustum object.
    m_Frustum = new Frustum;
    if (!m_Frustum) {
        return false;
    }

    // Initialize the frustum object.
    m_Frustum->Initialize(screenDepth);

    // Create the terrain shader.
    m_terrainShader = new TerrainShader();
    if (!m_terrainShader) {
        return false;
    }

    bool result;
    // Initialize the terrain shader.
    result = m_terrainShader->Initialize(device);
    if (!result) {
        return false;
    }
    // Load textures into the texture array.
    m_textureArray.reserve(32);
    TextureTerrain tmp;

    result = tmp.Initialize(device, context, L"Terrain/Engine/Textures/data/grass_diffuse.dds", TextureTerrain::DDS, true);
    if (!result) {
        return false;
    }
    m_textureArray.push_back(tmp);

    result = tmp.Initialize(device, context, L"Terrain/Engine/Textures/data/grass_normal.dds", TextureTerrain::DDS);
    if (!result) {
        return false;
    }
    m_textureArray.push_back(tmp);

    result = tmp.Initialize(device, context, L"Terrain/Engine/Textures/data/grass_rough.dds", TextureTerrain::DDS);
    if (!result) {
        return false;
    }
    m_textureArray.push_back(tmp);

    result = tmp.Initialize(device, context, L"Terrain/Engine/Textures/data/grass_ao.dds", TextureTerrain::DDS);
    if (!result) {
        return false;
    }
    m_textureArray.push_back(tmp);

    result = tmp.Initialize(device, context, L"Terrain/Engine/Textures/data/grass_diffuse2.dds", TextureTerrain::DDS, true);
    if (!result) {
        return false;
    }
    m_textureArray.push_back(tmp);

    result = tmp.Initialize(device, context, L"Terrain/Engine/Textures/data/grass_normal2.dds", TextureTerrain::DDS);
    if (!result) {
        return false;
    }
    m_textureArray.push_back(tmp);

    result = tmp.Initialize(device, context, L"Terrain/Engine/Textures/data/grass_rough2.dds", TextureTerrain::DDS);
    if (!result) {
        return false;
    }
    m_textureArray.push_back(tmp);

    result = tmp.Initialize(device, context, L"Terrain/Engine/Textures/data/grass_ao2.dds", TextureTerrain::DDS);
    if (!result) {
        return false;
    }
    m_textureArray.push_back(tmp);

    result = tmp.Initialize(device, context, L"Terrain/Engine/Textures/data/rock_diffuse.dds", TextureTerrain::DDS, true);
    if (!result) {
        return false;
    }
    m_textureArray.push_back(tmp);

    result = tmp.Initialize(device, context, L"Terrain/Engine/Textures/data/rock_normal.dds", TextureTerrain::DDS);
    if (!result) {
        return false;
    }
    m_textureArray.push_back(tmp);

    result = tmp.Initialize(device, context, L"Terrain/Engine/Textures/data/rock_rough.dds", TextureTerrain::DDS);
    if (!result) {
        return false;
    }
    m_textureArray.push_back(tmp);

    result = tmp.Initialize(device, context, L"Terrain/Engine/Textures/data/rock_ao.dds", TextureTerrain::DDS);
    if (!result) {
        return false;
    }
    m_textureArray.push_back(tmp);

    result = tmp.Initialize(device, context, L"Terrain/Engine/Textures/data/slope_diffuse.dds", TextureTerrain::DDS, true);
    if (!result) {
        return false;
    }
    m_textureArray.push_back(tmp);

    result = tmp.Initialize(device, context, L"Terrain/Engine/Textures/data/slope_normal.dds", TextureTerrain::DDS);
    if (!result) {
        return false;
    }
    m_textureArray.push_back(tmp);

    result = tmp.Initialize(device, context, L"Terrain/Engine/Textures/data/slope_rough.dds", TextureTerrain::DDS);
    if (!result) {
        return false;
    }
    m_textureArray.push_back(tmp);

    result = tmp.Initialize(device, context, L"Terrain/Engine/Textures/data/slope_ao.dds", TextureTerrain::DDS);
    if (!result) {
        return false;
    }
    m_textureArray.push_back(tmp);

    result = tmp.Initialize(device, context, L"Terrain/Engine/Textures/data/snow_diffuse.dds", TextureTerrain::DDS, true);
    if (!result) {
        return false;
    }
    m_textureArray.push_back(tmp);

    result = tmp.Initialize(device, context, L"Terrain/Engine/Textures/data/snow_normal.dds", TextureTerrain::DDS);
    if (!result) {
        return false;
    }
    m_textureArray.push_back(tmp);

    result = tmp.Initialize(device, context, L"Terrain/Engine/Textures/data/snow_rough.dds", TextureTerrain::DDS);
    if (!result) {
        return false;
    }
    m_textureArray.push_back(tmp);

    result = tmp.Initialize(device, context, L"Terrain/Engine/Textures/data/snow_ao.dds", TextureTerrain::DDS);
    if (!result) {
        return false;
    }
    m_textureArray.push_back(tmp);

    result = tmp.Initialize(device, context, L"Terrain/Engine/Textures/data/detailNormalMap.dds", TextureTerrain::DDS);
    if (!result) {
        return false;
    }
    m_textureArray.push_back(tmp);

    result = tmp.Initialize(device, context, L"Terrain/Engine/Textures/data/noise.dds", TextureTerrain::DDS);
    if (!result) {
        return false;
    }
    m_textureArray.push_back(tmp);

    result = tmp.Initialize(device, context, L"Terrain/Engine/Textures/data/HM.r32", TextureTerrain::R32);
    if (!result) {
        return false;
    }
    m_textureArray.push_back(tmp);

    // Create the terrain object.
    m_Terrain = new Terrain;
    if (!m_Terrain) {
        return false;
    }
    // Initialize the terrain object.
    result = m_Terrain->Initialize(device);
    if (!result) {
        return false;
    }

    m_HeightData = new TerrainHeightData();
    if (!m_HeightData) {
        return false;
    }

    TexMetadata info;
    ScratchImage image;
    /* Calculating terrain heights */
    HRESULT hr = LoadFromDDSFile(L"resources/HM.dds", DDS_FLAGS_NONE, &info, image);
    if (hr != S_OK)
        return false;
    /* Calculating terrain heights */
    m_HeightData->ConvertFrom(&image, &info);
    m_HeightData->CalcNormals(terrainHeight, 1);

    return true;
}
// Function to clear all stuff that was created in initialize function
void Zone::Shutdown() {
    // Release the terrain object.
    if (m_Terrain) {
        m_Terrain->Shutdown();
        delete m_Terrain;
        m_Terrain = nullptr;
    }

    if (m_Frustum) {
        delete m_Frustum;
        m_Frustum = nullptr;
    }

    if (m_terrainShader) {
        m_terrainShader->Shutdown();
        m_terrainShader = nullptr;
    }

    for (auto& f : m_textureArray) {
        f.Shutdown();
    }

    if (m_HeightData) {
        delete m_HeightData;
    }
}

// Render function
bool Zone::Render(XMMATRIX viewMatrix, XMMATRIX projectionMatrix, XMFLOAT3 cameraPos, XMFLOAT3 lightDir) {
    XMMATRIX worldMatrix = XMMatrixIdentity();
    m_Frustum->ConstructFrustum(viewMatrix, projectionMatrix);

    //m_Terrain->Render(Direct3D->GetDeviceContext());
    ID3D11ShaderResourceView* textures[] = { m_textureArray[0].GetTexture(), m_textureArray[1].GetTexture(), m_textureArray[2].GetTexture(), m_textureArray[3].GetTexture(), // Grass material
                                             m_textureArray[4].GetTexture(), m_textureArray[5].GetTexture(), m_textureArray[6].GetTexture(), m_textureArray[7].GetTexture(), // Grass 2 material
                                             m_textureArray[8].GetTexture(), m_textureArray[9].GetTexture(), m_textureArray[10].GetTexture(), m_textureArray[11].GetTexture(), // Rock material
                                             m_textureArray[12].GetTexture(), m_textureArray[13].GetTexture(), m_textureArray[14].GetTexture(), m_textureArray[15].GetTexture(), // Slope material
                                             m_textureArray[16].GetTexture(), m_textureArray[17].GetTexture(), m_textureArray[18].GetTexture(), m_textureArray[19].GetTexture(), // Snow material
                                             m_textureArray[20].GetTexture(),m_textureArray[21].GetTexture(), m_textureArray[22].GetTexture() }; // Height maps

    m_Terrain->Render(m_Context);

    //bool result = m_terrainShader->Render(context, m_Frustum->GetPlanes(), worldMatrix, viewMatrix,
    //                projectionMatrix, cameraPos, lightDir, textures, false);

    //if (!result) {
    //    return false;
    //}
    //Direct3D->TurnDepthPrePass();
    bool result = m_terrainShader->Render(m_Context, m_Frustum->GetPlanes(), worldMatrix, viewMatrix,
        projectionMatrix, cameraPos, lightDir, textures, true);
    //Direct3D->TurnZBufferOn();

    if (!result) {
        return false;
    }

    return true;
}
