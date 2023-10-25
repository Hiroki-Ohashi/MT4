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
	void CreateDirectionalResource(DirectXCommon* dir_, Mesh* mesh_);

	Material* GetMaterialDataSphere() { return materialDataSphere; }
	DirectionalLight* GetdirectionalLightData() { return directionalLightData; }
private:
	ID3D12Resource* vertexResourceSphere;
	ID3D12Resource* materialResourceSphere;
	ID3D12Resource* wvpResourceSphere;
	ID3D12Resource* directionalLightResource;

	D3D12_VERTEX_BUFFER_VIEW vertexBufferViewSphere{};

	VertexData* vertexDataSphere;
	Material* materialDataSphere;
	TransformationMatrix* wvpResourceDataSphere;

	Transform transformSphere;
	TransformationMatrix* worldMatrixSphere;

	const uint32_t kSubdivision = 16; //分割数
	uint32_t vertexIndex = (kSubdivision * kSubdivision) * 6;

	bool useMonsterBoll_;

	DirectionalLight* directionalLightData;
};