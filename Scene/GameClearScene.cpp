#include "GameClearScene.h"
#include "ImguiManager.h"
GameClearScene::GameClearScene(SceneManager* controller, SceneObjects* sceneObj)
{
	controller_ = controller;
	sceneObj_ = sceneObj;
}

GameClearScene::~GameClearScene()
{
	sceneObj_->Reset();
}

void GameClearScene::Initialize()
{
	player_ = sceneObj_->player_;
	player_->ResetParam();


	//タイマーの表示
	timeboard_ = Sprite::Create(32, { 820,50 });
	timeboard_->Initialize();

	timeS = sceneObj_->timeS;
	timeTS = sceneObj_->timeTS;
	timeM = sceneObj_->timeM;
	timeTM = sceneObj_->timeTM;

	{
		spriteTimeTM0_ = Sprite::Create(22, { 840,50 });
		spriteTimeTM0_->Initialize();
		spriteTimeTM1_ = Sprite::Create(23, { 840,50 });
		spriteTimeTM1_->Initialize();
		spriteTimeTM2_ = Sprite::Create(24, { 840,50 });
		spriteTimeTM2_->Initialize();
		spriteTimeTM3_ = Sprite::Create(25, { 840,50 });
		spriteTimeTM3_->Initialize();
		spriteTimeTM4_ = Sprite::Create(26, { 840,50 });
		spriteTimeTM4_->Initialize();
		spriteTimeTM5_ = Sprite::Create(27, { 840,50 });
		spriteTimeTM5_->Initialize();
		spriteTimeTM6_ = Sprite::Create(28, { 840,50 });
		spriteTimeTM6_->Initialize();
	}

	{
		spriteTimeM0_ = Sprite::Create(22, { 880,50 });
		spriteTimeM0_->Initialize();
		spriteTimeM1_ = Sprite::Create(23, { 880,50 });
		spriteTimeM1_->Initialize();
		spriteTimeM2_ = Sprite::Create(24, { 880,50 });
		spriteTimeM2_->Initialize();
		spriteTimeM3_ = Sprite::Create(25, { 880,50 });
		spriteTimeM3_->Initialize();
		spriteTimeM4_ = Sprite::Create(26, { 880,50 });
		spriteTimeM4_->Initialize();
		spriteTimeM5_ = Sprite::Create(27, { 880,50 });
		spriteTimeM5_->Initialize();
		spriteTimeM6_ = Sprite::Create(28, { 880,50 });
		spriteTimeM6_->Initialize();
		spriteTimeM7_ = Sprite::Create(29, { 880,50 });
		spriteTimeM7_->Initialize();
		spriteTimeM8_ = Sprite::Create(30, { 880,50 });
		spriteTimeM8_->Initialize();
		spriteTimeM9_ = Sprite::Create(31, { 880,50 });
		spriteTimeM9_->Initialize();
	}

	{
		spriteTimeTS0_ = Sprite::Create(22, { 960,50 });
		spriteTimeTS0_->Initialize();
		spriteTimeTS1_ = Sprite::Create(23, { 960,50 });
		spriteTimeTS1_->Initialize();
		spriteTimeTS2_ = Sprite::Create(24, { 960,50 });
		spriteTimeTS2_->Initialize();
		spriteTimeTS3_ = Sprite::Create(25, { 960,50 });
		spriteTimeTS3_->Initialize();
		spriteTimeTS4_ = Sprite::Create(26, { 960,50 });
		spriteTimeTS4_->Initialize();
		spriteTimeTS5_ = Sprite::Create(27, { 960,50 });
		spriteTimeTS5_->Initialize();
		spriteTimeTS6_ = Sprite::Create(28, { 960,50 });
		spriteTimeTS6_->Initialize();
	}

	{
		spriteTimeS0_ = Sprite::Create(22, { 1000,50 });
		spriteTimeS0_->Initialize();
		spriteTimeS1_ = Sprite::Create(23, { 1000,50 });
		spriteTimeS1_->Initialize();
		spriteTimeS2_ = Sprite::Create(24, { 1000,50 });
		spriteTimeS2_->Initialize();
		spriteTimeS3_ = Sprite::Create(25, { 1000,50 });
		spriteTimeS3_->Initialize();
		spriteTimeS4_ = Sprite::Create(26, { 1000,50 });
		spriteTimeS4_->Initialize();
		spriteTimeS5_ = Sprite::Create(27, { 1000,50 });
		spriteTimeS5_->Initialize();
		spriteTimeS6_ = Sprite::Create(28, { 1000,50 });
		spriteTimeS6_->Initialize();
		spriteTimeS7_ = Sprite::Create(29, { 1000,50 });
		spriteTimeS7_->Initialize();
		spriteTimeS8_ = Sprite::Create(30, { 1000,50 });
		spriteTimeS8_->Initialize();
		spriteTimeS9_ = Sprite::Create(31, { 1000,50 });
		spriteTimeS9_->Initialize();
	}


	clearA = Sprite::Create(52, { 0,0 });
	clearA->Initialize();

	clearB = Sprite::Create(53, { 0,0 });
	clearB->Initialize();

	clearB = Sprite::Create(54, { 0,0 });
	clearB->Initialize();

}

