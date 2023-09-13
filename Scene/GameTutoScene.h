#pragma once
#include "IScene.h"
#include "SceneInc.h"
class GameTutoScene :
    public IScene
{
protected:
	SceneManager* controller_;
	Input* input_ = nullptr;
	GamePad* gamePad_ = nullptr;


	SceneObjects* sceneObj_;


public:

	GameTutoScene(SceneManager* controller, SceneObjects* sceneObj);
	~GameTutoScene() override;

	void Initialize()override;

	void Update(Input* input, GamePad* gamePad, MouseInput* mouse) override;

	void Draw() override;

	//void Pause(Input* input);

private:	//メンバ変数
	//ステージセレクト
	//Sprite* spriteSele_ = nullptr;
	Sprite* spppppp = nullptr;
	Sprite* spriteSele2_ = nullptr;
	Sprite* spriteSele3_ = nullptr;
	Sprite* spriteSele4_ = nullptr;

	//OK?
	Sprite* spriteOk_ = nullptr;
	Sprite* spriteOk1_ = nullptr;

	int isSeleChange = 1;

	//セレクト1アニメーション
	Sprite* spriteSele1ani1_ = nullptr;
	Sprite* spriteSele1ani2_ = nullptr;
	Sprite* spriteSele1ani3_ = nullptr;
	bool isSele1Flag = false;
	int Sele1Timer = 0;

	//セレクト2アニメーション
	Sprite* spriteSele2ani1_ = nullptr;
	Sprite* spriteSele2ani2_ = nullptr;
	Sprite* spriteSele2ani3_ = nullptr;
	bool isSele2Flag = false;
	int Sele2Timer = 0;

	//操作説明
	Sprite* spriteSele2ani4_ = nullptr;


};


