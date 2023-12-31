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
	delete sprite_;
	delete sprite2_;
	delete sprite3_;
	delete sprite4_;
	delete sprite5_;
	delete sprite6_;
	delete spriteDash_;
	delete spriteJump_;

	delete spritetyokuden1_;
	delete spritetyokuden2_;
	delete spritetyokuden3_;
	delete spritetyokuden4_;
	delete spritetyokuden5_;
	delete spritetyokuden6_;

	delete spriteheiden1_;
	delete spriteheiden2_;
	delete spriteheiden3_;
	delete spriteheiden4_;
	delete spriteheiden5_;
	delete spriteheiden6_;
	delete timeboard_;

	delete spriteTimeM0_;
	delete spriteTimeM1_;
	delete spriteTimeM2_;
	delete spriteTimeM3_;
	delete spriteTimeM4_;
	delete spriteTimeM5_;
	delete spriteTimeM6_;
	delete spriteTimeM7_;
	delete spriteTimeM8_;
	delete spriteTimeM9_;

	delete spriteTimeTM0_;
	delete spriteTimeTM1_;
	delete spriteTimeTM2_;
	delete spriteTimeTM3_;
	delete spriteTimeTM4_;
	delete spriteTimeTM5_;
	delete spriteTimeTM6_;

	delete spriteTimeS0_;
	delete spriteTimeS1_;
	delete spriteTimeS2_;
	delete spriteTimeS3_;
	delete spriteTimeS4_;
	delete spriteTimeS5_;
	delete spriteTimeS6_;
	delete spriteTimeS7_;
	delete spriteTimeS8_;
	delete spriteTimeS9_;

	delete spriteTimeTS0_;
	delete spriteTimeTS1_;
	delete spriteTimeTS2_;
	delete spriteTimeTS3_;
	delete spriteTimeTS4_;
	delete spriteTimeTS5_;
	delete spriteTimeTS6_;

	/*for (int i = 0; i < SPHERE_COLISSION_NUM; i++)
	{
		delete &sphere[i];
		delete& spherePos[i];
	}*/

}

void PlayScene::Initialize()
{

	sphereSave.clear();
	//LoadBlockData();

	//LoadCsv("Resources/Csv/stageBlock.csv");
	LoadCsv("Resources/Csv/stageTest.csv");


	player_ = sceneObj_->player_;

	player_->ResetParam(sceneObj_->startPlayerPos);

	/*
	startplayerPos = sceneObj_->startPlayerPos;
	if (startplayerPos == 1)
	{
		player_->SetPosition({ 462,0,50 });
	}
	if (startplayerPos == 2)
	{
		player_->SetPosition({ 0,0,50 });
	}
	if (startplayerPos == 3)
	{
		player_->SetPosition({ 190,0,50 });
	}*/


	sprite_ = Sprite::Create(1, { 0,0 });

	sprite_->Initialize();

	sprite2_ = Sprite::Create(3, { 0,0 });


	sprite3_ = Sprite::Create(4, { 680,540 });
	sprite4_ = Sprite::Create(5, { 680,540 });

	sprite5_ = Sprite::Create(6, { 600,424 });
	sprite6_ = Sprite::Create(7, { 712,424 });

	sprite_->Initialize();
	sprite2_->Initialize();
	sprite3_->Initialize();
	sprite4_->Initialize();
	sprite5_->Initialize();
	sprite6_->Initialize();

	

	//直列回路の電気移動
	spritetyokuden1_ = Sprite::Create(10, { 0,0 });
	spritetyokuden1_->Initialize();
	spritetyokuden2_ = Sprite::Create(11, { 0,0 });
	spritetyokuden2_->Initialize();
	spritetyokuden3_ = Sprite::Create(12, { 0,0 });
	spritetyokuden3_->Initialize();
	spritetyokuden4_ = Sprite::Create(13, { 0,0 });
	spritetyokuden4_->Initialize();
	spritetyokuden5_ = Sprite::Create(14, { 0,0 });
	spritetyokuden5_->Initialize();
	spritetyokuden6_ = Sprite::Create(15, { 0,0 });
	spritetyokuden6_->Initialize();

	//並列回路の電気移動
	spriteheiden1_ = Sprite::Create(16, { 0,0 });
	spriteheiden1_->Initialize();
	spriteheiden2_ = Sprite::Create(17, { 0,0 });
	spriteheiden2_->Initialize();
	spriteheiden3_ = Sprite::Create(18, { 0,0 });
	spriteheiden3_->Initialize();
	spriteheiden4_ = Sprite::Create(19, { 0,0 });
	spriteheiden4_->Initialize();
	spriteheiden5_ = Sprite::Create(20, { 0,0 });
	spriteheiden5_->Initialize();
	spriteheiden6_ = Sprite::Create(21, { 0,0 });
	spriteheiden6_->Initialize();

	//タイマーの表示
	timeboard_ = Sprite::Create(32, { 820,50 });
	timeboard_->Initialize();

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

	audio = new Audio();
	audio->Initialize();

	audio->LoadWave("oto.wav");

	sceneObj_->chipManager_->Reset();

}

