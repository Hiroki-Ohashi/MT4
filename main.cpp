#include "GameScene.h"

// WIndowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

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
			
			gameScene->Update();

			// 描画処理
			
			gameScene->Draw();
		}
	}

	CoUninitialize();

	gameScene->Release();

	return 0;
}