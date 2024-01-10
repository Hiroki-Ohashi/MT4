#include "GameScene.h"

GameScene::~GameScene(){
	
}

void GameScene::Initialize(){

}

void GameScene::Update(){

	Quaternion rotation0 = MakeRotateAxisAngleQuaternion({ 0.71f, 0.71f, 0.0f }, 0.3f);
	Quaternion rotation1 = MakeRotateAxisAngleQuaternion({ 0.71f, 0.0f, 0.71f }, 3.141592f);
	
	Quaternion interpolate0 = Slerp(rotation0, rotation1, 0.0f);
	Quaternion interpolate1 = Slerp(rotation0, rotation1, 0.3f);
	Quaternion interpolate2 = Slerp(rotation0, rotation1, 0.5f);
	Quaternion interpolate3 = Slerp(rotation0, rotation1, 0.7f);
	Quaternion interpolate4 = Slerp(rotation0, rotation1, 1.0f);

	ImGui::Begin("interpolate0");
	ImGui::Text("% 6.02f, % 6.02f, % 6.02f, % 6.02f", interpolate0.x, interpolate0.y, interpolate0.z, interpolate0.w);
	ImGui::End();

	ImGui::Begin("interpolate1");
	ImGui::Text("% 6.02f, % 6.02f, % 6.02f, % 6.02f", interpolate1.x, interpolate1.y, interpolate1.z, interpolate1.w);
	ImGui::End();

	ImGui::Begin("interpolate2");
	ImGui::Text("% 6.02f, % 6.02f, % 6.02f, % 6.02f", interpolate2.x, interpolate2.y, interpolate2.z, interpolate2.w);
	ImGui::End();

	ImGui::Begin("interpolate3");
	ImGui::Text("% 6.02f, % 6.02f, % 6.02f, % 6.02f", interpolate3.x, interpolate3.y, interpolate3.z, interpolate3.w);
	ImGui::End();

	ImGui::Begin("interpolate4");
	ImGui::Text("% 6.02f, % 6.02f, % 6.02f, % 6.02f", interpolate4.x, interpolate4.y, interpolate4.z, interpolate4.w);
	ImGui::End();

}

void GameScene::Draw(){

	
}

void GameScene::Release(){
}
