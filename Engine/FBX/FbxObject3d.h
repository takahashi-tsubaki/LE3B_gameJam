#pragma once
#include "ErrorException.h"
#include "FbxLoader.h"
#include "FbxModel.h"
#include "Camera.h"

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include<DirectXMath.h>
#include <string>

#include "worldTransform.h"

class FbxObject3d
{
public:
	//�{�[���̍ő吔
	static const int MAX_BONES = 1000;//HLSL�������킹��


	WorldTransform worldTransform;

protected://�G�C���A�X
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public://�T�u�N���X
	//�萔�o�b�t�@�p�f�[�^�\����(���W�ϊ��s��p)
	struct ConstBufferDataTransfrom
	{
		Matrix4 viewproj;
		Matrix4 world;
		Vector3 cameraPos;
		Vector4 color;
	};
	struct ConstBufferDataSkin
	{
		XMMATRIX bones[MAX_BONES];
	};
public://��I�����o�֐�
	//setter
	static void SetDevice(ID3D12Device* device) { device_ = device; }
	static void SetCamera(Camera* camera) { camera_ = camera; }

	static void CreateGraphicsPipeline();

private://��I�����o�ϐ�
	//�f�o�C�X
	static ID3D12Device* device_;
	//�J����
	static Camera* camera_;

	static ComPtr<ID3D12RootSignature>rootsignature;
	//�p�C�v���C���X�e�[�g
	static ComPtr<ID3D12PipelineState> pipelineState;

public://�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();
	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// ���f���̃Z�b�g
	/// </summary>
	/// <param name="fbxModel"></param>
	void SetModel(FbxModel* fbxModel) { fbxModel_ = fbxModel; }

	void SetScale(Vector3 scale) { worldTransform.scale_ = scale;}

	void SetPosition(Vector3 position) { worldTransform.translation_ = position; }
	/// <summary>
	/// �{�[���p
	/// </summary>
	std::vector<Matrix4> bonesMat;
	void ResizeBonesMat(std::vector<FbxModel::Bone> bones);	//�{�[���̃T�C�Y���N���X�^�[�{�[���ɍ��킹��
	bool isBonesWorldMatCalc = false;	//�{�[���̃��[���h���W��ł̌v�Z�����邩�ǂ���
	std::vector<Matrix4>* GetBonesMatPtr();	//�{�[���̃��[���h�s��|�C���^��n��
	void SetIsBonesWorldMatCalc(bool isCalc);	//�{�[���v�Z�t���O�̃Z�b�^�[
	/// <summary>
	/// �A�j���[�V�����J�n
	/// </summary>
	void PlayAnimetion(int AnimNum);


	Vector3 GetPosition() { return worldTransform.translation_; }

	void SetColor(Vector4 color) { color_ = color; }

public:
	//�萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuffTransform;

	//�萔�o�b�t�@(�X�L��)
	ComPtr<ID3D12Resource> constBuffSkin;

	Vector4 color_ = { 1,1,1,1 };

	// ���[�J���X�P�[��
	Vector3 scale_ = { 1,1,1 };
	// X,Y,Z�����̃��[�J����]�p
	Vector3 rotation = { 0,0,0 };
	// ���[�J�����W
	Vector3 position_ = { 0,0,0 };
	// ���[�J�����[���h�ϊ��s��
	Matrix4 matWorld;

	FbxModel* fbxModel_ = nullptr;

	//1�t���[���̎���
	FbxTime frameTime;
	//�A�j���[�V�����J�n����
	FbxTime startTime;
	//�A�j���[�V�����I������
	FbxTime endTime;
	//���ݎ���
	FbxTime currentTime;
	//�A�j���[�V�����Đ���
	bool isPlay = false;

};