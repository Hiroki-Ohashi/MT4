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

class Sphere {
public:
	void Initialize(DirectXCommon* dir_, Mesh* mesh_);

	void Update(const Matrix4x4& transformationMatrixData);

	void Draw(DirectXCommon* dir_, Mesh* mesh_);

	void Release();

	void CreateVertexResourceSphere(DirectXCommon* dir_, Mesh* mesh_);
	void CreateMaterialResourceSphere(DirectXCommon* dir_, Mesh* mesh_);
	void CreateTransformationMatrixResourceSphere(DirectXCommon* dir_, Mesh* mesh_);
	void CreateDirectionalResource(DirectXCommon* dir_, Mesh* mesh_);

	Material* GetMaterialDataSphere() { return materialDataSphere; }
	DirectionalLight* GetDirectionalLightData(){return directionalLightData;}

private:
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResourceSphere;
	Microsoft::WRL::ComPtr<ID3D12Resource> materialResourceSphere;
	Microsoft::WRL::ComPtr<ID3D12Resource> wvpResourceSphere;
	Microsoft::WRL::ComPtr<ID3D12Resource> directionalLightResource;

	D3D12_VERTEX_BUFFER_VIEW vertexBufferViewSphere{};

	VertexData* vertexDataSphere;
	Material* materialDataSphere;
	TransformationMatrix* wvpResourceDataSphere;

	Transform transformSphere;
	Transform uvTransformSphere;
	TransformationMatrix* worldMatrixSphere;

	const uint32_t kSubdivision = 64; //分割数
	uint32_t vertexIndex = (kSubdivision * kSubdivision) * 6;

	bool useMonsterBoll_ = true;

	DirectionalLight* directionalLightData;
};