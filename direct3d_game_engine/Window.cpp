#include "Window.h"

Window::WindowClass Window::WindowClass::wndClass;

// WindowClass
Window::WindowClass::WindowClass()
	:hInstance(GetModuleHandle(nullptr))
{
	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = GetInstance();
	wc.lpszClassName = GetName();
	RegisterClass(&wc);
}

Window::WindowClass::~WindowClass()
{
	UnregisterClass(wndClassName, GetInstance());
}

const char* Window::WindowClass::GetName()
{
	return wndClassName;
}

HINSTANCE Window::WindowClass::GetInstance()
{
	return wndClass.hInstance;
}

// Window
Window::Window(int width, int height, const char* name)
{
	RECT rect;
	rect.left = 100;
	rect.right = rect.left + width;
	rect.top  = 100;
	rect.bottom = rect.top + height;
	AdjustWindowRect(&rect, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);

	hWnd = CreateWindowExA(
		0, WindowClass::GetName(), name,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top,
		nullptr, nullptr, WindowClass::GetInstance(), this
	);
	ShowWindow(hWnd, SW_SHOW);
}

Window::~Window()
{
	DestroyWindow(hWnd);
}

LRESULT Window::WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	switch(msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
