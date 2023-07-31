#pragma once
#include <Windows.h>
#include <cstdint>
#include "Function.h"
#include "MathFunction.h"

class WinApp;
class DirectXManeger;

class Triangle {
public:
	Triangle();
	~Triangle();

	void DxcInitialize();

	void DxcPso(DirectXManeger* dir_);

	void DxcVertexDraw(DirectXManeger* dir_, Vector4* pos);
	void DxcUpdate(DirectXManeger* dir_);

	void DxcViewport();
	void DxcScissor();

	void UploadTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages);

	void DxcRelease();


	ID3D12Resource* CreateBufferResource(ID3D12Device* device, size_t sizeInbytes);
	ID3D12Resource* CreateTextureResource(ID3D12Device* device, const DirectX::TexMetadata& metadata);

	IDxcUtils* dxcUtils = nullptr;
	IDxcCompiler3* dxcCompiler = nullptr;
	IDxcIncludeHandler* includeHandler = nullptr;


	ID3DBlob* signatureBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;
	ID3D12RootSignature* rootSignature = nullptr;
	ID3D12PipelineState* graphicsPipelineState = nullptr;

	D3D12_HEAP_PROPERTIES uploadHeapProperties{};

	ID3D12Resource* vertexResource;
	ID3D12Resource* materialResource;
	ID3D12Resource* wvpResource;

	VertexData* vertexData;
	Vector4* materialData;
	Matrix4x4* wvpData;

	ID3D12Resource* textureResource;

	IDxcBlob* vertexShaderBlob;
	IDxcBlob* pixelShaderBlob;

	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
	D3D12_VERTEX_BUFFER_VIEW materialBufferView{};

	D3D12_VIEWPORT viewport{};
	D3D12_RECT scissorRect{};

	D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU;

	static inline HRESULT hr_;

	static WinApp* window_;
};