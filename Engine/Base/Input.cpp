#include "Input.h"

void Input::Initialize(WinApp* winApp)
{
	this->winapp_ = winApp;
	HRESULT result;

	//DirectInput�̏�����
	result = DirectInput8Create(winapp_->GetInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
	assert(SUCCEEDED(result));

	//�L�[�{�[�h�f�o�C�X�̐���
	result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	assert(SUCCEEDED(result));

	//���̓f�[�^�`���̃Z�b�g
	result = keyboard->SetDataFormat(&c_dfDIKeyboard);
	assert(SUCCEEDED(result));

	//�r�����䃌�x���̃Z�b�g
	result = keyboard->SetCooperativeLevel(winapp_->Gethwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));
	//DISCL_FOREGROUND   ��ʂ���O�ɂ���ꍇ�̂ݓ��͂��󂯕t����
	//DISCL_NONEXCLUSIVE �f�o�C�X�����̃A�v�������Ő�L���Ȃ�
	//DISCL_NOWINKEY     Windows�L�[�𖳌��ɂ���

}

void Input::Update()
{

	//�O��̃L�[���͂�ۑ�
	memcpy(oldkeys, keys, sizeof(keys));

	//�L�[�{�[�h���̎擾�J�n
	keyboard->Acquire();

	//�S�L�[�̓��͏�Ԃ��擾����
	keyboard->GetDeviceState(sizeof(keys), keys);

}

bool Input::PushKey(BYTE keyNum)
{
	// �w��L�[�������Ă����true��Ԃ�
	if (keys[keyNum])
	{
		return true;
	}
	// �����łȂ����false��Ԃ�
	return false;
}

bool Input::TriggerKey(BYTE keyNum)
{
	// �w��L�[�������ꂽ�u�Ԃ�true��Ԃ�
	if (!oldkeys[keyNum] && keys[keyNum])
	{
		return true;
	}
	// �����łȂ����false��Ԃ�
	return false;
}

bool Input::ReleaseKey(BYTE keyNum)
{
	// �w��L�[�𗣂���Ă��邽����true��Ԃ�
	if (oldkeys[keyNum] && !keys[keyNum])
	{
		return true;
	}
	// �����łȂ����false��Ԃ�
	return false;
}

Input* Input::GetInstance()
{
	static Input instance;
	return &instance;
}
