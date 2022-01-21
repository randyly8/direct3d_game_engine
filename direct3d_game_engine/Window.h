#pragma once
#include "MyWin.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include <string>
#include <memory>

class Window
{
	friend class Window;
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
	int Go();
	void Update();
	Window(int width, int height, const char* name);
	~Window();
	Graphics& Gfx();
private:
	static LRESULT CALLBACK HandleMessageSetup(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK HandleMsgRedirect(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
private:
	MSG msg;
	HWND hWnd;
protected:
	Keyboard kbd;
	Mouse mouse;
	std::unique_ptr<Graphics> pGfx; // defer pointer
};

