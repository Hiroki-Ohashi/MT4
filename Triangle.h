#pragma once
#include <Windows.h>
#include <cstdint>
#include "WinApp.h"
#include "Function.h"
#include "Triangle.h"
#include "DirectX.h"



class Triangle {
public: 
	static void DxcInitialize();

	static void DxcPso();

	static void DxcVertexDraw();

	static void DxcViewport();
	static void DxcScissor();

	struct Vector4 final {
		float x;
		float y;
		float z;
		float w;
	};

	static inline ID3D12RootSignature* GetRootSignature() { return rootSignature; }
	static inline ID3D12PipelineState* GetGraphicsPipelineState() { return graphicsPipelineState; }
	static inline D3D12_VERTEX_BUFFER_VIEW GetVertexBufferView() { return vertexBufferView; }

	static inline ID3D12Resource* GetVertexResource() { return vertexResource; }
	static inline ID3DBlob* GetSignatureBlob() { return signatureBlob; }
	static inline ID3DBlob* GetErrorBlob() { return errorBlob; }
	static inline IDxcBlob* GetVertexShaderBlob() { return vertexShaderBlob; }
	static inline IDxcBlob* GetPixelShaderBlob() { return pixelShaderBlob; }

	static inline D3D12_VIEWPORT Getviewport() { return viewport; }
	static inline D3D12_RECT GetScissorRect() { return scissorRect; }


	static inline IDxcUtils* dxcUtils = nullptr;
	static inline IDxcCompiler3* dxcCompiler = nullptr;
	static inline IDxcIncludeHandler* includeHandler = nullptr;

	static inline ID3D12Resource* vertexResource = nullptr;
	static inline ID3DBlob* signatureBlob = nullptr;
	static inline ID3DBlob* errorBlob = nullptr;
	static inline ID3D12RootSignature* rootSignature = nullptr;
	static inline ID3D12PipelineState* graphicsPipelineState = nullptr;

	static inline Vector4* vertexData = nullptr;

	static inline IDxcBlob* vertexShaderBlob;
	static inline IDxcBlob* pixelShaderBlob;

	static inline D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};

	static inline D3D12_VIEWPORT viewport{};
	static inline D3D12_RECT scissorRect{};

	static inline HRESULT hr_;

	static WinApp* window_;
};