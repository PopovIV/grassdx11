#include "terrainHeightData.h"


TerrainHeightData::TerrainHeightData(void)
{
    pData = NULL;
    pNormals = NULL;
}

TerrainHeightData::~TerrainHeightData(void)
{
    if (pData)
        delete[] pData;
    if (pNormals)
        delete[] pNormals;

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

XMFLOAT3 TerrainHeightData::GetNormal(float a_fX, float a_fY) const
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
   XMFLOAT3 xmf_fLL = pNormals[uWidth * uLY + uLX];
   XMFLOAT3 xmf_fHL = pNormals[uWidth * uHY + uLX];
   XMFLOAT3 xmf_fLR = pNormals[uWidth * uLY + uHX];
   XMFLOAT3 xmf_fHR = pNormals[uWidth * uHY + uHX];
   XMVECTOR fLL, fHL, fLR, fHR;
   fLL = XMLoadFloat3(&xmf_fLL);
   fHL = XMLoadFloat3(&xmf_fHL);
   fLR = XMLoadFloat3(&xmf_fLR);
   fHR = XMLoadFloat3(&xmf_fHR);
   XMVECTOR normal = ((1.0f - fFracX) * fLL + fFracX * fLR) * (1.0f - fFracY) +
      fFracY * ((1.0f - fFracX) * fHL + fFracX * fHR);
   XMFLOAT3 xmN;
   XMStoreFloat3(&xmN, normal);
   return xmN;
}

void TerrainHeightData::ConvertFrom(const ScratchImage* a_image, const TexMetadata* a_info)
{
   UCHAR* pTexels = (UCHAR*)a_image->GetPixels();
   if (pData)
      return;
   pData = new float[a_info->height * a_info->width];
   pNormals = new XMFLOAT3[a_info->height * a_info->width];
   uHeight = a_info->height;
   uWidth = a_info->width;
   fHeight = (float)uHeight;
   fWidth = (float)uWidth;
   int size = a_image->GetPixelsSize();
   for (UINT row = 0; row < a_info->height; row++)
   {
      UINT rowStart = row * a_image->GetImage(0, 0, 0)->rowPitch;
      for (UINT col = 0; col < a_info->width; col++)
      {
         UINT colStart = col * 4;//RGBA
         pData[row * a_info->width + col] = ((float)pTexels[rowStart + colStart + 0]) / 255.0f;
      }
   }
}
void TerrainHeightData::CalcNormals(float a_fHeightScale, float a_fDistBtwVertices)
{
   enum DIR
   {
      LEFT = 0,
      RIGHT,
      UP,
      DOWN
   };
   XMFLOAT3 vToVertex[4]; //vector from current vertex to another one
   vToVertex[LEFT].x = -a_fDistBtwVertices;
   vToVertex[LEFT].z = 0.0f;
   vToVertex[RIGHT].x = a_fDistBtwVertices;
   vToVertex[RIGHT].z = 0.0f;
   vToVertex[UP].x = 0.0f;
   vToVertex[UP].z = a_fDistBtwVertices;
   vToVertex[DOWN].x = 0.0f;
   vToVertex[DOWN].z = -a_fDistBtwVertices;
   for (UINT row = 0; row < uHeight; row++)
   {
      for (UINT col = 0; col < uWidth; col++)
      {
         if (col == 0 || row == 0 || col == uWidth - 1 || row == uHeight - 1)
         {
            pNormals[row * uWidth + col].x = 0.0f;
            pNormals[row * uWidth + col].y = 1.0f;
            pNormals[row * uWidth + col].z = 0.0f;
            continue;
         }
         float fH = pData[row * uWidth + col];
         vToVertex[LEFT].y = pData[row * uWidth + col - 1] * a_fHeightScale - fH * a_fHeightScale;
         vToVertex[RIGHT].y = pData[row * uWidth + col + 1] * a_fHeightScale - fH * a_fHeightScale;
         vToVertex[DOWN].y = pData[row * uWidth + col - uWidth] * a_fHeightScale - fH * a_fHeightScale;
         vToVertex[UP].y = pData[row * uWidth + col + uWidth] * a_fHeightScale - fH * a_fHeightScale;
         pNormals[row * uWidth + col].x =
            pNormals[row * uWidth + col].y =
            pNormals[row * uWidth + col].z = 0.0f;
         XMVECTOR down = XMLoadFloat3(&vToVertex[DOWN]);
         XMVECTOR up = XMLoadFloat3(&vToVertex[UP]);
         XMVECTOR left = XMLoadFloat3(&vToVertex[LEFT]);
         XMVECTOR right = XMLoadFloat3(&vToVertex[RIGHT]);
         auto normalCalc = [](XMVECTOR& vec1, XMVECTOR& vec2, XMFLOAT3* xmf3Normal)
         {
            XMVECTOR vCrossProduct = XMVector3Cross(vec1, vec2);
            vCrossProduct = XMVector3Normalize(vCrossProduct);
            XMVECTOR normal = XMLoadFloat3(xmf3Normal);
            normal += vCrossProduct;
            XMStoreFloat3(xmf3Normal, normal);
         };
         normalCalc(down, left, &pNormals[row * uWidth + col]);
         normalCalc(right, down, &pNormals[row * uWidth + col]);
         normalCalc(up, right, &pNormals[row * uWidth + col]);
         normalCalc(left, up, &pNormals[row * uWidth + col]);
         XMVECTOR normal = XMLoadFloat3(&pNormals[row * uWidth + col]);
         normal = XMVector3Normalize(normal);
         XMStoreFloat3(&pNormals[row * uWidth + col], normal);
      }
   }
}
