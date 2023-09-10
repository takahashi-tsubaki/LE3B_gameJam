#pragma once
#include "PlayerAction.h"
class PlayerDash :
    public PlayerAction
{
protected:
	PlayerActionManager* ActionManager_;
public:

	PlayerDash(PlayerActionManager* ActionManager);
	~PlayerDash() override;

	void Initialize(Object3d* object) override;
	void Update(Input* input, GamePad* gamePad) override;
	void Draw()override;

	void Dash();

	void ResetParams();
private:
	Object3d* object_;
	Vector3 velocity_{ 0,0,0 };
	float speed = 0.5f;
	const float MAX_ACCEL = 2.0f;//加速の最大値
	const float accel = 0.1f;
	bool isDash_ = false;

	bool isAccel_ = false;
	bool isDecel_ = false;

	float DashFlameCount = 30.0f;

	float panelCount = 1.0f;
};

