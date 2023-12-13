#include "GameScene.h"

GameScene::~GameScene(){
	
}

void GameScene::Initialize(){

}

void GameScene::Update(){
	Quaternion rotation = MakeRotateAxisAngleQuaternion(Normalize(Vector3{ 1.0f, 0.4f, -0.2f }), 0.45f);
	Vector3 pointY = { 2.1f, -0.9f, 1.3f };
	Matrix4x4 rotateMatrix = MakeRotateMatrix(rotation);
	Vector3 rotateByQuaternion = RotateVector(pointY, rotation);
	Vector3 rotateByMatrix = Transforme(pointY, rotateMatrix);

	ImGui::Begin("rotation");
	ImGui::Text("% 6.02f, % 6.02f, % 6.02f, % 6.02f", rotation.x, rotation.y, rotation.z, rotation.w);
	ImGui::End();

	ImGui::Begin("rotateMatrix");
	ImGui::Text("% 6.03f, % 6.03f, % 6.03f, % 6.03f", rotateMatrix.m[0][0], rotateMatrix.m[0][1], rotateMatrix.m[0][2], rotateMatrix.m[0][3]);
	ImGui::Text("% 6.03f, % 6.03f, % 6.03f, % 6.03f", rotateMatrix.m[1][0], rotateMatrix.m[1][1], rotateMatrix.m[1][2], rotateMatrix.m[1][3]);
	ImGui::Text("% 6.03f, % 6.03f, % 6.03f, % 6.03f", rotateMatrix.m[2][0], rotateMatrix.m[2][1], rotateMatrix.m[2][2], rotateMatrix.m[2][3]);
	ImGui::Text("% 6.03f, % 6.03f, % 6.03f, % 6.03f", rotateMatrix.m[3][0], rotateMatrix.m[3][1], rotateMatrix.m[3][2], rotateMatrix.m[3][3]);
	ImGui::End();

	ImGui::Begin("rotateByQuaternion");
	ImGui::Text("% 6.02f, % 6.02f, % 6.02f", rotateByQuaternion.x, rotateByQuaternion.y, rotateByQuaternion.z);
	ImGui::End();

	ImGui::Begin("rotateByMatrix");
	ImGui::Text("% 6.02f, % 6.02f, % 6.02f", rotateByMatrix.x, rotateByMatrix.y, rotateByMatrix.z);
	ImGui::End();

}

void GameScene::Draw(){

	
}

void GameScene::Release(){
}
