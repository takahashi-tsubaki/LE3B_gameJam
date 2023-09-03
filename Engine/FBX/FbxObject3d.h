#pragma once
#include "ErrorException.h"
#include "FbxLoader.h"
#include "FbxModel.h"
#include "Camera.h"

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include<DirectXMath.h>
#include <string>

#include "worldTransform.h"

class FbxObject3d
{
public:
	//ボーンの最大数
	static const int MAX_BONES = 1000;//HLSL側を合わせる


	WorldTransform worldTransform;

protected://エイリアス
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectXを省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public://サブクラス
	//定数バッファ用データ構造体(座標変換行列用)
	struct ConstBufferDataTransfrom
	{
		Matrix4 viewproj;
		Matrix4 world;
		Vector3 cameraPos;
		Vector4 color;
	};
	struct ConstBufferDataSkin
	{
		XMMATRIX bones[MAX_BONES];
	};
public://情的メンバ関数
	//setter
	static void SetDevice(ID3D12Device* device) { device_ = device; }
	static void SetCamera(Camera* camera) { camera_ = camera; }

	static void CreateGraphicsPipeline();

private://情的メンバ変数
	//デバイス
	static ID3D12Device* device_;
	//カメラ
	static Camera* camera_;

	static ComPtr<ID3D12RootSignature>rootsignature;
	//パイプラインステート
	static ComPtr<ID3D12PipelineState> pipelineState;

public://メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// モデルのセット
	/// </summary>
	/// <param name="fbxModel"></param>
	void SetModel(FbxModel* fbxModel) { fbxModel_ = fbxModel; }

	void SetScale(Vector3 scale) { worldTransform.scale_ = scale;}

	void SetPosition(Vector3 position) { worldTransform.translation_ = position; }
	/// <summary>
	/// ボーン用
	/// </summary>
	std::vector<Matrix4> bonesMat;
	void ResizeBonesMat(std::vector<FbxModel::Bone> bones);	//ボーンのサイズをクラスターボーンに合わせる
	bool isBonesWorldMatCalc = false;	//ボーンのワールド座標上での計算をするかどうか
	std::vector<Matrix4>* GetBonesMatPtr();	//ボーンのワールド行列ポインタを渡す
	void SetIsBonesWorldMatCalc(bool isCalc);	//ボーン計算フラグのセッター
	/// <summary>
	/// アニメーション開始
	/// </summary>
	void PlayAnimetion(int AnimNum);


	Vector3 GetPosition() { return worldTransform.translation_; }

	void SetColor(Vector4 color) { color_ = color; }

public:
	//定数バッファ
	ComPtr<ID3D12Resource> constBuffTransform;

	//定数バッファ(スキン)
	ComPtr<ID3D12Resource> constBuffSkin;

	Vector4 color_ = { 1,1,1,1 };

	// ローカルスケール
	Vector3 scale_ = { 1,1,1 };
	// X,Y,Z軸回りのローカル回転角
	Vector3 rotation = { 0,0,0 };
	// ローカル座標
	Vector3 position_ = { 0,0,0 };
	// ローカルワールド変換行列
	Matrix4 matWorld;

	FbxModel* fbxModel_ = nullptr;

	//1フレームの時間
	FbxTime frameTime;
	//アニメーション開始時間
	FbxTime startTime;
	//アニメーション終了時間
	FbxTime endTime;
	//現在時間
	FbxTime currentTime;
	//アニメーション再生中
	bool isPlay = false;

};