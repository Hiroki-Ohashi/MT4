#pragma once
#include "Function.h"
#include "MathFunction.h"
#include "WinApp.h"

class Camera {
public:
	void Initialize();

	void Update(WinApp* winapp_);

	void Draw();
public:
	Transform cameraTransform;
	Matrix4x4 worldMatrix;
	Matrix4x4 cameraMatrix;
	Matrix4x4 viewMatrix;
	Matrix4x4 projectionMatrix;
	Matrix4x4 worldViewProjectionMatrix;
	Matrix4x4* transformationMatrixData;
};
