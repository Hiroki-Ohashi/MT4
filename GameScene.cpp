#include "GameScene.h"

GameScene::GameScene(){

}

GameScene::~GameScene(){
	for (int i = 0; i < Max; i++) {
		delete triangle[i];
	}
	delete sprite;
	delete sphere;
	delete mesh;
	delete model;
	delete camera;
	delete imgui;
}

void GameScene::Initialize(){

	mesh = new Mesh();
	mesh->Initialize();

	sprite = new Sprite();
	sprite->Initialize(mesh);

	sphere = new Sphere();
	sphere->Initialize(mesh);

	model = new Model();
	model->Initialize(mesh);

	imgui = new ImGuiManeger();
	imgui->Initialize();

	camera = new Camera();
	camera->Initialize();

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
		triangle[i]->Initialize(mesh, pos[i]);
	}
}

void GameScene::Update(){
	imgui->Update();
	mesh->Update();
	sprite->Update();
	camera->Update();
	sphere->Update(*camera->transformationMatrixData);
	model->Update(*camera->transformationMatrixData);

	for (int i = 0; i < 2; i++) {
		triangle[i]->Update(*camera->transformationMatrixData);
	}
}

void GameScene::Draw(){
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

}

void GameScene::Release(){
	mesh->Release();
	imgui->Release();
}
