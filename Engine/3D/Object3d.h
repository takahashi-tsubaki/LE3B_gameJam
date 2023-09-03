#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include <string>
#include "Model.h"
#include "Camera.h"
#include "GameCamera.h"
#include "Light.h"

#include "worldTransform.h"

#include "Vector3.h"

/// <summary>
/// 3D�I�u�W�F�N�g
/// </summary>
class Object3d
{
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: // �T�u�N���X	

	// �p�C�v���C���Z�b�g
	struct PipelineSet
	{
		// ���[�g�V�O�l�`��
		ComPtr<ID3D12RootSignature> rootsignature;
		// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
		ComPtr<ID3D12PipelineState> pipelinestate;
	};

	// �萔�o�b�t�@�p�f�[�^�\����B0
	struct ConstBufferDataB0
	{
		Matrix4 mat; // 3D�ϊ��s��
		Vector4 color;
	};

private: // �萔


public: // �ÓI�����o�֐�
	/// <summary>
	/// �ÓI������
	/// </summary>
	/// <param name="device">�f�o�C�X</param>
	/// <param name="camera">�J����</param>
	static void StaticInitialize(ID3D12Device* device, Camera* camera = nullptr);

	/// <summary>
	/// �O���t�B�b�N�p�C�v���C���̐���
	/// </summary>
	static void CreateGraphicsPipeline();

	/// <summary>
	/// �J�����̃Z�b�g
	/// </summary>
	/// <param name="camera">�J����</param>
	static void SetCamera(Camera* camera) { sCamera_ = camera; }

	/// <summary>
	/// �`��O����
	/// </summary>
	/// <param name="commandList">�`��R�}���h���X�g</param>
	static void PreDraw(ID3D12GraphicsCommandList* commandList);

	/// <summary>
	/// �`��㏈��
	/// </summary>
	static void PostDraw();

	/// <summary>
	/// 3D�I�u�W�F�N�g����
	/// </summary>
	/// <returns></returns>
	static Object3d* Create();

private: // �ÓI�����o�ϐ�
	// �f�o�C�X
	static ID3D12Device* device_;
	// �R�}���h���X�g
	static ID3D12GraphicsCommandList* sCommandList;
	// �e�N�X�`������p�p�C�v���C��
	static PipelineSet pipelineSet;
	// �J����
	static Camera* sCamera_;

public: // �����o�֐�
	bool Initialize();
	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	void UpdateMatrix();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();



	/// <summary>
	/// ���W�̎擾
	/// </summary>
	/// <returns>���W</returns>
	const Vector3& GetPosition() { return worldTransform.translation_; }

	/// <summary>
	/// ��]�p�̎擾
	/// </summary>
	/// <returns></returns>
	const Vector3& GetRotation() { return rotation_; }

	/// <summary>
	/// ���W�̐ݒ�
	/// </summary>
	/// <param name="position">���W</param>
	void SetPosition(Vector3 position) { worldTransform.translation_ = position; }

	void SetRotation(Vector3 rotation) { worldTransform.rotation_ = rotation; }

	/// <summary>
	/// �X�P�[���̐ݒ�
	/// </summary>
	/// <param name="position">�X�P�[��</param>
	void SetScale(Vector3 scale) { worldTransform.scale_ = scale; }

	/// <summary>
	/// ���[���h�s��̎擾
	/// </summary>
	/// <returns>���[���h�s��</returns>
	const Matrix4& GetMatWorld() { return worldTransform.matWorld_; }

	/// <summary>
	/// ���f���̃Z�b�g
	/// </summary>
	/// <param name="model">���f��</param>
	void SetModel(Model* model) { model_ = model; }

	void SetBillboard(bool isBillboard) { isBillboard_ = isBillboard; }

	static void SetLight(Light* light)
	{
		light_ = light;
	}

	void SetColor(Vector4 color) { color_ = color; }

	WorldTransform GetWorldTransform() { return worldTransform; }
	WorldTransform* GetWorldTransformPtr() { return &worldTransform; }

	Camera* GetCamera() { return sCamera_; }

private: // �����o�ϐ�
	
	// �萔�o�b�t�@�փf�[�^�]��
	ConstBufferDataB0* constMap = nullptr;

	ComPtr<ID3D12Resource> constBuffB0; // �萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuffCameraPosition; // �萔�o�b�t�@

	// �e�I�u�W�F�N�g
	Object3d* parent = nullptr;
	// ���f��
	Model* model_ = nullptr;
	// �r���{�[�h
	bool isBillboard_ = false;

	//���C�g
	static Light* light_;
public:

	//���[���h�s��
	WorldTransform worldTransform;

	// �F
	Vector4 color_ = { 1,1,1,1 };
	// ���[�J���X�P�[��
	Vector3 scale_ = { 1,1,1 };
	// X,Y,Z�����̃��[�J����]�p
	Vector3 rotation_ = { 0,0,0 };
	// ���[�J�����W
	Vector3 position_ = { 0,0,0 };
	// ���[�J�����[���h�ϊ��s��
	XMMATRIX matWorld;
	



};

