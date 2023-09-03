#pragma once
#include "WinApp.h"
#include "DirectXCommon.h"

#include <imgui_impl_win32.h>
#include "imgui_impl_dx12.h"
#include <imgui.h>
class ImguiManager
{
public:
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public:

	void Initialize(WinApp* winApp, DirectXCommon* dxCommon);

	void Finalize();

	static ImguiManager* GetInstance();

	/// <summary>
	/// 受付開始
	/// </summary>
	void Begin();

	/// <summary>
	/// 受付終了
	/// </summary>
	void End();

	/// <summary>
	/// 画面への描画
	/// </summary>
	void Draw();

private:

	DirectXCommon* dxCommon_ = nullptr;

	// SRV用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> srvHeap_;

};
