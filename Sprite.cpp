#include "Sprite.h"
#include "externals/imgui/imgui.h"


void Sprite::Initialize(DirectXCommon* dir_, Mesh* mesh_){

	Sprite::CreateVertexResourceSprite(dir_, mesh_);
	Sprite::CreateMaterialResourceSprite(dir_, mesh_);
	Sprite::CreateTransformationMatrixResourceSprite(dir_, mesh_);

	transformSprite = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	uvTransformSprite = {{1.0f, 1.0f, 1.0f},{0.0f, 0.0f, 0.0f},{0.0f, 0.0f, 0.0f},};

	// SpriteはLightingしないのでfalseを設定
	materialDataSprite->enableLighting = false;
}

void Sprite::Update(){
	transformationMatrixDataSprite->World = MakeAffineMatrix(transformSprite.scale, transformSprite.rotate, transformSprite.translate);
	Matrix4x4 viewMatrixSprite = MakeIndentity4x4();
	Matrix4x4 projectionMatrixSprite = MakeOrthographicMatrix(0.0f, 0.0f, float(winapp_->kClientWidth), float(winapp_->kClientHeight), 0.0f, 100.0f);
	Matrix4x4 worldViewProjectionMatrixSprite = Multiply(transformationMatrixDataSprite->World, Multiply(viewMatrixSprite, projectionMatrixSprite));
	transformationMatrixDataSprite->WVP = worldViewProjectionMatrixSprite;

	Matrix4x4 uvtransformMatrix = MakeScaleMatrix(uvTransformSprite.scale);
	uvtransformMatrix = Multiply(uvtransformMatrix, MakeRotateZMatrix(uvTransformSprite.rotate.z));
	uvtransformMatrix = Multiply(uvtransformMatrix, MakeTranslateMatrix(uvTransformSprite.translate));
	materialDataSprite->uvTransform = uvtransformMatrix;
}

void Sprite::Draw(DirectXCommon* dir_, Mesh* mesh_){
	// コマンドを積む
    dir_->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferViewSprite); // VBVを設定
	// Spriteの描画。変更が必要なものだけ変更する
	dir_->GetCommandList()->IASetIndexBuffer(&indexBufferViewSprite);
	// マテリアルCBufferの場所を設定
	dir_->GetCommandList()->SetGraphicsRootConstantBufferView(0, materialResourceSprite->GetGPUVirtualAddress());
	// TransformationMatrixCBufferの場所を設定
	dir_->GetCommandList()->SetGraphicsRootConstantBufferView(1, transformationMatrixResourceSprite->GetGPUVirtualAddress());
	// SRVのDescriptorTableの先頭を設定。2はrootParameter[2]である。
	dir_->GetCommandList()->SetGraphicsRootDescriptorTable(2, mesh_->textureSrvHandleGPU);
	// 描画(DrawCall/ドローコール)
	dir_->GetCommandList()->DrawIndexedInstanced(6, 1, 0, 0, 0);

	ImGui::Begin("UVTransform");
	ImGui::DragFloat2("UVTransform", &uvTransformSprite.translate.x, 0.01f, -10.0f, 10.0f);
	ImGui::DragFloat2("UVScale", &uvTransformSprite.scale.x, 0.01f, -10.0f, 10.0f);
	ImGui::SliderAngle("UVRotate", &uvTransformSprite.rotate.z);
	ImGui::End();
}

void Sprite::Release(){
}

void Sprite::CreateVertexResourceSprite(DirectXCommon* dir_, Mesh* mesh_){
	// Sprite用の頂点リソースを作る
	vertexResourceSprite = mesh_->CreateBufferResource(dir_->GetDevice(), sizeof(VertexData) * 4);

	// リソースの先頭のアドレスから使う
	vertexBufferViewSprite.BufferLocation = vertexResourceSprite->GetGPUVirtualAddress();
	// 使用するリソースのサイズは頂点6つ分のサイズ
	vertexBufferViewSprite.SizeInBytes = sizeof(VertexData) * 4;
	// 1頂点あたりのサイズ
	vertexBufferViewSprite.StrideInBytes = sizeof(VertexData);

	vertexResourceSprite->Map(0, nullptr, reinterpret_cast<void**>(&vertexDataSprite));

	// 三角形
	vertexDataSprite[0].position = { 0.0f, 360.0f, 0.0f, 1.0f }; // 左下
	vertexDataSprite[0].texcoord = { 0.0f, 1.0f };
	vertexDataSprite[0].normal = { 0.0f, 0.0f, -1.0f };

	vertexDataSprite[1].position = { 0.0f, 0.0f, 0.0f, 1.0f }; // 左上
	vertexDataSprite[1].texcoord = { 0.0f, 0.0f };
	vertexDataSprite[1].normal = { 0.0f, 0.0f, -1.0f };

	vertexDataSprite[2].position = { 640.0f, 360.0f, 0.0f, 1.0f }; // 右下
	vertexDataSprite[2].texcoord = { 1.0f, 1.0f };
	vertexDataSprite[2].normal = { 0.0f, 0.0f, -1.0f };

	vertexDataSprite[3].position = { 640.0f, 0.0f, 0.0f, 1.0f }; // 右上
	vertexDataSprite[3].texcoord = { 1.0f, 0.0f };
	vertexDataSprite[3].normal = { 0.0f, 0.0f, -1.0f };

	// index
	indexResourceSprite = mesh_->CreateBufferResource(dir_->GetDevice(), sizeof(uint32_t) * 6);
	// リソースの先頭のアドレスから使う
	indexBufferViewSprite.BufferLocation = indexResourceSprite->GetGPUVirtualAddress();
	// 使用するリソースのサイズはindex6つ分のサイズ
	indexBufferViewSprite.SizeInBytes = sizeof(uint32_t) * 6;
	// indexはuint32_tとする
	indexBufferViewSprite.Format = DXGI_FORMAT_R32_UINT;

	indexDataSprite = nullptr;

	indexResourceSprite->Map(0, nullptr, reinterpret_cast<void**>(&indexDataSprite));

	indexDataSprite[0] = 0;
	indexDataSprite[1] = 1;
	indexDataSprite[2] = 2;
	indexDataSprite[3] = 1;
	indexDataSprite[4] = 3;
	indexDataSprite[5] = 2;
}

void Sprite::CreateMaterialResourceSprite(DirectXCommon* dir_, Mesh* mesh_){
	// マテリアル用のリソースを作る。今回はcolor1つ分のサイズを用意する
	materialResourceSprite = mesh_->Mesh::CreateBufferResource(dir_->GetDevice(), sizeof(Material));
	// マテリアルにデータを書き込む
	materialDataSprite = nullptr;
	// 書き込むためのアドレスを取得
	materialResourceSprite->Map(0, nullptr, reinterpret_cast<void**>(&materialDataSprite));
	// 白を設定
	materialDataSprite->color = { 1.0f, 1.0f, 1.0f, 1.0f };

	materialDataSprite->uvTransform = MakeIndentity4x4();
}


void Sprite::CreateTransformationMatrixResourceSprite(DirectXCommon* dir_, Mesh* mesh_){
	// Sprite用のTransformationMatrix用のリソースを作る。Matrix4x4 1つ分のサイズを用意する
	transformationMatrixResourceSprite = mesh_->CreateBufferResource(dir_->GetDevice(), sizeof(TransformationMatrix));

	// 書き込むためのアドレスを取得
	transformationMatrixResourceSprite->Map(0, nullptr, reinterpret_cast<void**>(&transformationMatrixDataSprite));

	// 単位行列を書き込んでおく
	transformationMatrixDataSprite->WVP = MakeIndentity4x4();
}
