#ifndef _LOD_H_
#define _LOD_H_

float g_fDissolve = 0.15;

inline float4 CalcTerrNormal(float2 a_vTexCoord)
{
    int H, W, dummy;
    g_txHeightMap.GetDimensions(0, H, W, dummy);
    float dX = 1.0f / W;
    float dZ = 1.0f / H;

    float3 tangent = float3(2 * dX, 0, 0);
    tangent.y += g_txHeightMap.SampleLevel(g_samLinear, float2(a_vTexCoord.x + dX, a_vTexCoord.y), 0.0f).x - g_txHeightMap.SampleLevel(g_samLinear, float2(a_vTexCoord.x - dX, a_vTexCoord.y), 0.0f).x;

    float3 bitangent = float3(0, 0, 2 * dZ);
    bitangent.y += g_txHeightMap.SampleLevel(g_samLinear, float2(a_vTexCoord.x, a_vTexCoord.y + dZ), 0.0f).x - g_txHeightMap.SampleLevel(g_samLinear, float2(a_vTexCoord.x, a_vTexCoord.y - dZ), 0.0f).x;
    tangent = normalize(tangent);
    bitangent = normalize(bitangent);
    float3 normal = cross(bitangent, tangent);

    return float4(normal, 0.0);
}

inline void ScreenClip(float4 a_vWorldPt1, float4 a_vWorldPt2, inout float a_fTransparency)
{
    float4 vScreenPos[2];
    vScreenPos[0] = mul(a_vWorldPt1, g_mViewProj);
    vScreenPos[1] = mul(a_vWorldPt2, g_mViewProj);
    vScreenPos[0].xyz = vScreenPos[0].xyz / vScreenPos[0].w;
    vScreenPos[1].xyz = vScreenPos[1].xyz / vScreenPos[1].w;
    float4 vScreenClip1 = float4(-1.0, -1.0, 0.0, 0.0);
    float4 vScreenClip2 = float4(1.0, 1.0, 1.0, 0.0);
    if ( any( step(vScreenPos[0], vScreenClip1) ) && any( step(vScreenPos[1], vScreenClip1) ) )
    {
        a_fTransparency = 0.0;
    }
    
    if ( any( step(vScreenClip2.xyz, vScreenPos[0].xyz) ) && any( step(vScreenClip2.xyz, vScreenPos[1].xyz) ) )
    {
        a_fTransparency = 0.0;
    }
}

inline float LodAlphaOffset(float4 a_vWorldPt)
{
	float3 vViewPos = mul(a_vWorldPt, g_mView).xyz;
    float fBladeDist = length(vViewPos);
	if (fBladeDist < 0.1) 
        return 0.0;

    float fLerpCoef1 = (fBladeDist+0.1) /g_fGrassRadius;
    fLerpCoef1 *= fLerpCoef1;
   
    float2 vTexCoord    = ((a_vWorldPt.xz / g_fTerrRadius) * 0.5 + 0.5 );
    float3 vNormal = CalcTerrNormal(vTexCoord).xyz;
	float3 vV = g_mInvCamView[3].xyz - a_vWorldPt.xyz; 
	float tmp = 0.43; 
	if (vV.y<0.0) tmp += 0.1 * vV.y/(5.0 + abs(vV.y));
	vV = normalize(vV);
	float fdot = dot(vV, vNormal);
	tmp = tmp - fdot;
	if (fdot<0) fdot*=-0.4;
	float t = 1.f - fdot;
	float h = g_mInvCamView[3].y;

    if (h < 250.0f)
        h = 0.0f;
    else
        h = (h - 250.0f) / 400.0f;

	if ((a_vWorldPt.y > 6.0)&&(t > 0.92)) 
        return (0.2 + h);
	else 
        return (tmp *(1.0+3.0*fLerpCoef1)+h);
}

/*
 * returns: x - Alpha, y - segwidth, z - texIndex, w - right x-TexCoord
 */
inline float4 CalcTransparency( float a_fBaseAlpha, float4 a_vFirstPt, out float a_fDissolve, out uint a_uNumVertices )
{
    float2 vUV = (a_vFirstPt.xz / g_fTerrRadius) * 0.5 + 0.5;
    float3 normal =  CalcTerrNormal(vUV);
    float slope = 1.0f - normal.y;

    if (a_vFirstPt.y > 250 || slope > 0.6) {
        a_fDissolve = 0.0;
        a_uNumVertices = 0;
        return float4(0, 0, 0, 0);
    }

	//if (GetSeatingInfo(vUV) < 0.5) {
	//	a_fDissolve = 0.0;
    //    a_uNumVertices = 0;
    //    return float4(0, 0, 0, 0);
    //}

    float fDist = length(a_vFirstPt.xyz - g_mInvCamView[3].xyz);
	a_uNumVertices = 7;

    if (fDist > 60.0)
       a_uNumVertices = 4;
	if (fDist > 75.0)
	   a_uNumVertices = 3;
    if (fDist > 100.0)
       a_uNumVertices = 2;

    if (fDist > 0.5)
       a_uNumVertices = 4;

    float fAlphaOffset = LodAlphaOffset(a_vFirstPt);
    float fAlpha = a_fBaseAlpha - fAlphaOffset;
    a_fDissolve = 1.0;
    if (fAlpha < g_fDissolve)
    {
		a_fDissolve = fAlpha / g_fDissolve;		
    }
//      if (fDist > 40.0)
//		 return float4(fAlpha-0.33, 12.0, 1, 1.0);
//	  else
	     return float4(fAlpha, 1.0, 0.0, 1.0);
}

inline float3 CalcWind( float3 a_vPos, int a_iSegmentIndex )
{
    float2 vTexCoord = ((a_vPos.xz / g_fTerrRadius) * 0.5 + 0.5 );
    return g_txAirTex.SampleLevel(g_samLinear, float3(vTexCoord, a_iSegmentIndex), 0).rgb;
}

#endif

