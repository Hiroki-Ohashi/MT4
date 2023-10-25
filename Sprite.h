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

	void Update();

	void Draw(DirectXCommon* dir_, Mesh* mesh_);

	void Release();

	void CreateVertexResourceSprite(DirectXCommon* dir_, Mesh* mesh_);
	void CreateMaterialResourceSprite(DirectXCommon* dir_, Mesh* mesh_);
	void CreateTransformationMatrixResourceSprite(DirectXCommon* dir_, Mesh* mesh_);

	Material* GetMaterialDataSprite() { return materialDataSprite; }

private:

	static WinApp* winapp_;

	ID3D12Resource* vertexResourceSprite;
	ID3D12Resource* materialResourceSprite;
	ID3D12Resource* transformationMatrixResourceSprite;
	ID3D12Resource* indexResourceSprite;

	D3D12_VERTEX_BUFFER_VIEW vertexBufferViewSprite{};
	D3D12_INDEX_BUFFER_VIEW indexBufferViewSprite{};

	VertexData* vertexDataSprite;
	Material* materialDataSprite;
	TransformationMatrix* transformationMatrixDataSprite;
	uint32_t* indexDataSprite;

	Transform transformSprite;
	Transform uvTransformSprite;
};