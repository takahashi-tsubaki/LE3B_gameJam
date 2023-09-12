#include "PlayerDash.h"
#include "CollisionAttribute.h"
PlayerDash::PlayerDash(PlayerActionManager* ActionManager, std::vector<SphereCollider*>sphere, std::vector<Vector3> spherePos)
{
	ActionManager_ = ActionManager;
	sphere_ = sphere;
	spherePos_ = spherePos;
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
	CheckCollision();
}

void PlayerDash::Draw()
{
	
}

void PlayerDash::Dash()
{
	
	velocity_ = { speed_,0,0 };
	object_->worldTransform.translation_ += velocity_;
	//if (speed_ < MAX_ACCEL)
	//{
	//	isAccel_ = true;
	//	isDecel_ = false;
	//}
	
	if (speed_ >= MAX_ACCEL)
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
		speed_ += accel;
	}
	if (isDecel_ == true)
	{
		speed_ -= accel;
	}
	if (speed_ <= 0)
	{
		isDash_ = false;
	}
	
}

void PlayerDash::ResetParams()
{
	isDash_ = false;
	isDecel_ = false;
	isAccel_ = false;

	speed_ = 0.5f;
	DashFlameCount = 5.0f;
}

void PlayerDash::CheckCollision()
{

	for (int i = 0; i < SPHERE_COLISSION_NUM; i++)
	{
		if (sphere_[i]->GetIsHit() == true)
		{
			//当たったものの属性が敵だった時
			if (sphere_[i]->GetCollisionInfo().collider->GetAttribute() == COLLISION_ATTR_WALL)
			{
				DashFlameCount = 0;
				speed_ = 0.0f;
			}
			
		}
		if (sphere_[i]->GetIsHit() == false)
		{
			if (isDash_ == true)
			{
				isAccel_ = true;
				isDecel_ = false;
			}

		}
	}
	

	
	for (int i = 0; i < SPHERE_COLISSION_NUM; i++) {

		spherePos_[i] = object_->worldTransform.translation_;
		sphere_[i]->Update();
	}
}
