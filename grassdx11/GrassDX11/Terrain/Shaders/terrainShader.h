//--------------------------------------------------------------------------------------
// TerrainShader  - class for color map terrain shader
//--------------------------------------------------------------------------------------
#ifndef _TERRAINSHADER_H_
#define _TERRAINSHADER_H_

#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <fstream>
#include "../Terrain/Engine/Utility/D3DInclude.h"
#include "../Terrain/Shaders/defines.h"

using namespace DirectX;
using namespace std;

class TerrainShader {
  private:
    struct MatrixBufferType {
        XMMATRIX worldMatrix;
    };

    struct SceneProjectionBufferType {
        XMMATRIX viewProjectionMatrix;
        XMFLOAT4 planes[6];
        XMFLOAT3 cameraPos;
    };

    struct LightBufferType {
        XMFLOAT4 ambientColor;
        XMFLOAT4 diffuseColor;
        XMFLOAT4 lightDirection;
    };

    struct ScaleBufferType {
        XMINT4 scales; // x - grass, y - rock, z - slope, w - snow
        XMFLOAT4 detailScale; // x - detail texture scale
    };

  public:
    // Function to initialize shader
    bool Initialize(ID3D11Device* device);
    // Function to realese shader
    void Shutdown() { ShutdownShader(); }
    // Render function
    bool Render(ID3D11DeviceContext* deviceContext, XMFLOAT4* frustumPlanes, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, XMFLOAT3 cameraPos, XMFLOAT3 lightDir, XMFLOAT3 lightColor, ID3D11ShaderResourceView* textures[], bool normalPass);

  private:
    // Function to initialize shader
    bool InitializeShader(ID3D11Device* device, const wchar_t* vsFilename, const wchar_t* psFilename, const wchar_t* hsFilename, const wchar_t* dsFilename, const wchar_t* csFilename);
    // Function to release shader
    void ShutdownShader();
    // Function to fill shader buffers and params
    bool SetShaderParameters(ID3D11DeviceContext* deviceContext, XMFLOAT4* frustumPlanes, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, XMFLOAT3 cameraPos, XMFLOAT3 lightDir, XMFLOAT3 lightColor, ID3D11ShaderResourceView* textures[]);
    // Render function
    void RenderShader(ID3D11DeviceContext* deviceContext, bool normalPass);

    ID3D11VertexShader* m_vertexShader = nullptr;
    ID3D11PixelShader* m_pixelShader = nullptr;
    ID3D11HullShader* m_hullShader = nullptr;
    ID3D11DomainShader* m_domainShader = nullptr;
    ID3D11ComputeShader* m_pCullShader = nullptr;
    ID3D11InputLayout* m_layout = nullptr;
    ID3D11Buffer* m_worldMatrixBuffer = nullptr;
    ID3D11Buffer* m_pCullParams = nullptr;
    ID3D11Buffer* m_viewProjectionMatrixBuffer = nullptr;
    ID3D11SamplerState* m_samplerState = nullptr;
    ID3D11SamplerState* m_samplerStateNoMips = nullptr;
    ID3D11Buffer* m_lightBuffer = nullptr;
    ID3D11Buffer* m_scaleBuffer = nullptr;

    ID3D11Buffer* m_pInderectArgsSrc = nullptr;
    ID3D11Buffer* m_pInderectArgs = nullptr;
    ID3D11UnorderedAccessView* m_pInderectArgsUAV = nullptr;
    ID3D11Buffer* m_pGeomBufferInstVis = nullptr;
    ID3D11Buffer* m_pGeomBufferInstVisGpu = nullptr;
    ID3D11UnorderedAccessView* m_pGeomBufferInstVisGpu_UAV = nullptr;
};

#endif
