#pragma once

#include "BaseCollider.h"
#include "CollisionPrimitive.h"
#include "MyMath.h"

class SphereCollider : public BaseCollider , public Sphere
{
public:
	SphereCollider(Vector3 offset = {0 , 0 , 0} , float radius = 1.0f) :
		offset(offset) ,
		radius_(radius)
	{
		//���`����Z�b�g
		shapeType = COLLISIONSHAPE_SPHERE;
	}

	//�X�V
	void Update() override;

	inline void SetRadius(float radius)
	{
		radius_ = radius; 
	}
	
	float GetRadius()
	{
		return radius_; 
	}
	
	inline void SetBasisPos(Vector3* pos)
	{
		basisPos = pos;
	}

	Vector3 GetBasisPos()
	{
		return *basisPos;
	}

private:
	//�I�u�W�F�N�g���S����̃I�t�Z�b�g
	Vector3 offset;

	//���f�����Ȃ��ꍇ�̊�ƂȂ�x�N�g��
	Vector3* basisPos = nullptr;

	//���a
	float radius_;

};

