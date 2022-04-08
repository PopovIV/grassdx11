#pragma once

#include <d3d11.h>
#include "../Application/Window.h"
#include "../Dev/Helpers.h"
#include "Camera2.h"
#include "CameraClass.h"

namespace AvocadoSky {

	class Renderer {
	private:
		IDXGISwapChain* _swapChain;
		ID3D11Device* _device;
		ID3D11DeviceContext* _deviceContext;
		ID3D11RenderTargetView* _renderTargetView;

		ID3D11Texture2D* _depthStencilBuffer;
		ID3D11DepthStencilState* _depthStencilState;
		ID3D11DepthStencilView* _depthStencilView;
		ID3D11RasterizerState* _rasterState;

		D3D11_TEXTURE2D_DESC _backBufferDesc;
		D3D11_RASTERIZER_DESC _rasterDesc;

		ID3D11BlendState* m_alphaEnableBlendingState;
		ID3D11BlendState* m_alphaDisableBlendingState;
		ID3D11BlendState* m_alphaBlendState2;

		Camera* _camera;
		//CameraClass* _camera2;

		XMMATRIX _projectionMatrix;
		XMMATRIX _viewMatrix;

		const bool vsyncEnabled = false;

		bool createDevice(RenderWindow& window, bool vsyncEnabled);
		bool createRenderTarget();
		bool createDepthStencilBuffers();
		bool createBlendState();



	public:
		int screenW;
		int screenH;

		void EnableSecondBlendState();

		void TurnOnAlphaBlending();
		void TurnOffAlphaBlending();

		Renderer(
			int screenWidth, int screenHeight,
			ID3D11Device* _device,
			ID3D11DeviceContext* _deviceContext,
			ID3D11Texture2D* _pRenderTarget,
			ID3D11RenderTargetView* _pRTRV,
			ID3D11Texture2D* _pDSTarget,
			ID3D11DepthStencilView* _pDSRV,
			ID3D11DepthStencilState* _depthStencilStateEnabled
		);

		Renderer(RenderWindow& window);
		~Renderer();

		void beginFrame();
		void clear();
		void endFrame();

		void setCamera(Camera& cam);

		//void setCamera(CameraClass& cam);

		void setWireframe(bool wireFrame);

		ID3D11Device* getDevice() const;
		ID3D11DeviceContext* getDeviceContext() const;

		XMMATRIX getProjectionMatrix();
		XMMATRIX getViewMatrix();

		XMFLOAT3 getCameraPosition() const;

	};
}