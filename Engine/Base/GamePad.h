#pragma once

#include <windows.h>

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

#include <xinput.h>
#pragma comment (lib,"xinput.lib")

//名前の簡略化
enum Button
{
	A = XINPUT_GAMEPAD_A,
	B = XINPUT_GAMEPAD_B,
	Y = XINPUT_GAMEPAD_Y,
	X = XINPUT_GAMEPAD_X,
	START = XINPUT_GAMEPAD_START,
	BACK  = XINPUT_GAMEPAD_BACK,
	LB    = XINPUT_GAMEPAD_LEFT_SHOULDER,
	RB    = XINPUT_GAMEPAD_RIGHT_SHOULDER,
	LT,
	RT,
};

enum Stick
{
	L_UP,L_DOWN,L_LEFT,L_RIGHT,
	R_UP,R_DOWN,R_LEFT,R_RIGHT,
	XBOX_STICK_NUM
};

class GamePad
{

public:

	GamePad();
	~GamePad();

	/// <summary>
	/// 初期化
	/// </summary>
	

	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// ボタンのトリガー入力
	/// </summary>
	/// <param name="button">チェックしたいボタン</param>
	/// <returns>押したかどうか</returns>
	bool ButtonTrigger(Button button);

	/// <summary>
	/// スティックのトリガー入力
	/// </summary>
	/// <param name="stick">スティックの方向</param>
	/// <param name="deadRange">デッドゾーンの範囲</param>
	/// <param name="deadRate">デッドゾーン判定の度合い(初期値1.0f)</param>
	/// <returns>倒したかどうか</returns>
	bool StickTrigger(Stick stick,const float& deadRange = 0.3f,const Vector2& deadRate = {1.0f,1.0f});

	/// <summary>
	/// ボタンの入力
	/// </summary>
	/// <param name="button">チェックしたいボタン</param>
	/// <returns>押したかどうか</returns>
	bool ButtonInput(Button button);

	/// <summary>
	/// スティックの入力
	/// </summary>
	/// <param name="stick">スティックの方向</param>
	/// <param name="deadRange">デッドゾーンの範囲</param>
	/// <param name="deadRate">デッドゾーン判定の度合い(初期値1.0f)</param>
	/// <returns>倒したかどうか</returns>
	bool StickInput(Stick stick, const float& deadRange = 0.3f, const Vector2& deadRate = { 1.0f,1.0f });

	/// <summary>
	/// ボタンを離した瞬間
	/// </summary>
	/// <param name="button">チェックしたいボタン</param>
	/// <returns>離したかどうか</returns>
	bool ButtonOffTrigger(Button button);

	/// <summary>
	///	スティックを離した瞬間
	/// </summary>
	/// <param name="stick">スティックの方向</param>
	/// <param name="deadRange">デッドゾーンの範囲</param>
	/// <param name="deadRate">デッドゾーン判定の度合い(初期値1.0f)</param>
	/// <returns>離したかどうか</returns>
	bool StickOffTrigger(Stick stick, const float& deadRange = 0.3f, const Vector2& deadRate = { 1.0f,1.0f });

	/// <summary>
	/// コントローラーの左スティックのベクトル
	/// </summary>
	/// <param name="deadRate">デッドゾーン判定の度合い(初期値1.0f)</param>
	/// <returns>ベクトル</returns>
	Vector2 GetLeftStickVec(const Vector2& deadRate = { 1.0f,1.0f });

	/// <summary>
	/// コントローラーの右スティックのベクトル
	/// </summary>
	/// <param name="deadRate">デッドゾーン判定の度合い(初期値1.0f)</param>
	/// <returns>ベクトル</returns>
	Vector2 GetRightStickVec(const Vector2& deadRate = { 1.0f,1.0f });

	/// <summary>
	/// コントローラーを振動させる
	/// </summary>
	/// <param name="power">振動の強さ0.0f～1.0f</param>
	/// <param name="span">振動の時間フレーム</param>
	void ShakeController(const float& power, const int& span);

	//メンバ変数
private:

	XINPUT_STATE xinputState{};
	XINPUT_STATE oldXinputState{};
	//コントローラーの振動の強さ
	float shakePower = 0.0f;
	//コントローラーの振動の長さ
	int shakeTimer = 0;
	//振動させるかどうか
	bool whetherShake = false;
	//デッドゾーンに入っているか(deadRate : デッドゾーン判定の度合い、1.0fだとデフォルト)
	bool StickInDeadZone(Vector2& thumb,const Vector2& deadRate);

	GamePad& operator=(const GamePad&) = delete;
	GamePad(const GamePad&) = delete;

	//最高入力強度
	const float STICK_INPUT_MAX = 32768.0f;


};

