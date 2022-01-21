#pragma once
#include "MyWin.h"
#include <d3d11.h>

class Graphics
{
public:
	Graphics(HWND hWnd);
	~Graphics();
	// flip frame
	void EndFrame(); 
	void ClearBuffer(float red, float green, float blue) noexcept;
private:
	ID3D11Device* pDevice = nullptr;
	IDXGISwapChain* pSwap = nullptr;
	ID3D11DeviceContext* pContext = nullptr;
	ID3D11RenderTargetView* pTarget = nullptr;
};

