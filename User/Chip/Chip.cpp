#include "Chip.h"
#include "imgui.h"


Chip::Chip()
{
}

Chip::~Chip()
{
}

/// シーンの更新を行う
void Chip::Initialize() {

	nowDrag_ = false;
	isChipGet_ = false;

	model_ = Model::CreateFromOBJ("Cube2");

	object_ = Object3d::Create();
	object_->SetModel(model_);
	object_->Initialize();
	object_->position_ = { 0,0,1 };

	reticle = Object3d::Create();
	reticle->SetModel(model_);
	reticle->Initialize();
	reticle->position_ = { 10,0,10 };

	//当たり判定用
	SPHERE_COLISSION_NUM = 2;
	sphere.resize(SPHERE_COLISSION_NUM);
	spherePos.resize(SPHERE_COLISSION_NUM);
	//FbxO_.get()->isBonesWorldMatCalc = true;	// ボーンの行列を取得するか
	coliderPosTest_.resize(SPHERE_COLISSION_NUM);

	//rayvec = Affin::GetWorldTrans(reticle->wtf.matWorld) - Affin::GetWorldTrans(object_->wtf.matWorld);
	//rayvec = -(Affin::GetWorldTrans(object_->worldTransform.matWorld_) - Affin::GetWorldTrans(reticle->worldTransform.matWorld_));

	for (int i = 0; i < SPHERE_COLISSION_NUM; i++) {
		if (i == 0) {
			sphere[i] = new SphereCollider;
			CollisionManager::GetInstance()->AddCollider(sphere[i]);
			sphere[i]->SetObject3d(object_);
			sphere[i]->SetRadius(1.0f);
			sphere[i]->Update();
			sphere[i]->SetAttribute(COLLISION_ATTR_POWERCHIP);
		}
		if (i == 1) {
			sphere[i] = new SphereCollider;
			CollisionManager::GetInstance()->AddCollider(sphere[i]);
			sphere[i]->SetObject3d(reticle);
			sphere[i]->SetRadius(1.0f);
			sphere[i]->Update();
			sphere[i]->SetAttribute(COLLISION_ATTR_CURSOR);
		}

		//test
		coliderPosTest_[i] = Object3d::Create();
		coliderPosTest_[i]->SetModel(model_);
		coliderPosTest_[i]->worldTransform.translation_ = rayvec;
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

/// シーンの更新を行う
void Chip::Update(Input* input, MouseInput* mouse) {
	if (input) {

	}

	Vector2 mousepos = mouse->GetMousePosition();
	reticle->worldTransform.translation_ = { reticle->GetCamera()->eye_.x +(mousepos.x * mouseSensitivity_),reticle->GetCamera()->eye_.y +(mousepos.y * mouseSensitivity_),0 };	/// カメラ座標「目」｛0，0，-100｝前提

	if (mouse->PushMouseButton(0)) {
		if (nowDrag_ == false) {
			nowDrag_ = true;

			isAreaSet = false;
		}

	}
	else {
		nowDrag_ = false;
	}

	for (int i = 0; i < SPHERE_COLISSION_NUM; i++) {

		if (sphere[0]->GetIsHit() == true && sphere[0]->GetCollisionInfo().collider->GetAttribute() == COLLISION_ATTR_CURSOR &&
			sphere[0]->GetCollisionInfo().collider->GetCollisionInfo().object == object_ && isAreaSet == false) {
			mousePos_ = sphere[0]->GetCollisionInfo().object->worldTransform.translation_;
			if (nowDrag_ == true) {
				isChipGet_ = true;
			}
			else {
				isChipGet_ = false;
			}


		}

		if (sphere[0]->GetIsHit() == true && sphere[0]->GetCollisionInfo().collider->GetAttribute() == COLLISION_ATTR_POWERCHIP_AREA &&
			sphere[0]->GetCollisionInfo().collider->GetCollisionInfo().object == object_) {
			areaPos_ = sphere[0]->GetCollisionInfo().object->worldTransform.translation_;

			isAreaSet = true;
			isChipGet_ = false;
		}


	}
	ImGui::Begin("chipFlag");
	if (isChipGet_ == true) {
		ImGui::Text("a");
		object_->worldTransform.translation_ = mousePos_;
		object_->worldTransform.translation_.x = mousePos_.x;
		object_->worldTransform.translation_.y = mousePos_.y;
		object_->worldTransform.translation_.z = mousePos_.z;
	}
	if (sphere[0]->GetIsHit() != true && sphere[0]->GetCollisionInfo().collider->GetAttribute() != COLLISION_ATTR_POWERCHIP_AREA && nowDrag_ == false) {
		object_->worldTransform.translation_ = restPos_;
		object_->worldTransform.translation_.x = object_->GetCamera()->eye_.x + restPos_.x;
		object_->worldTransform.translation_.y = object_->GetCamera()->eye_.y + restPos_.y;
		object_->worldTransform.translation_.z = restPos_.z;
	}
	if (isAreaSet == true) {
		ImGui::Text("b");
		//object_->worldTransform.translation_ = areaPos_;
		object_->worldTransform.translation_.x = areaPos_.x;
		object_->worldTransform.translation_.y = areaPos_.y;
		object_->worldTransform.translation_.z = 0;
	}
	/*if (isAreaSet == false && isChipGet_ == false && nowDrag_ == false) {
		object_->worldTransform.translation_.x = object_->GetCamera()->eye_.x + restPos_.x;
		object_->worldTransform.translation_.y = object_->GetCamera()->eye_.y + restPos_.y;
	}*/

	ImGui::Text("c");
	ImGui::End();

	for (int i = 0; i < SPHERE_COLISSION_NUM; i++) {

		coliderPosTest_[i]->worldTransform.translation_ = sphere[i]->center;
		sphere[i]->Update();
		coliderPosTest_[i]->Update();
	}
	object_->Update();
	reticle->Update();
}

/// シーンの描画を行う
void Chip::Draw(DirectXCommon* dxCommon) {
	Object3d::PreDraw(dxCommon->GetCommandList());
	object_->Draw();
	coliderPosTest_[0]->Draw();
	coliderPosTest_[1]->Draw();
	Object3d::PostDraw();
}

/// リセットを行う
void Chip::Reset() {

}