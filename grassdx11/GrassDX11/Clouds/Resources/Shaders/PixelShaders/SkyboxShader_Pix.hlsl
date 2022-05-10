
struct Input {
	float4 position : SV_POSITION;
	float3 dir : TEXCOORD;
};

TextureCube cubeMapTexture : register(t0);
SamplerState sampleType : register(s0);

SamplerState MeshTextureSampler
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

float4 main(Input input) : SV_TARGET {
	 
	float3 viewDir = normalize(input.dir);

	// Sample sky box
    float3 col = cubeMapTexture.Sample(MeshTextureSampler, viewDir).rgb;

	//return float4(col, 0.1f);
	return float4(col, 1.0f);
}