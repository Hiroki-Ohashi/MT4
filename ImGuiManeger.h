#pragma once
#include <Windows.h>
#include <cstdint>
#include <d3d12.h>

class WinApp;
class DirectX;

class ImGuiManeger {
public:

	void Initialize(WinApp* winApp_, DirectX* dir_);
	void Update();
	void Draw(DirectX* dir_);
	void Release();
};
