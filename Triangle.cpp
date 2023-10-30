#include "Triangle.h"

void Triangle::Initialize(DirectXCommon* dir_, Mesh* mesh_, Vector4* pos){

	Triangle::CreateVertexResource(dir_, mesh_, pos);
	Triangle::CreateMaterialResource(dir_, mesh_);
	Triangle::CreateWVPResource(dir_, mesh_);

	transform = { {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} };
}

void Triangle::Update(const Matrix4x4& transformationMatrixData){
	transform.rotate.y += 0.03f;

	wvpData->World = MakeAffineMatrix(transform.scale, transform.rotate, transform.translate);
	wvpData->World = Multiply(wvpData->World, transformationMatrixData);
	wvpData->WVP = wvpData->World;
}

void Triangle::Draw(DirectXCommon* dir_, Mesh* mesh_){
	dir_->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferView);
	// 形状を設定。PSOに設定しているものとはまた別。同じものを設定すると考えておけば良い
	dir_->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// マテリアルCBufferの場所を設定
	dir_->GetCommandList()->SetGraphicsRootConstantBufferView(0, materialResource->GetGPUVirtualAddress());
	// wvp用のCBufferの場所を設定
	dir_->GetCommandList()->SetGraphicsRootConstantBufferView(1, wvpResource->GetGPUVirtualAddress());
	// SRVのDescriptorTableの先頭を設定。2はrootParameter[2]である。
	dir_->GetCommandList()->SetGraphicsRootDescriptorTable(2, mesh_->textureSrvHandleGPU);
	// 描画(DrawCall/ドローコール)。3頂点で1つのインスタンス。
	//dir_->GetCommandList()->DrawInstanced(6, 1, 0, 0);
}

void Triangle::Release(){
	vertexResource->Release();
	materialResource->Release();
	wvpResource->Release();
}

void Triangle::CreateVertexResource(DirectXCommon* dir_, Mesh* mesh_, Vector4* pos){
	// 頂点用のリソースを作る。今回はcolor1つ分のサイズを用意する
	vertexResource = mesh_->CreateBufferResource(dir_->GetDevice(), sizeof(VertexData) * 6);

	// リソースの先頭のアドレスから使う
	vertexBufferView.BufferLocation = vertexResource->GetGPUVirtualAddress();
	// 使用するリソースのサイズは頂点3つ分のサイズ
	vertexBufferView.SizeInBytes = sizeof(VertexData) * 6;
	// 1頂点あたりのサイズ
	vertexBufferView.StrideInBytes = sizeof(VertexData);

	// 頂点リソースにデータを書き込む
	vertexData = nullptr;
	// 書き込むためのアドレスを取得
	vertexResource->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	//// 左下
	//vertexData[0] = { -0.1f, -0.1f, 0.0f, 1.0f };
	//// 上
	//vertexData[1] = { 0.0f, 0.1f, 0.0f, 1.0f };
	//// 右上
	//vertexData[2] = { 0.1f, -0.1f, 0.0f, 1.0f };

	// 左下
	vertexData[0].position = pos[0];
	vertexData[0].texcoord = { 0.0f, 1.0f };

	vertexData[0].normal.x = vertexData[0].position.x;
	vertexData[0].normal.y = vertexData[0].position.y;
	vertexData[0].normal.z = vertexData[0].position.z;

	// 上
	vertexData[1].position = pos[1];
	vertexData[1].texcoord = { 0.5f, 0.0f };

	vertexData[1].normal.x = vertexData[1].position.x;
	vertexData[1].normal.y = vertexData[1].position.y;
	vertexData[1].normal.z = vertexData[1].position.z;

	// 右上
	vertexData[2].position = pos[2];
	vertexData[2].texcoord = { 1.0f, 1.0f };

	vertexData[2].normal.x = vertexData[2].position.x;
	vertexData[2].normal.y = vertexData[2].position.y;
	vertexData[2].normal.z = vertexData[2].position.z;

	// 左下2
	vertexData[3].position = pos[0];
	vertexData[3].texcoord = { 0.0f, 1.0f };

	vertexData[3].normal.x = vertexData[3].position.x;
	vertexData[3].normal.y = vertexData[3].position.y;
	vertexData[3].normal.z = vertexData[3].position.z;

	// 上2
	vertexData[4].position = pos[1];
	vertexData[4].texcoord = { 0.5f, 0.0f };

	vertexData[4].normal.x = vertexData[4].position.x;
	vertexData[4].normal.y = vertexData[4].position.y;
	vertexData[4].normal.z = vertexData[4].position.z;

	// 右上2
	vertexData[5].position = pos[2];
	vertexData[5].texcoord = { 1.0f, 1.0f };

	vertexData[5].normal.x = vertexData[4].position.x;
	vertexData[5].normal.y = vertexData[4].position.y;
	vertexData[5].normal.z = vertexData[4].position.z;

}

void Triangle::CreateMaterialResource(DirectXCommon* dir_, Mesh* mesh_){
	// マテリアル用のリソースを作る。今回はcolor1つ分のサイズを用意する
	materialResource = mesh_->Mesh::CreateBufferResource(dir_->GetDevice(), sizeof(Material));
	// マテリアルにデータを書き込む
	materialData = nullptr;
	// 書き込むためのアドレスを取得
	materialResource->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
	// 白を設定
	materialData->color = { 1.0f, 1.0f, 1.0f, 1.0f };

	materialData->enableLighting = false;
	materialData->uvTransform = MakeIndentity4x4();
}

void Triangle::CreateWVPResource(DirectXCommon* dir_, Mesh* mesh_){
	// WVP用のリソースを作る。Matrix4x4 1つ分のサイズを用意する
	wvpResource = mesh_->CreateBufferResource(dir_->GetDevice(), sizeof(TransformationMatrix));
	// 書き込むためのアドレスを取得
	wvpResource->Map(0, nullptr, reinterpret_cast<void**>(&wvpData));
	// 単位行列を書き込んでおく
	wvpData->WVP = MakeIndentity4x4();
}