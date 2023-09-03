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

	//������
	void Initialize() override;

	//�I��
	void Finalize() override;

	//���t���[���X�V
	void Update() override;

	//�`��
	void Draw() override;

private:
	/*ID3D12DebugDevice* debugInterface;*/

	FbxManager* fbxManager = nullptr;
	PostEffect* postEffect = nullptr;

	Framework* framework = nullptr;
	GameScene* gameScene = nullptr;
};