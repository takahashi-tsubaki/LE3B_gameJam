#include "GameTutoScene.h"
#include "ImguiManager.h"
GameTutoScene::GameTutoScene(SceneManager* controller, SceneObjects* sceneObj)
{
	controller_ = controller;
	sceneObj_ = sceneObj;
}

GameTutoScene::~GameTutoScene()
{
	sceneObj_->Reset();
}

void GameTutoScene::Initialize()
{
	//直列回路の電気移動
	spppppp = Sprite::Create(33, { 0,0 });
	spppppp->Initialize();
	spriteSele2_ = Sprite::Create(34, { 0,0 });
	spriteSele2_->Initialize();
	spriteSele3_ = Sprite::Create(35, { 0,0 });
	spriteSele3_->Initialize();
	spriteSele4_ = Sprite::Create(36, { 0,0 });
	spriteSele4_->Initialize();

	spriteOk_ = Sprite::Create(37, { 0,300 });
	spriteOk_->Initialize();

	spriteOk1_ = Sprite::Create(38, { 0,300 });
	spriteOk1_->Initialize();

	spriteSele1ani1_ = Sprite::Create(39, { 0,0 });
	spriteSele1ani1_->Initialize();
	spriteSele1ani2_ = Sprite::Create(40, { 0,0 });
	spriteSele1ani2_->Initialize();
	spriteSele1ani3_ = Sprite::Create(41, { 0,0 });
	spriteSele1ani3_->Initialize();
	
	spriteSele2ani1_ = Sprite::Create(42, { 0,0 });
	spriteSele2ani1_->Initialize();
	spriteSele2ani2_ = Sprite::Create(43, { 0,0 });
	spriteSele2ani2_->Initialize();
	spriteSele2ani3_ = Sprite::Create(44, { 0,0 });
	spriteSele2ani3_->Initialize();
	
	spriteSele3ani1_ = Sprite::Create(46, { 0,0 });
	spriteSele3ani1_->Initialize();
	spriteSele3ani2_ = Sprite::Create(47, { 0,0 });
	spriteSele3ani2_->Initialize();
	spriteSele3ani3_ = Sprite::Create(48, { 0,0 });
	spriteSele3ani3_->Initialize();

	spriteSele4ani1_ = Sprite::Create(49, { 200,150 });
	spriteSele4ani1_->Initialize();
	spriteSele4ani2_ = Sprite::Create(50, { 200,150 });
	spriteSele4ani2_->Initialize();
	spriteSele4ani3_ = Sprite::Create(51, { 200,150 });
	spriteSele4ani3_->Initialize();
}

void GameTutoScene::Update(Input* input, GamePad* gamePad, MouseInput* mouse)
{
	gamePad->Update();
	sceneObj_->skydomeO_->Update();

	assert(input);
	controller_->camera_->Update();

	if (input->TriggerKey(DIK_W)){
		isSeleChange--;
	}
	else if (input->TriggerKey(DIK_S)) {
		isSeleChange++;
	}

	if (isSeleChange <= 1) {isSeleChange = 1;}
	else if (isSeleChange >= 4) {isSeleChange = 4;}

	if (input->TriggerKey(DIK_SPACE)) {
		if (isSeleChange == 1) {
			isSele1Flag = true;
		}
		else if (isSeleChange == 2) {
			isSele2Flag = true;
		}
		else if (isSeleChange == 3) {
			isSele3Flag = true;
		}
		else if (isSeleChange == 4) {
			isSele4Flag = true;
		}
	}
	if (isSele1Flag == true) {Sele1Timer++;}
	if (Sele1Timer > 30) {
		Sele1Timer = 30;
		startPlayerPos = 1;
		isSele1Flag = false;
	}

	if (isSele2Flag == true) { Sele2Timer++; }
	if (Sele2Timer > 30) {
		Sele2Timer = 30;
		startPlayerPos = 2;
		isSele2Flag = false;
	}

	if (isSele3Flag == true) { Sele3Timer++; }
	if (Sele3Timer > 30) {
		Sele3Timer = 30;
		startPlayerPos = 3;
		isSele3Flag = false;
	}

	if (isSele4Flag == true) { Sele4Timer++; }
	if (Sele4Timer >= 30) {
		Sele4Timer = 30;
		startPlayerPos = 4;
		isSele4Flag = false;
	}


	if (Sele1Timer >= 30||
		Sele2Timer >= 30||
		Sele3Timer >= 30) {
		sceneObj_->startPlayerPos = startPlayerPos;
		controller_->ChangeSceneNum(S_PLAY);
	}

	if (Sele4Timer >= 5) {
		if (input->TriggerKey(DIK_SPACE)) {
			Sele4Timer = 0;
		}
	}
}

