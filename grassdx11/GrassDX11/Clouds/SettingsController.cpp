#include "pch.h"
#include "SettingsController.h"
#include "Engine\Application\Time.h"

using namespace AvocadoSky;

float SettingsController::turbidity = 2.0f;
float SettingsController::time = 0.0f;
float SettingsController::brightness = 1.0f;
float SettingsController::scale = 0.3f;
float SettingsController::translationSpeed = 0.0f;
XMFLOAT3 SettingsController::diffuse = XMFLOAT3(0.5f, 0.5f, 0.5f);

float SettingsController::nightTime = 3.0f;
float SettingsController::dayTime = 6.0f;
float SettingsController::timeSpeed = 0.0f;

float SettingsController::dayBrightness = 1.0f;
float SettingsController::nightBrightness = 0.5f;
float SettingsController::brightnessSpeed = 0.0f;

XMFLOAT3 SettingsController::dayDiffuse = XMFLOAT3(0.5f, 0.5f, 0.5f);
XMFLOAT3 SettingsController::nightDiffuse = XMFLOAT3(0.2f, 0.2f, 0.2f);
XMFLOAT3 SettingsController::diffuseSpeed = XMFLOAT3(0.0f, 0.0f, 0.0f);

float SettingsController::usualTranslationSpeed = 0.2f;
float SettingsController::animationTranslationSpeed = 2.0f;
float SettingsController::animationSteps = 1000.0f;

bool SettingsController::changeDayTime = false;
bool SettingsController::currentTimeiSDay = true;


std::string SettingsController::fpsStr = "";

void SettingsController::ImGuiNewFrame() {
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void SettingsController::ImGuiInit(const HWND hwnd, const Renderer &renderer) {
	IMGUI_CHECKVERSION();
	static ImVec2 pos = ImVec2(50, renderer.screenH - 400);
	//ImGui::SetNextWindowPos(pos);
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(renderer.getDevice(), renderer.getDeviceContext());
	ImGui::StyleColorsDark();
}

void SettingsController::DispalyFPSMonitor() {
	ImGui::Begin("FPS Monitor");

	if (Time::hasOneSecondPassed()) {
		int fps = Time::getFramesPerSecond();
		fpsStr = "FPS: " + std::to_string(fps) + " (" + std::to_string(1000.0f / fps) + " ms)";
	}

	ImGui::Text(fpsStr.c_str());
}

void SettingsController::DisplayTurbiditySlider() {
	ImGui::SliderFloat("Turbidity", &SettingsController::turbidity, 0.5f, 5.0f);
}

void SettingsController::DisplayTimeSlider() {
	ImGui::SliderFloat("Time", &SettingsController::time, 0.0f, 3.0f);
}

void SettingsController::DisplayCloudsSettings()
{
	ImGui::SliderFloat("Clouds translation", &SettingsController::translationSpeed, 0.0f, 1.0f);
	ImGui::SliderFloat("Clouds brightness", &SettingsController::brightness, 0.0f, 3.0f);
	ImGui::SliderFloat("Clouds scale", &SettingsController::scale, 0.0f, 0.5f);
}

void SettingsController::ImGuiEndFrame() {
	ImGui::End();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void  SettingsController::Init() {
	timeSpeed = (dayTime - nightTime) / animationSteps;
	brightnessSpeed = (dayBrightness - nightBrightness) / animationSteps;
	diffuseSpeed.x = (dayDiffuse.x - nightDiffuse.x) / animationSteps;
	diffuseSpeed.y = (dayDiffuse.y - nightDiffuse.y) / animationSteps;
	diffuseSpeed.z = (dayDiffuse.z - nightDiffuse.z) / animationSteps;

	diffuse = dayDiffuse;
	translationSpeed = usualTranslationSpeed;
}

void SettingsController::Update() {
	if (changeDayTime) {
		if (currentTimeiSDay) {
			if (time < nightTime)
			{
				translationSpeed = animationTranslationSpeed;
				time += timeSpeed;
				brightness -= brightnessSpeed;

				diffuse.x -= diffuseSpeed.x;
				diffuse.y -= diffuseSpeed.y;
				diffuse.z -= diffuseSpeed.z;
			}
			else {
				currentTimeiSDay = false;
				translationSpeed = usualTranslationSpeed;
				changeDayTime = false;
			}			
		}
		else {
			if (time < dayTime)
			{
				translationSpeed = animationTranslationSpeed;
				time += timeSpeed;
				brightness += brightnessSpeed;

				diffuse.x += diffuseSpeed.x;
				diffuse.y += diffuseSpeed.y;
				diffuse.z += diffuseSpeed.z;
			}
			else {
				currentTimeiSDay = true;
				time = 0;
				translationSpeed = usualTranslationSpeed;
				changeDayTime = false;
			}
			
		}
		
	}
}
