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
	void Update(Input* input,MouseInput* mouse);

	/// シーンの描画を行う
	void Draw(DirectXCommon* dxCommon);

	/// リセットを行う
	void Reset();

	//
	void SetPos(Vector3 pos) { object_->worldTransform.translation_ = pos; }
	void SetRestPos(Vector3 pos) { restPos_= pos; }
	void SetReticle(Vector3 ret) { reticle->worldTransform.translation_ = ret; }


	// 種族番号取得
	void SetTribe(int tribe) { Tribe_ = tribe; }
	int HowTribe() { return Tribe_; }

	WorldTransform GetTransform() { return object_->worldTransform; }

	bool GetisAreaSet() { return isAreaSet; };


	float GetPower() { return power; };

private:
	//void FrontFace();
	//void ColiderUpdate();

	const float MAX_POWER = 100.0f;
	float power = MAX_POWER;
	Vector3 restPos_;

public:
	Model* model_;
	Object3d* reticle;
	Object3d* object_;
	Vector3 areaPos_;
	Vector3 mousePos_;

	int isDecreasePower;	// 0 none, 1 並列, 2 直列

	float mouseSensitivity_ = 0.099f;	//マウス感度 0.05
	bool isGetThis = false;
private:
	int Tribe_ = 0;
	bool isChipGet_;
	bool nowDrag_;
	bool isAreaSet;
	

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

