#include "terrainHeightData.h"


TerrainHeightData::TerrainHeightData(void)
{
    pData = NULL;
}

TerrainHeightData::~TerrainHeightData(void)
{
    if (pData)
        delete[] pData;

}

float TerrainHeightData::GetHeight(float a_fX, float a_fY) const
{
    float fX = a_fX * (float)(uWidth - 1);
    float fY = a_fY * (float)(uHeight - 1);
    UINT uLX = (UINT)floor(fX);
    UINT uHX = uLX + 1;
    UINT uLY = (UINT)floor(fY);
    UINT uHY = uLY + 1;
    float fFracX = (fX)-floor(fX);
    float fFracY = (fY)-floor(fY);
    if (uHX > uWidth - 1)
        uHX = uWidth - 1;
    if (uHY > uHeight - 1)
        uHY = uHeight - 1;
    float fLL = pData[uWidth * uLY + uLX];
    float fHL = pData[uWidth * uHY + uLX];
    float fLR = pData[uWidth * uLY + uHX];
    float fHR = pData[uWidth * uHY + uHX];
    return ((1.0f - fFracX) * fLL + fFracX * fLR) * (1.0f - fFracY) +
        fFracY * ((1.0f - fFracX) * fHL + fFracX * fHR);
}


float TerrainHeightData::GetHeight2x2(float a_fX, float a_fY) const
{
    float dU = 1.0f / (fWidth);
    float dV = 1.0f / (fWidth);
    float h0 = GetHeight(a_fX, a_fY);
    float h1 = GetHeight(a_fX + dU, a_fY + dV);
    float h2 = GetHeight(a_fX, a_fY + dV);
    float h3 = GetHeight(a_fX + dU, a_fY);
    return (h0 + h1 + h2 + h3) * 0.25f;
}

bool TerrainHeightData::ConvertFrom(const wchar_t* filename)
{
    FILE* F;
    size_t Size = 0;
    fopen_s(&F, StringConverter::wstr2str(filename).c_str(), "rb");
    if (F == NULL)
        return false;
    fseek(F, 0, SEEK_END);
    Size = ftell(F) / sizeof(float);
    rewind(F);
    pData = new float[Size];
    fread_s(pData, Size * sizeof(float), sizeof(float), Size, F);
    fclose(F);
    fWidth = 4096;
    fHeight = 4096;
    uWidth = 4096;
    uHeight = 4096;
    return true;
}
