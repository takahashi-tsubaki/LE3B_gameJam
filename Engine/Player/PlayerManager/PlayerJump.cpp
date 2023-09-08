#include "PlayerJump.h"

PlayerJump::PlayerJump(PlayerActionManager* ActionManager)
{
	ActionManager_ = ActionManager;
}

PlayerJump::~PlayerJump()
{
}

void PlayerJump::Initialize(FbxObject3d* fbxObject)
{
	fbxObject_ = fbxObject;
}

void PlayerJump::Update(Input* input, GamePad* gamePad)
{
	if (input->PushKey(DIK_W))
	{
		velocity_ = { 0,speed,0 };
		fbxObject_->worldTransform.translation_ += velocity_;
	}
	if (input->PushKey(DIK_S))
	{
		velocity_ = { 0,-speed,0 };
		fbxObject_->worldTransform.translation_+= velocity_;
	}
}

void PlayerJump::Draw()
{
}
