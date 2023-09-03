#pragma once
#include "WinApp.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "GamePad.h"
#include "FPS.h"

#include "ImguiManager.h"
#include "Sprite.h"
#include"Light.h"
#include "ParticleManager.h"
#include "FbxLoader.h"
class Framework
{
public:

	//������
	virtual void Initialize();

	//�I��
	virtual void Finalize();

	//���t���[���X�V
	virtual void Update();

	//�`��
	virtual void Draw() = 0;

	virtual void SetRequest(bool request) { endRequest_ = request; }

	//�I���`�F�b�N
	virtual bool IsEndRequest() { return endRequest_; }

	//�f�X�g���N�^
	virtual ~Framework() = default;

	//���s
	void Run();

protected:
	//FPS
	FPS* fps = new FPS;
	WinApp* winApp = nullptr;
	Input* input = nullptr;
	GamePad* gamePad_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
	ImguiManager* imgui = nullptr;
	bool endRequest_ = false;
};