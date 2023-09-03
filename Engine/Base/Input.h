#pragma once
#include <cassert>

#define DIRECTINPUT_VERSION  0x0800
#include <dinput.h>

#include "WinApp.h"
#include <windows.h>
#include <wrl.h>

#pragma comment(lib,"dinput8.lib")//directInput�̃o�[�W����
#pragma comment(lib,"dxguid.lib")

class Input
{
	//�����o�֐�
public:

	template<class Type> using ComPtr = Microsoft::WRL::ComPtr<Type>;

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(WinApp* winApp);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// 
	/// </summary>
	/// <returns>������Ă��邩�ǂ���</returns>
	bool PushKey(BYTE keyNum);

	/// <summary>
	/// 
	/// </summary>
	/// <returns>���������ǂ���</returns>
	bool TriggerKey(BYTE keyNum);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="keyNum"></param>
	/// <returns>�����ꂽ���ǂ���</returns>
	bool ReleaseKey(BYTE keyNum);

	static Input* GetInstance();

	//�����o�ϐ�
private:

	//DirectInput�̏�����
	ComPtr<IDirectInput8> directInput = nullptr;

	//�L�[�{�[�h�f�o�C�X�̐���
	ComPtr<IDirectInputDevice8> keyboard = nullptr;

	BYTE keys[256] = {};
	BYTE oldkeys[256] = {};

	WinApp* winapp_ = nullptr;

};