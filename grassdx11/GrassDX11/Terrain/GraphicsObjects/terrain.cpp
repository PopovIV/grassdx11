#include "terrain.h"
#include <cstdlib>

// Function to initialize the vertex and index buffers
inline int div_ceil(int numerator, int denominator)
{
    std::div_t res = std::div(numerator, denominator);
    return res.rem ? (res.quot + 1) : res.quot;
}

bool Terrain::Initialize(ID3D11Device* device) {
    //(x + y - 1) / y
    m_heightMap = new HeightMapType[div_ceil((TERRAIN_CHUNK_WIDTH + 1) * (TERRAIN_CHUNK_HEIGHT + 1), TERRAIN_CHUNK_OFFSET)];
    if (!m_heightMap) {
        return false;
    }

    SetTerrainCoordinates();

    // Now build the 3D model of the terrain.
    bool result = InitializeBuffers(device);
    if (!result) {
        return false;
    }

    ShutdownTerrainModel();

    return true;
}

// Function to clear all data from vertex and index buffers
void Terrain::Shutdown() {
    // Shutdown buffers
    ShutdownBuffers();
    // Release the terrain model.
    ShutdownTerrainModel();
    // Release the height map.
    ShutdownHeightMap();
}

void Terrain::SetTerrainCoordinates() {
    // Loop through all the elements in the height map array and adjust their coordinates correctly.
    int index = 0;
    for (int j = 0; j < div_ceil(TERRAIN_CHUNK_HEIGHT + 1, TERRAIN_CHUNK_OFFSET); j++) {
        for (int i = 0; i < div_ceil(TERRAIN_CHUNK_WIDTH + 1, TERRAIN_CHUNK_OFFSET); i++) {

            // Set the X and Z coordinates.
            m_heightMap[index].x = (float)i * TERRAIN_CHUNK_OFFSET;
            m_heightMap[index].z = (float)j * TERRAIN_CHUNK_OFFSET;

            // Move the terrain depth into the positive range.  For example from (0, -256) to (256, 0).
            //m_heightMap[index].z += (float)(TERRAIN_CHUNK_HEIGHT - 1);

            index++;
        }
    }
}

void Terrain::ShutdownHeightMap() {
    // Release the height map array.
    if (m_heightMap) {
        delete[] m_heightMap;
        m_heightMap = nullptr;
    }
}

void Terrain::ShutdownTerrainModel() {
    // Release the terrain model data.
    if (m_terrainModel) {
        delete[] m_terrainModel;
        m_terrainModel = nullptr;
    }
}

// Function to initialize terrain vertex and index buffer
bool Terrain::InitializeBuffers(ID3D11Device* device) {
    HRESULT result = S_OK;
    int divChunkWidth = div_ceil(TERRAIN_CHUNK_WIDTH + 1, TERRAIN_CHUNK_OFFSET);
    int divChunkHeight = div_ceil(TERRAIN_CHUNK_HEIGHT + 1, TERRAIN_CHUNK_OFFSET);

    // Calculate the number of vertices in the terrain.
    m_vertexCount = divChunkWidth * divChunkHeight;
    // Set the index count to the same as the vertex count.
    m_indexCount = m_vertexCount * 6;

    // Create the vertex array.
    VertexType* vertices;
    vertices = new VertexType[m_vertexCount];
    if (!vertices) {
        return false;
    }

    // Create the index array.
    unsigned long* indices;
    indices = new unsigned long[m_indexCount];
    if (!indices) {
        return false;
    }

    // Load the vertex array and index array with 3D terrain model data.
    int indexVertex = 0;
    int indexIndex = 0;
    for (int j = 0; j < divChunkHeight; j++) {
        for (int i = 0; i < divChunkWidth; i++) {
            if (i == divChunkWidth - 1 || j == divChunkHeight - 1) {
                int index = (divChunkWidth * j) + i;
                vertices[indexVertex++].position = XMFLOAT3(m_heightMap[index].x, 0.0f, m_heightMap[index].z);
                continue;
            }
            // Get the indexes to the four points of the quad.
            int index1 = (divChunkWidth * j) + i;          // Left bottom.
            int index2 = (divChunkWidth * (j + 1)) + i;      // Left up.
            int index3 = (divChunkWidth * (j + 1)) + (i + 1);  // Right up.
            int index4 = (divChunkWidth * j) + (i + 1);      // Right bottom.

            vertices[indexVertex++].position = XMFLOAT3(m_heightMap[index1].x, 0.0f, m_heightMap[index1].z);
            indices[indexIndex++] = index2;
            indices[indexIndex++] = index3;
            indices[indexIndex++] = index1;
            indices[indexIndex++] = index1;
            indices[indexIndex++] = index3;
            indices[indexIndex++] = index4;
        }
    }

    D3D11_BUFFER_DESC vertexBufferDesc;
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.MiscFlags = 0;
    vertexBufferDesc.StructureByteStride = 0;

    // Give the subresource structure a pointer to the vertex data.
    D3D11_SUBRESOURCE_DATA vertexData;
    vertexData.pSysMem = vertices;
    vertexData.SysMemPitch = 0;
    vertexData.SysMemSlicePitch = 0;

    // Now create the vertex buffer.
    result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
    if (FAILED(result)) {
        return false;
    }

    D3D11_BUFFER_DESC indexBufferDesc;
    // Set up the description of the static index buffer.
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;
    indexBufferDesc.StructureByteStride = 0;

    // Give the subresource structure a pointer to the index data.
    D3D11_SUBRESOURCE_DATA indexData;
    indexData.pSysMem = indices;
    indexData.SysMemPitch = 0;
    indexData.SysMemSlicePitch = 0;

    // Create the index buffer.
    result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
    if (FAILED(result)) {
        return false;
    }

    // Release the arrays now that the buffers have been created and loaded.
    delete[] vertices;
    vertices = 0;

    delete[] indices;
    indices = 0;

    return true;
}

// Function to shutdown buffers
void Terrain::ShutdownBuffers() {
    // Release the index buffer.
    if (m_indexBuffer) {
        m_indexBuffer->Release();
        m_indexBuffer = nullptr;
    }
    // Release the vertex buffer.
    if (m_vertexBuffer) {
        m_vertexBuffer->Release();
        m_vertexBuffer = nullptr;
    }
}

// Function to render buffers
void Terrain::RenderBuffers(ID3D11DeviceContext* deviceContext) {
    // Set vertex buffer stride and offset.
    unsigned int stride = sizeof(VertexType);
    unsigned int offset = 0;

    // Set the vertex buffer to active in the input assembler so it can be rendered.
    deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

    // Set the index buffer to active in the input assembler so it can be rendered.
    deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

    // Set the type of primitive that should be rendered from this vertex buffer, in this case lines.
    deviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST);
}
