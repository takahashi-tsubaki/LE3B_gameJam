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
	if (input->TriggerKey(DIK_RETURN) || gamePad->ButtonTrigger(X))
	{
		controller_->ChangeSceneNum(S_TITLE);
	}
	player_->Update(input, gamePad);
	assert(input);
	controller_->camera_->Update();
}

void GameClearScene::Draw()
{
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
