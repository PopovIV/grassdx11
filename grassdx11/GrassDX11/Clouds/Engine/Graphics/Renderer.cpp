#include "Renderer.h"
#include "../Dev/Log.h"
#include <wrl\client.h>
#include "../../pch.h"

using namespace AvocadoSky;

bool Renderer::createRenderTarget() {
	HRESULT hr;
	// Get back buffer from swap chain
	Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
	hr = this->_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf()));

	if (FAILED(hr))	{
		Log::error("GetBuffer failed");
		return false;
	}

	hr = this->_device->CreateRenderTargetView(	backBuffer.Get(), nullptr, &this->_renderTargetView );

	if (FAILED(hr)) {
		Log::error("Failed to create render target view");
		return false;
	}

	// Get desc before releasing
	backBuffer->GetDesc(&_backBufferDesc);

	return true;
}


bool Renderer::createDepthStencilBuffers()
{
	HRESULT result;

	// Create a description of the depth and stencil buffers
	//D3D11_TEXTURE2D_DESC depthStencilBufferDesc = { 0 };
	//depthStencilBufferDesc.Width = window.getWidth();
	//depthStencilBufferDesc.Height = window.getHeight();
	//depthStencilBufferDesc.MipLevels = 1;
	//depthStencilBufferDesc.ArraySize = 1;
	//depthStencilBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	//depthStencilBufferDesc.SampleDesc.Count = 1;
	//depthStencilBufferDesc.SampleDesc.Quality = 0;
	//depthStencilBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	//depthStencilBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	//depthStencilBufferDesc.CPUAccessFlags = 0;
	//depthStencilBufferDesc.MiscFlags = 0;



	// Create a texture for the depth and stencil buffers using the filled out
	// description
	/*result = _device->CreateTexture2D(&depthStencilBufferDesc, NULL, &this->_depthStencilBuffer);

	if (FAILED(result))	{
		Log::error("Could not create depth/stencil texture.");
		return false;
	}*/

	// Create a description of the depth and stencil states
	//D3D11_DEPTH_STENCIL_DESC depthStencilDesc = { 0 };

	//depthStencilDesc.DepthEnable = true;
	//depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; // Write on/off
	//depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	//depthStencilDesc.StencilEnable = false;
	//depthStencilDesc.StencilReadMask = 0xFF; // Portion for reading
	//depthStencilDesc.StencilWriteMask = 0xFF; // Portion for writing

	//// Stencil operations if pixel is front-facing
	//depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	//depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	//depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	//depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	//// Stencil operations if pixel is back-facing
	//depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	//depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	//depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	//depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	////depthStencilDesc.DepthFunc == D3D11_COMPARISON_LESS_EQUAL;
	////depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;

	//// Create a depth stencil state
	//result = _device->CreateDepthStencilState(&depthStencilDesc, &this->_depthStencilState);

	//if (FAILED(result))	{
	//	Log::error("Could not create depth stencil state.");
	//	return false;
	//}

	//// Set the depth stencil state
	//_deviceContext->OMSetDepthStencilState(this->_depthStencilState, 1);

	//// Set up the depth stencil views desc
	//D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	//ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	//depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	//depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	//depthStencilViewDesc.Texture2D.MipSlice = 0;


	//// Create the depth stencil view
	//result = _device->CreateDepthStencilView(this->_depthStencilBuffer, &depthStencilViewDesc, &this->_depthStencilView);

	//if (FAILED(result))	{
	//	Log::error("Failed creating depth stencil view.");
	//	return false;
	//}

	//// Bind the render target view and depth stencil view to the 
	//// output merger pipeline
	//this->_deviceContext->OMSetRenderTargets(1, &this->_renderTargetView, _depthStencilView);

	//// Setup the raster description which will determine how and what
	//// polygons will be drawn
	//this->_rasterDesc.AntialiasedLineEnable = false;
	//this->_rasterDesc.CullMode = D3D11_CULL_NONE;
	//this->_rasterDesc.DepthBias = 0;
	//this->_rasterDesc.DepthBiasClamp = 0.0f;
	//this->_rasterDesc.DepthClipEnable = true;
	//this->_rasterDesc.FillMode = D3D11_FILL_SOLID;
	//this->_rasterDesc.FrontCounterClockwise = false;
	//this->_rasterDesc.MultisampleEnable = false;
	//this->_rasterDesc.ScissorEnable = false;
	//this->_rasterDesc.SlopeScaledDepthBias = 0.0f;

	//// Create the rasterizer state from the description we just filled out
	//result = _device->CreateRasterizerState(&_rasterDesc, &this->_rasterState);

	//if (FAILED(result))	{
	//	Log::error("Could not create rasterizer state.");
	//	return false;
	//}

	//// Set rasteriser state
	//_deviceContext->RSSetState(this->_rasterState);

	//// Set viewport
	//CD3D11_VIEWPORT viewport = CD3D11_VIEWPORT(	0.0f, 0.0f,	(float)_backBufferDesc.Width, (float)_backBufferDesc.Height	);

	//this->_deviceContext->RSSetViewports(1, &viewport);

	return true;
}

