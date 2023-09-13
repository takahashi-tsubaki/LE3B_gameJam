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
	/*spriteSele2ani4_ = Sprite::Create(45, { 0,0 });
	spriteSele2ani4_->Initialize();*/
	


}

void GameTutoScene::Update(Input* input, GamePad* gamePad, MouseInput* mouse)
{
	gamePad->Update();
	if (input->TriggerKey(DIK_RETURN) || gamePad->ButtonTrigger(X))
	{
		controller_->ChangeSceneNum(S_PLAY);
	}
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
	}
	if (isSele1Flag == true) {Sele1Timer++;}
	if (Sele1Timer > 30) {
		Sele1Timer = 30;
		isSele1Flag = false;
	}

	if (isSele2Flag == true) { Sele2Timer++; }
	if (Sele2Timer > 30) {
		Sele2Timer = 30;
		isSele2Flag = false;
	}

	if (Sele1Timer >= 30) {
		controller_->ChangeSceneNum(S_PLAY);
	}
}

void GameTutoScene::Draw()
{
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
	
	

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
