#pragma once
#include "IScene.h"
#include "SceneInc.h"

class PlayScene;

class PauseScene :
    public IScene
{
protected:
	SceneManager* controller_;
	Input* input_ = nullptr;
	GamePad* gamePad_ = nullptr;

	Sprite* sprite_ = nullptr;
	Sprite* sprite2_ = nullptr;

	Model* model = nullptr;
	Object3d* object = nullptr;

	PostEffect* postEffect = nullptr;

	Camera* camera_ = nullptr;

	GameCamera* gameCamera = nullptr;


	FbxModel* fbxModel = nullptr;
	FbxObject3d* fbxObject = nullptr;

	//天球
	Object3d* skydomeO_ = nullptr;
	Model* skydomeM_ = nullptr;


	Player* player_ = nullptr;
	Enemy* enemy_ = nullptr;

	CollisionManager* colMan = nullptr;

	SceneObjects* sceneObj_;

	Sprite* playerHpSprite_ = nullptr;
	Sprite* enemyHpSprite_ = nullptr;

	Vector3 nowEye;

	//プレイヤーの弾モデル関連
	std::list <std::unique_ptr<PlayerBullet>> pBullets_;
	std::list <std::unique_ptr<EnemyBullet>> eBullets_;

public:

	PauseScene(SceneManager* controller, SceneObjects* sceneObj);
	~PauseScene() override;

	void Initialize() override;

	void Update(Input* input, GamePad* gamePad) override;

	void Draw() override;

	//void Pause(Input* input);
};

