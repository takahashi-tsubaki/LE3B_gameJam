#pragma once
#include "Chip.h"
#include "ChipArea.h"
#include <string>
#include <map>
#include <vector>

class ChipManager // 電池を統括＆動きを決定するようにするクラス
{
public:
	ChipManager();
	~ChipManager();

	void Initialize(int junpnum = 2, int runnum = 2, int areanum = 2);
	void Update(Input* input, MouseInput* mouse);
	void Draw(DirectXCommon* dxCommon);

	void SearchPair();

	
	void Reset() { chips_.clear(); };
	void AddChip(std::string chipName, Chip* chip);
	void AddChipArea(std::string chipAreaName, ChipArea* chipArea);
private:



	std::map<std::string ,Chip* > chipMap_;

	std::vector<Chip*> chips_;
	std::vector<ChipArea*> chipAreas_;

	/// <summary>
	/// 仮宣言 ⇩
	/// </summary>
	Chip* chip_ = nullptr;
	ChipArea* chipArea_ = nullptr;
	Chip* chip2_ = nullptr;
	ChipArea* chipArea2_ = nullptr;
};
