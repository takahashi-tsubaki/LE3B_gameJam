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

	void Update();

	void Draw();

	void Delete();

	void Reset();

public:
	SceneObjects* sceneObj = nullptr;

	FbxModel* fbxModel = nullptr;
	FbxObject3d* fbxObject = nullptr;
	Sprite* sprite_ = nullptr;

	//天球
	Object3d* skydomeO_ = nullptr;
	Model* skydomeM_ = nullptr;

	Model* model = nullptr;
	Object3d* object = nullptr;

	Model* asmodel = nullptr;
	Object3d* asobj_[2] = {0};

	SceneManager* controller_;
};

