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

	void Initialize(FbxObject3d* gameObject) override;
	void Update(Input* input, GamePad* gamePad) override;
	void Draw()override;
private:
	FbxObject3d* gameObject_;
	Vector3 velocity_{ 0,0,0 };
	float speed = 0.5f;
};

