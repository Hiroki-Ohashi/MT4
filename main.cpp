#include <Windows.h>
#include <cstdint>
#include <string>
#include <format>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include <dxgidebug.h>
#include <dxcapi.h>
#include "WinApp.h"
#include "Function.h"
#include "DirectX.h"
#include "Triangle.h"

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dxcompiler.lib")

// WIndowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	WinApp* winapp = new WinApp(L"CG2");
	Triangle* triangle = new Triangle;
	
	DirectX::Initialize();
	DirectX::Fence();

	MSG msg{};
	
	Triangle::DxcInitialize();
	Triangle::DxcPso();

	for (int i = 0; i < 10; i++) {
		triangle->DxcVertexDraw();
	}

	Triangle::DxcViewport();
	Triangle::DxcScissor();

	// ウインドウの×ボタンが押されるまでループ
	while (msg.message != WM_QUIT) {
		// Windowにメッセージが来てたら最優先で処理させる
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			// ゲームの処理
			DirectX::Update();
		}
	}

	DirectX::Release();

	return 0;
}