void PlayScene::Update(Input* input, GamePad* gamePad, MouseInput* mouse)
{
	gamePad->Update();
	sceneObj_->Update(input);
	//音声再生
	if (soundCheckFlag == 0) {
		//音声再生

		pSourceVoice[0] = audio->PlayWave("oto.wav");
		pSourceVoice[0]->SetVolume(0.5f);
		soundCheckFlag = 1;
	}

	if (input->TriggerKey(DIK_TAB) || gamePad->ButtonTrigger(START)) {
		controller_->PushScene(S_PAUSE);
	}

	if (input->TriggerKey(DIK_LSHIFT) || gamePad->ButtonTrigger(BACK)) {
		controller_->camera_->Update();
	}

	if (input->TriggerKey(DIK_R))
	{
		if (modeC == 0)
		{
			modeC = 1;
			if (isStockFlag2 == true)
			{
				heidenTimer = 0;
				isHeidenFlag = false;
				isStockFlag2 = false;

			}
		}
		else
		{
			modeC = 0;
			if (isStockFlag == true)
			{

				tyokudenTimer = 0;
				isTyokudenFlag = false;
				isStockFlag = false;

			}
		}
	}

	if (pause == 0)
	{
		if (input->TriggerKey(DIK_Q))
		{
			pause = 1;
		}
		else if (input->TriggerKey(DIK_E))
		{
			pause = 2;
		}
	}
	else if (pause == 1 || pause == 2)
	{
		if (input->TriggerKey(DIK_E))
		{
			pause = 0;
		}
		if (input->TriggerKey(DIK_Q))
		{
			for (SphereCollider* s : sphereSave)
			{
				CollisionManager::GetInstance()->RemoveCollider(s);

			}
			controller_->ChangeSceneNum(S_TITLE);
			pSourceVoice[0]->Stop();
			soundCheckFlag = 0;
		}
	}

	

	GameTimer();

	player_->chipPat_ = sceneObj_->chipManager_->GetPattern();
	if (sceneObj_->chipManager_->isMove == true) {
		player_->chipOnMove_ = true;
	}

	/*if (startplayerPos == 1)
	{
		player_->SetPosition({462,0,50});
	}
	if (startplayerPos == 2)
	{
		player_->SetPosition({ 0,0,50 });
	}
	if (startplayerPos == 3)
	{
		player_->SetPosition({ 190,0,50 });
	}*/

	player_->Update(input, gamePad);

	controller_->camera_->SetEye({ player_->GetPosition().x - 20,player_->GetPosition().y, player_->GetPosition().z - 150 });
	controller_->camera_->SetTarget({ player_->GetPosition().x - 20,player_->GetPosition().y, player_->GetPosition().z });
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

	

	sceneObj_->chipManager_->modeChangePos(modeC);

	sceneObj_->chipManager_->Update(input, mouse);

	mouse->Update();

	//ImGui::Begin("mouseCheck");
	////ImGui::SetWindowPos({ 200 , 200 });
	//ImGui::SetWindowSize({ 500,100 });
	//ImGui::InputInt("mouseNum", &num_);
	//ImGui::InputFloat2("position", &mousePos.x);
	//ImGui::End();

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

	//ジャンプエフェクト処理
	if (input->TriggerKey(DIK_A)) { isDashFlag = true; }
	if (isDashFlag == true) { dashtimer++; }
	if (dashtimer >= 10) {
		dashtimer = 0;
		isDashFlag = false;
	}
	//ダッシュエフェクト処理
	if (input->TriggerKey(DIK_W)) { isJumpFlag = true; }
	if (isJumpFlag == true) { jumptimer++; }
	if (jumptimer >= 7) {
		jumptimer = 0;
		isJumpFlag = false;
	}

	if (sceneObj_->chipManager_->GetPattern() != 0)
	{
		//並列回路の電気が通る
		if (modeC == 0) {
			if (isStockFlag2 == false) {
				if (input->TriggerKey(DIK_SPACE)) { isHeidenFlag = true; }
				if (isHeidenFlag == true) { heidenTimer++; }
				if (heidenTimer >= 30) {
					heidenTimer = 30;
					isStockFlag2 = true;
				}
			}
			/*else if (isStockFlag2 == true) {
				if (input->TriggerKey(DIK_SPACE)) {
					heidenTimer = 0;
					isHeidenFlag = false;
					isStockFlag2 = false;
				}
			}*/
		}

		//直列回路の電気が通る
		if (modeC == 1) {
			if (isStockFlag == false) {
				if (input->TriggerKey(DIK_SPACE)) { isTyokudenFlag = true; }
				if (isTyokudenFlag == true) { tyokudenTimer++; }
				if (tyokudenTimer >= 15) {
					tyokudenTimer = 15;
					isStockFlag = true;
				}
			}
			/*else if (isStockFlag == true) {
				if (input->TriggerKey(DIK_SPACE)) {
					tyokudenTimer = 0;
					isTyokudenFlag = false;
					isStockFlag = false;
				}
			}*/
		}
	}
	else
	{
		heidenTimer = 0;
		tyokudenTimer = 0;
		isHeidenFlag = false;
		isStockFlag2 = false;
	}

	if (player_->GetIsGoal() == true)
	{
		pSourceVoice[0]->Stop();
		soundCheckFlag = 0;
		timeFps = sceneObj_->timeFps;

		sceneObj_->timeTM = timeTM;
		sceneObj_->timeM = timeM;
		sceneObj_->timeTS = timeTS;
		sceneObj_->timeS = timeS;


		for (SphereCollider* s : sphereSave)
		{
			CollisionManager::GetInstance()->RemoveCollider(s);
			
		}

		controller_->ChangeSceneNum(S_CLEAR);
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
#pragma endregion
#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(controller_->dxCommon_->GetCommandList());
	// 背景スプライト描画
	if (modeC == 0)
	{
		sprite_->Draw();
	}
	else
	{
		sprite2_->Draw();
	}


	if (tyokudenTimer >= 1 && tyokudenTimer <= 2) { spritetyokuden1_->Draw(); }
	else if (tyokudenTimer >= 3 && tyokudenTimer <=5 ) { spritetyokuden2_->Draw(); }
	else if (tyokudenTimer >= 6 && tyokudenTimer <= 8) { spritetyokuden3_->Draw(); }
	else if (tyokudenTimer >= 9 && tyokudenTimer <= 11) { spritetyokuden4_->Draw(); }
	else if (tyokudenTimer >= 12 && tyokudenTimer <= 14) { spritetyokuden5_->Draw(); }
	else if (tyokudenTimer >= 15 && tyokudenTimer <= 15) { spritetyokuden6_->Draw(); }

	if (heidenTimer >= 1 && heidenTimer <= 5) { spriteheiden1_->Draw(); }
	else if (heidenTimer >= 6 && heidenTimer <= 10) { spriteheiden2_->Draw(); }
	else if (heidenTimer >= 11 && heidenTimer <= 15) { spriteheiden3_->Draw(); }
	else if (heidenTimer >= 16 && heidenTimer <= 20) { spriteheiden4_->Draw(); }
	else if (heidenTimer >= 21 && heidenTimer <= 25) { spriteheiden5_->Draw(); }
	else if (heidenTimer >= 26 && heidenTimer <= 30) { spriteheiden6_->Draw(); }

	if (pause == 1)
	{
		sprite3_->Draw();
		sprite5_->Draw();
	}
	else if (pause == 2)
	{
		sprite4_->Draw();
		sprite6_->Draw();
	}

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
	sceneObj_->chipManager_->Draw(controller_->dxCommon_);

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

			GenerBlock(Vector3(x, y, z), num);
		}
	}
}

