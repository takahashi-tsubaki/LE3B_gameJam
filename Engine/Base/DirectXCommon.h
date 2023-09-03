#pragma once
#include"ErrorException.h"
#include "WinApp.h"
//リンクの設定
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
using namespace Microsoft::WRL;

class DirectXCommon
{
private:
	HRESULT result;

	ComPtr<IDXGIFactory7>dxgiFactory;
	ComPtr<ID3D12Device>dev;
	ComPtr<IDXGISwapChain1>swapChain1;
	ComPtr<IDXGISwapChain4>swapChain;
	ComPtr<ID3D12CommandAllocator>cmdAllocator;
	ComPtr<ID3D12GraphicsCommandList>commandList;
	ComPtr<ID3D12CommandQueue>commandQueue;
	ComPtr<ID3D12DescriptorHeap> rtvHeap;
	//コマンドキューの設定
	D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};

	std::vector<ComPtr<ID3D12Resource>>backBuffers;

	ComPtr<ID3D12DescriptorHeap> dsvHeap;

	ComPtr<ID3D12Fence> fence = nullptr;

	UINT64 fenceVal = 0;

	FLOAT clearColor[4] = { 0.1f, 0.25f, 0.5f, 0.0f };//青っぽい色

	D3D12_RESOURCE_BARRIER barrierDesc{};
	//デスクリプタヒープの設定
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};

	//深度バッファの生成
	ComPtr<ID3D12Resource> depthBuff = nullptr;

	WinApp* winApp_ = nullptr;
	

	
public:
	void Initialize(WinApp*winApp);
	void InitializeDevice();
	void InitializeCommand();
	void InitializeSwapChain();
	void InitializeRenderTargetView();
	void InitializeDeaphBuffer();
	void InitializeFence();

	//描画関連
	void preDraw();
	void postDraw();

	//Getter
	ID3D12Device* GetDevice()const { return dev.Get(); }
	ID3D12GraphicsCommandList* GetCommandList()const { return commandList.Get(); }
	static DirectXCommon* GetInstance();

	//バックバッファの数を取得
	size_t GetBackBufferCount() const { return backBuffers.size(); }
};

