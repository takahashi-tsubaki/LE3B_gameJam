#pragma once
#include "PlayerAction.h"
class PlayerMove :
	public PlayerAction
{
protected:
	PlayerActionManager* ActionManager_;

public:

	PlayerMove(PlayerActionManager* ActionManager);
	~PlayerMove() override;

	void Initialize(Object3d* object) override;
	void Update(Input* input, GamePad* gamePad) override;
	void Draw()override;

private:
	Object3d* object_;
	Vector3 velocity_{ 0,0,0 };
	float speed = 0.5f;
};