void PlayScene::GenerBlock(Vector3 BlockPos, int num)
{
	sceneObj_->asobj_[num]->worldTransform.translation_.x = BlockPos.x;
	sceneObj_->asobj_[num]->worldTransform.translation_.y = BlockPos.y;
	sceneObj_->asobj_[num]->worldTransform.translation_.z = BlockPos.z;
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

			}
			blockType = BlockType::Init;
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

	num_ = num;

	if (attribute == COLLISION_ATTR_LAND)
	{

		for (int i = 0; i < SPHERE_COLISSION_NUM; i++)
		{
			sphere[i] = new SphereCollider;
			sphereSave.push_back(sphere[i]);
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
			sphereSave.push_back(sphere[i]);
			CollisionManager::GetInstance()->AddCollider(sphere[i]);
			spherePos[i] = sceneObj_->asobj_[num]->worldTransform.translation_;
			sphere[i]->SetBasisPos(&spherePos[i]);
			sphere[i]->SetRadius(1.0f);
			sphere[i]->SetAttribute(attribute);
			sphere[i]->Update();
		}
		sceneObj_->asobj_[num]->SetColor({ 0.0f,0.0f,1.0f,1.0f });
	}
	else if (attribute == COLLISION_ATTR_WALL)
	{
		for (int i = 0; i < SPHERE_COLISSION_NUM; i++)
		{
			sphere[i] = new SphereCollider;
			sphereSave.push_back(sphere[i]);
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

void PlayScene::GameTimer()
{
	timeFps++;

	if (timeFps >= 60)
	{
		timeS++;
		timeFps = 0;
	}
	else
	{
		timeFps;
	}

	if (timeS >= 10)
	{
		timeTS++;
		timeS = 0;
	}

	if (timeTS >= 6)
	{
		timeM++;
		timeTS = 0;
		if (timeM >= 10)
		{
			timeTM++;
			timeM = 0;
		}
	}

}

void PlayScene::DrawGameTimer()
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

