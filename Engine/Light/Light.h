#pragma once
#include <DirectXMath.h>
#include <d3d12.h>
#include <d3dx12.h>
#include "Vector4.h"
class Light
{
private:
	// Microsoft::WRL::���ȗ�
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	// �萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferData
	{
		Vector4 lightv;//���C�g�ւ̕�����\���x�N�g��
		XMFLOAT3 lightColor;//���C�g�̐F
	};

private://��I�����o�ϐ�
	//�f�o�C�X
	static ID3D12Device* device_;

public://��I�����o�֐�
	/// <summary>
	/// ��I������
	/// </summary>
	static void StaticInitalize(ID3D12Device* device);

private://�����o�ϐ�
	//�萔�o�b�t�@
	ComPtr<ID3D12Resource>constBuff;
	//���C�g��������(�P�ʃx�N�g��)
	Vector4 lightdir_ = { 1,0,0,0 };
	//���C�g�F
	XMFLOAT3 lightcolor_ = { 1,1,1 };
	//�_�[�e�B�t���O
	bool dirty = false;

public:
	/// <summary>
	/// �萔�o�b�t�@�]��
	/// </summary>
	void TransfarConstBuffer();

	/// <summary>
	/// ���C�g�������Z�b�g
	/// </summary>
	/// <param name="lightdir"></param>
	void SetLightDir( Vector4& lightdir);
	/// <summary>
	/// ���C�g�F���Z�b�g
	/// </summary>
	void SetLightColor(const XMFLOAT3 lightcolor);

	/// <summary>
	/// ������
	/// </summary>
	void Initalize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ID3D12GraphicsCommandList*cmdList,UINT rootParameterIndex);


	static Light* Create();
};

