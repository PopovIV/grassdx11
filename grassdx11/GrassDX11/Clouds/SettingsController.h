#pragma once

#include "Engine\Graphics\ImGui\imgui.h"
#include "Engine\Graphics\ImGui\imgui_impl_dx11.h"
#include "Engine\Graphics\ImGui\imgui_impl_win32.h"
#include "Engine\Graphics\Renderer.h"

namespace AvocadoSky {

    class SettingsController {

    public:
        static bool changeDayTime;
        
        static float turbidity;
        static float time;

        static float brightness;
        static float scale;
        static float translationSpeed;

        static XMFLOAT3 diffuse;

        static std::string fpsStr;

        static void ImGuiInit(const HWND hwnd, const Renderer& renderer);

        static void ImGuiNewFrame();

        static void DispalyFPSMonitor();
        static void DisplayTurbiditySlider();
        static void DisplayTimeSlider();
        static void DisplayCloudsSettings();

        static void ImGuiEndFrame();

        static void Init();
        static void Update();

    private:
        static bool currentTimeiSDay;

        static float nightTime;// = 3.0f;
        static float dayTime;// = 6.0f;
        static float timeSpeed;

        static float dayBrightness;
        static float nightBrightness;
        static float brightnessSpeed;

        static float usualTranslationSpeed;
        static float animationTranslationSpeed;

        static XMFLOAT3 dayDiffuse;
        static XMFLOAT3 nightDiffuse;
        static XMFLOAT3 diffuseSpeed;

        static float animationSteps;

    };
}

