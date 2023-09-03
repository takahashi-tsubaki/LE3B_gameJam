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
	////FBX�������J��
	//FbxLoader::GetInstance()->Finalize();
	delete imgui;
	//���͉��
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
		//�Q�[�����[�v�𔲂���
	}

	fps->FpsControlBegin();
	input->Update();
	imgui->Begin();
}

void Framework::Run()
{
	//������
	Initialize();

	while (true)
	{
		//�X�V
		Update();
		if (IsEndRequest())
		{
			break;
			//�Q�[�����[�v�𔲂���
		}
		//�`��
		Draw();
	}
	//�������
	Finalize();
}
