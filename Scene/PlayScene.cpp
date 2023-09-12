#include "PlayScene.h"
#include "ImguiManager.h"
#include "JsonLoader.h"
#include <fstream>
#include <list>
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

	LoadCsv("Resources/Csv/stageTest.csv");
	player_ = sceneObj_->player_;
	player_->ResetParam();
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
	if (player_->GetIsGoal() == true)
	{

		controller_->ChangeSceneNum(S_CLEAR);
	}


	player_->Update(input, gamePad);

	controller_->camera_->SetEye({ player_->GetPosition().x,player_->GetPosition().y, player_->GetPosition().z - 100 });
	controller_->camera_->SetTarget(player_->GetPosition());
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
	sceneObj_->chip_->Update(input, mouse);
	sceneObj_->chipArea_->Update();
	sceneObj_->chip2_->Update(input, mouse);
	sceneObj_->chipArea2_->Update();

	mouse->Update();

	ImGui::Begin("mouseCheck");
	//ImGui::SetWindowPos({ 200 , 200 });
	ImGui::SetWindowSize({ 500,100 });
	ImGui::InputInt("mouseNum", &mouseCheckNum);
	ImGui::InputFloat2("position", &mousePos.x);
	ImGui::End();

	sceneObj_->skydomeO_->Update();
	//for分に
	for (int i = 0; i < blockNum; i++)
	{
		sceneObj_->asobj_[i]->Update();
	}
	sceneObj_->plaobject->Update();	

	controller_->camera_->Update();


	//リセット処理
	if (input->TriggerKey(DIK_R))
	{

		//player_->Initialize(controller_->dxCommon_,enemy_);
		//enemy_->Initialize(controller_->dxCommon_,player_);
	}
	for (int i = 0; i < 5; i++)
	{
		ImGui::Begin("Block");
		ImGui::InputFloat3("Pos", &sceneObj_->asobj_[i]->worldTransform.translation_.x);
		ImGui::End();
	}
	

}

void PlayScene::Draw()
{
#pragma region 3Dオブジェクト描画
	//// 3Dオブジェクト描画前処理
	Object3d::PreDraw(controller_->dxCommon_->GetCommandList());

	//// 3Dオブジェクトの描画

	/*fbxObject->Draw(dxCommon_->GetCommandList());*/

	sceneObj_->skydomeO_->Draw();
	for (int i = 0; i < blockNum; i++)
	{
		sceneObj_->asobj_[i]->Draw();
	}
	player_->Draw();
	///// <summary>
	///// ここに3Dオブジェクトの描画処理を追加できる
	///// </summary>

	//// 3Dオブジェクト描画後処理
	Object3d::PostDraw();
	sceneObj_->chipArea_->Draw(controller_->dxCommon_);
	sceneObj_->chipArea2_->Draw(controller_->dxCommon_);
#pragma endregion
#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(controller_->dxCommon_->GetCommandList());
	// 背景スプライト描画

	sprite_->Draw();
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

	sceneObj_->chip_->Draw(controller_->dxCommon_);

	sceneObj_->chip2_->Draw(controller_->dxCommon_);
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

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void PlayScene::LoadCsv(const char* word)
{
	std::ifstream file;
	file.open(word);


	assert(file.is_open());
	//ファイルの内容を文字列ストリームにコピー
	stageBlockCommands << file.rdbuf();

	//ファイルを閉じる
	file.close();

	//
	std::string line;

	//コマンド実行ループ
	while (getline(stageBlockCommands, line))
	{
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

			//blockの番号
			std::getline(line_stream, word, ',');
			BlockType attribute = static_cast<BlockType>(std::atof(word.c_str()));

			switch (attribute)
			{
			case BlockType::Init:
				break;
			case BlockType::Normal:
				GenerBlocks(Vector3(x, y, z), num, COLLISION_ATTR_LAND);
				break;
			case BlockType::Goal:
				GenerBlocks(Vector3(x, y, z), num, COLLISION_ATTR_GOAL);
				break;
			case BlockType::Wall:
				GenerBlocks(Vector3(x, y, z), num, COLLISION_ATTR_WALL);
				break;
				blockType = BlockType::Init;
			}
		}
		
	}
}

void PlayScene::GenerBlocks(Vector3 BlockPos, int num, unsigned short attribute)
{
	sceneObj_->asobj_[num]->worldTransform.translation_.x = BlockPos.x;
	sceneObj_->asobj_[num]->worldTransform.translation_.y = BlockPos.y;
	sceneObj_->asobj_[num]->worldTransform.translation_.z = BlockPos.z;
	sphere.resize(SPHERE_COLISSION_NUM);
	spherePos.resize(SPHERE_COLISSION_NUM);

	if (attribute == COLLISION_ATTR_LAND)
	{
		
		for (int i = 0; i < SPHERE_COLISSION_NUM; i++)
		{
			sphere[i] = new SphereCollider;
			CollisionManager::GetInstance()->AddCollider(sphere[i]);
			spherePos[i] = sceneObj_->asobj_[num]->worldTransform.translation_;
			sphere[i]->SetBasisPos(&spherePos[i]);
			sphere[i]->SetRadius(1.0f);
			sphere[i]->SetAttribute(attribute);
			sphere[i]->Update();
		}
	}
	else if (attribute == COLLISION_ATTR_GOAL)
	{
		for (int i = 0; i < SPHERE_COLISSION_NUM; i++)
		{
			sphere[i] = new SphereCollider;
			CollisionManager::GetInstance()->AddCollider(sphere[i]);
			spherePos[i] = sceneObj_->asobj_[num]->worldTransform.translation_;
			sphere[i]->SetBasisPos(&spherePos[i]);
			sphere[i]->SetRadius(1.0f);
			sphere[i]->SetAttribute(attribute);
			sphere[i]->Update();
		}
		sceneObj_->asobj_[num]->SetColor({0.0f,0.0f,1.0f,1.0f});
	}
	else if (attribute == COLLISION_ATTR_WALL)
	{
		for (int i = 0; i < SPHERE_COLISSION_NUM; i++)
		{
			sphere[i] = new SphereCollider;
			CollisionManager::GetInstance()->AddCollider(sphere[i]);
			spherePos[i] = sceneObj_->asobj_[num]->worldTransform.translation_;
			sphere[i]->SetBasisPos(&spherePos[i]);
			sphere[i]->SetRadius(1.0f);
			sphere[i]->SetAttribute(attribute);
			sphere[i]->Update();
		}
		sceneObj_->asobj_[num]->SetColor({ 1.0f,0.0f,1.0f,1.0f });
	}
}


