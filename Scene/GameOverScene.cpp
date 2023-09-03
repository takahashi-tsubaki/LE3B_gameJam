#include "GameOverScene.h"
#include "ImguiManager.h"
GameOverScene::GameOverScene(SceneManager* controller, SceneObjects* sceneObj)
{
	controller_ = controller;
	sceneObj_ = sceneObj;
}

GameOverScene::~GameOverScene()
{
	sceneObj_->Reset();
}

void GameOverScene::Initialize()
{
	sprite_ = Sprite::Create(5, { 400,200 });
}

void GameOverScene::Update(Input* input, GamePad* gamePad)
{
	gamePad->Update();
	if (input->TriggerKey(DIK_RETURN) || gamePad->ButtonTrigger(X))
	{
		controller_->ChangeSceneNum(S_TITLE);
	}
	assert(input);
	controller_->camera_->Update();
}

void GameOverScene::Draw()
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
