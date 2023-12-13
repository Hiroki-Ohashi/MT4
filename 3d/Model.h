#pragma once

#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include <cstdint>
#include <fstream>
#include <sstream>
#include "WinApp.h"
#include "Function.h"
#include "MathFunction.h"
#include "DirectXCommon.h"
#include "TextureManager.h"
#include "Mesh.h"
#include "Camera.h"

struct MaterialData {
	std::string textureFilePath;
};

struct ModelData {
	std::vector<VertexData> vertices;
	MaterialData material;
};

class Model {
public:
	void Initialize();

	void Update();

	void Draw(const Matrix4x4& transformationMatrixData, uint32_t index);

	void Release();

	void CreateVertexResource();
	void CreateMaterialResource();
	void CreateWVPResource();
	Microsoft::WRL::ComPtr<ID3D12Resource> CreateBufferResource(Microsoft::WRL::ComPtr<ID3D12Device> device, size_t sizeInbytes);


	ModelData LoadObjFile(const std::string& directoryPath, const std::string& filename);
	MaterialData LoadMaterialTemplateFile(const std::string& directoryPath, const std::string& filename);

private:

	WinApp* winapp_ = WinApp::GetInsTance();
	TextureManager* texture_ = TextureManager::GetInstance();
	Camera* camera_ = Camera::GetInstance();

	ModelData modelData;

	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};

	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource;
	Microsoft::WRL::ComPtr<ID3D12Resource> materialResource;
	Microsoft::WRL::ComPtr<ID3D12Resource> wvpResource;

	VertexData* vertexData;
	Material* materialData;
	TransformationMatrix* wvpData;

	Transform transform;
	Transform uvTransform;

	bool isModel;
};