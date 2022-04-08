cbuffer MatrixBuffer
{
    matrix projectionMatrix;
    matrix viewMatrix;
    matrix worldMatrix;
};

struct VS_INPUT
{
    float3 position : POSITION;
};

struct PS_INPUT
{
    float4 position : SV_POSITION;
    float2 xy : TEXCOORD0;
};

PS_INPUT main(VS_INPUT input)
{
    PS_INPUT output;

    output.position = mul(float4(input.position, 1.0), worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);

    output.xy = input.position.xy;

    return output;
}