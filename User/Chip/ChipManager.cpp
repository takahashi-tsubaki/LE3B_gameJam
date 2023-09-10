#include "ChipManager.h"

ChipManager::ChipManager()
{
}

ChipManager::~ChipManager()
{
}



void ChipManager::AddChip(std::string chipName, Chip* chip)
{
	assert(chip);
	chips_.insert(std::make_pair(chipName, chip));
}
