#pragma once
#include "Chip.h"
#include "ChipArea.h"
#include <string>
#include <map>
#include <vector>
#include "ChipPattern.h"

class ChipManager // 電池を統括＆動きを決定するようにするクラス
{
public:
	ChipManager();
	~ChipManager();

	void Initialize(int junpnum = 2, int runnum = 2, int areanum = 2);
	void Update(Input* input, MouseInput* mouse);
	void Draw(DirectXCommon* dxCommon);

	void SearchPair();

	void CollisionUpdate();

	int MakePattern();

	void Reset() { chips_.clear(); };
	void AddChip(std::string chipName, Chip* chip);
	void AddChipArea(std::string chipAreaName, ChipArea* chipArea);

	void InitializeChip(int junpnum = 2, int runnum = 2);
	void InitializeArea();
	void ChangeParallel(Input* input);
	unsigned short GetPattern() { return pattern; };
private:
	unsigned short pattern;
	bool isParallel = true;


	//std::map<std::string ,Chip* > chipMap_;

	//std::string chipST;
	std::vector<Chip*> chips_;
	//std::string areaST;
	std::vector<ChipArea*> chipAreas_;

	/// <summary>
	/// 仮宣言 ⇩
	/// </summary>
	Chip* newChipDash = nullptr;
	ChipArea* chipArea_ = nullptr;
	Chip* newChipJunp = nullptr;
	ChipArea* chipArea2_ = nullptr;



public:
	Model* model_ = nullptr;
	Object3d* mouse_ = nullptr;
	float mouseSensitivity_ = 0.099f;	//マウス感度 0.05
	//コライダー
	/// <summary>
	/// 当たり判定
	/// </summary>
	Vector3 collposA, collposB;
public:
	void SetSphere(SphereCollider* sphere_) { sphere = sphere_; }
	SphereCollider* GetSphere() { return sphere; }
private:
	SphereCollider* sphere = nullptr;
};
