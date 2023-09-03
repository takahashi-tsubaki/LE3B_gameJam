#include "MyGame.h"


void DebugOutputFormatString(const char* format, ...) {
#ifdef _DEBUG
	va_list valist;
	va_start(valist, format);
	vprintf(format, valist);
	va_end(valist);
#endif
}

void MyGame::Initialize()
{
	Framework::Initialize();

	fbxManager = FbxManager::Create();


	OutputDebugStringA("Hello DirectX!!\n");


	//情的初期化
	Sprite::StaticInitialize(dxCommon_->GetDevice(), WinApp::window_width, WinApp::window_height);
	// 3Dオブジェクト静的初期化
	Object3d::StaticInitialize(dxCommon_->GetDevice());
	//ライト情的初期化
	Light::StaticInitalize(dxCommon_->GetDevice());
	//パーティクル情的初期化
	ParticleManager::StaticInitialize(dxCommon_->GetDevice(), dxCommon_->GetCommandList());

	//FBXの初期化
	FbxLoader::GetInstance()->Initialize(dxCommon_->GetDevice());

	/*Sprite::LoadTexture(100,L"Resources/white1x1.png");*/

	postEffect = new PostEffect();
	postEffect->Initialize();

	//ゲームシーンの初期化
	gameScene = new GameScene();
	gameScene->Initalize(dxCommon_,input,gamePad_);
}

void MyGame::Finalize()
{

	delete gameScene;
	delete postEffect;
	//基底クラスの終了処理
	Framework::Finalize();
}

void MyGame::Update()
{

	//基底クラスの更新処理
	Framework::Update();

	gameScene->Update();
	

}

void MyGame::Draw()
{
	/*postEffect->PreDrawScene(dxCommon_->GetCommandList());*/
	
	/*postEffect->PostDrawScene(dxCommon_->GetCommandList());*/

	//描画前処理
	dxCommon_->preDraw();
	//ゲームシーンの描画
	gameScene->Draw();

	/*postEffect->Draw(dxCommon_->GetCommandList());*/

	imgui->End();

	imgui->Draw();

	//描画後処理
	dxCommon_->postDraw();

	fps->FpsControlEnd();
}
