#pragma once
#include "MyWin.h"
#include "MyException.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include <string>
#include <memory>

class Window
{
public:
	class Exception : public MyException
	{
	public:
		Exception(int line, const char* file, HRESULT hr);
		const char* what() const override;
		virtual const char* GetType() const;
		static std::string TranslateErrorCode(HRESULT hr);
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;
	private:
		HRESULT hr;
	};
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

// error exception macro
#define MYWND_EXCEPT( hr ) Window::Exception( __LINE__,__FILE__,hr )
#define MYWND_LAST_EXCEPT() Window::Exception( __LINE__,__FILE__,GetLastError() )