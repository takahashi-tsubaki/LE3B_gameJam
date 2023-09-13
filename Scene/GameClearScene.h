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

public:

	GameClearScene(SceneManager* controller, SceneObjects* sceneObj);
	~GameClearScene() override;

	void Initialize()override;

	void Update(Input* input, GamePad* gamePad, MouseInput* mouse) override;

	void Draw() override;

	void GameTimer();

	void DrawGameTimer();

	//void Pause(Input* input);
private:

	int timeFps = 0;

	int timeTM = 0;
	int timeM = 0;
	int timeTS = 0;
	int timeS = 0;
	Sprite* timeboard_ = nullptr;
	//分(10)
	Sprite* spriteTimeTM0_ = nullptr;
	Sprite* spriteTimeTM1_ = nullptr;
	Sprite* spriteTimeTM2_ = nullptr;
	Sprite* spriteTimeTM3_ = nullptr;
	Sprite* spriteTimeTM4_ = nullptr;
	Sprite* spriteTimeTM5_ = nullptr;
	Sprite* spriteTimeTM6_ = nullptr;
	//分(1)
	Sprite* spriteTimeM0_ = nullptr;
	Sprite* spriteTimeM1_ = nullptr;
	Sprite* spriteTimeM2_ = nullptr;
	Sprite* spriteTimeM3_ = nullptr;
	Sprite* spriteTimeM4_ = nullptr;
	Sprite* spriteTimeM5_ = nullptr;
	Sprite* spriteTimeM6_ = nullptr;
	Sprite* spriteTimeM7_ = nullptr;
	Sprite* spriteTimeM8_ = nullptr;
	Sprite* spriteTimeM9_ = nullptr;
	//秒(10)
	Sprite* spriteTimeTS0_ = nullptr;
	Sprite* spriteTimeTS1_ = nullptr;
	Sprite* spriteTimeTS2_ = nullptr;
	Sprite* spriteTimeTS3_ = nullptr;
	Sprite* spriteTimeTS4_ = nullptr;
	Sprite* spriteTimeTS5_ = nullptr;
	Sprite* spriteTimeTS6_ = nullptr;
	//秒(1)
	Sprite* spriteTimeS0_ = nullptr;
	Sprite* spriteTimeS1_ = nullptr;
	Sprite* spriteTimeS2_ = nullptr;
	Sprite* spriteTimeS3_ = nullptr;
	Sprite* spriteTimeS4_ = nullptr;
	Sprite* spriteTimeS5_ = nullptr;
	Sprite* spriteTimeS6_ = nullptr;
	Sprite* spriteTimeS7_ = nullptr;
	Sprite* spriteTimeS8_ = nullptr;
	Sprite* spriteTimeS9_ = nullptr;
};

