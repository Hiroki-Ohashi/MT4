#pragma once
#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include <cstdint>
#include "Function.h"
#include "MathFunction.h"


#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

class DirectXCommon;

class Triangle {
public:

	ID3D12Resource* CreateBufferResource(ID3D12Device* device, size_t sizeInbytes);

	void CreateVertexResource(DirectXCommon* dir_, Vector4* pos);

	void CreateMaterialResource(DirectXCommon* dir_);

	void CreateWVPResource(DirectXCommon* dir_);

	// 初期化
	void Initialize(DirectXCommon* dir_, Vector4* pos);
	// 読み込み
	void Update();
	// 描画
	void Draw(DirectXCommon* dir_);
	// 解放
	void Release();

public:

	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
	D3D12_VERTEX_BUFFER_VIEW materialBufferView{};

	ID3D12Resource* vertexResource;
	ID3D12Resource* materialResource;
	ID3D12Resource* wvpResource;

	VertexData* vertexData;
	Vector4* materialData;
	Matrix4x4* wvpData;

	static inline HRESULT hr_;
};