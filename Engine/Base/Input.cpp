#include "Input.h"

void Input::Initialize(WinApp* winApp)
{
	this->winapp_ = winApp;
	HRESULT result;

	//DirectInputの初期化
	result = DirectInput8Create(winapp_->GetInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
	assert(SUCCEEDED(result));

	//キーボードデバイスの生成
	result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	assert(SUCCEEDED(result));

	//入力データ形式のセット
	result = keyboard->SetDataFormat(&c_dfDIKeyboard);
	assert(SUCCEEDED(result));

	//排他制御レベルのセット
	result = keyboard->SetCooperativeLevel(winapp_->Gethwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));
	//DISCL_FOREGROUND   画面が手前にある場合のみ入力を受け付ける
	//DISCL_NONEXCLUSIVE デバイスをこのアプリだけで専有しない
	//DISCL_NOWINKEY     Windowsキーを無効にする

}

void Input::Update()
{

	//前回のキー入力を保存
	memcpy(oldkeys, keys, sizeof(keys));

	//キーボード情報の取得開始
	keyboard->Acquire();

	//全キーの入力状態を取得する
	keyboard->GetDeviceState(sizeof(keys), keys);

}

bool Input::PushKey(BYTE keyNum)
{
	// 指定キーを押していればtrueを返す
	if (keys[keyNum])
	{
		return true;
	}
	// そうでなければfalseを返す
	return false;
}

bool Input::TriggerKey(BYTE keyNum)
{
	// 指定キーを押された瞬間にtrueを返す
	if (!oldkeys[keyNum] && keys[keyNum])
	{
		return true;
	}
	// そうでなければfalseを返す
	return false;
}

bool Input::ReleaseKey(BYTE keyNum)
{
	// 指定キーを離されているた時にtrueを返す
	if (oldkeys[keyNum] && !keys[keyNum])
	{
		return true;
	}
	// そうでなければfalseを返す
	return false;
}

Input* Input::GetInstance()
{
	static Input instance;
	return &instance;
}
