#include "Vector2.h"

Vector2::Vector2() : x(0), y(0) {}

Vector2::Vector2(float x, float y) : x(x), y(y) {}

Vector2 Vector2::operator+() const { return *this; }

Vector2 Vector2::operator-() const { return Vector2(-x, -y); }

Vector2& Vector2::operator+=(const Vector2& v) {
	x += v.x;
	y += v.y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& v) {
	x -= v.x;
	y -= v.y;
	return *this;
}

Vector2& Vector2::operator*=(float s) {
	x *= s;
	y *= s;
	return *this;
}

Vector2& Vector2::operator/=(float s) {
	x /= s;
	y /= s;
	return *this;
}

const Vector2 operator+(const Vector2& v1, const Vector2& v2)
{
	Vector2 temp(v1);
	temp.x += v2.x;
	temp.y += v2.y;
	return temp;
}

const Vector2 operator-(const Vector2& v1, const Vector2& v2)
{
	Vector2 temp(v1);
	temp.x -= v2.x;
	temp.y -= v2.y;
	return temp;
}

const Vector2 operator*(const Vector2& v, float s)
{
	Vector2 temp(v);
	temp.x *= s;
	temp.y *= s;
	return temp;
}

const Vector2 operator*(float s, const Vector2& v)
{
	Vector2 temp;
	temp.x = s * v.x;
	temp.y = s * v.y;
	return temp;
}

const Vector2 operator/(const Vector2& v, float s)
{
	Vector2 temp(v);
	temp.x /= s;
	temp.y /= s;
	return temp;
}
