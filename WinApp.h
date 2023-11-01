#pragma once
#include <Windows.h>
#include <cstdint>
#include <d3d12.h>
#include "externals/imgui/imgui.h"
#include "externals/imgui/imgui_impl_dx12.h"
#include "externals/imgui/imgui_impl_win32.h"

class WinApp {
public:

	static WinApp* GetInsTance();

	void Initialize(const wchar_t* title);

	WNDCLASS wc{};

	// クライアント領域のサイズ
	static const int32_t kClientWidth = 1280;
	static const int32_t kClientHeight = 720;

	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	static inline HWND hwnd = nullptr;
	static inline ID3D12Debug1* debugController = nullptr;
};