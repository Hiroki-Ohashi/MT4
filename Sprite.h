#pragma once
#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include <cstdint>
#include "WinApp.h"
#include "Function.h"
#include "MathFunction.h"
#include "DirectXCommon.h"
#include "Triangle.h"

class Mesh;

class Sprite {
public:
	void Initialize(DirectXCommon* dir_, Mesh* mesh_);

	void Update(WinApp* winapp_);

	void Draw(DirectXCommon* dir_, Mesh* mesh_);

	void Release();

	void CreateVertexResourceSprite(DirectXCommon* dir_, Mesh* mesh_);
	void CreateMaterialResource(DirectXCommon* dir_, Mesh* mesh_);
	void CreateTransformationMatrixResourceSprite(DirectXCommon* dir_, Mesh* mesh_);

private:
	ID3D12Resource* vertexResourceSprite;
	ID3D12Resource* materialResource;
	ID3D12Resource* transformationMatrixResourceSprite;

	D3D12_VERTEX_BUFFER_VIEW vertexBufferViewSprite{};
	D3D12_VERTEX_BUFFER_VIEW materialBufferView{};

	VertexData* vertexDataSprite;
	Vector4* materialData;
	Matrix4x4* transformationMatrixDataSprite;

	Transform transformSprite;
};