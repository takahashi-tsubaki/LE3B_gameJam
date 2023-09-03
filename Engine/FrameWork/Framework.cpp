#include "Framework.h"

void Framework::Initialize()
{
	fps = new FPS();
	fps->SetFrameRate(60);

	winApp = new WinApp();
	winApp->Initialize();

	input = new Input();
	input->Initialize(winApp);

	gamePad_ = new GamePad();

	dxCommon_ = new DirectXCommon();
	dxCommon_->Initialize(winApp);

	imgui = new ImguiManager();
	imgui->Initialize(winApp, dxCommon_);
	endRequest_ = false;



	/*Sprite::LoadTexture(100,L"Resources/white1x1.png");*/

}

void Framework::Finalize()
{
	imgui->Finalize();
	winApp->Finalize();
	////FBXメモリ開放
	//FbxLoader::GetInstance()->Finalize();
	delete imgui;
	//入力解放
	delete input;
	delete winApp;
	delete dxCommon_;
	delete fps;
}

void Framework::Update()
{
	
	if (winApp->ProcessMessage())
	{
		SetRequest(true);
		//ゲームループを抜ける
	}

	fps->FpsControlBegin();
	input->Update();
	imgui->Begin();
}

void Framework::Run()
{
	//初期化
	Initialize();

	while (true)
	{
		//更新
		Update();
		if (IsEndRequest())
		{
			break;
			//ゲームループを抜ける
		}
		//描画
		Draw();
	}
	//解放処理
	Finalize();
}
