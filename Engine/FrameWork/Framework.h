#pragma once
#include "WinApp.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "GamePad.h"
#include "FPS.h"

#include "ImguiManager.h"
#include "Sprite.h"
#include"Light.h"
#include "ParticleManager.h"
#include "FbxLoader.h"
class Framework
{
public:

	//初期化
	virtual void Initialize();

	//終了
	virtual void Finalize();

	//毎フレーム更新
	virtual void Update();

	//描画
	virtual void Draw() = 0;

	virtual void SetRequest(bool request) { endRequest_ = request; }

	//終了チェック
	virtual bool IsEndRequest() { return endRequest_; }

	//デストラクタ
	virtual ~Framework() = default;

	//実行
	void Run();

protected:
	//FPS
	FPS* fps = new FPS;
	WinApp* winApp = nullptr;
	Input* input = nullptr;
	GamePad* gamePad_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
	ImguiManager* imgui = nullptr;
	bool endRequest_ = false;
};