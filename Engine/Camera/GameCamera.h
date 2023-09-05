#pragma once
#include "Camera.h"
#include "Input.h"
#include "Object3d.h"

class GameCamera :
    public Camera
{
public:
    //�R���X�g���N�^
    GameCamera(int width, int height, Input* input);
    //�f�X�g���N�^
    ~GameCamera();

    //������
    void Initialize();
    //�X�V
    void Update();

    void SetTargetPos(WorldTransform* targetPos) { targetPos_ = targetPos; }
    WorldTransform* GetTargetPos() { return targetPos_; }
    void RemoveTargetPos() { targetPos_ = nullptr; }
    void SetEyePos(WorldTransform* eyePos) {eyePos_ = eyePos;}
    void SetFollowerPos(WorldTransform* wtf) { followerPos_ = wtf; }
    WorldTransform* GetEyePos() { return eyePos_; }
    void RemoveEyePos() { eyePos_ = nullptr; }
    void ViewPointMovement();

    void MoveCamera();

    //���@�ƓG��Ǐ]����

    void IsFollow(bool isFollow) { isFollow_ = isFollow; }

private:

    Input* input_ = nullptr;

    WorldTransform* targetPos_ = nullptr;
    WorldTransform* eyePos_ = nullptr;
    WorldTransform* followerPos_ = nullptr;

    float cameraHeight_ = 6;
    float cameraDistance_ = 20.0f;
    //�J���������֌W
    const float  MAX_CAMERA_DISTANCE = 50.0f;
    const float  MIN_CAMERA_DISTANCE = 7.0f;
    const float MAX_CHANGE_TIMER = 30;
    int cameraModeChangeCountTimer = 30;

    Vector3 loolAtPos = {};

    bool isFollow_ = false;

    bool isstanby = false;

};

