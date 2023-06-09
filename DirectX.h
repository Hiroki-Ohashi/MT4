#pragma once

#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include <cstdint>
#include "WinApp.h"
#include "Function.h"
#include "Triangle.h"


#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

class DirectX {
public:
	static void Initialize();
	static void Fence();
	static void Update();
	static void Release();

	static inline ID3D12Device* GetDevice() { return device_; }

private:
	static inline IDXGIFactory7* dxgiFactory_ = nullptr;
	static inline ID3D12Device* device_ = nullptr;
	static inline IDXGIAdapter4* useAdapter_ = nullptr;
	static inline ID3D12CommandQueue* commandQueue_ = nullptr;
	static inline ID3D12CommandAllocator* commandAllocator_ = nullptr;
	static inline ID3D12GraphicsCommandList* commandList_ = nullptr;
	static inline IDXGISwapChain4* swapChain_ = nullptr;
	static inline ID3D12DescriptorHeap* rtvDescriptorHeap_ = nullptr;
	static inline D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles[2];
	static inline ID3D12Resource* swapChainResources[2] = { nullptr };
	static inline ID3D12Fence* fence = nullptr;
	static inline uint64_t fenceValue = 0;
	static inline HANDLE fenceEvent = 0;
	static inline HRESULT hr_;

	//static inline HWND hwnd = nullptr;
	static WinApp* window_;
};
