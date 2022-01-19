#include "Window.h"

Window::WindowClass Window::WindowClass::wndClass;

// WindowClass
Window::WindowClass::WindowClass()
	:hInstance(GetModuleHandle(nullptr))
{
	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = HandleMessageSetup;
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

bool Window::ProcessMesseges()
{
	bool gResult = GetMessage(&msg, NULL, 0, 0);
	if (gResult)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return gResult;
}

void Window::Update()
{
	while (!kbd.CharBufferIsEmpty())
	{
		unsigned char ch = kbd.ReadChar();
		std::string outmsg = "Char: ";
		outmsg += ch;
		outmsg += "\n";
		OutputDebugStringA(outmsg.c_str());
	}
	while (!kbd.KeyBufferIsEmpty())
	{
		KeyboardEvent kbe = kbd.ReadKey();
		unsigned char keycode = kbe.GetKeyCode();
		std::string outmsg = "";
		if (kbe.IsPress()) outmsg += "Key press: ";
		if (kbe.IsRelease()) outmsg += "Key Release: ";
		outmsg += keycode;
		outmsg += "\n";
		OutputDebugStringA(outmsg.c_str());
	}
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

LRESULT Window::HandleMessageSetup(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_NCCREATE:
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* pWindow = reinterpret_cast<Window*>(pCreate->lpCreateParams);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
		SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(HandleMsgRedirect));
		return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);
	}
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

LRESULT CALLBACK Window::HandleMsgRedirect(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		return 0;

	default:
	{
		// retrieve ptr to window class
		Window* const pWindow = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		// forward message to window class handler
		return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);
	}
	}
}

LRESULT Window::WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	switch(msg)
	{
	case WM_KEYDOWN: 
	{
		unsigned char keycode = static_cast<unsigned char>(wParam);
		if (kbd.IsKeysAutoRepeat())
		{
			kbd.OnKeyPressed(keycode);
		}
		else
		{
			const bool wasPressed = lParam & 0x40000000;
			if (!wasPressed)
			{
				kbd.OnKeyPressed(keycode);
			}
		}
		return 0;
	}
	case WM_KEYUP:
	{
		unsigned char keycode = static_cast<unsigned char>(wParam);
		kbd.OnKeyReleased(keycode);
		return 0;
	}
	case WM_CHAR:
	{
		unsigned char ch = static_cast<unsigned char>(wParam);
		if (kbd.IsCharsAutoRepeat())
		{
			kbd.OnChar(ch);
		}
		else
		{
			const bool wasPressed = lParam & 0x40000000;
			if (!wasPressed)
			{
				kbd.OnChar(ch);
			}
		}
		return 0;
	}
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
