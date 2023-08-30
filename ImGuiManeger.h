#pragma once
#include <Windows.h>
#include <cstdint>
#include <d3d12.h>

class WinApp;
class DirectXCommon;

class ImGuiManeger {
public:
	void Initialize(WinApp* winApp_, DirectXCommon* dir_);
	void Update();
	void Draw(DirectXCommon* dir_);
	void Release();
};
