#pragma once

#include "Vector3.h"

// �s��
class Matrix4 {
public:
	//      �s ��
	float m[4][4];

	// �R���X�g���N�^
	Matrix4();
	// �������w�肵�Ă̐���
	Matrix4(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33);

	static Matrix4 MakeIdentity()
	{
		Matrix4 mat;
		return mat;
	}

	// �P�ʍs������߂�
	Matrix4 identity();

	//�g��k���s��̐ݒ�
	Matrix4 scale(const Vector3& s);

	// ��]�s��̐ݒ�
	Matrix4 rotateX(float angle);
	Matrix4 rotateY(float angle);
	Matrix4 rotateZ(float angle);

	// ���s�ړ��s��̍쐬
	Matrix4 translate(const Vector3& t);

	// ���W�ϊ��i�x�N�g���ƍs��̊|���Z������j
	Vector3 transform(const Vector3& v, const Matrix4& m);

	// Vector3�ŃQ�b�g
	Vector3 GetWorldPos();

	//// pos��ptr
	//Vector3* GetWorldPosPtr();

	// ������Z�q�I�[�o�[���[�h
	Matrix4& operator*=(const Matrix4& m2);
	Matrix4 operator*(const Matrix4& m1);
};

// 2�����Z�q�I�[�o�[���[�h
const Vector3 operator*(const Vector3& v, const Matrix4& m);

// 2�����Z�q�I�[�o�[���[�h
const Matrix4 operator*(const Matrix4& m1, const Matrix4& m2);