#pragma once
#include <Windows.h>
#include <cstdint>
#include <d3d12.h>

class WinApp;

class ImGuiManeger {
public:
	void Initialize();

	void Update();

	void Draw();

	void Release();
};