#include "GameManager.h"

GameManager::GameManager()
{
	winapp = WinApp::GetInsTance();
	winapp->Initialize(L"CG2");

	directX = DirectXCommon::GetInsTance();
	directX->Initialize();

	mesh = Mesh::GetInsTance();
	mesh->Initialize();

	input = Input::GetInsTance();
	input->Initialize();
}

GameManager::~GameManager()
{
}

GameManager* GameManager::GetInsTance()
{
	static GameManager instance;
	return &instance;
}

void GameManager::Run()
{
	CoInitializeEx(0, COINIT_MULTITHREADED);

	GameScene* gameScene = new GameScene;

	gameScene->Initialize();

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

			directX->Update();
			input->Update();
			mesh->Update();
			gameScene->Update();

			// 描画処理

			gameScene->Draw();
			directX->Close();
		}
	}

	CoUninitialize();

	gameScene->Release();
	mesh->Release();
	directX->Release();
}
