#include "PlayerActionManager.h"
#include "PlayerMove.h"

PlayerActionManager::PlayerActionManager()
{
	action_.reset(new PlayerMove(&*this));
}

PlayerActionManager::~PlayerActionManager()
{

}

void PlayerActionManager::ActionInitialize(Object3d* object)
{
	object_ = object;
	action_.get()->Initialize(object_);
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
	ActionInitialize(object_);
	action_.get()->Initialize(object_);
}
