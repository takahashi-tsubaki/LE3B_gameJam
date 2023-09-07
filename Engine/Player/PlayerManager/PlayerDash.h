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

	void Initialize(FbxObject3d* gameObject) override;
	void Update(Input* input, GamePad* gamePad) override;
	void Draw()override;
private:
};

