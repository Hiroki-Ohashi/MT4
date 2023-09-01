#pragma once
#include <Windows.h>
#include <cstdint>
#include "Function.h"
#include "MathFunction.h"

class WinApp;
class DirectXCommon;

class Mesh {
public:
	Mesh();
	~Mesh();

	void Initialize(DirectXCommon* dir_);

	void Pso(DirectXCommon* dir_);

	void VertexDraw(DirectXCommon* dir_, Vector4* pos);

	void Update(DirectXCommon* dir_);

	void Viewport();
	void Scissor();

	void UploadTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages);

	void Release();

	ID3D12Resource* CreateTextureResource(ID3D12Device* device, const DirectX::TexMetadata& metadata);

public:
	IDxcUtils* dxcUtils = nullptr;
	IDxcCompiler3* dxcCompiler = nullptr;
	IDxcIncludeHandler* includeHandler = nullptr;


	ID3DBlob* signatureBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;
	ID3D12RootSignature* rootSignature = nullptr;
	ID3D12PipelineState* graphicsPipelineState = nullptr;

	ID3D12Resource* textureResource;

	IDxcBlob* vertexShaderBlob;
	IDxcBlob* pixelShaderBlob;

	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
	D3D12_VERTEX_BUFFER_VIEW materialBufferView{};

	D3D12_ROOT_PARAMETER rootParameters[3] = {};

	D3D12_VIEWPORT viewport{};
	D3D12_RECT scissorRect{};

	D3D12_CPU_DESCRIPTOR_HANDLE textureSrvHandleCPU;
	D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU;

	static inline HRESULT hr_;

	static WinApp* window_;
};