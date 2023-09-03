#pragma once
#include "IScene.h"
#include "SceneInc.h"
#include "SceneObjects.h"
class TitleScene :
    public IScene
{
protected:
    SceneManager* controller_;
	Input* input_ = nullptr;
	GamePad* gamePad_ = nullptr;

	Sprite* sprite_ = nullptr;
	Sprite* sprite2_ = nullptr;

	Model* model = nullptr;
	Object3d* object = nullptr;

	PostEffect* postEffect = nullptr;


	FbxModel* fbxModel = nullptr;
	FbxObject3d* fbxObject = nullptr;

	//“V‹…
	Object3d* skydomeO_ = nullptr;
	Model* skydomeM_ = nullptr;


	WorldTransform followPos;
	WorldTransform targetPos;

	SceneObjects* sceneObj_;

public:

    TitleScene(SceneManager* controller, SceneObjects* sceneObj);
    ~TitleScene() override;

    void Initialize()override;

    void Update(Input* input, GamePad* gamePad) override;

    void Draw() override;

    //void Pause(Input* input);
};

