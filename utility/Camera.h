#pragma once
#include "Function.h"
#include "MathFunction.h"
#include "WinApp.h"

class Camera {
public:

	static Camera* GetInstance();

	void Initialize();

	void Update();

	void Draw();

	const Matrix4x4* GetTransformationMatrixData() { return transformationMatrixData; }
private:

	static WinApp* winapp_;

	Transform cameraTransform;
	Matrix4x4 worldMatrix;
	Matrix4x4 cameraMatrix;
	Matrix4x4 viewMatrix;
	Matrix4x4 projectionMatrix;
	Matrix4x4 worldViewProjectionMatrix;
	Matrix4x4* transformationMatrixData;
};
