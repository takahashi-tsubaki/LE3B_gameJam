#include "ImguiManager.h"
void ImguiManager::Initialize(WinApp* winApp, DirectXCommon* dxCommon)
{

	HRESULT result;
	dxCommon_ = dxCommon;

	////ImGui�̃R���e�L�X�g�𐶐�
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	//Win32�p�����֐�
	ImGui_ImplWin32_Init(winApp->Gethwnd());

	//�f�X�N���v�^�ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC desc = {  };
	desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	desc.NumDescriptors = 1;
	desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

	//�f�X�N���v�^�q�[�v
	result = dxCommon_->GetDevice()->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&srvHeap_));
	assert(SUCCEEDED(result));

	//DirectX12�p������
	ImGui_ImplDX12_Init(dxCommon_->GetDevice(),
		static_cast<int>(dxCommon_->GetBackBufferCount()),
		DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, srvHeap_.Get(),
		srvHeap_->GetCPUDescriptorHandleForHeapStart(),
		srvHeap_->GetGPUDescriptorHandleForHeapStart()
	);

	ImGuiIO& io = ImGui::GetIO();
	//�W���t�H���g��ǉ�����
	io.Fonts->AddFontDefault();

}

void ImguiManager::Finalize()
{
	//��n��
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	//�f�X�N���v�^�q�[�v�����
	srvHeap_.Reset();
}

ImguiManager* ImguiManager::GetInstance()
{
	static ImguiManager instance;
	return &instance;
}

void ImguiManager::Begin()
{
	//ImGui�t���[���J�n
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

}

void ImguiManager::End()
{
	ImGui::Render();
}

void ImguiManager::Draw()
{
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	//�f�X�N���v�^�q�[�v�̔z����Z�b�g����R�}���h
	ID3D12DescriptorHeap* ppHeaps[] = { srvHeap_.Get() };
	commandList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
	//�`��R�}���h�𔭍s
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(),commandList);

}
