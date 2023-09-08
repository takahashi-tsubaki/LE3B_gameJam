#pragma once
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

class SceneManager;

class SceneObjects
{
public:

	void Initialize(SceneManager* controller);

	void Update(Input* input );

	void Draw();

	void Delete();

	void Reset();

public:
	SceneObjects* sceneObj = nullptr;
	Sprite* sprite_ = nullptr;

	//天球
	Object3d* skydomeO_ = nullptr;
	Model* skydomeM_ = nullptr;

	Model* model = nullptr;
	Object3d* object = nullptr;

	Model* asmodel = nullptr;
	Object3d* asobj_[2] = {0};

	Model* plamodel = nullptr;
	Object3d* plaobject = nullptr;
	Model* walkmodel1 = nullptr;
	Model* walkmodel2 = nullptr;
	Model* jumpmodel = nullptr;
	Model* jumpmodelL = nullptr;
	Model* dashmodel0 = nullptr;
	Model* dashmodel1 = nullptr;
	Model* dashmodel2 = nullptr;
	int changeModelTimer = 0;
	int changeModelTimerD = 0;

	SceneManager* controller_;
};

