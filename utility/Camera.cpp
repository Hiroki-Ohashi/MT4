#include "Camera.h"
#include "imgui.h"


Camera* Camera::GetInstance()
{
	static Camera instance;
	return &instance;
}

void Camera::Initialize(){
	cameraTransform = { {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, -10.0f} };
}

void Camera::Update(){
	worldMatrix = MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, -5.0f });
	cameraMatrix = MakeAffineMatrix(cameraTransform.scale, cameraTransform.rotate, cameraTransform.translate);
	viewMatrix = Inverse(cameraMatrix);
	projectionMatrix = MakePerspectiveMatrix(0.45f, float(winapp_->GetKClientWidth()) / float(winapp_->GetKClientHeight()), 0.1f, 100.0f);
	worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
	transformationMatrixData = &worldViewProjectionMatrix;

	if (ImGui::TreeNode("Camera")) {
		ImGui::DragFloat3("Camera Transform", &cameraTransform.translate.x, 0.01f, -50.0f, 50.0f);
		ImGui::TreePop();
	}
}

void Camera::Draw(){}
