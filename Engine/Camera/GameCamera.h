#pragma once
#include "Camera.h"
#include "Input.h"
#include "Object3d.h"

class GameCamera :
    public Camera
{
public:
    //コンストラクタ
    GameCamera(int width, int height, Input* input);
    //デストラクタ
    ~GameCamera();

    //初期化
    void Initialize();
    //更新
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

    //自機と敵を追従する

    void IsFollow(bool isFollow) { isFollow_ = isFollow; }

private:

    Input* input_ = nullptr;

    WorldTransform* targetPos_ = nullptr;
    WorldTransform* eyePos_ = nullptr;
    WorldTransform* followerPos_ = nullptr;

    float cameraHeight_ = 6;
    //カメラ距離関係
    const float  MAX_CAMERA_DISTANCE = 50.0f;
    const float  MIN_CAMERA_DISTANCE = 7.0f;
    float cameraDistance_ = 20.0f;
    const float MAX_CHANGE_TIMER = 30;
    int cameraModeChangeCountTimer = 30;

    Vector3 loolAtPos = {};

    bool isFollow_ = false;

    bool isstanby = false;

};

