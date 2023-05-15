#include "defines.h"

struct GeomBuffer {
    matrix worldMatrix;
};

cbuffer GeomBufferInst : register (b0)
{
    GeomBuffer geomBuffer[(TERRAIN_CHUNK_COUNT_WIDTH + 1) * (TERRAIN_CHUNK_COUNT_HEIGHT + 1)];
};

cbuffer SceneMatrixBuffer : register (b1)
{
    matrix viewProjectionMatrix;
    float4 planes[6];
    float3 cameraPos;
};

cbuffer IndexBuffer : register(b2)
{
    uint4 objectIDs[(TERRAIN_CHUNK_COUNT_WIDTH + 1) * (TERRAIN_CHUNK_COUNT_HEIGHT + 1)];
}