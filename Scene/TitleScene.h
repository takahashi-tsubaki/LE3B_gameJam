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

	SceneObjects* sceneObj_;

public:

    TitleScene(SceneManager* controller, SceneObjects* sceneObj);
    ~TitleScene() override;

    void Initialize()override;

    void Update(Input* input, GamePad* gamePad, MouseInput* mouse) override;

    void Draw() override;

    //void Pause(Input* input);
};

