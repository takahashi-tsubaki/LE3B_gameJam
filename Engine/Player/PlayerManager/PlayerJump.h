#pragma once
#include "PlayerAction.h"
#include "SphereCollider.h"
class PlayerJump :
	public PlayerAction
{
protected:
	PlayerActionManager* ActionManager_;
public:
	PlayerJump(PlayerActionManager* ActionManager, std::vector<SphereCollider*>sphere, std::vector<Vector3> spherePos);
	~PlayerJump() override;

	void Initialize(Object3d* object) override;
	void Update(Input* input, GamePad* gamePad) override;
	void Draw()override;
	void Jump();

	void SetIsJump(bool isJump) { isJump_ = isJump; }
	bool GetIsJump() { return isJump_; }

	//ジャンプの変数のリセット
	void ParamReset();

	void Gravity();

	void CheckCollision();

private:
	Object3d* object_;
	Vector3 velocity_{ 0,0,0 };
	float speed = 0.5f;
	float jumpHeight = 2.0f;
	const float gravity = 0.2f;
	bool isJump_ = false;
	Vector3 fallV;

	float gSpeed = 0.0f;

	float panelCount = 1.0f;

	int SPHERE_COLISSION_NUM = 1;	//コライダー（スフィア）の数
	std::vector<SphereCollider*>sphere_;
	std::vector<Vector3> spherePos_ = {};

};

