#include "PlayerActionManager.h"
#include "PlayerMove.h"

PlayerActionManager::PlayerActionManager()
{
	action_.reset(new PlayerMove(&*this));
}

PlayerActionManager::~PlayerActionManager()
{

}

void PlayerActionManager::ActionInitialize(FbxObject3d* fbxObject)
{
	fbxObject_ = fbxObject;
	action_.get()->Initialize(fbxObject);
}

void PlayerActionManager::ActionUpdate(Input* input, GamePad* gamePad)
{
	action_.get()->Update(input,gamePad);
}

void PlayerActionManager::ActionDraw()
{
	action_.get()->Draw();
}

void PlayerActionManager::ChangeAction(PlayerAction* Action)
{
	action_.reset(Action);
	ActionInitialize(fbxObject_);
	action_.get()->Initialize(fbxObject_);
}
