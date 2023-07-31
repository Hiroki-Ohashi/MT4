#pragma once
#include <Windows.h>
#include <cstdint>
#include <d3d12.h>

class WinApp;
class DirectXManeger;

class ImGuiManeger {
public:
	void Initialize(WinApp* winApp_, DirectXManeger* dir_);
	void Update();
	void Draw(DirectXManeger* dir_);
	void Release();
};
