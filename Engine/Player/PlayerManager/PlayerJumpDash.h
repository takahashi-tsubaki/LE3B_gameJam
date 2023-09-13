#pragma once
#include "PlayerAction.h"
#include "SphereCollider.h"
class PlayerJumpDash :
    public PlayerAction
{
protected:
	PlayerActionManager* ActionManager_;
public:

	PlayerJumpDash(PlayerActionManager* ActionManager, std::vector<SphereCollider*>sphere, std::vector<Vector3> spherePos);
	~PlayerJumpDash() override;

	void Initialize(Object3d* object) override;
	void Update(Input* input, GamePad* gamePad) override;
	void Draw()override;
	void JumpDash(Input* input);

	//ジャンプダッシュの変数のリセット
	void ParamReset();

	void Gravity();

	void CheckCollision();

private:
	Object3d* object_;
	Vector3 velocity_{ 0,0,0 };
	float speed = 0.5f;
	float jumpHeight = 2.0f;
	const float gravity = 0.2f;
	bool isJumpDash_ = false;
	Vector3 fallV;

	float gSpeed = 0.0f;

	float panelCount = 1.0f;

	int SPHERE_COLISSION_NUM = 1;	//コライダー（スフィア）の数
	std::vector<SphereCollider*>sphere_;
	std::vector<Vector3> spherePos_ = {};
};

