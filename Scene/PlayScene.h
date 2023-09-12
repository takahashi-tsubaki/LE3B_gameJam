#pragma once
#include "IScene.h"
#include "SceneInc.h"
#include <map>
#include <sstream>


struct LevelData;

class PlayScene :
    public IScene
{
protected:
    SceneManager* controller_;
	Input* input_ = nullptr;
	GamePad* gamePad_ = nullptr;

	SceneObjects* sceneObj_;

	LevelData* levelData_ = nullptr;

public:

    PlayScene(SceneManager* controller, SceneObjects* sceneObj);
    ~PlayScene() override;

    void Initialize()override;

    void Update(Input*input, GamePad* gamePad) override;

    void Draw() override;

	/// <summary>
	/// blockデータの読み込み
	/// </summary>
	void LoadBlockData();

	/// <summary>
	/// block発生コマンドの更新
	/// </summary>
	void UpdataBlockCommands();

	/// <summary>
	/// 敵の発生
	/// </summary>
	void GenerBlock(Vector3 BlockPos, int num);

    //void Pause(Input* input);

public:
	int jumptimer = 0;
	bool isJumpFlag = false;

	int dashtimer = 0;
	bool isDashFlag = false;

private:	//メンバ変数
	const float PI = 3.141592;
	Camera* camera_ = nullptr;
	Sprite* sprite_ = nullptr;
	XMFLOAT2 spritePosition;
	Sprite* spriteDash_ = nullptr;
	XMFLOAT2 spriteDashPosition;
	

	// blockでステージ生成
	std::stringstream stageBlockCommands;


};

