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

	//オブジェクトのInitializeを呼び出す
	void ObjectInitialize();
	// 各シーンのInitializeを呼び出す
	void SceneInitialize();
	// 各シーンのUpdateを呼び出す
	void SceneUpdate(Input* input,GamePad* gamePad);
	// 各シーンのDrawを呼び出す
	void SceneDraw();

	void ChangeSceneNum(int number);
	// シーンを変更する
	void ChangeScene();

	void PushScene(int number);

	void PopScene();

	int GetSceneNum() { return sceneNum; }

};

