#include <crtdbg.h>
#include "ErrorLogger.h"

#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>

#include "Engine/Application/Window.h"
#include "Engine/Graphics/Renderer.h"
#include "Engine/Graphics/Texture.h"
#include "Engine/Graphics/Mesh.h"
#include "Engine/Graphics/ComputeShader.h"
#include "Engine/Application/Time.h"
#include "ShaderHandlers/SkyboxShader.h"
#include "Examples\GameObjects\Skybox.h"
#include "Examples\GameObjects\CameraController.h"


#include "Engine\Graphics\ImGui\imgui.h"
#include "Engine\Graphics\ImGui\imgui_impl_dx11.h"
#include "Engine\Graphics\ImGui\imgui_impl_win32.h"
#include "SettingsController.h"


#include "Examples/GameObjects/PerlinNoise.h"
#include "Clouds.h"
#include "Terrain.h"


int main(void) {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	int windowWidth = 1920;
	int windowHeight = 1080;

	RenderWindow window(windowWidth, windowHeight, "Sky");

	window.MyRegisterClass();

	if (!window.CreateMainWnd()) {
		Log::error("Could not initialize window.");
	}

	ID3D11Debug* d3dDebug = nullptr;

	Renderer renderer(window);

	renderer.getDevice()->QueryInterface(IID_PPV_ARGS(&d3dDebug));	

	CameraController cameraController(windowWidth, windowHeight);

	renderer.setCamera(cameraController.getCamera());

	Time time;

	Skybox skybox(renderer);

	Clouds clouds(renderer);

	//Terrain terrain(renderer);

	clouds.setSkybox(skybox);

	//terrain.setSkybox(skybox);

	SettingsController::ImGuiInit(window.GetHWND(), renderer);

	window.Update();

	while (window.isRunning())	{

		window.Update();
		time.updateDeltaTime();
		cameraController.update();

		renderer.beginFrame();
		renderer.clear();
		
		skybox.draw();

		renderer.EnableSecondBlendState();

		//renderer.TurnOnAlphaBlending();

		clouds.draw();

		renderer.TurnOffAlphaBlending();

		//terrain.draw();

		//renderer.TurnOffAlphaBlending();


		SettingsController::ImGuiNewFrame();

		SettingsController::DispalyFPSMonitor();
		SettingsController::DisplayTimeSlider();
		SettingsController::DisplayTurbiditySlider();

		SettingsController::DisplayCloudsSettings();
		
		SettingsController::ImGuiEndFrame();

		renderer.endFrame();
	}

	window.Release();

	UINT reference = renderer.getDevice()->Release();

	if (reference > 1) {
		d3dDebug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
		d3dDebug->Release();
	}
	
	return 0;
}



