#pragma once
#include "../../includes.h"
#include "../Terrain/Engine/Utility/stringConverter.h"
#include <DirectXTex.h>


struct TerrainHeightData
{
    float* pData;
    UINT          uHeight;
    UINT          uWidth;
    float         fHeight;
    float         fWidth;

    bool     ConvertFrom(const wchar_t* filename);
    float    GetHeight(float a_fX, float a_fY) const;

    TerrainHeightData(void);
    ~TerrainHeightData(void);
};
