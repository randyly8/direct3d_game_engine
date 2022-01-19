#pragma once
#include <windows.h>

class Window
{
private:
	class WindowClass
	{
	public:
		static const char* GetName();
		static HINSTANCE GetInstance();
	private:
		WindowClass();
		~WindowClass();
		static constexpr const char* wndClassName = "Direct3D Engine";
		static WindowClass wndClass;
		HINSTANCE hInstance;
	};
public:
	Window(int width, int height, const char* name);
	~Window();
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
private:
	HWND hWnd;
};

