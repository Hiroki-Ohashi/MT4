#pragma once
#include "WinApp.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "GameScene.h"

class GameManager {
public:
	GameManager();
	~GameManager();

	static GameManager* GetInsTance();

	void Run();

private:
	WinApp* winapp = nullptr;
	DirectXCommon* directX = nullptr;
	Input* input = nullptr;
};