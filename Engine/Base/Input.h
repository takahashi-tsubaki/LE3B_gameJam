#pragma once
#include <cassert>

#define DIRECTINPUT_VERSION  0x0800
#include <dinput.h>

#include "WinApp.h"
#include <windows.h>
#include <wrl.h>

#pragma comment(lib,"dinput8.lib")//directInputのバージョン
#pragma comment(lib,"dxguid.lib")

class Input
{
	//メンバ関数
public:

	template<class Type> using ComPtr = Microsoft::WRL::ComPtr<Type>;

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(WinApp* winApp);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 
	/// </summary>
	/// <returns>押されているかどうか</returns>
	bool PushKey(BYTE keyNum);

	/// <summary>
	/// 
	/// </summary>
	/// <returns>押したかどうか</returns>
	bool TriggerKey(BYTE keyNum);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="keyNum"></param>
	/// <returns>離されたかどうか</returns>
	bool ReleaseKey(BYTE keyNum);

	static Input* GetInstance();

	//メンバ変数
private:

	//DirectInputの初期化
	ComPtr<IDirectInput8> directInput = nullptr;

	//キーボードデバイスの生成
	ComPtr<IDirectInputDevice8> keyboard = nullptr;

	BYTE keys[256] = {};
	BYTE oldkeys[256] = {};

	WinApp* winapp_ = nullptr;

};