#include "SceneObjects.h"
#include "SceneManager.h"
#include "Framework.h"
void SceneObjects::Initialize(SceneManager* controller)
{
	Sprite::LoadTexture(1, L"Resources/ketuma2.png");
	Sprite::LoadTexture(3, L"Resources/ketuma.png");
	Sprite::LoadTexture(4, L"Resources/ketuma3.png");
	Sprite::LoadTexture(5, L"Resources/ketuma4.png");
	Sprite::LoadTexture(6, L"Resources/ketuma5.png");
	Sprite::LoadTexture(7, L"Resources/ketuma6.png");

	Sprite::LoadTexture(8, L"Resources/dash.png");
	Sprite::LoadTexture(9, L"Resources/jump.png");

	Sprite::LoadTexture(10, L"Resources/tyokuden1.png");
	Sprite::LoadTexture(11, L"Resources/tyokuden2.png");
	Sprite::LoadTexture(12, L"Resources/tyokuden3.png");
	Sprite::LoadTexture(13, L"Resources/tyokuden4.png");
	Sprite::LoadTexture(14,L"Resources/tyokuden5.png");
	Sprite::LoadTexture(15,L"Resources/tyokuden6.png");

	Sprite::LoadTexture(16, L"Resources/heiden1.png");
	Sprite::LoadTexture(17, L"Resources/heiden2.png");
	Sprite::LoadTexture(18, L"Resources/heiden3.png");
	Sprite::LoadTexture(19, L"Resources/heiden4.png");
	Sprite::LoadTexture(20, L"Resources/heiden5.png");
	Sprite::LoadTexture(21, L"Resources/heiden6.png");


	//Sprite::LoadTexture(2, L"Resources/mario.jpg");

	//Sprite::LoadTexture(4, L"Resources/sprite/clear.png");
	//Sprite::LoadTexture(5, L"Resources/sprite/over.png");

	controller_ = controller;

	skydomeO_ = Object3d::Create();
	skydomeM_ = Model::CreateFromOBJ("skydome");
	skydomeO_->SetModel(skydomeM_);

	skydomeO_->SetScale({ 100,100,100 });

	//for分に
	for (int i = 0; i < blockNum; i++)
	{
		asobj_[i] = Object3d::Create();
		asmodel = Model::CreateFromOBJ("as");
		asobj_[i]->SetModel(asmodel);
	}

	plaobject = Object3d::Create();
	plamodel = Model::CreateFromOBJ("human");
	walkmodel1 = Model::CreateFromOBJ("walk1");
	walkmodel2 = Model::CreateFromOBJ("walk2");
	jumpmodel = Model::CreateFromOBJ("jump");
	jumpmodelL = Model::CreateFromOBJ("jumpL");
	dashmodel0 = Model::CreateFromOBJ("dash0");
	dashmodel1 = Model::CreateFromOBJ("dash1");
	dashmodel2 = Model::CreateFromOBJ("dash2");


	chipManager_ = new ChipManager();
	chipManager_->Initialize(2,2,2);

	//plaobject->SetModel(plamodel);


	player_ = new Player();
	player_->Initialize(controller_->dxCommon_);
}

void SceneObjects::Update(Input* input)
{
	if (input->PushKey(DIK_W)) {plaobject->SetModel(jumpmodelL);}
	else if (input->PushKey(DIK_S)) {plaobject->SetModel(jumpmodel);}
	else if (input->PushKey(DIK_A)) {
		changeModelTimer++;
		if (changeModelTimer > 24) {
			changeModelTimer = 0;
		}
		if (changeModelTimer >= 1 && changeModelTimer <= 6) {
			plaobject->SetModel(dashmodel1);
		}
		else if (changeModelTimer >= 7 && changeModelTimer <= 12) {
			plaobject->SetModel(dashmodel0);
		}
		else if (changeModelTimer >= 13 && changeModelTimer <= 18) {
			plaobject->SetModel(dashmodel2);
		}
		else if (changeModelTimer >= 19 && changeModelTimer <= 24) {
			plaobject->SetModel(dashmodel0);
		}
	}
	else if (input->PushKey(DIK_D)) {
		changeModelTimer++;
		if (changeModelTimer > 43) {
			changeModelTimer = 0;
		}


		if (changeModelTimer >= 1 && changeModelTimer <= 10) {
			plaobject->SetModel(walkmodel1);
		}
		else if (changeModelTimer >= 11 && changeModelTimer <= 21) {
			plaobject->SetModel(plamodel);
		}
		else if (changeModelTimer >= 22 && changeModelTimer <= 32) {
			plaobject->SetModel(walkmodel2);
		}
		else if (changeModelTimer >= 33 && changeModelTimer <= 43) {
			plaobject->SetModel(plamodel);
		}
	}
	else {
		plaobject->SetModel(plamodel);
	}

}

void SceneObjects::Delete()
{

	delete skydomeO_;
	delete skydomeM_;
	//for分に
	for (int i = 0; i < blockNum; i++)
	{
		delete asobj_[i];
	}
	delete asmodel;
	delete plaobject;
	delete plamodel;
	delete walkmodel1;
	delete walkmodel1;
	delete jumpmodel;
	delete jumpmodelL;
	delete dashmodel0;
	delete dashmodel1;
	delete dashmodel2;
	delete fbxObject;
	delete fbxModel;
	delete chipManager_;

}

void SceneObjects::Reset()
{
}


