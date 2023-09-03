#pragma once

/// <summary>
/// 2�����x�N�g��
/// </summary>
class Vector2 {
public:
	float x; // x����
	float y; // y����

public:
	// �R���X�g���N�^
	Vector2();                          // ��x�N�g���Ƃ���
	Vector2(float x, float y); // x����, y���� ���w�肵�Ă̐���

	// �P�����Z�q�I�[�o�[���[�h
	Vector2 operator+() const;
	Vector2 operator-() const;

	// ������Z�q�I�[�o�[���[�h
	Vector2& operator+=(const Vector2& v);
	Vector2& operator-=(const Vector2& v);
	Vector2& operator*=(float s);
	Vector2& operator/=(float s);
};
//�񍀉��Z�q�I�[�o�[���[�h
//�������Ȉ����i�����̕��Ə����j�̃p�^�[���ɑΉ����邽�߁A�ȉ��̂悤�ɏ������Ă���
const Vector2 operator+(const Vector2& v1, const Vector2& v2);
const Vector2 operator-(const Vector2& v1, const Vector2& v2);
const Vector2 operator*(const Vector2& v, float s);
const Vector2 operator*(float s, const Vector2& v);
const Vector2 operator/(const Vector2& v, float s);