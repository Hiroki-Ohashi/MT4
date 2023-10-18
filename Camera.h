#pragma once
#include "Function.h"
#include "MathFunction.h"
#include "WinApp.h"

class Camera {
public:
	void Initialize();

	void Update();

	void Draw();
public:

	static WinApp* winapp_;

	Transform cameraTransform;
	Matrix4x4 worldMatrix;
	Matrix4x4 cameraMatrix;
	Matrix4x4 viewMatrix;
	Matrix4x4 projectionMatrix;
	Matrix4x4 worldViewProjectionMatrix;
	Matrix4x4* transformationMatrixData;
};
