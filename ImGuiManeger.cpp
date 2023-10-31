#include "ImGuiManeger.h"
#include "DirectXCommon.h"
#include "WinApp.h"
#include <Windows.h>
#include <cstdint>
#include <d3d12.h>
#include "externals/imgui/imgui.h"
#include "externals/imgui/imgui_impl_dx12.h"
#include "externals/imgui/imgui_impl_win32.h"

void ImGuiManeger::Initialize(WinApp* winApp_, DirectXCommon* dir_){
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(winApp_->hwnd);
	ImGui_ImplDX12_Init(dir_->GetDevice(),
		dir_->GetSwapChainDesc().BufferCount,
		dir_->GetRtvDesc().Format,
		dir_->GetSrvDescriptorHeap(),
		dir_->GetSrvDescriptorHeap()->GetCPUDescriptorHandleForHeapStart(),
		dir_->GetSrvDescriptorHeap()->GetGPUDescriptorHandleForHeapStart()
	);
}

void ImGuiManeger::Update(){
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void ImGuiManeger::Draw(DirectXCommon* dir_){
	// 開発用UIの処理。実際に開発用のUIを出す場合はココをゲーム固有の処理に置き換える
	//ImGui::ShowDemoWindow();
	// ImGuiの内部コマンドを生成する
	ImGui::Render();
	// 実際にcommandListのImGuiの描画コマンドを積む
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), dir_->GetCommandList());
}

void ImGuiManeger::Release(){
	// Cleanup
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}
