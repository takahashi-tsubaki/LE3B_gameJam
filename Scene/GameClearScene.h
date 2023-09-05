#pragma once
#include "IScene.h"
#include "SceneInc.h"
class GameClearScene :
    public IScene
{
protected:
	SceneManager* controller_;
	Input* input_ = nullptr;
	GamePad* gamePad_ = nullptr;

	SceneObjects* sceneObj_;


public:

	GameClearScene(SceneManager* controller, SceneObjects* sceneObj);
	~GameClearScene() override;

	void Initialize()override;

	void Update(Input* input, GamePad* gamePad) override;

	void Draw() override;

	//void Pause(Input* input);
};
