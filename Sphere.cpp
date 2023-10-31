#include "Sphere.h"
#define _USE_MATH_DEFINES
#include "math.h"
#include "externals/imgui/imgui.h"

void Sphere::Initialize(DirectXCommon* dir_, Mesh* mesh_){

	Sphere::CreateVertexResourceSphere(dir_, mesh_);
	Sphere::CreateMaterialResourceSphere(dir_, mesh_);
	Sphere::CreateTransformationMatrixResourceSphere(dir_, mesh_);
	Sphere::CreateDirectionalResource(dir_, mesh_);

	transformSphere = { {0.5f,0.5f,0.5f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	uvTransformSphere = { {1.0f, 1.0f, 1.0f},{0.0f, 0.0f, 0.0f},{0.0f, 0.0f, 0.0f}, };

	directionalLightData->color = { 1.0f, 1.0f, 1.0f, 1.0f };
	directionalLightData->direction = { 0.0f, -1.0f, 1.0f };
	directionalLightData->intensity = 1.0f;
}

void Sphere::Update(const Matrix4x4& transformationMatrixData){
	transformSphere.rotate.y += 0.02f;

	wvpResourceDataSphere->World = MakeAffineMatrix(transformSphere.scale, transformSphere.rotate, transformSphere.translate);
	wvpResourceDataSphere->World = Multiply(wvpResourceDataSphere->World, transformationMatrixData);
	wvpResourceDataSphere->WVP = wvpResourceDataSphere->World;

	Matrix4x4 uvtransformMatrix = MakeScaleMatrix(uvTransformSphere.scale);
	uvtransformMatrix = Multiply(uvtransformMatrix, MakeRotateZMatrix(uvTransformSphere.rotate.z));
	uvtransformMatrix = Multiply(uvtransformMatrix, MakeTranslateMatrix(uvTransformSphere.translate));
	materialDataSphere->uvTransform = uvtransformMatrix;
}

void Sphere::Draw(DirectXCommon* dir_, Mesh* mesh_){
	// Spriteの描画。変更が必要なものだけ変更する
	dir_->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferViewSphere); // VBVを設定
	// マテリアルCBufferの場所を設定
	dir_->GetCommandList()->SetGraphicsRootConstantBufferView(0, materialResourceSphere->GetGPUVirtualAddress());
	// TransformationMatrixCBufferの場所を設定
	dir_->GetCommandList()->SetGraphicsRootConstantBufferView(1, wvpResourceSphere->GetGPUVirtualAddress());
	dir_->GetCommandList()->SetGraphicsRootConstantBufferView(3, directionalLightResource->GetGPUVirtualAddress());
	// SRVのDescriptorTableの先頭を設定。2はrootParameter[2]である。
	dir_->GetCommandList()->SetGraphicsRootDescriptorTable(2, useMoon ? mesh_->textureSrvHandleGPU2 : mesh_->textureSrvHandleGPU);
	if (isSphere == true) {
		// 描画(DrawCall/ドローコール)
		dir_->GetCommandList()->DrawInstanced(vertexIndex, 1, 0, 0);
	}

	ImGui::Begin("Sphere");
	ImGui::Checkbox("IsSphere", &isSphere);
	ImGui::Checkbox("useMoon", &useMoon);

	ImGui::DragFloat3("Transform", &transformSphere.translate.x, 0.01f, -10.0f, 10.0f);

	ImGui::SliderFloat3("Light Direction", &directionalLightData->direction.x, -1.0f, 1.0f);
	directionalLightData->direction = Normalize(directionalLightData->direction);
	ImGui::SliderFloat("Intensity", &directionalLightData->intensity, 0.0f, 1.0f);

	ImGui::DragFloat2("UVTransform", &uvTransformSphere.translate.x, 0.01f, -10.0f, 10.0f);
	ImGui::DragFloat2("UVScale", &uvTransformSphere.scale.x, 0.01f, -10.0f, 10.0f);
	ImGui::SliderAngle("UVRotate", &uvTransformSphere.rotate.z);
	ImGui::End();
}

void Sphere::Release() {
}

void Sphere::CreateVertexResourceSphere(DirectXCommon* dir_, Mesh* mesh_){

	// 頂点リソースを作る
	vertexResourceSphere = mesh_->CreateBufferResource(dir_->GetDevice(), sizeof(VertexData) * vertexIndex);

	// リソースの先頭のアドレスから使う
	vertexBufferViewSphere.BufferLocation = vertexResourceSphere->GetGPUVirtualAddress();
	// 使用するリソースのサイズは頂点6つ分のサイズ
	vertexBufferViewSphere.SizeInBytes = sizeof(VertexData) * vertexIndex;
	// 1頂点あたりのサイズ
	vertexBufferViewSphere.StrideInBytes = sizeof(VertexData);

	vertexResourceSphere->Map(0, nullptr, reinterpret_cast<void**>(&vertexDataSphere));

	// 経度1つ分の角度
	const float kLonEvery = 2.0f * float(M_PI) / float(kSubdivision);

	// 緯度1つ分の角度
	const float kLatEvery = float(M_PI) / float(kSubdivision);

	// 緯度の方向に分割
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = float(-M_PI) / 2.0f + kLatEvery * latIndex;

		// 経度の方向に分割しながら線を書く
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			int32_t start = (latIndex * kSubdivision + lonIndex) * 6;
			float lon = lonIndex * kLonEvery;

			// 頂点にデータを入力する
			// 基準点a
			vertexDataSphere[start].position.x = cos(lat) * cos(lon);
			vertexDataSphere[start].position.y = sin(lat);
			vertexDataSphere[start].position.z = cos(lat) * sin(lon);
			vertexDataSphere[start].position.w = 1.0f;

			vertexDataSphere[start].texcoord = { float(lonIndex) / float(kSubdivision) ,1.0f - float(latIndex) / float(kSubdivision) };

			vertexDataSphere[start].normal.x = vertexDataSphere[start].position.x;
			vertexDataSphere[start].normal.y = vertexDataSphere[start].position.y;
			vertexDataSphere[start].normal.z = vertexDataSphere[start].position.z;

			// 基準点b
			vertexDataSphere[start + 1].position.x = cos(lat + kLatEvery) * cos(lon);
			vertexDataSphere[start + 1].position.y = sin(lat + kLatEvery);
			vertexDataSphere[start + 1].position.z = cos(lat + kLatEvery) * sin(lon);
			vertexDataSphere[start + 1].position.w = 1.0f;

			vertexDataSphere[start + 1].texcoord = { vertexDataSphere[start].texcoord.x,vertexDataSphere[start].texcoord.y - (1.0f / kSubdivision) };

			vertexDataSphere[start + 1].normal.x = vertexDataSphere[start + 1].position.x;
			vertexDataSphere[start + 1].normal.y = vertexDataSphere[start + 1].position.y;
			vertexDataSphere[start + 1].normal.z = vertexDataSphere[start + 1].position.z;

			// 基準点c
			vertexDataSphere[start + 2].position.x = cos(lat) * cos(lon + kLonEvery);
			vertexDataSphere[start + 2].position.y = sin(lat);
			vertexDataSphere[start + 2].position.z = cos(lat) * sin(lon + kLonEvery);
			vertexDataSphere[start + 2].position.w = 1.0f;

			vertexDataSphere[start + 2].texcoord = { vertexDataSphere[start].texcoord.x + (1.0f / (float)kSubdivision),vertexDataSphere[start].texcoord.y };
			
			vertexDataSphere[start + 2].normal.x = vertexDataSphere[start + 2].position.x;
			vertexDataSphere[start + 2].normal.y = vertexDataSphere[start + 2].position.y;
			vertexDataSphere[start + 2].normal.z = vertexDataSphere[start + 2].position.z;

			// 基準点b
			vertexDataSphere[start + 3].position.x = cos(lat + kLatEvery) * cos(lon);
			vertexDataSphere[start + 3].position.y = sin(lat + kLatEvery);
			vertexDataSphere[start + 3].position.z = cos(lat + kLatEvery) * sin(lon);
			vertexDataSphere[start + 3].position.w = 1.0f;
			
			vertexDataSphere[start + 3].texcoord = { vertexDataSphere[start].texcoord.x,vertexDataSphere[start].texcoord.y - (1.0f / (float)kSubdivision) };

			vertexDataSphere[start + 3].normal.x = vertexDataSphere[start + 3].position.x;
			vertexDataSphere[start + 3].normal.y = vertexDataSphere[start + 3].position.y;
			vertexDataSphere[start + 3].normal.z = vertexDataSphere[start + 3].position.z;

			// 基準点d
			vertexDataSphere[start + 4].position.x = cos(lat + kLatEvery) * cos(lon + kLonEvery);
			vertexDataSphere[start + 4].position.y = sin(lat + kLatEvery);
			vertexDataSphere[start + 4].position.z = cos(lat + kLatEvery) * sin(lon + kLonEvery);
			vertexDataSphere[start + 4].position.w = 1.0f;
			
			vertexDataSphere[start + 4].texcoord = { vertexDataSphere[start].texcoord.x + (1.0f / (float)kSubdivision),vertexDataSphere[start].texcoord.y - (1.0f / (float)kSubdivision) };

			vertexDataSphere[start + 4].normal.x = vertexDataSphere[start + 4].position.x;
			vertexDataSphere[start + 4].normal.y = vertexDataSphere[start + 4].position.y;
			vertexDataSphere[start + 4].normal.z = vertexDataSphere[start + 4].position.z;

			// 基準点c
			vertexDataSphere[start + 5].position.x = cos(lat) * cos(lon + kLonEvery);
			vertexDataSphere[start + 5].position.y = sin(lat);
			vertexDataSphere[start + 5].position.z = cos(lat) * sin(lon + kLonEvery);
			vertexDataSphere[start + 5].position.w = 1.0f;
			
			vertexDataSphere[start + 5].texcoord = { vertexDataSphere[start].texcoord.x + (1.0f / (float)kSubdivision),vertexDataSphere[start].texcoord.y };

			vertexDataSphere[start + 5].normal.x = vertexDataSphere[start + 5].position.x;
			vertexDataSphere[start + 5].normal.y = vertexDataSphere[start + 5].position.y;
			vertexDataSphere[start + 5].normal.z = vertexDataSphere[start + 5].position.z;

		}
	}
}

