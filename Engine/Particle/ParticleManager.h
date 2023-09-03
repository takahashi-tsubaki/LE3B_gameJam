#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <forward_list>
#include "MyMath.h"
#include "GameCamera.h"
#include <array>


/// <summary>
/// 3D�I�u�W�F�N�g
/// </summary>
class ParticleManager
{
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;


public: // �T�u�N���X
	// �萔�o�b�t�@�p�f�[�^�\���́i�}�e���A���j
	struct ConstBufferDataMaterial {
		Vector4 color; // �F (RGBA)
	};

	// ���_�f�[�^�\����
	struct VertexPos
	{
		Vector3 pos; // xyz���W
		float scale;
	};

	// �萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferData
	{
		Matrix4 mat;
		Matrix4 matBillboard;	// �r���{�[�h�s��
	};

	//�p�[�e�B�N���ꗱ
	struct Particle {

		//���W
		Vector3 position = {};
		//���x
		Vector3 velocity = {};
		//�����x
		Vector3 accel = {};
		//���݃t���[��
		int frame = 0;
		//�ߋ��t���[��
		int num_frame = 0;

		//�X�P�[��
		float scale = 1.0f;
		//�����l
		float s_scale = 1.0f;
		//�ŏI�l
		float e_scale = 0.0f;

		Vector4 color; // �F (RGBA)
	};

private: // �萔

	const int vertexCount = _countof(vertices);

public: // �ÓI�����o�֐�
	/// <summary>
	/// �ÓI������
	/// </summary>
	/// <param name="device">�f�o�C�X</param>
	/// <param name="window_width">��ʕ�</param>
	/// <param name="window_height">��ʍ���</param>
	static void StaticInitialize(ID3D12Device* device, ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// �O���t�B�b�N�p�C�v���C������
	/// </summary>
	/// <returns>����</returns>
	static void InitializeGraphicsPipeline();

private: // �ÓI�����o�ϐ�

	// �f�o�C�X
	static Microsoft::WRL::ComPtr<ID3D12Device> device;
	// �R�}���h���X�g
	//static Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cmdList;
	// ���[�g�V�O�l�`��
	static ComPtr<ID3D12RootSignature> rootsignature;
	// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
	static ComPtr<ID3D12PipelineState> pipelinestate;

private: // �����o�ϐ�
	// �f�X�N���v�^�T�C�Y
	UINT descriptorHandleIncrementSize;
	// �f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> descHeap;
	// ���_�o�b�t�@
	ComPtr<ID3D12Resource> vertBuff;
	// �e�N�X�`���o�b�t�@
	ComPtr<ID3D12Resource>texbuff;
	// �V�F�[�_���\�[�X�r���[�̃n���h��(CPU)
	CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
	// �V�F�[�_���\�[�X�r���[�̃n���h��(CPU)
	CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;

	// ���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView;
	// ���_�f�[�^�z��
	VertexPos vertices[2024];
	// �萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuff;

	//�p�[�e�B�N���z��
	std::forward_list<Particle>particles;

	ConstBufferDataMaterial* constMapMaterial = nullptr;
private:// �����o�֐�

	/// <summary>
	/// 3D�I�u�W�F�N�g����
	/// </summary>
	/// <returns></returns>
	ParticleManager* Create();

	/// <summary>
	/// �f�X�N���v�^�q�[�v�̏�����
	/// </summary>
	void InitializeDescriptorHeap();

	/// <summary>
	/// �e�N�X�`���ǂݍ���
	/// </summary>
	void LoadTexture();

	/// <summary>
	/// ���f���쐬
	/// </summary>
	void CreateModel();

public: // �����o�֐�

	ParticleManager();
	~ParticleManager();

	void LoadTexture(const std::string& fileName);
	bool Initialize();
	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
	void Draw(ID3D12GraphicsCommandList* cmdList);
	/// <summary>
	/// �}�l�[�W���[�̍��W�����ƂɃ����_���ɕ��o����
	/// </summary>

	void RandParticle(Vector3 pos);


	/// <summary>
	/// �p�[�e�B�N���̒ǉ�
	/// </summary>
	///	<param name="life">��������</param>
	///	<param name="position">�������W</param>
	///	<param name="velocity">���x</param>
	///	<param name="accel">�����x</param>
	void Add(int life, Vector3 position, Vector3 velociy, Vector3 accel, float start_scale, float end_scale);

	static void SetCamera(Camera* camera) { ParticleManager::camera = camera; }

	// ���[���h�g�����X�t�H�[���̐ݒ�
	void SetWorldTransform(WorldTransform wtf) { wtf_ = wtf; };
	// �p�[�e�B�N�������ʒu�̐ݒ�
	void Setposition(Vector3 position) { wtf_.translation_ = position; };
	void SetMatWorld(Matrix4 mat) { wtf_.matWorld_ = mat; };
	void SetBillboardMatWorld(Matrix4 mat) { bill = mat; };

	WorldTransform GetWorldTransform()
	{
		return wtf_;
	};

private: // �����o�ϐ�
	static Camera* camera;
	// ���[�J���X�P�[��
	WorldTransform wtf_;
	Matrix4 bill;

};