void GameTutoScene::Draw()
{
	//// 3Dオブジェクト描画前処理
	Object3d::PreDraw(controller_->dxCommon_->GetCommandList());

	//// 3Dオブジェクトの描画

	/*fbxObject->Draw(dxCommon_->GetCommandList());*/

	sceneObj_->skydomeO_->Draw();


	//// 3Dオブジェクト描画後処理
	Object3d::PostDraw();

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(controller_->dxCommon_->GetCommandList());


	if (isSeleChange == 1) {spppppp->Draw();}
	else if (isSeleChange == 2) {spriteSele2_->Draw();}
	else if (isSeleChange == 3) {spriteSele3_->Draw();}
	else if (isSeleChange == 4) {spriteSele4_->Draw();}

	if (isSeleChange == 1) {
		if (Sele1Timer >= 1 && Sele1Timer <= 30) { spriteSele1ani1_->Draw(); }
		if (Sele1Timer >= 6 && Sele1Timer <= 30) { spriteSele1ani2_->Draw(); }
		if (Sele1Timer >= 11 && Sele1Timer <= 30) { spriteSele1ani3_->Draw(); }
		if (Sele1Timer >= 15 && Sele1Timer <= 17) { spriteOk1_->Draw(); }
		if (Sele1Timer >= 18 && Sele1Timer <= 20) { spriteOk_->Draw(); }
		if (Sele1Timer >= 21 && Sele1Timer <= 24) { spriteOk1_->Draw(); }
		if (Sele1Timer >= 25 && Sele1Timer <= 30) { spriteOk_->Draw(); }
	}
	else if (isSeleChange == 2) {
		if (Sele2Timer >= 1  && Sele2Timer <= 30) { spriteSele2ani1_->Draw(); }
		if (Sele2Timer >= 6  && Sele2Timer <= 30) { spriteSele2ani2_->Draw(); }
		if (Sele2Timer >= 11 && Sele2Timer <= 30) { spriteSele2ani3_->Draw(); }
		if (Sele2Timer >= 15 && Sele2Timer <= 17) { spriteOk1_->Draw(); }
		if (Sele2Timer >= 18 && Sele2Timer <= 20) { spriteOk_->Draw(); }
		if (Sele2Timer >= 21 && Sele2Timer <= 24) { spriteOk1_->Draw(); }
		if (Sele2Timer >= 25 && Sele2Timer <= 30) { spriteOk_->Draw(); }
	}
	else if (isSeleChange == 3) {
		if (Sele3Timer >= 1 &&  Sele3Timer <= 30) { spriteSele3ani1_->Draw(); }
		if (Sele3Timer >= 6 &&  Sele3Timer <= 30) { spriteSele3ani2_->Draw(); }
		if (Sele3Timer >= 11 && Sele3Timer <= 30) { spriteSele3ani3_->Draw(); }
		if (Sele3Timer >= 15 && Sele3Timer <= 17) { spriteOk1_->Draw(); }
		if (Sele3Timer >= 18 && Sele3Timer <= 20) { spriteOk_->Draw(); }
		if (Sele3Timer >= 21 && Sele3Timer <= 24) { spriteOk1_->Draw(); }
		if (Sele3Timer >= 25 && Sele3Timer <= 30) { spriteOk_->Draw(); }
	}
	else if (isSeleChange == 4) {
		if (Sele4Timer >= 1 && Sele4Timer <= 30) { spriteSele4ani1_->Draw(); }
		if (Sele4Timer >= 6 && Sele4Timer <= 30) { spriteSele4ani2_->Draw(); }
		if (Sele4Timer >=11 && Sele4Timer <= 30) { spriteSele4ani3_->Draw(); }
	}

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	//
	// スプライト描画後処理
	Sprite::PostDraw();

	
#pragma endregion
}
