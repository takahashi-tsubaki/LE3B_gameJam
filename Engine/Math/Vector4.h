#pragma once

#include <DirectXMath.h>

class Vector4
{
public:
	float x;
	float y;
	float z;
	float w;
public:
	//�R���X�g���N�^
	Vector4();								//��x�N�g���Ƃ���
	Vector4(float x, float y, float z, float w);		//x����,y����,z���� ���w�肵�Đ���

	//�����o�֐�
	float length() const;					//�m����(����)�����߂�
	Vector4& normalize();					//���K������
	float dot(const Vector4& v) const;		//���ς����߂�
	Vector4 cross(const Vector4& v) const;	//�O�ς����߂�

	Vector4 XMVECToVec4(DirectX::XMVECTOR XMVEC);
	DirectX::XMVECTOR Vec4ToXMVEC(Vector4 Vec4);
	//�P�����Z�q�I�[�o�[���[�h
	Vector4 operator+() const;
	Vector4 operator-() const;

	//������Z�q�I�[�o�[���[�h
	Vector4& operator+=(const Vector4& v);
	Vector4& operator-=(const Vector4& v);
	Vector4& operator*=(float s);
	Vector4& operator/=(float s);

};


//�@2�����Z�q�I�[�o�[���[�h
//�@���낢��Ȉ����̃p�^�[���ɑΉ�(�����̏���)���邽�߁A�ȉ��̂悤�ɏ������Ă���
const Vector4 operator+(const Vector4& v1, const Vector4& v2);
const Vector4 operator-(const Vector4& v1, const Vector4& v2);
const Vector4 operator*(const Vector4& v, float s);
const Vector4 operator*(float s, const Vector4& v);
const Vector4 operator/(const Vector4& v, float s);