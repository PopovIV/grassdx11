#pragma once

#include "../../pch.h"

#include "Input.h"
#include "../Dev/Log.h"
#include "../Graphics//ImGui/imgui.h"
#include "../Graphics//ImGui\imgui_impl_dx11.h"
#include "../Graphics//ImGui\imgui_impl_win32.h"

namespace AvocadoSky {

	class RenderWindow {
	private:
		Input _input;
		HWND _handle = NULL;
		std::string _windowTitle = "";

		int _width = 0;
		int _height = 0;

		bool _isRun;
		bool _controlByCoursor = true;

		void CheckQuit();

	public:
		RenderWindow(int windowWidth, int windowHeight, std::string windowTitle);
		~RenderWindow();

		bool MyRegisterClass();
		bool CreateMainWnd();
		LRESULT CALLBACK MessageProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

		bool Update();
		bool isRunning();
		bool Release();

		const HWND& GetHWND() const;
		const int& getWidth() const;
		const int& getHeight() const;

		const bool isFocus() const;
	};
}