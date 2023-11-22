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
	delete imgui;
	delete textureManager;
}

void GameScene::Initialize(){

	textureManager = new TextureManager();
	textureManager->Initialize();

	camera = new Camera();
	camera->Initialize();

	sprite = new Sprite(); 
	sprite->Initialize(textureManager);

	sphere = new Sphere();
	sphere->Initialize(textureManager);

	model = new Model();
	model->Initialize(textureManager);

	imgui = new ImGuiManeger();
	imgui->Initialize();

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

	for (int i = 0; i < Max; i++) {
		triangle[i] = new Triangle();
		triangle[i]->Initialize(textureManager, pos[i]);
	}

	texture = textureManager->SetTexture("Resources/uvChecker.png", texture);
	//moonTexture = mesh->SetTexture("Resources/moon.png", moonTexture);
}

void GameScene::Update(){
	imgui->Update();
	camera->Update();
}

void GameScene::Draw(){

	/*for (int i = 2; i < Max; i++) {
		triangle[i]->Draw(texture, *camera->transformationMatrixData);
	}

	triangle[0]->Draw(texture, *camera->transformationMatrixData);
	triangle[1]->Draw(texture, *camera->transformationMatrixData);

	sphere->Draw(texture, *camera->transformationMatrixData);
	
	sprite->Draw(texture);

	model->Draw(texture, *camera->transformationMatrixData);*/

	Vector3 axis = Normalize({ 1.0f, 1.0f, 1.0f });
	float angle = 0.44f;
	Matrix4x4 rotateMatrix = MakeRotateAxisAngle(axis, angle);

	ImGui::Begin("rotateMatrix");
	ImGui::DragFloat("Matrix[0][0]",rotateMatrix.m[0]);
	ImGui::End();

	imgui->Draw();

}

void GameScene::Release(){
	imgui->Release();
}
