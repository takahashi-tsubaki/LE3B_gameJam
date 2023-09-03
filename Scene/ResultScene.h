#pragma once
#include "IScene.h"
#include "SceneInc.h"
class ResultScene :
    public IScene
{
protected:
    SceneManager* controller_;
	Input* input_ = nullptr;
	GamePad* gamePad_ = nullptr;

	SceneObjects* sceneObj_;
public:

    ResultScene(SceneManager* controller, SceneObjects* sceneObj);
    ~ResultScene() override;

    void Initialize()override;

    void Update(Input* input, GamePad* gamePad) override;

    void Draw() override;

    //void Pause(Input* input);
};

