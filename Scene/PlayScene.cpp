#include "PlayScene.h"
#include "ImguiManager.h"

PlayScene::PlayScene(SceneManager* controller, SceneObjects* sceneObj)
{
	controller_ = controller;
	sceneObj_ = sceneObj;

}

PlayScene::~PlayScene()
{
	sceneObj_->Reset();

}

void PlayScene::Initialize()
{


}

void PlayScene::Update(Input* input, GamePad* gamePad)
{
	gamePad->Update();
	//シーンチェンジ
	if (input->TriggerKey(DIK_RETURN) || gamePad->ButtonTrigger(X))
	{

		controller_->ChangeSceneNum(S_TITLE);
	}

	if (input->TriggerKey(DIK_TAB) || gamePad->ButtonTrigger(START))
	{
		controller_->PushScene(S_PAUSE);
	}

	if (input->TriggerKey(DIK_LSHIFT) || gamePad->ButtonTrigger(BACK))
	{
	
	}

	

	controller_->camera_->Update();

	/*ImGui::Begin("cameraPos");
	//ImGui::SetWindowPos({ 200 , 200 });
	ImGui::SetWindowSize({ 500,100 });
	ImGui::InputFloat3("eye", &camera_->eye_.x);
	ImGui::InputFloat3("target", &camera_->target_.x);
	ImGui::End();*/

	/*sceneObj_->skydomeO_->Update();*/

	

	//リセット処理
	if (input->TriggerKey(DIK_R))
	{
		
		//player_->Initialize(controller_->dxCommon_,enemy_);
		//enemy_->Initialize(controller_->dxCommon_,player_);
	}

	
}

void PlayScene::Draw()
{
#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(controller_->dxCommon_->GetCommandList());
	// 背景スプライト描画


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
	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
