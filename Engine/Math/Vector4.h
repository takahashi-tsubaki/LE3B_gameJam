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
	//コンストラクタ
	Vector4();								//零ベクトルとする
	Vector4(float x, float y, float z, float w);		//x成分,y成分,z成分 を指定して生成

	//メンバ関数
	float length() const;					//ノルム(長さ)を求める
	Vector4& normalize();					//正規化する
	float dot(const Vector4& v) const;		//内積を求める
	Vector4 cross(const Vector4& v) const;	//外積を求める

	Vector4 XMVECToVec4(DirectX::XMVECTOR XMVEC);
	DirectX::XMVECTOR Vec4ToXMVEC(Vector4 Vec4);
	//単項演算子オーバーロード
	Vector4 operator+() const;
	Vector4 operator-() const;

	//代入演算子オーバーロード
	Vector4& operator+=(const Vector4& v);
	Vector4& operator-=(const Vector4& v);
	Vector4& operator*=(float s);
	Vector4& operator/=(float s);

};


//　2項演算子オーバーロード
//　いろいろな引数のパターンに対応(引数の序列)するため、以下のように準備している
const Vector4 operator+(const Vector4& v1, const Vector4& v2);
const Vector4 operator-(const Vector4& v1, const Vector4& v2);
const Vector4 operator*(const Vector4& v, float s);
const Vector4 operator*(float s, const Vector4& v);
const Vector4 operator/(const Vector4& v, float s);