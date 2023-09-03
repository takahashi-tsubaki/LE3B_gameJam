#pragma once
#include "WinApp.h"
#include "DirectXCommon.h"

#include <imgui_impl_win32.h>
#include "imgui_impl_dx12.h"
#include <imgui.h>
class ImguiManager
{
public:
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public:

	void Initialize(WinApp* winApp, DirectXCommon* dxCommon);

	void Finalize();

	static ImguiManager* GetInstance();

	/// <summary>
	/// ��t�J�n
	/// </summary>
	void Begin();

	/// <summary>
	/// ��t�I��
	/// </summary>
	void End();

	/// <summary>
	/// ��ʂւ̕`��
	/// </summary>
	void Draw();

private:

	DirectXCommon* dxCommon_ = nullptr;

	// SRV�p�f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> srvHeap_;

};
