#include "Window.h"

using namespace AvocadoSky;

RenderWindow* g_renderWindow = nullptr;

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lparam) {
	switch (uMsg) {
	case WM_DESTROY:
		DestroyWindow(hwnd);
		break;
	default:
		return g_renderWindow->MessageProc(hwnd, uMsg, wparam, lparam);
	}
	return NULL;
}

void RenderWindow::CheckQuit() {
//#ifdef _DEBUG
	if (Input::isKeyDown(Keys::ESCAPE)) {
		this->_isRun = false;
	}
//#endif
}

RenderWindow::RenderWindow(int windowWidth, int windowHeight, std::string windowTitle)
	: _handle(nullptr), _isRun(false), 
	_width(windowWidth), _height(windowHeight),
	_windowTitle(windowTitle) {}

RenderWindow::~RenderWindow() {}


bool RenderWindow::MyRegisterClass() {

	WNDCLASSEX wc;
	wc.cbClsExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	//wc.lpszClassName = "MyWindowClass";
	//wc.lpszMenuName = "";
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = &WndProc;

	if (!RegisterClassEx(&wc)) {
		Log::error("Window class registration failed.");
		return false;
	}

	g_renderWindow = this;

	return true;
}

bool RenderWindow::CreateMainWnd() {	

	DWORD displayStyle = WS_OVERLAPPEDWINDOW;

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	RECT windowRect;
	windowRect.left = (screenWidth - _width) / 2;
	windowRect.top = (screenHeight - _height) / 2;
	windowRect.right = windowRect.left + _width;
	windowRect.bottom = windowRect.top + _height;

	AdjustWindowRect(&windowRect, displayStyle, FALSE);

	/*this->_handle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, 
		"MyWindowClass", 
		_windowTitle.c_str(), 
		displayStyle,
		windowRect.left, windowRect.top,
		windowRect.right - windowRect.left, 
		windowRect.bottom - windowRect.top,
		NULL, NULL, NULL, NULL
	);*/

	if (!this->_handle) {
		Log::error("Handle creation failed!");
		return false;
	}

	ShowWindow(this->_handle, SW_SHOW);
	SetForegroundWindow(this->_handle);
	SetFocus(this->_handle);
	UpdateWindow(this->_handle);


	ShowCursor(FALSE);

	this->_isRun = true;

	return true;
}

bool RenderWindow::Update() {
	_input.updateLastPressedKeys();

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG)); 
	
	while (PeekMessage(&msg,this->_handle,0,0, PM_REMOVE)){
		TranslateMessage(&msg);
		DispatchMessage(&msg); 
	}

	if (msg.message == WM_NULL)	{
		if (!IsWindow(this->_handle)) {
			this->_handle = NULL; 
			DestroyWindow(this->_handle);
			return false;
		}
	}

	if (this->_controlByCoursor) {
		ShowCursor(FALSE);
		// Follow cursor
		POINT newCursorPoint;
		newCursorPoint.x = this->_width / 2;
		newCursorPoint.y = this->_height / 2;


		// Update cursor delta
		POINT cursorPoint;
		GetCursorPos(&cursorPoint);
		ScreenToClient(this->_handle, &cursorPoint);

		_input.setCursorDelta(cursorPoint.x - newCursorPoint.x, cursorPoint.y - newCursorPoint.y);

		// Lock cursor position
		if (this->isFocus()) {
			ClientToScreen(this->_handle, &newCursorPoint);
			SetCursorPos(newCursorPoint.x, newCursorPoint.y);
		}

		// Update cursor position
		_input.setCursorPos(newCursorPoint.x, newCursorPoint.y);
	}
	else {
		ShowCursor(TRUE);
	}

	// Process frame
	if (this->_isRun) {
		this->CheckQuit();
	}

	return true;
}
 
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT RenderWindow::MessageProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {

	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam)) {
		return true;
	}

	switch (msg) 
	{
	case WM_KEYDOWN:
		this->_input.setKeyDown((unsigned int) wparam);

		if (this->_input.isKeyDown(Keys::Q)) {
			_controlByCoursor = !_controlByCoursor;
		}

		break;

	case WM_KEYUP:
		this->_input.setKeyUp((unsigned int) wparam);
		break;

	case WM_DESTROY:
		this->Release();
		break;

	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return 0;
}

bool RenderWindow::isRunning() {
	return this->_isRun;
}

bool RenderWindow::Release() {
	if (this->_handle) {
		DestroyWindow(this->_handle);
	}

	return true;
}


const HWND& RenderWindow::GetHWND() const {
	return this->_handle;
}

const int& RenderWindow::getWidth() const {
	return _width;
}

const int& RenderWindow::getHeight() const {
	return _height;
}

const bool RenderWindow::isFocus() const {
	return GetFocus() != NULL;
}
