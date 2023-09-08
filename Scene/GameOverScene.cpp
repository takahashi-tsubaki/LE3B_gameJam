#include "GameOverScene.h"
#include "ImguiManager.h"
GameOverScene::GameOverScene(SceneManager* controller, SceneObjects* sceneObj)
{
	controller_ = controller;
	sceneObj_ = sceneObj;
}

GameOverScene::~GameOverScene()
{
	sceneObj_->Reset();
}

void GameOverScene::Initialize()
{

}

void GameOverScene::Update(Input* input, GamePad* gamePad, MouseInput* mouse)
{
	gamePad->Update();
	if (input->TriggerKey(DIK_RETURN) || gamePad->ButtonTrigger(X))
	{
		controller_->ChangeSceneNum(S_TITLE);
	}
	assert(input);
	controller_->camera_->Update();
}

void GameOverScene::Draw()
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
