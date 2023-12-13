#include "GameScene.h"

GameScene::~GameScene(){
	
}

void GameScene::Initialize(){

}

void GameScene::Update(){
	Quaternion q1 = { 2.0f,3.0f,4.0f,1.0f };
	Quaternion q2 = { 1.0f,3.0f,5.0f,2.0f };
	Quaternion identity = IdentityQuaternion();
	Quaternion conj = Conjugate(q1);
	Quaternion inv = Inverse(q1);
	Quaternion normal = Normalize(q1);
	Quaternion mul1 = Multiply(q1, q2);
	Quaternion mul2 = Multiply(q2, q1);
	float norm = Norm(q1);

	ImGui::Begin("IdentityQuaternion");
	ImGui::Text("% 6.02f, % 6.02f, % 6.02f, % 6.02f", identity.x, identity.y, identity.z, identity.w);
	ImGui::End();

	ImGui::Begin("Conjugate");
	ImGui::Text("% 6.02f, % 6.02f, % 6.02f, % 6.02f", conj.x, conj.y, conj.z, conj.w);
	ImGui::End();

	ImGui::Begin("Inverse");
	ImGui::Text("% 6.02f, % 6.02f, % 6.02f, % 6.02f", inv.x, inv.y, inv.z, inv.w);
	ImGui::End();

	ImGui::Begin("Normalize");
	ImGui::Text("% 6.02f, % 6.02f, % 6.02f, % 6.02f", normal.x, normal.y, normal.z, normal.w);
	ImGui::End();

	ImGui::Begin("Multiply(q1, q2)");
	ImGui::Text("% 6.02f, % 6.02f, % 6.02f, % 6.02f", mul1.x, mul1.y, mul1.z, mul1.w);
	ImGui::End();

	ImGui::Begin("Multiply(q2, q1)");
	ImGui::Text("% 6.02f, % 6.02f, % 6.02f, % 6.02f", mul2.x, mul2.y, mul2.z, mul2.w);
	ImGui::End();

	ImGui::Begin("Norm");
	ImGui::Text("% 6.02f", norm);
	ImGui::End();
}

void GameScene::Draw(){

	
}

void GameScene::Release(){
}
