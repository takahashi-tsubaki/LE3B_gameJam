#include "SceneObjects.h"
#include "SceneManager.h"
void SceneObjects::Initialize(SceneManager* controller)
{
	Sprite::LoadTexture(1, L"Resources/kuribo-.jpg");
	Sprite::LoadTexture(2, L"Resources/mario.jpg");

	Sprite::LoadTexture(4, L"Resources/sprite/clear.png");
	Sprite::LoadTexture(5, L"Resources/sprite/over.png");

	controller_ = controller;

	skydomeO_ = Object3d::Create();
	skydomeM_ = Model::CreateFromOBJ("skydome");
	skydomeO_->SetModel(skydomeM_);

	skydomeO_->SetScale({ 1,1,1 });


	fbxModel = FbxLoader::GetInstance()->LoadModelFromFile("boss_prot4");

	fbxObject = new FbxObject3d();
	fbxObject->Initialize();
	fbxObject->SetModel(fbxModel);
	//fbxObject->SetScale({0.1f,0.1f,0.1f});
	//fbxObject->SetPosition({ 0,-50,0 });

	fbxObject->SetPosition({ 0,-10,10 });

	player_ = new Player();
	enemy_ = new Enemy();
	enemy_->Initialize(controller_->dxCommon_, player_);
	player_->Initialize(controller_->dxCommon_, enemy_);
}

void SceneObjects::Delete()
{
	delete skydomeO_;
	delete skydomeM_;
	delete fbxObject;
	delete fbxModel;
	delete player_;
	delete enemy_;
}

void SceneObjects::Reset()
{
	enemy_->Reset();
	player_->Reset();
}


