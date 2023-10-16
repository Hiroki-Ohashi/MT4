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

class Mesh;

class Triangle {
public:

	// 初期化
	void Initialize(DirectXCommon* dir_, Mesh* mesh_, Vector4* pos);
	// 読み込み
	void Update(const Matrix4x4& transformationMatrixData);
	// 描画
	void Draw(DirectXCommon* dir_, Mesh* mesh_);
	// 解放
	void Release();

	void CreateVertexResource(DirectXCommon* dir_, Mesh* mesh_, Vector4* pos);
	void CreateMaterialResource(DirectXCommon* dir_, Mesh* mesh_);
	void CreateWVPResource(DirectXCommon* dir_, Mesh* mesh_);

public:

	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
	D3D12_VERTEX_BUFFER_VIEW materialBufferView{};

	ID3D12Resource* vertexResource;
	ID3D12Resource* materialResource;
	ID3D12Resource* wvpResource;

	VertexData* vertexData;
	Vector4* materialData;
	Matrix4x4* wvpData;

	Transform transform;

	Matrix4x4 worldMatrix;

	static inline HRESULT hr_;
};