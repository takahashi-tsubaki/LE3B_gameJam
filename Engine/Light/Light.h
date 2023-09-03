#pragma once
#include <DirectXMath.h>
#include <d3d12.h>
#include <d3dx12.h>
#include "Vector4.h"
class Light
{
private:
	// Microsoft::WRL::を省略
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	// 定数バッファ用データ構造体
	struct ConstBufferData
	{
		Vector4 lightv;//ライトへの方向を表すベクトル
		XMFLOAT3 lightColor;//ライトの色
	};

private://情的メンバ変数
	//デバイス
	static ID3D12Device* device_;

public://情的メンバ関数
	/// <summary>
	/// 情的初期化
	/// </summary>
	static void StaticInitalize(ID3D12Device* device);

private://メンバ変数
	//定数バッファ
	ComPtr<ID3D12Resource>constBuff;
	//ライト光線方向(単位ベクトル)
	Vector4 lightdir_ = { 1,0,0,0 };
	//ライト色
	XMFLOAT3 lightcolor_ = { 1,1,1 };
	//ダーティフラグ
	bool dirty = false;

public:
	/// <summary>
	/// 定数バッファ転送
	/// </summary>
	void TransfarConstBuffer();

	/// <summary>
	/// ライト方向をセット
	/// </summary>
	/// <param name="lightdir"></param>
	void SetLightDir( Vector4& lightdir);
	/// <summary>
	/// ライト色をセット
	/// </summary>
	void SetLightColor(const XMFLOAT3 lightcolor);

	/// <summary>
	/// 初期化
	/// </summary>
	void Initalize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ID3D12GraphicsCommandList*cmdList,UINT rootParameterIndex);


	static Light* Create();
};

