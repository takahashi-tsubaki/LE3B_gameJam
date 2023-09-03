#pragma once
#include "DirectXCommon.h"
#include "SceneManager.h"
#include "Input.h"
#include "GamePad.h"

#include "Sprite.h"
#include "PostEffect.h"

#include "Camera.h"
#include "Light.h"
#include "Model.h"
#include "Object3d.h"

#include "ParticleManager.h"

#include "Vector3.h"

#include "FbxObject3d.h"

#include "Player.h"
#include "Enemy.h"
class IScene
{

protected:

	SceneManager* controller;

public:

	IScene();

	virtual ~IScene();

	virtual void Initialize() = 0;

	virtual void Update(Input*input,GamePad* gamePad) = 0;

	virtual void Draw() = 0;

};

