#pragma once
#include "ErrorException.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "GamePad.h"

#include "Sprite.h"
#include "PostEffect.h"

#include "Camera.h"
#include "Light.h"
#include "Model.h"
#include "Object3d.h"

#include "ParticleManager.h"

#include "Vector3.h"

#include "FbxObject3d.h"

#include "Player.h"
#include "Enemy.h"
#include "SceneManager.h"
#include "SceneObjects.h"
class GameScene
{

public:

	GameScene();
	~GameScene();

	void Initalize(DirectXCommon* dxCommon, Input* input, GamePad* gamePad);

	void Update();

	void Draw();

	

private:
	DirectXCommon* dxCommon_ = nullptr;

	Input* input_ = nullptr;
	GamePad* gamePad_ = nullptr;

	Sprite* sprite_ = nullptr;
	Sprite* sprite2_ = nullptr;

	Model* model = nullptr;
	Object3d* object = nullptr;

	PostEffect* postEffect = nullptr;

	Camera* camera_ = nullptr;

	GameCamera* gameCamera = nullptr;

	Light* light_ = nullptr;

	FbxModel* fbxModel = nullptr;
	FbxObject3d* fbxObject = nullptr;

	//“V‹…
	Object3d* skydomeO_ = nullptr;
	Model* skydomeM_ = nullptr;



	Player* player_ = nullptr;
	Enemy* enemy_ = nullptr;

	CollisionManager* colMan = nullptr;

	IScene* scene_ = nullptr;
	SceneManager* sceneManager = nullptr;
	SceneObjects* sceneObjects = nullptr;
};