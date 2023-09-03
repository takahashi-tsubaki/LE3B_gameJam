#pragma once

#include "Mesh.h"
#include <string>
#include <unordered_map>
#include <vector>

/// <summary>
/// ���f���f�[�^
/// </summary>
class Model {
private: // �G�C���A�X
  // Microsoft::WRL::���ȗ�
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private:
	static const std::string baseDirectory;

private: // �ÓI�����o�ϐ�
  // �f�o�C�X
	static ID3D12Device* device_;
	// �f�X�N���v�^�T�C�Y
	static UINT descriptorHandleIncrementSize;

public: // �ÓI�����o�֐�
  /// <summary>
  /// �ÓI������
  /// </summary>
  /// <param name="device">�f�o�C�X</param>
	static void StaticInitialize(ID3D12Device* device);

	/// <summary>
	/// OBJ�t�@�C�����烁�b�V������
	/// </summary>
	/// <param name="modelname">���f����</param>
	/// <returns>�������ꂽ���f��</returns>
	/*static Model* CreateFromOBJ(const std::string& modelname);*/
	static Model* CreateFromOBJ(const std::string& modelname, bool smoothing = false);


public: // �����o�֐�
  /// <summary>
  /// �f�X�g���N�^
  /// </summary>
	~Model();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="modelname">���f����</param>
	void Initialize(const std::string& modelname, bool smoothing);

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="cmdList">���ߔ��s��R�}���h���X�g</param>
	void Draw(ID3D12GraphicsCommandList* cmdList);

private: // �����o�ϐ�
  // ���O
	std::string name;
	// ���b�V���R���e�i
	std::vector<Mesh*> meshes;
	// �}�e���A���R���e�i
	std::unordered_map<std::string, Material*> materials;
	// �f�t�H���g�}�e���A��
	Material* defaultMaterial = nullptr;
	// �f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> descHeap;

private: // �����o�֐�
  /// <summary>
  /// �}�e���A���ǂݍ���
  /// </summary>
	void LoadMaterial(const std::string& directoryPath, const std::string& filename);

	/// <summary>
	/// �}�e���A���o�^
	/// </summary>
	void AddMaterial(Material* material);

	/// <summary>
	/// �f�X�N���v�^�q�[�v�̐���
	/// </summary>
	void CreateDescriptorHeap();

	/// <summary>
	/// �e�N�X�`���ǂݍ���
	/// </summary>
	void LoadTextures();
};
