#include "MyMath.h"
#include <cassert>
#include <cmath>

namespace MyMath
{

	float Dig2Rad(float dig)
	{
		float rad;

		rad = dig * (PI / 180);

		return rad;
	}

	float Rad2Dig(float rad)
	{
		float deg;

		deg = rad * (180 / PI);

		return deg;
	}
	float Vector2Length(const Vector2& v) {
		return (float)std::sqrt(v.x * v.x + v.y * v.y);
	}

	const Vector3 Vector3Zero() {
		static const Vector3 result{ 0.0f, 0.0f, 0.0f };

		return result;
	}

	bool Vector3Equal(const Vector3& v1, const Vector3& v2) {
		return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
	}

	float Vector3Length(const Vector3& v) {
		return (float)std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	}

	Vector3& Vector3Normalize(Vector3& v) {
		float len = Vector3Length(v);
		if (len != 0) {
			return v /= len;
		}
		return v;
	}

	float Vector3Dot(const Vector3& v1, const Vector3& v2) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	Vector3 Vector3Cross(const Vector3& v1, const Vector3& v2) {
		Vector3 temp;
		temp.x = v1.y * v2.z - v1.z * v2.y;
		temp.y = v1.z * v2.x - v1.x * v2.z;
		temp.z = v1.x * v2.y - v1.y * v2.x;
		return temp;
	}

	//// 2項演算子オーバーロード
	//const Vector3 operator+(const Vector3& v1, const Vector3& v2) {
	//	Vector3 temp(v1);
	//	return temp += v2;
	//}

	//const Vector3 operator-(const Vector3& v1, const Vector3& v2) {
	//	Vector3 temp(v1);
	//	return temp -= v2;
	//}

	//const Vector3 operator*(const Vector3& v, float s) {
	//	Vector3 temp(v);
	//	return temp *= s;
	//}

	//const Vector3 operator*(float s, const Vector3& v) { return v * s; }

	//const Vector3 operator/(const Vector3& v, float s) {
	//	Vector3 temp(v);
	//	return temp /= s;
	//}

