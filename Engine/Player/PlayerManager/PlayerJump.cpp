#include "PlayerJump.h"
#include "CollisionAttribute.h"
#include "ImguiManager.h"
PlayerJump::PlayerJump(PlayerActionManager* ActionManager)
{
	ActionManager_ = ActionManager;

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
			ParamReset();
			jumpHeight *= (panelCount);//ジャンプのパネルの枚数により高さを変化させる
			isJump_ = true;
		}
	}
	if (isJump_ == true)
	{
		Jump();
	}
	/*CheckCollision();*/

	/*ImGui::Begin("Jump");
	ImGui::SetWindowPos({ 500, 100 });
	ImGui::InputFloat("Height", &jumpHeight);

	ImGui::End();*/

}

void PlayerJump::Draw()
{
}

void PlayerJump::Jump()
{
	jumpTimer += 0.2f;
	if (jumpTimer > 12.0f)
	{
		isJump_ = false;
		jumpTimer = 0.0f;
	}

	object_->worldTransform.translation_.y += jumpHeight;
	if (jumpHeight < 0.0f)
	{
		/*object_->worldTransform.translation_.y = 0.0f;*/
		jumpHeight = 0.0f;
	}
	else
	{
		jumpHeight -= gravity;
	}
	
}


void PlayerJump::ParamReset()
{
	jumpHeight = 2.0f;
}

void PlayerJump::Gravity()
{
	//if (jumpHeight < 0.0f)
	//{
	//	//sitamuki
	//	const float fallacc = -0.02f;
	//	const float fallVY = -0.5f;
	//	//kasoku
	//	fallV.y = max(fallV.y + fallacc, fallVY);
	//	object_->worldTransform.translation_.x += fallV.x;
	//	object_->worldTransform.translation_.y += fallV.y;
	//	object_->worldTransform.translation_.z += fallV.z;
	//}
	
}

void PlayerJump::CheckCollision()
{
}
