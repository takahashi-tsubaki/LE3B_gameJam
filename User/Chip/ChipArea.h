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


class ChipArea
{
public:
	ChipArea();
	~ChipArea();


	/// シーンの更新を行う
	void Initialize();

	/// シーンの更新を行う
	void Update();

	/// シーンの描画を行う
	void Draw(DirectXCommon* dxCommon);

	/// リセットを行う
	void Reset();

	//
	void SetPos(Vector3 pos) { object_->worldTransform.translation_ = pos; }
	void SetScale(Vector3 scale) { object_->worldTransform.scale_ = scale; }
	//void SetReticle(Vector3 ret) { reticle->worldTransform.translation_ = ret; }


	// 種族番号取得
	//int SetTribe(int tribe) { Tribe_ = tribe; }
	//int HowTribe() { return Tribe_; }

	WorldTransform GetTransform() { return object_->worldTransform; }

private:
	//void FrontFace();
	//void ColiderUpdate();

public:
	Model* model_;
	Object3d* object_;

	//float mouseSensitivity_ = 0.099f;	//マウス感度 0.05
private:

	// 領域用
	bool isSet;

	//コライダー
public:
	void SetSphere(std::vector<SphereCollider*> sphere_) { sphere = sphere_; }
	std::vector<SphereCollider*> GetSphere() { return sphere; }
private:
	int SPHERE_COLISSION_NUM = 1;	//コライダー（スフィア）の数
	std::vector<Matrix4>* collisionBonesMat;	//当たり判定用のボーンのワールド行列 // fbx化後の仕様予定
	std::vector<SphereCollider*> sphere;
	std::vector<Vector3> spherePos;
	std::vector<Object3d*> coliderPosTest_;/*
	RayCollider* ray;
	RaycastHit* rayHit;*/
	Vector3 rayvec;
};

