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
	AddChip("1RED", chip_);

	chip2_ = new Chip();
	chip2_->Initialize();
	chip2_->object_->worldTransform.translation_ = { -30,-25,0 };
	chip2_->object_->color_ = { 0,0,1,1 };
	AddChip("1RED", chip2_);

	chipArea_ = new ChipArea();
	chipArea_->Initialize();
	chipArea_->SetPos({ -43.0f,25.0f,0.0f });
	AddChipArea("1", chipArea_);

	chipArea2_ = new ChipArea();
	chipArea2_->Initialize();
	chipArea2_->SetPos({ -43.0f,17.0f,0.0f });
	AddChipArea("2", chipArea2_);
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
