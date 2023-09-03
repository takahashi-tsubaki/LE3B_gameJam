#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include <string>
#include "Model.h"
#include "Camera.h"
#include "GameCamera.h"
#include "Light.h"

#include "worldTransform.h"

#include "Vector3.h"

/// <summary>
/// 3Dオブジェクト
/// </summary>
class Object3d
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: // サブクラス	

	// パイプラインセット
	struct PipelineSet
	{
		// ルートシグネチャ
		ComPtr<ID3D12RootSignature> rootsignature;
		// パイプラインステートオブジェクト
		ComPtr<ID3D12PipelineState> pipelinestate;
	};

	// 定数バッファ用データ構造体B0
	struct ConstBufferDataB0
	{
		Matrix4 mat; // 3D変換行列
		Vector4 color;
	};

private: // 定数


public: // 静的メンバ関数
	/// <summary>
	/// 静的初期化
	/// </summary>
	/// <param name="device">デバイス</param>
	/// <param name="camera">カメラ</param>
	static void StaticInitialize(ID3D12Device* device, Camera* camera = nullptr);

	/// <summary>
	/// グラフィックパイプラインの生成
	/// </summary>
	static void CreateGraphicsPipeline();

	/// <summary>
	/// カメラのセット
	/// </summary>
	/// <param name="camera">カメラ</param>
	static void SetCamera(Camera* camera) { sCamera_ = camera; }

	/// <summary>
	/// 描画前処理
	/// </summary>
	/// <param name="commandList">描画コマンドリスト</param>
	static void PreDraw(ID3D12GraphicsCommandList* commandList);

	/// <summary>
	/// 描画後処理
	/// </summary>
	static void PostDraw();

	/// <summary>
	/// 3Dオブジェクト生成
	/// </summary>
	/// <returns></returns>
	static Object3d* Create();

private: // 静的メンバ変数
	// デバイス
	static ID3D12Device* device_;
	// コマンドリスト
	static ID3D12GraphicsCommandList* sCommandList;
	// テクスチャあり用パイプライン
	static PipelineSet pipelineSet;
	// カメラ
	static Camera* sCamera_;

public: // メンバ関数
	bool Initialize();
	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	void UpdateMatrix();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();



	/// <summary>
	/// 座標の取得
	/// </summary>
	/// <returns>座標</returns>
	const Vector3& GetPosition() { return worldTransform.translation_; }

	/// <summary>
	/// 回転角の取得
	/// </summary>
	/// <returns></returns>
	const Vector3& GetRotation() { return rotation_; }

	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="position">座標</param>
	void SetPosition(Vector3 position) { worldTransform.translation_ = position; }

	void SetRotation(Vector3 rotation) { worldTransform.rotation_ = rotation; }

	/// <summary>
	/// スケールの設定
	/// </summary>
	/// <param name="position">スケール</param>
	void SetScale(Vector3 scale) { worldTransform.scale_ = scale; }

	/// <summary>
	/// ワールド行列の取得
	/// </summary>
	/// <returns>ワールド行列</returns>
	const Matrix4& GetMatWorld() { return worldTransform.matWorld_; }

	/// <summary>
	/// モデルのセット
	/// </summary>
	/// <param name="model">モデル</param>
	void SetModel(Model* model) { model_ = model; }

	void SetBillboard(bool isBillboard) { isBillboard_ = isBillboard; }

	static void SetLight(Light* light)
	{
		light_ = light;
	}

	void SetColor(Vector4 color) { color_ = color; }

	WorldTransform GetWorldTransform() { return worldTransform; }
	WorldTransform* GetWorldTransformPtr() { return &worldTransform; }

	Camera* GetCamera() { return sCamera_; }

private: // メンバ変数
	
	// 定数バッファへデータ転送
	ConstBufferDataB0* constMap = nullptr;

	ComPtr<ID3D12Resource> constBuffB0; // 定数バッファ
	ComPtr<ID3D12Resource> constBuffCameraPosition; // 定数バッファ

	// 親オブジェクト
	Object3d* parent = nullptr;
	// モデル
	Model* model_ = nullptr;
	// ビルボード
	bool isBillboard_ = false;

	//ライト
	static Light* light_;
public:

	//ワールド行列
	WorldTransform worldTransform;

	// 色
	Vector4 color_ = { 1,1,1,1 };
	// ローカルスケール
	Vector3 scale_ = { 1,1,1 };
	// X,Y,Z軸回りのローカル回転角
	Vector3 rotation_ = { 0,0,0 };
	// ローカル座標
	Vector3 position_ = { 0,0,0 };
	// ローカルワールド変換行列
	XMMATRIX matWorld;
	



};