bool Renderer::createBlendState() {
	// Clear the blend state description.

	HRESULT result;

	D3D11_BLEND_DESC blendStateDescription = { 0 };

	

	// Create an alpha enabled blend state description.
	blendStateDescription.RenderTarget[0].BlendEnable = TRUE;
	blendStateDescription.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blendStateDescription.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendStateDescription.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendStateDescription.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendStateDescription.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendStateDescription.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendStateDescription.RenderTarget[0].RenderTargetWriteMask = 0x0f;


	// Create the blend state using the description.
	result = this->getDevice()->CreateBlendState(&blendStateDescription, &m_alphaEnableBlendingState);
	if (FAILED(result))
	{
		return false;
	}

	// Modify the description to create an alpha disabled blend state description.
	blendStateDescription.RenderTarget[0].BlendEnable = FALSE;

	// Create the second blend state using the description.
	result = this->getDevice()->CreateBlendState(&blendStateDescription, &m_alphaDisableBlendingState);
	if (FAILED(result))
	{
		return false;
	}

	// Create a secondary alpha blend state description.
	blendStateDescription.RenderTarget[0].BlendEnable = TRUE;
	blendStateDescription.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blendStateDescription.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	blendStateDescription.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendStateDescription.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendStateDescription.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendStateDescription.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendStateDescription.RenderTarget[0].RenderTargetWriteMask = 0x0f;

	// Create the blend state using the description.
	result = this->getDevice()->CreateBlendState(&blendStateDescription, &m_alphaBlendState2);
	if (FAILED(result))
	{
		return false;
	}

}

Renderer::Renderer(int screenWidth, int screenHeight,
	ID3D11Device* device,
	ID3D11DeviceContext* deviceContext,
	ID3D11Texture2D* pRenderTarget,
	ID3D11RenderTargetView* pRTRV,
	ID3D11Texture2D* pDSTarget,
	ID3D11DepthStencilView* pDSRV,
	ID3D11DepthStencilState* depthStencilStateEnabled) {

	screenW = screenWidth;
	screenH = screenHeight;


	_device = device;
	_deviceContext = deviceContext;
	_renderTargetView = pRTRV;
	_depthStencilBuffer = pDSTarget;
	_depthStencilView = pDSRV;
	_depthStencilState = depthStencilStateEnabled;

	this->_projectionMatrix = XMMatrixIdentity();
	this->_viewMatrix = XMMatrixIdentity();

	this->createDepthStencilBuffers();
	this->createBlendState();
}



Renderer::~Renderer() {
	// Set to windowed mode or the swap chain will throw an exception
	/*if (this->_swapChain) {
		this->_swapChain->SetFullscreenState(false, NULL);
	}

	S_RELEASE(this->_rasterState);
	S_RELEASE(this->_depthStencilView);
	S_RELEASE(this->_depthStencilState);
	S_RELEASE(this->_depthStencilBuffer);
	S_RELEASE(this->_renderTargetView);
	S_RELEASE(this->_deviceContext);
	S_RELEASE(this->_device);
	S_RELEASE(this->_swapChain);*/
	S_RELEASE(this->m_alphaBlendState2);
	S_RELEASE(this->m_alphaEnableBlendingState);
	S_RELEASE(this->m_alphaDisableBlendingState);
}


void Renderer::beginFrame() {
	// Update view matrix
	/*if (this->_camera != nullptr) {
		this->_viewMatrix = this->_camera->getViewMatrix();
	}*/

	//if (this->_camera2 != nullptr) {
	//	this->_viewMatrix = this->_camera2->GetViewMatrix();
	//}
}

void Renderer::endFrame() {
	// Swap buffers
	this->_swapChain->Present(vsyncEnabled, 0);
}

void Renderer::clear() {

	float backgroundColor[] = { 0.5f, 0.5f, 0.5f, 1.0f };

	this->_deviceContext->ClearRenderTargetView(this->_renderTargetView, backgroundColor);
	this->_deviceContext->ClearDepthStencilView(this->_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	//this->_swapChain->Present(0, NULL);
}

ID3D11Device* Renderer::getDevice() const {
	return this->_device;
}

ID3D11DeviceContext* Renderer::getDeviceContext() const {
	return this->_deviceContext;
}


XMMATRIX Renderer::getProjectionMatrix() {
	return this->_projectionMatrix;
}

XMMATRIX Renderer::getViewMatrix() {
	return this->_viewMatrix;
}


void Renderer::TurnOnAlphaBlending()
{
	float blendFactor[4];


	// Setup the blend factor.
	blendFactor[0] = 0.0f;
	blendFactor[1] = 0.0f;
	blendFactor[2] = 0.0f;
	blendFactor[3] = 0.0f;

	// Turn on the alpha blending.
	this->getDeviceContext()->OMSetBlendState(m_alphaEnableBlendingState, blendFactor, 0xffffffff);

	return;
}


void Renderer::TurnOffAlphaBlending()
{
	float blendFactor[4];


	// Setup the blend factor.
	blendFactor[0] = 0.0f;
	blendFactor[1] = 0.0f;
	blendFactor[2] = 0.0f;
	blendFactor[3] = 0.0f;

	// Turn off the alpha blending.
	this->getDeviceContext()->OMSetBlendState(m_alphaDisableBlendingState, blendFactor, 0xffffffff);

	return;
}

void Renderer::EnableSecondBlendState()
{
	float blendFactor[4];


	// Setup the blend factor.
	blendFactor[0] = 0.0f;
	blendFactor[1] = 0.0f;
	blendFactor[2] = 0.0f;
	blendFactor[3] = 0.0f;

	// Turn on the alpha blending.
	this->getDeviceContext()->OMSetBlendState(m_alphaBlendState2, blendFactor, 0xffffffff);

	return;
}