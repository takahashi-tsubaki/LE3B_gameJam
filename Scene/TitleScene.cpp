#include "TitleScene.h"

TitleScene::TitleScene(SceneManager* controller, SceneObjects* sceneObj)
{
	controller_ = controller;
	sceneObj_ = sceneObj;

}

TitleScene::~TitleScene()
{


	sceneObj_->Reset();
	//delete sceneObj_->skydomeO_;
	/*sceneObj_->Delete();*/
}

void TitleScene::Initialize()
{

}

void TitleScene::Update(Input* input, GamePad* gamePad)
{
	sceneObj_->skydomeO_->Update();
	controller_->camera_->Update();
	gamePad->Update();
	if (input->TriggerKey(DIK_RETURN) || gamePad->ButtonTrigger(X))
	{
		controller_->ChangeSceneNum(S_PLAY);
	}
}

void TitleScene::Draw()
{
#pragma region �w�i�X�v���C�g�`��
	// �w�i�X�v���C�g�`��O����
	Sprite::PreDraw(controller_->dxCommon_->GetCommandList());
	// �w�i�X�v���C�g�`��


	/// <summary>
	/// �����ɔw�i�X�v���C�g�̕`�揈����ǉ��ł���
	/// </summary>

	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
#pragma endregion

#pragma region 3D�I�u�W�F�N�g�`��
	//// 3D�I�u�W�F�N�g�`��O����
	Object3d::PreDraw(controller_->dxCommon_->GetCommandList());

	//// 3D�I�u�W�F�N�g�̕`��

	/*fbxObject->Draw(dxCommon_->GetCommandList());*/

	sceneObj_->skydomeO_->Draw();
	//skydomeO_->Draw();

	///// <summary>
	///// ������3D�I�u�W�F�N�g�̕`�揈����ǉ��ł���
	///// </summary>

	//// 3D�I�u�W�F�N�g�`��㏈��
	Object3d::PostDraw();
#pragma endregion


	//#pragma region �؂�|���S���`��
	//	postEffect->PreDrawScene(dxCommon_->GetCommandList());
	//
	//	//// �؂�|���S���̕`��
	//	postEffect->Draw(dxCommon_->GetCommandList());
	//	///// <summary>
	//	///// �����ɂ؂�|���S���̕`�揈����ǉ��ł���
	//	///// </summary>
	//
	//	
	//
	//	postEffect->PostDrawScene(dxCommon_->GetCommandList());
	//
	//
	//
	//#pragma endregion
#pragma region �O�i�X�v���C�g�`��
	// �O�i�X�v���C�g�`��O����
	Sprite::PreDraw(controller_->dxCommon_->GetCommandList());

	//sprite_->Draw();
	/// <summary>
	/// �����ɑO�i�X�v���C�g�̕`�揈����ǉ��ł���
	/// </summary>
	//
	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();

#pragma endregion
}
