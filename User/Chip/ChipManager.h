#pragma once
#include "Chip.h"
#include "ChipArea.h"
#include <string>
#include <map>

class ChipManager // 電池を統括＆動きを決定するようにするクラス
{
public:
	ChipManager();
	~ChipManager();


	
	void Reset() { chips_.clear(); };
	void AddChip(std::string chipName, Chip* chip);
private:
	std::map<std::string, Chip*> chips_;
};
