#pragma once
#include "Vector3.h"
#include "Matrix4.h"
#include "MyMath.h"

class WorldTransform {
public:
	WorldTransform(Vector3 scale, Vector3 rotation, Vector3 translation);
	WorldTransform() {};
	//メンバ関数
	void initialize();

	//ワールド変換行列の更新
	void UpdateMatWorld();

	//メンバ変数
	//スケール
	Vector3 scale_ = { 1,1,1 };
	//XYZ軸回転
	Vector3 rotation_ = { 0,0,0 };
	//ローカル座標
	Vector3 translation_ = { 0,0,0 };
	//ワールド変換行列
	Matrix4 matWorld_;
	//親オブジェクトのワールド変換のポインタ
	WorldTransform* parent_ = nullptr;

};
