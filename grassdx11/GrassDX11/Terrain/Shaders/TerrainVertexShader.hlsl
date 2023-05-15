#define TERRAIN_CHUNK_WIDTH 64
#define TERRAIN_CHUNK_HEIGHT 64
#define TERRAIN_CHUNK_COUNT_WIDTH 1024 / TERRAIN_CHUNK_WIDTH
#define TERRAIN_CHUNK_COUNT_HEIGHT 1024 / TERRAIN_CHUNK_HEIGHT

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

SamplerState SampleTypeNoMips : register(s0);

Texture2D HM : register(t0);

struct VS_INPUT
{
    float4 position : POSITION;
    uint instanceId : SV_InstanceID;
};

struct HS_INPUT
{
    float4 position : POSITION;
    float3 normal : NORMAL;
    float3 tangent: TANGENT;
    float3 bitangent : BITANGENT;
    float2 tex : TEXCOORD;
    uint instanceId : INST_ID;
};

HS_INPUT main(VS_INPUT input)
{
    HS_INPUT output;
    unsigned int idx = objectIDs[input.instanceId].x;
    output.instanceId = idx;

    output.position = mul(float4(input.position.xyz, 1.0), geomBuffer[idx].worldMatrix);
    output.tex = float2(1.0f * (output.position.x + 512) / (TERRAIN_CHUNK_WIDTH * TERRAIN_CHUNK_COUNT_WIDTH), (output.position.z + 512) / (TERRAIN_CHUNK_HEIGHT * TERRAIN_CHUNK_COUNT_HEIGHT));
    output.position.y += HM.SampleLevel(SampleTypeNoMips, output.tex, 0.0f).x * 100.0;
    int H, W, dummy;
    HM.GetDimensions(0, H, W, dummy);
    float dX = 1.0f / W;
    float dZ = 1.0f / H;

    output.tangent = float3(2 * dX, 0, 0);
    output.tangent.y += 
        HM.SampleLevel(SampleTypeNoMips, float2(output.tex.x + dX, output.tex.y), 0.0f).x - HM.SampleLevel(SampleTypeNoMips, float2(output.tex.x - dX, output.tex.y), 0.0f).x;

    output.bitangent = float3(0, 0, 2 * dZ);
    output.bitangent.y += HM.SampleLevel(SampleTypeNoMips, float2(output.tex.x, output.tex.y + dZ), 0.0f).x - 
        HM.SampleLevel(SampleTypeNoMips, float2(output.tex.x, output.tex.y - dZ), 0.0f).x;
    output.tangent = normalize(output.tangent);
    output.bitangent = normalize(output.bitangent);
    output.normal = cross(output.bitangent, output.tangent);

    return output;
}
