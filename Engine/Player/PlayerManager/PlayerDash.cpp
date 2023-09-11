#include "PlayerDash.h"

PlayerDash::PlayerDash(PlayerActionManager* ActionManager)
{
	ActionManager_ = ActionManager;
}

PlayerDash::~PlayerDash()
{
}

void PlayerDash::Initialize(Object3d* object)
{
	object_ = object;
}

void PlayerDash::Update(Input* input, GamePad* gamePad)
{
	if (input->TriggerKey(DIK_SPACE))
	{
		if (isDash_ == false)
		{
			isDash_ = true;
		}
	}
	if (isDash_ == true)
	{
		Dash();
	}
	else
	{
		ResetParams();
	}
}

void PlayerDash::Draw()
{
	
}

void PlayerDash::Dash()
{
	velocity_ = { speed,0,0 };
	object_->worldTransform.translation_ += velocity_;
	if (speed < MAX_ACCEL)
	{
		isAccel_ = true;
		isDecel_ = false;
	}
	else
	{
		DashFlameCount--;
	}
	
	if (DashFlameCount < 0)
	{
		isDecel_ = true;
		isAccel_ = false;
	}
	if (isAccel_ == true)
	{
		speed += accel;
	}
	if (isDecel_ == true)
	{
		speed -= accel;
	}
	if (speed <= 0)
	{
		isDash_ = false;
	}
}

void PlayerDash::ResetParams()
{
	isDash_ = false;
	isDecel_ = false;
	isAccel_ = false;

	speed = 0.5f;
	DashFlameCount = 30.0f;
}
