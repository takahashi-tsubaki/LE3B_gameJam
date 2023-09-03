#pragma once
#include "gameScene.h"
#include "DirectXCommon.h"
#include "Object3d.h"
#include "Light.h"
#include "ParticleManager.h"
#include "PostEffect.h"
#include "FbxLoader.h"

#include "Framework.h"

class MyGame : public Framework
{
public:

	//初期化
	void Initialize() override;

	//終了
	void Finalize() override;

	//毎フレーム更新
	void Update() override;

	//描画
	void Draw() override;

private:
	/*ID3D12DebugDevice* debugInterface;*/

	FbxManager* fbxManager = nullptr;
	PostEffect* postEffect = nullptr;

	Framework* framework = nullptr;
	GameScene* gameScene = nullptr;
};