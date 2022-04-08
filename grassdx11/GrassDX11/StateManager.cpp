#include "statemanager.h"

StateManager& GetGlobalStateManager(void)
{
   static StateManager instance;
   return instance;
}

StateManager::StateManager(void)
{
   m_pD3DDevice = NULL;
   m_bUseWireframe = false;
}

StateManager::~StateManager(void)
{
   for (RasterStateMap::iterator it = m_mRasterizerStates.begin();
      it != m_mRasterizerStates.end(); ++it)
   {
      SAFE_RELEASE(it->second);
   }
}

bool StateManager::AddRasterizerState(std::string a_sName, D3D11_RASTERIZER_DESC& Desc)
{
   if (m_pD3DDevice == NULL)
      return false;

   if (auto it = m_mRasterizerStates.find(a_sName); it != m_mRasterizerStates.end()) {
       SAFE_RELEASE(it->second);
   }
      //return true;

   //clear map

   ID3D11RasterizerState* rs_state;

   HRESULT hr;

   hr = m_pD3DDevice->CreateRasterizerState(&Desc, &rs_state);
   if (hr != S_OK)
      return false;

   m_mRasterizerStates[a_sName] = rs_state;

   return true;
}

bool StateManager::SetRasterizerState(std::string a_sName)
{
   if (m_pD3DDevice == NULL)
      return false;

   RasterStateMap::iterator it;

   it = m_mRasterizerStates.find(a_sName);
   if (it == m_mRasterizerStates.end())
      return false;

   try {
       m_pD3DDeviceCtx->RSSetState(it->second);
   }
   catch (...) {
       return false;
   }
   
   return true;
}
