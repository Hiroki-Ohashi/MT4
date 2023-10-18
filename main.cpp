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
#include "externals/imgui/imgui.h"


#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dxcompiler.lib")



// WIndowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	CoInitializeEx(0, COINIT_MULTITHREADED);

	// 三角形の数
	const int Max = 26;

	Vector4 pos[Max][3];
	for (int i = 2; i < Max; i++) {
		// 左下
		pos[i][0] = { -0.95f - (i * -0.07f), -0.75f, 0.0f, 1.0f };
		// 上
		pos[i][1] = { -0.92f - (i * -0.07f), -0.5f, 0.0f, 1.0f };
		// 右下
		pos[i][2] = { -0.89f - (i * -0.07f), -0.75f, 0.0f, 1.0f };
	}

	// 左下
	pos[0][0] = { -0.5f, -0.25f, 0.0f, 1.0f };
	// 上
	pos[0][1] = { 0.0f, 0.5f, 0.0f, 1.0f };
	// 右下
	pos[0][2] = { 0.5f, -0.25f, 0.0f, 1.0f };

	// 左下2
	pos[1][0] = { -0.5f, -0.25f, 0.5f, 1.0f };
	// 上2
	pos[1][1] = { 0.0f, 0.0f, 0.0f, 1.0f };
	// 右下2
	pos[1][2] = { 0.5f, -0.25f, -0.5f, 1.0f };

	WinApp* winapp = new WinApp(L"CG2");
	DirectXCommon* directX = new DirectXCommon();
	Mesh* mesh = new Mesh();
	Triangle* triangle[Max];
	Sprite* sprite = new Sprite();
	Sphere* sphere = new Sphere();
	ImGuiManeger* imgui = new ImGuiManeger();
	Camera* camera = new Camera();
	
	directX->Initialize(winapp);
	mesh->Initialize(directX);
	sprite->Initialize(directX, mesh);
	sphere->Initialize(directX, mesh);
	camera->Initialize();
	imgui->Initialize(winapp, directX);

	for (int i = 0; i < Max; i++) {
		triangle[i] = new Triangle();
		triangle[i]->Initialize(directX, mesh, pos[i]);
	}

	bool useMonsterBoll = true;

	MSG msg{};

	// ウインドウの×ボタンが押されるまでループ
	while (msg.message != WM_QUIT) {
		// Windowにメッセージが来てたら最優先で処理させる
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			// ゲームの処理



			imgui->Update();
			directX->Update();
			mesh->Update(directX);
			sprite->Update(winapp);
			camera->Update(winapp);
			sphere->Update(*camera->transformationMatrixData, useMonsterBoll);

			for (int i = 0; i < 2; i++) {
				triangle[i]->Update(*camera->transformationMatrixData);
			}

			for (int i = 2; i < Max; i++) {
				triangle[i]->Draw(directX, mesh);
			}

			triangle[0]->Draw(directX, mesh);
			triangle[1]->Draw(directX, mesh);

			sphere->Draw(directX, mesh);
			sprite->Draw(directX, mesh);

			ImGui::Begin("Mesh Color");
			ImGui::ColorEdit3("Mesh Color", &triangle[0]->materialData->x);
			ImGui::End();

			ImGui::Checkbox("useMonsterBall", &useMonsterBoll);

			/*ImGui::Begin("Camera Position");
			ImGui::SliderFloat3("Camera Pos", &cameraTransform.translate.x, -1.0f, 1.0f);
			ImGui::SliderFloat3("Camera scale", &cameraTransform.scale.x, -1.0f, 1.0f);
			ImGui::SliderFloat3("Camera rotate", &cameraTransform.rotate.x, -1.0f, 1.0f);
			ImGui::End();*/


			imgui->Draw(directX);

			directX->Close();
		}
		CoUninitialize();
	}

	for (int i = 0; i < Max; i++) {
		triangle[i]->Release();
		delete triangle[i];
	}

	sprite->Release();
	delete sprite;
	sphere->Release();
	delete sphere;
	mesh->Release();
	delete mesh;
	imgui->Release();
	directX->Release(winapp);
	delete camera;

	delete imgui;
	delete directX;

	return 0;
}