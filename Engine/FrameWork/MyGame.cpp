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


	//��I������
	Sprite::StaticInitialize(dxCommon_->GetDevice(), WinApp::window_width, WinApp::window_height);
	// 3D�I�u�W�F�N�g�ÓI������
	Object3d::StaticInitialize(dxCommon_->GetDevice());
	//���C�g��I������
	Light::StaticInitalize(dxCommon_->GetDevice());
	//�p�[�e�B�N����I������
	ParticleManager::StaticInitialize(dxCommon_->GetDevice(), dxCommon_->GetCommandList());

	//FBX�̏�����
	FbxLoader::GetInstance()->Initialize(dxCommon_->GetDevice());

	/*Sprite::LoadTexture(100,L"Resources/white1x1.png");*/

	postEffect = new PostEffect();
	postEffect->Initialize();

	//�Q�[���V�[���̏�����
	gameScene = new GameScene();
	gameScene->Initalize(dxCommon_,input,gamePad_);
}

void MyGame::Finalize()
{

	delete gameScene;
	delete postEffect;
	//���N���X�̏I������
	Framework::Finalize();
}

void MyGame::Update()
{

	//���N���X�̍X�V����
	Framework::Update();

	gameScene->Update();
	

}

void MyGame::Draw()
{
	/*postEffect->PreDrawScene(dxCommon_->GetCommandList());*/
	
	/*postEffect->PostDrawScene(dxCommon_->GetCommandList());*/

	//�`��O����
	dxCommon_->preDraw();
	//�Q�[���V�[���̕`��
	gameScene->Draw();

	/*postEffect->Draw(dxCommon_->GetCommandList());*/

	imgui->End();

	imgui->Draw();

	//�`��㏈��
	dxCommon_->postDraw();

	fps->FpsControlEnd();
}
