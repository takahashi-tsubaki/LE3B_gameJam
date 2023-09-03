#pragma once
#include <Windows.h>

#include <tchar.h>

class WinApp
{
public:



	static LRESULT WindowProc(HWND hwnd,UINT msg,WPARAM wparam,LPARAM lparam);

	void Initialize();


	void Update();

	//getter
	HWND Gethwnd()const {return hwnd;}
	HINSTANCE GetInstance()const {return w.hInstance;}

	//
	void Finalize();

	//���b�Z�[�W����
	bool ProcessMessage();

public:

	static const int window_width = 1280;
	static const int window_height = 720;

private:

	//�E�B���h�E�N���X�̐ݒ�
	WNDCLASSEX w = {};

	//�E�B���h�E�n���h��
	HWND hwnd = nullptr;

};