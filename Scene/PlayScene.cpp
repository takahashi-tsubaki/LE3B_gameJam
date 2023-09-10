#include "PlayScene.h"
#include "ImguiManager.h"
#include "JsonLoader.h"
#include <fstream>

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

	LoadBlockData();
	player_ = sceneObj_->player_;
	sprite_ =  Sprite::Create(1, { 0,0 });
	sprite_->Initialize();
}

void PlayScene::Update(Input* input, GamePad* gamePad, MouseInput* mouse)
{
	gamePad->Update();
	sceneObj_->Update(input);
	//シーンチェンジ
	if (input->TriggerKey(DIK_RETURN) || gamePad->ButtonTrigger(X)){controller_->ChangeSceneNum(S_TITLE);}

	if (input->TriggerKey(DIK_TAB) || gamePad->ButtonTrigger(START)){controller_->PushScene(S_PAUSE);}

	if (input->TriggerKey(DIK_LSHIFT) || gamePad->ButtonTrigger(BACK)){	
	controller_->camera_->Update();
	}

	player_->Update(input, gamePad);
	controller_->camera_->SetEye({ player_->GetWorldPos().x,player_->GetWorldPos().y, player_->GetWorldPos().z - 100 });
	controller_->camera_->SetTarget(player_->GetWorldPos());
	controller_->camera_->Update();

	//左クリック時
	if (mouse->TriggerMouseButton(0))
	{
		mouseCheckNum = 0;
		mousePos = mouse->GetMousePosition();
	}
	//右クリック時
	if (mouse->TriggerMouseButton(1))
	{
		mouseCheckNum = 1;
		mousePos = mousePos;
	}

	mouse->Update();

	ImGui::Begin("mouseCheck");
	//ImGui::SetWindowPos({ 200 , 200 });
	ImGui::SetWindowSize({ 500,100 });
	ImGui::InputInt("mouseNum", &mouseCheckNum);
	ImGui::InputFloat2("position", &mousePos.x);
	ImGui::End();

	sceneObj_->skydomeO_->Update();
	sceneObj_->asobj_[0]->Update();
	sceneObj_->asobj_[1]->Update();
	sceneObj_->plaobject->Update();

	controller_->camera_->Update();

	//block発生
	UpdataBlockCommands();

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

	sceneObj_->skydomeO_->Draw();

	sceneObj_->asobj_[0]->Draw();
	sceneObj_->asobj_[1]->Draw();

	sceneObj_->plaobject->Draw();
	player_->Draw();

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

	sprite_->Draw();
	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void PlayScene::LoadBlockData()
{
	//ファイルを開く
	std::ifstream file;
	file.open("Resources/stageBlock.csv");

	assert(file.is_open());

	//ファイルの内容を文字列ストリームにコピー
	stageBlockCommands << file.rdbuf();

	//ファイルを閉じる
	file.close();
}

void PlayScene::UpdataBlockCommands()
{
	// 1行分の文字列を入れる変数
	std::string line;

	//コマンド実行ループ
	while (getline(stageBlockCommands, line)) {
		// 1行分の文字数をストリームに変換して解折しやすくなる
		std::istringstream line_stream(line);

		std::string word;
		//,区切りで行の先頭文字を取得
		getline(line_stream, word, ',');

		//"//"から始まる行はコメント
		if (word.find("//") == 0) {
			//コメント行を飛ばす
			continue;
		}
		// POPコマンド
		if (word.find("POP") == 0) {
			// X座標
			std::getline(line_stream, word, ',');
			float x = static_cast<float>(std::atof(word.c_str()));

			// Y座標
			std::getline(line_stream, word, ',');
			float y = static_cast<float>(std::atof(word.c_str()));

			// Z座標
			std::getline(line_stream, word, ',');
			float z = static_cast<float>(std::atof(word.c_str()));

			//blockの番号
			std::getline(line_stream, word, ',');
			int num = static_cast<float>(std::atof(word.c_str()));

			GenerBlock(Vector3(x, y, z),num);
		}
	}
}

void PlayScene::GenerBlock(Vector3 BlockPos, int num)
{
	sceneObj_->asobj_[num]->worldTransform.translation_.x = BlockPos.x;
	sceneObj_->asobj_[num]->worldTransform.translation_.y = BlockPos.y;
	sceneObj_->asobj_[num]->worldTransform.translation_.z = BlockPos.z;
}


