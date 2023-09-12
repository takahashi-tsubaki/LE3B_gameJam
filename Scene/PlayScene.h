#pragma once
#include "Audio.h"
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

	Player* player_ = nullptr;
	Player* player2_ = nullptr;
	SceneObjects* sceneObj_;


	LevelData* levelData_ = nullptr;

	Vector2 mousePos;
	int mouseCheckNum = 0;

public:

    PlayScene(SceneManager* controller, SceneObjects* sceneObj);
    ~PlayScene() override;

    void Initialize()override;

    void Update(Input*input, GamePad* gamePad, MouseInput* mouse) override;

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

private:	//メンバ変数
	const float PI = 3.141592;
	Camera* camera_ = nullptr;
	Sprite* sprite_ = nullptr;
	Sprite* sprite2_ = nullptr;
	Sprite* sprite3_ = nullptr;
	Sprite* sprite4_ = nullptr;
	Sprite* sprite5_ = nullptr;
	Sprite* sprite6_ = nullptr;
	Audio* audio = nullptr;

	// blockでステージ生成
	std::stringstream stageBlockCommands;

	int blockNum = 45;

	int modeC = 0;

	//bool pause = FALSE;
	int pause = 0;

public:
	//音を止める関数
	IXAudio2SourceVoice* pSourceVoice[10] = { 0 };
	//音関係まとめ
	int soundCheckFlag = 0;
};

