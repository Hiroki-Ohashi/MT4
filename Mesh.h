#pragma once

#include <Windows.h>
#include <cstdint>
#include <string>
#include <format>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include <dxgidebug.h>
#include <dxcapi.h>
#include "WinApp.h"
#include "Function.h"
#include "DirectXCommon.h"

class Mesh {
public:
	void Initialize(DirectXCommon* dir_);

	void CreatePso(DirectXCommon* dir_);

	void Update(DirectXCommon* dir_);

	void Viewport();
	void Scissor();

	void Release();

	ID3D12Resource* CreateTextureResource(ID3D12Device* device, const DirectX::TexMetadata& metadata);
	ID3D12Resource* CreateBufferResource(ID3D12Device* device, size_t sizeInbytes);
	DirectX::ScratchImage LoadTexture(const std::string& filePath);

	void UploadTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages);

	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(ID3D12DescriptorHeap* descriptorHeap, uint32_t descriptorSize, uint32_t index);
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(ID3D12DescriptorHeap* descriptorHeap, uint32_t descriptorSize, uint32_t index);

public:
	IDxcUtils* dxcUtils = nullptr;
	IDxcCompiler3* dxcCompiler = nullptr;
	IDxcIncludeHandler* includeHandler = nullptr;


	ID3DBlob* signatureBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;
	ID3D12RootSignature* rootSignature = nullptr;
	ID3D12PipelineState* graphicsPipelineState = nullptr;
	D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc{};

	IDxcBlob* vertexShaderBlob;
	IDxcBlob* pixelShaderBlob;

	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
	D3D12_VERTEX_BUFFER_VIEW materialBufferView{};

	D3D12_ROOT_PARAMETER rootParameters[3] = {};

	D3D12_DESCRIPTOR_RANGE descriptorRange[1] = {};

	D3D12_STATIC_SAMPLER_DESC staticSamplers[1] = {};
	D3D12_INPUT_ELEMENT_DESC inputElementDescs[2] = {};

	D3D12_VIEWPORT viewport{};
	D3D12_RECT scissorRect{};

	static inline HRESULT hr_;

	static WinApp* window_;

	ID3D12Resource* textureResource;
	ID3D12Resource* textureResource2;

	D3D12_CPU_DESCRIPTOR_HANDLE textureSrvHandleCPU;
	D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU;

	D3D12_CPU_DESCRIPTOR_HANDLE textureSrvHandleCPU2;
	D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU2;

};