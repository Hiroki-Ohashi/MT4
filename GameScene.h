#pragma once
#include <Windows.h>
#include <cstdint>
#include <string>
#include <format>

#include "WinApp.h"
#include "Function.h"
#include "DirectXCommon.h"
#include "Mesh.h"
#include "Triangle.h"
#include "Sprite.h"
#include "ImGuiManeger.h"
#include "MathFunction.h"
#include "Camera.h"
#include "Sphere.h"
#include "Model.h"
#include "externals/imgui/imgui.h"

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dxcompiler.lib")


class GameScene {
public:
	GameScene();
	~GameScene();

	// 初期化
	void Initialize();
	// 読み込み
	void Update();
	// 描画
	void Draw();
	// 解放
	void Release();

private:

	// 三角形の数
	static const int Max = 26;

	WinApp* winapp = nullptr;
	DirectXCommon* directX = nullptr;
	Mesh* mesh = nullptr;
	Triangle* triangle[Max];
	Sprite* sprite = nullptr;
	Sphere* sphere = nullptr;
	Model* model = nullptr;
	ImGuiManeger* imgui = nullptr;
	Camera* camera = nullptr;
};
