#include "Light.h"
using namespace DirectX;
ID3D12Device* Light::device_ = nullptr;

void Light::StaticInitalize(ID3D12Device* device)
{
	//�ď������`�F�b�N
	assert(!device_);
	//nullptr�`�F�b�N
	assert(device);
	//��I�����o�ϐ��̃Z�b�g
	device_ = device;
}

void Light::Initalize()
{
	HRESULT result;
	// �q�[�v�v���p�e�B
	CD3DX12_HEAP_PROPERTIES heapPropsConstantBuffer = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	// ���\�[�X�ݒ�
	CD3DX12_RESOURCE_DESC resourceDescConstantBuffer =
		CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) & ~0xff);

	// �萔�o�b�t�@�̐���
	result = device_->CreateCommittedResource(
		&heapPropsConstantBuffer, D3D12_HEAP_FLAG_NONE, &resourceDescConstantBuffer, D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr, IID_PPV_ARGS(&constBuff));
	assert(SUCCEEDED(result));

	//�萔�o�b�t�@�փf�[�^�]��
	TransfarConstBuffer();
}

void Light::Update()
{
	//�l�̍X�V���������Ƃ������萔�o�b�t�@�ɓ]������
	if (dirty)
	{
		TransfarConstBuffer();
		dirty = false;
	}
}

void Light::Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex)
{
	//�萔�o�b�t�@�r���[���Z�b�g
	cmdList->SetGraphicsRootConstantBufferView(rootParameterIndex,constBuff->GetGPUVirtualAddress());
}

Light* Light::Create()
{
	//3D�I�u�W�F�N�g�̃C���X�^���X�̐���
	Light* instance = new Light();
	//������
	instance->Initalize();
	return instance;
}

void Light::TransfarConstBuffer()
{

	HRESULT result;
	// �萔�o�b�t�@�Ƀf�[�^�]��
	ConstBufferData* constMap = nullptr;
	result = this->constBuff->Map(0, nullptr, (void**)&constMap);
	if (SUCCEEDED(result)) {
		constMap->lightv = -lightdir_;
		constMap->lightColor =lightcolor_;	// �s��̍���	
		constBuff->Unmap(0, nullptr);
	}
}

void Light::SetLightDir(Vector4& lightdir)
{
	//���K�����ăZ�b�g
	lightdir_ = lightdir.normalize();
	dirty = true;
}

void Light::SetLightColor(const XMFLOAT3 lightcolor)
{
	lightcolor_ = lightcolor;
	dirty = true;
}
