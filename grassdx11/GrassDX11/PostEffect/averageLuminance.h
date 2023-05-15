//--------------------------------------------------------------------------------------
// averageLuminance - class for calculating average luminance
//--------------------------------------------------------------------------------------
#ifndef _AVERAGELUMINANCE_H_
#define _AVERAGELUMINANCE_H_

#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <fstream>
#include <vector>
#include "renderTexture.h"

using namespace DirectX;
using namespace std;

#define ARRAY_SIZE 20

class AverageLuminance {
  public:
    // Function to initialize
    bool Initialize(ID3D11Device* device, int screenWidth, int screenHeight);
    // Function to realese
    void Shutdown();
    // Render function
    float Process(ID3D11DeviceContext* deviceContext, ID3D11ShaderResourceView* sourceTexture);
    void Resize(ID3D11Device* device, int width, int height);
  private:
    void CopyTexture(ID3D11DeviceContext* deviceContext, ID3D11ShaderResourceView* sourceTexture, RenderTexture& dst, ID3D11PixelShader* pixelShader);

    bool CreateTextures(ID3D11Device* device, int width, int height);

    // Function to initialize
    bool InitializeShader(ID3D11Device* device, const wchar_t* vsFilename, const wchar_t* psCopyFilename, const wchar_t* psFilename);

    std::vector<RenderTexture*> m_renderTextures;

    ID3D11VertexShader* m_vertexShader = nullptr;
    ID3D11PixelShader* m_copyPixelShader = nullptr;
    ID3D11PixelShader* m_pixelShader = nullptr;
    ID3D11SamplerState* m_sampleState = nullptr;
    ID3D11Texture2D* m_luminanceTextureArray[ARRAY_SIZE];
    ID3D11Texture2D* m_luminanceTextureGPU;
    unsigned int m_curFrame = 0;

    float m_adaptedLuminance = 0.0f;

    LARGE_INTEGER m_qpcFrequency;
    LARGE_INTEGER m_qpcLastTime;
};
#endif