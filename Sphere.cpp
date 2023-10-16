#include "Sphere.h"
#define _USE_MATH_DEFINES
#include "math.h"

void Sphere::Initialize(DirectXCommon* dir_, Mesh* mesh_){
	Sphere::CreateVertexResourceSphere(dir_, mesh_);
	Sphere::CreateTransformationMatrixResourceSphere(dir_, mesh_);

	transformSphere = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
}

void Sphere::Update(WinApp* winapp_, const Matrix4x4& transformationMatrixData){
	Matrix4x4 worldMatrixSphere = MakeAffineMatrix(transformSphere.scale, transformSphere.rotate, transformSphere.translate);
	worldMatrixSphere = Multiply(worldMatrixSphere, transformationMatrixData);
	*transformationMatrixDataSphere = worldMatrixSphere;
}

void Sphere::Draw(DirectXCommon* dir_, Mesh* mesh_){
	// Spriteの描画。変更が必要なものだけ変更する
	dir_->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferViewSphere); // VBVを設定
	// TransformationMatrixCBufferの場所を設定
	dir_->GetCommandList()->SetGraphicsRootConstantBufferView(1, transformationMatrixResourceSphere->GetGPUVirtualAddress());
	// 描画(DrawCall/ドローコール)
	dir_->GetCommandList()->DrawInstanced(startIndex, 1, 0, 0);
}

void Sphere::Release() {
	vertexResourceSphere->Release();
	transformationMatrixResourceSphere->Release();
}

void Sphere::CreateVertexResourceSphere(DirectXCommon* dir_, Mesh* mesh_){

	// Sprite用の頂点リソースを作る
	vertexResourceSphere = mesh_->CreateBufferResource(dir_->GetDevice(), sizeof(VertexData) * 6);

	// リソースの先頭のアドレスから使う
	vertexBufferViewSphere.BufferLocation = vertexResourceSphere->GetGPUVirtualAddress();
	// 使用するリソースのサイズは頂点6つ分のサイズ
	vertexBufferViewSphere.SizeInBytes = sizeof(VertexData) * startIndex;
	// 1頂点あたりのサイズ
	vertexBufferViewSphere.StrideInBytes = sizeof(VertexData);

	vertexResourceSphere->Map(0, nullptr, reinterpret_cast<void**>(&vertexDataSphere));

	// 経度1つ分の角度
	const float kLonEvery = 2.0f * PI / float(kSubdivision);

	// 緯度1つ分の角度
	const float kLatEvery = PI / float(kSubdivision);

	// 緯度の方向に分割
	for (latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -PI / 2.0f + kLatEvery * latIndex;

		// 経度の方向に分割しながら線を書く
		for (lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			int32_t start = (latIndex * kSubdivision + lonIndex) * 6;
			float lon = lonIndex * kLonEvery;
			float u = float(lonIndex) / float(kSubdivision);
			float v = 1.0f - float(latIndex) / float(kSubdivision);

			// 頂点にデータを入力する
			// 基準点a
			vertexDataSphere[start].position.x = cos(lat) * cos(lon);
			vertexDataSphere[start].position.y = sin(lat);
			vertexDataSphere[start].position.z = cos(lat) * sin(lon);
			vertexDataSphere[start].position.w = 1.0f;
			vertexDataSphere[start].texcoord = { u,v + (1.0f / kSubdivision) };
			// 基準点b
			vertexDataSphere[start + 1].position.x = cos(lat + kLatEvery) * cos(lon);
			vertexDataSphere[start + 1].position.y = sin(lat + kLatEvery);
			vertexDataSphere[start + 1].position.z = cos(lat + kLatEvery) * sin(lon);
			vertexDataSphere[start + 1].position.w = 1.0f;
			vertexDataSphere[start + 1].texcoord = { u,v };
			// 基準点c
			vertexDataSphere[start + 2].position.x = cos(lat) * cos(lon + kLonEvery);
			vertexDataSphere[start + 2].position.y = sin(lat);
			vertexDataSphere[start + 2].position.z = cos(lat) * sin(lon + kLonEvery);
			vertexDataSphere[start + 2].position.w = 1.0f;
			vertexDataSphere[start + 2].texcoord = { u + (1.0f / kSubdivision),v + (1.0f / kSubdivision) };
			// 基準点b
			vertexDataSphere[start + 3].position.x = cos(lat + kLatEvery) * cos(lon);
			vertexDataSphere[start + 3].position.y = sin(lat + kLatEvery);
			vertexDataSphere[start + 3].position.z = cos(lat + kLatEvery) * sin(lon);
			vertexDataSphere[start + 3].position.w = 1.0f;
			vertexDataSphere[start + 3].texcoord = { u,v };
			// 基準点d
			vertexDataSphere[start + 4].position.x = cos(lat + kLatEvery) * cos(lon + kLonEvery);
			vertexDataSphere[start + 4].position.y = sin(lat + kLatEvery);
			vertexDataSphere[start + 4].position.z = cos(lat + kLatEvery) * sin(lon + kLonEvery);
			vertexDataSphere[start + 4].position.w = 1.0f;
			vertexDataSphere[start + 4].texcoord = { u + (1.0f / kSubdivision),v };
			// 基準点c
			vertexDataSphere[start + 5].position.x = cos(lat) * cos(lon + kLonEvery);
			vertexDataSphere[start + 5].position.y = sin(lat);
			vertexDataSphere[start + 5].position.z = cos(lat) * sin(lon + kLonEvery);
			vertexDataSphere[start + 5].position.w = 1.0f;
			vertexDataSphere[start + 5].texcoord = { u + (1.0f / kSubdivision),v + (1.0f / kSubdivision) };
		}
	}
}

void Sphere::CreateTransformationMatrixResourceSphere(DirectXCommon* dir_, Mesh* mesh_){
	// Sprite用のTransformationMatrix用のリソースを作る。Matrix4x4 1つ分のサイズを用意する
	transformationMatrixResourceSphere = mesh_->CreateBufferResource(dir_->GetDevice(), sizeof(Matrix4x4));

	// 書き込むためのアドレスを取得
	transformationMatrixResourceSphere->Map(0, nullptr, reinterpret_cast<void**>(&transformationMatrixDataSphere));

	// 単位行列を書き込んでおく
	*transformationMatrixDataSphere = MakeIndentity4x4();
}
