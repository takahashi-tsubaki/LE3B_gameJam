#pragma once
#include "IScene.h"
#include "SceneInc.h"
class GameOverScene :
    public IScene
{
protected:
	SceneManager* controller_;
	Input* input_ = nullptr;
	GamePad* gamePad_ = nullptr;


	SceneObjects* sceneObj_;


public:

	GameOverScene(SceneManager* controller, SceneObjects* sceneObj);
	~GameOverScene() override;

	void Initialize()override;

	void Update(Input* input, GamePad* gamePad, MouseInput* mouse) override;

	void Draw() override;

	//void Pause(Input* input);
};


