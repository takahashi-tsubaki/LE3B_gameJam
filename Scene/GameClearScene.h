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
	Player* player_ = nullptr;

	Sprite* clearA = nullptr;
	Sprite* clearB = nullptr;
	Sprite* clearC = nullptr;

public:

	GameClearScene(SceneManager* controller, SceneObjects* sceneObj);
	~GameClearScene() override;

	void Initialize()override;

	void Update(Input* input, GamePad* gamePad, MouseInput* mouse) override;

	void Draw() override;

	//void Pause(Input* input);
};

