#pragma once
#include "Vector3.h"
#include "Matrix4.h"
#include "MyMath.h"

class WorldTransform {
public:
	WorldTransform(Vector3 scale, Vector3 rotation, Vector3 translation);
	WorldTransform() {};
	//�����o�֐�
	void initialize();

	//���[���h�ϊ��s��̍X�V
	void UpdateMatWorld();

	//�����o�ϐ�
	//�X�P�[��
	Vector3 scale_ = { 1,1,1 };
	//XYZ����]
	Vector3 rotation_ = { 0,0,0 };
	//���[�J�����W
	Vector3 translation_ = { 0,0,0 };
	//���[���h�ϊ��s��
	Matrix4 matWorld_;
	//�e�I�u�W�F�N�g�̃��[���h�ϊ��̃|�C���^
	WorldTransform* parent_ = nullptr;

};
