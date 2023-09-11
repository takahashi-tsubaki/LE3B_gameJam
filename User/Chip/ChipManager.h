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

	void CollisionUpdate();

	int MakePattern();

	void Reset() { chips_.clear(); };
	void AddChip(std::string chipName, Chip* chip);
	void AddChipArea(std::string chipAreaName, ChipArea* chipArea);
private:
	int pattern = 0;


	std::map<std::string ,Chip* > chipMap_;

	std::string chipST;
	std::vector<Chip*> chips_;
	std::string areaST;
	std::vector<ChipArea*> chipAreas_;

	/// <summary>
	/// 仮宣言 ⇩
	/// </summary>
	Chip* chipR_ = nullptr;
	ChipArea* chipArea_ = nullptr;
	Chip* chipB_ = nullptr;
	ChipArea* chipArea2_ = nullptr;



public:
	Model* model_;
	Object3d* mouse_;
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
	SphereCollider* sphere;
};
