#pragma once
#include <Windows.h>
#include <cstdint>
#include "Function.h"

class WinApp;
class DirectX;

class Triangle {
public: 
	Triangle();
	~Triangle();

	void DxcInitialize();

	void DxcPso(DirectX* dir_);

	void DxcVertexDraw(DirectX* dir_, Vector4* pos);
	void DxcUpdate(DirectX* dir_);

	void DxcViewport();
	void DxcScissor();

	void DxcRelease();


	IDxcUtils* dxcUtils = nullptr;
	IDxcCompiler3* dxcCompiler = nullptr;
	IDxcIncludeHandler* includeHandler = nullptr;

	ID3D12Resource* vertexResource = nullptr;
	ID3DBlob* signatureBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;
	ID3D12RootSignature* rootSignature = nullptr;
	ID3D12PipelineState* graphicsPipelineState = nullptr;

	Vector4* vertexData = nullptr;

	IDxcBlob* vertexShaderBlob;
	IDxcBlob* pixelShaderBlob;

	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};

	D3D12_VIEWPORT viewport{};
	D3D12_RECT scissorRect{};

	static inline HRESULT hr_;

	static WinApp* window_;
};