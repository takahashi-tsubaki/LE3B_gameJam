#pragma once
#include "Audio.h"
#include "IScene.h"
#include "SceneInc.h"
#include <map>
#include <sstream>

enum class BlockType
{
	Init,    //0
	Normal,  //1
	Goal,    //2
	Wall,    //3
};

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


	void LoadCsv(const char* word);


	void GenerBlocks(Vector3 BlockPos, int num, unsigned short attribute);

	void GameTimer();

	void DrawGameTimer();

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

	Sprite* spriteJump_ = nullptr;
	XMFLOAT2 spriteJumpPosition;
	Sprite* spriteDash_ = nullptr;
	XMFLOAT2 spriteDashPosition;

	Sprite* spritetyokuden1_ = nullptr;
	Sprite* spritetyokuden2_ = nullptr;
	Sprite* spritetyokuden3_ = nullptr;
	Sprite* spritetyokuden4_ = nullptr;
	Sprite* spritetyokuden5_ = nullptr;
	Sprite* spritetyokuden6_ = nullptr;
	bool isTyokudenFlag = false;
	bool isStockFlag = false;
	int tyokudenTimer = 0;

	Sprite* spriteheiden1_ = nullptr;
	Sprite* spriteheiden2_ = nullptr;
	Sprite* spriteheiden3_ = nullptr;
	Sprite* spriteheiden4_ = nullptr;
	Sprite* spriteheiden5_ = nullptr;
	Sprite* spriteheiden6_ = nullptr;
	bool isHeidenFlag = false;
	bool isStockFlag2 = false;
	int heidenTimer = 0;

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


	// blockでステージ生成
	std::stringstream stageBlockCommands;

	int blockNum = 200;
	BlockType blockType = BlockType::Init;
	int SPHERE_COLISSION_NUM = 1;	//コライダー（スフィア）の数
	std::vector<Matrix4>* collisionBonesMat;	//当たり判定用のボーンのワールド行列
	std::vector<SphereCollider*> sphere;
	std::vector<Vector3> spherePos = {};

	int modeC = 0;

	//bool pause = FALSE;
	int pause = 0;

public:
	//音を止める関数
	IXAudio2SourceVoice* pSourceVoice[10] = { 0 };
	//音関係まとめ
	int soundCheckFlag = 0;

	int jumptimer = 0;
	bool isJumpFlag = false;

	int dashtimer = 0;
	bool isDashFlag = false;

	int timeFps = 0;

	int timeTM = 0;
	int timeM = 0;
	int timeTS = 0;
	int timeS = 0;

};

