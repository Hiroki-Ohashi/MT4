#include "Sprite.h"

void Sprite::Initialize(DirectXCommon* dir_, Mesh* mesh_){

	Sprite::CreateVertexResourceSprite(dir_, mesh_);
	Sprite::CreateTransformationMatrixResourceSprite(dir_, mesh_);

	transformSprite = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
}

void Sprite::Update(WinApp* winapp_){
	Matrix4x4 worldMatrixSprite = MakeAffineMatrix(transformSprite.scale, transformSprite.rotate, transformSprite.translate);
	Matrix4x4 viewMatrixSprite = MakeIndentity4x4();
	Matrix4x4 projectionMatrixSprite = MakeOrthographicMatrix(0.0f, 0.0f, float(winapp_->kClientWidth), float(winapp_->kClientHeight), 0.0f, 100.0f);
	Matrix4x4 worldViewProjectionMatrixSprite = Multiply(worldMatrixSprite, Multiply(viewMatrixSprite, projectionMatrixSprite));
	*transformationMatrixDataSprite = worldViewProjectionMatrixSprite;
}

void Sprite::Draw(DirectXCommon* dir_, Mesh* mesh_){
	// Spriteの描画。変更が必要なものだけ変更する
	dir_->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferViewSprite); // VBVを設定
	// TransformationMatrixCBufferの場所を設定
	dir_->GetCommandList()->SetGraphicsRootConstantBufferView(1, transformationMatrixResourceSprite->GetGPUVirtualAddress());
	// 描画(DrawCall/ドローコール)
	dir_->GetCommandList()->DrawInstanced(6, 1, 0, 0);
}

void Sprite::Release(){
	vertexResourceSprite->Release();
	transformationMatrixResourceSprite->Release();
}

void Sprite::CreateVertexResourceSprite(DirectXCommon* dir_, Mesh* mesh_){
	// Sprite用の頂点リソースを作る
	vertexResourceSprite = mesh_->CreateBufferResource(dir_->GetDevice(), sizeof(VertexData) * 6);

	// リソースの先頭のアドレスから使う
	vertexBufferViewSprite.BufferLocation = vertexResourceSprite->GetGPUVirtualAddress();
	// 使用するリソースのサイズは頂点6つ分のサイズ
	vertexBufferViewSprite.SizeInBytes = sizeof(VertexData) * 6;
	// 1頂点あたりのサイズ
	vertexBufferViewSprite.StrideInBytes = sizeof(VertexData);

	vertexResourceSprite->Map(0, nullptr, reinterpret_cast<void**>(&vertexDataSprite));

	// 1枚目の三角形
	vertexDataSprite[0].position = { 0.0f, 360.0f, 0.0f, 1.0f }; // 左下
	vertexDataSprite[0].texcoord = { 0.0f, 1.0f };
	vertexDataSprite[1].position = { 0.0f, 0.0f, 0.0f, 1.0f }; // 左上
	vertexDataSprite[1].texcoord = { 0.0f, 0.0f };
	vertexDataSprite[2].position = { 640.0f, 360.0f, 0.0f, 1.0f }; // 右下
	vertexDataSprite[2].texcoord = { 1.0f, 1.0f };
	// 2枚目の三角形
	vertexDataSprite[3].position = { 0.0f, 0.0f, 0.0f, 1.0f }; // 左上
	vertexDataSprite[3].texcoord = { 0.0f, 0.0f };
	vertexDataSprite[4].position = { 640.0f, 0.0f, 0.0f, 1.0f }; // 右上
	vertexDataSprite[4].texcoord = { 1.0f, 0.0f };
	vertexDataSprite[5].position = { 640.0f, 360.0f, 0.0f, 1.0f }; // 右下
	vertexDataSprite[5].texcoord = { 1.0f, 1.0f };
}


void Sprite::CreateTransformationMatrixResourceSprite(DirectXCommon* dir_, Mesh* mesh_){
	// Sprite用のTransformationMatrix用のリソースを作る。Matrix4x4 1つ分のサイズを用意する
	transformationMatrixResourceSprite = mesh_->CreateBufferResource(dir_->GetDevice(), sizeof(Matrix4x4));

	// 書き込むためのアドレスを取得
	transformationMatrixResourceSprite->Map(0, nullptr, reinterpret_cast<void**>(&transformationMatrixDataSprite));

	// 単位行列を書き込んでおく
	*transformationMatrixDataSprite = MakeIndentity4x4();
}