	// 単位行列を求める
	Matrix4 Matrix4Identity() {
		static const Matrix4 result{ 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
									0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

		return result;
	}

	Matrix4 Matrix4Transpose(const Matrix4& m) {
		Matrix4 result;

		for (size_t i = 0; i < 4; i++) {
			for (size_t j = 0; j < 4; j++) {
				result.m[i][j] = m.m[j][i];
			}
		}

		return result;
	}

	float Matrix4Determinant(const Matrix4& m) {

		float det = +m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]
			+ m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]
			+ m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]

			- m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]
			- m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]
			- m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]

			- m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]
			- m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]
			- m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]

			+ m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]
			+ m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]
			+ m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]

			+ m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]
			+ m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]
			+ m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]

			- m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]
			- m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]
			- m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]

			- m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]
			- m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]
			- m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]

			+ m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]
			+ m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]
			+ m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0];
		return det;
	}

	Matrix4 Matrix4Inverse(const Matrix4& m, float* pdet) {

		// 行列式を得る
		float det = Matrix4Determinant(m);
		if (pdet) {
			*pdet = det;
		}

		assert(std::abs(det) < 1.0e-10 && "Determinant is nearly equal to zero");

		float divDet = 1.0f / det;

		Matrix4 result;

		result.m[0][0] =
			divDet * (m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][1] +
				m.m[1][3] * m.m[2][1] * m.m[3][2] - m.m[1][3] * m.m[2][2] * m.m[3][1] -
				m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[1][1] * m.m[2][3] * m.m[3][2]);

		result.m[0][1] =
			divDet * (-m.m[0][1] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[2][3] * m.m[3][1] -
				m.m[0][3] * m.m[2][1] * m.m[3][2] + m.m[0][3] * m.m[2][2] * m.m[3][1] +
				m.m[0][2] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[2][3] * m.m[3][2]);

		result.m[0][2] =
			divDet * (m.m[0][1] * m.m[1][2] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[3][1] +
				m.m[0][3] * m.m[1][1] * m.m[3][2] - m.m[0][3] * m.m[1][2] * m.m[3][1] -
				m.m[0][2] * m.m[1][1] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[3][2]);

		result.m[0][3] =
			divDet * (-m.m[0][1] * m.m[1][2] * m.m[2][3] - m.m[0][2] * m.m[1][3] * m.m[2][1] -
				m.m[0][3] * m.m[1][1] * m.m[2][2] + m.m[0][3] * m.m[1][2] * m.m[2][1] +
				m.m[0][2] * m.m[1][1] * m.m[2][3] + m.m[0][1] * m.m[1][3] * m.m[2][2]);

		result.m[1][0] =
			divDet * (-m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[1][2] * m.m[2][3] * m.m[3][0] -
				m.m[1][3] * m.m[2][0] * m.m[3][2] + m.m[1][3] * m.m[2][2] * m.m[3][0] +
				m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[1][0] * m.m[2][3] * m.m[3][2]);

		result.m[1][1] =
			divDet * (m.m[0][0] * m.m[2][2] * m.m[3][3] + m.m[0][2] * m.m[2][3] * m.m[3][0] +
				m.m[0][3] * m.m[2][0] * m.m[3][2] - m.m[0][3] * m.m[2][2] * m.m[3][0] -
				m.m[0][2] * m.m[2][0] * m.m[3][3] - m.m[0][0] * m.m[2][3] * m.m[3][2]);

		result.m[1][2] =
			divDet * (-m.m[0][0] * m.m[1][2] * m.m[3][3] - m.m[0][2] * m.m[1][3] * m.m[3][0] -
				m.m[0][3] * m.m[1][0] * m.m[3][2] + m.m[0][3] * m.m[1][2] * m.m[3][0] +
				m.m[0][2] * m.m[1][0] * m.m[3][3] + m.m[0][0] * m.m[1][3] * m.m[3][2]);

		result.m[1][3] =
			divDet * (m.m[0][0] * m.m[1][2] * m.m[2][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] +
				m.m[0][3] * m.m[1][0] * m.m[2][2] - m.m[0][3] * m.m[1][2] * m.m[2][0] -
				m.m[0][2] * m.m[1][0] * m.m[2][3] - m.m[0][0] * m.m[1][3] * m.m[2][2]);

		result.m[2][0] =
			divDet * (m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][3] * m.m[3][0] +
				m.m[1][3] * m.m[2][0] * m.m[3][1] - m.m[1][3] * m.m[2][1] * m.m[3][0] -
				m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[1][0] * m.m[2][3] * m.m[3][1]);

		result.m[2][1] =
			divDet * (-m.m[0][0] * m.m[2][1] * m.m[3][3] - m.m[0][1] * m.m[2][3] * m.m[3][0] -
				m.m[0][3] * m.m[2][0] * m.m[3][1] + m.m[0][3] * m.m[2][1] * m.m[3][0] +
				m.m[0][1] * m.m[2][0] * m.m[3][3] + m.m[0][0] * m.m[2][3] * m.m[3][1]);

		result.m[2][2] =
			divDet * (m.m[0][0] * m.m[1][1] * m.m[3][3] + m.m[0][1] * m.m[1][3] * m.m[3][0] +
				m.m[0][3] * m.m[1][0] * m.m[3][1] - m.m[0][3] * m.m[1][1] * m.m[3][0] -
				m.m[0][1] * m.m[1][0] * m.m[3][3] - m.m[0][0] * m.m[1][3] * m.m[3][1]);

		result.m[2][3] =
			divDet * (-m.m[0][0] * m.m[1][1] * m.m[2][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] -
				m.m[0][3] * m.m[1][0] * m.m[2][1] + m.m[0][3] * m.m[1][1] * m.m[2][0] +
				m.m[0][1] * m.m[1][0] * m.m[2][3] + m.m[0][0] * m.m[1][3] * m.m[2][1]);

		result.m[3][0] =
			divDet * (-m.m[1][0] * m.m[2][1] * m.m[3][2] - m.m[1][1] * m.m[2][2] * m.m[3][0] -
				m.m[1][2] * m.m[2][0] * m.m[3][1] + m.m[1][2] * m.m[2][1] * m.m[3][0] +
				m.m[1][1] * m.m[2][0] * m.m[3][2] + m.m[1][0] * m.m[2][2] * m.m[3][1]);

		result.m[3][1] =
			divDet * (m.m[0][0] * m.m[2][1] * m.m[3][2] + m.m[0][1] * m.m[2][2] * m.m[3][0] +
				m.m[0][2] * m.m[2][0] * m.m[3][1] - m.m[0][2] * m.m[2][1] * m.m[3][0] -
				m.m[0][1] * m.m[2][0] * m.m[3][2] - m.m[0][0] * m.m[2][2] * m.m[3][1]);

		result.m[3][2] =
			divDet * (-m.m[0][0] * m.m[1][1] * m.m[3][2] - m.m[0][1] * m.m[1][2] * m.m[3][0] -
				m.m[0][2] * m.m[1][0] * m.m[3][1] + m.m[0][2] * m.m[1][1] * m.m[3][0] +
				m.m[0][1] * m.m[1][0] * m.m[3][2] + m.m[0][0] * m.m[1][2] * m.m[3][1]);

		result.m[3][3] =
			divDet * (m.m[0][0] * m.m[1][1] * m.m[2][2] + m.m[0][1] * m.m[1][2] * m.m[2][0] +
				m.m[0][2] * m.m[1][0] * m.m[2][1] - m.m[0][2] * m.m[1][1] * m.m[2][0] -
				m.m[0][1] * m.m[1][0] * m.m[2][2] - m.m[0][0] * m.m[1][2] * m.m[2][1]);

		return result;
	}

	Matrix4 Matrix4Scaling(float sx, float sy, float sz) {
		Matrix4 result{ sx,   0.0f, 0.0f, 0.0f, 0.0f, sy,   0.0f, 0.0f,
					   0.0f, 0.0f, sz,   0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

		return result;
	}

	Matrix4 Matrix4RotationX(float angle) {
		float sin = std::sin(angle);
		float cos = std::cos(angle);

		Matrix4 result{ 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, cos,  sin,  0.0f,
					   0.0f, -sin, cos,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

		return result;
	}

	Matrix4 Matrix4RotationY(float angle) {
		float sin = std::sin(angle);
		float cos = std::cos(angle);

		Matrix4 result{ cos, 0.0f, -sin, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
					   sin, 0.0f, cos,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

		return result;
	}

	Matrix4 Matrix4RotationZ(float angle) {
		float sin = std::sin(angle);
		float cos = std::cos(angle);

		Matrix4 result{ cos,  sin,  0.0f, 0.0f, -sin, cos,  0.0f, 0.0f,
					   0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

		return result;
	}

	Matrix4 Matrix4Translation(float tx, float ty, float tz) {
		Matrix4 result{ 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
					   0.0f, 0.0f, 1.0f, 0.0f, tx,   ty,   tz,   1.0f };

		return result;
	}

	Matrix4 Matrix4LookAtLH(const Vector3& eye, const Vector3& target, const Vector3& up) {
		assert(!Vector3Equal(eye, target));
		assert(!Vector3Equal(up, Vector3Zero()));

		// 視線方向
		Vector3 eyeDirection = target - eye;

		// 各軸ベクトルを算出
		Vector3 R2 = Vector3Normalize(eyeDirection);

		Vector3 R0 = Vector3Cross(up, R2);
		R0 = Vector3Normalize(R0);

		Vector3 R1 = Vector3Cross(R2, R0);

		// 平行移動成分を算出
		Vector3 NegEyePosition = -eye;

		float D0 = Vector3Dot(R0, NegEyePosition);
		float D1 = Vector3Dot(R1, NegEyePosition);
		float D2 = Vector3Dot(R2, NegEyePosition);

		Matrix4 m{ R0.x, R1.x, R2.x, 0.0f, R0.y, R1.y, R2.y, 0.0f,
				  R0.z, R1.z, R2.z, 0.0f, D0,   D1,   D2,   1.0f };

		return m;
	}

	Matrix4 Matrix4Orthographic(
		float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ) {
		assert(fabsf(viewRight - viewLeft) > 0.00001f);
		assert(fabsf(viewTop - viewBottom) > 0.00001f);
		assert(fabsf(farZ - nearZ) > 0.00001f);

		float width = 1.0f / (viewRight - viewLeft);
		float height = 1.0f / (viewTop - viewBottom);
		float fRange = 1.0f / (farZ - nearZ);
		float sx = width * 2.0f;
		float sy = height * 2.0f;
		float sz = fRange;
		float tx = -(viewLeft + viewRight) * width;
		float ty = -(viewTop + viewBottom) * height;
		float tz = -fRange * nearZ;

		Matrix4 m{ sx, 0.0f, 0.0f, 0.0f, 0.0f, sy, 0.0f, 0.0f, 0.0f, 0.0f, sz, 0.0f, tx, ty, tz, 1.0f };

		return m;
	}

	Matrix4 Matrix4Perspective(float fovAngleY, float aspectRatio, float nearZ, float farZ) {
		assert(nearZ > 0.0f && farZ > 0.f);
		assert(fabsf(fovAngleY) > 0.00001f * 2.0f);
		assert(fabsf(aspectRatio) > 0.00001f);
		assert(fabsf(farZ - nearZ) > 0.00001f);

		float sinFov = std::sin(0.5f * fovAngleY);
		float cosFov = std::cos(0.5f * fovAngleY);

		float height = cosFov / sinFov;
		float width = height / aspectRatio;
		float fRange = farZ / (farZ - nearZ);

		Matrix4 m{ width, 0.0f,   0.0f, 0.0f, 0.0f, height,          0.0f, 0.0f, 0.0f,
				  0.0f,  fRange, 1.0f, 0.0f, 0.0f, -fRange * nearZ, 0.0f };

		return m;
	}

	Vector3 Vector3Transform(const Vector3& v, const Matrix4& m) {

		Vector3 result{
		  v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + m.m[3][0],
		  v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + m.m[3][1],
		  v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + m.m[3][2] };

		return result;
	}

	Vector3 Vector3TransformCoord(const Vector3& v, const Matrix4& m) {
		float w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + m.m[3][3];

		Vector3 result{
		  (v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + m.m[3][0]) / w,
		  (v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + m.m[3][1]) / w,
		  (v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + m.m[3][2]) / w };

		return result;
	}

	Vector3 Vector3TransformNormal(const Vector3& v, const Matrix4& m) {

		Vector3 result{
		  v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0],
		  v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1],
		  v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] };

		return result;
	}

	Matrix4 operator*(const Matrix4& m1, const Matrix4& m2) {
		Matrix4 result = m1;

		return result *= m2;
	}

	Vector3 operator*(const Vector3& v, const Matrix4& m) { return Vector3Transform(v, m); }

	float Lerp(float a, float b, float t) { return a + t * (b - a); }

	Matrix4 Initialize()
	{
		Matrix4 matInitialize = {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};

		return matInitialize;
	}

	Matrix4 Scale(Vector3 scale)
	{
		//スケーリング行列を宣言
		Matrix4 matScale = {
			scale.x, 0.0f, 0.0f,    0.0f,
			0.0f, scale.y, 0.0f, 0.0f,
			0.0f,    0.0f, scale.z, 0.0f,
			0.0f, 0.0f,    0.0f, 1.0f
		};

		Matrix4 scaling = Initialize();
		scaling *= matScale;

		return scaling;
	}

	Matrix4 Rotate(Vector3 rotation, int X_1_Y_2_Z_3_XYZ_6)
	{
		int rotationX = 1;
		int rotationY = 2;
		int rotationZ = 3;
		/*int rotationXYZ = 6;*/

		if (X_1_Y_2_Z_3_XYZ_6 == rotationX) {
			Matrix4 matRotX = {
			  1.0f,0.0f,0.0f,0.0f,
			  0.0f,cos(rotation.x),sin(rotation.x),0.0f,
			  0.0f,-sin(rotation.x),cos(rotation.x),0.0f,
			  0.0f,0.0f,0.0f,1.0f
			};
			Matrix4 rotationX_ = Initialize();
			rotationX_ *= matRotX;

			return rotationX_;
		}
		else if (X_1_Y_2_Z_3_XYZ_6 == rotationY) {
			Matrix4 matRotY = {
				cos(rotation.y), 0.0f, -sin(rotation.y), 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				sin(rotation.y), 0.0f, cos(rotation.y),  0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			};
			Matrix4 rotationY_ = Initialize();
			rotationY_ *= matRotY;

			return rotationY_;
		}
		else if (X_1_Y_2_Z_3_XYZ_6 == rotationZ) {
			Matrix4 matRotZ = {
			  cos(rotation.z),sin(rotation.z),0.0f,0.0f,
			  -sin(rotation.z),cos(rotation.z),0.0f,0.0f,
			  0.0f,0.0f,1.0f,0.0f,
			  0.0f,0.0f,0.0f,1.0f
			};
			Matrix4 rotationZ_ = Initialize();
			rotationZ_ *= matRotZ;

			return rotationZ_;
		}
		else {
			Matrix4 matRotXYZ;
			Matrix4 matRot_X, matRot_Y, matRot_Z;
			matRot_X = {
			  1.0f,0.0f,0.0f,0.0f,
			  0.0f,cos(rotation.x),sin(rotation.x),0.0f,
			  0.0f,-sin(rotation.x),cos(rotation.x),0.0f,
			  0.0f,0.0f,0.0f,1.0f
			};
			matRot_Y = {
				cos(rotation.y), 0.0f, -sin(rotation.y),
				0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
				sin(rotation.y), 0.0f, cos(rotation.y),
				0.0f, 0.0f, 0.0f, 0.0f, 1.0f
			};
			matRot_Z = {
			  cos(rotation.z),sin(rotation.z),0.0f,0.0f,
			  -sin(rotation.z),cos(rotation.z),0.0f,0.0f,
			  0.0f,0.0f,1.0f,0.0f,
			  0.0f,0.0f,0.0f,1.0f
			};
			//各軸の回転行列を合成
			matRotXYZ = Initialize();

			matRotXYZ *= matRot_X;
			matRotXYZ *= matRot_Y;
			matRotXYZ *= matRot_Z;

			return matRotXYZ;
		}
	}

	Matrix4 Move(Vector3 move)
	{
		Matrix4 matMove = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		move.x, move.y, move.z, 1.0f
		};

		return matMove;
	}

	Vector3 MatVector(const Vector3 vector3, const Matrix4 matrix4)
	{
		Vector3 retVec = {};

		retVec.x =
			vector3.x * matrix4.m[0][0] + vector3.y * matrix4.m[1][0] + vector3.z * matrix4.m[2][0];

		retVec.y =
			vector3.x * matrix4.m[0][1] + vector3.y * matrix4.m[1][1] + vector3.z * matrix4.m[2][1];

		retVec.z =
			vector3.x * matrix4.m[0][2] + vector3.y * matrix4.m[1][2] + vector3.z * matrix4.m[2][2];

		return retVec;
	}

	Vector3 GetWorldtransform(const Matrix4 matrix4)
	{
		//ワールド座標を入れる変数
		Vector3 worldPos;
		//ワールド行列の平行移動成分
		worldPos.x = matrix4.m[3][0];
		worldPos.y = matrix4.m[3][1];
		worldPos.z = matrix4.m[3][2];

		return worldPos;
	}

	Vector3 AddVector(const Vector3 v1, const Vector3 v2)
	{
		Vector3 addVec = {};

		addVec.x = v1.x + v2.x;

		addVec.y = v1.y + v2.y;

		addVec.z = v1.z + v2.z;

		return addVec;

	}

	Vector3 bVelocity(Vector3& velocity, Matrix4& mat)
	{
		Vector3 result = { 0, 0, 0 };


		result.x = velocity.x * mat.m[0][0] +
			velocity.y * mat.m[1][0] +
			velocity.z * mat.m[2][0];

		result.y = velocity.x * mat.m[0][1] +
			velocity.y * mat.m[1][1] +
			velocity.z * mat.m[2][1];

		result.z = velocity.x * mat.m[0][2] +
			velocity.y * mat.m[1][2] +
			velocity.z * mat.m[2][2];


		return result;
	}

	Vector3 wDivision(const Vector3& v, const Matrix4& m)
	{
		Vector4 divVec = {};

		divVec.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + 1 * m.m[3][0];

		divVec.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + 1 * m.m[3][1];

		divVec.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + 1 * m.m[3][2];

		divVec.w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + 1 * m.m[3][3];

		divVec.x = divVec.x / divVec.w;

		divVec.y = divVec.y / divVec.w;

		divVec.z = divVec.z / divVec.w;

		return { divVec.x, divVec.y, divVec.z };
	}

	float FieldOfViewY(float focalLengs, float sensor)
	{

		return 2 * atan(sensor / (2 * focalLengs));
	}

	Matrix4 ConvertXMMATtoMat4(DirectX::XMMATRIX XMMatrix)
	{
		Matrix4 result;
		for (int i = 0; i < 4; i++) {

			result.m[i][0] = DirectX::XMVectorGetX(XMMatrix.r[i]);
			result.m[i][1] = DirectX::XMVectorGetY(XMMatrix.r[i]);
			result.m[i][2] = DirectX::XMVectorGetZ(XMMatrix.r[i]);
			result.m[i][3] = DirectX::XMVectorGetW(XMMatrix.r[i]);
		}


		return result;
	}

	DirectX::XMMATRIX ConvertMat4toXMMat(Matrix4 m)
	{
		DirectX::XMMATRIX result;
		result = DirectX::XMMatrixSet(
			m.m[0][0], m.m[0][1], m.m[0][2], m.m[0][3],
			m.m[1][0], m.m[1][1], m.m[1][2], m.m[1][3],
			m.m[2][0], m.m[2][1], m.m[2][2], m.m[2][3],
			m.m[3][0], m.m[3][1], m.m[3][2], m.m[3][3]);

		return result;
	}

	Matrix4 MakeInverse(const Matrix4* mat)
	{
		assert(mat);

		//掃き出し法を行う行列
		float sweep[4][8]{};
		//定数倍用
		float constTimes = 0.0f;
		//許容する誤差
		float MAX_ERR = 1e-10f;
		//戻り値用
		Matrix4 retMat;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				//weepの左側に逆行列を求める行列をセット
				sweep[i][j] = mat->m[i][j];

				//sweepの右側に単位行列をセット
				sweep[i][4 + j] = Matrix4::MakeIdentity().m[i][j];
			}
		}

		//全ての列の対角成分に対する繰り返し
		for (int i = 0; i < 4; i++)
		{
			//最大の絶対値を注目対角成分の絶対値と仮定
			float max = fabs(sweep[i][i]);
			int maxIndex = i;

			//i列目が最大の絶対値となる行を探す
			for (int j = i + 1; j < 4; j++)
			{
				if (fabs(sweep[j][i]) > max)
				{
					max = fabs(sweep[j][i]);
					maxIndex = j;
				}
			}

			if (fabs(sweep[maxIndex][i]) <= MAX_ERR)
			{
				//逆行列は求められない
				return Matrix4::MakeIdentity();
			}

			//操作(1):i行目とmaxIndex行目を入れ替える
			if (i != maxIndex)
			{
				for (int j = 0; j < 8; j++)
				{
					float tmp = sweep[maxIndex][j];
					sweep[maxIndex][j] = sweep[i][j];
					sweep[i][j] = tmp;
				}
			}

			//sweep[i][i]に掛けると1になる値を求める
			constTimes = 1 / sweep[i][i];

			//操作(2):p行目をa倍する
			for (int j = 0; j < 8; j++)
			{
				//これによりsweep[i][i]が1になる
				sweep[i][j] *= constTimes;
			}

			//操作(3)によりi行目以外の行のi列目を0にする
			for (int j = 0; j < 4; j++)
			{
				if (j == i)
				{
					//i行目はそのまま
					continue;
				}

				//i行目に掛ける値を求める
				constTimes = -sweep[j][i];

				for (int k = 0; k < 8; k++)
				{
					//j行目にi行目をa倍した行を足す
					//これによりsweep[j][i]が0になる
					sweep[j][k] += sweep[i][k] * constTimes;
				}
			}
		}

		//sweepの右半分がmatの逆行列
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				retMat.m[i][j] = sweep[i][4 + j];
			}
		}

		return retMat;
	}

} // namespace MathUtility