void GameClearScene::Update(Input* input, GamePad* gamePad, MouseInput* mouse)
{
	gamePad->Update();
	if (input->TriggerKey(DIK_SPACE) || gamePad->ButtonTrigger(X))
	{
		controller_->ChangeSceneNum(S_TITLE);
	}
	player_->Update(input, gamePad);
	assert(input);
	controller_->camera_->Update();
}

void GameClearScene::Draw()
{
#pragma region 3Dオブジェクト描画
	//// 3Dオブジェクト描画前処理
	Object3d::PreDraw(controller_->dxCommon_->GetCommandList());

	//// 3Dオブジェクトの描画

	/*fbxObject->Draw(dxCommon_->GetCommandList());*/

	sceneObj_->skydomeO_->Draw();

	///// <summary>
	///// ここに3Dオブジェクトの描画処理を追加できる
	///// </summary>

	//// 3Dオブジェクト描画後処理
	Object3d::PostDraw();
#pragma endregion
#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(controller_->dxCommon_->GetCommandList());
	// 背景スプライト描画
	

	DrawGameTimer();

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion

#pragma region 3Dオブジェクト描画
	//// 3Dオブジェクト描画前処理
	Object3d::PreDraw(controller_->dxCommon_->GetCommandList());

	//// 3Dオブジェクトの描画

	/*fbxObject->Draw(dxCommon_->GetCommandList());*/

	//sceneObj_->skydomeO_->Draw();

	//sceneObj_->plaobject->Draw();


	///// <summary>
	///// ここに3Dオブジェクトの描画処理を追加できる
	///// </summary>

	//// 3Dオブジェクト描画後処理
	Object3d::PostDraw();

#pragma endregion


	//#pragma region ぺらポリゴン描画
	//	postEffect->PreDrawScene(dxCommon_->GetCommandList());
	//
	//	//// ぺらポリゴンの描画
	//	postEffect->Draw(dxCommon_->GetCommandList());
	//	///// <summary>
	//	///// ここにぺらポリゴンの描画処理を追加できる
	//	///// </summary>
	//
	//	
	//
	//	postEffect->PostDrawScene(dxCommon_->GetCommandList());
	//
	//
	//
	//#pragma endregion
#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(controller_->dxCommon_->GetCommandList());



	//sprite_->Draw();

	{
		clearA->Draw();
		/*clearB->Draw();
		clearC->Draw();*/
	}


	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion

}

void GameClearScene::DrawGameTimer()
{
	timeboard_->Draw();

	if (timeS == 0) { spriteTimeS0_->Draw(); }
	else if (timeS == 1) { spriteTimeS1_->Draw(); }
	else if (timeS == 2) { spriteTimeS2_->Draw(); }
	else if (timeS == 3) { spriteTimeS3_->Draw(); }
	else if (timeS == 4) { spriteTimeS4_->Draw(); }
	else if (timeS == 5) { spriteTimeS5_->Draw(); }
	else if (timeS == 6) { spriteTimeS6_->Draw(); }
	else if (timeS == 7) { spriteTimeS7_->Draw(); }
	else if (timeS == 8) { spriteTimeS8_->Draw(); }
	else if (timeS == 9) { spriteTimeS9_->Draw(); }

	if (timeTS == 0) { spriteTimeTS0_->Draw(); }
	else if (timeTS == 1) { spriteTimeTS1_->Draw(); }
	else if (timeTS == 2) { spriteTimeTS2_->Draw(); }
	else if (timeTS == 3) { spriteTimeTS3_->Draw(); }
	else if (timeTS == 4) { spriteTimeTS4_->Draw(); }
	else if (timeTS == 5) { spriteTimeTS5_->Draw(); }
	else if (timeTS == 6) { spriteTimeTS6_->Draw(); }

	if (timeM == 0) { spriteTimeM0_->Draw(); }
	else if (timeM == 1) { spriteTimeM1_->Draw(); }
	else if (timeM == 2) { spriteTimeM2_->Draw(); }
	else if (timeM == 3) { spriteTimeM3_->Draw(); }
	else if (timeM == 4) { spriteTimeM4_->Draw(); }
	else if (timeM == 5) { spriteTimeM5_->Draw(); }
	else if (timeM == 6) { spriteTimeM6_->Draw(); }
	else if (timeM == 7) { spriteTimeM7_->Draw(); }
	else if (timeM == 8) { spriteTimeM8_->Draw(); }
	else if (timeM == 9) { spriteTimeM9_->Draw(); }

	if (timeTM == 0) { spriteTimeTM0_->Draw(); }
	else if (timeTM == 1) { spriteTimeTM1_->Draw(); }
	else if (timeTM == 2) { spriteTimeTM2_->Draw(); }
	else if (timeTM == 3) { spriteTimeTM3_->Draw(); }
	else if (timeTM == 4) { spriteTimeTM4_->Draw(); }
	else if (timeTM == 5) { spriteTimeTM5_->Draw(); }
	else if (timeTM == 6) { spriteTimeTM6_->Draw(); }
}
