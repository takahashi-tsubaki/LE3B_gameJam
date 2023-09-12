#pragma once

#include "BaseCollider.h"
#include "CollisionPrimitive.h"
#include "MyMath.h"

class SphereCollider : public BaseCollider , public Sphere
{
public:
	SphereCollider(Vector3 offset = {0 , 0 , 0} , float _radius = 1.0f) :
		offset(offset) ,
		radius_(_radius)
	{
		//球形状をセット
		shapeType = COLLISIONSHAPE_SPHERE;
	}

	//更新
	void Update() override;

	void SetRadius(float _radius)
	{
		radius_ = _radius; 
	}
	
	float GetRadius()
	{
		return radius_; 
	}
	
	void SetBasisPos(Vector3* pos)
	{
		basisPos = pos;
	}

	Vector3 GetBasisPos()
	{
		return *basisPos;
	}

	void SetOffSet(Vector3 off) { offset = off; }
	Vector3 GetOffSet() { return offset; }

private:
	//オブジェクト中心からのオフセット
	Vector3 offset;

	//モデルがない場合の基準となるベクトル
	Vector3* basisPos = nullptr;

	//半径
	float radius_;

};

