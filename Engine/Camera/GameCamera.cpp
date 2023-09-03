#include "GameCamera.h"
#include "Vector3.h"
#include "Ease.h"
GameCamera::GameCamera(int width, int height, Input* input) : Camera(width, height)
{
	input_ = input;

	//�J�����̏�����
	Vector3 eye = eye_;
	Vector3 target = target_;
	Vector3 up = up_;

	this->SetEye(eye);
	this->SetTarget(target);
	this->SetUp(up);

	//followerPos_->initialize();
	//targetPos_->initialize();

}

GameCamera::~GameCamera()
{

}

void GameCamera::Initialize()
{

}

void GameCamera::Update()
{
	MoveCamera();

	Camera::Update();
}

void GameCamera::MoveCamera()
{
	//�J�����̈ʒu
	Vector3 eyeVec = followerPos_->translation_ - targetPos_->translation_;

	Vector3 eyePos = eyeVec;

	float mag = 1.0f;
	float eyeLen = eyePos.length();//�x�N�g���̒���

	if (eyeLen > 1.0f) {	//���������̃x�N�g�����P�ʃx�N�g�����傫��������
		mag = 1.0f / eyeLen; //�x�N�g���̒�����1�ɂ���
	};

	eyePos.x *= mag;	//mag��������Ɛ��K�������
	eyePos.y *= mag;
	eyePos.z *= mag;

	cameraDistance_ = Ease::InQuad(MIN_CAMERA_DISTANCE, MAX_CAMERA_DISTANCE, cameraModeChangeCountTimer, MAX_CHANGE_TIMER);
	cameraHeight_ = Ease::InQuad(3, 6, cameraModeChangeCountTimer, MAX_CHANGE_TIMER);

	Vector3 primalyCamera =
	{ followerPos_->translation_.x + eyePos.x * cameraDistance_ ,//���@����������ʒu�ɃJ�������Z�b�g
		cameraHeight_ ,
		followerPos_->translation_.z + eyePos.z * cameraDistance_ };

	float eyeVecAngle = atan2f(primalyCamera.x - targetPos_->translation_.x, primalyCamera.z - targetPos_->translation_.z);//�J���������炷�ۂɎg����

	float shiftLen = -5.0f;	//���炷��
	Vector3 shiftVec = { primalyCamera.x + sinf(eyeVecAngle +MyMath::PI / 2) * shiftLen , primalyCamera.y , primalyCamera.z + cosf(eyeVecAngle + MyMath::PI / 2) * shiftLen };

	SetEye(shiftVec + loolAtPos);

	Vector3 zOffsetTarget = targetPos_->translation_ - eye_;	//�G�Ǝ��@���߂����Ă��o�O��Ȃ��悤�ɂ�����
	float targetToEyeLen = zOffsetTarget.length();
	zOffsetTarget.nomalize();
	zOffsetTarget *= targetToEyeLen * 2.0f;
	zOffsetTarget.y += 3.0f;

	SetTarget(targetPos_->translation_ /*+ (followerPos_->translation_ - followerPos_->translation_ / 2)*/);

	Camera::Update();
}



