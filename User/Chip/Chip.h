#pragma once
#include "Input.h"
#include "MouseInput.h"
#include "DirectXCommon.h"
#include "worldTransform.h"
#include "Object3d.h"
#include "Affin.h"

#include"SphereCollider.h"
#include"CollisionManager.h"
#include"CollisionAttribute.h"


class Chip
{
public:
	Chip();
	~Chip();


	/// シーンの更新を行う
	void Initialize();

	/// シーンの更新を行う
	void Update(Input* input);

	/// シーンの描画を行う
	void Draw(DirectXCommon* dxCommon);

	/// リセットを行う
	void Reset();

	//
	void SetPos(Vector3 pos) { object_->worldTransform.translation_ = pos; }
	void SetReticle(Vector3 ret) { reticle->worldTransform.translation_ = ret; }
	

	// 種族番号取得
	int HowTribe() { return Tribe_; }
	bool HowDead() { return isDead; }

	WorldTransform GetTransform() { return object_->worldTransform; }

private:
	//void FrontFace();
	//void ColiderUpdate();

public:

	MouseInput* mouse_;
	Model* model_;
	Object3d* reticle;
	Object3d* object_;

	float mouseSensitivity_ = 0.099f;	//マウス感度 0.05
	//private:
	const int Tribe_ = 1;
	bool isFound = false;
	bool isFire = false;
	bool isBlocked = false;



	Vector3 frontVec_;
	bool isDead = false;


	//移動速度
	const float kMoveSpeed_ = 0.5f;
	bool isRun_ = false;
	//移動ベクトル
	Vector3 velocity_;
	// 初期回転向き保存
	Vector3 restRotate_;

	//コライダー
public:
	void SetSphere(std::vector<SphereCollider*> sphere_) { sphere = sphere_; }
	std::vector<SphereCollider*> GetSphere() { return sphere; }
private:
	int SPHERE_COLISSION_NUM = 2;	//コライダー（スフィア）の数
	std::vector<Matrix4>* collisionBonesMat;	//当たり判定用のボーンのワールド行列 // fbx化後の仕様予定
	std::vector<SphereCollider*> sphere;
	std::vector<Vector3> spherePos;
	std::vector<Object3d*> coliderPosTest_;/*
	RayCollider* ray;
	RaycastHit* rayHit;*/
	Vector3 rayvec;
};

