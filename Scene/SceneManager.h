#pragma once
#include <memory>
#include <stack>

#include "DirectXCommon.h"
#include "GameCamera.h"
#include "Input.h"
#include "GamePad.h"
#include "SceneObjects.h"
class IScene;
class Input;

class SceneManager
{
public:
	DirectXCommon* dxCommon_;
	GameCamera* camera_;

	Input* input_ = nullptr;
	GamePad* gamePad_ = nullptr;
protected:
	std::stack<std::shared_ptr<IScene>> _scene;
	SceneObjects* sceneObjects_;

	bool isChange = false;
	int sceneNum = 0;

public:

	SceneManager(DirectXCommon* dxCommon,GameCamera* camera, SceneObjects* sceneObjects);
	~SceneManager();

	//�I�u�W�F�N�g��Initialize���Ăяo��
	void ObjectInitialize();
	// �e�V�[����Initialize���Ăяo��
	void SceneInitialize();
	// �e�V�[����Update���Ăяo��
	void SceneUpdate(Input* input,GamePad* gamePad);
	// �e�V�[����Draw���Ăяo��
	void SceneDraw();

	void ChangeSceneNum(int number);
	// �V�[����ύX����
	void ChangeScene();

	void PushScene(int number);

	void PopScene();

	int GetSceneNum() { return sceneNum; }

};

