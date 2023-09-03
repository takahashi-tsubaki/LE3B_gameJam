#include "GameClearScene.h"
#include "ImguiManager.h"
GameClearScene::GameClearScene(SceneManager* controller, SceneObjects* sceneObj)
{
	controller_ = controller;
	sceneObj_ = sceneObj;
}

GameClearScene::~GameClearScene()
{
	sceneObj_->Reset();
}

void GameClearScene::Initialize()
{
	sprite_ = Sprite::Create(4, { 310,200 });
}

void GameClearScene::Update(Input* input, GamePad* gamePad)
{
	gamePad->Update();
	if (input->TriggerKey(DIK_RETURN) || gamePad->ButtonTrigger(X))
	{
		controller_->ChangeSceneNum(S_TITLE);
	}

	assert(input);
	controller_->camera_->Update();
}

void GameClearScene::Draw()
{
#pragma region �O�i�X�v���C�g�`��
	// �O�i�X�v���C�g�`��O����
	Sprite::PreDraw(controller_->dxCommon_->GetCommandList());

	//sprite_->Draw();
	/// <summary>
	/// �����ɑO�i�X�v���C�g�̕`�揈����ǉ��ł���
	/// </summary>
	sprite_->Draw();
	//
	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();

#pragma endregion

}
