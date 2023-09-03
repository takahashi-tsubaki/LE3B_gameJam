#include "SceneManager.h"
#include "Input.h"
#include "SceneInc.h"

#include <cassert>

SceneManager::SceneManager(DirectXCommon* dxCommon,GameCamera* camera, SceneObjects* sceneObjects)
{
	dxCommon_ = dxCommon;
	sceneObjects_ = sceneObjects;
	_scene.emplace(new TitleScene(&*this, sceneObjects_));
	camera_ = camera;

}

SceneManager::~SceneManager()
{
}

void SceneManager::SceneInitialize()
{
	_scene.top().get()->Initialize();
}

void SceneManager::SceneUpdate(Input* input, GamePad* gamePad)
{
	_scene.top().get()->Update(input,gamePad);
}

void SceneManager::SceneDraw()
{
	_scene.top().get()->Draw();
}

void SceneManager::ChangeSceneNum(int number)
{
	sceneNum = number;
	if (isChange == false)
	{
		isChange = true;
	}
}

void SceneManager::ChangeScene()
{
	if (isChange == true)
	{
		
		switch (sceneNum)
		{
		case S_TITLE:
			_scene.pop();
			_scene.emplace(new TitleScene(&*this, sceneObjects_));
			SceneInitialize();
			break;
		case S_PLAY:
			_scene.pop();
			_scene.emplace(new PlayScene(&*this, sceneObjects_));
			SceneInitialize();
			break;
		case S_CLEAR:
			_scene.pop();
			_scene.emplace(new GameClearScene(&*this, sceneObjects_));
			SceneInitialize();
			break;
		case S_OVER:
			_scene.pop();
			_scene.emplace(new GameOverScene(&*this, sceneObjects_));
			SceneInitialize();
			break;
		case S_PAUSE:
			_scene.pop();
			_scene.emplace(new PauseScene(&*this, sceneObjects_));
			SceneInitialize();
			break;
		default:
			_scene.emplace(new TitleScene(&*this, sceneObjects_));
			SceneInitialize();
			break;
		}
		isChange = false;

	
	}
	else
	{
		isChange = false;
	}
	
}

void SceneManager::PushScene(int number)
{
	sceneNum = number;
	switch (sceneNum)
	{
	case S_TITLE:
		_scene.emplace(new TitleScene(&*this, sceneObjects_));

		break;
	case S_PLAY:
		_scene.emplace(new PlayScene(&*this, sceneObjects_));
		break;
	case S_CLEAR:
		_scene.emplace(new GameClearScene(&*this, sceneObjects_));

		break;
	case S_OVER:
		_scene.emplace(new GameOverScene(&*this, sceneObjects_));

		break;
	case S_PAUSE:
		_scene.emplace(new PauseScene(&*this, sceneObjects_));

		break;
	default:
		_scene.emplace(new TitleScene(&*this, sceneObjects_));
		break;
	}
}

void SceneManager::PopScene()
{
	_scene.pop();
}
