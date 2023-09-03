#pragma once

#include "Vector3.h"

// 行列
class Matrix4 {
public:
	//      行 列
	float m[4][4];

	// コンストラクタ
	Matrix4();
	// 成分を指定しての生成
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

	// 単位行列を求める
	Matrix4 identity();

	//拡大縮小行列の設定
	Matrix4 scale(const Vector3& s);

	// 回転行列の設定
	Matrix4 rotateX(float angle);
	Matrix4 rotateY(float angle);
	Matrix4 rotateZ(float angle);

	// 平行移動行列の作成
	Matrix4 translate(const Vector3& t);

	// 座標変換（ベクトルと行列の掛け算をする）
	Vector3 transform(const Vector3& v, const Matrix4& m);

	// Vector3でゲット
	Vector3 GetWorldPos();

	//// posをptr
	//Vector3* GetWorldPosPtr();

	// 代入演算子オーバーロード
	Matrix4& operator*=(const Matrix4& m2);
	Matrix4 operator*(const Matrix4& m1);
};

// 2項演算子オーバーロード
const Vector3 operator*(const Vector3& v, const Matrix4& m);

// 2項演算子オーバーロード
const Matrix4 operator*(const Matrix4& m1, const Matrix4& m2);