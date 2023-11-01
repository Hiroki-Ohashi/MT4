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

	WinApp* winapp = WinApp::GetInsTance();
	DirectXCommon* directX = DirectXCommon::GetInsTance();
	Mesh* mesh = new Mesh();
	Triangle* triangle[Max];
	Sprite* sprite = new Sprite();
	Sphere* sphere = new Sphere();
	Model* model = new Model();
	ImGuiManeger* imgui = new ImGuiManeger();
	Camera* camera = new Camera();
	
	winapp->Initialize(L"CG2");
	directX->Initialize();
	mesh->Initialize();
	sprite->Initialize(mesh);
	sphere->Initialize(mesh);
	model->Initialize(mesh);
	camera->Initialize();
	imgui->Initialize();

	for (int i = 0; i < Max; i++) {
		triangle[i] = new Triangle();
		triangle[i]->Initialize(mesh, pos[i]);
	}

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


			// 更新処理
			imgui->Update();
			directX->Update();
			mesh->Update();
			sprite->Update();
			camera->Update();
			sphere->Update(*camera->transformationMatrixData);
			model->Update(*camera->transformationMatrixData);

			for (int i = 0; i < 2; i++) {
				triangle[i]->Update(*camera->transformationMatrixData);
			}


			// 描画処理
			for (int i = 2; i < Max; i++) {
				triangle[i]->Draw();
			}

			triangle[0]->Draw();
			triangle[1]->Draw();

			sphere->Draw();
			sprite->Draw();
			model->Draw();


			ImGui::Begin("Mesh Color");

			ImGui::ColorEdit3("Triangle[0] Color", &triangle[0]->GetMaterialData()->color.x);
			ImGui::ColorEdit3("Triangle[1] Color", &triangle[1]->GetMaterialData()->color.x);
			ImGui::ColorEdit3("Sprite Color", &sprite->GetMaterialDataSprite()->color.x);
			ImGui::ColorEdit3("Sphere Color", &sphere->GetMaterialDataSphere()->color.x);

			ImGui::End();


			imgui->Draw();

			directX->Close();
		}
		CoUninitialize();
	}

	mesh->Release();
	imgui->Release();
	directX->Release();


	for (int i = 0; i < Max; i++) {
		delete triangle[i];
	}
	delete sprite;
	delete sphere;
	delete mesh;
	delete model;
	delete camera;
	delete imgui;

	return 0;
}