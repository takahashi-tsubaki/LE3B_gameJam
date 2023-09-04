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

	
}

void GameScene::Initalize(DirectXCommon* dxCommon, Input* input, GamePad* gamePad)
{
	dxCommon_ = dxCommon;
	input_ = input;
	//�C���X�^���X�̎擾
	gamePad_ = gamePad;

	//input_ = Input::GetInstance();
	camera_ = new Camera(WinApp::window_width, WinApp::window_height);
	camera_->SetEye({ 0,40.0f,-200 });

	gameCamera = new GameCamera(WinApp::window_width, WinApp::window_height,input);
	assert(gameCamera);

	
	
	//// �J���������_���Z�b�g
	//camera_->SetTarget({ 0, 0, 0 });
	// 3D�I�u�W�F�N�g�ɃJ�������Z�b�g
	Object3d::SetCamera(gameCamera);
	//���C�g����
	light_ = Light::Create();
	//���C�g�F��ݒ�
	light_->SetLightColor({ 1,1,1 });
	//3D�I�u�W�F�N�g�Ƀ��C�g���Z�b�g
	Object3d::SetLight(light_);

	//�f�o�C�X���Z�b�g
	FbxObject3d::SetDevice(dxCommon_->GetDevice());
	//�J�������Z�b�g
	FbxObject3d::SetCamera(gameCamera);
	//�O���t�B�b�N�X�p�C�v���C������
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

	
	//�����蔻��
	colMan->CheckAllCollisions();

}
void GameScene::Draw()
{
	sceneManager->SceneDraw();
//#pragma region �w�i�X�v���C�g�`��
//	// �w�i�X�v���C�g�`��O����
//	Sprite::PreDraw(dxCommon_->GetCommandList());
//	// �w�i�X�v���C�g�`��
//	
//	
//	/// <summary>
//	/// �����ɔw�i�X�v���C�g�̕`�揈����ǉ��ł���
//	/// </summary>
//
//	// �X�v���C�g�`��㏈��
//	Sprite::PostDraw();
//#pragma endregion
//
//#pragma region 3D�I�u�W�F�N�g�`��
//	//// 3D�I�u�W�F�N�g�`��O����
//	Object3d::PreDraw(dxCommon_->GetCommandList());
//
//	//// 3D�I�u�W�F�N�g�̕`��
//
//	/*fbxObject->Draw(dxCommon_->GetCommandList());*/
//
//	skydomeO_->Draw();
//
//	player_->Draw();
//	enemy_->Draw();
//
//	///// <summary>
//	///// ������3D�I�u�W�F�N�g�̕`�揈����ǉ��ł���
//	///// </summary>
//
//	//// 3D�I�u�W�F�N�g�`��㏈��
//	Object3d::PostDraw();
//#pragma endregion
//
//#pragma region �p�[�e�B�N���`��
//
//	//// �p�[�e�B�N���`��O����
//	Particle::PreDraw(dxCommon_->GetCommandList());
//
//	//// 3D�I�u�W�F�N�g�̕`��
//	
//	///// <summary>
//	///// ������3D�I�u�W�F�N�g�̕`�揈����ǉ��ł���
//	///// </summary>
//
//	//// �p�[�e�B�N���`��㏈��
//	Particle::PostDraw();
//
//#pragma endregion
//
////#pragma region �؂�|���S���`��
////	postEffect->PreDrawScene(dxCommon_->GetCommandList());
////
////	//// �؂�|���S���̕`��
////	postEffect->Draw(dxCommon_->GetCommandList());
////	///// <summary>
////	///// �����ɂ؂�|���S���̕`�揈����ǉ��ł���
////	///// </summary>
////
////	
////
////	postEffect->PostDrawScene(dxCommon_->GetCommandList());
////
////
////
////#pragma endregion
//#pragma region �O�i�X�v���C�g�`��
//	// �O�i�X�v���C�g�`��O����
//	Sprite::PreDraw(dxCommon_->GetCommandList());
//
//	//sprite_->Draw();
//	/// <summary>
//	/// �����ɑO�i�X�v���C�g�̕`�揈����ǉ��ł���
//	/// </summary>
//
//	//
//	// �X�v���C�g�`��㏈��
//	Sprite::PostDraw();
//
//#pragma endregion
}


