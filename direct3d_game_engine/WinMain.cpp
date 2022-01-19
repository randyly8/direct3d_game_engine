#include "Window.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Window wnd(100, 100, "This is a test.");

	while (wnd.ProcessMesseges() == true)
	{
		wnd.Update();
	}

	return 0;
}