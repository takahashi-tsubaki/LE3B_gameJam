#pragma once
#include "PlayerAction.h"
class PlayerJump :
	public PlayerAction
{
protected:
	PlayerActionManager* ActionManager_;
public:
	PlayerJump(PlayerActionManager* ActionManager);
	~PlayerJump() override;

	void Initialize(FbxObject3d* gameObject) override;
	void Update(Input* input, GamePad* gamePad) override;
	void Draw()override;
	void Jump();

	void SetIsJump(bool isJump) { isJump_ = isJump; }
	bool GetIsJump() { return isJump_; }

	//ジャンプの変数のリセット
	void ParamReset();
private:
	FbxObject3d* fbxObject_;
	Vector3 velocity_{ 0,0,0 };
	float speed = 0.5f;
	float jumpHeight = 10.0f;
	const float gravity = 1.0f;
	bool isJump_ = false;

	float panelCount = 1.0f;

};

