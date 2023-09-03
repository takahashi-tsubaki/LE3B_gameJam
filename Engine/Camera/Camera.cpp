#include "Camera.h"

using namespace DirectX;

Matrix4 Camera::matBillboard = MyMath::ConvertXMMATtoMat4(DirectX::XMMatrixIdentity());
Matrix4 Camera::matBillboardY = MyMath::ConvertXMMATtoMat4(DirectX::XMMatrixIdentity());


Camera::Camera(int window_width, int window_height)
{
	aspectRatio = (float)window_width / window_height;

	//ビュー行列の計算
	UpdateViewMatrix();

	// 射影行列の計算
	UpdateProjectionMatrix();

	// ビュープロジェクションの合成
	matViewProjection = matView * matProjection;
}

void Camera::Update()
{
	if (viewDirty || projectionDirty) {
		// 再計算必要なら
		if (viewDirty) {
			// ビュー行列更新
			UpdateViewMatrix();
			viewDirty = false;
		}

		// 再計算必要なら
		if (projectionDirty) {
			// ビュー行列更新
			UpdateProjectionMatrix();
			projectionDirty = false;
		}
		// ビュープロジェクションの合成
		matViewProjection = matView * matProjection;
	}

	//UpdateViewMatrix();
	//UpdateProjectionMatrix();
	//matViewProjection = matView * matProjection;
}

void Camera::UpdateViewMatrix()
{
	// 視点座標
	Vector3 eyePosition = eye_;
	// 注視点座標
	Vector3 targetPosition = target_;
	// （仮の）上方向
	Vector3 upVector =up_;

	// カメラZ軸（視線方向）
	Vector3 cameraAxisZ = targetPosition - eyePosition;

	//正規化
	cameraAxisZ.nomalize();

	// カメラのX軸（右方向）
	Vector3 cameraAxisX;
	// X軸は上方向→Z軸の外積で求まる
	cameraAxisX = upVector.cross(cameraAxisZ);
	// ベクトルを正規化
	cameraAxisX.nomalize();

	// カメラのY軸（上方向）
	Vector3 cameraAxisY;
	// Y軸はZ軸→X軸の外積で求まる
	cameraAxisY = cameraAxisZ.cross(cameraAxisX);

	// ここまでで直交した3方向のベクトルが揃う
	//（ワールド座標系でのカメラの右方向、上方向、前方向）	

	// カメラ回転行列

	Matrix4 matCameraRot;
	// カメラ座標系→ワールド座標系の変換行列
	matCameraRot.m[0][0] = cameraAxisX.x;
	matCameraRot.m[0][1] = cameraAxisX.y;
	matCameraRot.m[0][2] = cameraAxisX.z;
	matCameraRot.m[0][3] = 0;
	matCameraRot.m[1][0] = cameraAxisY.x;
	matCameraRot.m[1][1] = cameraAxisY.y;
	matCameraRot.m[1][2] = cameraAxisY.z;
	matCameraRot.m[1][3] = 0;
	matCameraRot.m[2][0] = cameraAxisZ.x;
	matCameraRot.m[2][1] = cameraAxisZ.y;
	matCameraRot.m[2][2] = cameraAxisZ.z;
	matCameraRot.m[2][3] = 0;
	matCameraRot.m[3][0] = 0;
	matCameraRot.m[3][1] = 0;
	matCameraRot.m[3][2] = 0;
	matCameraRot.m[3][3] = 1;

	// 転置により逆行列（逆回転）を計算
	matView = MyMath::ConvertXMMATtoMat4(XMMatrixTranspose(MyMath::ConvertMat4toXMMat(matCameraRot)));

	// 視点座標に-1を掛けた座標
	Vector3 reverseEyePosition = -eyePosition;
	// カメラの位置からワールド原点へのベクトル（カメラ座標系）
	float tX = cameraAxisX.dot(reverseEyePosition);	// X成分
	float tY = cameraAxisY.dot(reverseEyePosition);	// Y成分
	float tZ = cameraAxisZ.dot(reverseEyePosition);	// Z成分
	// 一つのベクトルにまとめる
	Vector3 translation = { tX , tY , tZ };
	// ビュー行列に平行移動成分を設定
	matView.m[3][0] = translation.x;
	matView.m[3][1] = translation.y;
	matView.m[3][2] = translation.z;
	matView.m[3][3] = 1;

#pragma region 全方向ビルボード行列の計算
	// ビルボード行列
	matBillboard.m[0][0] = cameraAxisX.x;
	matBillboard.m[0][1] = cameraAxisX.y;
	matBillboard.m[0][2] = cameraAxisX.z;
	matBillboard.m[0][3] = 0;
	matBillboard.m[1][0] = cameraAxisY.x;
	matBillboard.m[1][1] = cameraAxisY.y;
	matBillboard.m[1][2] = cameraAxisY.z;
	matBillboard.m[1][3] = 0;
	matBillboard.m[2][0] = cameraAxisZ.x;
	matBillboard.m[2][1] = cameraAxisZ.y;
	matBillboard.m[2][2] = cameraAxisZ.z;
	matBillboard.m[2][3] = 0;
	matBillboard.m[3][0] = 0;
	matBillboard.m[3][1] = 0;
	matBillboard.m[3][2] = 0;
	matBillboard.m[3][3] = 1;
#pragma region

#pragma region Y軸回りビルボード行列の計算
	// カメラX軸、Y軸、Z軸
	Vector3 ybillCameraAxisX, ybillCameraAxisY, ybillCameraAxisZ;

	// X軸は共通
	ybillCameraAxisX = cameraAxisX;
	// Y軸はワールド座標系のY軸
	ybillCameraAxisY = upVector.nomalize();
	// Z軸はX軸→Y軸の外積で求まる
	ybillCameraAxisZ = ybillCameraAxisX.cross(ybillCameraAxisY);

	// Y軸回りビルボード行列
	matBillboardY.m[0][0] = cameraAxisX.x;
	matBillboardY.m[0][1] = cameraAxisX.y;
	matBillboardY.m[0][2] = cameraAxisX.z;
	matBillboardY.m[0][3] = 0;
	matBillboardY.m[1][0] = cameraAxisY.x;
	matBillboardY.m[1][1] = cameraAxisY.y;
	matBillboardY.m[1][2] = cameraAxisY.z;
	matBillboardY.m[1][3] = 0;
	matBillboardY.m[2][0] = cameraAxisZ.x;
	matBillboardY.m[2][1] = cameraAxisZ.y;
	matBillboardY.m[2][2] = cameraAxisZ.z;
	matBillboardY.m[2][3] = 0;
	matBillboardY.m[3][0] = 0;
	matBillboardY.m[3][1] = 0;
	matBillboardY.m[3][2] = 0;
	matBillboardY.m[3][3] = 1;

#pragma endregion
}

