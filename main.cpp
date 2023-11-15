#include "GameManager.h"



// WIndowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	GameManager* gameManager = GameManager::GetInsTance();

	gameManager->Run();

	return 0;
}