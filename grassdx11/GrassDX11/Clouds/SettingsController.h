#pragma once

#include "Engine\Graphics\ImGui\imgui.h"
#include "Engine\Graphics\ImGui\imgui_impl_dx11.h"
#include "Engine\Graphics\ImGui\imgui_impl_win32.h"
#include "Engine\Graphics\Renderer.h"

namespace AvocadoSky {

    class SettingsController {

    public:

        static float turbidity;
        static float time;

        static float brightness;
        static float scale;
        static float translationSpeed;

        static std::string fpsStr;

        static void ImGuiInit(const HWND hwnd, const Renderer& renderer);

        static void ImGuiNewFrame();

        static void DispalyFPSMonitor();
        static void DisplayTurbiditySlider();
        static void DisplayTimeSlider();
        static void DisplayCloudsSettings();

        static void ImGuiEndFrame();
    };
}

