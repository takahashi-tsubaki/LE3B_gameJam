#pragma once
#include "DirectXCommon.h"
#include "Input.h"
#include "GamePad.h"
#include "MouseInput.h"

#include "Object3d.h"
#include "Model.h"

#include "FbxObject3d.h"
#include "FbxModel.h"

#include "MyMath.h"
#include "ImguiManager.h"
#include "Camera.h"

#include"SphereCollider.h"
#include"CollisionManager.h"
#include"CollisionAttribute.h"

#include "PlayerActionManager.h"
class Player
{
public:

	std::unique_ptr <PlayerActionManager> pActManager_;

	//コンストラクタ
	Player();
	//デストラクタ
	~Player();
public:
	void Initialize(DirectXCommon* dxCommon);

	void Update(Input* input, GamePad* gamePad);

	void Draw();

	void SetPosition(Vector3 position) { playerO_->worldTransform.translation_ = position; playerO_->Update(); }
	Vector3 GetPosition() { return playerO_->worldTransform.translation_; }

	PlayerActionManager* GetPlayerActionManager() { return pActManager_.get(); };

	void CheckCollision();

	bool GetIsGoal() { return isGoal_; }

	void ResetParam(int startplayerPos);

	bool GetIsHit() { return isHit; }

	void Move();

	void Respawn();

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	GamePad* gamePad_ = nullptr;
	MouseInput* mouse_ = nullptr;

	Object3d* playerO_ = nullptr;
	Model* playerM_ = nullptr;
	Model* walkmodel1 = nullptr;
	Model* walkmodel2 = nullptr;
	Model* jumpmodel = nullptr;
	Model* jumpmodelL = nullptr;
	Model* dashmodel0 = nullptr;
	Model* dashmodel1 = nullptr;
	Model* dashmodel2 = nullptr;
	int changeModelTimer = 0;
	int changeModelTimerD = 0;

	//当たり判定に必要なもの
	int SPHERE_COLISSION_NUM = 1;	//コライダー（スフィア）の数
	std::vector<Matrix4>* collisionBonesMat;	//当たり判定用のボーンのワールド行列
	std::vector<SphereCollider*> sphere;
	std::vector<Vector3> spherePos = {};
	int hitDeley = 0;	//何フレーム連続で当たるか


	int actionNum = 1;
	int oldActionNum_ = 0;	//アクション前フレーム保存変数

	bool isGoal_ = false;

	bool isHit = false;

	bool OnGround = false;
	Vector3 fallV;

	float gravity = 0.0f;
	const float addSpeed = 0.1f;

	Vector3 move;
	float speed = 0.25f;


	 int startplayerPos_;
public:
	//
	unsigned short chipPat_;
	bool chipOnMove_;
};

