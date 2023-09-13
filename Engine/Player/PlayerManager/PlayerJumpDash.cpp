#include "PlayerJumpDash.h"

PlayerJumpDash::PlayerJumpDash(PlayerActionManager* ActionManager, std::vector<SphereCollider*> sphere, std::vector<Vector3> spherePos)
{
	ActionManager_ = ActionManager;
	sphere_ = sphere;
	spherePos_ = spherePos;
}

PlayerJumpDash::~PlayerJumpDash()
{
	
}

void PlayerJumpDash::Initialize(Object3d* object)
{
	object_ = object;
}

void PlayerJumpDash::Update(Input* input, GamePad* gamePad)
{
	if (input->TriggerKey(DIK_SPACE))
	{
		if (isJumpDash_ == false)
		{
			isJumpDash_ = true;
		}
	}
	if (isJumpDash_ == true)
	{
		JumpDash(input);
	}
	else
	{
		ParamReset();
	}
}

void PlayerJumpDash::Draw()
{
}

void PlayerJumpDash::JumpDash(Input* input)
{
	velocity_.y = jumpHeight;
	if (input->PushKey(DIK_A))
	{
		velocity_.x = speed*-1;
		
		/*gameObject_->SetPosition({ gameObject_->GetPosition().x-1.0f,gameObject_->GetPosition().y,gameObject_->GetPosition().z + 1.0f });*/
	}
	if (input->PushKey(DIK_D))
	{
		velocity_.x = speed;
		object_->worldTransform.translation_ += velocity_;
		/*gameObject_->SetPosition({ gameObject_->GetPosition().x+1.0f,gameObject_->GetPosition().y,gameObject_->GetPosition().z + 1.0f });*/
	}

	object_->worldTransform.translation_ += velocity_;

	if (jumpHeight < 0.0f)
	{
		isJumpDash_ = false;
	}
	jumpHeight -= gravity;
}

void PlayerJumpDash::ParamReset()
{
	jumpHeight = 2.0f;
	velocity_ = { 0,0,0 };
}

void PlayerJumpDash::Gravity()
{
	//sitamuki
	const float fallacc = -0.02f;
	const float fallVY = -0.5f;
	//kasoku
	fallV.y = max(fallV.y + fallacc, fallVY);
	object_->worldTransform.translation_.x += fallV.x;
	object_->worldTransform.translation_.y += fallV.y;
	object_->worldTransform.translation_.z += fallV.z;
}

void PlayerJumpDash::CheckCollision()
{
	for (int i = 0; i < SPHERE_COLISSION_NUM; i++)
	{
		if (sphere_[i]->GetIsHit() == true)
		{
			isJumpDash_ = false;
		}
		if (sphere_[i]->GetIsHit() == false)
		{
			if (isJumpDash_ == false)
			{
				Gravity();
			}
		}
	}
	for (int i = 0; i < SPHERE_COLISSION_NUM; i++) {

		spherePos_[i] = object_->worldTransform.translation_;
		sphere_[i]->Update();
	}
}
