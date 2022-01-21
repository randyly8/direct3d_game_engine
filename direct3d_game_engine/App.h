#pragma once
#include "Window.h"
class App
{
public:
	App();
	int Go(); // message loop
private:
	void DoFrame();
private:
	Window wnd;
};

