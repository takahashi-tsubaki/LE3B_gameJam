#pragma once
#include <memory>
#include <stack>

#include "FbxObject3d.h"

class Input;
class GamePad;
class MouseInput;
class PlayerAction;


enum ActionNum
{
	Stop = 0,
	Move = 1,
	Dash = 2,
	Jump = 3,

};

class PlayerActionManager
{
private:
	std::shared_ptr<PlayerAction> action_;
public:
	//コンストラクタ
	PlayerActionManager();
	//デストラクタ
	~PlayerActionManager();

public:
	void ActionInitialize(FbxObject3d* fbxObject);

	void ActionUpdate(Input* input, GamePad* gamePad);

	void ActionDraw();
	// シーンを変更する
	void ChangeAction(PlayerAction* Action);

public:

	void SetActionNum(int actionNum) {actionNum_ = actionNum;}

	int GetActionNum() { return actionNum_; }
private:
	FbxObject3d* fbxObject_;
	int actionNum_ = 0;
};
