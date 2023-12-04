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
#include "Mesh.h"
#include "TextureManager.h"

class Triangle {
public:

	// 初期化
	void Initialize(const std::string& filePath, Vector4* pos);
	// 読み込み
	void Update();
	// 描画
	void Draw(const Matrix4x4& transformationMatrixData);
	// 解放
	void Release();

	void CreateVertexResource(Vector4* pos);
	void CreateMaterialResource();
	void CreateWVPResource();

	Microsoft::WRL::ComPtr<ID3D12Resource> CreateBufferResource(Microsoft::WRL::ComPtr<ID3D12Device> device, size_t sizeInbytes);

	Material* GetMaterialData() { return materialData; }
	bool GetTriangle() { return isTriangle; }
	void SetIsTriangle(bool isTriangle_) { isTriangle_ = isTriangle; }

private:
	TextureManager* texture_ = TextureManager::GetInstance();

	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};

	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource;
	Microsoft::WRL::ComPtr<ID3D12Resource> materialResource;
	Microsoft::WRL::ComPtr<ID3D12Resource> wvpResource;

	VertexData* vertexData;
	Material* materialData;
	TransformationMatrix* wvpData;

	Transform transform;

	Matrix4x4 worldMatrix;

	bool isTriangle = false;

	static inline HRESULT hr_;

	uint32_t texture;
};