#include "ChipManager.h"

#include "imgui.h"

ChipManager::ChipManager()
{
}

ChipManager::~ChipManager()
{
}

void ChipManager::Initialize(int junpnum, int runnum, int areanum)
{
	InitializeChip(junpnum, runnum);

	InitializeArea();

	model_ = Model::CreateFromOBJ("Cube1");

	mouse_ = Object3d::Create();
	mouse_->SetModel(model_);
	mouse_->Initialize();
	mouse_->position_ = { 0,0,0 };

	sphere = new SphereCollider;
	CollisionManager::GetInstance()->AddCollider(sphere);
	sphere->SetObject3d(mouse_);
	sphere->SetRadius(mouse_->worldTransform.scale_.x);
	sphere->Update();
	sphere->SetAttribute(COLLISION_ATTR_CURSOR);
}

void ChipManager::Update(Input* input, MouseInput* mouse)
{
	Vector2 mousepos = mouse->GetMousePosition();
	mouse_->worldTransform.translation_ = { mousepos.x * mouseSensitivity_,mousepos.y * mouseSensitivity_,0 };	/// カメラ座標「目」｛0，0，-100｝前提
	//if (sphere->GetIsHit() == true && sphere->GetCollisionInfo().collider->GetAttribute() == COLLISION_ATTR_POWERCHIP) {
	//	mouse_->position_.z = 1;
	//}
	ChangeParallel(input);
	CollisionUpdate();
	pattern = MakePattern();
	ImGui::Begin("ChipPatteern");
	ImGui::Text("Pattern: %d", pattern);
	ImGui::Text("isParallel: %d", isParallel);
	for (ChipArea* area : chipAreas_) {
		area->Update();
	}
	for (Chip* chip : chips_) {
		chip->Update(input, mouse);
	}
	ImGui::End();

	sphere->Update();
}

void ChipManager::Draw(DirectXCommon* dxCommon)
{

	for (ChipArea* area : chipAreas_) {
		area->Draw(dxCommon);
	}
	for (Chip* chip : chips_) {
		chip->Draw(dxCommon);
	}

}

void ChipManager::SearchPair()
{

}

void ChipManager::CollisionUpdate()
{
	/// <summary>
	/// 当たり判定
	/// </summary>
	for (ChipArea* area : chipAreas_) {
		collposA = area->object_->worldTransform.translation_;
		//敵更新
		for (Chip* chip : chips_) {
			collposB = chip->object_->worldTransform.translation_;
			float a =
				std::powf(collposB.x - collposA.x, 2.0f) +
				std::powf(collposB.y - collposA.y, 2.0f) +
				std::powf(collposB.z - collposA.z, 2.0f);
			float lenR = std::powf((area->GetSphere()[0]->radius + chip->GetSphere()[0]->radius), 2.0);

			// 球と球の交差判定
			if (a <= lenR) {
				area->OnColision(chip);
			}
		}
	}
	//for (ChipArea* area : chipAreas_) {
	//	//敵更新
	//	for (Chip* chip : chips_) {
	//		if (area->GetSphere()[0]->GetIsHit() == true && area->GetSphere()[0]->GetCollisionInfo().object == chip->object_ ) {
	//			area->OnColision(chip);
	//		}

	//	}
	//}
}

int ChipManager::MakePattern()
{
	if (chipAreas_[0]->subject == nullptr || chipAreas_[1]->subject == nullptr) {
		return 0;
	}
	if (isParallel == true) {
		if (chipAreas_[0]->subject->HowTribe() == 1 && chipAreas_[1]->subject->HowTribe() == 1 ||
			chipAreas_[0]->subject->HowTribe() == 1 && chipAreas_[1]->subject->HowTribe() == 1) {
			return 0b1 << 1;
		}
		if (chipAreas_[0]->subject->HowTribe() == 1 && chipAreas_[1]->subject->HowTribe() == 2 ||
			chipAreas_[0]->subject->HowTribe() == 2 && chipAreas_[1]->subject->HowTribe() == 1) {
			return 0b1 << 2;
		}
		if (chipAreas_[0]->subject->HowTribe() == 2 && chipAreas_[1]->subject->HowTribe() == 2 ||
			chipAreas_[0]->subject->HowTribe() == 2 && chipAreas_[1]->subject->HowTribe() == 2) {
			return 0b1 << 3;
		}
	}
	if (isParallel == false) {
		if (chipAreas_[0]->subject->HowTribe() == 1 && chipAreas_[1]->subject->HowTribe() == 1 ||
			chipAreas_[0]->subject->HowTribe() == 1 && chipAreas_[1]->subject->HowTribe() == 1) {
			return 0b1 << 4;
		}
		if (chipAreas_[0]->subject->HowTribe() == 1 && chipAreas_[1]->subject->HowTribe() == 2 ||
			chipAreas_[0]->subject->HowTribe() == 2 && chipAreas_[1]->subject->HowTribe() == 1) {
			return 0b1 << 5;
		}
		if (chipAreas_[0]->subject->HowTribe() == 2 && chipAreas_[1]->subject->HowTribe() == 2 ||
			chipAreas_[0]->subject->HowTribe() == 2 && chipAreas_[1]->subject->HowTribe() == 2) {
			return 0b1 << 6;
		}
	}
}

void ChipManager::AddChip(std::string chipName, Chip* chip)
{
	assert(chip);
	chips_.emplace_back(chip);
}

void ChipManager::AddChipArea(std::string chipAreaName, ChipArea* chipArea)
{
	assert(chipArea);
	chipAreas_.emplace_back(chipArea);
}

void ChipManager::InitializeChip(int junpnum, int runnum)
{
	float dY = -20;
	for (int i = 0; i < runnum; i++) {
		Chip* newChipDash = new Chip();
		newChipDash->Initialize();
		newChipDash->SetTribe(1);
		newChipDash->object_->worldTransform.translation_ = { -30,dY,0 };
		dY += 5;
		newChipDash->object_->color_ = { 1,0,0,1 };
		AddChip("1R", newChipDash);
	}


	float jY = -20;
	for (int i = 0; i < junpnum; i++) {
		newChipJunp = new Chip();
		newChipJunp->Initialize();
		newChipJunp->SetTribe(2);
		newChipJunp->object_->worldTransform.translation_ = { -35,jY,0 };
		jY += 5;
		newChipJunp->object_->color_ = { 0,0,1,1 };
		AddChip("1B", newChipJunp);
	}

}

void ChipManager::InitializeArea()
{

	chipArea_ = new ChipArea();
	chipArea_->Initialize();
	chipArea_->SetTribe(1);
	chipArea_->SetPos({ -43.0f,25.0f,0.0f });
	AddChipArea("A1", chipArea_);

	chipArea2_ = new ChipArea();
	chipArea2_->Initialize();
	chipArea2_->SetTribe(2);
	chipArea2_->SetPos({ -43.0f,17.0f,0.0f });
	AddChipArea("A2", chipArea2_);
}

void ChipManager::ChangeParallel(Input* input)
{
	if (input->TriggerKey(DIK_R)) {
		if (isParallel == true) {
			isParallel = false;
		}
		else {
			isParallel = true;
		}
	}
	if (isParallel == true) {
		chipArea_->SetPos({ -43.0f,25.0f,0.0f });
		chipArea2_->SetPos({ -43.0f,17.0f,0.0f });
	}
	else {

	}
}