void Sphere::CreateMaterialResourceSphere(DirectXCommon* dir_, Mesh* mesh_){
	// マテリアル用のリソースを作る。今回はcolor1つ分のサイズを用意する
	materialResourceSphere = mesh_->Mesh::CreateBufferResource(dir_->GetDevice(), sizeof(Material));
	// マテリアルにデータを書き込む
	materialDataSphere = nullptr;
	// 書き込むためのアドレスを取得
	materialResourceSphere->Map(0, nullptr, reinterpret_cast<void**>(&materialDataSphere));
	// 白を設定
	materialDataSphere->color = { 1.0f, 1.0f, 1.0f, 1.0f };
	// SphereはLightingするのでtrueを設定
	materialDataSphere->enableLighting = true;

	materialDataSphere->uvTransform = MakeIndentity4x4();
}

void Sphere::CreateTransformationMatrixResourceSphere(DirectXCommon* dir_, Mesh* mesh_){
	// Sprite用のTransformationMatrix用のリソースを作る。Matrix4x4 1つ分のサイズを用意する
	wvpResourceSphere = mesh_->CreateBufferResource(dir_->GetDevice(), sizeof(TransformationMatrix));

	// 書き込むためのアドレスを取得
	wvpResourceSphere->Map(0, nullptr, reinterpret_cast<void**>(&wvpResourceDataSphere));

	// 単位行列を書き込んでおく
	wvpResourceDataSphere->WVP = MakeIndentity4x4();
	wvpResourceDataSphere->World = MakeIndentity4x4();
}

void Sphere::CreateDirectionalResource(DirectXCommon* dir_, Mesh* mesh_){
	directionalLightResource = mesh_->CreateBufferResource(dir_->GetDevice(), sizeof(DirectionalLight));
	directionalLightResource->Map(0, nullptr, reinterpret_cast<void**>(&directionalLightData));
}
