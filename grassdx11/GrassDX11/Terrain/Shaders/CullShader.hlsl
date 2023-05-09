#define TERRAIN_CHUNK_WIDTH 32
#define TERRAIN_CHUNK_HEIGHT 32
#define TERRAIN_CHUNK_COUNT_WIDTH 1024 / TERRAIN_CHUNK_WIDTH
#define TERRAIN_CHUNK_COUNT_HEIGHT 1024 / TERRAIN_CHUNK_HEIGHT

struct GeomBuffer {
    matrix worldMatrix;
};

cbuffer GeomBufferInst : register (b0)
{
    GeomBuffer geomBuffer[TERRAIN_CHUNK_COUNT_WIDTH * TERRAIN_CHUNK_COUNT_HEIGHT];
};

cbuffer SceneMatrixBuffer : register (b1)
{
    matrix viewProjectionMatrix;
    float4 planes[6];
    float3 cameraPos;
};

cbuffer IndexBuffer : register(b2)
{
    uint4 objectIDs[TERRAIN_CHUNK_COUNT_WIDTH * TERRAIN_CHUNK_COUNT_HEIGHT];
}

SamplerState SamplerType : register(s0);
Texture2D<float2> HM : register(t0);

RWStructuredBuffer<uint> indirectArgs : register(u0);
RWStructuredBuffer<uint4> objectsIds : register(u1);

bool IsBoxInside(in float4 planes[6], in float3 bbMin, in float3 bbMax) {
    for (int i = 0; i < 6; i++) {
        float3 norm = planes[i].xyz;
        float4 p = float4(
            norm.x < 0 ? bbMin.x : bbMax.x,
            norm.y < 0 ? bbMin.y : bbMax.y,
            norm.z < 0 ? bbMin.z : bbMax.z,
            1.0f
            );
        float s = dot(p, planes[i]);
        if (s < 0.0f) {
            return false;
        }
    }

    return true;
}

[numthreads(64, 1, 1)]
void main(uint3 globalThreadId : SV_DispatchThreadID)
{
    if (globalThreadId.x >= TERRAIN_CHUNK_COUNT_HEIGHT * TERRAIN_CHUNK_COUNT_WIDTH) {
        return;
    }
    float4 bbMin = float4(0, 0, 0, 1);
    float4 bbMax = float4(TERRAIN_CHUNK_WIDTH - 1, 0, TERRAIN_CHUNK_HEIGHT - 1, 1);
    bbMin = mul(bbMin, geomBuffer[globalThreadId.x].worldMatrix);
    bbMax = mul(bbMax, geomBuffer[globalThreadId.x].worldMatrix);

    float u = (1.0f * globalThreadId.x % TERRAIN_CHUNK_COUNT_WIDTH);
    float v = TERRAIN_CHUNK_COUNT_HEIGHT - (1.0f * globalThreadId.x % TERRAIN_CHUNK_COUNT_HEIGHT) - 1;
    //float2 texCoord = float2(u, v);

    float2 height = HM.Load(int3(u,v, 7));
    bbMin.y += height.r * 500.0f;
    bbMax.y += height.g * 500.0f;

    bbMin -= float4(1000.0f, 1000.0f, 1000.0f, 0.0f);
    bbMax += float4(1000.0f, 1000.0f, 1000.0f, 0.0f);

    if (IsBoxInside(planes, bbMin.xyz, bbMax.xyz)) {
        uint id = 0;
        InterlockedAdd(indirectArgs[1], 1, id);
        objectsIds[id] = uint4(globalThreadId.x, 0, 0, 0);
    }
}