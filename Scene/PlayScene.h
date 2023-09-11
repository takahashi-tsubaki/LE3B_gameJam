#pragma once
#include "IScene.h"
#include "SceneInc.h"
#include <map>
#include <sstream>
#include <memory>

enum class BlockType
{
	Init,    //0
	Normal,  //1
	Goal,    //2
};

class PlayScene :
    public IScene
{
private:

	using fsPath = std::experimental::filesystem::path;

    SceneManager* controller_;
	Input* input_ = nullptr;
	GamePad* gamePad_ = nullptr;

	Player* player_ = nullptr;
	SceneObjects* sceneObj_;

	Vector2 mousePos;
	int mouseCheckNum = 0;

	Vector3 objPosition;

public:

    PlayScene(SceneManager* controller, SceneObjects* sceneObj);
    ~PlayScene() override;

    void Initialize()override;

    void Update(Input*input, GamePad* gamePad, MouseInput* mouse) override;

    void Draw() override;

	void LoadCsv(const char* word);


	void GenerBlocks(Vector3 BlockPos, int num, unsigned short attribute);

    //void Pause(Input* input);

private:	//メンバ変数
	const float PI = 3.141592;
	Camera* camera_ = nullptr;
	Sprite* sprite_ = nullptr;

	// blockでステージ生成
	std::stringstream stageBlockCommands;
	int blockNum = 45;
	BlockType blockType = BlockType::Init;

	int SPHERE_COLISSION_NUM = 1;	//コライダー（スフィア）の数
	std::vector<Matrix4>* collisionBonesMat;	//当たり判定用のボーンのワールド行列
	std::vector<SphereCollider*> sphere;
	std::vector<Vector3> spherePos = {};



};

