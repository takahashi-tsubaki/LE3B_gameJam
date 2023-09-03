#include "Vector4.h"

#include<cmath>  //sprt

Vector4::Vector4() :x(0), y(0), z(0), w(0)
{
}

Vector4::Vector4(float x, float y, float z, float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

float Vector4::length()const {
	return std::sqrt(x * x + y * y + z * z + w * w);
}

Vector4& Vector4::normalize() {
	float len = length();
	if (len != 0) {
		return *this /= len;
	}
	return *this;
}

float Vector4::dot(const Vector4& v) const
{
	return x * v.x + y * v.y + z * v.z + w * v.w;
}

Vector4 Vector4::cross(const Vector4& v) const
{
	return Vector4(
		y * v.z - z * v.y,
		z * v.x - x * v.z,
		x * v.y - y * v.x,
		v.w
	);
}

Vector4 Vector4::XMVECToVec4(DirectX::XMVECTOR XMVEC)
{
	Vector4 result;
	result.x = XMVEC.m128_f32[0];
	result.y = XMVEC.m128_f32[1];
	result.z = XMVEC.m128_f32[2];
	result.w = XMVEC.m128_f32[3];

	return result;
}

DirectX::XMVECTOR Vector4::Vec4ToXMVEC(Vector4 Vec4)
{
	DirectX::XMVECTOR result;
	result.m128_f32[0] = Vec4.x;
	result.m128_f32[1] = Vec4.y;
	result.m128_f32[2] = Vec4.z;
	result.m128_f32[3] = Vec4.w;

	return result;
}

Vector4 Vector4::operator+() const
{
	return Vector4(x, y, z, w);
}

Vector4 Vector4::operator-() const
{
	return Vector4(x, y, z, w);
}

Vector4& Vector4::operator+=(const Vector4& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
	return *this;
}

Vector4& Vector4::operator-=(const Vector4& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
	return *this;
}

Vector4& Vector4::operator*=(float s)
{
	x *= s;
	y *= s;
	z *= s;
	w *= s;
	return *this;
}

Vector4& Vector4::operator/=(float s)
{
	x /= s;
	y /= s;
	z /= s;
	w /= s;
	return *this;
}



const Vector4 operator+(const Vector4& v1, const Vector4& v2)
{
	Vector4 temp = v1;
	temp.x += v2.x;
	temp.y += v2.y;
	temp.z += v2.z;
	temp.w += v2.w;
	return temp;
}

const Vector4 operator-(const Vector4& v1, const Vector4& v2)
{
	Vector4 temp(v1);
	temp.x -= v2.x;
	temp.y -= v2.y;
	temp.z -= v2.z;
	temp.w -= v2.w;
	return temp;
}

const Vector4 operator*(const Vector4& v, float s)
{
	Vector4 temp(v);
	temp.x *= s;
	temp.y *= s;
	temp.z *= s;
	temp.w *= s;
	return temp;
}

const Vector4 operator*(float s, const Vector4& v)
{
	Vector4 temp;
	temp.x = v.x * s;
	temp.y = v.y * s;
	temp.z = v.z * s;
	temp.w = v.w * s;
	return temp;
}

const Vector4 operator/(const Vector4& v, float s)
{
	Vector4 temp(v);
	temp.x /= s;
	temp.y /= s;
	temp.z /= s;
	temp.w /= s;
	return temp;
}