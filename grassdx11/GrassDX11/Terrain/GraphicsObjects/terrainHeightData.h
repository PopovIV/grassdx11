#pragma once
#include "../../includes.h"
#include "../Terrain/Engine/Utility/stringConverter.h"
#include <DirectXTex.h>


struct TerrainHeightData
{
    float* pData;
    XMFLOAT3* pNormals;
    UINT          uHeight;
    UINT          uWidth;
    float         fHeight;
    float         fWidth;

    bool     ConvertFrom(const wchar_t* filename);
    void CalcNormals(float a_fHeightScale, float a_fDistBtwVertices);
    float    GetHeight(float a_fX, float a_fY) const;
    XMFLOAT3  GetNormal(float a_fX, float a_fY) const;

    TerrainHeightData(void);
    ~TerrainHeightData(void);
};
