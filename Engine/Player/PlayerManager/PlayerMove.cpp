#include "PlayerMove.h"

PlayerMove::PlayerMove(PlayerActionManager* ActionManager)
{
	ActionManager_ = ActionManager;
}

PlayerMove::~PlayerMove()
{
}

void PlayerMove::Initialize(FbxObject3d* gameObject)
{
	gameObject_ = gameObject;
}

void PlayerMove::Update(Input* input, GamePad* gamePad)
{
	if (input->PushKey(DIK_W))
	{
		velocity_ = { 0,0,speed };
		gameObject_->worldTransform.translation_ += velocity_;
	}
	if (input->PushKey(DIK_S))
	{
		velocity_ = { 0,0,-speed };
		gameObject_->worldTransform.translation_ += velocity_;
	}
	if (input->PushKey(DIK_A))
	{
		velocity_ = { -speed,0,0 };
		gameObject_->worldTransform.translation_ += velocity_;
		/*gameObject_->SetPosition({ gameObject_->GetPosition().x-1.0f,gameObject_->GetPosition().y,gameObject_->GetPosition().z + 1.0f });*/
	}
	if (input->PushKey(DIK_D))
	{
		velocity_ = { speed, 0,0 };
		gameObject_->worldTransform.translation_ += velocity_;
		/*gameObject_->SetPosition({ gameObject_->GetPosition().x+1.0f,gameObject_->GetPosition().y,gameObject_->GetPosition().z + 1.0f });*/
	}
}

void PlayerMove::Draw()
{
}
