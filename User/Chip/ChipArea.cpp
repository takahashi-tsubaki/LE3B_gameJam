#include "ChipArea.h"


ChipArea::ChipArea()
{
}

ChipArea::~ChipArea()
{
}

/// エリアの初期化
void ChipArea::Initialize() {

	model_ = Model::CreateFromOBJ("Cube1");

	object_ = Object3d::Create();
	object_->SetModel(model_);
	object_->Initialize();
	object_->position_ = { 0,0,0 };

	//reticle = Object3d::Create();
	//reticle->SetModel(model_);
	//reticle->Initialize();
	//reticle->position_ = { 10,0,10 };

	//当たり判定用
	SPHERE_COLISSION_NUM = 1;
	sphere.resize(SPHERE_COLISSION_NUM);
	spherePos.resize(SPHERE_COLISSION_NUM);
	//FbxO_.get()->isBonesWorldMatCalc = true;	// ボーンの行列を取得するか
	coliderPosTest_.resize(SPHERE_COLISSION_NUM);

	//rayvec = Affin::GetWorldTrans(reticle->wtf.matWorld) - Affin::GetWorldTrans(object_->wtf.matWorld);
	//rayvec = -(Affin::GetWorldTrans(object_->worldTransform.matWorld_) - Affin::GetWorldTrans(reticle->worldTransform.matWorld_));

	for (int i = 0; i < SPHERE_COLISSION_NUM; i++) {

		sphere[i] = new SphereCollider;
		CollisionManager::GetInstance()->AddCollider(sphere[i]);
		spherePos[i] = Affin::GetWorldTrans(object_->worldTransform.matWorld_);
		sphere[i]->SetObject3d(object_);
		//sphere[i]->SetBasisPos(&spherePos[i]);
		sphere[i]->SetRadius(object_->worldTransform.scale_.x);
		sphere[i]->Update();
		sphere[i]->SetAttribute(COLLISION_ATTR_POWERCHIP_AREA);

		//test
		coliderPosTest_[i] = Object3d::Create();
		coliderPosTest_[i]->SetModel(model_);
		coliderPosTest_[i]->worldTransform.translation_ = sphere[i]->center;
		coliderPosTest_[i]->worldTransform.scale_ = Vector3{ sphere[i]->GetRadius(),sphere[i]->GetRadius() ,sphere[i]->GetRadius() };
		coliderPosTest_[i]->worldTransform.rotation_ = { 0,0,0 };
		coliderPosTest_[i]->Update();
	}

	/*ray = new RayCollider;
	ray->SetStart(Affin::GetWorldTrans(object_->wtf.matWorld));
	ray->SetDir(rayvec);
	ray->SetObject3d(object_);
	CollisionManager::GetInstance()->AddCollider(ray);
	rayHit = new RaycastHit;*/
}

/// エリアの更新を行う
void ChipArea::Update() {
	object_->worldTransform.translation_.z = 1;
	object_->worldTransform.scale_ = {2.5f,2.5f,1.0f};

	for (int i = 0; i < SPHERE_COLISSION_NUM; i++) {
		sphere[i]->SetRadius(object_->worldTransform.scale_.x);
		coliderPosTest_[i]->worldTransform.translation_ = sphere[i]->center;
		spherePos[i] = object_->worldTransform.translation_;
		if (sphere[i]->GetIsHit() == true && sphere[i]->GetCollisionInfo().collider->GetAttribute() == COLLISION_ATTR_POWERCHIP) {
			isSet = true;
		}
		else {
			isSet = false;
		}
	}
	for (int i = 0; i < SPHERE_COLISSION_NUM; i++) {

		/*coliderPosTest_[i]->wtf.position = ray->GetDir();*/
		sphere[i]->Update();
		coliderPosTest_[i]->Update();
	}
	object_->Update();
}

/// エリアの描画を行う
void ChipArea::Draw(DirectXCommon* dxCommon) {
	Object3d::PreDraw(dxCommon->GetCommandList());
	object_->Draw();
	//reticle->Draw();
	//coliderPosTest_[0]->Draw();
	Object3d::PostDraw();
}

/// リセットを行う
void ChipArea::Reset() {

}