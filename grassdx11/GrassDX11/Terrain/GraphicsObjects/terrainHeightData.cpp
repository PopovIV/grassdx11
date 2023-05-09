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
    a_fY = 1.0 - a_fY * 4;
    float fX = a_fX * (float)(uWidth - 1) * 4;
    float fY = a_fY * (float)(uHeight - 1);
    UINT uLX = (UINT)floor(fX);
    UINT uHX = uLX + 1;
    UINT uLY = (UINT)floor(fY);
    UINT uHY = uLY + 1;
    float fFracX = (fX)-floor(fX);
    float fFracY = (fY)-floor(fY);
    uLX = std::min(std::max(0u,uLX), uWidth - 1);
    uLY = std::min(std::max(0u, uLY), uHeight - 1);
    uHX = std::min(std::max(0u, uHX), uWidth - 1);
    uHY = std::min(std::max(0u, uHY), uHeight - 1);
    float fLL = pData[uWidth * uLY + uLX];
    float fHL = pData[uWidth * uHY + uLX];
    float fLR = pData[uWidth * uLY + uHX];
    float fHR = pData[uWidth * uHY + uHX];
    return ((1.0f - fFracX) * fLL + fFracX * fLR) * (1.0f - fFracY) +
        fFracY * ((1.0f - fFracX) * fHL + fFracX * fHR);
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
    uWidth = sqrt(Size);
    uHeight = Size / uWidth;
    fWidth = uWidth;
    fHeight = uHeight;
    return true;
}
