#include "PlayerJump.h"
#include "CollisionAttribute.h"
#include "ImguiManager.h"
PlayerJump::PlayerJump(PlayerActionManager* ActionManager, std::vector<SphereCollider*>sphere, std::vector<Vector3> spherePos)
{
	ActionManager_ = ActionManager;
	sphere_ = sphere;
	spherePos_ = spherePos;
}

PlayerJump::~PlayerJump()
{
}

void PlayerJump::Initialize(Object3d* object)
{
	object_ = object;
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

	CheckCollision();

	ImGui::Begin("Jump");
	ImGui::SetWindowPos({ 500, 100 });
	ImGui::InputFloat("Height", &jumpHeight);

	ImGui::End();

}

void PlayerJump::Draw()
{
}

void PlayerJump::Jump()
{

	object_->worldTransform.translation_.y += jumpHeight;
	if (jumpHeight < 0.0f)
	{
		/*object_->worldTransform.translation_.y = 0.0f;*/
		isJump_ = false;
	}
	jumpHeight -= gravity;
}


void PlayerJump::ParamReset()
{
	jumpHeight = 2.0f;
}

void PlayerJump::Gravity()
{
	//sitamuki
	const float fallacc = -0.01f;
	const float fallVY = -0.2f;
	//kasoku
	fallV.y = max(fallV.y + fallacc, fallVY);
	object_->worldTransform.translation_.x += fallV.x;
	object_->worldTransform.translation_.y += fallV.y;
	object_->worldTransform.translation_.z += fallV.z;
}

void PlayerJump::CheckCollision()
{
	for (int i = 0; i < SPHERE_COLISSION_NUM; i++)
	{
		if (sphere_[i]->GetIsHit() == true)
		{
			isJump_ = false;
		}
		if (sphere_[i]->GetIsHit() == false)
		{
			if (isJump_ == false)
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
