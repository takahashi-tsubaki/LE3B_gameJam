#pragma once

#include <DirectXMath.h>

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"

namespace MyMath {

	const float PI = 3.141592654f;
	// �x���@->���W�A���ϊ�
	float Dig2Rad(float value);
	// ���W�A��->�x���@�ϊ� 
	float Rad2Dig(float value);

	// �m����(����)�����߂�
	float Vector2Length(const Vector2& v);

	// ��x�N�g����Ԃ�
	const Vector3 Vector3Zero();
	// 2�x�N�g������v���Ă��邩���ׂ�
	bool Vector3Equal(const Vector3& v1, const Vector3& v2);
	// �m����(����)�����߂�
	float Vector3Length(const Vector3& v);
	// ���K������
	Vector3& Vector3Normalize(Vector3& v);
	// ���ς����߂�
	float Vector3Dot(const Vector3& v1, const Vector3& v2);
	// �O�ς����߂�
	Vector3 Vector3Cross(const Vector3& v1, const Vector3& v2);

	// �P�ʍs������߂�
	Matrix4 Matrix4Identity();
	// �]�u�s������߂�
	Matrix4 Matrix4Transpose(const Matrix4& m);
	// �t�s������߂�
	Matrix4 Matrix4Inverse(const Matrix4& m, float* det = nullptr);

	// �g��k���s��̍쐬
	Matrix4 Matrix4Scaling(float sx, float sy, float sz);

	// ��]�s��̍쐬
	Matrix4 Matrix4RotationX(float angle);
	Matrix4 Matrix4RotationY(float angle);
	Matrix4 Matrix4RotationZ(float angle);

	// ���s�ړ��s��̍쐬
	Matrix4 Matrix4Translation(float tx, float ty, float tz);

	// �r���[�s��̍쐬
	Matrix4 Matrix4LookAtLH(const Vector3& eye, const Vector3& target, const Vector3& up);
	// ���s���e�s��̍쐬
	Matrix4 Matrix4Orthographic(
		float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ);
	// �������e�s��̍쐬
	Matrix4 Matrix4Perspective(float fovAngleY, float aspectRatio, float nearZ, float farZ);

	// ���W�ϊ��iw���Z�Ȃ��j
	Vector3 Vector3Transform(const Vector3& v, const Matrix4& m);
	// ���W�ϊ��iw���Z����j
	Vector3 Vector3TransformCoord(const Vector3& v, const Matrix4& m);
	// �x�N�g���ϊ�
	Vector3 Vector3TransformNormal(const Vector3& v, const Matrix4& m);

	// 2�����Z�q�I�[�o�[���[�h
	Matrix4 operator*(const Matrix4& m1, const Matrix4& m2);
	Vector3 operator*(const Vector3& v, const Matrix4& m);

	// ���`���
	float Lerp(float a, float b, float t);

	Matrix4 Initialize();
	Matrix4 Scale(Vector3 scale);
	Matrix4 Rotate(Vector3 rotation, int X_1_Y_2_Z_3_XYZ_6);
	Matrix4 Move(Vector3 move);
	//void  affin(WorldTransform& affin);

	Vector3 MatVector(const Vector3 vector3, const Matrix4 matrix4);

	Vector3 GetWorldtransform(const Matrix4 matrix4);

	Vector3 AddVector(const Vector3 v1, const Vector3 v2);

	Vector3 bVelocity(Vector3& velocity, Matrix4& mat);

	//���W�ϊ�
	Vector3 wDivision(const Vector3& v, const Matrix4& m);

	float FieldOfViewY(float focalLengs, float sensor);

	Matrix4 ConvertXMMATtoMat4(DirectX::XMMATRIX XMMatrix);
	DirectX::XMMATRIX ConvertMat4toXMMat(Matrix4 m);

	Matrix4 MakeInverse(const Matrix4* mat);

	
} // namespace MathUtility