void Camera::UpdateProjectionMatrix()
{
	// 透視投影による射影行列の生成
	MakePerspectiveL(
		FieldOfViewY(),
		aspectRatio,
		0.1f, 100000.0f,
		matProjection
	);
}

void Camera::MoveEyeVector(const Vector3& move)
{
	// 視点座標を移動し、反映
	Vector3 eye_moved = GetEye();

	eye_moved.x += move.x;
	eye_moved.y += move.y;
	eye_moved.z += move.z;

	SetEye(eye_moved);
}

void Camera::MoveVector(const Vector3& move)
{
	// 視点と注視点座標を移動し、反映
	Vector3 eye_moved = GetEye();
	Vector3 target_moved = GetTarget();

	eye_moved.x += move.x;
	eye_moved.y += move.y;
	eye_moved.z += move.z;

	target_moved.x += move.x;
	target_moved.y += move.y;
	target_moved.z += move.z;

	SetEye(eye_moved);
	SetTarget(target_moved);
}

float Camera::FieldOfViewY()
{
	 float ans = static_cast <float>(2 * atan(sensor_ / (2 * focalLengs_)));
	return  ans;

}

void Camera::MakePerspectiveL(float fovAngleY, float aspect, float near_, float far_, Matrix4& matrix)
{

	float h = static_cast <float>(1 / tan(fovAngleY * 0.5));
	float w = h / aspect;
	float a = far_ / (far_ - near_);
	float b = (-near_ * far_) / (far_ - near_);

	matrix = {
		w , 0 , 0 , 0 ,
		0 , h , 0 , 0 ,
		0 , 0 , a , 1 ,
		0 , 0 , b , 0
	};
}

void Camera::MakeLookL(const Vector3& eye, const Vector3& target, const Vector3& up, Matrix4& mat)
{
	Vector3 zVec = target - eye;
	zVec.nomalize();

	Vector3 xVec = up.cross(zVec);
	xVec.nomalize();

	Vector3 yVec = zVec.cross(xVec);
	yVec.nomalize();

	mat.m[0][0] = xVec.x;
	mat.m[0][1] = xVec.y;
	mat.m[0][2] = xVec.z;
	mat.m[1][0] = yVec.x;
	mat.m[1][1] = yVec.y;
	mat.m[1][2] = yVec.z;
	mat.m[2][0] = zVec.x;
	mat.m[2][1] = zVec.y;
	mat.m[2][2] = zVec.z;
	mat.m[3][0] = eye.x;
	mat.m[3][1] = eye.y;
	mat.m[3][2] = eye.z;
}

void Camera::disEyeTarget(Vector3 pos1, Vector3 pos2)
{

	 pos1_ = pos1;
	 pos2_ = pos2;

	Vector3 distance = (pos2_ - pos1_)/2;
	//distance.nomalize();
	Vector3 disXtoZ;
	disXtoZ.x = distance.x * 2;
	disXtoZ.y = 20.0f;
	disXtoZ.z = distance.z * 2 - 100.0f;

	Vector3 target = { 0,45.0f,0 };

	SetEye(disXtoZ);
	SetTarget(target);


}

void Camera::MoveTarget(Input* input)
{
	if (input->PushKey(DIK_LEFT))
	{
		target.x -= 0.5f;
	}
	if (input->PushKey(DIK_RIGHT))
	{
		target.x += 0.5f;
	}
	if (input->PushKey(DIK_UP))
	{
		target.z += 0.5f;
	}
	if (input->PushKey(DIK_DOWN))
	{
		target.z -= 0.5f;
	}

	SetTarget(target);
}



