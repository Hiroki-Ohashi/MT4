#pragma once
#include <Windows.h>
#include <cstdint>
#include "Function.h"
#include "MathFunction.h"

class WinApp;
class DirectXCommon;

class Mesh {
public:
	void Initialize(DirectXCommon* dir_);

	void Pso(DirectXCommon* dir_);

	void Update(DirectXCommon* dir_);

	void Viewport();
	void Scissor();

	void Release();

public:
	IDxcUtils* dxcUtils = nullptr;
	IDxcCompiler3* dxcCompiler = nullptr;
	IDxcIncludeHandler* includeHandler = nullptr;


	ID3DBlob* signatureBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;
	ID3D12RootSignature* rootSignature = nullptr;
	ID3D12PipelineState* graphicsPipelineState = nullptr;

	IDxcBlob* vertexShaderBlob;
	IDxcBlob* pixelShaderBlob;

	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
	D3D12_VERTEX_BUFFER_VIEW materialBufferView{};

	D3D12_ROOT_PARAMETER rootParameters[3] = {};

	D3D12_VIEWPORT viewport{};
	D3D12_RECT scissorRect{};

	static inline HRESULT hr_;

	static WinApp* window_;
};