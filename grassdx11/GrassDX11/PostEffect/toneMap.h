//--------------------------------------------------------------------------------------
// toneMap  - class for adding post effects
//--------------------------------------------------------------------------------------
#ifndef _TONEMAP_H_
#define _TONEMAP_H_

#include "averageLuminance.h"

using namespace DirectX;
using namespace std;


__declspec(align(16))
struct LuminanceConstantBuffer {
    float AverageLuminance;
};

class ToneMap {
  public:
    // Function to initialize
    bool Initialize(ID3D11Device* device, int textureWidth, int textureHeight);
    // Function to realese
    void Shutdown();
    void Resize(ID3D11Device* device, int width, int height);
    // Render function
    void Process(ID3D11DeviceContext* deviceContext, ID3D11ShaderResourceView* sourceTexture, ID3D11RenderTargetView* renderTarget, D3D11_VIEWPORT viewport);
  private:
    // Function to initialize
    bool InitializeShader(ID3D11Device* device, const wchar_t* vsFilename, const wchar_t* psFilenam);

    AverageLuminance* m_averageLuminance = nullptr;
    ID3D11VertexShader* m_vertexShader = nullptr;
    ID3D11PixelShader* m_pixelShader = nullptr;
    ID3D11SamplerState* m_sampleState = nullptr;
    ID3D11Buffer* m_luminanceBuffer = nullptr;
};
#endif