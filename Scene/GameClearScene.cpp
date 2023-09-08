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

}

void GameClearScene::Update(Input* input, GamePad* gamePad, MouseInput* mouse)
{
	gamePad->Update();
	if (input->TriggerKey(DIK_RETURN) || gamePad->ButtonTrigger(X))
	{
		controller_->ChangeSceneNum(S_TITLE);
	}

	assert(input);
	controller_->camera_->Update();
}

void GameClearScene::Draw()
{
#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(controller_->dxCommon_->GetCommandList());

	//sprite_->Draw();
	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion

}
