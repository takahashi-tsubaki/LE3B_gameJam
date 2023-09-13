#pragma once
#include <memory>
#include <stack>

#include "FbxObject3d.h"

#include "Object3d.h"

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
	JumpDash = 4,
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
	void ActionInitialize(Object3d* object);

	void ActionUpdate(Input* input, GamePad* gamePad);

	void ActionDraw();
	// シーンを変更する
	void ChangeAction(PlayerAction* Action);

public:

	void SetActionNum(int actionNum) {actionNum_ = actionNum;}

	int GetActionNum() { return actionNum_; }
private:
	FbxObject3d* fbxObject_;
	Object3d* object_;
	int actionNum_ = 0;
};

