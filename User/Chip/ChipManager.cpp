#include "ChipManager.h"

ChipManager::ChipManager()
{
}

ChipManager::~ChipManager()
{
}

void ChipManager::Initialize(int junpnum, int runnum, int areanum)
{
	chip_ = new Chip();
	chip_->Initialize();
	chip_->object_->worldTransform.translation_ = { -30,-20,0 };
	chip_->object_->color_ = { 1,0,0,1 };
	AddChip("1B", chip_);

	chip2_ = new Chip();
	chip2_->Initialize();
	chip2_->object_->worldTransform.translation_ = { -30,-25,0 };
	chip2_->object_->color_ = { 0,0,1,1 };
	AddChip("1R", chip2_);

	chipArea_ = new ChipArea();
	chipArea_->Initialize();
	chipArea_->SetPos({ -33.5f,27.5f,0.0f });
	AddChipArea("A1", chipArea_);

	chipArea2_ = new ChipArea();
	chipArea2_->Initialize();
	chipArea2_->SetPos({ -33.5f,17.5f,0.0f });
	AddChipArea("A2", chipArea2_);
}

void ChipManager::Update(Input* input, MouseInput* mouse)
{

	for (Chip* chip : chips_) {
		chip->Update(input, mouse);
	}
	for (ChipArea* area : chipAreas_) {
		area->Update();
	}
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
	for (ChipArea* area : chipAreas_) {
		for (Chip* chip : chips_) {
			chip->object_->worldTransform.translation_;
			area->object_->worldTransform.translation_;
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

void ChipManager::modeChangePos(int num)
{
	if (num == 0)
	{
		chipArea_->SetPos({ -33.5f,27.5f,0.0f });
		
		chipArea2_->SetPos({ -33.5f,17.5f,0.0f });
	}
	else if (num == 1)
	{
		chipArea_->SetPos({ -42.0f,20.0f,0.0f });

		chipArea2_->SetPos({ -25.0f,20.0f,0.0f });
	}
}
