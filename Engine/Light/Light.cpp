#include "Light.h"
using namespace DirectX;
ID3D12Device* Light::device_ = nullptr;

void Light::StaticInitalize(ID3D12Device* device)
{
	//再初期化チェック
	assert(!device_);
	//nullptrチェック
	assert(device);
	//情的メンバ変数のセット
	device_ = device;
}

void Light::Initalize()
{
	HRESULT result;
	// ヒーププロパティ
	CD3DX12_HEAP_PROPERTIES heapPropsConstantBuffer = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	// リソース設定
	CD3DX12_RESOURCE_DESC resourceDescConstantBuffer =
		CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) & ~0xff);

	// 定数バッファの生成
	result = device_->CreateCommittedResource(
		&heapPropsConstantBuffer, D3D12_HEAP_FLAG_NONE, &resourceDescConstantBuffer, D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr, IID_PPV_ARGS(&constBuff));
	assert(SUCCEEDED(result));

	//定数バッファへデータ転送
	TransfarConstBuffer();
}

void Light::Update()
{
	//値の更新があったときだけ定数バッファに転送する
	if (dirty)
	{
		TransfarConstBuffer();
		dirty = false;
	}
}

void Light::Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex)
{
	//定数バッファビューをセット
	cmdList->SetGraphicsRootConstantBufferView(rootParameterIndex,constBuff->GetGPUVirtualAddress());
}

Light* Light::Create()
{
	//3Dオブジェクトのインスタンスの生成
	Light* instance = new Light();
	//初期化
	instance->Initalize();
	return instance;
}

void Light::TransfarConstBuffer()
{

	HRESULT result;
	// 定数バッファにデータ転送
	ConstBufferData* constMap = nullptr;
	result = this->constBuff->Map(0, nullptr, (void**)&constMap);
	if (SUCCEEDED(result)) {
		constMap->lightv = -lightdir_;
		constMap->lightColor =lightcolor_;	// 行列の合成	
		constBuff->Unmap(0, nullptr);
	}
}

void Light::SetLightDir(Vector4& lightdir)
{
	//正規化してセット
	lightdir_ = lightdir.normalize();
	dirty = true;
}

void Light::SetLightColor(const XMFLOAT3 lightcolor)
{
	lightcolor_ = lightcolor;
	dirty = true;
}
