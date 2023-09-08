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
		panelCount = 1.5f;
	}
	if (input->PushKey(DIK_S))
	{
		panelCount = 1.0f;
	}
	if (input->TriggerKey(DIK_SPACE))
	{
		if (isJump_ == false)
		{
			jumpHeight *= (panelCount);//ジャンプのパネルの枚数により高さを変化させる
			isJump_ = true;
		}
	}
	if (isJump_ == true)
	{
		Jump();
	}
	else
	{
		ParamReset();
	}
}

void PlayerJump::Draw()
{
}

void PlayerJump::Jump()
{

	fbxObject_->worldTransform.translation_.y += jumpHeight;
	if (fbxObject_->worldTransform.translation_.y < 0.0f)
	{
		fbxObject_->worldTransform.translation_.y = 0.0f;
		isJump_ = false;
	}
	jumpHeight -= gravity;
}

void PlayerJump::ParamReset()
{
	jumpHeight = 10.0f;
}