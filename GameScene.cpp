#include "GameScene.h"

GameScene::GameScene(){

}

GameScene::~GameScene(){
	for (int i = 0; i < Max; i++) {
		delete triangle[i];
	}
	delete sprite;
	delete sphere;
	delete model;
	delete camera;
}

void GameScene::Initialize(){

	camera = new Camera();
	camera->Initialize();

	sprite = new Sprite(); 
	sprite->Initialize("Resources/uvChecker.png");

	sphere = new Sphere();
	sphere->Initialize("Resources/moon.png");

	model = new Model();
	model->Initialize("Resources/uvChecker.png");

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

	triangle[0] = new Triangle();
	triangle[0]->Initialize("Resources/monsterBall.png", pos[0]);

	for (int i = 1; i < Max; i++) {
		triangle[i] = new Triangle();
		triangle[i]->Initialize("Resources/uvChecker.png", pos[i]);
	}
}

void GameScene::Update(){
	camera->Update();
}

void GameScene::Draw(){

	for (int i = 2; i < Max; i++) {
		triangle[i]->Draw(*camera->transformationMatrixData);
	}

	triangle[0]->Draw(*camera->transformationMatrixData);
	triangle[1]->Draw(*camera->transformationMatrixData);

	sphere->Draw(*camera->transformationMatrixData);
	
	sprite->Draw();

	model->Draw(*camera->transformationMatrixData);
}

void GameScene::Release(){
}
