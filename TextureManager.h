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

class TextureManager {
public:
	void Initialize();

	uint32_t SetTexture(const std::string& filePath, uint32_t index);

	Microsoft::WRL::ComPtr<ID3D12Resource> CreateTextureResource(Microsoft::WRL::ComPtr<ID3D12Device> device, const DirectX::TexMetadata& metadata);
	DirectX::ScratchImage LoadTexture(const std::string& filePath);

	void UploadTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages);

	D3D12_GPU_DESCRIPTOR_HANDLE GetTextureSRVHandleGPU(uint32_t index) { return textureSrvHandleGPU[index]; }

	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap, uint32_t descriptorSize, uint32_t index);
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap, uint32_t descriptorSize, uint32_t index);

private:

	static const int kMaxTexture = 100;

	// DescriptorSizeを取得しておく
	uint32_t descriptorSizeSRV;

	DirectXCommon* dir_ = DirectXCommon::GetInsTance();

	Microsoft::WRL::ComPtr<ID3D12Resource> textureResource[kMaxTexture];

	D3D12_CPU_DESCRIPTOR_HANDLE textureSrvHandleCPU[kMaxTexture];
	D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU[kMaxTexture];
};