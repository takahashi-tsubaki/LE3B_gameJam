#pragma once

#include <windows.h>

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

#include <xinput.h>
#pragma comment (lib,"xinput.lib")

//���O�̊ȗ���
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
	/// ������
	/// </summary>
	

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �{�^���̃g���K�[����
	/// </summary>
	/// <param name="button">�`�F�b�N�������{�^��</param>
	/// <returns>���������ǂ���</returns>
	bool ButtonTrigger(Button button);

	/// <summary>
	/// �X�e�B�b�N�̃g���K�[����
	/// </summary>
	/// <param name="stick">�X�e�B�b�N�̕���</param>
	/// <param name="deadRange">�f�b�h�]�[���͈̔�</param>
	/// <param name="deadRate">�f�b�h�]�[������̓x����(�����l1.0f)</param>
	/// <returns>�|�������ǂ���</returns>
	bool StickTrigger(Stick stick,const float& deadRange = 0.3f,const Vector2& deadRate = {1.0f,1.0f});

	/// <summary>
	/// �{�^���̓���
	/// </summary>
	/// <param name="button">�`�F�b�N�������{�^��</param>
	/// <returns>���������ǂ���</returns>
	bool ButtonInput(Button button);

	/// <summary>
	/// �X�e�B�b�N�̓���
	/// </summary>
	/// <param name="stick">�X�e�B�b�N�̕���</param>
	/// <param name="deadRange">�f�b�h�]�[���͈̔�</param>
	/// <param name="deadRate">�f�b�h�]�[������̓x����(�����l1.0f)</param>
	/// <returns>�|�������ǂ���</returns>
	bool StickInput(Stick stick, const float& deadRange = 0.3f, const Vector2& deadRate = { 1.0f,1.0f });

	/// <summary>
	/// �{�^���𗣂����u��
	/// </summary>
	/// <param name="button">�`�F�b�N�������{�^��</param>
	/// <returns>���������ǂ���</returns>
	bool ButtonOffTrigger(Button button);

	/// <summary>
	///	�X�e�B�b�N�𗣂����u��
	/// </summary>
	/// <param name="stick">�X�e�B�b�N�̕���</param>
	/// <param name="deadRange">�f�b�h�]�[���͈̔�</param>
	/// <param name="deadRate">�f�b�h�]�[������̓x����(�����l1.0f)</param>
	/// <returns>���������ǂ���</returns>
	bool StickOffTrigger(Stick stick, const float& deadRange = 0.3f, const Vector2& deadRate = { 1.0f,1.0f });

	/// <summary>
	/// �R���g���[���[�̍��X�e�B�b�N�̃x�N�g��
	/// </summary>
	/// <param name="deadRate">�f�b�h�]�[������̓x����(�����l1.0f)</param>
	/// <returns>�x�N�g��</returns>
	Vector2 GetLeftStickVec(const Vector2& deadRate = { 1.0f,1.0f });

	/// <summary>
	/// �R���g���[���[�̉E�X�e�B�b�N�̃x�N�g��
	/// </summary>
	/// <param name="deadRate">�f�b�h�]�[������̓x����(�����l1.0f)</param>
	/// <returns>�x�N�g��</returns>
	Vector2 GetRightStickVec(const Vector2& deadRate = { 1.0f,1.0f });

	/// <summary>
	/// �R���g���[���[��U��������
	/// </summary>
	/// <param name="power">�U���̋���0.0f�`1.0f</param>
	/// <param name="span">�U���̎��ԃt���[��</param>
	void ShakeController(const float& power, const int& span);

	//�����o�ϐ�
private:

	XINPUT_STATE xinputState{};
	XINPUT_STATE oldXinputState{};
	//�R���g���[���[�̐U���̋���
	float shakePower = 0.0f;
	//�R���g���[���[�̐U���̒���
	int shakeTimer = 0;
	//�U�������邩�ǂ���
	bool whetherShake = false;
	//�f�b�h�]�[���ɓ����Ă��邩(deadRate : �f�b�h�]�[������̓x�����A1.0f���ƃf�t�H���g)
	bool StickInDeadZone(Vector2& thumb,const Vector2& deadRate);

	GamePad& operator=(const GamePad&) = delete;
	GamePad(const GamePad&) = delete;

	//�ō����͋��x
	const float STICK_INPUT_MAX = 32768.0f;


};

