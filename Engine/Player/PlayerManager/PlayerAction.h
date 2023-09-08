#pragma once
#include "FbxObject3d.h"

#include "Input.h"
#include "GamePad.h"
#include "MouseInput.h"

#include "PlayerActionManager.h"


class PlayerAction
{
protected:
	PlayerActionManager* actionManager_ ;
public:

	PlayerAction();
	virtual ~PlayerAction();

	virtual void Initialize(FbxObject3d *fbxObject) = 0;

	virtual void Update(Input* input,GamePad* gamePad) = 0;

	virtual void Draw() = 0;
};

