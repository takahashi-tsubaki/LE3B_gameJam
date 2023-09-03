#pragma once

/// <summary>
/// 3�����x�N�g��
/// </summary>
class Vector3 {
public:
	float x; // x����
	float y; // y����
	float z; // z����

public:

	// �R���X�g���N�^
	Vector3();                          // ��x�N�g���Ƃ���
	Vector3(float x, float y, float z); // x����, y����, z���� ���w�肵�Ă̐���

	float length() const;
	Vector3& nomalize();
	float dot(const Vector3& v) const;
	Vector3 cross(const Vector3& v) const;
	Vector3 sub(const Vector3& v)const;
	const Vector3 lerp(const Vector3& start, const Vector3& end, const float t);

	// �P�����Z�q�I�[�o�[���[�h
	Vector3 operator+() const;
	Vector3 operator-() const;

	// ������Z�q�I�[�o�[���[�h
	Vector3& operator+=(const Vector3& v);
	Vector3& operator-=(const Vector3& v);
	Vector3& operator*=(float s);
	Vector3& operator/=(float s);
};

const Vector3 operator+(const Vector3& v1, const Vector3& v2);
const Vector3 operator-(const Vector3& v1, const Vector3& v2);
const Vector3 operator*(const Vector3& v, float s);
const Vector3 operator*(float s, const Vector3& v);
const Vector3 operator/(const Vector3& v, float s);