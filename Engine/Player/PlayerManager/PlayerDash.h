#pragma once
#include "PlayerAction.h"
#include "SphereCollider.h"
class Player;

class PlayerDash :
	public PlayerAction
{
protected:
	PlayerActionManager* ActionManager_;
public:

	PlayerDash(PlayerActionManager* ActionManager, std::vector<SphereCollider*>sphere, std::vector<Vector3> spherePos);
	~PlayerDash() override;

	void Initialize(Object3d* object) override;
	void Update(Input* input, GamePad* gamePad) override;
	void Draw()override;

	void Dash();

	void ResetParams();

	void SetSpeed(float speed) { speed_ = speed; }

	void SetFlameCount(float flameCount) { DashFlameCount = flameCount; }

	void CheckCollision();

private:
	Object3d* object_;
	Vector3 velocity_{ 0,0,0 };
	float speed_ = 0.5f;
	const float MAX_ACCEL = 1.0f;//加速の最大値
	const float accel = 0.1f;
	bool isDash_ = false;

	bool isAccel_ = false;
	bool isDecel_ = false;

	float DashFlameCount = 5.0f;

	float panelCount = 1.0f;

	bool isHit_ = false;

	int SPHERE_COLISSION_NUM = 1;	//コライダー（スフィア）の数
	std::vector<SphereCollider*>sphere_;
	std::vector<Vector3> spherePos_ = {};
};

