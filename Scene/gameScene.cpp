#include "gameScene.h"
#pragma warning(push)
#include "FbxLoader.h"
#include "FbxObject3d.h"

#include "ImguiManager.h"
#pragma warning(pop)

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete camera_ ;
	delete fbxObject;
	delete fbxModel;

	/*safe_delete(fbxObject);
	safe_delete(fbxModel);*/
}

void GameScene::Initalize(DirectXCommon* dxCommon, Input* input, GamePad* gamePad)
{
	dxCommon_ = dxCommon;
	input_ = input;
	//インスタンスの取得
	gamePad_ = gamePad;

	//input_ = Input::GetInstance();
	camera_ = new Camera(WinApp::window_width, WinApp::window_height);
	camera_->SetEye({ 0,40.0f,-200 });

	gameCamera = new GameCamera(WinApp::window_width, WinApp::window_height,input);
	assert(gameCamera);

	
	
	//// カメラ注視点をセット
	//camera_->SetTarget({ 0, 0, 0 });
	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(gameCamera);
	//ライト生成
	light_ = Light::Create();
	//ライト色を設定
	light_->SetLightColor({ 1,1,1 });
	//3Dオブジェクトにライトをセット
	Object3d::SetLight(light_);

	//デバイスをセット
	FbxObject3d::SetDevice(dxCommon_->GetDevice());
	//カメラをセット
	FbxObject3d::SetCamera(gameCamera);
	//グラフィックスパイプライン生成
	FbxObject3d::CreateGraphicsPipeline();
	ParticleManager::SetCamera(gameCamera);

	colMan = CollisionManager::GetInstance();

	sceneObjects = new SceneObjects();

	sceneManager = new SceneManager(dxCommon_,gameCamera, sceneObjects);
	sceneManager->SceneInitialize();
	sceneObjects->Initialize(sceneManager);

}

void GameScene::Update()
{
	sceneManager->ChangeScene();
	sceneManager->SceneUpdate(input_,gamePad_);
	//gameCamera->Update();
	/*Vector3 nowEye = gameCamera->GetEye();

	light_->Update();
	gamePad_->Update();

	fbxObject->Update();


	ImGui::Begin("Camera");

	ImGui::SliderFloat("eye:x", &nowEye.x, -400.0f, 400.0f);
	ImGui::SliderFloat("eye:xz", &nowEye.z, -400.0f, 400.0f);

	ImGui::End();

	gameCamera->Update();


	skydomeO_->Update();

	player_->Update();
	enemy_->Update();*/

	
	//当たり判定
	colMan->CheckAllCollisions();

}
void GameScene::Draw()
{
	sceneManager->SceneDraw();
//#pragma region 背景スプライト描画
//	// 背景スプライト描画前処理
//	Sprite::PreDraw(dxCommon_->GetCommandList());
//	// 背景スプライト描画
//	
//	
//	/// <summary>
//	/// ここに背景スプライトの描画処理を追加できる
//	/// </summary>
//
//	// スプライト描画後処理
//	Sprite::PostDraw();
//#pragma endregion
//
//#pragma region 3Dオブジェクト描画
//	//// 3Dオブジェクト描画前処理
//	Object3d::PreDraw(dxCommon_->GetCommandList());
//
//	//// 3Dオブジェクトの描画
//
//	/*fbxObject->Draw(dxCommon_->GetCommandList());*/
//
//	skydomeO_->Draw();
//
//	player_->Draw();
//	enemy_->Draw();
//
//	///// <summary>
//	///// ここに3Dオブジェクトの描画処理を追加できる
//	///// </summary>
//
//	//// 3Dオブジェクト描画後処理
//	Object3d::PostDraw();
//#pragma endregion
//
//#pragma region パーティクル描画
//
//	//// パーティクル描画前処理
//	Particle::PreDraw(dxCommon_->GetCommandList());
//
//	//// 3Dオブジェクトの描画
//	
//	///// <summary>
//	///// ここに3Dオブジェクトの描画処理を追加できる
//	///// </summary>
//
//	//// パーティクル描画後処理
//	Particle::PostDraw();
//
//#pragma endregion
//
////#pragma region ぺらポリゴン描画
////	postEffect->PreDrawScene(dxCommon_->GetCommandList());
////
////	//// ぺらポリゴンの描画
////	postEffect->Draw(dxCommon_->GetCommandList());
////	///// <summary>
////	///// ここにぺらポリゴンの描画処理を追加できる
////	///// </summary>
////
////	
////
////	postEffect->PostDrawScene(dxCommon_->GetCommandList());
////
////
////
////#pragma endregion
//#pragma region 前景スプライト描画
//	// 前景スプライト描画前処理
//	Sprite::PreDraw(dxCommon_->GetCommandList());
//
//	//sprite_->Draw();
//	/// <summary>
//	/// ここに前景スプライトの描画処理を追加できる
//	/// </summary>
//
//	//
//	// スプライト描画後処理
//	Sprite::PostDraw();
//
//#pragma endregion
}


