#pragma once

#include "DXUT.h"
#include "DXUTcamera.h"
#include "../Terrain/GraphicsObjects/zone.h"
#include "Mesh.h"

class LandscapeCamera : public CFirstPersonCamera
{
public:
   LandscapeCamera (float a_fHeight, Zone* const a_pTerrain, float a_fHeightScale, float a_fGrassRadius)
      :
      m_fDefaultHeight(a_fHeight), m_pTerrain(a_pTerrain),
      m_fHeightScale(a_fHeightScale), m_fGrassRadius(a_fGrassRadius)
   {}

   virtual void FrameMove (FLOAT fElapsedTime);

private:
   Zone* const m_pTerrain;
   float m_fHeightScale;
   float m_fGrassRadius;

   float m_fDefaultHeight;
};


class HeightCamera : public CFirstPersonCamera
{
public:
   HeightCamera (float a_fHeight, std::pair<float, float> a_pMinMaxHeight,
      Zone* const a_pTerrain, float a_fHeightScale, float a_fGrassRadius) :
      m_fDefaultHeight(a_fHeight), m_pTerrain(a_pTerrain),
      m_fHeightScale(a_fHeightScale), m_fGrassRadius(a_fGrassRadius),
      m_pMinMaxHeight(a_pMinMaxHeight)
   {
      m_bEnableYAxisMovement = false;
   }

   virtual void FrameMove (FLOAT fElapsedTime);

private:
   Zone* const m_pTerrain;
   float m_fHeightScale;
   float m_fGrassRadius;

   float m_fDefaultHeight;
   std::pair<float, float> m_pMinMaxHeight;
};


class MeshCamera : public CFirstPersonCamera
{
public:
   MeshCamera(float a_fMeshDist, std::pair<float, float> a_pMinMaxMeshDist,
      float a_fHeight, std::pair<float, float> a_pMinMaxHeight,
      Mesh* a_pMesh,
      Zone* const a_pTerrain, float a_fHeightScale, float a_fGrassRadius) :
      m_pMesh(a_pMesh), m_fMeshDist(a_fMeshDist),
      m_fDefaultHeight(a_fHeight), m_pTerrain(a_pTerrain),
      m_fHeightScale(a_fHeightScale), m_fGrassRadius(a_fGrassRadius),
      m_pMinMaxHeight(a_pMinMaxHeight), m_pMinMaxMeshDist(a_pMinMaxMeshDist)
   {
      m_vLookDir.x = 0.0f;
      m_vLookDir.y = 0.0f;
      m_vLookDir.z = 0.0f;
      m_nOldWheelMouseDelta = 0;
   }

   virtual void FrameMove (FLOAT fElapsedTime);

   float GetMeshDist (void) const noexcept;

private:
   Zone* const m_pTerrain;
   float m_fHeightScale;
   float m_fGrassRadius;

   float m_fDefaultHeight;
   std::pair<float, float> m_pMinMaxHeight;

   Mesh* m_pMesh;
   XMFLOAT3 m_vLookDir;

   float m_fMeshDist;
   std::pair<float, float> m_pMinMaxMeshDist;

   short int m_nOldWheelMouseDelta;
};
