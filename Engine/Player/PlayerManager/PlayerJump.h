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
private:
	FbxObject3d* fbxObject_;
	Vector3 velocity_{ 0,0,0 };
	float speed = 0.5f;
};
