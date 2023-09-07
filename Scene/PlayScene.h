#pragma once
#include "IScene.h"
#include "SceneInc.h"
class PlayScene :
    public IScene
{
protected:
    SceneManager* controller_;
	Input* input_ = nullptr;
	GamePad* gamePad_ = nullptr;

	Player* player_ = nullptr;
	SceneObjects* sceneObj_;

public:

    PlayScene(SceneManager* controller, SceneObjects* sceneObj);
    ~PlayScene() override;

    void Initialize()override;

    void Update(Input*input, GamePad* gamePad) override;

    void Draw() override;

    //void Pause(Input* input);
};

