#include "Window.h"
#include "App.h"

App::App()
	:
	wnd(800, 600, "This is a test.")
{
}

int App::Go()
{
	MSG msg = wnd.RetrieveMessage();
	BOOL gResult;
	while ((gResult = GetMessage(&msg, NULL, 0, 0)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		DoFrame();
	}
	if (gResult == -1) return -1;
	return msg.wParam;
}

void App::DoFrame()
{
}
