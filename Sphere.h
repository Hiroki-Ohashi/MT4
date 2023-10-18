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

	void Update(const Matrix4x4& transformationMatrixData, bool useMonsterBoll);

	void Draw(DirectXCommon* dir_, Mesh* mesh_);

	void Release();

	void CreateVertexResourceSphere(DirectXCommon* dir_, Mesh* mesh_);
	void CreateMaterialResourceSphere(DirectXCommon* dir_, Mesh* mesh_);
	void CreateTransformationMatrixResourceSphere(DirectXCommon* dir_, Mesh* mesh_);

	Material* GetMaterialDataSphere() { return materialDataSphere; }

private:
	ID3D12Resource* vertexResourceSphere;
	ID3D12Resource* materialResourceSphere;
	ID3D12Resource* transformationMatrixResourceSphere;

	D3D12_VERTEX_BUFFER_VIEW vertexBufferViewSphere{};

	VertexData* vertexDataSphere;
	Material* materialDataSphere;
	Matrix4x4* transformationMatrixDataSphere;

	Transform transformSphere;
	Matrix4x4 worldMatrixSphere;

	uint32_t latIndex = 16;
	uint32_t lonIndex = 16;
	uint32_t kSubdivision = 16;
	
	int32_t startIndex = (latIndex * kSubdivision + lonIndex) * 6;

	DirectionalLight directionalLightData;

	bool useMonsterBoll_;
};